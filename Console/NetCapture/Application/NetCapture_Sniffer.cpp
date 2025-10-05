/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       NetCapture_Sniffer.cpp
* 
* @class      NETCAPTURE_SNIFFER
* @brief      Net Capture Sniffer class
* @ingroup    EXAMPLES
* 
* @copyright  GEN Group. All rights reserved.
* 
* @cond
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
* documentation files(the "Software"), to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense, and/ or sell copies of the Software,
* and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of
* the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
* THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
* @endcond
* 
* --------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "NetCapture_Sniffer.h"

#include "DIOFactory.h"
#include "DIOPCap.h"
#include "DIOPCap_Filters.h"

#include "XFactory.h"
#include "XConsole.h"
#include "XTrace.h"
#include "XThreadCollected.h"

#include "NetCapture_ThreadCollectedEnum.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         NETCAPTURE_FRAME::NETCAPTURE_FRAME()
* @brief      Constructor
* @ingroup    
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
NETCAPTURE_FRAME::NETCAPTURE_FRAME()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         NETCAPTURE_FRAME::~NETCAPTURE_FRAME()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
NETCAPTURE_FRAME::~NETCAPTURE_FRAME()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCAPTURE_FRAME::IsSend()
* @brief      IsSend
* @ingroup    
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCAPTURE_FRAME::IsSend()
{
  return issend;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void NETCAPTURE_FRAME::SetIsSend(bool issend)
* @brief      SetIsSend
* @ingroup    
* 
* @param[in]  issend : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void NETCAPTURE_FRAME::SetIsSend(bool issend)
{
  this->issend = issend;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBUFFER* NETCAPTURE_FRAME::GetPayLoadBuffer()
* @brief      GetPayLoadBuffer
* @ingroup    
* 
* @return     XBUFFER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBUFFER* NETCAPTURE_FRAME::GetPayLoadBuffer()
{
  return &payloadbuffer;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void NETCAPTURE_FRAME::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void NETCAPTURE_FRAME::Clean()
{

}


#pragma endregion


#pragma region CLASS_NETCAPTURE_SNIFFER


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         NETCAPTURE_SNIFFER::NETCAPTURE_SNIFFER()
* @brief      Constructor
* @ingroup    
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
NETCAPTURE_SNIFFER::NETCAPTURE_SNIFFER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         NETCAPTURE_SNIFFER::~NETCAPTURE_SNIFFER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
NETCAPTURE_SNIFFER::~NETCAPTURE_SNIFFER()
{
  Capture_End();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCAPTURE_SNIFFER::Capture_Ini()
* @brief      Capture_Ini
* @ingroup    
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCAPTURE_SNIFFER::Capture_Ini()
{
  DIOPCAPNETINTERFACE* netinterface			 = NULL; 
	int                  indexnetinterface = 4; // -1;
  bool                 status            =  false;   

  diopcap = GEN_DIOFACTORY.CreatePCap();
  if(!diopcap)  
    {
      return false;
    }
  
  if(!diopcap->Ini())
    {
      return false;
    }

  framesmutex = GEN_XFACTORY.Create_Mutex();
  if(!framesmutex)
    {
      return false;
    }
 
  for(int c=0; c<(int)diopcap->GetNetInterfaces()->GetSize(); c++)
    {
      netinterface = diopcap->GetNetInterface(c);
      if(netinterface) 
        {          
          if(indexnetinterface == -1)
            {
              if(netinterface->IsLoopBack())
                {
                  indexnetinterface = c;                    
                }
            }
            
           XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[%2d] %c %s, [%s]"), c, (indexnetinterface == c)?__C('*'):__C('-'), netinterface->GetName()->Get(), netinterface->GetDescription()->Get());						
        }
    }

  if(indexnetinterface != -1)
    {      
      threadsniffer = CREATEXTHREAD((XTHREADGROUPID)NETCAPTURE_XTHREADGROUPID_SNIFFER, __L("NETCAPTURE_SNIFFER::CaptureIni"), ThreadRunFunctionSniffer, this);
      status =  threadsniffer?true:false;

      if(status)
        {
          threadmanager = CREATEXTHREAD((XTHREADGROUPID)NETCAPTURE_XTHREADGROUPID_SNIFFER, __L("NETCAPTURE_SNIFFER::CaptureIni2"), ThreadRunFunctionManager, this);
          status =  threadmanager?true:false;
          
          if(status)
            {
		          status = diopcap->Capture_Start(indexnetinterface, true, 100);
              if(status)
                {
                  status = threadsniffer->Ini(true);    
                  if(status)
                    {
                      status = threadmanager->Ini(true);    
                    }
                }        
            }
        }
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCAPTURE_SNIFFER::Capture_Manager()
* @brief      Capture_Manager
* @ingroup    
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCAPTURE_SNIFFER::Capture_Manager()
{
  XDWORD nsize = Sniffer_Get()->GetSize();

  for(XDWORD c=0;c<nsize;c++) 
	  {
      NETCAPTURE_FRAME* frame = Sniffer_Get(c);
	    if(frame) 
        {
          XBUFFER* buffer = frame->GetPayLoadBuffer();
          if(buffer)
            {
              // XTRACE_PRINTDATABLOCKCOLOR((frame->IsSend()?XTRACE_COLOR_BLUE:XTRACE_COLOR_PURPLE), (*buffer));
              //if(!buffer->IsEmpty())
              //  {
              //    XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("%02X"), buffer->Get()[0]);
              //  }
            }

          Sniffer_Del(c);
        }
    }  

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCAPTURE_SNIFFER::Capture_End()
* @brief      Capture_End
* @ingroup    
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCAPTURE_SNIFFER::Capture_End()
{
  if(threadsniffer)
    {
      threadsniffer->End();
      delete threadsniffer;

      threadsniffer =  NULL;
    }

  if(threadmanager)
    {
      threadmanager->End();
      delete threadmanager;

      threadmanager =  NULL;
    }

  if(diopcap)
    {   
 	    diopcap->Capture_End();
      diopcap->End();														

	    GEN_DIOFACTORY.DeletePCap(diopcap);

      diopcap = NULL;
    }

  if(framesmutex)
    {
      GEN_XFACTORY.Delete_Mutex(framesmutex);
      framesmutex =  NULL;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPCAP* NETCAPTURE_SNIFFER::GetDIOPCap()
* @brief      GetDIOPCap
* @ingroup    
* 
* @return     DIOPCAP* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOPCAP* NETCAPTURE_SNIFFER::GetDIOPCap()
{
  return diopcap;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCAPTURE_SNIFFER::Sniffer_Add(bool issend, XBYTE* framedata, XDWORD framesize )
* @brief      Sniffer_Add
* @ingroup    
* 
* @param[in]  issend : 
* @param[in]  framedata : 
* @param[in]  framesize : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCAPTURE_SNIFFER::Sniffer_Add(bool issend, XBYTE* framedata, XDWORD framesize ) 
{
  NETCAPTURE_FRAME* frame = NULL;
  
  frame = new NETCAPTURE_FRAME();
  if(!frame)
    {
      return false;
    }

  frame->SetIsSend(issend);
  frame->GetPayLoadBuffer()->Add(framedata, framesize);

  Sniffer_Interpreter(frame);

  if(framesmutex)
    {
      framesmutex->Lock();
    }

  frames.Add(frame);

  if(framesmutex)
    {
      framesmutex->UnLock();
    }
        
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         NETCAPTURE_FRAME* NETCAPTURE_SNIFFER::Sniffer_Get(int index)
* @brief      Sniffer_Get
* @ingroup    
* 
* @param[in]  index : 
* 
* @return     NETCAPTURE_FRAME* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
NETCAPTURE_FRAME* NETCAPTURE_SNIFFER::Sniffer_Get(int index)
{
 NETCAPTURE_FRAME* frame = NULL;

  if(framesmutex)
    {
      framesmutex->Lock();
    }

  frame = frames.Get(index);
  
  if(framesmutex)
    {
      framesmutex->UnLock();
    }

  return frame;

}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCAPTURE_SNIFFER::Sniffer_Del(int index)
* @brief      Sniffer_Del
* @ingroup    
* 
* @param[in]  index : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCAPTURE_SNIFFER::Sniffer_Del(int index)
{
  bool status = false;

  if(framesmutex)
    {
      framesmutex->Lock();
    }

  NETCAPTURE_FRAME* frame = frames.Get(index);
  if(frame)
    {
      frames.Delete(frame);
      delete frame;
      status = true;
    }

  if(framesmutex)
    {
      framesmutex->UnLock();
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCAPTURE_SNIFFER::Sniffer_DelAll()
* @brief      Sniffer_DelAll
* @ingroup    
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCAPTURE_SNIFFER::Sniffer_DelAll()
{
  if(framesmutex)
    {
      framesmutex->Lock();
    }

  bool status = false;

  frames.DeleteContents();
  frames.DeleteAll();

  if(framesmutex)
    {
      framesmutex->UnLock();
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<NETCAPTURE_FRAME*>* NETCAPTURE_SNIFFER::Sniffer_Get()
* @brief      Sniffer_Get
* @ingroup    
* 
* @return     XVECTOR<NETCAPTURE_FRAME*>* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<NETCAPTURE_FRAME*>* NETCAPTURE_SNIFFER::Sniffer_Get() 
{
  return &frames;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCAPTURE_SNIFFER::Sniffer_Interpreter(NETCAPTURE_FRAME* frame)
* @brief      Sniffer_Interpreter
* @ingroup    
* 
* @param[in]  frame : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCAPTURE_SNIFFER::Sniffer_Interpreter(NETCAPTURE_FRAME* frame)
{
  if(!frame)
    {
      return false;
    }

  XBUFFER* buffer = frame->GetPayLoadBuffer();
  if(!buffer)
    {
      return true;
    }

  XWORD ID;
  buffer->Get(ID, 0);

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void NETCAPTURE_SNIFFER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void NETCAPTURE_SNIFFER::Clean()
{
  diopcap           = NULL;
  threadsniffer     = NULL;
  threadmanager     = NULL;
  framesmutex = NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void NETCAPTURE_SNIFFER::ThreadRunFunctionSniffer(void* param)
* @brief      ThreadRunFunctionSniffer
* @ingroup    
* 
* @param[in]  param : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void NETCAPTURE_SNIFFER::ThreadRunFunctionSniffer(void* param)
{
  NETCAPTURE_SNIFFER* sniffer = (NETCAPTURE_SNIFFER*)param;
  if(!sniffer) return;

  DIOPCAP* diopcap = sniffer->GetDIOPCap();
  if(!diopcap)
    {
      return;
    }
  
  XDWORD nsize = diopcap->Frames_Get()->GetSize();

  for(XDWORD c=0;c<nsize;c++) 
	  {
      DIOPCAPFRAME* frame = diopcap->Frames_Get(c);
	    if(frame) 
        {
          //if(diopcap->GetFilters()->Entrys_Check(frame))
            { 
              XSTRING protocoltypestr;
              XSTRING sourceMAC;
              XSTRING sourceIP;
              XSTRING targetMAC;
              XSTRING targetIP;

              frame->GetProtocolTypeString(protocoltypestr);
              frame->GetSourceMAC()->GetXString(sourceMAC);
              frame->GetSourceIP()->GetXString(sourceIP);
              frame->GetTargetMAC()->GetXString(targetMAC);
              frame->GetTargetIP()->GetXString(targetIP);
             
              XTRACE_PRINTCOLOR(XTRACE_COLOR_PURPLE, __L("----------------------------------------------------------------------------------------------------"));

              XTRACE_PRINTCOLOR(XTRACE_COLOR_PURPLE, __L("%s    [%s](%s) -> [%s](%s)  port [%d]") , protocoltypestr.Get()
                                                                                                  , sourceMAC.Get()
                                                                                                  , sourceIP.Get()
                                                                                                  , targetMAC.Get()
                                                                                                  , targetIP.Get()
                                                                                                  , frame->GetSourcePort());

              XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_BLUE, frame->GetDataPayload(), frame->GetDataPayLoadSize()); 
            }       

          diopcap->Frames_Delete(c);
        }
    }  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void NETCAPTURE_SNIFFER::ThreadRunFunctionManager(void* param)
* @brief      ThreadRunFunctionManager
* @ingroup    
* 
* @param[in]  param : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void NETCAPTURE_SNIFFER::ThreadRunFunctionManager(void* param)
{
  NETCAPTURE_SNIFFER* sniffer = (NETCAPTURE_SNIFFER*)param;
  if(!sniffer) return;

  sniffer->Capture_Manager();

}


#pragma endregion


#pragma endregion


