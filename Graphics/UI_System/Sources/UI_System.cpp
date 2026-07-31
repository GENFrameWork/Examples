/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_System.cpp
* 
* @class      UI_SYSTEM
* @brief      Graphics UI System Monitor Example class
* @ingroup    EXAMPLES
* 
* @copyright  EndoraSoft. All rights reserved.
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

#include "GEN_Defines.h"



/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "UI_System.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#include "VersionFrameWork.h"

#include "XPath.h"
#include "XDateTime.h"
#include "XTimer.h"
#include "XFactory.h"
#include "XDir.h"
#include "XString.h"
#include "XSystem.h"
#include "XLog.h"
#include "XConsole.h"
#include "XFileXML.h"
#include "XTranslation.h"
#include "XTranslation_GEN.h"
#include "XThread.h"
#include "XTrace.h"

#include "DIOFactory.h"
#include "DIOStreamDeviceIP.h"
#include "DIOStreamIPLocalEnumDevices.h"

#include "DIOCheckTCPIPConnections.h"
#include "DIOCheckInternetConnection.h"

#include "GRP2DCanvas.h"
#include "GRPScreenCFGChromes.h"
#include "GRPScreen.h"
#include "GRPViewPort.h"
#include "GRPXEvent.h"

#include "INPManager.h"

#include "UI_XEvent.h"
#include "UI_Manager.h"
#include "UI_Element.h"
#include "UI_Element_Text.h"
#include "UI_Element_Form.h"
#include "UI_Element_Button.h"
#include "UI_Element_ProgressBar.h"
#include "UI_Element_ProgressRadial.h"
#include "UI_Element_ProgressImage.h"
#include "UI_SkinCanvas.h"

#include "APPFlowLog.h"
#include "APPFlowExtended.h"

#include "UI_System_CFG.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"




/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

 APPLICATIONCREATEINSTANCE(UI_SYSTEM, canvas2d)



