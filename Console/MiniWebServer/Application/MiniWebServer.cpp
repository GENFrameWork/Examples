/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       MiniWebServer.cpp
* 
* @class      MINIWEBSERVER
* @brief      Example Mini Web Server class
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

/*---- PRECOMPILATION INCLUDES ----------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "MiniWebServer.h"

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
#include "XPathsManager.h"
#include "XFileTXT.h"
#include "XFileCSV.h"
#include "XFileXML.h"
#include "XFileJSON.h"
#include "XTranslation.h"
#include "XTranslation_GEN.h"
#include "XTranslation.h"
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
#include "DIOWebServer_XEvent.h"
#include "DIODynDNS_Manager.h"

#include "DIOCheckTCPIPConnections.h"
#include "DIOCheckInternetConnection.h"

#include "DIOScraperWeb.h"
#include "DIOScraperWebPublicIP.h"
#include "DIOScraperWebGeolocationIP.h"
#include "DIOScraperWebUserAgentID.h"

#include "APPBase.h"
#include "APPLog.h"
#include "APPInternetServices.h"
#include "APPWebServer.h"

#include "MiniWebServer_CFG.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

APPLICATIONCREATEINSTANCE(MINIWEBSERVER, miniwebserver)

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------

@fn         MINIWEBSERVER::MINIWEBSERVER()
@brief      Constructor
@ingroup    APPLICATION

@return     Does not return anything. 

--------------------------------------------------------------------------------------------------------------------*/
MINIWEBSERVER::MINIWEBSERVER() :  XFSMACHINE(0)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         MINIWEBSERVER::~MINIWEBSERVER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    APPLICATION
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
MINIWEBSERVER::~MINIWEBSERVER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool MINIWEBSERVER::InitFSMachine()
* @brief      InitFSMachine
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool MINIWEBSERVER::InitFSMachine()
{
  if(!AddState( MINIWEBSERVER_XFSMSTATE_NONE            ,
                MINIWEBSERVER_XFSMEVENT_INI             , MINIWEBSERVER_XFSMSTATE_INI           ,
                MINIWEBSERVER_XFSMEVENT_END             , MINIWEBSERVER_XFSMSTATE_END           ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( MINIWEBSERVER_XFSMSTATE_INI             ,
                MINIWEBSERVER_XFSMEVENT_NONE            , MINIWEBSERVER_XFSMSTATE_NONE          ,
                MINIWEBSERVER_XFSMEVENT_END             , MINIWEBSERVER_XFSMSTATE_END           ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( MINIWEBSERVER_XFSMSTATE_END             ,
                MINIWEBSERVER_XFSMEVENT_NONE            , MINIWEBSERVER_XFSMSTATE_NONE          ,
                MINIWEBSERVER_XFSMEVENT_INI             , MINIWEBSERVER_XFSMSTATE_INI           ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool MINIWEBSERVER::AppProc_Ini()
* @brief      AppProc_Ini
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool MINIWEBSERVER::AppProc_Ini()
{
  XSTRING string;
  XSTRING stringresult;
  XPATH   xpathsection;
  XPATH   xpath;
  bool    status;

  //-------------------------------------------------------------------------------------------------

  GEN_SET_VERSION(APPLICATION_NAMEAPP, APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR, APPLICATION_OWNER, APPLICATION_YEAROFCREATION)

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

  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_WEB,  APPDEFAULT_DIRECTORY_WEB);

  GEN_XPATHSMANAGER.CreateAllPathSectionOnDisk();

  //--------------------------------------------------------------------------------------------------

  InitFSMachine();

  //--------------------------------------------------------------------------------------------------

  console->Clear();
  Show_Header(true);

  //--------------------------------------------------------------------------------------------------

  xmutexshowallstatus = GEN_XFACTORY.Create_Mutex();
  if(!xmutexshowallstatus) return false;

  //--------------------------------------------------------------------------------------------------

  APP_CFG_SETAUTOMATICTRACETARGETS

  //--------------------------------------------------------------------------------------------------

  /*
  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathsection);
  xpath.Create(3 , xpathsection.Get(), MINIWEBSERVER_LNG_NAMEFILE, XTRANSLATION_NAMEFILEEXT);

  if(!GEN_XTRANSLATION.Ini(xpath))
    {
      return false;
    }
  */

  GEN_XTRANSLATION.SetActual(XLANGUAGE_ISO_639_3_CODE_SPA);

  //--------------------------------------------------------------------------------------------------

  if(APP_CFG.Log_IsActive())
    {
      string.Format(APPCONSOLE_DEFAULTMESSAGEMASK, __L("Activando sistema LOG"));
      console->PrintMessage(string.Get(), 1, true, false);

      status = APP_LOG.Ini(&APP_CFG, APPLICATION_NAMEFILE , APPLICATION_VERSION
                                                          , APPLICATION_SUBVERSION
                                                          , APPLICATION_SUBVERSIONERR);

      stringresult.Format((status)?__L("Ok."):__L("ERROR!"));
      console->PrintMessage(stringresult.Get(), 0, false, true);

      XSTRING SO_ID;
      status = GEN_XSYSTEM.GetOperativeSystemID(SO_ID);

      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Application ROOT path: %s"),  GEN_XPATHSMANAGER.GetPathSection(XPATHSMANAGERSECTIONTYPE_ROOT)->xpath->Get());
      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("%s"),  GEN_VERSION.GetAppVersion()->Get());   
      XTRACE_PRINTMSGSTATUS(__L("S.O. version"), SO_ID.Get()); 

      stringresult.Format((status)?__L("Ok."):__L("ERROR!"));
      APP_LOG_ENTRY(((status)?XLOGLEVEL_INFO:XLOGLEVEL_ERROR), APP_CFG_LOG_SECTIONID_INITIATION, false, __L("%s: %s") , string.Get(), stringresult.Get());
           
      APP_LOG_ENTRY(((status)?XLOGLEVEL_INFO:XLOGLEVEL_ERROR), APP_CFG_LOG_SECTIONID_INITIATION, false,  __L("Identificacion SO: %s"), SO_ID.Get());

      XDWORD total = 0;
      XDWORD free  = 0;

      GEN_XSYSTEM.GetMemoryInfo(total,free);

      APP_LOG_ENTRY(XLOGLEVEL_INFO, APP_CFG_LOG_SECTIONID_INITIATION, false, XT_L(XTRANSLATION_GEN_ID_APPLOG_TOTALMEMORY), total, free, GEN_XSYSTEM.GetFreeMemoryPercent());
    }

  //--------------------------------------------------------------------------------------

  status = false;

  string.Format(APPCONSOLE_DEFAULTMESSAGEMASK, __L("Activando servicios Internet"));
  console->PrintMessage(string.Get(),1,true,false);

  appinternetservices = new APPINTERNETSERVICES();
  status = (appinternetservices)?true:false;
  if(status) status = appinternetservices->Ini(&APP_CFG);

  stringresult.Format((status)?__L("Ok."):__L("ERROR!"));
  console->PrintMessage(stringresult.Get(), 0, false, true);

  APP_LOG_ENTRY((status)?XLOGLEVEL_INFO:XLOGLEVEL_ERROR, APP_CFG_LOG_SECTIONID_INITIATION, false, __L("%s: %s") , string.Get(), stringresult.Get());

  if(!status) return false;

  if(appinternetservices->GetDynDNSManager())
    {
      //appinternetservices->GetDynDNSManager()->GetLogin()->Set(__L(""));
      //appinternetservices->GetDynDNSManager()->GetPassword()->Set(__L(""));
    }

  //--------------------------------------------------------------------------------------------------

  SetEvent(MINIWEBSERVER_XFSMEVENT_INI);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool MINIWEBSERVER::AppProc_FirstUpdate()
* @brief      AppProc_FirstUpdate
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool MINIWEBSERVER::AppProc_FirstUpdate()
{
  XSTRING string;
  XSTRING stringresult;
  bool    status = false;

  //--------------------------------------------------------------------------------------------------

  xtimerupdateconsole = GEN_XFACTORY.CreateTimer();
  if(!xtimerupdateconsole) return false;

  //--------------------------------------------------------------------------------------------------

  status = false;

  if(APP_CFG.WebServer_GetPort())
    {
      string.Format(APPCONSOLE_DEFAULTMESSAGEMASK,__L("Inicializando Web Server"));
      console->PrintMessage(string.Get(),1,true,false);

      appwebserver = new APPWEBSERVER();
      if(appwebserver) status = true;

      if(status) status = appwebserver->Ini(&APP_CFG, true, false, false);

      stringresult = (status)?__L("Ok."):__L("ERROR!");
      console->PrintMessage(stringresult.Get(), 0, false, true);

      if(status)
        {
          SubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_REQUEST             , (XSUBJECT *)appwebserver);
          SubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_DOAUTHENTICATE      , (XSUBJECT *)appwebserver);
          SubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_CHECKAUTHENTICATE   , (XSUBJECT *)appwebserver);
          SubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_REQUEST_ENDPOINT    , (XSUBJECT *)appwebserver);

          apirest = new MINIWEBSERVER_APIREST(this);
          if(!apirest) return false;
        }

      APP_LOG_ENTRY((status)?XLOGLEVEL_INFO:XLOGLEVEL_ERROR, APP_CFG_LOG_SECTIONID_INITIATION, false, __L("%s: %s") , string.Get(), stringresult.Get());
    }

  //--------------------------------------------------------------------------------------------------

  status = false;

  string.Format(APPCONSOLE_DEFAULTMESSAGEMASK,__L("Inicializando WebSocket"));
  console->PrintMessage(string.Get(),1,true,false);

  appwebsocket = new APPWEBSERVER();
  if(appwebsocket) status = true;

  if(status) status = appwebsocket->Ini(17009, true, APP_CFG.WebServer_GetTimeoutToServerPage(), APP_CFG.WebServer_GetLocalAddress());

  stringresult = (status)?__L("Ok."):__L("ERROR!");
  console->PrintMessage(stringresult.Get(), 0, false, true);

  if(status)
    {
      SubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_REQUEST                , (XSUBJECT *)appwebsocket);
      SubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_DOAUTHENTICATE         , (XSUBJECT *)appwebsocket);
      SubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_CHECKAUTHENTICATE      , (XSUBJECT *)appwebsocket);
      SubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_CONNECTED    , (XSUBJECT *)appwebsocket);
      SubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_READDATA     , (XSUBJECT *)appwebsocket);
      SubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_DISCONNECTED , (XSUBJECT *)appwebsocket);
    }

  APP_LOG_ENTRY((status)?XLOGLEVEL_INFO:XLOGLEVEL_ERROR, APP_CFG_LOG_SECTIONID_INITIATION, false, __L("%s: %s") , string.Get(), stringresult.Get());

  //--------------------------------------------------------------------------------------------------

  console->PrintMessage(__L(" "),0,false,true);
  console->WaitKey(__L("  Pulsa una tecla para continuar... (%d)"), 1, false, 5);

  //--------------------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool MINIWEBSERVER::AppProc_Update()
