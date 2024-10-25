/**-------------------------------------------------------------------------------------------------------------------
*
* @file       NetConn.cpp
*
* @class      NETCONN
* @brief      Net Connection class (DIOCoreProtol example)
* @ingroup    EXAMPLES  
*
* @copyright  GEN Group. All right reserved.
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
*---------------------------------------------------------------------------------------------------------------------*/


/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "NetConn.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#include "VersionFrameWork.h"

#include "XPath.h"
#include "XDateTime.h"
#include "XTimer.h"
#include "XFactory.h"
#include "XRand.h"
#include "XDir.h"
#include "XString.h"
#include "XSystem.h"
#include "XLog.h"
#include "XConsole.h"
#include "XFileTXT.h"
#include "XFileCSV.h"
#include "XFileXML.h"
#include "XTranslation.h"
#include "XTranslation_GEN.h"
#include "XScheduler.h"
#include "XScheduler_XEvent.h"
#include "XConsole.h"
#include "XThread.h"
#include "XTrace.h"
#include "XObserver.h"

#include "HashMD5.h"

#include "DIOFactory.h"
#include "DIOStreamCipher.h"
#include "DIOStreamDeviceIP.h"
#include "DIOStreamIPLocalEnumDevices.h"
#include "DIOStreamTCPIPConfig.h"
#include "DIOStreamTCPIP.h"
#include "DIOWebClient_XEvent.h"
#include "DIOWebClient.h"

#include "DIOCheckTCPIPConnections.h"
#include "DIOCheckInternetConnection.h"

#include "DIOScraperWeb.h"
#include "DIOScraperWebPublicIP.h"
#include "DIOScraperWebGeolocationIP.h"
#include "DIOScraperWebUserAgentID.h"

#include "APPLog.h"
#include "APPInternetServices.h"
#include "APPExtended.h"