/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         UI_SYSTEM::UI_SYSTEM()
* @brief      Constructor.
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
UI_SYSTEM::UI_SYSTEM() :  XFSMACHINE(0)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         UI_SYSTEM::~UI_SYSTEM()
* @brief      Destructor.
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
UI_SYSTEM::~UI_SYSTEM()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::InitFSMachine()
* @brief      Initializes the finite state machine.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::InitFSMachine()
{
  if(!AddState( UI_SYSTEM_XFSMSTATE_NONE           ,
                UI_SYSTEM_XFSMEVENT_INI            , UI_SYSTEM_XFSMSTATE_INI          ,
                UI_SYSTEM_XFSMEVENT_END            , UI_SYSTEM_XFSMSTATE_END          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( UI_SYSTEM_XFSMSTATE_INI            ,
                UI_SYSTEM_XFSMEVENT_NONE           , UI_SYSTEM_XFSMSTATE_NONE         ,
                UI_SYSTEM_XFSMEVENT_END            , UI_SYSTEM_XFSMSTATE_END          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( UI_SYSTEM_XFSMSTATE_END            ,
                UI_SYSTEM_XFSMEVENT_NONE           , UI_SYSTEM_XFSMSTATE_NONE         ,
                UI_SYSTEM_XFSMEVENT_INI            , UI_SYSTEM_XFSMSTATE_INI          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::AppProc_Ini()
* @brief      Initializes the application process.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::AppProc_Ini()
{
  XSTRING string;
  XSTRING stringresult;
  bool    status = false;

  //-------------------------------------------------------------------------------------------------

  GEN_SET_VERSION(APPLICATION_NAMEAPP, APPLICATION_NAMEFILE, APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR, APPLICATION_OWNER, APPLICATION_YEAROFCREATION)

  Application_GetName()->Set(APPLICATION_NAMEAPP);

  SetInitOptions( APPFLOWGRAPHICS_INIOPTION_CREATEMAINSCREEN    |
                  APPFLOWGRAPHICS_INIOPTION_SHOWMAINSCREEN      |
                  APPFLOWGRAPHICS_INIOPTION_INPUT);

  //--------------------------------------------------------------------------------------------------

  XTRACE_SETAPPLICATIONNAME((*Application_GetName()));
  XTRACE_SETAPPLICATIONVERSION(APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR);
  XTRACE_SETAPPLICATIONID(string);

  //--------------------------------------------------------------------------------------------------

  GEN_XPATHSMANAGER.AdjustRootPathDefault(APPFLOW_DEFAULT_DIRECTORY_ROOT);

  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_GRAPHICS      , APPFLOW_DEFAULT_DIRECTORY_GRAPHICS);
  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_FONTS         , APPFLOW_DEFAULT_DIRECTORY_FONTS);
  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_UI_LAYOUTS    , APPFLOW_DEFAULT_DIRECTORY_UI_LAYOUTS);


  GEN_XPATHSMANAGER.CreateAllPathSectionOnDisk();

  //--------------------------------------------------------------------------------------------------

  InitFSMachine();

  //--------------------------------------------------------------------------------------

  xtimer = GEN_XFACTORY.CreateTimer();
  if(!xtimer) return false;

  xtimer->Reset();

  //--------------------------------------------------------------------------------------
  // NOTE: GEN does not currently expose the real Operating System boot uptime (there is no
  //       "GetSystemUpTime()" in XSYSTEM), so "xtimer" is used as the running clock for the
  //       "Tiempo de funcionamiento del sistema" card: it measures the time elapsed since this
  //       monitor application started. Swap it for a real OS uptime source (e.g. reading
  //       /proc/uptime on Linux) here and in HardwareInfo_UpdateUptime() when one is available.
  //--------------------------------------------------------------------------------------

  diocheckinternetconnection = GEN_NEW DIOCHECKINTERNETCONNECTION(5);

  //--------------------------------------------------------------------------------------

  currentsectionID               = UI_SYSTEM_SECTIONID_RESUMEN;
  lastupdatehardwareinfo_second  = 0;

  //--------------------------------------------------------------------------------------
  
  { XPATH xpath;
    
    GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpath);
    xpath.Slash_Add();
    xpath.Add(APPLICATION_NAMEFILE);
    xpath.Add(XTRANSLATION_NAMEFILEEXT);    

    if(!GEN_XTRANSLATION.Ini(xpath))
      {
        return false;
      }

    GEN_XTRANSLATION.SetActual(XLANGUAGE_ISO_639_3_CODE_SPA);
  }

  //--------------------------------------------------------------------------------------------------

  APPFLOW_CFG_SETAUTOMATICTRACETARGETS

  //--------------------------------------------------------------------------------------------------

  APPFLOW_EXTENDED.APPStart(&APPFLOW_CFG);

  //--------------------------------------------------------------------------------------------------

  SetEvent(UI_SYSTEM_XFSMEVENT_INI);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::AppProc_FirstUpdate()
* @brief      Executes the first application update.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::AppProc_FirstUpdate()
{
  //--------------------------------------------------------------------------------------

  INPDEVICE* inpdevice;

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_KEYBOARD);
  if(inpdevice)
    {
      button[UI_SYSTEM_BUTTON_ESC]      = inpdevice->GetButton(INPBUTTON_ID_ESCAPE);
      button[UI_SYSTEM_BUTTON_F5]       = inpdevice->GetButton(INPBUTTON_ID_F5);

      button[UI_SYSTEM_BUTTON_MOUSE]    = inpdevice->GetButton(INPBUTTON_ID_MOUSE_RIGHT);
    }

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_MOUSE);
  if(inpdevice)
    {
      button[UI_SYSTEM_BUTTON_MOUSE] = inpdevice->GetButton(INPBUTTON_ID_MOUSE_LEFT);
      cursor = inpdevice->GetCursor(0);
    }

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_TOUCHSCREEN);
  if(inpdevice)
    {     
      button[UI_SYSTEM_BUTTON_TOUCHSCREEN] = inpdevice->GetButton(INPBUTTON_ID_TOUCHSCREEN);     
      cursor = inpdevice->GetCursor(0);
    }

  //--------------------------------------------------------------------------------------

  if(!Ini_UserInterface(true)) return false;

  //--------------------------------------------------------------------------------------
  // First hardware info population, so the dashboard shows real values on the very first
  // rendered frame instead of waiting for the first UI_SYSTEM_HARDWAREINFO_UPDATEPERIOD_SECONDS
  // tick.
  //--------------------------------------------------------------------------------------

  UpdateHardwareInfo(true);

  //--------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::AppProc_Update()
