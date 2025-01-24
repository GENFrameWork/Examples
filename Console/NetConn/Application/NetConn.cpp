/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       NetConn.cpp
* 
* @class      NETCONN
* @brief      Net Connection class (DIOCoreProtocol example)
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
#include "DIOCoreProtocol_Connection.h"
#include "DIOWebClient_XEvent.h"
#include "DIOWebClient.h"

#include "DIOCheckTCPIPConnections.h"
#include "DIOCheckInternetConnection.h"

#include "DIOScraperWeb.h"
#include "DIOScraperWebPublicIP.h"
#include "DIOScraperWebGeolocationIP.h"
#include "DIOScraperWebUserAgentID.h"

#include "DIOCoreProtocol_ConnectionsManager_XEvent.h"

#include "APPFlowLog.h"
#include "APPFlowInternetServices.h"
#include "APPFlowExtended.h"

#include "NetConn_CFG.h"
#include "NetConn_CoreProtocol.h"
#include "NetConn_CoreProtocol_Connection.h"
#include "NetConn_CoreProtocol_ConnectionsManager.h"
#include "NetConn_CoreProtocol_Response.h"

#include "NetConn_AgentState.h"
#include "NetConn_TestUpdateClass.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

APPLICATIONCREATEINSTANCE(NETCONN, netconn)

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         NETCONN::NETCONN() : XFSMACHINE(0)
* @brief      Constructor
* @ingroup    APPLICATION
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
NETCONN::NETCONN() : XFSMACHINE(0)
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
  if(!AddState( NETCONN_XFSMSTATE_NONE            ,
                NETCONN_XFSMEVENT_INI             , NETCONN_XFSMSTATE_INI             ,
                NETCONN_XFSMEVENT_END             , NETCONN_XFSMSTATE_END             ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( NETCONN_XFSMSTATE_INI             ,
                NETCONN_XFSMEVENT_UPDATE          , NETCONN_XFSMSTATE_UPDATE          ,
                NETCONN_XFSMEVENT_END             , NETCONN_XFSMSTATE_END             ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( NETCONN_XFSMSTATE_UPDATE          ,                
                NETCONN_XFSMEVENT_END             , NETCONN_XFSMSTATE_END             ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( NETCONN_XFSMSTATE_END             ,
                NETCONN_XFSMEVENT_NONE            , NETCONN_XFSMSTATE_NONE            ,
                NETCONN_XFSMEVENT_INI             , NETCONN_XFSMSTATE_INI             ,
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
 
  GEN_XPATHSMANAGER.AdjustRootPathDefault(APPFLOW_DEFAULT_DIRECTORY_ROOT);

  GEN_XPATHSMANAGER.CreateAllPathSectionOnDisk(); 

 //--------------------------------------------------------------------------------------------------

  /*
  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathsection);
  xpath.Create(3 , xpathsection.Get(), NETCONN_LNG_NAMEFILE, XTRANSLATION_NAMEFILEEXT);

  if(!GEN_XTRANSLATION.Ini(xpath))
    {
      return false;
    }
  */

  GEN_XTRANSLATION.SetActual(XLANGUAGE_ISO_639_3_CODE_ENG);

  //--------------------------------------------------------------------------------------------------

  if(GetExecParams())
    {
      XSTRING* param = (XSTRING*)GetExecParams()->Get(0);
      if(param)
        {
          modeserver = APPFLOW_CFG.Connection_IsServer();

          if(!param->Compare(__L("SERVER"), true))  
            {
              modeserver = true;
            }

          if(!param->Compare(__L("CLIENT"), true))  
            {
              modeserver = false;
            }
        }
    }

  //--------------------------------------------------------------------------------------------------

  Application_GetName()->AddFormat(__L("%s %s"), APPLICATION_NAMEAPP, modeserver?__L("Server"):__L("Client")); 

  GEN_SET_VERSION(Application_GetName()->Get(), APPLICATION_NAMEFILE, APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR, APPLICATION_OWNER, APPLICATION_YEAROFCREATION)
  
  //--------------------------------------------------------------------------------------------------

  XTRACE_SETAPPLICATIONNAME((*Application_GetName()));
  XTRACE_SETAPPLICATIONVERSION(APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR);
  XTRACE_SETAPPLICATIONID(string);

  //--------------------------------------------------------------------------------------------------

  APPFLOW_CFG_SETAUTOMATICTRACETARGETS

  //--------------------------------------------------------------------------------------------------

  InitFSMachine();

  //--------------------------------------------------------------------------------------------------

  xmutexshowallstatus = GEN_XFACTORY.Create_Mutex();
  if(!xmutexshowallstatus) return false;

  //--------------------------------------------------------------------------------------------------

  APPFLOW_EXTENDED.APPStart(&APPFLOW_CFG, this);

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

  if(!modeserver)
    {
      agentstate = new NETCONN_AGENTSTATE();
      if(agentstate)
        {
          agentstate->Update();          
        }

      testupdateclass = new NETCONN_TESTUPDATECLASS();
      if(testupdateclass)
        {
          testupdateclass->Update();
        }
    }

  //--------------------------------------------------------------------------------------------------

  connectionsmanager = new NETCONN_COREPROTOCOL_CONNECTIONSMANAGER();
  if(connectionsmanager)
    {
      if(!connectionsmanager->Ini(modeserver))
        {
          return false;
        }

      SubscribeEvent(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_COMMANDRESPONSE , connectionsmanager);     
      SubscribeEvent(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_UPDATECLASS     , connectionsmanager);     
      SubscribeEvent(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_ASKUPDATECLASS  , connectionsmanager);     
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
          case NETCONN_XFSMSTATE_NONE       : break;

          case NETCONN_XFSMSTATE_INI        : break;

          case NETCONN_XFSMSTATE_UPDATE     : if(GetExitType() == APPFLOWBASE_EXITTYPE_UNKNOWN)
                                                {
                                                  if(xtimerupdateconsole)
                                                    {
                                                      if(xtimerupdateconsole->GetMeasureMilliSeconds() >= 100)
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
              case NETCONN_XFSMSTATE_NONE   : break;

              case NETCONN_XFSMSTATE_INI    : SetEvent(NETCONN_XFSMEVENT_UPDATE);
                                              break;

              case NETCONN_XFSMSTATE_UPDATE : break;

              case NETCONN_XFSMSTATE_END    : break;
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

  if(connectionsmanager)
    {
      UnSubscribeEvent(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_COMMANDRESPONSE , connectionsmanager);
      UnSubscribeEvent(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_UPDATECLASS     , connectionsmanager);
      UnSubscribeEvent(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_ASKUPDATECLASS  , connectionsmanager);
      
      connectionsmanager->End();
      delete connectionsmanager;
      connectionsmanager = NULL;        
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

  if(!modeserver)
    {      
      if(agentstate)
        {
          delete agentstate;
          agentstate = NULL;  
        }

      if(testupdateclass)
        {
          delete testupdateclass;
          testupdateclass = NULL;
        }
    }

  //--------------------------------------------------------------------------------------

  APPFLOW_EXTENDED.APPEnd();
  APPFLOW_EXTENDED.DelInstance();  
  APPFLOW_CFG.DelInstance();

  //--------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCONN::IsServer()
* @brief      IsServer
* @ingroup    EXAMPLES
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCONN::IsServer()
{
  return netconn->modeserver;
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
  APPFLOW_LOG_ENTRY(XLOGLEVEL_WARNING, APPFLOW_CFG_LOG_SECTIONID_STATUSAPP, false, __L("Key pressed: 0x%02X [%c]"), key, character);

  console->Printf(__L("\r    \r"));

  switch(key)
    {
      case 0x1B : // ESC Exit application
                  SetExitType(APPFLOWBASE_EXITTYPE_BY_USER);
                  break;

      case 'T'  : if(connectionsmanager)
                    { 
                      DIOCOREPROTOCOL_CONNECTION* connection = connectionsmanager->Connections_Get((XDWORD)0);
                      XSTRING                     result;
                      bool                        status;

                      status = connectionsmanager->Command_Do(connection, NETCONN_COREPROTOCOL_COMMAND_TYPE_GETVERSION, result, 10);
                      XTRACE_PRINTCOLOR(status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED, __L("[Core Protocol Command: Get version] Result: \"%s\""), status?result.Get():__L("Error!"));                        
                    }
                  break;

      case 'Y'  : if(connectionsmanager)
                    { 
                      DIOCOREPROTOCOL_CONNECTION* connection = connectionsmanager->Connections_Get((XDWORD)0);
                      XSTRING                     result;
                      bool                        status;

                      status = connectionsmanager->Command_Do(connection, NETCONN_COREPROTOCOL_COMMAND_TYPE_OTHERCOMMAND, result, 10);
                      XTRACE_PRINTCOLOR(status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED, __L("[Core Protocol Command: Other command] Result: \"%s\""), status?result.Get():__L("Error!"));
                    }
                  break;


      case 'U'  : if(connectionsmanager)
                    { 
                      NETCONN_COREPROTOCOL_CONNECTION*  connection  = (NETCONN_COREPROTOCOL_CONNECTION*)connectionsmanager->Connections_Get((XDWORD)0);                                                                
                      bool                              status      = false;
  
                      if(!connection->IsServer())
                        {                            
                          status = connectionsmanager->UpdateClass_Do(connection, __L("testupdateclass"), connection->GetTestUpdateClass(), 10);
                        }
                                            
                      XTRACE_PRINTCOLOR(status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED, __L("[Update class Test Update Class Client->Server] Result: \"%s\""), status?__L("Ok"):__L("Error!"));
                    }
                  break;

      case 'I'  : if(connectionsmanager)
                    { 
                      NETCONN_COREPROTOCOL_CONNECTION*  connection  = (NETCONN_COREPROTOCOL_CONNECTION*)connectionsmanager->Connections_Get((XDWORD)0);                                                                
                      bool                              status      = false;
                        
                      status = connectionsmanager->UpdateClass_DoAsk(connection, __L("testupdateclass"), connection->GetTestUpdateClass(), 10);
                                            
                      XTRACE_PRINTCOLOR(status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED, __L("[Update class Test Update Class Server Ask Client] Result: \"%s\""), status?__L("Ok"):__L("Error!"));
                    }
                  break;

   
      case 'O'  : if(connectionsmanager)
                    { 
                      NETCONN_COREPROTOCOL_CONNECTION*  connection  = (NETCONN_COREPROTOCOL_CONNECTION*)connectionsmanager->Connections_Get((XDWORD)0);                                                                
                      bool                              status      = false;
  
                      if(!connection->IsServer())
                        {                            
                          status = connection->GetTestUpdateClass()->Update();
                        }
                                            
                      XTRACE_PRINTCOLOR(status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED, __L("[Update class Test Update Class Client->Server] Result: \"%s\""), status?__L("Ok"):__L("Error!"));
                    }
                  break;


    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         NETCONN_AGENTSTATE* NETCONN::GetAgentState()
* @brief      GetAgentState
* @ingroup    EXAMPLES
* 
* @return     NETCONN_AGENTSTATE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
NETCONN_AGENTSTATE* NETCONN::GetAgentState()
{
  return agentstate;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         NETCONN_TESTUPDATECLASS* NETCONN::GetTestUpdateClass()
* @brief      GetTestUpdateClass
* @ingroup    EXAMPLES
* 
* @return     NETCONN_TESTUPDATECLASS* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
NETCONN_TESTUPDATECLASS* NETCONN::GetTestUpdateClass()
{
  return testupdateclass;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCONN::Show_TestUpdateClass()
* @brief      Show_TestUpdateClass
* @ingroup    EXAMPLES
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCONN::Show_TestUpdateClass()
{ 
  XSTRING string;
  XSTRING string2;

  if(!connectionsmanager)
    {
      return false;
    }

  if(modeserver)
    {
      return false;
    }

  string  = __L("Client Data");
  string2.Format(__L("number %d"), GetTestUpdateClass()->GetNumber());   
  Show_Line(string, string2);

  string  = __L("");
  string2.Format(__L("string \"%s\""), GetTestUpdateClass()->GetString()->Get());   
  Show_Line(string, string2);

  console->Printf(__L("\n"));

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

  if(!connectionsmanager)
    {
      return false;
    }

  DIOCOREPROTOCOL_CFG* protocolCFG = connectionsmanager->GetProtocolCFG();
  if(!protocolCFG)
    {
      return false;
    }

  string  = __L("Connexion mode");
  string2.Format(__L("%s - %s : %s"), protocolCFG->GetIsServer()?__L("Server"):__L("Client"), APPFLOW_CFG.Connection_GetTransportType()->Get(), APPFLOW_CFG.Connection_GetTransportConfig()->Get());

  Show_Line(string, string2);

  if(connectionsmanager)
    {
      if(connectionsmanager->Connections_GetXMutex())
        {
          connectionsmanager->Connections_GetXMutex()->Lock();
        }

      console->Printf(__L("   Connexions: \n"));

      for(XDWORD c=0; c<connectionsmanager->Connections_GetAll()->GetSize(); c++)
        {
          NETCONN_COREPROTOCOL_CONNECTION*  connection = (NETCONN_COREPROTOCOL_CONNECTION*)connectionsmanager->Connections_GetAll()->Get(c);
          XSTRING                           connectionID;
          XSTRING                           measurestatus;
          XSTRING                           measurewithoutconnexion;
          XSTRING                           statusstring;

          if(connection)
            {                                                  
              if((connection->Status_Get() == DIOCOREPROTOCOL_CONNECTION_STATUS_READY)        || 
                 (connection->Status_Get() == DIOCOREPROTOCOL_CONNECTION_STATUS_INSTABILITY)  ||    
                 (connection->Status_Get() == DIOCOREPROTOCOL_CONNECTION_STATUS_DISCONNECTED))
                {       
                  connection->GetXTimerStatus()->GetMeasureString(measurestatus);         
                  connection->GetXTimerWithoutConnexion()->GetMeasureString(measurewithoutconnexion);    
                  connection->Status_GetString(statusstring);

                  //string.Format(__L("   %03d  %-10s  %-15s [not msg try (%d) [%s]  n msg [%d] \n"), c+1, measurestatus.Get(), statusstring.Get(), connection->GetHeartBetsCounter(), measurewithoutconnexion.Get(),  connection->Messages_GetAll()->GetAll()->GetSize());   

                  connection->GetIDConnection()->GetToString(connectionID);

                  if(modeserver)
                    {    
                      if(connection->GetTestUpdateClass() && connection->GetCoreProtocol()->UpdateClass_IsAllInitialized())  
                        {
                          string.Format(__L("   %03d %-10s %-20s %-15s %d,\"%s\"\n"), c+1, measurestatus.Get(), connectionID.Get(), statusstring.Get(), connection->GetTestUpdateClass()->GetNumber(), connection->GetTestUpdateClass()->GetString()->Get());   
                        }
                    }
                   else 
                    {
                      string.Format(__L("   %03d %-10s %-20s %-15s\n"), c+1, measurestatus.Get(), connectionID.Get(), statusstring.Get());   
                    }
              
                  console->Printf(string.Get());
                }
            }
        }

      console->Printf(__L("\n"));
      
      if(connectionsmanager->Connections_GetXMutex())
        {
          connectionsmanager->Connections_GetXMutex()->UnLock();
        }
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

  APPFLOW_EXTENDED.ShowAll();
  
  Show_TestUpdateClass();
  Show_ConnectionsStatus();

  if(xmutexshowallstatus) xmutexshowallstatus->UnLock();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void NETCONN::HandleEvent_ConnectionManager(NETCONN_CONNECTIONSMANAGER_XEVENT* event)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    EXAMPLES
* 
* @param[in]  event : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void NETCONN::HandleEvent_CoreProtocolConnectionManager(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT* event)
{
  switch(event->GetEventType())
    {
      case DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_COMMANDRESPONSE : if(!response.CommandResponse(event))
                                                                              {
                                                                                event->GetContenteResponseString()->Format(__L("[Error] Unkown command !!!"));
                                                                              }
                                                                            break;  

      case DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_UPDATECLASS     :
      case DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_ASKUPDATECLASS  : if(!response.UpdateClassResponse(event))
                                                                              {
                                                                                event->GetContenteResponseString()->Format(__L("[Error] Unkown class !!!"));
                                                                              }                                                                            
                                                                            break;
    }
}


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
  
  switch(xevent->GetEventFamily())
    {
      case XEVENT_TYPE_COREPROTOCOLCONNECTIONSMANAGER   : { DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT* event = (DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT*)xevent;
                                                            if(!event) return;

                                                            HandleEvent_CoreProtocolConnectionManager(event);
                                                          }
                                                          break;
    }
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
 
  connectionsmanager          = NULL; 

  agentstate                  = NULL;
  testupdateclass             = NULL;
}


#pragma endregion

