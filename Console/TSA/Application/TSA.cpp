/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       TSA.cpp
* 
* @class      TSA
* @brief      GEN TSA (Test Script Automatic) Example class
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

#include "TSA.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#include "Version.h"

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

#include "Script_Language_G.h"
#include "Script_Language_Lua.h"
#include "Script_Language_Javascript.h"

#include "TSA_CFG.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

APPLICATIONCREATEINSTANCE(TSA, scripts)

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TSA::TSA()
* @brief      Constructor
* @ingroup    EXAMPLES
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TSA::TSA() : XFSMACHINE(0)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TSA::~TSA()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    EXAMPLES
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TSA::~TSA()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TSA::InitFSMachine()
* @brief      InitFSMachine
* @ingroup    EXAMPLES
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool TSA::InitFSMachine()
{
  if(!AddState( TSA_XFSMSTATE_NONE            ,
                TSA_XFSMEVENT_INI             , TSA_XFSMSTATE_INI           ,
                TSA_XFSMEVENT_END             , TSA_XFSMSTATE_END           ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( TSA_XFSMSTATE_INI             ,
                TSA_XFSMEVENT_UPDATE          , TSA_XFSMSTATE_UPDATE        ,                
                TSA_XFSMEVENT_END             , TSA_XFSMSTATE_END           ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( TSA_XFSMSTATE_UPDATE          ,               
                TSA_XFSMEVENT_END             , TSA_XFSMSTATE_END           ,                 
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( TSA_XFSMSTATE_END             ,
                TSA_XFSMEVENT_NONE            , TSA_XFSMSTATE_NONE          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TSA::AppProc_Ini()
* @brief      AppProc_Ini
* @ingroup    EXAMPLES
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool TSA::AppProc_Ini()
{
  XSTRING string;
  XSTRING stringresult;
  XPATH   xpathsection;
  XPATH   xpath;
  bool    status;

  GEN_SET_VERSION(APPLICATION_NAMEAPP, APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR, APPLICATION_OWNER, APPLICATION_YEAROFCREATION)
  GetApplicationName()->Set(APPLICATION_NAMEAPP);

  ACTIVATEXTHREADGROUP(XTHREADGROUPID_SCHEDULER);
  ACTIVATEXTHREADGROUP(XTHREADGROUPID_DIOSTREAM);

  XTRACE_SETAPPLICATIONNAME((*GetApplicationName()));
  XTRACE_SETAPPLICATIONVERSION(APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR);
  XTRACE_SETAPPLICATIONID(string);

  GEN_XPATHSMANAGER.AdjustRootPathDefault(APPDEFAULT_DIRECTORY_ROOT);
  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_SCRIPTS, APPDEFAULT_DIRECTORY_SCRIPTS);
  GEN_XPATHSMANAGER.CreateAllPathSectionOnDisk();

  InitFSMachine();

  xmutexshowallstatus = GEN_XFACTORY.Create_Mutex();
  if(!xmutexshowallstatus) return false;

  APP_CFG_SETAUTOMATICTRACETARGETS

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Application ROOT path: %s"),  GEN_XPATHSMANAGER.GetPathSection(XPATHSMANAGERSECTIONTYPE_ROOT)->xpath->Get());
    
  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathsection);
  xpath.Create(3 , xpathsection.Get(), APPLICATION_NAMEFILE, XTRANSLATION_NAMEFILEEXT);

  if(!GEN_XTRANSLATION.Ini(xpath))
    {
      return false;
    }
    
  GEN_XTRANSLATION.SetActual(XLANGUAGE_ISO_639_3_CODE_SPA);

  Show_Header(true);

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

      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("%s"),  GEN_VERSION.GetAppVersion()->Get());   
      XTRACE_PRINTSTATUS(__L("S.O. version"), SO_ID.Get()); 

      stringresult.Format((status)?__L("Ok."):__L("ERROR!"));
      APP_LOG_ENTRY(((status)?XLOGLEVEL_INFO:XLOGLEVEL_ERROR), APP_CFG_LOG_SECTIONID_INITIATION, false, __L("%s: %s") , string.Get(), stringresult.Get());
           
      APP_LOG_ENTRY(((status)?XLOGLEVEL_INFO:XLOGLEVEL_ERROR), APP_CFG_LOG_SECTIONID_INITIATION, false,  __L("Identificacion SO: %s"), SO_ID.Get());

      XDWORD total = 0;
      XDWORD free  = 0;

      GEN_XSYSTEM.GetMemoryInfo(total,free);

      APP_LOG_ENTRY(XLOGLEVEL_INFO, APP_CFG_LOG_SECTIONID_INITIATION, false, XT_L(XTRANSLATION_GEN_ID_APPLOG_TOTALMEMORY), total, free, GEN_XSYSTEM.GetFreeMemoryPercent());
    }

  SetEvent(TSA_XFSMEVENT_INI);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TSA::AppProc_FirstUpdate()
* @brief      AppProc_FirstUpdate
* @ingroup    EXAMPLES
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool TSA::AppProc_FirstUpdate()
{
  xtimerupdateconsole = GEN_XFACTORY.CreateTimer();
  if(!xtimerupdateconsole) return false;

  xtimerscriptrun = GEN_XFACTORY.CreateTimer();
  if(!xtimerscriptrun) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TSA::AppProc_Update()
* @brief      AppProc_Update
* @ingroup    EXAMPLES
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool TSA::AppProc_Update()
{
  if(GetEvent()==TSA_XFSMEVENT_NONE) 
    {
      switch(GetCurrentState())
        {
          case TSA_XFSMSTATE_NONE       : break;

          case TSA_XFSMSTATE_INI        : break;

          case TSA_XFSMSTATE_UPDATE     : if(GetExitType() == APPBASE_EXITTYPE_UNKNOWN)
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

          case TSA_XFSMSTATE_END        : break;

        }
    }
   else 
    {
      if(GetEvent()<TSA_LASTEVENT)
        {
          CheckTransition();

          switch(GetCurrentState())
            {
              case TSA_XFSMSTATE_NONE   : break;

              case TSA_XFSMSTATE_INI    : if(!CreateScripToExec())
                                                {
                                                  SetExitType(APPBASE_EXITTYPE_BY_SERIOUSERROR);
                                                }

                                              SetEvent(TSA_XFSMEVENT_UPDATE);
                                              break;

              case TSA_XFSMSTATE_UPDATE : break;

              case TSA_XFSMSTATE_END    : DeleteScripToExec();
                                              break;
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TSA::AppProc_End()
* @brief      AppProc_End
* @ingroup    EXAMPLES
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool TSA::AppProc_End()
{
  XSTRING string;
  XSTRING stringresult;

  SetEvent(TSA_XFSMEVENT_END);

  DeleteScripToExec();

  if(xmutexshowallstatus)
    {
      GEN_XFACTORY.Delete_Mutex(xmutexshowallstatus);
      xmutexshowallstatus = NULL;
    }

  if(xtimerscriptrun)
    {
      GEN_XFACTORY.DeleteTimer(xtimerscriptrun);
      xtimerscriptrun = NULL;
    }

  if(xtimerupdateconsole)
    {
      GEN_XFACTORY.DeleteTimer(xtimerupdateconsole);
      xtimerupdateconsole = NULL;
    }

  APP_LOG.DelInstance();

  APP_CFG.DelInstance();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TSA::KeyValidSecuences(int key)
* @brief      KeyValidSecuences
* @ingroup    EXAMPLES
* 
* @param[in]  key : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool TSA::KeyValidSecuences(int key)
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

      case 'R'  : { if(xtimerscriptrun) xtimerscriptrun->Reset();

                    if(script) script->Run();

                    XQWORD timereleapsed      =  xtimerscriptrun->GetMeasureMilliSeconds();
                    double timereleapsedfloat = ((double)timereleapsed/(double)1000);

                    XTRACE_PRINTCOLOR(1, __L("Run exec in %d milliseconds (%.2f seconds)."), (XDWORD)timereleapsed, timereleapsedfloat);
                  }
                  break;

      case 'L'  : CreateScripToExec();
                  break;


      case 'S'  : break;

    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TSA::CreateScripToExec()
* @brief      CreateScripToExec
* @ingroup    EXAMPLES
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool TSA::CreateScripToExec()
{
  DeleteScripToExec();

  XPATH   namefilescript;
  XPATH   xpath;

  if(GetExecParams())
    {
      XSTRING* param = (XSTRING*)GetExecParams()->Get(0);
      if(param) namefilescript = param->Get();
    }

  // namefilescript = __L("test.g");
  
  script = SCRIPT::Create(namefilescript.Get());  
  if(!script) 
    {
      return NULL;
    }

  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_SCRIPTS, xpath);
  xpath.Slash_Add();
  xpath += namefilescript;

  return script->Load(xpath);  
}
  


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TSA::DeleteScripToExec()
* @brief      DeleteScripToExec
* @ingroup    EXAMPLES
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool TSA::DeleteScripToExec()
{
  if(!script) return false;
  
  delete script;
  script = NULL;

  UnSubscribeEvent(SCRIPT_XEVENT_TYPE_ERROR, this);
  UnSubscribeEvent(SCRIPT_XEVENT_TYPE_BREAK, this);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TSA::Show_AppStatus()
* @brief      Show_AppStatus
* @ingroup    EXAMPLES
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool TSA::Show_AppStatus()
{
  XSTRING string;
  XSTRING string2;

  XDWORD  total;
  XDWORD  free;

  GEN_XSYSTEM.GetMemoryInfo(total,free);

  string  = __L("Memoria total");
  string2.Format(__L("%d Kb, libre %d Kb (el %d%%%%)"), total, free, GEN_XSYSTEM.GetFreeMemoryPercent());
  Show_Line(string, string2);

  XDATETIME* datetime = GEN_XFACTORY.CreateDateTime();
  if(datetime)
    {
      datetime->Read();

      string  = __L("Fecha ");
      datetime->GetDateTimeToString(XDATETIME_FORMAT_STANDARD | XDATETIME_FORMAT_TEXTMONTH | XDATETIME_FORMAT_ADDDAYOFWEEK, string2);
      Show_Line(string, string2);

      GEN_XFACTORY.DeleteDateTime(datetime);
    }

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
* @fn         bool TSA::Show_ScriptStatus()
* @brief      Show_ScriptStatus
* @ingroup    EXAMPLES
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool TSA::Show_ScriptStatus()
{
  XSTRING string;
  XSTRING string2;

  string  = __L("Script Status");
  string2.Format(__L("%s"), script->GetNameScript()->Get());

  Show_Line(string, string2);


  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TSA::Show_AllStatus()
* @brief      Show_AllStatus
* @ingroup    EXAMPLES
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool TSA::Show_AllStatus()
{
  console->Clear();

  if(xmutexshowallstatus) xmutexshowallstatus->Lock();

  if(Show_Header(false))  console->PrintMessage(__L(""),0, false, true);
  if(Show_AppStatus())    console->PrintMessage(__L(""),0, false, true);
  if(Show_ScriptStatus()) console->PrintMessage(__L(""),0, false, true);

  if(xmutexshowallstatus) xmutexshowallstatus->UnLock();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void TSA::HandleEvent_Script(SCRIPT_XEVENT* event)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    EXAMPLES
* 
* @param[in]  event : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void TSA::HandleEvent_Script(SCRIPT_XEVENT* event)
{
  switch(event->GetEventType())
    {
      case SCRIPT_XEVENT_TYPE_ERROR    : XTRACE_PRINTCOLOR(4,__L("Script ERROR [%d]: %s line %d -> \"%s\""), event->GetError(), event->GetErrorText()->Get(), event->GetNLine(), event->GetCurrentToken()->Get());
                                        break;

      case SCRIPT_XEVENT_TYPE_BREAK    : XTRACE_PRINTCOLOR(4,__L("Script BREAK: line %d -> \"%s\""), event->GetNLine(), event->GetCurrentToken()->Get());
                                        break;

    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void TSA::HandleEvent(XEVENT* xevent)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    EXAMPLES
* 
* @param[in]  xevent : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void TSA::HandleEvent(XEVENT* xevent)
{
  if(!xevent) return;

  switch(xevent->GetEventFamily())
    {
       case XEVENT_TYPE_SCRIPT     : { SCRIPT_XEVENT* event = (SCRIPT_XEVENT*)xevent;
                                      if(!event) return;

                                      HandleEvent_Script(event);
                                    }
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void TSA::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    EXAMPLES
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void TSA::Clean()
{
  xtimerupdateconsole         = NULL;
  xtimerscriptrun             = NULL;

  xmutexshowallstatus         = NULL;

  script                      = NULL;
}


#pragma endregion