* @brief      Executes the application update cycle.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::AppProc_Update()
{
  if(GetEvent()==UI_SYSTEM_XFSMEVENT_NONE) // Not GEN_NEW event
    {
      switch(GetCurrentState())
        {
          case UI_SYSTEM_XFSMSTATE_NONE      : break;

          case UI_SYSTEM_XFSMSTATE_INI       : UpdateInput();
                                                UpdateHardwareInfo(false);
                                                DrawFrame();
                                                GetMainScreen()->UpdateViewports();
                                                break;

          case UI_SYSTEM_XFSMSTATE_END       : break;

        }
    }
   else //  New event
    {
      if(GetEvent()<UI_SYSTEM_LASTEVENT)
        {
          CheckTransition();

          switch(GetCurrentState())
            {
              case UI_SYSTEM_XFSMSTATE_NONE  : break;

              case UI_SYSTEM_XFSMSTATE_INI   : break;

              case UI_SYSTEM_XFSMSTATE_END   : break;
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::AppProc_End()
* @brief      Ends the application process.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::AppProc_End()
{
  //--------------------------------------------------------------------------------------

  SetCurrentState(UI_SYSTEM_XFSMSTATE_END);

  //--------------------------------------------------------------------------------------
  
  Ini_UserInterface(false);

  //--------------------------------------------------------------------------------------

  if(diocheckinternetconnection)
    {
      GEN_DELETE diocheckinternetconnection;
      diocheckinternetconnection = NULL;
    }

  //--------------------------------------------------------------------------------------

  if(xtimer)
    {
      GEN_XFACTORY.DeleteTimer(xtimer);
      xtimer = NULL;
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
* @fn         bool UI_SYSTEM::UpdateInput()
* @brief      Updates the application input state.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::UpdateInput()
{
   int  height  = GetMainScreen()->GetHeight();

  if(cursor)    
    {  
      if(cursor->GetMotion()->IsReadyToTest(50))
        {
          cursor->GetMotion()->InvertYAxis(height);

          GEN_USERINTERFACE.SendEvent(UI_XEVENT_TYPE_INPUT_CURSOR_MOTION, cursor->GetMotion());

          cursor->GetMotion()->Reset();
        }
       else    
        {
          if(cursor->GetMotion()->GetNPoints() < 50)
            {         
              static int   cursor_x       = 0;
              static int   cursor_y       = 0;
              int          now_cursor_x   = (int)cursor->GetX();
              int          now_cursor_y   = (int)height - (int)cursor->GetY();
              bool         changed        = false;

              if(cursor_x != now_cursor_x)  
                { 
                  cursor_x = now_cursor_x;
                  changed  = true;
                }

              if(cursor_y != now_cursor_y)  
                {
                  cursor_y = now_cursor_y;          
                  changed  = true;
                }

              if(changed)
                {
                  GEN_USERINTERFACE.SendEvent(UI_XEVENT_TYPE_INPUT_CURSOR_MOVE,  cursor_x,  cursor_y);
                }

              if(button[UI_SYSTEM_BUTTON_MOUSE]->IsPressedWithRelease())
                {
                  GEN_USERINTERFACE.SendEvent(UI_XEVENT_TYPE_INPUT_SELECCTION,  cursor_x,  cursor_y);   

                  cursor->GetMotion()->Reset();       
                }
    
              if(button[UI_SYSTEM_BUTTON_TOUCHSCREEN])
                {             
                  if(button[UI_SYSTEM_BUTTON_TOUCHSCREEN]->IsPressed())
                    {             
                      GEN_USERINTERFACE.SendEvent(UI_XEVENT_TYPE_INPUT_CURSOR_MOVE,  cursor_x,  cursor_y);
                      GEN_USERINTERFACE.SendEvent(UI_XEVENT_TYPE_INPUT_SELECCTION,   cursor_x, cursor_y);          

                      cursor->GetMotion()->Reset();
                    }
                }
            }
        }
    }


  for(int c=0; c<UI_SYSTEM_BUTTON_MOUSE; c++)
    {
      if(button[c])
        {
          if(button[c]->IsPressedWithRelease())
            {
              switch(c)
                {
                  case UI_SYSTEM_BUTTON_F5    : Ini_UserInterface(false);
                                                Ini_UserInterface(true);
                                                UpdateHardwareInfo(true);
                                                break;

                  case UI_SYSTEM_BUTTON_ESC   : SetExitType(APPFLOWBASE_EXITTYPE_BY_USER);
                                                break;
                }
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::Ini_Graphics(GRPSCREEN* screen)
* @brief      Initializes the graphics subsystem.
* @ingroup    EXAMPLES
*
* @param[in]  screen : Screen where the graphics or user interface resources are created.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::Ini_Graphics(GRPSCREEN* screen)
{

  //--------------------------------------------------------------------------------------

  screen->SetWidth(1440);
  screen->SetHeight(900);

  screen->GetTitle()->Set(__L("Monitor del Sistema"));  
  screen->SetDesktopScreenSelected(GRPSCREENTYPE_DESKTOP_MAIN);

  //--------------------------------------------------------------------------------------

  UserInterface_CFGChromes(screen); 

  //--------------------------------------------------------------------------------------

  GetMainScreen()->CreateViewport(GRPVIEWPORT_ID_MAIN , 0.0f, 0.0f, (float)screen->GetWidth()   , (float)screen->GetHeight(), 0, 0, (screen->GetWidth()), (screen->GetHeight()));

  //--------------------------------------------------------------------------------------
                                          
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::Ini_UserInterface(bool on)
* @brief      Initializes or ends the user interface.
* @ingroup    EXAMPLES
*
* @param[in]  on : true to enable the operation; false to disable it.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::Ini_UserInterface(bool on)
{  
  if(!on)
    { 
      GEN_USERINTERFACE.SubscribeOutputEvents(false, this, &GEN_USERINTERFACE.GetInstance());
      GEN_USERINTERFACE.SubscribeInputEvents(false);
      GEN_USERINTERFACE.DelInstance();
   
      return true;
    }

  GRPSCREEN*    screen    = NULL;
  GRPVIEWPORT*  viewport  = NULL;
  GRP2DCANVAS*  canvas    = NULL;
  XPATH         xpath;
  
  screen = GetMainScreen();
  if(!screen)   
    {
      return false;
    } 

  viewport = screen->GetViewport(0);
  if(!viewport) 
    {
      return false;
    }

  canvas = viewport->GetCanvas();
  if(!canvas)   
    {
      return false;
    }
 
  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_UI_LAYOUTS, xpath);
  xpath.Slash_Add();
  xpath.Add(__L("ui_system/ui_system.xml"));
    
  if(!GEN_USERINTERFACE.Load(xpath, screen, 0)) 
    {
      return false;
    }

  GEN_USERINTERFACE.SubscribeInputEvents(true);
  GEN_USERINTERFACE.SubscribeOutputEvents(true, this, &GEN_USERINTERFACE.GetInstance());   

  GEN_USERINTERFACE.Layout_PutBackground();

  GEN_USERINTERFACE.Elements_SetToRedraw();

  //--------------------------------------------------------------------------------------
  // Reflect the currently selected sidebar section (survives a F5 layout reload).
  //--------------------------------------------------------------------------------------

  UserInterface_SelectSection(currentsectionID);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::DrawFrame()
* @brief      Draws the current frame.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::DrawFrame()
{
  GRPSCREEN*     screen    = NULL;
  GRPVIEWPORT*   viewport  = NULL;
  GRP2DCANVAS*   canvas    = NULL;

  screen = GetMainScreen();
  if(!screen) 
    {
      return false;  
    }

  viewport = screen->GetViewport(0);
  if(!viewport) 
    {
      return false;
    }

  canvas =  viewport->GetCanvas();
  if(!canvas) 
    {
      return false;
    }
 
  //--------------------------------------------------------------------------------------

  canvas->ReleaseDrawFramerate();  
 
  canvas->RebuildAllAreas();

  //--------------------------------------------------------------------------------------

  GEN_USERINTERFACE.Elements_RebuildDrawAreas();
  
  GEN_USERINTERFACE.Update(); 

  //--------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::UpdateHardwareInfo(bool forced)
* @brief      Polls the GEN hardware/system information sources and refreshes the dashboard.
* @ingroup    EXAMPLES
*
* @param[in]  forced : true to ignore the update period and refresh immediately.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::UpdateHardwareInfo(bool forced)
{
  if(!xtimer) return false;

  XQWORD actualsecond = xtimer->GetMeasureSeconds();

  if((!forced) && ((actualsecond - lastupdatehardwareinfo_second) < UI_SYSTEM_HARDWAREINFO_UPDATEPERIOD_SECONDS))
    {
      return true;
    }

  lastupdatehardwareinfo_second = actualsecond;

  //--------------------------------------------------------------------------------------

  HardwareInfo_UpdateCPU();
  HardwareInfo_UpdateMemory();
  HardwareInfo_UpdateDateTime();
  HardwareInfo_UpdateUptime();
  HardwareInfo_UpdateConnection();
  HardwareInfo_UpdateFooter();

  //--------------------------------------------------------------------------------------
  // A single global redraw is enough: it re-resolves every #[MASK] literal text in the
  // layout (via UserInterface_ChangeLiteralText / the automatic PROGRESSBAR_PERCENT mask)
  // and repaints the progress elements with the levels set above.
  //--------------------------------------------------------------------------------------

  GEN_USERINTERFACE.Elements_SetToRedraw();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::HardwareInfo_UpdateCPU()
* @brief      Reads CPU temperature and CPU usage from GEN_XSYSTEM and updates the related UI elements.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::HardwareInfo_UpdateCPU()
{
  //--------------------------------------------------------------------------------------
  // CPU Temperature. On several platforms GEN_XSYSTEM.GetCPUTemperature() is still a pending
  // stub (returns 0.0f), so if no real reading is available the value is left as a "--"
  // placeholder instead of showing a fake number.
  //--------------------------------------------------------------------------------------

  float cputemperature = GEN_XSYSTEM.GetCPUTemperature();
  float cputemperaturelevel = 0.0f;

  if(cputemperature > 0.0f)
    {
      cpu_temperature_str.Format(__L("%d\u00B0C"), (int)(cputemperature + 0.5f));

      cputemperaturelevel = cputemperature;
      if(cputemperaturelevel > 100.0f) cputemperaturelevel = 100.0f;
    }
   else
    {
      cpu_temperature_str.Set(__L("--"));            // TODO: wire a real CPU sensor (e.g. /sys/class/thermal) here
    }

  UI_ELEMENT_PROGRESS_IMAGE* element_temp = (UI_ELEMENT_PROGRESS_IMAGE*)GEN_USERINTERFACE.Element_Get(__L("cpu_temp_bar"), UI_ELEMENT_TYPE_PROGRESSIMAGE);
  if(element_temp) element_temp->SetLevel(cputemperaturelevel);

  //--------------------------------------------------------------------------------------
  // CPU Usage (total, real value read from the OS: /proc/stat on Linux, WMI on Windows, ...)
  //--------------------------------------------------------------------------------------

  int cpuusage = GEN_XSYSTEM.GetCPUUsageTotal();

  UI_ELEMENT_PROGRESS_RADIAL* element_cpu = (UI_ELEMENT_PROGRESS_RADIAL*)GEN_USERINTERFACE.Element_Get(__L("cpu_usage_radial"), UI_ELEMENT_TYPE_PROGRESSRADIAL);
  if(element_cpu) element_cpu->SetLevel((cpuusage != XSYSTEM_CPUUSAGE_ERROR) ? (float)cpuusage : 0.0f);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::HardwareInfo_UpdateMemory()
* @brief      Reads RAM usage from GEN_XSYSTEM and updates the related UI elements.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::HardwareInfo_UpdateMemory()
{
  XDWORD total        = 0;
  XDWORD free         = 0;
  float  usedpercent  = 0.0f;

  if(GEN_XSYSTEM.GetMemoryInfo(total, free) && total)
    {
      XDWORD used = total - free;

      double totalGB = (double)total / (1024.0 * 1024.0 * 1024.0);
      double usedGB  = (double)used  / (1024.0 * 1024.0 * 1024.0);

      ram_used_total_str.Format(__L("%.1f GB / %.1f GB"), usedGB, totalGB);

      usedpercent = (float)(((double)used / (double)total) * 100.0);
    }
   else
    {
      ram_used_total_str.Set(__L("-- GB / -- GB"));
    }

  UI_ELEMENT_PROGRESS_RADIAL* element_radial = (UI_ELEMENT_PROGRESS_RADIAL*)GEN_USERINTERFACE.Element_Get(__L("ram_usage_radial"), UI_ELEMENT_TYPE_PROGRESSRADIAL);
  if(element_radial) element_radial->SetLevel(usedpercent);

  UI_ELEMENT_PROGRESSBAR* element_bar = (UI_ELEMENT_PROGRESSBAR*)GEN_USERINTERFACE.Element_Get(__L("ram_linear_bar"), UI_ELEMENT_TYPE_PROGRESSBAR);
  if(element_bar) element_bar->SetLevel(usedpercent);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::HardwareInfo_UpdateDateTime()
* @brief      Reads the actual system date and time.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::HardwareInfo_UpdateDateTime()
{
  XDATETIME* xdatetime = GEN_XFACTORY.CreateDateTime();
  if(!xdatetime) return false;

  xdatetime->Read();

  system_date_str.Format(__L("%02d/%02d/%04d"), xdatetime->GetDay(),  xdatetime->GetMonth(),   xdatetime->GetYear());
  system_time_str.Format(__L("%02d:%02d:%02d"), xdatetime->GetHours(), xdatetime->GetMinutes(), xdatetime->GetSeconds());

  GEN_XFACTORY.DeleteDateTime(xdatetime);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::HardwareInfo_UpdateUptime()
* @brief      Builds the "Tiempo de funcionamiento del sistema" figures out of the elapsed apptimer.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::HardwareInfo_UpdateUptime()
{
  if(!xtimer) return false;

  XQWORD allseconds = xtimer->GetMeasureSeconds();

  XDWORD years   = XDATETIME_SECONDSYEARS(allseconds);
  XDWORD months  = XDATETIME_SECONDSMONTHS(allseconds);
  XDWORD hours   = (XDWORD)(allseconds / XDATETIME_SECONDSINHOUR);

  uptime_years_str.Format  (__L("%d"), years);
  uptime_months_str.Format (__L("%d"), months);
  uptime_hours_str.Format  (__L("%d"), hours);
  uptime_seconds_str.Format(__L("%d"), (XDWORD)allseconds);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::HardwareInfo_UpdateConnection()
* @brief      Checks the internet connection status, its latency and the local IP address.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::HardwareInfo_UpdateConnection()
{
  bool isconnected = false;

  if(diocheckinternetconnection)
    {
      isconnected = diocheckinternetconnection->Check();
    }

  if(isconnected)
    {
      connection_status_str.Set(__L("Conectado"));
      connection_quality_str.Set(__L("Conexi\u00F3n estable"));
      connection_mark_str.Set(__L("OK"));
    }
   else
    {
      connection_status_str.Set(__L("Desconectado"));
      connection_quality_str.Set(__L("Sin conexi\u00F3n"));
      connection_mark_str.Set(__L("--"));
    }

  UI_ELEMENT_FORM* element_badge = (UI_ELEMENT_FORM*)GEN_USERINTERFACE.Element_Get(__L("connection_status_badge"), UI_ELEMENT_TYPE_FORM);
  if(element_badge)
    {
      element_badge->GetColor()->SetFromString(isconnected ? __L("60,200,110,255") : __L("225,70,70,255"));
    }

  //--------------------------------------------------------------------------------------
  // Local IP (first active local network device: Ethernet/WiFi/PPP).
  //--------------------------------------------------------------------------------------

  DIOSTREAMIPLOCALENUMDEVICES* enumdevices = (DIOSTREAMIPLOCALENUMDEVICES*)GEN_DIOFACTORY.CreateStreamEnumDevices(DIOSTREAMENUMTYPE_IP_LOCAL);
  if(enumdevices)
    {
      DIOSTREAMDEVICEIP* device = (DIOSTREAMDEVICEIP*)enumdevices->GetFirstActiveDevice();
      if(device)
        {
          XSTRING ipstring;

          device->GetIP()->GetXString(ipstring);

          local_ip_str.Format(__L("IP: %s"), ipstring.Get());
        }
       else
        {
          local_ip_str.Set(__L("IP: --"));
        }

      GEN_DIOFACTORY.DeleteStreamEnumDevices(enumdevices);
    }
   else
    {
      local_ip_str.Set(__L("IP: --"));
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::HardwareInfo_UpdateFooter()
* @brief      Builds the status bar literals (equipment name, operative system and uptime summary).
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::HardwareInfo_UpdateFooter()
{
  //--------------------------------------------------------------------------------------
  // Equipment name: GEN does not expose the machine hostname on every platform (it is
  // intentionally left out of XSYSTEM::GetOperativeSystemID()), so GetUserAndDomain() is used
  // as a best-effort source and, if it is not available, the field is left as a placeholder.
  //--------------------------------------------------------------------------------------

  XSTRING user;
  XSTRING domain;

  if(GEN_XSYSTEM.GetUserAndDomain(user, domain) && (!domain.IsEmpty()))
    {
      footer_equipo_str.Format(__L("Equipo: %s"), domain.Get());
    }
   else
    {
      footer_equipo_str.Set(__L("Equipo: --"));           // TODO: add a real hostname source for this platform
    }

  //--------------------------------------------------------------------------------------

  XSTRING operativesystemID;

  if(GEN_XSYSTEM.GetOperativeSystemID(operativesystemID) && (!operativesystemID.IsEmpty()))
    {
      footer_so_str.Format(__L("SO: %s"), operativesystemID.Get());
    }
   else
    {
      footer_so_str.Set(__L("SO: --"));
    }

  //--------------------------------------------------------------------------------------

  if(xtimer)
    {
      XSTRING measure;

      xtimer->GetMeasureString(measure, true);

      if(!measure.IsEmpty())
            footer_uptime_str.Format(__L("Uptime del sistema: %s"), measure.Get());
       else footer_uptime_str.Set(__L("Uptime del sistema: 0 segundos"));
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::UserInterface_ElementSelected(UI_ELEMENT* element)
* @brief      Processes the selected user interface element.
* @ingroup    EXAMPLES
*
* @param[in]  element : User interface element to process.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::UserInterface_ElementSelected(UI_ELEMENT* element)
{
  if(!element) return false;


  switch(element->GetChromeRole())
    {
      case UI_ELEMENT_CHROMEROLE_ICON     : break;

      case UI_ELEMENT_CHROMEROLE_MINIMIZE : if(GetMainScreen()) GetMainScreen()->Minimize(true);
                                            break;

      case UI_ELEMENT_CHROMEROLE_MAXIMIZE : if(GetMainScreen()) GetMainScreen()->Maximize(true);
                                            break;

      case UI_ELEMENT_CHROMEROLE_CLOSE    : SetExitType(APPFLOWBASE_EXITTYPE_BY_USER);
                                            break;

      default                             : break;
    }


  XSTRING elementname;

  elementname = element->GetName()->Get();

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("UI Element [%s]: Selected! "), element->GetName()->Get());

  if(!elementname.Compare(__L("nav-resumen-btn")       , true)) UserInterface_SelectSection(UI_SYSTEM_SECTIONID_RESUMEN);
  if(!elementname.Compare(__L("nav-cpu-btn")           , true)) UserInterface_SelectSection(UI_SYSTEM_SECTIONID_CPU);
  if(!elementname.Compare(__L("nav-memoria-btn")       , true)) UserInterface_SelectSection(UI_SYSTEM_SECTIONID_MEMORIA);
  if(!elementname.Compare(__L("nav-red-btn")           , true)) UserInterface_SelectSection(UI_SYSTEM_SECTIONID_RED);
  if(!elementname.Compare(__L("nav-disco-btn")         , true)) UserInterface_SelectSection(UI_SYSTEM_SECTIONID_DISCO);
  if(!elementname.Compare(__L("nav-procesos-btn")      , true)) UserInterface_SelectSection(UI_SYSTEM_SECTIONID_PROCESOS);
  if(!elementname.Compare(__L("nav-alertas-btn")       , true)) UserInterface_SelectSection(UI_SYSTEM_SECTIONID_ALERTAS);
  if(!elementname.Compare(__L("nav-configuracion-btn") , true)) UserInterface_SelectSection(UI_SYSTEM_SECTIONID_CONFIGURACION);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::UserInterface_SelectSection(UI_SYSTEM_SECTIONID sectionID)
* @brief      Highlights the selected sidebar entry.
* @note       Only the "Resumen" section has real dashboard content for now (it is the section
*             shown in the reference mock-up); the remaining sections are already wired for
*             navigation and are left ready to receive their own content_xxx panel later.
* @ingroup    EXAMPLES
*
* @param[in]  sectionID : Section to select.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::UserInterface_SelectSection(UI_SYSTEM_SECTIONID sectionID)
{
  // NOTE: the active/inactive highlight is a separate flat "nav-xxx-hl" rounded rectangle
  // (declared before the sidebar buttons in the layout, so it is painted behind them) that is
  // simply shown/hidden, instead of recoloring the button itself: nesting plain content inside
  // a "form" turned out to not be positioned correctly by this GEN build, so every element with
  // visual meaning of its own is kept as a flat, top-level, absolutely positioned element.
  static XCHAR* navhlnames[UI_SYSTEM_SECTIONID_MAX]     = { __L("nav-resumen-hl")        ,
                                                             __L("nav-cpu-hl")            ,
                                                             __L("nav-memoria-hl")        ,
                                                             __L("nav-red-hl")            ,
                                                             __L("nav-disco-hl")          ,
                                                             __L("nav-procesos-hl")       ,
                                                             __L("nav-alertas-hl")        ,
                                                             __L("nav-configuracion-hl")   };

  static XCHAR* navtextnames[UI_SYSTEM_SECTIONID_MAX]   = { __L("nav-resumen-text")      ,
                                                             __L("nav-cpu-text")          ,
                                                             __L("nav-memoria-text")      ,
                                                             __L("nav-red-text")          ,
                                                             __L("nav-disco-text")        ,
                                                             __L("nav-procesos-text")     ,
                                                             __L("nav-alertas-text")      ,
                                                             __L("nav-configuracion-text") };

  for(int c=0; c<UI_SYSTEM_SECTIONID_MAX; c++)
    {
      bool isactive = (c == (int)sectionID);

      UI_ELEMENT_FORM* element_hl = (UI_ELEMENT_FORM*)GEN_USERINTERFACE.Element_Get(navhlnames[c], UI_ELEMENT_TYPE_FORM);
      if(element_hl) element_hl->SetVisible(isactive);

      UI_ELEMENT_TEXT* element_txt = (UI_ELEMENT_TEXT*)GEN_USERINTERFACE.Element_Get(navtextnames[c], UI_ELEMENT_TYPE_TEXT);
      if(element_txt) element_txt->GetColor()->SetFromString(isactive ? __L("228,232,238,255") : __L("146,156,171,255"));
    }

  currentsectionID = sectionID;

  GEN_USERINTERFACE.Elements_SetToRedraw();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::UserInterface_ChangeLiteralText(UI_ELEMENT_TEXT* element_text, XSTRING* maskvalue, XSTRING* maskresolved)
* @brief      Resolves a user interface literal text.
* @ingroup    EXAMPLES
*
* @param[in]  element_text : Text element that contains the literal to resolve.
* @param[in]  maskvalue : Mask value to resolve.
* @param[in]  maskresolved : Resolved mask output value.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::UserInterface_ChangeLiteralText(UI_ELEMENT_TEXT* element_text, XSTRING* maskvalue, XSTRING* maskresolved)
{
  if(!element_text)   return false;
  if(!maskvalue)      return false;
  if(!maskresolved)   return false;

  if(!maskvalue->Compare(__L("APP_VERSION"), true))
    {
      maskresolved->Format(__L("%d.%d.%d"), APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR);
    }

  if(!maskvalue->Compare(__L("CPU_TEMPERATURE")   , true))  maskresolved->Set(cpu_temperature_str.Get());
  if(!maskvalue->Compare(__L("RAM_USED_TOTAL")    , true))  maskresolved->Set(ram_used_total_str.Get());
  if(!maskvalue->Compare(__L("SYSTEM_DATE")       , true))  maskresolved->Set(system_date_str.Get());
  if(!maskvalue->Compare(__L("SYSTEM_TIME")       , true))  maskresolved->Set(system_time_str.Get());
  if(!maskvalue->Compare(__L("UPTIME_MONTHS")     , true))  maskresolved->Set(uptime_months_str.Get());
  if(!maskvalue->Compare(__L("UPTIME_HOURS")      , true))  maskresolved->Set(uptime_hours_str.Get());
  if(!maskvalue->Compare(__L("UPTIME_YEARS")      , true))  maskresolved->Set(uptime_years_str.Get());
  if(!maskvalue->Compare(__L("UPTIME_SECONDS")    , true))  maskresolved->Set(uptime_seconds_str.Get());
  if(!maskvalue->Compare(__L("CONNECTION_STATUS") , true))  maskresolved->Set(connection_status_str.Get());
  if(!maskvalue->Compare(__L("CONNECTION_QUALITY"), true))  maskresolved->Set(connection_quality_str.Get());
  if(!maskvalue->Compare(__L("CONNECTION_MARK")   , true))  maskresolved->Set(connection_mark_str.Get());
  if(!maskvalue->Compare(__L("LOCAL_IP")          , true))  maskresolved->Set(local_ip_str.Get());
  if(!maskvalue->Compare(__L("FOOTER_EQUIPO")     , true))  maskresolved->Set(footer_equipo_str.Get());
  if(!maskvalue->Compare(__L("FOOTER_SO")         , true))  maskresolved->Set(footer_so_str.Get());
  if(!maskvalue->Compare(__L("FOOTER_UPTIME")     , true))  maskresolved->Set(footer_uptime_str.Get());

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SYSTEM::UserInterface_CFGChromes(GRPSCREEN* screen)
* @brief      user interface  CFGchromes
* @ingroup    
* 
* @param[in]  screen : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::UserInterface_CFGChromes(GRPSCREEN* screen)
{
  GRPSCREENCFGCHROMES cfgchromes;

  #ifdef GRP_SCREEN_CUSTOMCHROMES_ACTIVE

  //cfgchromes.SetCustomAutoHide(500);

  #else

  cfgchromes.SetNativeCaptionActive(true);
  cfgchromes.SetNativeIconActive(true);
  cfgchromes.SetNativeTitleActive(true); 
  cfgchromes.SetNativeMinimizeActive(true);
  cfgchromes.SetNativeMaximizeActive(true);
  cfgchromes.SetNativeCloseActive(true);  

  #endif

  cfgchromes.SetResizeActive(true);

  screen->SetCFGChromes(cfgchromes);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void UI_SYSTEM::HandleEvent_UserInterface(UI_XEVENT* event)
* @brief      Handles user interface events.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @param[in]  event : Event information to process.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void UI_SYSTEM::HandleEvent_UserInterface(UI_XEVENT* event)
{
  switch(event->GetEventType())
    {
      case  UI_XEVENT_TYPE_OUTPUT_SELECTED        : { UI_ELEMENT* element = event->GetElement();
                                                      if(element) UserInterface_ElementSelected(element);                                                      
                                                    }
                                                    break;

      case UI_XEVENT_TYPE_OUTPUT_TEXTTOCHANGE     : { UI_ELEMENT_TEXT* element_text = (UI_ELEMENT_TEXT*)event->GetElement();

                                                      UserInterface_ChangeLiteralText(element_text, event->GetMaskTextValue(), event->GetMaskTextResolved());
                                                    } 
                                                    break;

      case UI_XEVENT_TYPE_OUTPUT_CHANGECONTENTS   : break;
      
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void UI_SYSTEM::HandleEvent_Graphics(GRPXEVENT* event)
* @brief      Handles graphics events.
* @ingroup    EXAMPLES
*
* @param[in]  event : Event information to process.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void UI_SYSTEM::HandleEvent_Graphics(GRPXEVENT* event)
{
  switch(event->GetEventType())
    {
      case GRPXEVENT_TYPE_SCREEN_CREATING   : { GRPSCREEN* screen  = event->GetScreen();
                                                if(!screen) break;
                                                                                              
                                                Ini_Graphics(screen);                                         
                                              }
                                              break;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void UI_SYSTEM::HandleEvent(XEVENT* xevent)
* @brief      Handles an event.
* @ingroup    EXAMPLES
*
* @param[in]  xevent : Event information to process.
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void UI_SYSTEM::HandleEvent(XEVENT* xevent)
{
  if(!xevent) return;

  switch(xevent->GetEventFamily())
    {
      case XEVENT_TYPE_GRAPHICS       : { GRPXEVENT* event = (GRPXEVENT*)xevent;
                                          if(!event) return;

                                          HandleEvent_Graphics(event);
                                        }
                                        break;

      case XEVENT_TYPE_USERINTERFACE  : { UI_XEVENT* event = (UI_XEVENT*)xevent;
                                          if(!event) return;

                                          HandleEvent_UserInterface(event);
                                        }
                                        break;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void UI_SYSTEM::Clean()
* @brief      Cleans the object internal state.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void UI_SYSTEM::Clean()
{
  xtimer                       = NULL;

  for(int c=0; c<UI_SYSTEM_BUTTON_MAX; c++)
    {
      button[c] = NULL;
    }

  cursor                        = NULL;

  diocheckinternetconnection    = NULL;

  currentsectionID               = UI_SYSTEM_SECTIONID_RESUMEN;
  lastupdatehardwareinfo_second  = 0;

  cpu_temperature_str.Empty();
  ram_used_total_str.Empty();
  system_date_str.Empty();
  system_time_str.Empty();
  uptime_months_str.Empty();
  uptime_hours_str.Empty();
  uptime_years_str.Empty();
  uptime_seconds_str.Empty();
  connection_status_str.Empty();
  connection_quality_str.Empty();
  connection_mark_str.Empty();
  local_ip_str.Empty();
  footer_equipo_str.Empty();
  footer_so_str.Empty();
  footer_uptime_str.Empty();
}


