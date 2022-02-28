/**-------------------------------------------------------------------------------------------------------------------
*
* @file       Tests.cpp
*
* @class      TESTS
* @brief      GEN Tests Example class
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @copyright  Copyright(c) 2008 - 2016 GEN Group.
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

#include "XFactory.h"
#include "XPath.h"
#include "XDateTime.h"
#include "XTimer.h"
#include "XDir.h"
#include "XRand.h"
#include "XDir.h"
#include "XString.h"
#include "XSystem.h"
#include "XLog.h"
#include "XConsole.h"
#include "XFileTXT.h"
#include "XFileCSV.h"
#include "XFileXML.h"
#include "XFileRIFF.h"
#include "XFileDFU.h"
#include "XVariant.h"
#include "XTranslation.h"
#include "XScheduler.h"
#include "XScheduler_XEvent.h"
#include "XThread.h"
#include "XTrace.h"
#include "XObserver.h"
#include "XSharedMemoryManager.h"
#include "XProcessManager.h"

#include "HashMD5.h"
#include "HashSHA1.h"
#include "HashSHA2.h"
#include "HashWhirlpool.h"

#include "DIOFactory.h"
#include "DIOStreamDeviceIP.h"
#include "DIOStreamDeviceWifi.h"
#include "DIOStreamDeviceBluetooth.h"
#include "DIOStreamDeviceBluetoothLE.h"
#include "DIOStreamDeviceUSB.h"
#include "DIOStreamConfig.h"
#include "DIOStreamUARTConfig.h"
#include "DIOStreamUART.h"
#include "DIOStreamUSBLocalEnumDevices.h"
#include "DIOStreamUSBConfig.h"
#include "DIOStreamUSB.h"
#include "DIOStreamIPLocalEnumDevices.h"
#include "DIOStreamTCPIPConfig.h"
#include "DIOStreamTCPIP.h"
#include "DIOStreamBluetoothLocalEnumDevices.h"
#include "DIOStreamBluetoothRemoteEnumDevices.h"
#include "DIOStreamBluetoothLERemoteEnumDevices.h"
#include "DIOStreamI2CConfig.h"
#include "DIOStreamI2C.h"
#include "DIOI2C_Devices.h"
#include "DIOStreamSPIConfig.h"
#include "DIOStreamSPI.h"
#include "DIOSPI_Devices.h"
#include "DIOStreamTLSConfig.h"
#include "DIOStreamTLS.h"
#include "DIOGPIO.h"
#include "DIOMPSSE.h"
#include "DIODNSProtocol.h"
#include "DIODNSResolved.h"
#include "DIOStreamWifiRemoteEnumDevices.h"
#include "DIOWakeOnLAN.h"
#include "DIONotificationsManager.h"

#include "DIOWebClient_XEvent.h"
#include "DIOWebClient.h"

#include "DIOCheckTCPIPConnections.h"
#include "DIOCheckInternetConnection.h"

#include "DIOScraperWeb.h"
#include "DIOScraperWebCache.h"
#include "DIOScraperWebGeolocationIP.h"
#include "DIOScraperWebMACManufacturer.h"
#include "DIOScraperWebPublicIP.h"
#include "DIOScraperWebSexName.h"
#include "DIOScraperWebTranslation.h"
#include "DIOScraperWebUserAgentID.h"
#include "DIOScraperWebWeather.h"
#include "DIOWifiManagerMode.h"
#include "DIOATCMDS.h"
#include "DIOATCMDGSM.h"
#include "DIOSNMP.h"
#include "DIOLedNeoPixelWS2812B.h"

#include "DIOAlerts.h"

#ifdef SND_ACTIVE
#include "SNDFactory.h"
#include "SNDElement.h"
#endif


#include "APPLog.h"
#include "APPCheckResourcesHardware_XEvent.h"
#include "APPCheckResourcesHardware.h"
#include "APPInternetServices.h"
#include "APPAlerts.h"

#ifdef WINDOWS
 #include "Tests_WindowsPlatform.h"
 #include "DIOWINDOWSStreamWifiRemoteEnumDevices.h"
 #include "XWINDOWSAccessControlLists.h"
#endif


#ifdef LINUX
 #include "Tests_LinuxPlatform.h"
 #include "INPLINUXDeviceID.h"
 #include "DIOLINUXDBus.h"
 #include "DIOLINUXNetworkManager.h"
#endif


#include "Tests_CFG.h"

#include "Tests.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

 APPLICATIONCREATEINSTANCE(TESTS, tests)

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TESTS::TESTS
* @brief      Constructor
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param
* @return
*
*---------------------------------------------------------------------------------------------------------------------*/
TESTS::TESTS() :  XFSMACHINE(0)
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TESTS::~TESTS
* @brief      Destructor
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param
* @return
*
*---------------------------------------------------------------------------------------------------------------------*/
TESTS::~TESTS()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TESTS::InitFSMachine
* @brief      Init FS Machine
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::InitFSMachine()
{
  if(!AddState( TESTS_XFSMSTATE_NONE            ,
                TESTS_XFSMEVENT_INI             , TESTS_XFSMSTATE_INI           ,
                TESTS_XFSMEVENT_END             , TESTS_XFSMSTATE_END           ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( TESTS_XFSMSTATE_INI             ,
                TESTS_XFSMEVENT_NONE            , TESTS_XFSMSTATE_NONE          ,
                TESTS_XFSMEVENT_END             , TESTS_XFSMSTATE_END           ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( TESTS_XFSMSTATE_END             ,
                TESTS_XFSMEVENT_NONE            , TESTS_XFSMSTATE_NONE          ,
                TESTS_XFSMEVENT_INI             , TESTS_XFSMSTATE_INI           ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::AppProc_PlatformIni()
* @brief      AppProc_PlatformIni
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::AppProc_PlatformIni()
{
  //--------------------------------------------------------------------------------------
  
  #ifdef WINDOWS
  Windows_Platform_Ini();
  #endif  

  //--------------------------------------------------------------------------------------
  
  #ifdef LINUX
  Linux_Platform_Ini();    
  #endif  
    
  //--------------------------------------------------------------------------------------


  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TESTS::AppProc_Ini
* @brief      Ini Application
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::AppProc_Ini()
{
  XSTRING string;
  XSTRING stringresult;
  XPATH   xpathsection;
  XPATH   xpath;
  bool    status = false;

  //-------------------------------------------------------------------------------------------------

  GetApplicationName()->Set(APPLICATION_NAMEAPP);

  //--------------------------------------------------------------------------------------------------

  //ACTIVATEXTHREADGROUP(XTHREADGROUPID_SCHEDULER);
  //ACTIVATEXTHREADGROUP(XTHREADGROUPID_DIOSTREAM);
  //ACTIVATEXTHREADGROUP(XTHREADGROUPID_APPOWNER);

  //--------------------------------------------------------------------------------------------------

  GEN_XPATHSMANAGER.AdjustRootPathDefault(APPDEFAULT_DIRECTORY_ROOT);

  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_GRAPHICS   , APPDEFAULT_DIRECTORY_GRAPHICS);
  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_SOUNDS     , APPDEFAULT_DIRECTORY_SOUNDS);
  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_DATABASES  , APPDEFAULT_DIRECTORY_DATABASES);
  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_WEB        , APPDEFAULT_DIRECTORY_WEB);
  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_FIRMWARE   , APPDEFAULT_DIRECTORY_FIRMWARE);

  GEN_XPATHSMANAGER.CreateAllPathSectionOnDisk();

  //--------------------------------------------------------------------------------------------------

  InitFSMachine();

  //--------------------------------------------------------------------------------------


  //Test_DIOWifiManagerMode(this);


  XTRACE_SETAPPLICATIONNAME((*GetApplicationName()));
  XTRACE_SETAPPLICATIONVERSION(APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR);
  XTRACE_SETAPPLICATIONID(string);
  //XTRACE_SETLOCALIPFILTER(172);


  APP_CFG.SetAutomaticTraceTargets();

  //--------------------------------------------------------------------------------------

  /*
  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathsection);
  xpath.Create(3 , xpathsection.Get(), TESTS_LNG_NAMEFILE, XTRANSLATION_NAMEFILEEXT);

  if(!GEN_XTRANSLATION.Ini(xpath))
    {
      return false;
    }

  */

  GEN_XTRANSLATION.SetActual(XLANGUAGE_ISO_639_3_CODE_SPA);


  //--------------------------------------------------------------------------------------

  console->Clear();
  Show_Header(true);

  //--------------------------------------------------------------------------------------

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

  string.Format(APPCONSOLE_DEFAULTMESSAGEMASK, __L("Control de recursos hardware"));

  appcheckresourceshardware = new APPCHECKRESOURCESHARDWARE();
  status = (appcheckresourceshardware)?true:false;
  if(status) status = appcheckresourceshardware->Ini(&APP_CFG);

  stringresult.Format((status)?__L("Ok."):__L("ERROR!"));

  APP_LOG_ENTRY((status)?XLOGLEVEL_INFO:XLOGLEVEL_ERROR, APP_CFG_LOG_SECTIONID_INITIATION, false, __L("%s: %s") , string.Get(), stringresult.Get());

  if(!status) return false;

  SubscribeEvent(APPCHECKRESOURCESHARDWARE_XEVENT_TYPE_MEMFREELIMIT  , appcheckresourceshardware);
  SubscribeEvent(APPCHECKRESOURCESHARDWARE_XEVENT_TYPE_CPUUSAGELIMIT , appcheckresourceshardware);

  //--------------------------------------------------------------------------------------

  status = false;

  string.Format(APPCONSOLE_DEFAULTMESSAGEMASK, __L("Control Servicios Internet"));

  appinternetservices = new APPINTERNETSERVICES();
  status = (appinternetservices)?true:false;
  if(status) status = appinternetservices->Ini(&APP_CFG);

  stringresult.Format((status)?__L("Ok."):__L("ERROR!"));

  APP_LOG_ENTRY((status)?XLOGLEVEL_INFO:XLOGLEVEL_ERROR, APP_CFG_LOG_SECTIONID_INITIATION, false, __L("%s: %s") , string.Get(), stringresult.Get());

  if(!status) return false;

//--------------------------------------------------------------------------------------

  SetEvent(TESTS_XFSMEVENT_INI);

  return true;
}






/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TESTS::AppProc_FirstUpdate
* @brief      First Update
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::AppProc_FirstUpdate()
{
  //--------------------------------------------------------------------------------------

  xmutexshowallstatus = GEN_XFACTORY.Create_Mutex();
  if(!xmutexshowallstatus) return false;

  //--------------------------------------------------------------------------------------

  xtimerupdateconsole = GEN_XFACTORY.CreateTimer();
  if(!xtimerupdateconsole) return false;

  //--------------------------------------------------------------------------------------

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TESTS::AppProc_Update
* @brief      Update Application
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::AppProc_Update()
{
  if(GetEvent()==TESTS_XFSMEVENT_NONE) // Not new event
    {
      switch(GetCurrentState())
        {
          case TESTS_XFSMSTATE_NONE       : break;

          case TESTS_XFSMSTATE_INI        : if(GetExitType() == APPBASE_EXITTYPE_UNKNOWN)
                                              {
                                                if(xtimerupdateconsole)
                                                  {
                                                    if(xtimerupdateconsole->GetMeasureSeconds() >= 1)
                                                      {
                                                        Show_AllStatus();
                                                        xtimerupdateconsole->Reset();
                                                      }
                                                    
                                                    #ifndef TESTS_NOKEY
                                                    if(console->KBHit())
                                                      {
                                                        //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[press key]"));

                                                        int key = console->GetChar();
                                                        KeyValidSecuences(key);
                                                      }
                                                    #else                                                    
                                                    Do_Tests(); 
                                                    #endif
                  
                                                  }
                                              }
                                            break;

          case TESTS_XFSMSTATE_END        : break;

        }
    }
   else //  New event
    {
      if(GetEvent()<TESTS_LASTEVENT)
        {
          CheckTransition();

          switch(GetCurrentState())
            {
              case TESTS_XFSMSTATE_NONE   : break;

              case TESTS_XFSMSTATE_INI    : break;

              case TESTS_XFSMSTATE_END    : break;
            }
        }
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TESTS::AppProc_End
* @brief      End Application
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::AppProc_End()
{
  XSTRING string;
  XSTRING stringresult;

  //--------------------------------------------------------------------------------------

  SetEvent(TESTS_XFSMEVENT_END);

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

  if(appinternetservices)
    {
      string.Format(APPCONSOLE_DEFAULTMESSAGEMASK,__L("Desactivando servicios Internet"));

      delete appinternetservices;
      appinternetservices = NULL;

      stringresult = __L("Ok.");
      APP_LOG_ENTRY(XLOGLEVEL_INFO, APP_CFG_LOG_SECTIONID_ENDING, false, __L("%s: %s")  , string.Get(), stringresult.Get());
    }

  //--------------------------------------------------------------------------------------

  if(appcheckresourceshardware)
    {
      UnSubscribeEvent(APPCHECKRESOURCESHARDWARE_XEVENT_TYPE_MEMFREELIMIT  , appcheckresourceshardware);
      UnSubscribeEvent(APPCHECKRESOURCESHARDWARE_XEVENT_TYPE_CPUUSAGELIMIT , appcheckresourceshardware);
  
      string.Format(APPCONSOLE_DEFAULTMESSAGEMASK,__L("Desactivando control recursos HW"));

      delete appcheckresourceshardware;
      appcheckresourceshardware = NULL;

      stringresult = __L("Ok.");
      APP_LOG_ENTRY(XLOGLEVEL_INFO, APP_CFG_LOG_SECTIONID_ENDING, false, __L("%s: %s")  , string.Get(), stringresult.Get());
    }

  //--------------------------------------------------------------------------------------

  APP_LOG.DelInstance();

  //--------------------------------------------------------------------------------------

  APP_CFG.DelInstance();

  //--------------------------------------------------------------------------------------

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::AppProc_PlatformEnd()
* @brief      AppProc_PlatformEnd
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::AppProc_PlatformEnd()
{
  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::KeyValidSecuences(int key)
* @brief      KeyValidSecuences
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param[in]  key :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::KeyValidSecuences(int key)
{
  XCHAR character = (XCHAR)key;

  if((character<32) || (character>127)) character = __C('?');
  APP_LOG_ENTRY(XLOGLEVEL_WARNING, APP_CFG_LOG_SECTIONID_STATUSAPP, false, __L("Key pressed: 0x%02X [%c]"), key, character);

  console->Printf(__L("\r    \r"));
  console->Printf(__L("\n"));

  switch(key)
    {
      case 'Q'  : // ESC Exit application
                  SetExitType(APPBASE_EXITTYPE_BY_USER);
                  break;

      case 'T'  : Do_Tests();
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param[in]  string :
* @param[in]  string2 :
* @param[in]  tab :
* @param[in]  linefeed :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Show_Line(XSTRING& string, XSTRING& string2, int tab, bool linefeed)
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
* @fn         bool SCRIPT::Show_Header(bool separator)
* @brief      Show_Header
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param[in]  separator :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Show_Header(bool separator)
{
  XSTRING header;

  if(!console->TipicalHeader_Create(APPLICATION_YEAROFCREATION, APPLICATION_NAMEAPP, APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR, TESTS_ENTERPRISE, header)) return false;

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
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Show_AppStatus()
{
  XSTRING string;
  XSTRING string2;


  //-------------------------------------------------------------------------------
  // Platforms

  XSTRING           platformstr;
  XSYSTEM_PLATFORM  platform;
  
  platform = GEN_XSYSTEM.GetPlatform(&platformstr);

  string  = __L("Plataforma");
  string2.Format(__L("%s"), platformstr.Get());
  Show_Line(string, string2);


  //-------------------------------------------------------------------------------
  // Memory status

  XDWORD  total;
  XDWORD  free;
  
  GEN_XSYSTEM.GetMemoryInfo(total,free);

  string  = __L("Memoria total");
  string2.Format(__L("%d Kb, libre %d Kb (el %d%%)"), total, free, GEN_XSYSTEM.GetFreeMemoryPercent());
  Show_Line(string, string2);


  //-------------------------------------------------------------------------------
  // CPU usage status
  /*
  XSTRING nameapp =  APPLICATION_NAMEFILE;

  #ifdef WINDOWS
  nameapp.Add(__L(".exe"));
  #endif

  string  = __L("Uso de CPU");
  string2.Format(__L("Total %d%% , [%s] aplicacion  %d%%"), GEN_XSYSTEM.GetCPUUsageTotal(), APPLICATION_NAMEAPP, GEN_XSYSTEM.GetCPUUsageForProcessName(nameapp.Get()));
  Show_Line(string, string2);
  */
  //-------------------------------------------------------------------------------
  // Date time

  XDATETIME* datetime = GEN_XFACTORY.CreateDateTime();
  if(datetime)
    {
      datetime->Read();

      string  = __L("Fecha ");
      datetime->GetDateTimeToString(XDATETIME_FORMAT_STANDARD | XDATETIME_FORMAT_TEXTMONTH | XDATETIME_FORMAT_ADDDAYOFWEEK, string2);
      Show_Line(string, string2);

      GEN_XFACTORY.DeleteDateTime(datetime);
    }

  //-------------------------------------------------------------------------------
  // Time Working

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
* @fn         bool TESTS::Show_AllStatus()
* @brief      Show_AllStatus
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Show_AllStatus()
{
  console->Clear();

  if(xmutexshowallstatus) xmutexshowallstatus->Lock();

  if(Show_Header(false))      console->PrintMessage(__L(""),0, false, true);
  if(Show_AppStatus())        console->PrintMessage(__L(""),0, false, true);

  if(xmutexshowallstatus) xmutexshowallstatus->UnLock();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Do_Tests()
* @brief      Do_Tests
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Do_Tests()
{
  TESTS_LIST_FUNCTION listfunctions[] = { { false  , Test_XString                    , __L("Test XString")                    },
                                          { false  , Test_XBuffer                    , __L("Test XBuffer")                    },
                                          { false  , Test_XVector                    , __L("Test XVector")                    },
                                          { false  , Test_XRand                      , __L("Test_XRand")                      },
                                          { false  , Test_XTrace                     , __L("Test XTrace")                     },
                                          { false  , Test_XLogs                      , __L("Test XLogs")                      },
                                          { false  , Test_XTree                      , __L("Test XTree")                      },
                                          { false  , Test_XDir                       , __L("Test XDir")                       },
                                          { false  , Test_Threads                    , __L("Test_Threads")                    },
                                          { false  , Test_DateTime                   , __L("Test_DateTime")                   },
                                          { false  , Test_HASH                       , __L("Test HASH")                       },
                                          { false  , Test_DIOStreamTCPIPConnection   , __L("Test DIOStreamTCPIPConnection")   },
                                          { false  , Test_XSystem                    , __L("Test System")                     },                                          
                                          { false  , Test_SharedMemory               , __L("Test SharedMemory")               },
                                          { false  , Test_GPIO                       , __L("Test GPIO")                       },
                                          { false  , Test_WebClient                  , __L("Test WebClient")                  },
                                          { false  , Test_ScraperWeb                 , __L("Test Scraper Web")                },
                                          { false  , Test_MPSSE                      , __L("Test MPSSE")                      },
                                          { false  , Test_DNSProtocol                , __L("Test DNS Protocol")               },
                                          { false  , Test_DIOCheckTCPIPConnections   , __L("Test DIOCheckTCPIPConnections")   },
                                          { false  , Test_WifiEnum                   , __L("Test Wifi Enum")                  },                                          
                                          { false  , Test_WakeOnLAN                  , __L("Test Wake On LAN")                },
                                          { false  , Test_DIOStreamTLS               , __L("Test DIOStreamTLS")               },         
                                          { false  , Test_SystemCPUUsage             , __L("Test System CPU Usage")           },         
                                          { false  , Test_AppAlerts                  , __L("Test App Alerts")                 },  
                                          { false  , Test_BluetoothEnum              , __L("Test Bluetooth Enum")             },                                          
                                          { false  , Test_BluetoothLEEnum            , __L("Test Bluetooth LE Enum")          },                                          
                                          { false  , Test_NTP_InternetServices       , __L("Test_NTP_InternetServices")       },                                              
                                          { false  , Test_Sound                      , __L("Test Sound")                      },       
                                          { true   , Test_ProcessManager             , __L("Test Process Manager")            },
                                          { false  , Test_GetUserAndDomain           , __L("Test Get User And Domain")        },
                                          { false  , Test_I2C_GPIO_MCP2317           , __L("Test I2C GPIO MCP2317")           },
                                          { false  , Test_SPI_GPIO_MCP2317           , __L("Test SPI GPIO MCP2317")           },
                                          { false  , Test_WifiManagerMode            , __L("Test Wifi Manager Mode")          }, 
                                          { false  , Test_NotificationsManager       , __L("Test Notifications Manager")      }, 
                                          { false  , Test_ATCommandGSM               , __L("Test AT Command GSM ")            }, 
                                          { false  , Test_SNMP                       , __L("Test SNMP ")                      },
                                          { false  , Test_XFileXML                   , __L("Test XFile XML")                  },  
                                          { false  , Test_XFileRIFF                  , __L("Test XFile RIFF")                 },
                                          { false  , Test_DIOStreamUSBConnection     , __L("Test DIOStreamConnection")        },
                                          { false  , Test_XFileDFU                   , __L("Test XFile DFU")                  },
                                          { false  , Test_SystemHostFile             , __L("Test System Host File")           },
                                          { false  , Test_SystemBatteryLevel         , __L("Test System Battery Level")       },
                                          { false  , Test_LedNeoPixelWS2812B         , __L("Test Led NeoPixel WS2812B")       }, 
                                          { false  , Test_DIOPCap                    , __L("Test DIO PCap")                   }, 
                                          { true   , Test_XProperty                  , __L("Test XProperty")                  },

                                          #ifdef WINDOWS
                                          { false  , Test_WindowsACL                 , __L("Test Windows ACL")                },
                                          #endif

                                          #ifdef LINUX
                                          { false  , Test_DBUS                       , __L("Test DBUS")                       },
                                          { false  , Test_NetWorkManager             , __L("Test Network Manager")            },
                                          { false  , Test_DeviceBusInputFile         , __L("Test Device Bus Input File")      },
                                          #endif                                       
                                        };

  for(int c=0; c<(sizeof(listfunctions)/sizeof(TESTS_LIST_FUNCTION)); c++)
    {
       if(listfunctions[c].active)
         {
           bool status = listfunctions[c].function(this);

           tests->console->Printf(__L("\n"));
           tests->console->Printf(__L("   [%02d] Test %-32s : %s \n"), c, listfunctions[c].namefunction, (status?__L("Ok."):__L("Error!")));
         }
    }

  //--------------------------------------------------------------------------------------------------

  console->PrintMessage(__L(" "), 0, false, true);
  console->WaitKey(__L("  Pulsa una tecla para continuar... (%d)"), 1, false, 5);

  //--------------------------------------------------------------------------------------------------

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Params_IsModeServer()
* @brief      IsModeServer
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Params_IsModeServer()
{
  bool modeserver = false;

  if(tests->GetExecParams())
    {
      XSTRING* param = (XSTRING*)tests->GetExecParams()->Get(0);
      if(param)
        {
          if(!param->Compare(__L("SERVER"), true))
            {
              modeserver = true;
            }
        }
    }

  return modeserver;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_XString(TESTS* tests)
* @brief      Test_XString
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param[in]  tests :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_XString(TESTS* tests)
{
  if(!tests->console) return false;

  XSTRING string;
  XSTRING substring;


  string = __L("hola radiola");
  string += __L(" mas... ");

  int index = string.Find(__L("mas"), true);

  XSTRING_CREATEOEM(string, charvar)
  printf(charvar);
  XSTRING_DELETEOEM(string, charvar)


  substring.AdjustSize(32);

  string.Format(__L("esto es una prueba %d"), 10);
  string.UnFormat(__L("esto es una %s"), substring.Get());

  substring.AdjustSize();

  tests->console->Printf(string.Get(), __L("\n\r"));

  XVECTOR<XSTRING*> results;

  //string = __L("hola;Radiola;Prueba de example;mas");

  string = __L("[123|321][234|432][hola]");

  string.Split(__C('['), results, false);



  string.Format(__L("Prueba de %3.2f%%"), 10.11f);

  tests->console->PrintMessage(string.Get(), 0, false, true);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_XBuffer(TESTS* tests)
* @brief      Test_XBuffer
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param[in]  tests :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_XBuffer(TESTS* tests)
{
  if(!tests->console) return false;

  XBUFFER   buffer;
  XWORD     valueword  = 0;
  XDWORD    valuedword = 0;
  XVARIANT  variant;
  XSTRING   string;

  
  buffer.Resize(32);

  buffer.Set((XBYTE)0x01, 0);
  buffer.Set((XWORD)0x0203, 1);
  buffer.Set((XDWORD)0x55AA55AA, 3);

  XTRACE_PRINTDATABLOCK(1, buffer, 1, 16);

  buffer.SetWithMask(__L("D"), 3, 0xAAAAAAAA);

  XTRACE_PRINTDATABLOCK(1, buffer, 1, 16);

  buffer.InsertWithMask(__L("W"), 3, 0xCAFE);

  XTRACE_PRINTDATABLOCK(1, buffer, 1, 16);

  valueword = 0;
  buffer.GetWithMask(__L("W"), 3, &valueword);

  XTRACE_PRINTDATABLOCK(1, buffer, 1, 16);

  valueword  = 0;
  valuedword = 0;
  buffer.ExtractWithMask(__L("WD"), 3, &valueword, &valuedword);

  XTRACE_PRINTDATABLOCK(1, buffer, 1, 16);

  XBYTE array[8] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };
  buffer.InsertWithMask(__L("A8"), 3, array);

  XTRACE_PRINTDATABLOCK(1, buffer, 1, 16);

  memset(array, 0, sizeof(array));
  buffer.InsertWithMask(__L("AX"), 3, array, sizeof(array));

  XTRACE_PRINTDATABLOCK(1, buffer, 1, 16);

  memset(array, 0, sizeof(array));
  buffer.ExtractWithMask(__L("AX"), 3, array, sizeof(array));

  XTRACE_PRINTDATABLOCK(1, buffer, 1, 16);

  variant = (XDWORD)10;
  buffer.InsertWithMask(__L("V"), 3, &variant);

  XTRACE_PRINTDATABLOCK(1, buffer, 1, 16);

  variant = (XDWORD)00;
  buffer.ExtractWithMask(__L("V"), 3, &variant);

  XTRACE_PRINTDATABLOCK(1, buffer, 1, 16);

  string = __L("hola radiola");
  buffer.InsertWithMask(__L("S"), 3, &string);

  XTRACE_PRINTDATABLOCK(1, buffer, 1, 16);

  string.Empty();
  buffer.ExtractWithMask(__L("S"), 3, &string);

  XTRACE_PRINTDATABLOCK(1, buffer, 1, 16);
  
  /*
  buffer.Bit_SetNBits(31);

  buffer.Bit_AddData(0xFFFFFFFF);

  XTRACE_PRINTDATABLOCK(1, buffer, 1, 16);

  buffer.Bit_AddData(0xFFFFFFFF);

  XTRACE_PRINTDATABLOCK(1, buffer, 1, 16);

  buffer.Bit_AddData(0xFFFFFFFF);

  XTRACE_PRINTDATABLOCK(1, buffer, 1, 16);

  XDWORD data = buffer.Bit_GetData(0);

  XTRACE_PRINTCOLOR(1, __L("%X"), data);

  data = 0xFFFF55AA;

  buffer.Bit_SetData(data, 0);

  XTRACE_PRINTDATABLOCK(1, buffer, 1, 16);
  */

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTS::Test_XRand(TESTS* tests)
* @brief      Test_XRand
* @ingroup    APPLICATION
* 
* @author     Abraham J. Velez 
* @date       10/11/2021 17:47:57
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_XRand(TESTS* tests)
{
  GEN_XRAND.Ini();

  for(int c=0; c<10; c++)
    {
      int value = GEN_XRAND.Between(0, 10);
      tests->console->Printf(__L("   [%2d] Random value: %d\n"), c, value);
    }

  for(int c=0; c<10; c++)
    {
      float value = ((float)GEN_XRAND.Between(0, 50) / (float)GEN_XRAND.Between(2, 9));
      tests->console->Printf(__L("   [%2d] Random value: %f\n"), c, value);
    }

  tests->console->Printf(__L("\n"));

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_XVector(TESTS* tests)
* @brief      Test_XVector
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param[in]  tests :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_XVector(TESTS* tests)
{
  if(!tests->console) return false;

  /*
  XVECTOR<int>  vector;

  //vector.SetIsMulti(true);

  vector.Add(10);
  vector.Add(50);
  vector.Add(10);

  int number = vector.Get(1);

  vector.Delete(50);

  vector.DeleteAll();
  */

  XVECTOR<XSTRING*>  vector;

  for(int c=0; c<11; c++)
    {
      XSTRING* string = new XSTRING();
      if(string)
        {
          string->Set(__L("hola"));
        }

      vector.Add(string);
    }

  vector.DeleteContents();
  vector.DeleteAll();


  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_XTrace()
* @brief      Test_XDebugTrace
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_XTrace(TESTS* tests)
{
  XDWORD counter = 10;

  if(!tests->console) return false;

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLACK  , __L("[%d] Linea de DEBUG .... "), counter);
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE   , __L("[%d] Linea de DEBUG .... "), counter);
  XTRACE_PRINTCOLOR(XTRACE_COLOR_GREEN  , __L("[%d] Linea de DEBUG .... "), counter);
  XTRACE_PRINTCOLOR(XTRACE_COLOR_PURPLE , __L("[%d] Linea de DEBUG .... "), counter);
  XTRACE_PRINTCOLOR(XTRACE_COLOR_RED    , __L("[%d] Linea de DEBUG .... "), counter);
  XTRACE_PRINTCOLOR(XTRACE_COLOR_GRAY   , __L("[%d] Linea de DEBUG .... "), counter);

  for(int c=0; c<5000; c++)
    {
      XTRACE_PRINTTAB(c, __L("[%d] Linea de DEBUG .... "), counter);
    }

  for(int c=0; c<5000; c++)
    {
      XTRACE_PRINTCODE(c, __L("[%d] Linea de DEBUG .... "), counter);
    }

  XBUFFER xbuffer;

  for(int c=0; c<1000; c++)
    {
      xbuffer.Add((XBYTE)0xFF);
    }

  XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_BLACK  , xbuffer);
  XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_BLUE   , xbuffer);
  XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_GREEN  , xbuffer);
  XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_PURPLE , xbuffer);
  XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_RED    , xbuffer);
  XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_GRAY   , xbuffer);


   for(int c=0; c<1000; c++)
    {
      XTRACE_PRINTDATABLOCKTAB(c, xbuffer);
    }

  for(int c=0; c<1000; c++)
    {
      XTRACE_PRINTDATABLOCKCODE(c, xbuffer);
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_XLogs(TESTS* tests)
* @brief      Test_XLogs
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param[in]  tests :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_XLogs(TESTS* tests)
{
  if(!APP_CFG.Log_IsActive()) return false;

  XBUFFER  xbuffer;
  XRAND*   xrand = GEN_XFACTORY.CreateRand();
  int      index = 0;

  if(!xrand) return false;

  xrand->Ini();

  for(int d=0; d<100; d++)
    {   

      int ndata = xrand->Between(16, 64);

      for(int c=0; c<100; c++)
        {         
          if(tests->console->KBHit()) break;
            
          xbuffer.Delete();         
          for(int e=0; e<ndata; e++)
            {
              xbuffer.Add((XBYTE)xrand->Max(255));
            }       

          APP_LOG_ENTRY(XLOGLEVEL_INFO, APP_CFG_LOG_SECTIONID_GENERIC, false, __L("%08d %s"), index, __L("Entrada en memoria del LOG"));          
          APP_LOG_ENTRY(XLOGLEVEL_INFO, APP_CFG_LOG_SECTIONID_GENERIC, false, xbuffer);

          index++;
        }     

      if(tests->console->KBHit()) break;

    }

  if(tests->console->KBHit()) 
    {
      tests->console->GetChar();
    }  

  GEN_XFACTORY.DeleteRand(xrand);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_XTree_AddChilds(XTREENODE_TEST* node, int nchild)
* @brief      Test_XTree_AddChilds
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param[in]  node :
* @param[in]  nchild :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_XTree_AddChilds(XTREE_NODE_TEST* node, int nchild)
{
  bool status = true;

  for(int c=0; c<nchild; c++)
    {
      XSTRING* subnodedata = new XSTRING();
      if(subnodedata)
        {
          subnodedata->Format(__L("%2d Child"), c+1);

          XTREE_NODE_TEST* subnode = new XTREE_NODE_TEST(subnodedata);
          if(subnode)
            {
              node->AddChild(subnode);
            }
           else
            {
              status = false;
              break;
            }
        }
       else
        {
          status = false;
          break;
        }
    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_XTree_InsertChilds(XTREE_NODE_TEST* node, int indexchild)
* @brief      Test_XTree_InsertChilds
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param[in]  node :
* @param[in]  indexchild :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_XTree_InsertChilds(XTREE_NODE_TEST* node, int indexchild)
{
  XSTRING* subnodedata = new XSTRING();
  if(!subnodedata) return false;

  subnodedata->Format(__L("%2d Insert Child"), indexchild);

  XTREE_NODE_TEST* subnode = new XTREE_NODE_TEST(subnodedata);
  if(subnode)
    {
      Test_XTree_AddChilds(subnode, 5);

      return node->InsertChild(indexchild, subnode);
    }

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_XTree(TESTS* tests)
* @brief      Test_XTree
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param[in]  tests :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_XTree(TESTS* tests)
{
  XTREE_TEST        xtree;
  XSTRING*          rootdata  = NULL;
  XTREE_NODE_TEST*  root      = NULL;

  rootdata = new XSTRING();
  if(!rootdata) return false;

  rootdata->Set("Root");

  root = new XTREE_NODE_TEST(rootdata);
  if(!root)
    {
      delete rootdata;
      return false;
    }

  tests->Test_XTree_AddChilds(root, 3);

  for(int c=0; c<root->GetNChildren(); c++)
    {
      XTREE_NODE_TEST* subnode = root->GetChild(c);
      if(subnode)
        {
          tests->Test_XTree_AddChilds(subnode, 2);

          for(int d=0; d<subnode->GetNChildren(); d++)
            {
              XTREE_NODE_TEST* subnode2 = subnode->GetChild(d);
              if(subnode2)
                {
                  if((c == 2) && (d == 0))
                        tests->Test_XTree_InsertChilds(subnode, 1);
                   else tests->Test_XTree_AddChilds(subnode2, 1);
                }
            }
        }
    }

  xtree.SetRoot(root);

  //--------------------------------------------------------
  // Show content

  XTREE_NODE_ITERATOR_TEST  it(xtree.Begin());
  XTREE_NODE_ITERATOR_TEST  it_end(xtree.End());

  while(it != it_end)
    {
      XTREE_NODE_TEST*  node   = it.GetCurrent();
      XSTRING           string;
      if(node)
        {
          if(node->GetLevel())
            {
              XSTRING tabsstr;

              tabsstr.Empty();
              for(int c=0; c<node->GetLevel()-1; c++)
                {
                  tabsstr.Add(__L("  "));
                }

              string.Format(__L("%s|- [%02d]"), tabsstr.Get(), node->GetLevel());
            }

          string.AddFormat(__L("%s"), (*it)->Get());

          tests->console->Printf(__L("%s\n"), string.Get());
          XTRACE_PRINTCOLOR(1, __L("%s"), string.Get());
        }

      ++it;
    }

  tests->console->Printf(__L("\n"));

  //--------------------------------------------------------
  // Delete all

  xtree.DeleteContents();
  xtree.DeleteAll();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_XDir(TESTS* tests)
* @brief      Test_XDir
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param[in]  tests :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_XDir(TESTS* tests)
{
  XDIR* xdir = GEN_XFACTORY.Create_Dir();
  if(!xdir) return false;

  XPATH         xpath;
  XDIRELEMENT   element;

  xdir->GetActual(xpath);

  tests->console->Printf(__L("Current DIR: [%s]\n"), xpath.Get());

  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpath);
  xpath.Slash_Add();
      
  if(xdir->FirstSearch(xpath.Get(), __L("*"), &element))
    {
      do{ XSTRING datetimestr;
              
          element.GetDateTimeFile_LastAccess()->GetDateTimeToString((XDATETIME_FORMAT_ADDDATE | XDATETIME_FORMAT_ADDTIME | XDATETIME_FORMAT_TIMEWITHSECONDS | XDATETIME_FORMAT_TEXTMONTH), datetimestr);

          tests->console->Printf(__L("Elements DIR: [%s] %s\n"), element.GetNameFile()->Get(), datetimestr.Get());
         
        } while(xdir->NextSearch(&element));
    }            
    

  GEN_XFACTORY.Delete_Dir(xdir);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_Threads(TESTS* tests)
* @brief      Test_Threads
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param[in]  tests :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_Threads(TESTS* tests)
{
  if(!tests->console) return false;

  XTHREADCOLLECTED* threads[TESTS_MAXNTHREADS];

  memset(threads, 0, TESTS_MAXNTHREADS * sizeof(XTHREADCOLLECTED*));

  for(int c=0; c<TESTS_MAXNTHREADS; c++)
    {
      void* index = 0;

      memcpy(&index, &c, sizeof(int));

      threads[c] = CREATEXTHREAD(XTHREADGROUPID_APPOWNER, __L("TESTS::Test_Threads"), ThreadRunFunction, index);
      if(!threads[c]) return false;

      threads[c]->Ini();
    }

  GEN_XSLEEP.Seconds(5);

  for(int c=0; c<TESTS_MAXNTHREADS; c++)
    {
      DELETEXTHREAD(XTHREADGROUPID_APPOWNER, threads[c]);
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_DateTime(TESTS* tests)
* @brief      Test_DateTime
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param[in]  tests :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_DateTime(TESTS* tests)
{  
  XSTRING     datetimestring;
  XDATETIME*  datetime = GEN_XFACTORY.CreateDateTime();
  if(!datetime) return false;
    
  datetime->Read();

  datetime->GetDateTimeToString(XDATETIME_FORMAT_STANDARD, datetimestring);

  tests->console->Printf(__L("Date %s  Number of Week %d\n"), datetimestring.Get(), datetime->GetWeekOfYear());
  tests->console->Printf(__L("Date EPOCH: %d\n"), datetime->GetEPOCHFormat());

  /*    
  datetime->SetDay(1);
  datetime->SetMonth(1);
  datetime->SetHours(1);
  datetime->SetMinutes(1);
  datetime->SetSeconds(1);

  for(int c=0; c<365; c++)
    {
      datetime->GetDateTimeToString(XDATETIME_FORMAT_STANDARD, datetimestring);
      tests->console->Printf(__L("Date %s  Number of Week %d\n"), datetimestring.Get(), datetime->GetWeekOfYear());
      datetime->AddDays(1);
    }
   */

  XPATH xpath;

  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpath);
  xpath.Slash_Add();
  xpath.Add(APPLICATION_NAMEFILE);
  xpath.Add(XFILECFG_EXTENSIONFILE);

  datetime->GetFileDateTime(xpath);
  datetime->GetDateTimeToString(XDATETIME_FORMAT_STANDARD, datetimestring);
  tests->console->Printf(__L("Date %s:%d of the file %s\n"), datetimestring.Get(), datetime->GetMilliSeconds(), xpath.Get());

  GEN_XFACTORY.DeleteDateTime(datetime);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_HASH(TESTS* tests)
* @brief      Test_HASH
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param[in]  tests :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_HASH(TESTS* tests)
{
  if(!tests->console) return false;

  XBUFFER  input;
  XSTRING  leyend;
  XSTRING  string;

  string = __L("The quick brown fox jumps over the lazy dog");

  tests->console->Printf(__L("Sentence: \"%s\"\n\n"), string.Get());

  XSTRING_CREATEOEM(string, charstr)
  input.Add((XBYTE*)charstr, string.GetSize());
  XSTRING_DELETEOEM(string, charstr)

  for(int c=0;c<8;c++)
    {
      HASH* hash = NULL;
      switch(c)
        {
          case  0 :  hash = new HASHCRC32();                    leyend = __L("CRC32");      break;
          case  1 :  hash = new HASHMD5();                      leyend = __L("MD5");        break;
          case  2 :  hash = new HASHSHA1();                     leyend = __L("SHA1");       break;
          case  3 :  hash = new HASHSHA2(HASHSHA2TYPE_224);     leyend = __L("SHA2 224");   break;
          case  4 :  hash = new HASHSHA2(HASHSHA2TYPE_256);     leyend = __L("SHA2 256");   break;
          case  5 :  hash = new HASHSHA2(HASHSHA2TYPE_384);     leyend = __L("SHA2 384");   break;
          case  6 :  hash = new HASHSHA2(HASHSHA2TYPE_512);     leyend = __L("SHA2 512");   break;
          case  7 :  hash = new HASHWHIRLPOOL();                leyend = __L("Whirpool");   break;
        }

      if(!hash) return false;

      tests->Test_Hash(hash, input, leyend.Get());
      delete hash;
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_DIOStreamTCPIPConnection(TESTS* tests)
* @brief      Test_DIOStreamTCPIPConnection
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param[in]  tests :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_DIOStreamTCPIPConnection(TESTS* tests)
{
  if(!tests->console) return false;

  DIOSTREAMTCPIPCONFIG diostreamcfg;
  DIOSTREAM*           diostream    = NULL;
  bool                 status       = false;

  diostreamcfg.SetMode(DIOSTREAMMODE_SERVER);
  diostreamcfg.SetRemotePort(8099);

  tests->console->Printf(__L("\n\nAbriendo servidor local  %s : %d\n\n"), diostreamcfg.GetLocalIP()->Get(), diostreamcfg.GetRemotePort());

  diostream = (DIOSTREAM*)GEN_DIOFACTORY.CreateStreamIO(&diostreamcfg);
  if(diostream)
    {
      int c=0;
      while(!tests->console->KBHit())
        {
          if(diostream->Open())
            {
              status = diostream->WaitToConnected(1);

              tests->console->Printf(__L("\r\nConexion %d estado: %s"), c, status?__L("Connected.       "):__L("Waiting...    "));

              while(diostream->GetConnectStatus()==DIOSTREAMSTATUS_CONNECTED)
                {
                  tests->console->Printf    (__L("\r\n    Sending packet(%d)"), c++);

                  diostream->WriteStr (__L("Hello Jello!\r\n"));
                  diostream->WaitToFlushOutXBuffer();
                }

              if(diostream->GetConnectStatus() !=  DIOSTREAMSTATUS_GETTINGCONNECTION) tests->console->Printf(__L("\r\nConexion %d estado: Disconnected"), c);

              diostream->Close();
              c=0;

              status = true;
            }
        }

      DIOFACTORY::GetInstance().DeleteStreamIO(diostream);
    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTS::Test_System(TESTS* tests)
* @brief      Test_System
* @ingroup    APPLICATION
* 
* @author     Abraham J. Velez 
* @date       11/11/2021 10:53:11
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_XSystem(TESTS* tests)
{
  XSTRING plataform_name;
  XSTRING OS_ID;

  GEN_XSYSTEM.GetPlatform(&plataform_name);
  GEN_XSYSTEM.GetOperativeSystemID(OS_ID);

  tests->console->Printf(__L("   Plataform                :  %s  \n"), plataform_name.Get());
  tests->console->Printf(__L("   Operative System Version :  %s  \n"), OS_ID.Get());

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_SharedMemory(TESTS* tests)
* @brief      Test_SharedMemory
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param[in]  tests :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_SharedMemory(TESTS* tests)
{
  #define SHAREDMEMORYID __L("SharedMemoryID")

  if(!tests->console) return false;

  bool modeserver = tests->Params_IsModeServer();

  tests->console->Printf(__L("   Creating Shared Memory: %s \n"), (modeserver?__L("[Master]"):__L("[Slave]")));

  
  XBYTE*    pointer = NULL;
  XDWORD    size    = 0;
  XDWORD*   data    = 0;
  bool      exit    = false;

  if(modeserver)
    {
      size = 32;
      pointer = GEN_XSHAREDMEMORYMANAGER.Create(SHAREDMEMORYID, size);
    }
   else pointer = GEN_XSHAREDMEMORYMANAGER.Open(SHAREDMEMORYID, size);

  tests->console->Printf(__L("   Create Shared Memory %d bytes: %s\n"), size, pointer?__L("Ok"):__L("Error!"));

  data = (XDWORD*)pointer;

  XRAND* xrand = GEN_XFACTORY.CreateRand();
  if(xrand)
    {
      if(pointer)
        {
          do{
              if(tests->console->KBHit())
                {
                  switch(tests->console->GetChar())
                    {
                      case ' '  : (*data) = (XDWORD)xrand->Max(100000000);   break;
                        default : exit = true;                               break;
                    }
                }

              tests->console->Printf(__L("   Data Shared Memory: %04X     \r"), (*data));

            } while(!exit);

          GEN_XSHAREDMEMORYMANAGER.Close();
        }

      GEN_XFACTORY.DeleteRand(xrand);
    }

  
  tests->console->Printf(__L("\n   Delete Shared Memory: Ok\n"));

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_GPIO(TESTS* tests)
* @brief      Test_GPIO
* @ingroup    APPLICATION
*
* @author
* @date       01/03/2016 12:30
*
* @param[in]  tests :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_GPIO(TESTS* tests)
{   
  bool status = false;  

  
  #ifdef DIOGPIO_ACTIVE
  
  GEN_DIOGPIO.SetMode(TESTS_GPIOENTRYID_TESTGPIO, DIOGPIO_MODE_OUTPUT);
         
  while(!tests->console->KBHit())
    {
      GEN_DIOGPIO.SetValue(TESTS_GPIOENTRYID_TESTGPIO, true);
      GEN_XSLEEP.MilliSeconds(50);
             
      GEN_DIOGPIO.SetValue(TESTS_GPIOENTRYID_TESTGPIO, false);
      GEN_XSLEEP.MilliSeconds(50);
    }
          
  status = true;

  //--------------------------------------------------------------

  #endif

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_WebClient(TESTS* tests)
* @brief      Test_WebClient
* @ingroup    APPLICATION
*
* @author
* @date       01/03/2016 12:30
*
* @param[in]  tests :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_WebClient(TESTS* tests)
{
  DIOWEBCLIENT  webclient;
  DIOURL        url;
  XBUFFER       webpage;
  bool          status;

  tests->SubscribeEvent(DIOWEBCLIENT_XEVENT_TYPE_OPENWEB         , &webclient);
  tests->SubscribeEvent(DIOWEBCLIENT_XEVENT_TYPE_WRITEHEADER     , &webclient);
  tests->SubscribeEvent(DIOWEBCLIENT_XEVENT_TYPE_SENDPOSTDATA    , &webclient);
  tests->SubscribeEvent(DIOWEBCLIENT_XEVENT_TYPE_HEADERERROR     , &webclient);
  tests->SubscribeEvent(DIOWEBCLIENT_XEVENT_TYPE_READHEADER      , &webclient);
  tests->SubscribeEvent(DIOWEBCLIENT_XEVENT_TYPE_READBODYBLOCK   , &webclient);
  tests->SubscribeEvent(DIOWEBCLIENT_XEVENT_TYPE_CLOSEWEB        , &webclient);


  //url = __L("http://ovh.net/files/10Mio.dat");
  url = __L("http://ovh.net/files/1Gio.dat");
  webclient.Set_Port(80);

  status =  webclient.Get(url, webpage, NULL, 60);
  XTRACE_PRINTCOLOR((status?1:4), __L("GET Web Client %s: %s"), url.Get(), status?__L("Ok!"):__L("Error!"));
  if(status)
    {
      XTRACE_PRINTDATABLOCK(1, webpage);
    }

  tests->UnSubscribeEvent(DIOWEBCLIENT_XEVENT_TYPE_OPENWEB         , &webclient);
  tests->UnSubscribeEvent(DIOWEBCLIENT_XEVENT_TYPE_WRITEHEADER     , &webclient);
  tests->UnSubscribeEvent(DIOWEBCLIENT_XEVENT_TYPE_SENDPOSTDATA    , &webclient);
  tests->UnSubscribeEvent(DIOWEBCLIENT_XEVENT_TYPE_HEADERERROR     , &webclient);
  tests->UnSubscribeEvent(DIOWEBCLIENT_XEVENT_TYPE_READHEADER      , &webclient);
  tests->UnSubscribeEvent(DIOWEBCLIENT_XEVENT_TYPE_READBODYBLOCK   , &webclient);
  tests->UnSubscribeEvent(DIOWEBCLIENT_XEVENT_TYPE_CLOSEWEB        , &webclient);


  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_ScrapersWeb()
* @brief      Test_ScrapersWeb
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_ScraperWeb(TESTS* tests)
{
  DIOSCRAPERWEBPUBLICIP*        publicip        = new DIOSCRAPERWEBPUBLICIP;
  DIOSCRAPERWEBGEOLOCATIONIP*   geolocationip   = new DIOSCRAPERWEBGEOLOCATIONIP;
  DIOSCRAPERWEBSEXNAME*         sexname         = new DIOSCRAPERWEBSEXNAME;
  DIOSCRAPERWEBUSERAGENTID*     useragentID     = new DIOSCRAPERWEBUSERAGENTID;
  DIOSCRAPERWEBTRANSLATION*     translation     = new DIOSCRAPERWEBTRANSLATION;
  DIOSCRAPERWEBMACMANUFACTURER* macmanufactured = new DIOSCRAPERWEBMACMANUFACTURER;
  DIOSCRAPERWEBWEATHER*         weather         = new DIOSCRAPERWEBWEATHER;

  XSTRING localIP;

  localIP = __L("192.168.1.3");

  //webclient->GetProxyURL()->Set(__L("10.155.192.17"));
  //webclient->SetProxyPort(8080);

    for(int c=0; c<10; c++)
      {
        if(publicip)
          {
            DIOIP ip;

            if(publicip->Get(ip, 5, &localIP))
              {
                XSTRING IPstring;

                ip.GetXString(IPstring);

                tests->console->Printf(__L("Public IP : %s\n\n"), IPstring.Get());

                if(geolocationip)
                  {
                    DIOGEOLOCATIONIP_RESULT geoIP;

                    if(geolocationip->Get(ip, geoIP, 5, &localIP))
                      {
                        tests->console->Printf(__L("City         : %s\n"),  geoIP.GetCity());
                        tests->console->Printf(__L("State        : %s\n"),  geoIP.GetState());
                        tests->console->Printf(__L("Contry       : %s\n"),  geoIP.GetCountry());
                        tests->console->Printf(__L("ISP          : %s\n"),  geoIP.GetISP());
                        tests->console->Printf(__L("Organization : %s\n"),  geoIP.GetOrganization());

                      } else tests->console->Printf(__L("Error!!!!\n"));

                    tests->console->Printf(__L("\n"));
                  }
              }
          }

        if(sexname)
          {
            DIOSCRAPERWEBSEXNAMETYPE sextype;
            XSTRING                  name;

            sexname->Get(__L("Alai"), sextype, &name,  5, &localIP);
            tests->console->Printf(__L("El nombre %.15s "), name.Get());

            switch(sextype)
              {
                case DIOSCRAPERWEBSEXNAMETYPE_NOTOBTAINED : tests->console->Printf(__L("no obtenido."));              break;
                case DIOSCRAPERWEBSEXNAMETYPE_NONAME      : tests->console->Printf(__L("no es un nombre propio."));   break;
                case DIOSCRAPERWEBSEXNAMETYPE_MALE        : tests->console->Printf(__L("es de hombre"));              break;
                case DIOSCRAPERWEBSEXNAMETYPE_FEMALE      : tests->console->Printf(__L("es de mujer"));               break;
              }

            tests->console->Printf(__L("\n\n"));
          }


        if(useragentID)
          {
            XSTRING browser;
            XSTRING SO;

            useragentID->Get(__L("Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.31 (KHTML, like Gecko) Chrome/26.0.1410.64 Safari/537.31"), browser, SO, 5, &localIP);

            tests->console->Printf(__L("Browser          : %s\n"), browser.Get());
            tests->console->Printf(__L("System Operative : %s\n"), SO.Get());

            tests->console->Printf(__L("\n"));
          }


        if(translation)
          {
            XSTRING        translate;
            XLANGUAGE_CODE languajes[] = {  XLANGUAGE_ISO_639_3_CODE_AFR     , //   Afrikaans
                                            XLANGUAGE_ISO_639_3_CODE_ALB     , //   Albanian
                                            XLANGUAGE_ISO_639_3_CODE_ARA     , //   Arabic
                                            XLANGUAGE_ISO_639_3_CODE_AZE     , //   Azerbaijani
                                            XLANGUAGE_ISO_639_3_CODE_BAQ     , //   Basque
                                            XLANGUAGE_ISO_639_3_CODE_BEL     , //   Belarusian
                                            XLANGUAGE_ISO_639_3_CODE_BEN     , //   Bengali
                                            XLANGUAGE_ISO_639_3_CODE_BUL     , //   Bulgarian
                                            XLANGUAGE_ISO_639_3_CODE_CAT     , //   Catalan
                                            XLANGUAGE_ISO_639_3_CODE_CHI     , //   Chinese    CHINESE_SIMPLIFIED  __L("zh-CN") CHINESE_TRADITIONAL __L("zh-TW")
                                            XLANGUAGE_ISO_639_3_CODE_CZE     , //   Czech
                                            XLANGUAGE_ISO_639_3_CODE_DAN     , //   Danish
                                            XLANGUAGE_ISO_639_3_CODE_DUT     , //   Dutch
                                            XLANGUAGE_ISO_639_3_CODE_ENG     , //   English
                                            XLANGUAGE_ISO_639_3_CODE_EPO     , //   Esperanto
                                            XLANGUAGE_ISO_639_3_CODE_EST     , //   Estonian
                                            XLANGUAGE_ISO_639_3_CODE_FIN     , //   Finnish
                                            XLANGUAGE_ISO_639_3_CODE_FRE     , //   French
                                            XLANGUAGE_ISO_639_3_CODE_GEO     , //   Georgian
                                            XLANGUAGE_ISO_639_3_CODE_GER     , //   German
                                            XLANGUAGE_ISO_639_3_CODE_GLE     , //   Irish
                                            XLANGUAGE_ISO_639_3_CODE_GLG     , //   Galician
                                            XLANGUAGE_ISO_639_3_CODE_GRE     , //   Greek Modern (1453-)
                                            XLANGUAGE_ISO_639_3_CODE_GUJ     , //   Gujarati
                                            XLANGUAGE_ISO_639_3_CODE_HAT     , //   Haitian
                                            XLANGUAGE_ISO_639_3_CODE_HEB     , //   Hebrew
                                            XLANGUAGE_ISO_639_3_CODE_HIN     , //   Hindi
                                            XLANGUAGE_ISO_639_3_CODE_HRV     , //   Croatian
                                            XLANGUAGE_ISO_639_3_CODE_HUN     , //   Hungarian
                                            XLANGUAGE_ISO_639_3_CODE_ICE     , //   Icelandic
                                            XLANGUAGE_ISO_639_3_CODE_IND     , //   Indonesian
                                            XLANGUAGE_ISO_639_3_CODE_ITA     , //   Italian
                                            XLANGUAGE_ISO_639_3_CODE_JPN     , //   Japanese
                                            XLANGUAGE_ISO_639_3_CODE_KAN     , //   Kannada
                                            XLANGUAGE_ISO_639_3_CODE_KOR     , //   Korean
                                            XLANGUAGE_ISO_639_3_CODE_LAT     , //   Latin
                                            XLANGUAGE_ISO_639_3_CODE_LAV     , //   Latvian
                                            XLANGUAGE_ISO_639_3_CODE_LIT     , //   Lithuanian
                                            XLANGUAGE_ISO_639_3_CODE_MAC     , //   Macedonian
                                            XLANGUAGE_ISO_639_3_CODE_MAY     , //   Malay
                                            XLANGUAGE_ISO_639_3_CODE_MLT     , //   Maltese
                                            XLANGUAGE_ISO_639_3_CODE_NOR     , //   Norwegian
                                            XLANGUAGE_ISO_639_3_CODE_PER     , //   Persian
                                            XLANGUAGE_ISO_639_3_CODE_POL     , //   Polish
                                            XLANGUAGE_ISO_639_3_CODE_POR     , //   Portuguese
                                            XLANGUAGE_ISO_639_3_CODE_RUM     , //   Romanian
                                            XLANGUAGE_ISO_639_3_CODE_RUS     , //   Russian
                                            XLANGUAGE_ISO_639_3_CODE_SLO     , //   Slovak
                                            XLANGUAGE_ISO_639_3_CODE_SLV     , //   Slovenian
                                            XLANGUAGE_ISO_639_3_CODE_SPA     , //   Spanish
                                            XLANGUAGE_ISO_639_3_CODE_SRP     , //   Serbian
                                            XLANGUAGE_ISO_639_3_CODE_SWA     , //   Swahili
                                            XLANGUAGE_ISO_639_3_CODE_SWE     , //   Swedish
                                            XLANGUAGE_ISO_639_3_CODE_TAM     , //   Tamil
                                            XLANGUAGE_ISO_639_3_CODE_TEL     , //   Telugu
                                            XLANGUAGE_ISO_639_3_CODE_THA     , //   Thai
                                            XLANGUAGE_ISO_639_3_CODE_TUR     , //   Turkish
                                            XLANGUAGE_ISO_639_3_CODE_UKR     , //   Ukrainian
                                            XLANGUAGE_ISO_639_3_CODE_URD     , //   Urdu
                                            XLANGUAGE_ISO_639_3_CODE_VIE     , //   Vietnamese
                                            XLANGUAGE_ISO_639_3_CODE_WEL     , //   Welsh
                                            XLANGUAGE_ISO_639_3_CODE_YID     , //   Yiddish

                                         };

            XSTRING origin;
            int     index = 0;

            origin = __L("La mesa de mi casa es roja");
            tests->console->Printf(__L("> %s\n"),origin.Get());

            for(int c=0;c<(sizeof(languajes)/sizeof(int))-1;c++)
              {
                if(translation->Get(origin.Get(), XLANGUAGE_ISO_639_3_CODE_SPA , languajes[c], translate, 5, &localIP))
                  {
                    if(translate.IsOEM())
                           tests->console->Printf(__L("> %s\n"),translate.Get());
                      else tests->console->Printf(__L("> (Special chars)\n"));

                    origin = translate.Get();
                    index = c+1;
                  }
              }

            tests->console->Printf(__L("\n"));
          }


        if(macmanufactured)
          {
            XBYTE    MAC[DIOMAC_MAXSIZE] = { 0x00, 0x04, 0x20, 0x11, 0x22, 0x33 };
            DIOMAC   deviceMAC;
            XSTRING  manufactured;

            deviceMAC.Set(MAC);

            tests->console->Printf(__L("MAC Manufactured: [%02X%02X%02X] "), deviceMAC.Get()[0], deviceMAC.Get()[1], deviceMAC.Get()[2]);

            if(macmanufactured->Get(deviceMAC, manufactured, 5, &localIP))
                  tests->console->Printf(__L("%s")      , manufactured.Get());
             else tests->console->Printf(__L("Unknow"));

            tests->console->Printf(__L("\n"));
          }

        if(weather)
          {
            XSTRING condition;
            float   temperature;
            float   humidity;

            tests->console->Printf(__L("Estado del tiempo: "));

            if(weather->Get(__L("SPXX0016"), true, condition, temperature,  humidity, 5, &localIP))
                    tests->console->Printf(__L("[%s] Temperatura %3.2f, humedad %3.2f%%%%. \n"), condition.Get(), temperature, humidity);
              else  tests->console->Printf(__L("no obtenido.\n"));

            tests->console->Printf(__L("\n"));
          }


      }

  delete publicip;
  delete geolocationip;
  delete sexname;
  delete useragentID;
  delete translation;
  delete macmanufactured;
  delete weather;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_MPSSE(TESTS* tests)
* @brief      Test_FT232H
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param[in]  tests :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_MPSSE(TESTS* tests)
{
  DIOMPSSE* MPSSE = new DIOMPSSE();
  if(!MPSSE)  return false;

  bool status = false;

  if(MPSSE->Open(0))
    {
      tests->console->Printf(__L("   Device found FT%s \n"), MPSSE->GetChipTypeName());


      status = true;

      MPSSE->Close();
    }

  delete MPSSE;

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_DNSProtocol(TESTS* tests)
* @brief      Test_DNSProtocol
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param[in]  tests :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_DNSProtocol(TESTS* tests)
{
  DIOURL          URL;
  DIODNSPROTOCOL  dnsprotocol;
  DIOIP           ipresolved;
  bool            status      = false;

  //URL = __L("www.google.es");

  URL = __L("members.dyndns.org");

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[DNS Resolve %s] Ini ..."),  URL.Get());

  status = GEN_DIODNSRESOLVED.ResolveURL(URL.Get(), ipresolved);
  if(status)
    {
      XSTRING IPstring;

      ipresolved.GetXString(IPstring);

      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[DNS Resolve %s] IP resuelve %s  (%s) "), URL.Get(), IPstring.Get(), (URL.IsLocalAddress()?__L("Local"):__L("Internet")));

    }
   else
    {
      XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[DNS Resolve %s] Not Found DNS URL!!!"), URL.Get());
    }

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[DNS Resolve %s] End."), URL.Get());

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_DIOCheckTCPIPConnections(TESTS* tests)
* @brief      Test_DIOCheckTCPIPConnections
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param[in]  tests :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_DIOCheckTCPIPConnections(TESTS* tests)
{
  DIOCHECKINTERNETCONNECTION* checkinternetconnection       = NULL;
  DIOCHECKTCPIPCONNECTIONS*   checkTCPIPconnections         = NULL;
  bool                        status                        = false;

  checkinternetconnection = new DIOCHECKINTERNETCONNECTION(10);
  if(checkinternetconnection)
    {
      //haveinternetconnection = checkinternetconnection->Check();
    }

  checkTCPIPconnections = new DIOCHECKTCPIPCONNECTIONS();
  if(checkTCPIPconnections)
    {
      XDWORD connectionID = 0x55AA55AA;

      status = checkTCPIPconnections->Ini(5, true, true);
      if(status)
        {
          status = checkTCPIPconnections->Connection_Add(__L("172.18.0.1"), connectionID);

          while(!tests->console->KBHit())
            {
              GEN_XSLEEP.Seconds(1);
            }

          checkTCPIPconnections->End();
        }
    }

  if(checkTCPIPconnections)
    {
      delete checkTCPIPconnections;
      checkTCPIPconnections = NULL;
    }


  if(checkinternetconnection)
    {
      delete checkinternetconnection;
      checkinternetconnection = NULL;
    }


  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_WifiEnum(TESTS* tests)
* @brief      Test_WifiEnum
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param[in]  tests :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_WifiEnum(TESTS* tests)
{
  bool                            status            = false;
  #ifdef DIOWIFI_ACTIVE
  DIOSTREAMWIFIREMOTEENUMDEVICES* wifiremotedevices = NULL;

  wifiremotedevices = (DIOSTREAMWIFIREMOTEENUMDEVICES*)GEN_DIOFACTORY.CreateStreamEnumDevices(DIOSTREAMENUMTYPE_WIFI_REMOTE);
  if(!wifiremotedevices) return false;

  status = wifiremotedevices->Search();

  for(XDWORD c=0; c<wifiremotedevices->GetDevices()->GetSize(); c++)
    {
      DIOSTREAMDEVICEWIFI* devicewifi = (DIOSTREAMDEVICEWIFI*)wifiremotedevices->GetDeviceByIndex(c);
      if(devicewifi) devicewifi->DebugPrintInfo();
    }

  GEN_DIOFACTORY.DeleteStreamEnumDevices(wifiremotedevices);
  #endif

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_WakeOnLAN(TESTS* tests)
* @brief      Test_WakeOnLAN
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:30
*
* @param[in]  tests : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_WakeOnLAN(TESTS* tests)
{
  DIOWAKEONLAN* wakeonlan = NULL;
  DIOMAC        MAC;
  DIOIP         broadcastIP;
  XBYTE         MACdata[DIOMAC_MAXSIZE] = { 0x10, 0xBF, 0x48, 0x78, 0x63, 0x53 };
  bool          status                  = false;

  MAC.Set(MACdata);
  broadcastIP.Set(__L("192.168.1.255"));

  wakeonlan = new DIOWAKEONLAN();
  if(!wakeonlan) return status;

  status = wakeonlan->SendActivation(&MAC, &broadcastIP);

  delete wakeonlan;

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_DIOStreamTLS(TESTS* tests)
* @brief      Test_DIOStreamTLS
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:30
*
* @param[in]  tests : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_DIOStreamTLS(TESTS* tests)
{
  if(!tests->console) return false;

  DIOSTREAMTLSCONFIG  diostreamcfg;
  DIOSTREAMTLS*       diostream    = NULL;
  XSTRING             line;
  bool                status       = false;


  diostreamcfg.GetRemoteURL()->Set(__L("www.google.es"));
  diostreamcfg.SetMode(DIOSTREAMMODE_CLIENT);
  diostreamcfg.SetRemotePort(443);

  line.Format(__L("Server [%s]: %d"), diostreamcfg.GetRemoteURL()->Get(), diostreamcfg.GetRemotePort());
  tests->console->Printf(__L("   %s\n"), line.Get());
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, line.Get());

  diostream = new DIOSTREAMTLS(&diostreamcfg);
  if(!diostream) return false;
  
  if(diostream->Open())
    {
      status = diostream->WaitToConnected(5);

      line.Format(__L("Connection status: %s"), status?__L("Connected."):__L("No connected."));  
      tests->console->Printf(__L("   %s\n"), line.Get());
      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), line.Get());            

      if(status)
        {             
          diostream->WriteStr (__L("Hello Jello!\r\n"));
          status = diostream->WaitToFlushOutXBuffer();

          line.Format(__L("Write: %s"), status?__L("Ok."):__L("Error!"));  
          tests->console->Printf(__L("   %s\n"), line.Get());

          XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), line.Get());             
        }
              
      status = diostream->Close();

      line.Format(__L("Close connection: %s"), status?__L("Ok."):__L("Error!"));  
      tests->console->Printf(__L("   %s\n\n"), line.Get());
      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), line.Get());                                 
    }

  delete diostream;
    

  return status;

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_SystemCPUUsage(TESTS* tests)
* @brief      Test_SystemCPUUsage
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:30
*
* @param[in]  tests : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_SystemCPUUsage(TESTS* tests)
{
  XSTRING nameapp;

  #ifdef WINDOWS
  nameapp = __L("tests.exe");
  #endif

  #ifdef LINUX
  nameapp = __L("tests");
  #endif


  while(!tests->console->KBHit())
    {      
      tests->console->Clear();

      tests->console->Printf(__L("   CPU usage %-16s : [%3d%%]       \n"), __L("Total"), GEN_XSYSTEM.GetCPUUsageTotal());                                                                                             
      tests->console->Printf(__L("   CPU usage %-16s : [%3d%%]       \n"), APPLICATION_NAMEAPP, GEN_XSYSTEM.GetCPUUsageForProcessName(nameapp.Get()));       

      /*
      for(int d=0; d<10; d++)
        {            
          for(int c=0; c<100000000; c++)
            {
               int a = 0;
               a++;
            }
        }
       */

      GEN_XSLEEP.Seconds(1);

    }

  tests->console->GetChar();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_AppAlerts(TESTS* tests)
* @brief      Test_AppAlerts
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:30
*
* @param[in]  tests : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_AppAlerts(TESTS* tests)
{
  int status[APP_ALERT_TYPE_MAX];

  if(GEN_APPALERTS.Ini(&APP_CFG.GetInstance() , APPLICATION_NAMEAPP 
                                              , APPLICATION_VERSION
                                              , APPLICATION_SUBVERSION
                                              , APPLICATION_SUBVERSIONERR
                                              , status
                                              , NULL))
    {
      int result = GEN_APPALERTS.Send((DIOALERTSSENDER_SMPT | DIOALERTSSENDER_WEB), DIOALERTS_CONDITIONS_ID_GENINTERN_TEST,  DIOALERTLEVEL_SERIOUS, __L("Aterta TEST"), __L("Esto es una prueba de Alerta."));

      result = GEN_APPALERTS.Send((DIOALERTSSENDER_SMPT | DIOALERTSSENDER_WEB), DIOALERTS_CONDITIONS_ID_GENINTERN_TEST,  DIOALERTLEVEL_SERIOUS, __L("Aterta TEST"), __L("Esto es una prueba de Alerta 2."));
  
      GEN_APPALERTS.End();
    }

  GEN_APPALERTS.DelInstance();

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_BluetoothEnum(TESTS* tests)
* @brief      Test_BluetoothEnum
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:30
*
* @param[in]  tests : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_BluetoothEnum(TESTS* tests)
{
  DIOSTREAMENUMDEVICES* enumdevicesremote = NULL;

  enumdevicesremote = GEN_DIOFACTORY.CreateStreamEnumDevices(DIOSTREAMENUMTYPE_BLUETOOTH_REMOTE);
	if(enumdevicesremote)
	  {					
      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Start Search sensors ... ")); 

      XTIMER*  xtimer;

      xtimer = GEN_XFACTORY.CreateTimer();

		  enumdevicesremote->Search();

		  xtimer->Reset();

			while(enumdevicesremote->IsSearching())
        {
          if(tests->console->KBHit()) break;          
				  XSLEEP::GetInstance().MilliSeconds(10);          
				}
					
			for(int c=0;c<(int)enumdevicesremote->GetDevices()->GetSize();c++)
			  {					
				  DIOSTREAMDEVICEBLUETOOTH* devicesearch = (DIOSTREAMDEVICEBLUETOOTH*)enumdevicesremote->GetDevices()->Get(c);
					if(devicesearch) 
						{	
              XSTRING MACstring; 

              devicesearch->GetMAC()->GetXString(MACstring);

              XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("  Sensor [MAC %s] %s"), MACstring.Get(), devicesearch->GetName()->Get()); 
            }
        }

       XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("End Search sensors ... ")); 

      GEN_XFACTORY.DeleteTimer(xtimer);
    }

  GEN_DIOFACTORY.DeleteStreamEnumDevices(enumdevicesremote);			

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_BluetoothLEEnum(TESTS* tests)
* @brief      Test_BluetoothLEEnum
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:30
*
* @param[in]  tests : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_BluetoothLEEnum(TESTS* tests)
{
  DIOSTREAMENUMDEVICES* enumdevicesremote = NULL;

  enumdevicesremote = GEN_DIOFACTORY.CreateStreamEnumDevices(DIOSTREAMENUMTYPE_BLUETOOTHLE_REMOTE);
	if(enumdevicesremote)
	  {					
      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Start Search sensors ... ")); 

      XTIMER*  xtimer;

      xtimer = GEN_XFACTORY.CreateTimer();

		  enumdevicesremote->Search();

		  xtimer->Reset();

			while(enumdevicesremote->IsSearching())
        {
          if(tests->console->KBHit()) break;          
				  XSLEEP::GetInstance().MilliSeconds(10);          
				}
					
      enumdevicesremote->StopSearch(false);
   

			for(int c=0;c<(int)enumdevicesremote->GetDevices()->GetSize();c++)
			  {					
				  DIOSTREAMDEVICEBLUETOOTHLE* devicesearch = (DIOSTREAMDEVICEBLUETOOTHLE*)enumdevicesremote->GetDevices()->Get(c);
					if(devicesearch) 
						{	
              XSTRING   MACstring; 
              XTIMER*   lastscantimer = devicesearch->GetLastScanTimer();
              XSTRING   lastscanmeasurestring;

              lastscantimer->GetMeasureString(lastscanmeasurestring, false);  
              devicesearch->GetMAC()->GetXString(MACstring);
              
              XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("  Sensor [MAC %s] %d last scan: %s"), MACstring.Get(), devicesearch->GetRSSI(), lastscanmeasurestring.Get()); 
            }
        }

      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("End Search sensors ... ")); 

      GEN_XFACTORY.DeleteTimer(xtimer);
    }

  GEN_DIOFACTORY.DeleteStreamEnumDevices(enumdevicesremote);			

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_NTP_InternetServices(TESTS* tests)
* @brief      Test_NTP_InternetServices
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:30
*
* @param[in]  tests : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_NTP_InternetServices(TESTS* tests)
{
  XDATETIME*  datetime1;
  XDATETIME*  datetime2;
  XSTRING     datetimestr;
  bool        status      = false;

  if(!tests->appinternetservices) return false;

  while(!tests->console->KBHit())
    {
      int hours = 0;

      datetime1 = tests->appinternetservices->DateTime_GetActual();
      if(datetime1)
        {    
          datetime1->GetDateTimeToString(XDATETIME_FORMAT_STANDARD, datetimestr);
          XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Date Time SO  : %s"), datetimestr.Get()); 

          hours = datetime1->GetHours();

          status = true;
        }

      datetime2 = tests->appinternetservices->DateTime_GetUTC();
      if(datetime2)
        {    
          datetime2->GetDateTimeToStringUTC((XDATETIME_FORMAT_YMD | XDATETIME_FORMAT_ADDTIME | XDATETIME_FORMAT_TIMEWITHSECONDS | XDATETIME_FORMAT_ADDTIMEMILLISECONDS), datetimestr);
          XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Date Time UTC : %s"), datetimestr.Get());       

          if(hours == datetime2->GetHours())
            {
              break;
            }

          status = true;
        }

     GEN_XSLEEP.MilliSeconds(100);
    } 

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_Sound(TESTS* tests)
* @brief      Test_Sound
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:30
*
* @param[in]  tests : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_Sound(TESTS* tests)
{

  bool status = false;


  #ifdef SND_ACTIVE
  
  /*
  for(int c=0; c<100; c++)
   {
     if(!GEN_XSYSTEM.Sound_SetLevel(c)) return false;
      
     GEN_XSLEEP.Seconds(1);
   }

  GEN_SNDFACTORY.Beep(440, 1.5);
  GEN_SNDFACTORY.Beep(660, 0.5);

  status = true;
  */


  SNDELEMENT* soundhdl = NULL;
  XPATH       xpath;
  
  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_SOUNDS, xpath);
  xpath.Slash_Add();
  xpath.Add(__L("alarm.ogg"));
    
  soundhdl = GEN_SNDFACTORY.Element_Add(xpath);
  if(!soundhdl) return false;  

  SNDINSTANCE* sndinstance = GEN_SNDFACTORY.PlaySound(soundhdl);
  status = sndinstance?true:false;
  
  GEN_XSLEEP.MilliSeconds((int)(soundhdl->GetDuration()*1000));
  
  GEN_SNDFACTORY.Element_Del(soundhdl);
   

  #endif

  return status;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_ProcessManager(TESTS* tests)
* @brief      Test_ProcessManager
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:30
*
* @param[in]  tests : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_ProcessManager(TESTS* tests)
{
  XSTRING             command;
  XSTRING             params; 
  XSTRING             in;
  XSTRING             out;
//int                 returncode;
  XVECTOR<XPROCESS*>  applist;
  
  /*
  command = __L("/usr/bin/festival");
  params  = __L("--language spanish --tts");
  in      = __L("Hola radiola");
 
  bool status = GEN_XPROCESSMANAGER.ExecuteApplication(command.Get(), params.Get(), &in, NULL, &returncode);

  */

  /*
  command = __L("D:\\depen dencies\\net-tools\\bin\\snmpwalk");
  params  = __L("");
  
  bool status = GEN_XPROCESSMANAGER.ExecuteApplication(command.Get(), params.Get(), &in, &out, &returncode);


  XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("Exec: %s "), (status?__L("Ok"):__L("Error!")));
  */

  bool status = GEN_XPROCESSMANAGER.GetApplicationRunningList(applist);

  if(status)
    {

      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("-- Applications ------------------------------------------------------------------"));        
      for(XDWORD c=0; c<applist.GetSize(); c++)
        {
          XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("%04d    ID    : %d"), c, applist.Get(c)->GetID());        
          XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("        Path  : %s")   , applist.Get(c)->GetPath()->Get());        
          XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("        Name  : %s")   , applist.Get(c)->GetName()->Get());  
          if(!applist.Get(c)->GetWindowTitle()->IsEmpty())
            {
              XTRACE_PRINTCOLOR(XTRACE_COLOR_PURPLE, __L("        Title : [%s]")    , applist.Get(c)->GetWindowTitle()->Get());                     
            }
        }
    }
    
  applist.DeleteContents();
  applist.DeleteAll();

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_GetUserAndDomain(TESTS* tests)
* @brief      Test_GetUserAndDomain
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:30
*
* @param[in]  tests : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_GetUserAndDomain(TESTS* tests)
{
  bool status;

  XSTRING   user;
  XSTRING   domain;

  status = GEN_XSYSTEM.GetUserAndDomain(user, domain);
  
  tests->console->Printf(__L("     user [%s]  domain [%s] \n\n"), user.Get(), domain.Get());

  return status;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TEST::Test_I2C_GPIO_MCP2317()
* @brief      Test_I2C_GPIO_MCP2317
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:30
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_I2C_GPIO_MCP2317(TESTS* tests)
{	
	tests->console->PrintMessage(__L(" I2C Test START..."),1,true,true);	
		
	DIOI2CGPIOMCP2317* mcp2317 = new DIOI2CGPIOMCP2317;
	if(!mcp2317) return false;
	
	if(mcp2317->Ini(1, 0x23, 10))
		{
			tests->console->PrintMessage(__L(" Ini ..."),1,true,true);	
			
			mcp2317->Configure();

			XBYTE rvalue = 0;
		  XBYTE wvalue;

			while(!tests->console->KBHit())
				{																
					for(int d=0; d<2; d++)
						{	
							wvalue = (!d)?0x01:0x80;

							for(int c=0; c<8; c++)
								{					
									
									tests->console->Printf(__L("Inputs: "));
									if(mcp2317->ReadInputs(DIOI2CGPIOMCP2317PORT_A, rvalue)) 
													tests->console->Printf(__L("%02X     \r"), rvalue); 
									   else tests->console->Printf(__L("No read. \r"), rvalue); 
									

									mcp2317->WriteOutputs(DIOI2CGPIOMCP2317PORT_B, wvalue);
									
									if(!d) wvalue <<= 1; else wvalue >>= 1;

									XSLEEP::GetInstance().MilliSeconds(150);			

									if(tests->console->KBHit()) break;
								}
						}					
				}
					
			if(mcp2317->End())
				{
					tests->console->PrintMessage(__L(" End ..."),1,true,true);	
				}
		}

	delete mcp2317;
	
  return true;	
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_SPI_GPIO_MCP2317(TESTS* tests)
* @brief      Test_SPI_GPIO_MCP2317
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:30
*
* @param[in]  tests : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_SPI_GPIO_MCP2317(TESTS* tests)
{	
	tests->console->PrintMessage(__L(" SPI Test START..."),1,true,true);	
		
  /*
	DIOSPIGPIOMCP23S17* mcp23s17 = new DIOSPIGPIOMCP23S17();
	if(!mcp23s17) return false;
	
	if(mcp23s17->Ini(0, 10))
		{
			tests->console->PrintMessage(__L(" Ini ..."),1,true,true);	

      mcp23s17->Configure();
			   
			XBYTE rvalue = 0;
		  
			while(!tests->console->KBHit())
				{																					
          mcp23s17->Write_Register(DIOSPIGPIOMCP23S17_GPIOA, 0, 0xFF);
					XSLEEP::GetInstance().MilliSeconds(150);			

          mcp23s17->Write_Register(DIOSPIGPIOMCP23S17_GPIOA, 0, 0x00);
					XSLEEP::GetInstance().MilliSeconds(150);			

				  if(tests->console->KBHit()) break;
					
				}
					
			if(mcp23s17->End())
				{
					tests->console->PrintMessage(__L(" End ..."),1,true,true);	
				}
		}

	delete mcp23s17;
  */
	
  return true;	
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_WifiManagerMode(TESTS* tests)
* @brief      Test_WifiManagerMode
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:30
*
* @param[in]  tests : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_WifiManagerMode(TESTS* tests)
{
  DIOWIFIMANAGERMODE* wifimanagermode = NULL;
  bool                status          = false;

  wifimanagermode = GEN_DIOFACTORY.CreateWifiManagerMode();
  status = wifimanagermode?true:false;
  if(status) 
    {
      wifimanagermode->SetSelectNetInterface(__L("wlan0"));     
      wifimanagermode->SetModeType(DIOWIFIMANAGER_MODETYPE_LINUX_CLIENT_NM);
    }  

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Do Connexion ..."));
  status = wifimanagermode->SetMode_Client(__L("AIQ_m09888_09888"), NULL, false);   
  
  XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("Connexion status: %s"), status?__L("Ok"):__L("Error!"));

  //-------------------------------------------------------------------------
 /*
  XSTRING  _aim;
  DIOIP    _IP;
  XSTRING  _IPstring;

  _aim = __L("xtracebizintek.dyndns.org"); 
 
  GEN_DIODNSRESOLVED.ResolveURL(_aim.Get(), _IP);

  _IP.GetXString(_IPstring);

  tests->console->Printf(__L("\n url: %s IP: %s \n"), _aim.Get(), _IPstring.Get());
 

  //-------------------------------------------------------------------------

  APP_CFG.SetAutomaticDNSResolved();

  */

  for(int c=0; c<5; c++)
    {
      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Is Connected: %s"), (wifimanagermode->IsDisconnected()?__L("no"):__L("yes")));
      GEN_XSLEEP.Seconds(1);
    }

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Des-Connexion."));
  wifimanagermode->Disconnect();

  GEN_DIOFACTORY.DeleteWifiManagerMode(wifimanagermode);

  return status;
}





/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTS::Test_NotificationsManager(TESTS* tests)
* @brief      Test_NotificationsManager
* @ingroup    APPLICATION
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:30
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_NotificationsManager(TESTS* tests)
{
  DIONOTIFICATIONSMANAGER* notificationmanager = GEN_DIOFACTORY.CreateNotificationsManager();
  if(!notificationmanager) return false;

  XSTRING genericapp;
  genericapp.Format(__L("Infodesig.%s"), APPLICATION_NAMEFILE);

  notificationmanager->Ini(APPLICATION_NAMEAPP, genericapp.Get());
  
  XSTRING msg;
  XSTRING msgfinal;

  msg = __L("Esto es una prueba de mensaje");

  msgfinal = msg;

  DIONOTIFICATION notification;

  notification.Get_Title()->Set(APPLICATION_NAMEAPP);
  notification.Get_Message()->Set(msgfinal);

  notification.SetApplicationHandle(tests->GetApplicationHandle());
  notificationmanager->Do(notification);

  notificationmanager->End();
  GEN_DIOFACTORY.DeleteNotificationsManager(notificationmanager);
 
  return true;
} 




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTS::Test_ATCommandGSM(TESTS* tests)
* @brief      Test_ATCommandGSM
* @ingroup    APPLICATION
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:30
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_ATCommandGSM(TESTS* tests)
{				
  #define ATCOMMAND_PIN  __L("7266")

	tests->console->Printf(__L("\n Creando dispositivo... \n"), 1 , true, true);	

	DIOSTREAMUARTCONFIG* diostreamcfg = new DIOSTREAMUARTCONFIG();
	if(diostreamcfg)
    {
	    diostreamcfg->SetFromString(__L("/dev/ttyUSB2,115200,8,N,1,NONE"));

	    DIOSTREAMUART* diostream = (DIOSTREAMUART*)DIOFACTORY::GetInstance().CreateStreamIO(diostreamcfg);
	    if(diostream) 
        {
	        DIOATCMDGSM* dioatcmdgsm =  new DIOATCMDGSM(diostream);
	        if(dioatcmdgsm) 
            {					
	            tests->console->Printf(__L(" Comprobando dispositivo... \n"), 1 , true, true);	

	            if(dioatcmdgsm->Ini(15, true, true))
		            {																	
			            tests->console->Printf(__L(" Dispositivo comandos AT accesible... \n \n"), 1 , true, true);	
			
			            XSTRING   string;
			            XSTRING   value;
                  bool      isPINresulto = false;

			            for(int c=0;c<10;c++)
				            {
					            string.Empty();
							
					            switch(c)
						            {
							            case    0 : if(dioatcmdgsm->GetManufactured(value)==DIOATCMD_ERROR_NONE)					  string.Format(__L(" Fabricante            : %s"), value.Get());                           break;
							            case    1 : if(dioatcmdgsm->GetModel(value)==DIOATCMD_ERROR_NONE)									  string.Format(__L(" Modelo de terminal    : %s"), value.Get());                           break;											
							            case    2 : if(dioatcmdgsm->GetIMEI(value)==DIOATCMD_ERROR_NONE)								  	string.Format(__L(" IMEI                  : %s"), value.Get());                           break;
							            case    3 : if(dioatcmdgsm->GetVersion(value)==DIOATCMD_ERROR_NONE)								  string.Format(__L(" Version               : %s"), value.Get());                           break;	
														
                          case    4 : if(dioatcmdgsm->PIN_IsResolved(isPINresulto)==DIOATCMD_ERROR_NONE)      string.Format(__L(" SIM PIN resuelto      : %s"), isPINresulto?__L("Si"):__L("No"));       break;	 

                          case    5 : if(!isPINresulto)
                                        {
                                          //DIOATCMD_ERROR error;
                                          //error = dioatcmdgsm->PIN_Activate(ATCOMMAND_PIN, false);                                      
                                          //string.Format(__L(" SIM PIN desactivado   : %s [%s]"), ((error == DIOATCMD_ERROR_NONE)?__L("Si"):__L("No")), ATCOMMAND_PIN);     	                                                      

                                          bool isenter = false;
                                          if(dioatcmdgsm->PIN_Enter(ATCOMMAND_PIN, isenter)==DIOATCMD_ERROR_NONE) string.Format(__L(" SIM PIN introducido   : %s [%s]"), (isenter?__L("Si"):__L("No")), ATCOMMAND_PIN);     	                                                      
                                        }
                                      break;


							            case    6 : { int RSSI = 0;
													              int BER  = 0;
																			
  													            if(dioatcmdgsm->GetSignalQuality(RSSI,BER)==DIOATCMD_ERROR_NONE)		  string.Format(__L(" Calidad de senal      : (RSSI %d)  (BER %d)"), RSSI, BER);																																							
	  											            }
		  										            break;		

							            case    7 : { bool avaible;

			  										            if(dioatcmdgsm->IsAvailableServiceGSM(avaible)==DIOATCMD_ERROR_NONE)	string.Format(__L(" Disp. Servicios GSM   : %s") , avaible?__L("Si"):__L("No"));                           
				  								            }
					  							            break;

							            case    8 : if(dioatcmdgsm->GetIMSI(value)==DIOATCMD_ERROR_NONE)									  string.Format(__L(" IMSI                  : %s"), value.Get());   
						  						            break;													
																									

							            case    9 : { XBYTE support;
															
							  						            if(dioatcmdgsm->GetSMSSupport(support)==DIOATCMD_ERROR_NONE)				  string.Format(__L(" Soporte SMS           : servicio %d, destino %s, origen %s, broadcast %s")	, (support>>4)  
								  																																														  																																									            , support&DIOATCMDGSM_SMSSUPPORT_MOVILETERMINATED ? __L("Si"):__L("No")
									  																																														  																																								            , support&DIOATCMDGSM_SMSSUPPORT_MOVILEORIGINATED ? __L("Si"):__L("No")
										    																																														  																																							          , support&DIOATCMDGSM_SMSSUPPORT_BROADCAST			  ? __L("Si"):__L("No"));																				
												              }
												              break;	
													
							            case   10 : { XBYTE format;
													              XBYTE support;
																																						
													              if(dioatcmdgsm->GetSMSFormat(format,false) ==DIOATCMD_ERROR_NONE) 
														              {
															              if(dioatcmdgsm->GetSMSFormat(support,true)==DIOATCMD_ERROR_NONE) 
																              {
																	              XSTRING strformat;
																	              XSTRING strsupport;

																	              strformat = __L("desconocido");
																	              if(format == DIOATCMDGSM_SMSFORMAT_PDU)  strformat = __L("PDU");
																	              if(format == DIOATCMDGSM_SMSFORMAT_TXT)  strformat = __L("Texto");

																	              if(support&DIOATCMDGSM_SMSFORMAT_PDU)		 strsupport = __L("PDU");
																	              if(support&DIOATCMDGSM_SMSFORMAT_TXT)     
																		              {
																			              if(!strsupport.IsEmpty()) strsupport += __L(" + ");
																			              strsupport += __L("Texto");
																		              }


																	              string.Format(__L(" Formato de SMS        : %s  (valido %s)"), strformat.Get(), strsupport.Get());																																							
																              }
														              }
												              }
												              break;	

							            case   11 : if(dioatcmdgsm->GetSMSCenter(value)==DIOATCMD_ERROR_NONE)						string.Format(__L(" Centro de mensajes    : %s"), value.Get());        break;		
						            }
											
					            if(!string.IsEmpty()) 
                        { 
                          tests->console->Printf(string.Get());	
                          tests->console->Printf(__L("\n"));	
                        }
				            }												 
											
			            tests->console->Printf(__L(" Enviando mensaje      : "));	

			            if(dioatcmdgsm->SendSMS(__L("64xxxxxx"),__L("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ$%&/{}[]()\\*#@+-\"=;:.,_|")) == DIOATCMD_ERROR_NONE) 	 //  ¿?¡!																		
						             tests->console->Printf(__L("Ok.\n"));	
				            else tests->console->Printf(__L("Error!\n"));	
											 
																
			            dioatcmdgsm->End();

		            } else tests->console->Printf(__L(" Dispositivo de comandos AT NO accesible!\n"));	
									
	            delete dioatcmdgsm;
           }

          DIOFACTORY::GetInstance().DeleteStreamIO(diostream);
        }
			
      delete diostreamcfg;																					    
		}
								
	tests->console->Printf(__L("\n Terminada conexion AT.\n"), 1, true, true);	

	return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTS::Test_SNMP(TESTS* tests)
* @brief      Test_SNMP
* @ingroup    APPLICATION
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:30
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_SNMP(TESTS* tests)
{  
  XSTRING			string;		
  bool        status = false;

	DIOSNMP* snmp = new DIOSNMP();
	if(snmp)  
    {	
	    status = snmp->Open(__L("47.61.135.23"), DIOSNMP_DEFAULT_PORT, false);
	    if(status)	
		    {	        		
          DIOSNMP_XBER xberout;

          snmp->SetVersion(DIOSNMP_VERSION_V2c);  
																	
			    status = snmp->Get(DIOSNMP_OPERATION_GETNEXTREQUEST, __L("public"), __L("1.3.6.1.2.1"), xberout); 
	
			    snmp->Close();
        }

      delete snmp;
		}        	
	
  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTS::Test_XFileXML(TESTS* tests)
* @brief      Test_XFileXML
* @ingroup    APPLICATION
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:30
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_XFileXML(TESTS* tests)
{
  XPATH       xpath;
  XFILEXML    xml;
  bool        status = false;

  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpath);
  xpath.Slash_Add();
  xpath.Add(__L("example.xml"));

  if(xml.Open(xpath, true))
    {
      xml.ReadAndDecodeAllLines();

      XFILEXMLELEMENT* root           = xml.GetRoot();
      XFILEXMLELEMENT* nodewebservice = NULL;

      if(root)
        {
          for(int c=0; c<root->GetNElements(); c++)
            {
              nodewebservice = root->GetElement(c);
              if(nodewebservice)
                {
                
                }
            }
        }

      xml.Close();

      status = true;
    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTS::Test_XFileRIFF(TESTS* tests)
* @brief      Test_XFileRIFF
* @ingroup    APPLICATION
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:30
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_XFileRIFF(TESTS* tests)
{
  XFILERIFF xfileRIFF;  
  XPATH     xpath;

  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpath);
  xpath.Slash_Add();
  xpath.Add(__L("example.avi"));

  if(xfileRIFF.Open(xpath.Get()))
    {
      bool status = xfileRIFF.ReadAllLists();

      xfileRIFF.Close();
  }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTS::Test_DIOStreamUSBConnection(TESTS* tests)
* @brief      Test_DIOStreamUSBConnection
* @ingroup    APPLICATION
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:30
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_DIOStreamUSBConnection(TESTS* tests)
{
  if(!tests->console) return false;

  DIOSTREAMUSBLOCALENUMDEVICES* enumdevices;
	DIOSTREAMDEVICEUSB*						device       = NULL;
  DIOSTREAMUSBCONFIG            diostreamcfg;
  DIOSTREAM*                    diostream    = NULL;
  XDWORD												PID          = 0xDF11;
	XDWORD												VID          = 0x0483;
  bool                          found        = false;    
  bool                          status       = false;


  tests->console->Printf(__L("\n\nBuscando dispositivo USB...\n"));

  while(!found)
    {
      enumdevices = (DIOSTREAMUSBLOCALENUMDEVICES*)GEN_DIOFACTORY.CreateStreamEnumDevices(DIOSTREAMENUMTYPE_USB_LOCAL);
	    if(!enumdevices) return false;	

	    enumdevices->Search();
      
      while(enumdevices->IsSearching())
       {
         GEN_XSLEEP.MilliSeconds(100);
       }
	
	    for(int c=0;c<(int)enumdevices->GetDevices()->GetSize();c++)
		    {				
			    device = (DIOSTREAMDEVICEUSB*)enumdevices->GetDevices()->Get(c);
			    if(device) 
				    {									    
					    if((device->GetProductID() == PID) && (device->GetVendorID() == VID))						    
                {																				
                  found = true;  
							    break;

						    } else device = NULL;
				    }
		    }

      if(tests->console->KBHit()) break;
    }

  if(!device) return false;
  if(!found)  return false;

  diostreamcfg.SetMode(DIOSTREAMMODE_CLIENT);	
  diostreamcfg.GetResource()->Set(device->GetResource()->Get());
  
  tests->console->Printf(__L("\nConnectando con USB device [%s]"), device->GetLocation()->Get());

  diostream = (DIOSTREAM*)GEN_DIOFACTORY.CreateStreamIO(&diostreamcfg);
  if(diostream)
    {
      if(diostream->Open())
        {
          status = diostream->WaitToConnected(1);

          tests->console->Printf(__L("\r\nConexion USB estado: %s"), status?__L("Connected!"):__L("Error!"));

          while(diostream->GetConnectStatus()==DIOSTREAMSTATUS_CONNECTED)
            {
              /*                                                  
              tests->console->Printf    (__L("\r\n    Sending packet(%d)"), c++);

              diostream->WriteStr (__L("Hello Jello!\r\n"));
              diostream->WaitToFlushOutXBuffer();
              */
            }
      
          diostream->Close();

          status = true;
        }

      DIOFACTORY::GetInstance().DeleteStreamIO(diostream);
    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTS::Test_XFileDFU(TESTS* tests)
* @brief      Test_XFileDFU
* @ingroup    APPLICATION
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:30
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_XFileDFU(TESTS* tests)
{
  XFILEDFU  xfileDFU;  
  XPATH     xpath;

  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_FIRMWARE, xpath);
  xpath.Slash_Add();
  xpath.Add(__L("firmware.dfu"));

  if(xfileDFU.Open(xpath.Get()))
    {
      if(xfileDFU.ReadAll())
        {


        }

      xfileDFU.Close();
    }
  
  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTS::Test_SystemHostFile(TESTS* tests)
* @brief      Test_SystemHostFile
* @ingroup    APPLICATION
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:30
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_SystemHostFile(TESTS* tests)
{
  GEN_XSYSTEM.HostFile(true, __L("youtube.es"), __L("127.0.0.1"));

  GEN_XSYSTEM.HostFile(false, __L("youtube.es"), __L(""));

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTS::Test_SystemBatteryLevel(TESTS* tests)
* @brief      Test_SystemBatteryLevel
* @ingroup    
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:30
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_SystemBatteryLevel(TESTS* tests)
{
  bool    isincharge   = false;
  XBYTE   batterylevel = 0;
  bool    status;

  status = GEN_XSYSTEM.GetBatteryLevel(isincharge, batterylevel);  
  if(status)
    {
      tests->console->Printf(__L("\n   Is in charge  : %s.\n"), (isincharge?__L("yes"):__L("No")));	
      tests->console->Printf(__L("   Battery level : %d%%.\n"), batterylevel);	
    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTS::Test_LedNeoPixelWS2812B(TESTS* tests)
* @brief      Test_LedNeoPixelWS2812B
* @ingroup    
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:30
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_LedNeoPixelWS2812B(TESTS* tests)
{
 
  DIOLEDNEOPIXELWS2812B* ledneopixelws2812b = GEN_DIOFACTORY.CreateLedNeopixelWS2812B(); 
  if(!ledneopixelws2812b)  return false;

  
  // ledneopixelws2812b->SetDataGPIOEntryID(TESTS_GPIOENTRYID_LED_NEOPIXEL);                                             
   
   
  if(ledneopixelws2812b->Ini(8))
    {      
      for(int c=0; c<30; c++)
        {
          XBYTE data1[] = { 0xFF, 0xFF, 0xFF,  // White    
                            0xFF, 0x00, 0x00,  // Red
                            0x00, 0xFF, 0x00,  // Green   
                            0x00, 0x00, 0xFF,  // Blue                             
                                                    
                            0xFF, 0xFF, 0xFF,  
                            0xFF, 0x00, 0x00,
                            0x00, 0xFF, 0x00,
                            0x00, 0x00, 0xFF,                            
                                                      
                          };

          ledneopixelws2812b->SendData(data1, sizeof(data1));
          GEN_XSLEEP.Seconds(1);

          
          XBYTE data2[] = { 0x00, 0x10, 0x00, 
                            0x00, 0x20, 0x00, 
                            0x00, 0x30, 0x00, 
                            0x00, 0x80, 0x00, 
                            0x00, 0xA0, 0x00, 
                            0x00, 0xB0, 0x00, 
                            0x00, 0xC0, 0x00, 
                            0x00, 0xFF, 0x00, 
                          };

          ledneopixelws2812b->SendData(data2, sizeof(data2));
          GEN_XSLEEP.Seconds(1);
          
          
          
          XBYTE data3[] = { 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00,
                          };

          ledneopixelws2812b->SendData(data3, sizeof(data3));
          GEN_XSLEEP.Seconds(1);
          

        }

      ledneopixelws2812b->End();
    }
  

  GEN_DIOFACTORY.DeleteLedNeopixelWS2812B(ledneopixelws2812b);
  
  
  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTS::Test_DIOPCap(TESTS* tests)
* @brief      Test_DIOPCap
* @ingroup    APPLICATION
* 
* @author     Abraham J. Velez 
* @date       12/12/2021 18:05:56
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_DIOPCap(TESTS* tests)
{
	#ifdef DIOPCAP_ACTIVE

	DIOPCAP*						 diopcap					 = NULL; 
	DIOPCAPNETINTERFACE* netinterface			 = NULL;  
	int                  indexnetinterface = 7;

	diopcap = DIOFACTORY::GetInstance().CreatePCap();
  if(!diopcap)  return false;

	if(diopcap->Ini())
    { 
				tests->console->Printf(__L("Interfaces de red disponibles: \n\n"));
      for(int c=0; c<(int)diopcap->GetNetInterfaces()->GetSize(); c++)
        {
          netinterface = diopcap->GetNetInterface(c);
          if(netinterface) tests->console->Printf(__L("[%2d] %s, [%s]\n"), c, netinterface->GetName()->Get(), netinterface->GetDescription()->Get());						
				}

			tests->console->Printf(__L("\n"));

			if(indexnetinterface != -1) 
				{
					if(diopcap->Capture_Start(indexnetinterface, true, 100)) 
						{
							while(!tests->console->KBHit())
								{
									int nsize = diopcap->Frames_Get()->GetSize();

									for(int c=0;c<nsize;c++)
										{
											DIOPCAPFRAME* frame = diopcap->Frames_Get(c);
											if(!frame) break;

											if(tests->console->KBHit()) break;
									                                                                                                                                   
											DIOPCAPETHERNETHEADER ethernetheader;                                                                                                             
											if(frame->GetHeaderEthernet(ethernetheader)) 
												{                          
													tests->console->Printf(__L("MAC Source: %02X:%02X:%02X:%02X:%02X:%02X  MAC Target: %02X:%02X:%02X:%02X:%02X:%02X ") , ethernetheader.MACsource[0], ethernetheader.MACsource[1], ethernetheader.MACsource[2], ethernetheader.MACsource[3], ethernetheader.MACsource[4], ethernetheader.MACsource[5]
																          																																																	  , ethernetheader.MACtarget[0], ethernetheader.MACtarget[1], ethernetheader.MACtarget[2], ethernetheader.MACtarget[3], ethernetheader.MACtarget[4], ethernetheader.MACtarget[5]);

													switch(ethernetheader.type)
														{
															case DIOPCAPETHERNETTYPE_IP			: {	DIOPCAPIPHEADER ipheader;																															
																																	if(frame->GetHeaderIP(ipheader))
																																		{ 
																																			DIOIP			ipsourceaddr;
																																			XSTRING		ipsourcestring;
																																			DIOIP			iptargetaddr;
																																			XSTRING   iptargetstring;
																																																																			
																																			ipsourceaddr.Set(ipheader.sourceaddr.byte1, ipheader.sourceaddr.byte2, ipheader.sourceaddr.byte3, ipheader.sourceaddr.byte4);
																																			iptargetaddr.Set(ipheader.targetaddr.byte1, ipheader.targetaddr.byte2, ipheader.targetaddr.byte3, ipheader.targetaddr.byte4);

																																			ipsourceaddr.GetXString(ipsourcestring);
																																			iptargetaddr.GetXString(iptargetstring);	

																																		  tests->console->Printf(__L("IP Source: %s IP Target: %s"), ipsourcestring.Get(), iptargetstring.Get());

																																		}
																																} 																																																															
																																break;

																										default		:	break;
														}	

												  tests->console->Printf(__L("\n"));

												}
									
											diopcap->Frames_Delete(c);
										}
								
								}
							
							diopcap->Capture_End();
						}
			
				}	 
			
			diopcap->End();														
		}

	DIOFACTORY::GetInstance().DeletePCap(diopcap);

	#endif
  
	return true;
}




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTS::Test_XProperty(TESTS* tests)
* @brief      Test_XProperty
* @ingroup    APPLICATION
* 
* @author     Abraham J. Velez 
* @date       28/02/2022 8:49:00
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_XProperty(TESTS* tests)
{
  TESTS_PROPERTY    foo = { 10.0f, 10.0f };
  TESTS_PROPERTY2   foo2(foo);

  foo.x  = foo.z;
  foo    = foo2.data;

  foo2.data2 = foo;
 
  double x = -(foo2.Get().x);
  std::cout << x << "\n";

  //double y = foo2.data. 
  //std::cout << y << "\n";


  return true;
}






#ifdef WINDOWS
/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_WindowsACL(TESTS* tests)
* @brief      Test_WindowsACL
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param[in]  tests :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_WindowsACL(TESTS* tests)
{
  XWINDOWSACCESSCONTROLLISTS  ACList;
  XPATH                       xpathsection;
  XPATH                       namefile;
  bool                        status = true;

  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathsection);
  namefile.Create(3 , xpathsection.Get(), __L("scraperweb"), __L(".xml"));

  status = ACList.SetFileOnlyPermissionForSystemUser(namefile.Get());

  GEN_XSLEEP.Seconds(2);

  status = ACList.SetFilePermissionForEveryone(namefile.Get());

  return status;
}

#endif



#ifdef LINUX
/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_DBUS(TESTS* tests)
* @brief      Test_DBUS
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:30
*
* @param[in]  tests : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_DBUS(TESTS* tests)
{
  DIOLINUXDBUS_MESSAGE  message;  
  DIOLINUXDBUS_MESSAGE  reply;  
  bool                  status = false;

  DIOLINUXDBUS* dbus = new DIOLINUXDBUS();
  if(dbus)
    {
      if(dbus->Ini())
        {        
          //---------------------------------------------------------------------------------

          /*    
          message.GetDestination()->Set(__L("org.freedesktop.NetworkManager"));
          message.GetPath()->Set(__L("/org/freedesktop/NetworkManager"));
          message.GetIFace()->Set(__L("org.freedesktop.NetworkManager.Devices"));
          message.GetMethod()->Set(__L("GetAll"));
          status = message.Create();
          if(status)
            {              
              message.SetArgument(true);

              message.SetArgument(DIOLINUXDBUS_IFACE_PROPERTIES);
              message.SetArgument(DIOLINUXDBUS_IFACE_PROPERTIES);

              status = dbus->CallMethod(message, reply);                       
              if(status)
                {

                  reply.Delete();
                }   

               message.Delete();
            }
           else 
            {
              XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[DBUS] Error create message ..."));
            }

          */

          //---------------------------------------------------------------------------------
          
          message.GetDestination()->Set(__L("org.freedesktop.NetworkManager"));
          message.GetPath()->Set(__L("/org/freedesktop/NetworkManager"));
          message.GetIFace()->Set(__L("org.freedesktop.NetworkManager"));
          message.GetMethod()->Set(__L("GetDevices"));

          status = message.Create();
          if(status)
            {              
              status = dbus->CallMethod(message, reply);                       
              if(status)
                { 
                  XVECTOR<XSTRING*> result;            

                  status = reply.GetResult(result);
                  if(status)
                    {
                      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("[DBUS] Result:"));
                      for(int c=0; c<result.GetSize(); c++)
                        {
                          XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("%s"), result.Get(c)->Get());
                        }

                      result.DeleteContents();
                      result.DeleteAll();
                    }
                   else
                    {
                      XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[DBUS] Error get result ..."));    
                    } 
                  
                  reply.Delete();
                }   

               message.Delete();
            }  
           else 
            {
              XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[DBUS] Error create message ..."));
            }
          

          //---------------------------------------------------------------------------------


          status = dbus->End();      
        }
 
      delete dbus;
    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTS::Test_NetWorkManager(TESTS* tests)
* @brief      Test_NetWorkManager
* @ingroup    
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:30
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_NetWorkManager(TESTS* tests)
{
  DIOLINUXNETWORKMANAGER networkmanager;
  
  if(networkmanager.Ini()) 
    {

      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Network Manager ] Activate ..."));    
      networkmanager.Enable(true);

      //networkmanager.Signal_Add(DIOLINUXNETWORKMANAGER_DEFAULT_DBUS_IFACE_MAIN  , __L("DeviceAdded"));
      //networkmanager.Signal_Add(DIOLINUXNETWORKMANAGER_DEFAULT_DBUS_IFACE_MAIN  , __L("DeviceRemoved"));
      networkmanager.Signal_Add(DIOLINUXNETWORKMANAGER_DEFAULT_DBUS_IFACE_MAIN  , __L("PropertiesChanged"));

      //networkmanager.Signal_Add(DIOLINUXNETWORKMANAGER_DEFAULT_DBUS_IFACE_DEVICE, __L("PropertiesChanged"));
  

      switch(networkmanager.GetConnectionState())
        {
          case DIOLINUXNETWORKMANAGER_STATE_UNKNOWN            :   XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Network Manager] Get Connection state: networking state is unknown"));                            break;
          case DIOLINUXNETWORKMANAGER_STATE_ASLEEP             :   XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Network Manager] Get Connection state: networking is not enabled"));                              break; 
          case DIOLINUXNETWORKMANAGER_STATE_DISCONNECTED       :   XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Network Manager] Get Connection state: there is no active network connection"));                  break;
          case DIOLINUXNETWORKMANAGER_STATE_DISCONNECTING      :   XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Network Manager] Get Connection state: network connections are being cleaned up"));               break;
          case DIOLINUXNETWORKMANAGER_STATE_CONNECTING         :   XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Network Manager] Get Connection state: a network connection is being started"));                  break;
          case DIOLINUXNETWORKMANAGER_STATE_CONNECTED_LOCAL    :   XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Network Manager] Get Connection state: there is only local IPv4 and/or IPv6 connectivity"));      break;
          case DIOLINUXNETWORKMANAGER_STATE_CONNECTED_SITE     :   XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Network Manager] Get Connection state: there is only site-wide IPv4 and/or IPv6 connectivity"));  break;
          case DIOLINUXNETWORKMANAGER_STATE_CONNECTED_GLOBAL   :   XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Network Manager] Get Connection state: there is global IPv4 and/or IPv6 Internet connectivity")); break;
        }

      XVECTOR<DIOSTREAMDEVICEIP*> devices;

      networkmanager.GetDevices(devices);

      for(XDWORD c=0; c<devices.GetSize(); c++)
        {
          DIOSTREAMDEVICEIP* deviceIP = devices.Get(c);
          if(deviceIP) deviceIP->DebugPrintInfo();
        }

      devices.DeleteContents();
      devices.DeleteAll();
       
      while(!tests->console->KBHit())
				{				
          GEN_XSLEEP.MilliSeconds(100);              
        }

      networkmanager.End();
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTS::Test_DeviceBusInputFile(TESTS* tests)
* @brief      Test_DeviceBusInputFile
* @ingroup    APPLICATION
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:30
* 
* @param[in]  tests : 
* 
* @return     static : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_DeviceBusInputFile(TESTS* tests)
{
  INPDEVICE_TYPE             typedevice = INPDEVICE_TYPE_TOUCHSCREEN; 
  XVECTOR<INPLINUXDEVICEID*> devices;
  bool                       status     = false;
   
  /* 
  XFILETXT* xfiletxtdevices =  new XFILETXT();
  if(xfiletxtdevices)
    {
      XPATH xpathdevices;
      
      #ifdef LINUX
      xpathdevices = INPLINUXDEVICEID_HANDLEFILE;
      #else
      GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathdevices);
      xpathdevices.Slash_Add();
      xpathdevices.Add(__L("devices"));      
      #endif
      
      if(xfiletxtdevices->Open(xpathdevices))
        {
          xfiletxtdevices->ReadAllFile();

          for(int c=0; c<xfiletxtdevices->GetNLines(); c++)
            {
              XSTRING* line = xfiletxtdevices->GetLine(c);
              if(line)
                {
                  int index = line->Find(__L("I:"), true);
                  if(index == 0)
                    {
                      INPLINUXDEVICEID* deviceID = new INPLINUXDEVICEID();
                      if(deviceID)
                        {
                          do{ line = xfiletxtdevices->GetLine(c);
                              if(!line) break;
                              if(line->GetSize() < 2) break;  

                              char typeline = (char)line->Get()[0];  
                              switch(typeline)
                                {    
                                  case  'I' : break;                                    

                                  case  'N' : { XSTRING name;

                                                name.AdjustSize(_MAXSTR);
                                                line->UnFormat(__L("N: Name=\"%s\""), name.Get());
                                                name.AdjustSize();      

                                                deviceID->GetName()->Set(name);
                                              }
                                              break;                                    

                                  case  'P' : break;                                    
                                  case  'S' : break;                                    
                                  case  'U' : break;                                    

                                  case  'H' : { XSTRING handlers;
                                                int     event_index = INPLINUXDEVICEID_INVALID;

                                                handlers.AdjustSize(_MAXSTR);
                                                line->UnFormat(__L("H: Handlers=%s"), handlers.Get());
                                                handlers.AdjustSize();      

                                                index = handlers.Find(__L("event"), true);
                                                if(index != XSTRING_NOTFOUND)
                                                  {
                                                    XSTRING eventstr;

                                                    handlers.Copy(index, eventstr);
                                                    eventstr.UnFormat(__L("event%d"), &event_index);

                                                    deviceID->SetEventIndex(event_index);
                                                  }                                                
                                              }
                                              break;        
                           
                                  case  'B' : { XCHAR* prefix[] = { __L("PROP=")  , 
                                                                    __L("EV=")    ,
                                                                    __L("KEY=")   ,
                                                                    __L("ABS=")   ,
                                                                    __L("REL=")   ,
                                                                    __L("MSC=")   
                                                                  };

                                                for(int d=0; d< (sizeof(prefix) / sizeof(XCHAR*)); d++)   
                                                  {
                                                    index = line->Find(prefix[d], true);
                                                    if(index != XSTRING_NOTFOUND)
                                                      {
                                                        switch(d)
                                                          {
                                                            case 0  : break;

                                                            case 1  : { XSTRING ev_str;

                                                                        ev_str.AdjustSize(_MAXSTR);
                                                                        line->Copy(index+3, ev_str);
                                                                        ev_str.AdjustSize();

                                                                        if(!ev_str.Compare(__L("120013"), true)) deviceID->SetType(INPDEVICE_TYPE_KEYBOARD);  
                                                                        if(!ev_str.Compare(__L("17"), true))     deviceID->SetType(INPDEVICE_TYPE_MOUSE);                                                                                                                        
                                                                        if(!ev_str.Compare(__L("b"), true))      deviceID->SetType(INPDEVICE_TYPE_TOUCHSCREEN);                                                                                                                        
                                                                      }
                                                                      break;

                                                            case 2  : break;
                                                            case 3  : break;
                                                            case 4  : break;
                                                            case 5  : break;
                                                          }
                                                      }
                                                  }  
                                              }
                                              break;                                                                      
                                }

                              c++;


                            } while(1);
 
                                
                          if((deviceID->GetEventIndex() != INPLINUXDEVICEID_INVALID) && 
                             (typedevice == deviceID->GetType()))
                            {            

                              devices.Add(deviceID);
               
                              #ifdef XTRACE_ACTIVE
                              XSTRING typestr;
   
                              switch(deviceID->GetType())
                                { 
                                                      default       :   
                                  case INPDEVICE_TYPE_NONE          : typestr = __L("Unkwown");       break;
                                  case INPDEVICE_TYPE_KEYBOARD      : typestr = __L("Keyboard");      break;
                                  case INPDEVICE_TYPE_MOUSE         : typestr = __L("Mouse");         break;
                                  case INPDEVICE_TYPE_JOSTICK       : typestr = __L("Jostick");       break;
                                  case INPDEVICE_TYPE_TOUCHSCREEN   : typestr = __L("TouchScreen");   break;
                                  case INPDEVICE_TYPE_WIIMOTE       : typestr = __L("WII Mote");      break;
                                }

                              XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Input Device] Event [%d] Type: %15s Device [%s]"), deviceID->GetEventIndex(), typestr.Get(), deviceID->GetName()->Get());                         
                              #endif                                               
                            } 
                           else delete deviceID;                                 
                        }   
                    }
                }
            }

          xfiletxtdevices->Close();
        }

      delete xfiletxtdevices;
    }

  */

  devices.DeleteContents();
  devices.DeleteAll();

  return status;
}

#endif


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS::Test_Hash(HASH* HASH, XBUFFER& input, XCHAR* leyend)
* @brief      Test_Hash
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param[in]  HASH :
* @param[in]  input :
* @param[in]  leyend :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS::Test_Hash(HASH* HASH, XBUFFER& input, XCHAR* leyend)
{
  if(!HASH) return false;

  XSTRING result;

  HASH->Do(input);

  HASH->GetResultString(result);

  console->Printf(__L("%-12s : %s\n"), leyend, result.Get());

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void TESTS::HandleEvent_Scheduler(XSCHEDULER_XEVENT* event)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param[in]  event :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void TESTS::HandleEvent_Scheduler(XSCHEDULER_XEVENT* event)
{
  /*
  switch(event->GetTask()->GetID())
    {

    }
  */
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void TESTS::HandleEvent_WebClient(DIOWEBCLIENT_XEVENT* event)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param[in]  event :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void TESTS::HandleEvent_WebClient(DIOWEBCLIENT_XEVENT* event)
{
  XSTRING line;
  DIOURL  URLweb;

  if(event->GetURL()) URLweb = event->GetURL()->Get();

  switch(event->GetEventType())
    {
      case DIOWEBCLIENT_XEVENT_TYPE_OPENWEB         :
      case DIOWEBCLIENT_XEVENT_TYPE_WRITEHEADER     :
      case DIOWEBCLIENT_XEVENT_TYPE_SENDPOSTDATA    :
      case DIOWEBCLIENT_XEVENT_TYPE_HEADERERROR     :
      case DIOWEBCLIENT_XEVENT_TYPE_READHEADER      : { line.Format(__L("Inicializando descarga [%s]")  , URLweb.Get());

                                                        console->PrintMessage(line.Get() , 4, true, false);
                                                        console->EraseToEndLine(line.GetSize()+4);
                                                        console->PrintMessage(__L("\r"), 0, false, false);
                                                      }
                                                      break;

      case DIOWEBCLIENT_XEVENT_TYPE_READBODYBLOCK   : { line.Format(__L("Descargando [%s] -> %d Kb ")  , URLweb.Get(), (event->GetDownloadSize() / 1024));

                                                        if(event->GetContentLenght()) line.AddFormat(__L("(%3.2f%%) "), event->GetOperationPercent());

                                                        line.AddFormat(__L("[%d Mbps] "), event->GetMBPSSpeed());

                                                        console->PrintMessage(line.Get() , 4, true, false);
                                                        console->EraseToEndLine(line.GetSize()+4);
                                                        console->PrintMessage(__L("\r"), 0, false, false);
                                                      }
                                                      break;

      case DIOWEBCLIENT_XEVENT_TYPE_CLOSEWEB        : console->PrintMessage(__L(" "), 0, false, true);
                                                      break;
    }
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TESTS::HandleEvent
* @brief      Handle Events
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param[]    xevent : event send to control
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void TESTS::HandleEvent(XEVENT* xevent)
{
  if(!xevent) return;

  switch(xevent->GetEventFamily())
    {
      case XEVENT_TYPE_SCHEDULER       :  { XSCHEDULER_XEVENT* event = (XSCHEDULER_XEVENT*)xevent;
                                            if(!event) return;

                                            HandleEvent_Scheduler(event);
                                          }
                                          break;

      case XEVENT_TYPE_WEBCLIENT       :  { DIOWEBCLIENT_XEVENT* event = (DIOWEBCLIENT_XEVENT*)xevent;
                                            if(!event) return;

                                            HandleEvent_WebClient(event);
                                          }
                                          break;
    }
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void TESTS::ThreadRunFunction(void* param)
* @brief      ThreadRunFunction
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param[in]  param :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void TESTS::ThreadRunFunction(void* param)
{
  //TESTS* test = (TESTS*)param;
  //if(!test) return;

  XDWORD indexthread = 0;

  memcpy(&indexthread, &param, sizeof(XDWORD));

  XTRACE_PRINTCOLOR(indexthread+1, __L("[%02d] Into Thread ...."), indexthread+1);

  GEN_XSLEEP.MilliSeconds(100);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void TESTS::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void TESTS::Clean()
{
  appcheckresourceshardware   = NULL;
  appinternetservices         = NULL;

  xtimerupdateconsole         = NULL;
  xmutexshowallstatus         = NULL;
}