* @brief      AppProc_Update
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool MINIWEBSERVER::AppProc_Update()
{
  if(GetEvent()==MINIWEBSERVER_XFSMEVENT_NONE) // Not new event
    {
      switch(GetCurrentState())
        {
          case MINIWEBSERVER_XFSMSTATE_NONE       : break;

          case MINIWEBSERVER_XFSMSTATE_INI        : if(GetExitType() == APPBASE_EXITTYPE_UNKNOWN)
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

          case MINIWEBSERVER_XFSMSTATE_END        : break;

        }
    }
   else //  New event
    {
      if(GetEvent()<MINIWEBSERVER_LASTEVENT)
        {
          CheckTransition();

          switch(GetCurrentState())
            {
              case MINIWEBSERVER_XFSMSTATE_NONE   : break;

              case MINIWEBSERVER_XFSMSTATE_INI    : break;

              case MINIWEBSERVER_XFSMSTATE_END    : break;
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool MINIWEBSERVER::AppProc_End()
* @brief      AppProc_End
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool MINIWEBSERVER::AppProc_End()
{
  XSTRING string;
  XSTRING stringresult;

  //--------------------------------------------------------------------------------------

  SetEvent(MINIWEBSERVER_XFSMEVENT_END);

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

  string.Format(APPCONSOLE_DEFAULTMESSAGEMASK,__L("Desactivando servicios Internet"));
  console->PrintMessage(string.Get(),1,true,false);

  delete appinternetservices;
  appinternetservices = NULL;

  stringresult = __L("Ok.");
  console->PrintMessage(stringresult.Get(), 0, false, true);
  APP_LOG_ENTRY(XLOGLEVEL_INFO, APP_CFG_LOG_SECTIONID_ENDING, false, __L("%s: %s")  , string.Get(), stringresult.Get());

  //--------------------------------------------------------------------------------------

  if(appwebserver)
    {
      string.Format(APPCONSOLE_DEFAULTMESSAGEMASK,__L("Desactivando servidor web"));
      console->PrintMessage(string.Get(),1,true,false);

      UnSubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_REQUEST             , (XSUBJECT *)appwebserver);
      UnSubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_DOAUTHENTICATE      , (XSUBJECT *)appwebserver);
      UnSubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_CHECKAUTHENTICATE   , (XSUBJECT *)appwebserver);
      UnSubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_REQUEST_ENDPOINT    , (XSUBJECT *)appwebserver);

      delete appwebserver;
      appwebserver = NULL;

      stringresult = __L("Ok.");

      console->PrintMessage(stringresult.Get(), 0, false, true);
      XLOG::GetInstance().AddEntry(XLOGLEVEL_INFO, APP_CFG_LOG_SECTIONID_ENDING, false, __L("%s: %s") , string.Get(), stringresult.Get());
    }

  if(apirest)
    {
      delete apirest;
      apirest = NULL;
    }

  //--------------------------------------------------------------------------------------

  if(appwebsocket)
    {
      string.Format(APPCONSOLE_DEFAULTMESSAGEMASK,__L("Desactivando WebSocket"));
      console->PrintMessage(string.Get(),1,true,false);

      UnSubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_REQUEST                 , (XSUBJECT *)appwebsocket);
      UnSubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_DOAUTHENTICATE          , (XSUBJECT *)appwebsocket);
      UnSubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_CHECKAUTHENTICATE       , (XSUBJECT *)appwebsocket);
      UnSubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_CONNECTED     , (XSUBJECT *)appwebsocket);
      UnSubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_READDATA      , (XSUBJECT *)appwebsocket);
      UnSubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_DISCONNECTED  , (XSUBJECT *)appwebsocket);

      delete appwebsocket;
      appwebsocket = NULL;

      stringresult = __L("Ok.");

      console->PrintMessage(stringresult.Get(), 0, false, true);
      XLOG::GetInstance().AddEntry(XLOGLEVEL_INFO, APP_CFG_LOG_SECTIONID_ENDING, false, __L("%s: %s") , string.Get(), stringresult.Get());
    }

  //--------------------------------------------------------------------------------------

  APP_LOG.DelInstance();

  APP_CFG.DelInstance();

  //--------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool MINIWEBSERVER::KeyValidSecuences(int key)