#include "NetConn_CFG.h"
#include "NetConn_Connections.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

 APPLICATIONCREATEINSTANCE(NETCONN, netconn)

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         NETCONN::NETCONN() : XFSMACHINE(0)
* @brief      Constructor
* @ingroup    APPLICATION
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
NETCONN::NETCONN() :  XFSMACHINE(0)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         NETCONN::~NETCONN()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    APPLICATION
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
NETCONN::~NETCONN()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCONN::InitFSMachine()
* @brief      InitFSMachine
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCONN::InitFSMachine()
{
  if(!AddState( NETCONN_XFSMSTATE_NONE           ,
                NETCONN_XFSMEVENT_INI              , NETCONN_XFSMSTATE_INI            ,
                NETCONN_XFSMEVENT_END              , NETCONN_XFSMSTATE_END            ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( NETCONN_XFSMSTATE_INI              ,
                NETCONN_XFSMEVENT_NONE           , NETCONN_XFSMSTATE_NONE         ,
                NETCONN_XFSMEVENT_END              , NETCONN_XFSMSTATE_END            ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( NETCONN_XFSMSTATE_END              ,
                NETCONN_XFSMEVENT_NONE           , NETCONN_XFSMSTATE_NONE         ,
                NETCONN_XFSMEVENT_INI              , NETCONN_XFSMSTATE_INI            ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCONN::AppProc_Ini()
* @brief      AppProc_Ini
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCONN::AppProc_Ini()
{
  XSTRING string;
  XSTRING stringresult;
  XPATH   xpathsection;
  XPATH   xpath;
  bool    status = false;

  //-------------------------------------------------------------------------------------------------

  GEN_SET_VERSION(APPLICATION_NAMEAPP, APPLICATION_NAMEFILE, APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR, APPLICATION_OWNER, APPLICATION_YEAROFCREATION)

  GetApplicationName()->Set(APPLICATION_NAMEAPP);
  
  //--------------------------------------------------------------------------------------------------

  ACTIVATEXTHREADGROUP(XTHREADGROUPID_SCHEDULER);
  ACTIVATEXTHREADGROUP(XTHREADGROUPID_DIOSTREAM);

  //--------------------------------------------------------------------------------------------------

  XTRACE_SETAPPLICATIONNAME((*GetApplicationName()));
  XTRACE_SETAPPLICATIONVERSION(APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR);
  XTRACE_SETAPPLICATIONID(string);

  //--------------------------------------------------------------------------------------------------

  GEN_XPATHSMANAGER.AdjustRootPathDefault(APPDEFAULT_DIRECTORY_ROOT);

  GEN_XPATHSMANAGER.CreateAllPathSectionOnDisk();

  //--------------------------------------------------------------------------------------------------

  if(GetExecParams())
    {
      XSTRING* param = (XSTRING*)GetExecParams()->Get(0);
      if(param)
        {
          if(!param->Compare(__L("SERVER"), true))  modeserver = true;
        }
    }

  //--------------------------------------------------------------------------------------------------

  InitFSMachine();

  //--------------------------------------------------------------------------------------------------

  xmutexshowallstatus = GEN_XFACTORY.Create_Mutex();
  if(!xmutexshowallstatus) return false;

  //--------------------------------------------------------------------------------------------------

  APP_CFG_SETAUTOMATICTRACETARGETS

  //--------------------------------------------------------------------------------------------------

  /*
  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathsection);
  xpath.Create(3 , xpathsection.Get(), NETCONN_LNG_NAMEFILE, XTRANSLATION_NAMEFILEEXT);

  if(!GEN_XTRANSLATION.Ini(xpath))
    {
      return false;
    }
  */

  GEN_XTRANSLATION.SetActual(XLANGUAGE_ISO_639_3_CODE_SPA);

  //--------------------------------------------------------------------------------------------------

  APP_EXTENDED.APPStart(&APP_CFG, this);

  //--------------------------------------------------------------------------------------------------

  SetEvent(NETCONN_XFSMEVENT_INI);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCONN::AppProc_FirstUpdate()
* @brief      AppProc_FirstUpdate
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCONN::AppProc_FirstUpdate()
{
  XSTRING string;
  XSTRING stringresult;
  bool    status = false;

  //--------------------------------------------------------------------------------------------------

  xtimerupdateconsole = GEN_XFACTORY.CreateTimer();
  if(!xtimerupdateconsole) return false;

  //--------------------------------------------------------------------------------------------------

  connections = new NETCONN_CONNECTIONS();
  if(connections)
    {
      if(!connections->Ini(modeserver))
        {
          return false;
        }
    }
  
  //--------------------------------------------------------------------------------------------------

  
  //console->PrintMessage(__L(" "), 0, false, true);
  //console->WaitKey(__L("  Pulsa una tecla para continuar... (%d)"), 1, false, 5);

  //--------------------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCONN::AppProc_Update()
* @brief      AppProc_Update
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCONN::AppProc_Update()
{
  if(GetEvent()==NETCONN_XFSMEVENT_NONE) // Not new event
    {
      switch(GetCurrentState())
        {
          case NETCONN_XFSMSTATE_NONE      : break;

          case NETCONN_XFSMSTATE_INI       : if(GetExitType() == APPBASE_EXITTYPE_UNKNOWN)
                                                {
                                                  if(xtimerupdateconsole)
                                                    {
                                                      if(xtimerupdateconsole->GetMeasureSeconds() >= 1)
                                                        {
                                                          Show_AllStatus();
                                                          xtimerupdateconsole->Reset();
                                                        }

                                                      if(console->KBHit())
                                                        {
                                                          int key = console->GetChar();
                                                          KeyValidSecuences(key);
                                                        }
                                                    }
                                                }
                                              break;

          case NETCONN_XFSMSTATE_END       : break;

        }
    }
   else //  New event
    {
      if(GetEvent()<NETCONN_LASTEVENT)
        {
          CheckTransition();

          switch(GetCurrentState())
            {
              case NETCONN_XFSMSTATE_NONE  : break;

              case NETCONN_XFSMSTATE_INI   : break;

              case NETCONN_XFSMSTATE_END   : break;
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCONN::AppProc_End()
* @brief      AppProc_End
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCONN::AppProc_End()
{
  XSTRING string;
  XSTRING stringresult;

  //--------------------------------------------------------------------------------------

  SetEvent(NETCONN_XFSMEVENT_END);

  //--------------------------------------------------------------------------------------

  if(connections)
    {
      connections->End();
      delete connections;
      connections = NULL;        
    }

  //--------------------------------------------------------------------------------------

  if(xmutexshowallstatus)
    {
      GEN_XFACTORY.Delete_Mutex(xmutexshowallstatus);
      xmutexshowallstatus = NULL;
    }

  //--------------------------------------------------------------------------------------

  if(xtimerupdateconsole)
    {
      GEN_XFACTORY.DeleteTimer(xtimerupdateconsole);
      xtimerupdateconsole = NULL;
    }

  //--------------------------------------------------------------------------------------

  APP_EXTENDED.APPEnd();
  APP_EXTENDED.DelInstance();  
  APP_CFG.DelInstance();

  //--------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool NETCONN::KeyValidSecuences(int key)
* @brief      KeyValidSecuences
* @ingroup    APPLICATION
*
* @param[in]  key :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCONN::KeyValidSecuences(int key)
{
  XCHAR character = (XCHAR)key;

  if((character<32) || (character>127)) character = __C('?');
  APP_LOG_ENTRY(XLOGLEVEL_WARNING, APP_CFG_LOG_SECTIONID_STATUSAPP, false, __L("Key pressed: 0x%02X [%c]"), key, character);

  console->Printf(__L("\r    \r"));

  switch(key)
    {
      case 0x1B : // ESC Exit application
                  SetExitType(APPBASE_EXITTYPE_BY_USER);
                  break;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCONN::Show_ConnectionsStatus()
* @brief      Show_ConnectionsStatus
* @ingroup    EXAMPLES
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCONN::Show_ConnectionsStatus()
{ 
  XSTRING string;
  XSTRING string2;

  if(!connections)
    {
      return false;
    }

  DIOCOREPROTOCOL_CFG* protocolCFG = connections->GetProtocolCFG();
  if(!protocolCFG)
    {
      return false;
    }

  string  = __L("Connexion mode");
  if(protocolCFG->GetIsServer())
          string2.Format(__L("Server"));
    else  string2.Format(__L("Client"));
  Show_Line(string, string2);

  if(protocolCFG->GetDIOStream())
    {
      string  = __L("Connexion status");
      
      switch(protocolCFG->GetDIOStream()->GetConnectStatus())
        {
          case DIOSTREAMSTATUS_DISCONNECTED      : string2.Format(__L("Disconnected"));              break;
          case DIOSTREAMSTATUS_CONNECTED         : string2.Format(__L("Connected"));                 break; 
          case DIOSTREAMSTATUS_GETTINGCONNECTION : string2.Format(__L("Getting connexion..."));      break; 
        }

      Show_Line(string, string2);
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool NETCONN::Show_AllStatus()
* @brief      Show_AllStatus
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCONN::Show_AllStatus()
{
  if(xmutexshowallstatus) xmutexshowallstatus->Lock();

  APP_EXTENDED.ShowAll();

  Show_ConnectionsStatus();

  if(xmutexshowallstatus) xmutexshowallstatus->UnLock();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void NETCONN::HandleEvent_ServerProtocolConnections(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT* event)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    APPLICATION
*
* @param[in]  event :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
/*
void NETCONN::HandleEvent_ServerProtocolConnections(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT* event)
{
  switch(event->GetEventType())
    {
      case DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_CONNECTEDCONNECTION    : break;

      case DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_INITPROTOCOL           : { DIOPROTOCOL_CONNECTION*  protocolconnection  =  event->GetProtocolConnection();
                                                                                  NETCONN_PROTOCOL*    protocol            =  NULL;
                                                                                  XSTRING                 IPstring;
                                                                                  bool                    status              = false;

                                                                                  if(!protocolconnection)  break;

                                                                                  protocol= (NETCONN_PROTOCOL*)protocolconnection->GetDIOProtocol();
                                                                                  if(!protocol)
                                                                                    {
                                                                                      XTRACE_PRINTCOLOR(4, __L("Ini Server protocol: Not instance protocol."));
                                                                                      break;
                                                                                    }

                                                                                  NETCONN_APPLICATIONDATA* applicationdata = (NETCONN_APPLICATIONDATA*)protocol->GetApplicationData();
                                                                                  if(!applicationdata)
                                                                                    {
                                                                                      XTRACE_PRINTCOLOR(4, __L("Ini Server protocol from %s: Not instance protocol data."), IPstring.Get());
                                                                                      break;
                                                                                    }

                                                                                  status = InitializeProtocolConnectionServer(protocol, applicationdata);

                                                                                  protocol->SetIsInitialized(status);
                                                                                }
                                                                                break;

      case DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_DISCONNECTEDCONNECTION :  { DIOPROTOCOL_CONNECTION* protocolconnection = event->GetProtocolConnection();
                                                                                  if(!protocolconnection)  break;

                                                                                  NETCONN_PROTOCOL* protocol = (NETCONN_PROTOCOL*)protocolconnection->GetDIOProtocol();
                                                                                  if(!protocol) break;

                                                                                  NETCONN_APPLICATIONDATA* applicationdata = (NETCONN_APPLICATIONDATA*)protocol->GetApplicationData();
                                                                                  if(!applicationdata) break;
                                                                                }
                                                                                break;

    }
}
*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void NETCONN::HandleEvent_ClientProtocolConnections(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT* event)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    APPLICATION
*
* @param[in]  event :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
/*
void NETCONN::HandleEvent_ClientProtocolConnections(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT* event)
{
  switch(event->GetEventType())
    {
      case DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_CONNECTEDCONNECTION       : break;

      case DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_INITPROTOCOL              : { DIOPROTOCOL_CONNECTION*  protocolconnection = event->GetProtocolConnection();
                                                                                    NETCONN_PROTOCOL*     protocol           = NULL;
                                                                                    bool                     status             = false;

                                                                                    if(protocolconnection) protocol = (NETCONN_PROTOCOL*)protocolconnection->GetDIOProtocol();
                                                                                    if(!protocol) break;

                                                                                    NETCONN_APPLICATIONDATA* applicationdata = (NETCONN_APPLICATIONDATA*)protocol->GetApplicationData();
                                                                                    if(!applicationdata) break;

                                                                                    status = InitializeProtocolConnectionClient(protocol, applicationdata);

                                                                                    protocol->SetIsInitialized(status);
                                                                                  }
                                                                                  break;

      case DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_DISCONNECTEDCONNECTION  : { DIOPROTOCOL_CONNECTION* protocolconnection =  event->GetProtocolConnection();
                                                                                  DIOPROTOCOL*            protocol          =  NULL;

                                                                                  if(protocolconnection) protocol =  protocolconnection->GetDIOProtocol();
                                                                                  if(!protocol)  break;
                                                                                }
                                                                                break;

    }
}
*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         NETCONN::HandleEvent
* @brief      Handle Events
* @ingroup
*
* @param[]    xevent : event send to control
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void NETCONN::HandleEvent(XEVENT* xevent)
{
  if(!xevent) return;

  /*
  switch(xevent->GetEventFamily())
    {

      case XEVENT_TYPE_PROTOCOLCONNECTIONS     : { DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT* event = (DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT*)xevent;
                                                  if(!event) return;

                                                  if(modeserver)
                                                         HandleEvent_ServerProtocolConnections(event);
                                                    else HandleEvent_ClientProtocolConnections(event);
                                                }
                                                break;


    }
  */
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void NETCONN::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void NETCONN::Clean()
{
  xtimerupdateconsole         = NULL;
  xmutexshowallstatus         = NULL;

  modeserver                  = false;
 
  connections                 = NULL; 
}
