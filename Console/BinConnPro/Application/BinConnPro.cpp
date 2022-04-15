/**-------------------------------------------------------------------------------------------------------------------
*
* @file        BinConnPro.cpp
*
* @class       BINCONNPRO
* @brief       Example Binary Connexion Protocol Device class
* @ingroup
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

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

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
#include "DIOProtocol_ApplicationData.h"
#include "DIOProtocol_ConnectionsManager.h"

#include "DIOCheckTCPIPConnections.h"
#include "DIOCheckInternetConnection.h"

#include "DIOScraperWeb.h"
#include "DIOScraperWebPublicIP.h"
#include "DIOScraperWebGeolocationIP.h"
#include "DIOScraperWebUserAgentID.h"

#include "APPLog.h"
#include "APPInternetServices.h"

#include "BinConnPro_ApplicationData.h"
#include "BinConnPro_ConnectionsManager.h"
#include "BinConnPro_Protocol.h"
#include "BinConnPro_CFG.h"

#include "BinConnPro.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

 APPLICATIONCREATEINSTANCE(BINCONNPRO, binconnpro)

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BINCONNPRO::BINCONNPRO
* @brief      Constructor
* @ingroup
*
* @param
* @return
*
*---------------------------------------------------------------------------------------------------------------------*/
BINCONNPRO::BINCONNPRO() :  XFSMACHINE(0)
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BINCONNPRO::~BINCONNPRO
* @brief      Destructor
* @ingroup
*
* @param
* @return
*
*---------------------------------------------------------------------------------------------------------------------*/
BINCONNPRO::~BINCONNPRO()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BINCONNPRO::InitFSMachine
* @brief      Init FS Machine
* @ingroup
*
* @param
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO::InitFSMachine()
{
  if(!AddState( BINCONNPRO_XFSMSTATE_NONE           ,
                BINCONNPRO_XFSMEVENT_INI              , BINCONNPRO_XFSMSTATE_INI            ,
                BINCONNPRO_XFSMEVENT_END              , BINCONNPRO_XFSMSTATE_END            ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( BINCONNPRO_XFSMSTATE_INI              ,
                BINCONNPRO_XFSMEVENT_NONE           , BINCONNPRO_XFSMSTATE_NONE         ,
                BINCONNPRO_XFSMEVENT_END              , BINCONNPRO_XFSMSTATE_END            ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( BINCONNPRO_XFSMSTATE_END              ,
                BINCONNPRO_XFSMEVENT_NONE           , BINCONNPRO_XFSMSTATE_NONE         ,
                BINCONNPRO_XFSMEVENT_INI              , BINCONNPRO_XFSMSTATE_INI            ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BINCONNPRO::AppProc_Ini
* @brief      Ini Application
* @ingroup
*
* @param
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO::AppProc_Ini()
{
  XSTRING string;
  XSTRING stringresult;
  XPATH   xpathsection;
  XPATH   xpath;
  bool    status = false;

  //-------------------------------------------------------------------------------------------------

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
  xpath.Create(3 , xpathsection.Get(), BINCONNPRO_LNG_NAMEFILE, XTRANSLATION_NAMEFILEEXT);

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
    }

  //--------------------------------------------------------------------------------------

  status = false;

  string.Format(APPCONSOLE_DEFAULTMESSAGEMASK, __L("Control Servicios Internet"));
  console->PrintMessage(string.Get(),1,true,false);

  appinternetservices = new APPINTERNETSERVICES();
  status = (appinternetservices)?true:false;
  if(status) status = appinternetservices->Ini(&APP_CFG);

  stringresult.Format((status)?__L("Ok."):__L("ERROR!"));
  console->PrintMessage(stringresult.Get(), 0, false, true);

  APP_LOG_ENTRY((status)?XLOGLEVEL_INFO:XLOGLEVEL_ERROR, APP_CFG_LOG_SECTIONID_INITIATION, false, __L("%s: %s") , string.Get(), stringresult.Get());

  if(!status) return false;

  //--------------------------------------------------------------------------------------------------

  SetEvent(BINCONNPRO_XFSMEVENT_INI);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BINCONNPRO::AppProc_FirstUpdate
* @brief      First Update
* @ingroup
*
* @param
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO::AppProc_FirstUpdate()
{
  XSTRING string;
  XSTRING stringresult;
  bool    status = false;

  //--------------------------------------------------------------------------------------------------

  xtimerupdateconsole = GEN_XFACTORY.CreateTimer();
  if(!xtimerupdateconsole) return false;

  //--------------------------------------------------------------------------------------------------



  //--------------------------------------------------------------------------------------------------

  if(APP_CFG.Protocol_IsActive())
    {
      status = true;

      if(modeserver)
             string.Format(APPCONSOLE_DEFAULTMESSAGEMASK, __L("Activando conexion servidor"));
        else string.Format(APPCONSOLE_DEFAULTMESSAGEMASK, __L("Activando conexion cliente"));

      console->PrintMessage(string.Get(),1,true,false);

      connectionsmanager = new BINCONNPRO_CONNECTIONSMANAGER();
      if(!connectionsmanager) status = false;

      if(status)
        {
          connectionsmanager->SetApplicationVersion(APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR);
          connectionsmanager->GetApplicationName()->Set(APPLICATION_NAMEAPP);

          if(modeserver)
            {
              status = connectionsmanager->Ini(modeserver, APP_CFG.Protocol_IsLocalEnumActive(), APP_CFG.Protocol_GetPort(), NULL);
              connectionsmanager->TargetURL_Add(__L(""));
            }
           else
            {
              XSTRING* targetstring = APP_CFG.Protocol_GetTarget();
              if(targetstring) connectionsmanager->TargetURL_Add(targetstring->Get());

              if(connectionsmanager->TargetURL_GetNTargets())
                {
                  connectionsmanager->ProtocolConnections_SetNLimit(connectionsmanager->TargetURL_GetNTargets());
                  status = connectionsmanager->Ini(modeserver, APP_CFG.Protocol_IsLocalEnumActive(), APP_CFG.Protocol_GetPort(), NULL);

                } else status = false;
            }
        }

      if(status)
        {
          SubscribeEvent(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_CONNECTEDCONNECTION    , connectionsmanager);
          SubscribeEvent(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_INITPROTOCOL           , connectionsmanager);
          SubscribeEvent(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_DISCONNECTEDCONNECTION , connectionsmanager);
        }

      stringresult = (status)?__L("Ok."):__L("ERROR!");
      console->PrintMessage(stringresult.Get(), 0, false, true);

      APP_LOG_ENTRY((status)?XLOGLEVEL_INFO:XLOGLEVEL_ERROR, APP_CFG_LOG_SECTIONID_INITIATION, false, __L("%s: %s") , string.Get(), stringresult.Get());
      if(!status) return false;
    }

  //--------------------------------------------------------------------------------------------------

  console->PrintMessage(__L(" "), 0, false, true);
  console->WaitKey(__L("  Pulsa una tecla para continuar... (%d)"), 1, false, 5);

  //--------------------------------------------------------------------------------------------------

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BINCONNPRO::AppProc_Update
* @brief      Update Application
* @ingroup
*
* @param
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO::AppProc_Update()
{
  if(GetEvent()==BINCONNPRO_XFSMEVENT_NONE) // Not new event
    {
      switch(GetCurrentState())
        {
          case BINCONNPRO_XFSMSTATE_NONE      : break;

          case BINCONNPRO_XFSMSTATE_INI       : if(GetExitType() == APPBASE_EXITTYPE_UNKNOWN)
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

          case BINCONNPRO_XFSMSTATE_END       : break;

        }
    }
   else //  New event
    {
      if(GetEvent()<BINCONNPRO_LASTEVENT)
        {
          CheckTransition();

          switch(GetCurrentState())
            {
              case BINCONNPRO_XFSMSTATE_NONE  : break;

              case BINCONNPRO_XFSMSTATE_INI   : break;

              case BINCONNPRO_XFSMSTATE_END   : break;
            }
        }
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BINCONNPRO::AppProc_End
* @brief      End Application
* @ingroup
*
* @param
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO::AppProc_End()
{
  XSTRING string;
  XSTRING stringresult;

  //--------------------------------------------------------------------------------------

  SetEvent(BINCONNPRO_XFSMEVENT_END);

  //--------------------------------------------------------------------------------------

  if(connectionsmanager)
    {
      string.Format(APPCONSOLE_DEFAULTMESSAGEMASK,__L("Desactivando servidor machines"));
      console->PrintMessage(string.Get(),1,true,false);

      connectionsmanager->ProtocolConnections_DisconnectAll();

      UnSubscribeEvent(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_CONNECTEDCONNECTION    , connectionsmanager);
      UnSubscribeEvent(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_INITPROTOCOL           , connectionsmanager);
      UnSubscribeEvent(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_DISCONNECTEDCONNECTION , connectionsmanager);

      connectionsmanager->End();

      delete connectionsmanager;
      connectionsmanager = NULL;

      stringresult = __L("Ok.");

      console->PrintMessage(stringresult.Get(), 0, false, true);
      APP_LOG_ENTRY(XLOGLEVEL_INFO, APP_CFG_LOG_SECTIONID_ENDING, false, __L("%s: %s")  , string.Get(), stringresult.Get());
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

  string.Format(APPCONSOLE_DEFAULTMESSAGEMASK,__L("Desactivando chequeo conexiones"));
  console->PrintMessage(string.Get(),1,true,false);

  delete appinternetservices;
  appinternetservices = NULL;

  stringresult = __L("Ok.");
  console->PrintMessage(stringresult.Get(), 0, false, true);
  APP_LOG_ENTRY(XLOGLEVEL_INFO, APP_CFG_LOG_SECTIONID_ENDING, false, __L("%s: %s")  , string.Get(), stringresult.Get());


  //--------------------------------------------------------------------------------------

  APP_LOG.DelInstance();

  //--------------------------------------------------------------------------------------

  APP_CFG.DelInstance();

  //--------------------------------------------------------------------------------------

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool BINCONNPRO::KeyValidSecuences(int key)
* @brief      KeyValidSecuences
* @ingroup    APPLICATION
*
* @param[in]  key :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO::KeyValidSecuences(int key)
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
* @fn         bool SCRIPT::Show_Line(XSTRING& string, XSTRING& string2, int tab, bool linefeed)
* @brief      Show_Line
* @ingroup    APPLICATION
*
* @param[in]  string :
* @param[in]  string2 :
* @param[in]  tab :
* @param[in]  linefeed :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO::Show_Line(XSTRING& string, XSTRING& string2, int tab, bool linefeed)
{
  XSTRING line1;
  XSTRING line2;

  console->Format_Message(string.Get(), tab , false, false, line1);
  if(tab)
    {
      int _tab = tab;

      if(_tab<37) _tab = 37;
      line1.AdjustSize(_tab, false, __L(" "));
    }

  console->Format_Message(string2.Get(), 0 , false, linefeed, line2);

  console->Print(line1.Get());
  console->Print(line2.Get());

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool BINCONNPRO::Show_LineDirect(XSTRING& string, bool lf)
* @brief      Show_LineDirect
* @ingroup    APPLICATION
*
* @param[in]  string :
* @param[in]  lf :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO::Show_LineDirect(XSTRING& string, bool lf)
{
  console->Print(string.Get());
  if(lf) console->Print(__L("\n"));

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT::Show_Header(bool separator)
* @brief      Show_Header
* @ingroup    APPLICATION
*
* @param[in]  separator :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO::Show_Header(bool separator)
{
  XSTRING header;

  if(!console->TipicalHeader_Create(APPLICATION_YEAROFCREATION, APPLICATION_NAMEAPP, APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR, APPLICATION_ENTERPRISE, header)) return false;

  console->Printf(header.Get());
  console->Printf(__L("\n"));
  if(separator) console->Printf(__L("\n"));

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT::Show_AppStatus()
* @brief      Show_AppStatus
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO::Show_AppStatus()
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
  appinternetservices->DateTime_GetActual()->GetDateTimeToString(XDATETIME_FORMAT_STANDARD | XDATETIME_FORMAT_TEXTMONTH | XDATETIME_FORMAT_ADDDAYOFWEEK, string2);
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
* @fn         bool BINCONNPRO::Show_InternetStatus()
* @brief      ShowInternetStatus
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO::Show_InternetStatus()
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
* @fn         bool BINCONNPRO::Show_ConnectionsStatus()
* @brief      Show_ConnectionsStatus
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO::Show_ConnectionsStatus()
{
  XSTRING string;
  XSTRING string2;

  string  = __L("Modo de protocolo");
  if(modeserver)
          string2.Format(__L("Servidor"));
    else  string2.Format(__L("Cliente"));
  Show_Line(string, string2);

  string.Empty();
  string2.Format(__L("Puerto   [%d] "), APP_CFG.Protocol_GetPort());
  Show_Line(string, string2);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool BINCONNPRO::Show_DeviceConnectedStatus()
* @brief      ShowDeviceConnectedStatus
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO::Show_DeviceConnectedStatus()
{
  XSTRING string;
  XSTRING string2;

  if(modeserver)
    {
      string  = __L("Dispositivos conectados");

      if(!connectionsmanager->ProtocolConnections_GetNConnected())
        {
          string2 = __L("Ninguno.");

          Show_Line(string, string2);
        }
       else
        {
          Show_Line(string, string2, false);

          string.Empty();
          Show_LineDirect(string, true);

          BINCONNPRO_OPENSEARCHPROTOCOLCONNECTION

          if(_protocol->IsOperational())
            {
              XSTRING IPstring;

              DIOSTREAMCIPHER* diostreamcipher =  (DIOSTREAMCIPHER*)_protocol->GetDIOStream();
              if(diostreamcipher)
                {
                  DIOSTREAMTCPIP* diostreamtcpip = (DIOSTREAMTCPIP*)diostreamcipher->GetDIOStreamBase();
                  if(diostreamtcpip)
                    {
                      DIOIP* remoteIP = diostreamtcpip->GetClientIP();
                      if(remoteIP) remoteIP->GetXString(IPstring);
                    }
                }

              XSTRING typestring;

              _applicationdata->device.GetDeviceTypeInString(typestring);

              string.Format(__L("   %-16s [%8d]  %-16s  %-18s [%d.%d.%d]") , typestring.Get()
                                                                           , _applicationdata->device.GetID()
                                                                           , IPstring.Get()
                                                                           , _applicationdata->applicationname.Get()
                                                                           , _applicationdata->applicationversion
                                                                           , _applicationdata->applicationsubversion
                                                                           , _applicationdata->applicationsubversionerr);

              Show_LineDirect(string, true);
            }

          BINCONNPRO_CLOSESEARCHPROTOCOLCONNECTION
        }
    }
   else
    {
      string  = __L("Estado dispositivo");

      string2.Empty();

      if(!connectionsmanager->ProtocolConnections_GetNConnected())
        {
          string2 = __L("Desconectado");
        }
       else
        {
          string2 = __L("Conectado");
          if(connectionsmanager->ProtocolConnections_GetFirstConnected())
            {
              if(connectionsmanager->ProtocolConnections_GetFirstConnected()->GetDIOProtocol())
                {
                  DIOSTREAMCIPHER* streamcipher = (DIOSTREAMCIPHER*)connectionsmanager->ProtocolConnections_GetFirstConnected()->GetDIOProtocol()->GetDIOStream();
                  if(streamcipher)
                   {
                     DIOSTREAMTCPIP* streamtcpip = (DIOSTREAMTCPIP*)streamcipher->GetDIOStreamBase();
                     if(streamtcpip)
                       {
                         DIOIP* IP = streamtcpip->GetClientIP();
                         if(IP)
                           {
                             XSTRING IPstring;
                             IP->GetXString(IPstring);

                             string2 += __L(" [");
                             string2 += IPstring.Get();
                             string2 += __L("]");
                           }
                       }
                    }
                }
            }
        }

      Show_Line(string, string2);
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool BINCONNPRO::Show_AllStatus()
* @brief      Show_AllStatus
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO::Show_AllStatus()
{
  console->Clear();

  if(xmutexshowallstatus) xmutexshowallstatus->Lock();

  if(Show_Header(false))            console->PrintMessage(__L(""),0, false, true);
  if(Show_AppStatus())              console->PrintMessage(__L(""),0, false, true);
  if(Show_InternetStatus())         console->PrintMessage(__L(""),0, false, true);
  if(Show_ConnectionsStatus())      console->PrintMessage(__L(""),0, false, true);
  if(Show_DeviceConnectedStatus())  console->PrintMessage(__L(""),0, false, true);

  if(xmutexshowallstatus) xmutexshowallstatus->UnLock();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool BINCONNPRO::InitializeProtocolConnectionServer(BINCONNPRO_PROTOCOL* protocol, BINCONNPRO_APPLICATIONDATA* applicationdata)
* @brief      InitializeProtocolConnectionServer
* @ingroup    APPLICATION
*
* @param[in]  protocol :
* @param[in]  applicationdata :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO::InitializeProtocolConnectionServer(BINCONNPRO_PROTOCOL* protocol, BINCONNPRO_APPLICATIONDATA* applicationdata)
{
  XSTRING IPstring;
  bool    status;

  if(protocol->IsConnected())
    {
      DIOSTREAMCIPHER* diostreamcipher =  (DIOSTREAMCIPHER*)protocol->GetDIOStream();
      if(diostreamcipher)
        {
          DIOSTREAMTCPIP* diostreamtcpip = (DIOSTREAMTCPIP*)diostreamcipher->GetDIOStreamBase();
          if(diostreamtcpip)
            {
              DIOIP* remoteIP = diostreamtcpip->GetClientIP();
              if(remoteIP)
                {
                  remoteIP->GetXString(IPstring);
                }
            }
        }
    }

  applicationdata->centername.Set(__L("Test Point"));
  applicationdata->location.GetStreet()->Set(APP_CFG.Location_GetStreet()->Get());
  applicationdata->location.GetCity()->Set(APP_CFG.Location_GetCity()->Get());
  applicationdata->location.GetCountry()->Set(APP_CFG.Location_GetCountry()->Get());
  applicationdata->location.GetState()->Set(APP_CFG.Location_GetState()->Get());
  applicationdata->location.SetPostalCode(APP_CFG.Location_GetPostalCode());

  status =  protocol->CMD_GetProtocolVersion(applicationdata->protocolversion, applicationdata->protocolsubversion, applicationdata->protocolsubversionerr);
  if(!status)
    {
      XTRACE_PRINTCOLOR(4, __L("Ini Server protocol from %s: Not get version protocol."), IPstring.Get());
      return false;
    }

  if((applicationdata->protocolversion       != BINCONNPRO_PROTOCOL_VERSION)       ||
     (applicationdata->protocolsubversion    != BINCONNPRO_PROTOCOL_SUBVERSION)    ||
     (applicationdata->protocolsubversionerr != BINCONNPRO_PROTOCOL_SUBVERSIONERR))
    {
      XTRACE_PRINTCOLOR(4, __L("Ini Server protocol from %s: Not version protocol valid."), IPstring.Get());
      return false;
    }

  status = protocol->CMD_GetApplicationVersion(applicationdata->applicationversion, applicationdata->applicationsubversion, applicationdata->applicationsubversionerr);
  if(!status)
    {
      XTRACE_PRINTCOLOR(4, __L("Ini Server protocol from %s: Not get application version."), IPstring.Get());
      return false;
    }

  status =  protocol->CMD_GetApplicationName(applicationdata->applicationname);
  if(!status)
    {
      XTRACE_PRINTCOLOR(4, __L("Ini Server protocol from %s: Not get application name."), IPstring.Get());
      return false;
    }

  XDWORD devicetype;
  XDWORD deviceID;

  status = protocol->CMD_GetDeviceTypeAndID(devicetype, deviceID);
  if(!status)
    {
      XTRACE_PRINTCOLOR(4, __L("Ini Server protocol from %s: Not get machine ID."), IPstring.Get());
      return false;
    }

  applicationdata->device.SetType((BINCONNPRO_PROTOCOL_DEVICETYPE)devicetype);
  applicationdata->device.SetID(deviceID);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool BINCONNPRO::InitializeProtocolConnectionClient(BINCONNPRO_PROTOCOL* protocol, BINCONNPRO_APPLICATIONDATA* applicationdata)
* @brief      InitializeProtocolConnectionClient
* @ingroup    APPLICATION
*
* @param[in]  protocol :
* @param[in]  applicationdata :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO::InitializeProtocolConnectionClient(BINCONNPRO_PROTOCOL* protocol, BINCONNPRO_APPLICATIONDATA* applicationdata)
{
  bool status = false;

  status =  protocol->CMD_GetProtocolVersion(applicationdata->protocolversion, applicationdata->protocolsubversion, applicationdata->protocolsubversionerr);
  if(!status)
    {
      XTRACE_PRINTCOLOR(4, __L("Ini Client protocol:  Not get version protocol."));
      return false;
    }

  if((applicationdata->protocolversion       != BINCONNPRO_PROTOCOL_VERSION)       ||
     (applicationdata->protocolsubversion    != BINCONNPRO_PROTOCOL_SUBVERSION)    ||
     (applicationdata->protocolsubversionerr != BINCONNPRO_PROTOCOL_SUBVERSIONERR))
    {
      XTRACE_PRINTCOLOR(4, __L("Ini Client protocol:  Not version protocol valid."));
      return false;
    }

  status = protocol->CMD_GetCenterName(applicationdata->centername);
  if(!status)
    {
      XTRACE_PRINTCOLOR(4, __L("Ini Client protocol:  Not get center name."));
      return false;
    }

  //XTRACE_SETAPPLICATIONID(applicationdata->centername);

  XSTRING street;
  XSTRING city;
  XSTRING state;
  XSTRING country;
  XDWORD  postalcode = 0;

  status = protocol->CMD_GetLocation(street,city, state, country, postalcode);
  if(!status)
    {
      XTRACE_PRINTCOLOR(4, __L("Ini Client protocol:  Not get location."));
      return false;
    }

  applicationdata->location.GetStreet()->Set(street);
  applicationdata->location.GetCity()->Set(city);
  applicationdata->location.GetState()->Set(state);
  applicationdata->location.GetCountry()->Set(country);
  applicationdata->location.SetPostalCode(postalcode);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void BINCONNPRO::HandleEvent_ServerProtocolConnections(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT* event)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    APPLICATION
*
* @param[in]  event :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void BINCONNPRO::HandleEvent_ServerProtocolConnections(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT* event)
{
  switch(event->GetEventType())
    {
      case DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_CONNECTEDCONNECTION    : break;

      case DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_INITPROTOCOL           : { DIOPROTOCOL_CONNECTION*  protocolconnection  =  event->GetProtocolConnection();
                                                                                  BINCONNPRO_PROTOCOL*    protocol            =  NULL;
                                                                                  XSTRING                 IPstring;
                                                                                  bool                    status              = false;

                                                                                  if(!protocolconnection)  break;

                                                                                  protocol= (BINCONNPRO_PROTOCOL*)protocolconnection->GetDIOProtocol();
                                                                                  if(!protocol)
                                                                                    {
                                                                                      XTRACE_PRINTCOLOR(4, __L("Ini Server protocol: Not instance protocol."));
                                                                                      break;
                                                                                    }

                                                                                  BINCONNPRO_APPLICATIONDATA* applicationdata = (BINCONNPRO_APPLICATIONDATA*)protocol->GetApplicationData();
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

                                                                                  BINCONNPRO_PROTOCOL* protocol = (BINCONNPRO_PROTOCOL*)protocolconnection->GetDIOProtocol();
                                                                                  if(!protocol) break;

                                                                                  BINCONNPRO_APPLICATIONDATA* applicationdata = (BINCONNPRO_APPLICATIONDATA*)protocol->GetApplicationData();
                                                                                  if(!applicationdata) break;
                                                                                }
                                                                                break;

    }
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void BINCONNPRO::HandleEvent_ClientProtocolConnections(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT* event)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    APPLICATION
*
* @param[in]  event :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void BINCONNPRO::HandleEvent_ClientProtocolConnections(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT* event)
{
  switch(event->GetEventType())
    {
      case DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_CONNECTEDCONNECTION       : break;

      case DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_INITPROTOCOL              : { DIOPROTOCOL_CONNECTION*  protocolconnection = event->GetProtocolConnection();
                                                                                    BINCONNPRO_PROTOCOL*     protocol           = NULL;
                                                                                    bool                     status             = false;

                                                                                    if(protocolconnection) protocol = (BINCONNPRO_PROTOCOL*)protocolconnection->GetDIOProtocol();
                                                                                    if(!protocol) break;

                                                                                    BINCONNPRO_APPLICATIONDATA* applicationdata = (BINCONNPRO_APPLICATIONDATA*)protocol->GetApplicationData();
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




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BINCONNPRO::HandleEvent
* @brief      Handle Events
* @ingroup
*
* @param[]    xevent : event send to control
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void BINCONNPRO::HandleEvent(XEVENT* xevent)
{
  if(!xevent) return;

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
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void BINCONNPRO::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void BINCONNPRO::Clean()
{
  xtimerupdateconsole         = NULL;

  xmutexshowallstatus         = NULL;

  appinternetservices         = NULL;

  modeserver                  = false;
  connectionsmanager          = NULL;
}