* @brief      KeyValidSecuences
* @ingroup    APPLICATION
* 
* @param[in]  key : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool MINIWEBSERVER::KeyValidSecuences(int key)
{
  XCHAR character = (XCHAR)key;

  if((character<32) || (character>127)) character = __C('?');
  APP_LOG_ENTRY(XLOGLEVEL_WARNING, APP_CFG_LOG_SECTIONID_STATUSAPP, false, __L("Key pressed: 0x%02X [%c]"), key, character);

  console->Printf(__L("\r    \r"));

  switch(key)
    {
      case 'Q'  : // ESC Exit application
                  SetExitType(APPBASE_EXITTYPE_BY_USER);
                  break;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool MINIWEBSERVER::Show_AppStatus()
* @brief      Show_AppStatus
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool MINIWEBSERVER::Show_AppStatus()
{
  XSTRING string;
  XSTRING string2;

  XDWORD  total;
  XDWORD  free;

  GEN_XSYSTEM.GetMemoryInfo(total,free);

  string  = __L("Memoria total");
  string2.Format(__L("%d Kb, libre %d Kb (el %d%%)"), total, free, GEN_XSYSTEM.GetFreeMemoryPercent());
  Show_Line(string, string2);
  
  string  = __L("Fecha ");
  appinternetservices->DateTime_GetLocal()->GetDateTimeToString(XDATETIME_FORMAT_STANDARD | XDATETIME_FORMAT_TEXTMONTH | XDATETIME_FORMAT_ADDDAYOFWEEK, string2);
  Show_Line(string, string2);

  if(xtimerglobal)
    {
      string  = __L("Tiempo de funcionamiento");
      xtimerglobal->GetMeasureString(string2, true);
      Show_Line(string, string2);
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool MINIWEBSERVER::Show_InternetStatus()
* @brief      Show_InternetStatus
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool MINIWEBSERVER::Show_InternetStatus()
{
  XSTRING string;
  XSTRING string2;

  string.Format(__L("Local  IP"));
  string2.Format(__L("[%s]"), appinternetservices->GetAutomaticLocalIP()->Get());
  Show_Line(string, string2);

  string.Format(__L("Conexion con Internet"));
  string2.Format(__L("%s. "), appinternetservices->HaveInternetConnection()?__L("Si"):__L("No"));
  Show_Line(string, string2);

  if(appinternetservices->HaveInternetConnection())
    {
      string.Format(__L("Public IP"));
      string2.Format(__L("[%s]"), appinternetservices->GetPublicIP()->Get());
      Show_Line(string, string2);

    } else console->PrintMessage(__L(""), 0, false, true);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool MINIWEBSERVER::Show_WebServerConfig()
* @brief      Show_WebServerConfig
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool MINIWEBSERVER::Show_WebServerConfig()
{
  XSTRING string;
  XSTRING string2;

  string.Format(__L("Web Server"));
  string2.Empty();
  Show_Line(string, string2);

  string.Format(__L("Port"));
  string2.Format(__L("%d"), appwebserver->GetWebServer()->GetPort());
  Show_Line(string, string2);

  string.Format(__L("Acceso Autenticado"));
  string2.Format(__L("%s"), appwebserver->GetIsAuthenticatedAccess()?__L("Si"):__L("No"));
  Show_Line(string, string2);


  string.Format(__L("Plugin(s) Activo(s)"));

  XDWORD nplugins = appwebserver->GetWebServer()->GetPluginsManager()->Plugins_GetNPlugins();
  string2.Format(__L("%d "), appwebserver->GetWebServer()->GetPluginsManager()->Plugins_GetNPlugins());

  for(XDWORD c=0; c<nplugins; c++)
    {
      DIOWEBSERVER_PLUGIN* plugin = appwebserver->GetWebServer()->GetPluginsManager()->Plugins_Get(c);
      if(plugin) string2.AddFormat(__L("[%s] "), plugin->GetName()->Get());
    }

  Show_Line(string, string2);


  string.Format(__L("Solo sirve API Rest"));
  string2.Format(__L("%s"), appwebserver->GetIsApiRestOnly()?__L("Si"):__L("No"));
  Show_Line(string, string2);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool MINIWEBSERVER::Show_WebSocketConfig()
* @brief      Show_WebSocketConfig
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool MINIWEBSERVER::Show_WebSocketConfig()
{
  if(!appwebsocket)                   return false;
  if(!appwebsocket->GetWebServer())   return false;

  XSTRING string;
  XSTRING string2;

  string.Format(__L("WebSocket"));
  string2.Empty();
  Show_Line(string, string2);

  string.Format(__L("Port"));
  string2.Format(__L("%d"), appwebsocket->GetWebServer()->GetPort());
  Show_Line(string, string2);


  int nconnections_active = 0;

  DIOWEBSERVER_CONNECTION* connection;

  connection = appwebsocket->GetWebServer()->Websocket_GetConnection();
  while(connection)
    {
      nconnections_active++;
      connection = appwebsocket->GetWebServer()->Websocket_GetNextConnection();
    }

  string.Format(__L("Conexiones activas"));
  string2.Format(__L("[%d]"), nconnections_active);
  Show_Line(string, string2);

  if(nconnections_active)
    {
      connection = appwebsocket->GetWebServer()->Websocket_GetConnection();
      while(connection)
        {
          string.Empty();
          string2.Format(__L("Ver. %2d - Protocol \"%s\" - [%s]") , connection->GetRequest()->WebSocket_GetVersion()
                                                                  , connection->GetRequest()->WebSocket_GetProtocol()->Get()
                                                                  , connection->GetRequest()->GetResource()->Get());
          Show_Line(string, string2);

          connection = appwebsocket->GetWebServer()->Websocket_GetNextConnection();
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool MINIWEBSERVER::Show_AllStatus()
* @brief      Show_AllStatus
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool MINIWEBSERVER::Show_AllStatus()
{
  console->Clear();

  if(xmutexshowallstatus) xmutexshowallstatus->Lock();

  if(Show_Header(false))      console->PrintMessage(__L(""),0, false, true);
  if(Show_AppStatus())        console->PrintMessage(__L(""),0, false, true);
  if(Show_InternetStatus())   console->PrintMessage(__L(""),0, false, true);
  if(Show_WebServerConfig())  console->PrintMessage(__L(""),0, false, true);
  if(Show_WebSocketConfig())  console->PrintMessage(__L(""),0, false, true);

  if(xmutexshowallstatus) xmutexshowallstatus->UnLock();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void MINIWEBSERVER::HandleEvent_WebServer(DIOWEBSERVER_XEVENT* event)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    APPLICATION
*
* @param[in]  event :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void MINIWEBSERVER::HandleEvent_WebServer(DIOWEBSERVER_XEVENT* event)
{
  if(!event) return;

  switch(event->GetEventType())
    {
      case DIOWEBSERVER_XEVENT_TYPE_REQUEST               : event->SetStatus(false);
                                                            break;

      case DIOWEBSERVER_XEVENT_TYPE_DOAUTHENTICATE        : event->SetIsRequestAuthenticate(true);
                                                            break;

      case DIOWEBSERVER_XEVENT_TYPE_CHECKAUTHENTICATE     : event->SetIsRequestAuthenticate(true);
                                                            break;

      case DIOWEBSERVER_XEVENT_TYPE_REQUEST_ENDPOINT      : { DIOWEBHEADER_RESULT result = DIOWEBHEADER_RESULT_OK;
                                                              XSTRING             output;

                                                              event->SetStatus(apirest->ResolveEndPoint(event->GetRequest(), event->GetQueryString(), &result, &output));

                                                              event->SetIsRequestAuthenticate(true);
                                                              event->SetResult(result);
                                                              event->GetOutput()->Set(output);
                                                            }
                                                            break;

      case DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_CONNECTED   : // Accepted connection
                                                            event->SetStatus(true);
                                                            break;

      case DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_READDATA    : { event->GetServer()->Websocket_Ping(__L("cucu..."));
                                                              event->GetServer()->Websocket_Write(__L("Hello word!"));
                                                            }
                                                          break;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void MINIWEBSERVER::HandleEvent(XEVENT* xevent)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    APPLICATION
* 
* @param[in]  xevent : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void MINIWEBSERVER::HandleEvent(XEVENT* xevent)
{
  if(!xevent) return;

  switch(xevent->GetEventFamily())
    {
      case XEVENT_TYPE_WEBSERVER       : { DIOWEBSERVER_XEVENT* event = (DIOWEBSERVER_XEVENT*)xevent;
                                           if(!event) return;

                                           HandleEvent_WebServer(event);
                                         }
                                        break;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void MINIWEBSERVER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    APPLICATION
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void MINIWEBSERVER::Clean()
{
  xtimerupdateconsole       = NULL;

  xmutexshowallstatus       = NULL;

  appinternetservices       = NULL;

  appwebserver              = NULL;
  apirest                   = NULL;
  appwebsocket              = NULL;
}


#pragma endregion

