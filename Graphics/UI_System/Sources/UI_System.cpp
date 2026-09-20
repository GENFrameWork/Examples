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
#include "XDiagLog.h"                        // TEMPORARY diagnostic-only, see XDiagLog.h -- remove with it

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

 APPLICATIONCREATEINSTANCE(UI_SYSTEM, ui_system)



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
  // Background hardware-info thread: HardwareInfo_Compute() (see its own note in UI_System.h)
  // is what used to run straight inside AppProc_Update(), in the middle of the render loop --
  // most notably HardwareInfo_UpdateConnection(), which can block on a real network check. It
  // now runs here instead, on its own XTHREAD, so a slow/stalled network check can never delay
  // a rendered frame: AppProc_Update() only ever calls the cheap, non-blocking HardwareInfo_Apply().
  //
  // Created/started only AFTER every field it (or HardwareInfo_Compute()) touches is already in
  // its final initial state above -- lastupdatehardwareinfo_second in particular, since
  // hardwareinfothread->Ini() below can have the background thread calling HardwareInfo_Compute()
  // before this function returns, and that field is read/written under hardwareinfomutex from
  // then on, never again from this (main) thread directly.
  //
  // waityield is set short (200ms) so a HardwareInfo_RequestForced() call (F5) or shutdown is
  // noticed quickly -- HardwareInfo_Compute() still self-throttles to once every
  // UI_SYSTEM_HARDWAREINFO_UPDATEPERIOD_SECONDS internally, exactly as before, so this does not
  // make the actual hardware reads any more frequent than they already were.
  //--------------------------------------------------------------------------------------

  hardwareinfomutex = GEN_XFACTORY.Create_Mutex();
  if(!hardwareinfomutex) return false;

  hardwareinfothread = GEN_XFACTORY.CreateThread(XTHREADGROUPID_UI_SYSTEM_HARDWAREINFO, __L("UI_SYSTEM::HardwareInfo"), ThreadFunction_UpdateHardwareInfo, this);
  if(!hardwareinfothread) return false;

  hardwareinfothread->SetWaitYield(200);
  hardwareinfothread->Ini();

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
  // The normal path: Ini_Graphics() already loaded the dashboard, before the window was ever shown
  // (see the note there). This is now just the fallback/retry for a platform where that early attempt
  // did not run or did not succeed -- same failure handling as the original single call site, an app
  // that cannot load its own UI aborts here instead of continuing into a silently blank window.
  //--------------------------------------------------------------------------------------

  if(!dashboardloaded)
    {
      if(!Ini_UserInterface(true)) return false;
    }

  //--------------------------------------------------------------------------------------
  // First hardware info population. This used to be a synchronous, forced UpdateHardwareInfo(true)
  // call right here -- deliberately kept out of Ini_Graphics() and left this late specifically
  // because HardwareInfo_UpdateConnection() can block on a real network check (see the note that
  // used to be here, and still applies -- it just moved, see Ini_Graphics()). Now that hardware
  // info runs on its own background thread (started in AppProc_Ini(), already running by the time
  // this executes), that concern is gone: this just raises a flag for it to pick up on its very
  // next tick instead of running the read itself. The dashboard's first rendered frame still shows
  // its authored placeholder values for one or two frames until that first background pass
  // publishes -- same as before, just no longer at the cost of a synchronous block here.
  //--------------------------------------------------------------------------------------

  HardwareInfo_RequestForced();

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
                                               HardwareInfo_Apply();
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
  // Stop the background hardware-info thread FIRST, before anything below it reads (xtimer,
  // diocheckinternetconnection) gets deleted, and before Ini_UserInterface(false) tears down
  // GEN_USERINTERFACE. hardwareinfoexiting is a fast-path guard so a thread tick that fires
  // between this flag being set and End() actually stopping it returns immediately instead of
  // starting one more (unlockable) compute pass; End() itself blocks (via WaitToEnd()) until any
  // pass already in flight has finished, so by the time this block returns the background thread
  // is guaranteed to no longer be touching xtimer/diocheckinternetconnection/hardwareinfomutex.
  //--------------------------------------------------------------------------------------

  hardwareinfoexiting = true;

  if(hardwareinfothread)
    {
      hardwareinfothread->End();
      GEN_XFACTORY.DeleteThread(XTHREADGROUPID_UI_SYSTEM_HARDWAREINFO, hardwareinfothread);

      hardwareinfothread = NULL;
    }

  if(hardwareinfomutex)
    {
      GEN_XFACTORY.Delete_Mutex(hardwareinfomutex);
      hardwareinfomutex = NULL;
    }

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
                                                HardwareInfo_RequestForced();
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
  // Load the dashboard as early as possible: SCREEN_CREATING (which is what is being handled right
  // now, all the way up the call chain to HandleEvent_Graphics()) fires BEFORE CreateMainScreenProcess()
  // goes on to call mainscreen->Create(show) -- the call that actually maps the native window and makes
  // it visible. Ini_UserInterface() used to run from AppProc_FirstUpdate() instead, which is the first
  // tick of the app's main loop -- by construction AFTER the window was already on screen. Whatever the
  // OS painted in between (an empty/zeroed canvas -- see the GRP2DCANVAS::Buffer_Create() fix -- or,
  // before that fix, whatever was left in the freshly allocated buffer) was visible to the user for the
  // whole time dashboard.xml and its ~30 SVG icons were being parsed and decoded. Doing that same work
  // HERE instead removes essentially all of it from the window the user could watch it happen in: the
  // viewport/canvas this needs already exist (CreateViewport() just above), and nothing else this touches
  // depends on the native window itself.
  //
  // Hardware info population deliberately stays OUT of this early call, and is still requested from
  // AppProc_FirstUpdate() instead (now via HardwareInfo_RequestForced(), no longer a synchronous call --
  // see AppProc_Ini()/AppProc_FirstUpdate()). HardwareInfo_UpdateConnection() can block on a real network
  // check; that used to matter here because the call was synchronous and this runs before the window
  // exists at all. It runs on its own background thread now, so it would technically be safe to request
  // it this early too -- left at AppProc_FirstUpdate() anyway, since nothing here depends on hardware info
  // being ready any sooner and moving it would not change when the first real values actually appear on
  // screen (that is gated by the background thread's own first pass, not by when it is asked to start).
  // The dashboard's first frame simply shows its authored placeholder values for a frame or two, same as
  // it always could between any two periodic refreshes.
  //
  // dashboardloaded records whether this attempt succeeded, so AppProc_FirstUpdate() below does not load
  // it a second time on the normal path, but still retries -- and still aborts startup on failure exactly
  // like the original single call site did -- if this one did not run or did not succeed (a platform whose
  // canvas creation is genuinely deferred past this point would hit that fallback, not a silent blank UI).
  //--------------------------------------------------------------------------------------

  dashboardloaded = Ini_UserInterface(true);

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
  xpath.Add(__L("ui_system/dashboard.xml"));
    
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
  // TEMPORARY DIAGNOSTIC INSTRUMENTATION (2026-09) -- see XDiagLog.h. Root-causing a multi-second full-dashboard
  // blank-freeze reported on real hardware/VMs (Windows and Linux) that a sandboxed reconstruction did not fully
  // explain. Times each of the 3 frame phases against XDiagLog's shared wall clock (a real platform XTIMER, NOT
  // clock()/CPU time -- a genuine block/wait must show up here, unlike CPU time, which would hide it). Logs a
  // [SLOWFRAME] line only when this single frame took over 20ms (past a 16.6ms/60fps budget) and a [HEARTBEAT]
  // line once a second regardless, so a stall INSIDE DrawFrame (heartbeats keep coming, frames are just slow) can
  // be told apart from the whole main loop not being called at all (heartbeats themselves stop appearing).
  //--------------------------------------------------------------------------------------

  static XQWORD diag_framecounter    = 0;
  static XQWORD diag_hb_windowstart  = XDIAGLOG_NOWUS();
  static XQWORD diag_hb_frames       = 0;
  static XQWORD diag_hb_maxus        = 0;

  // TEMPORARY diagnostics -- counters defined in UI_Skin.cpp, incremented on every UI_SKIN::Draw() call this
  // frame (recursive: covers every top-level element AND every descendant visited via Draw_Form()/Draw_Menu()
  // etc). Tells us the ACTUAL size of the tree walked per frame and how much of it was visible/dirty, since the
  // existing "update=" timing alone cannot distinguish "few elements, each expensive" from "many elements,
  // walked normally" -- both would show the same total. Extern-declared here rather than in a header since
  // this is throwaway.
  extern XDWORD diagskin_visits;
  extern XDWORD diagskin_visible;
  extern XDWORD diagskin_dirty;
  extern XQWORD diagskin_shadowus;         // UI_SkinCanvas.cpp -- accumulated us inside soft-shadow build+composite
  extern XDWORD diagskin_shadowcalls;      // UI_SkinCanvas.cpp -- how many soft-shadow draws happened this frame
  extern XDWORD diagskin_shadowcachehits;  // UI_SkinCanvas.cpp -- of those, how many reused the cached bitmap (Draw_Form path only)
  extern XDWORD diagskin_shadowcachemiss;  // UI_SkinCanvas.cpp -- of those, how many had to rebuild it

  diagskin_visits          = 0;
  diagskin_visible         = 0;
  diagskin_dirty           = 0;
  diagskin_shadowus         = 0;
  diagskin_shadowcalls      = 0;
  diagskin_shadowcachehits  = 0;
  diagskin_shadowcachemiss  = 0;

  XQWORD diag_t0 = XDIAGLOG_NOWUS();

  //--------------------------------------------------------------------------------------

  canvas->ReleaseDrawFramerate();

  canvas->RebuildAllAreas();

  XQWORD diag_t1 = XDIAGLOG_NOWUS();

  //--------------------------------------------------------------------------------------

  GEN_USERINTERFACE.Elements_RebuildDrawAreas();

  XQWORD diag_t2 = XDIAGLOG_NOWUS();

  GEN_USERINTERFACE.Update();

  XQWORD diag_t3 = XDIAGLOG_NOWUS();

  //--------------------------------------------------------------------------------------
  // Diagnostic bookkeeping -- see note above.
  //--------------------------------------------------------------------------------------

  diag_framecounter++;
  diag_hb_frames++;
  if((diag_t3 - diag_t0) > diag_hb_maxus) diag_hb_maxus = diag_t3 - diag_t0;

  if((diag_t3 - diag_t0) > 20000)
    {
      XDIAGLOG_WRITE("SLOWFRAME", "n=%llu total=%lluus canvasrebuild=%lluus elementsrebuild=%lluus update=%lluus skinvisits=%u skinvisible=%u skindirty=%u shadowcalls=%u shadowus=%llu shadowhits=%u shadowmiss=%u",
                      (unsigned long long)diag_framecounter,
                      (unsigned long long)(diag_t3-diag_t0), (unsigned long long)(diag_t1-diag_t0),
                      (unsigned long long)(diag_t2-diag_t1), (unsigned long long)(diag_t3-diag_t2),
                      (unsigned int)diagskin_visits, (unsigned int)diagskin_visible, (unsigned int)diagskin_dirty,
                      (unsigned int)diagskin_shadowcalls, (unsigned long long)diagskin_shadowus,
                      (unsigned int)diagskin_shadowcachehits, (unsigned int)diagskin_shadowcachemiss);
    }

  if((XDIAGLOG_NOWUS() - diag_hb_windowstart) > 1000000ULL)
    {
      XDIAGLOG_WRITE("HEARTBEAT", "frames_in_window=%llu maxframe=%lluus", (unsigned long long)diag_hb_frames, (unsigned long long)diag_hb_maxus);
      diag_hb_frames      = 0;
      diag_hb_maxus       = 0;
      diag_hb_windowstart = XDIAGLOG_NOWUS();
    }

  //--------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void UI_SYSTEM::ThreadFunction_UpdateHardwareInfo(void* param)
* @brief      Background thread entry point: called repeatedly (every hardwareinfothread waityield
*             tick) by GEN's XTHREAD, for as long as the thread is running.
* @note       STATIC. Runs on the background thread, never on the main thread.
* @ingroup    EXAMPLES
*
* @param[in]  param : the UI_SYSTEM instance (passed as the thread's data pointer at creation).
*
*---------------------------------------------------------------------------------------------------------------------*/
void UI_SYSTEM::ThreadFunction_UpdateHardwareInfo(void* param)
{
  UI_SYSTEM* uisystem = (UI_SYSTEM*)param;
  if(!uisystem)                      return;
  if(uisystem->hardwareinfoexiting)  return;

  uisystem->HardwareInfo_Compute(false);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::HardwareInfo_Compute(bool forced)
* @brief      Reads every hardware/system information source and publishes the results for
*             HardwareInfo_Apply() to pick up. This is the direct replacement for what the old
*             UpdateHardwareInfo(bool) did, minus touching GEN_USERINTERFACE/UI_ELEMENT directly.
* @note       Runs ONLY on the background thread (called from ThreadFunction_UpdateHardwareInfo()).
* @ingroup    EXAMPLES
*
* @param[in]  forced : true to ignore the update period and refresh immediately.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::HardwareInfo_Compute(bool forced)
{
  if(!xtimer)             return false;
  if(!hardwareinfomutex)  return false;

  XQWORD actualsecond = xtimer->GetMeasureSeconds();
  bool   duetorun;

  hardwareinfomutex->Lock();

    if(hardwareinfo_forcenext)
      {
        forced                  = true;
        hardwareinfo_forcenext  = false;
      }

    duetorun = forced || ((actualsecond - lastupdatehardwareinfo_second) >= UI_SYSTEM_HARDWAREINFO_UPDATEPERIOD_SECONDS);

  hardwareinfomutex->UnLock();

  if(!duetorun) return true;

  //--------------------------------------------------------------------------------------
  // Everything below runs UNLOCKED, into local (this call's own stack, background-thread-only)
  // variables: this is exactly the work that used to run straight inside AppProc_Update() and
  // could stall rendering -- most notably HardwareInfo_UpdateConnection(), which can block on a
  // real network check. It is now free to take as long as it needs without the render loop (or
  // HardwareInfo_Apply(), which only ever takes the mutex for the short "publish" block further
  // down) ever waiting on it.
  //--------------------------------------------------------------------------------------

  XSTRING temperaturestr, usedtotalstr, datestr, timestr;
  XSTRING monthsstr, hoursstr, yearsstr, secondsstr;
  XSTRING statusstr, qualitystr, markstr, ipstr;
  XSTRING equipostr, sostr, uptimestr;

  float temperaturelevel = 0.0f;
  float cpuusagelevelnow = 0.0f;
  float ramusagelevelnow = 0.0f;
  bool  isconnectednow   = false;

  // TEMPORARY diagnostic-only (see XDiagLog.h): times each source and the mutex re-acquire below, to check
  // empirically whether HardwareInfo_UpdateConnection() (the one documented as able to block on a real network
  // check) or mutex contention with the render thread is actually overlapping with the multi-second blank-freeze
  // under investigation, rather than trusting the "this can never stall rendering" design intent unverified.
  XQWORD diagh_t0 = XDIAGLOG_NOWUS();
  HardwareInfo_UpdateCPU(temperaturestr, temperaturelevel, cpuusagelevelnow);
  XQWORD diagh_t1 = XDIAGLOG_NOWUS();
  HardwareInfo_UpdateMemory(usedtotalstr, ramusagelevelnow);
  XQWORD diagh_t2 = XDIAGLOG_NOWUS();
  HardwareInfo_UpdateDateTime(datestr, timestr);
  XQWORD diagh_t3 = XDIAGLOG_NOWUS();
  HardwareInfo_UpdateUptime(monthsstr, hoursstr, yearsstr, secondsstr);
  XQWORD diagh_t4 = XDIAGLOG_NOWUS();
  HardwareInfo_UpdateConnection(isconnectednow, statusstr, qualitystr, markstr, ipstr);
  XQWORD diagh_t5 = XDIAGLOG_NOWUS();
  HardwareInfo_UpdateFooter(equipostr, sostr, uptimestr);
  XQWORD diagh_t6 = XDIAGLOG_NOWUS();

  if((diagh_t6 - diagh_t0) > 5000)   // this whole unlocked block took over 5ms
    {
      XDIAGLOG_WRITE("HWINFO", "cpu=%lluus mem=%lluus datetime=%lluus uptime=%lluus connection=%lluus footer=%lluus total=%lluus",
                      (unsigned long long)(diagh_t1-diagh_t0), (unsigned long long)(diagh_t2-diagh_t1),
                      (unsigned long long)(diagh_t3-diagh_t2), (unsigned long long)(diagh_t4-diagh_t3),
                      (unsigned long long)(diagh_t5-diagh_t4), (unsigned long long)(diagh_t6-diagh_t5),
                      (unsigned long long)(diagh_t6-diagh_t0));
    }

  //--------------------------------------------------------------------------------------
  // Publish: the only point where this thread touches the fields the main thread reads
  // (directly in HardwareInfo_Apply(), or via UserInterface_ChangeLiteralText() when
  // GEN_USERINTERFACE resolves a #[MASK] literal during its own redraw). Held just long enough
  // to copy already-computed values -- never around any of the work above.
  //--------------------------------------------------------------------------------------

  { XQWORD diagh_lockwaitstart = XDIAGLOG_NOWUS();
    hardwareinfomutex->Lock();
    XQWORD diagh_lockwaitelapsed = XDIAGLOG_NOWUS() - diagh_lockwaitstart;
    if(diagh_lockwaitelapsed > 5000)   // acquiring the "publish" lock itself took over 5ms -- contention
      {
        XDIAGLOG_WRITE("HWINFO", "publish-lock WAIT elapsed=%lluus (contended by the render thread?)", (unsigned long long)diagh_lockwaitelapsed);
      }
  }

    cpu_temperature_str.Set(temperaturestr.Get());
    ram_used_total_str.Set(usedtotalstr.Get());
    system_date_str.Set(datestr.Get());
    system_time_str.Set(timestr.Get());
    uptime_months_str.Set(monthsstr.Get());
    uptime_hours_str.Set(hoursstr.Get());
    uptime_years_str.Set(yearsstr.Get());
    uptime_seconds_str.Set(secondsstr.Get());
    connection_status_str.Set(statusstr.Get());
    connection_quality_str.Set(qualitystr.Get());
    connection_mark_str.Set(markstr.Get());
    local_ip_str.Set(ipstr.Get());
    footer_equipo_str.Set(equipostr.Get());
    footer_so_str.Set(sostr.Get());
    footer_uptime_str.Set(uptimestr.Get());

    cpu_temperaturelevel = temperaturelevel;
    cpu_usagelevel       = cpuusagelevelnow;
    ram_usagelevel       = ramusagelevelnow;
    isconnected          = isconnectednow;

    lastupdatehardwareinfo_second = actualsecond;
    hardwareinfo_haspending       = true;

  hardwareinfomutex->UnLock();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::HardwareInfo_Apply()
* @brief      Pushes whatever HardwareInfo_Compute() last published into the actual UI_ELEMENTs
*             and asks for a redraw. Cheap no-op when nothing changed since the last frame.
* @note       Runs ONLY on the main thread (called from AppProc_Update(), where the old inline
*             UpdateHardwareInfo(false) call used to be). This is the only place in the whole
*             class that still touches UI_ELEMENT/GEN_USERINTERFACE for hardware info.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::HardwareInfo_Apply()
{
  if(!hardwareinfomutex) return false;

  bool  haspending;
  float temperaturelevel = 0.0f;
  float cpuusagelevelnow = 0.0f;
  float ramusagelevelnow = 0.0f;
  bool  isconnectednow   = false;

  // TEMPORARY diagnostic-only (see XDiagLog.h): this runs on the MAIN (render) thread -- if acquiring this lock
  // ever takes a long time, that is direct proof of the background hardware-info thread stalling the render
  // loop, regardless of what the design intent says.
  XQWORD diaga_lockwaitstart = XDIAGLOG_NOWUS();

  hardwareinfomutex->Lock();

    { XQWORD diaga_lockwaitelapsed = XDIAGLOG_NOWUS() - diaga_lockwaitstart;
      if(diaga_lockwaitelapsed > 5000)
        {
          XDIAGLOG_WRITE("HWINFO", "MAIN THREAD apply-lock WAIT elapsed=%lluus (render thread stalled by background thread)", (unsigned long long)diaga_lockwaitelapsed);
        }
    }

    haspending = hardwareinfo_haspending;

    if(haspending)
      {
        hardwareinfo_haspending = false;

        temperaturelevel = cpu_temperaturelevel;
        cpuusagelevelnow = cpu_usagelevel;
        ramusagelevelnow = ram_usagelevel;
        isconnectednow   = isconnected;
      }

  hardwareinfomutex->UnLock();

  if(!haspending) return true;                            // nothing new since the last frame

  //--------------------------------------------------------------------------------------
  // From here on this is exactly what UpdateHardwareInfo(false)'s HardwareInfo_UpdateCPU() /
  // _UpdateMemory() / _UpdateConnection() used to do inline, just fed from the values the
  // background thread already computed instead of computing them here. No mutex needed below:
  // this function only ever runs on the main thread.
  //--------------------------------------------------------------------------------------

  UI_ELEMENT_PROGRESS_IMAGE* element_temp = (UI_ELEMENT_PROGRESS_IMAGE*)GEN_USERINTERFACE.Element_Get(__L("cpu_temp_bar"), UI_ELEMENT_TYPE_PROGRESSIMAGE);
  if(element_temp) element_temp->SetLevel(temperaturelevel);

  UI_ELEMENT_PROGRESS_RADIAL* element_cpu = (UI_ELEMENT_PROGRESS_RADIAL*)GEN_USERINTERFACE.Element_Get(__L("cpu_usage_radial"), UI_ELEMENT_TYPE_PROGRESSRADIAL);
  if(element_cpu) element_cpu->SetLevel(cpuusagelevelnow);

  UI_ELEMENT_PROGRESS_RADIAL* element_radial = (UI_ELEMENT_PROGRESS_RADIAL*)GEN_USERINTERFACE.Element_Get(__L("ram_usage_radial"), UI_ELEMENT_TYPE_PROGRESSRADIAL);
  if(element_radial) element_radial->SetLevel(ramusagelevelnow);

  UI_ELEMENT_PROGRESSBAR* element_bar = (UI_ELEMENT_PROGRESSBAR*)GEN_USERINTERFACE.Element_Get(__L("ram_linear_bar"), UI_ELEMENT_TYPE_PROGRESSBAR);
  if(element_bar) element_bar->SetLevel(ramusagelevelnow);

  //--------------------------------------------------------------------------------------
  // Status glyph. Two images sit stacked at the same spot in the layout (a green disc with a
  // tick, and a red disc with a cross); only one of them is ever visible. This replaces the
  // previous "recolour a round form" approach, which stopped being visible once Draw_Form
  // started preferring background-color over color for its fill.
  //--------------------------------------------------------------------------------------

  UI_ELEMENT* element_iconok = GEN_USERINTERFACE.Element_Get(__L("connection_icon_ok"), UI_ELEMENT_TYPE_IMAGE);
  if(element_iconok) element_iconok->SetVisible(isconnectednow);

  UI_ELEMENT* element_iconko = GEN_USERINTERFACE.Element_Get(__L("connection_icon_ko"), UI_ELEMENT_TYPE_IMAGE);
  if(element_iconko) element_iconko->SetVisible(!isconnectednow);

  //--------------------------------------------------------------------------------------
  // The status line follows the same semantics: green when up, red when down.
  //--------------------------------------------------------------------------------------

  UI_ELEMENT_TEXT* element_status = (UI_ELEMENT_TEXT*)GEN_USERINTERFACE.Element_Get(__L("connection_status_text"), UI_ELEMENT_TYPE_TEXT);
  if(element_status) element_status->GetColor()->SetFromString(isconnectednow ? __L("63,185,80") : __L("248,81,73"));

  //--------------------------------------------------------------------------------------
  // Mark only the text leaves whose masks can have changed. The skin's rebuild-area transaction expands
  // this set to every overlapping surface/element before restoring pixels, so the example does not need to
  // know which card happens to be behind each value. Keeping that dependency in the renderer is essential:
  // a future CSS layout can move or restack these elements without changing application code.
  //--------------------------------------------------------------------------------------

  static XCHAR* maskedtextelements[] =
    {
      __L("footer_equipo_text")      ,
      __L("footer_so_text")          ,
      __L("footer_uptime_text")      ,
      __L("cpu_temp_value")          ,
      __L("ram_used_total")          ,
      __L("system_date")             ,
      __L("system_time")             ,
      __L("uptime_months_value")     ,
      __L("uptime_hours_value")      ,
      __L("uptime_years_value")      ,
      __L("uptime_seconds_value")    ,
      __L("connection_status_text")  ,
      __L("connection_quality")      ,
      __L("connection_ip")           ,
    };

  for(int c=0; c<(int)(sizeof(maskedtextelements)/sizeof(maskedtextelements[0])); c++)
    {
      UI_ELEMENT* element_masked = GEN_USERINTERFACE.Element_Get(maskedtextelements[c], UI_ELEMENT_TYPE_TEXT);
      if(element_masked) GEN_USERINTERFACE.Elements_SetToRedraw(element_masked, false);
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::HardwareInfo_RequestForced()
* @brief      Non-blocking replacement for the old UpdateHardwareInfo(true) call sites (first
*             frame, F5): raises a flag for the background thread to notice on its next tick
*             (within hardwareinfothread's waityield) instead of running the reads synchronously
*             on the caller's thread.
* @ingroup    EXAMPLES
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::HardwareInfo_RequestForced()
{
  if(!hardwareinfomutex) return false;

  hardwareinfomutex->Lock();
    hardwareinfo_forcenext = true;
  hardwareinfomutex->UnLock();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::HardwareInfo_UpdateCPU(XSTRING& outtemperature, float& outtemperaturelevel, float& outusagelevel)
* @brief      Reads CPU temperature and CPU usage from GEN_XSYSTEM.
* @note       Called from HardwareInfo_Compute(), on the background thread. Writes only into its
*             own output parameters -- no member/UI_ELEMENT access here anymore.
* @ingroup    EXAMPLES
*
* @param[out] outtemperature : formatted "NN", digits only (or "--" if unavailable). The "\u00B0C" unit is a
*             separate, smaller-sizefont static <text> element (cpu_temp_unit) in dashboard.xml -- see the
*             comment there -- so it no longer travels inside this string.
* @param[out] outtemperaturelevel : temperature level for cpu_temp_bar, clamped to [0,100].
* @param[out] outusagelevel : CPU usage percent for cpu_usage_radial, 0 if unavailable.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::HardwareInfo_UpdateCPU(XSTRING& outtemperature, float& outtemperaturelevel, float& outusagelevel)
{
  //--------------------------------------------------------------------------------------
  // CPU Temperature: a real sensor reading on Windows (WMI), Linux (thermal sysfs), and Android
  // (same sysfs interface -- XANDROIDSYSTEM inherits XLINUXSYSTEM's implementation). Some boards/
  // OEM builds still expose no readable thermal zone at all, and microcontroller platforms
  // (ESP32/STM32) have no CPU temperature sensor to read in the first place; GEN_XSYSTEM.
  // GetCPUTemperature() returns 0.0f in every one of those cases, so the value is left as a "--"
  // placeholder instead of showing a fake number.
  //--------------------------------------------------------------------------------------

  float cputemperature = GEN_XSYSTEM.GetCPUTemperature();

  outtemperaturelevel = 0.0f;

  if(cputemperature > 0.0f)
    {
      outtemperature.Format(__L("%d"), (int)(cputemperature + 0.5f));

      outtemperaturelevel = cputemperature;
      if(outtemperaturelevel > 100.0f) outtemperaturelevel = 100.0f;
    }
   else
    {
      outtemperature.Set(__L("--"));
    }

  //--------------------------------------------------------------------------------------
  // CPU Usage (total, real value read from the OS: /proc/stat on Linux, WMI on Windows, ...)
  //--------------------------------------------------------------------------------------

  int cpuusage = GEN_XSYSTEM.GetCPUUsageTotal();

  outusagelevel = (cpuusage != XSYSTEM_CPUUSAGE_ERROR) ? (float)cpuusage : 0.0f;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::HardwareInfo_UpdateMemory(XSTRING& outusedtotal, float& outusagelevel)
* @brief      Reads RAM usage from GEN_XSYSTEM.
* @note       Called from HardwareInfo_Compute(), on the background thread. Writes only into its
*             own output parameters -- no member/UI_ELEMENT access here anymore.
* @ingroup    EXAMPLES
*
* @param[out] outusedtotal : formatted RAM used / total, selecting KB, MB, GB or TB from total memory.
* @param[out] outusagelevel : RAM used percent, for ram_usage_radial and ram_linear_bar.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::HardwareInfo_UpdateMemory(XSTRING& outusedtotal, float& outusagelevel)
{
  XDWORD total = 0;
  XDWORD free  = 0;

  outusagelevel = 0.0f;

  if(GEN_XSYSTEM.GetMemoryInfo(total, free) && total)
    {
      XDWORD       used          = total - free;
      double       memorydivisor = 1.0;
      const XCHAR* memoryunit    = __L("KB");

      if(total >= (1024U * 1024U * 1024U))
        {
          memorydivisor = 1024.0 * 1024.0 * 1024.0;
          memoryunit    = __L("TB");
        }
      else if(total >= (1024U * 1024U))
        {
          memorydivisor = 1024.0 * 1024.0;
          memoryunit    = __L("GB");
        }
      else if(total >= 1024U)
        {
          memorydivisor = 1024.0;
          memoryunit    = __L("MB");
        }

      outusedtotal.Format(__L("%.1f %s / %.1f %s"),
                          (double)used  / memorydivisor, memoryunit,
                          (double)total / memorydivisor, memoryunit);

      outusagelevel = (float)(((double)used / (double)total) * 100.0);
    }
   else
    {
      outusedtotal.Set(__L("-- / --"));
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::HardwareInfo_UpdateDateTime(XSTRING& outdate, XSTRING& outtime)
* @brief      Reads the actual system date and time.
* @note       Called from HardwareInfo_Compute(), on the background thread.
* @ingroup    EXAMPLES
*
* @param[out] outdate : formatted "DD/MM/YYYY".
* @param[out] outtime : formatted "HH:MM:SS".
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::HardwareInfo_UpdateDateTime(XSTRING& outdate, XSTRING& outtime)
{
  XDATETIME* xdatetime = GEN_XFACTORY.CreateDateTime();
  if(!xdatetime) return false;

  xdatetime->Read();

  outdate.Format(__L("%02d/%02d/%04d"), xdatetime->GetDay(),  xdatetime->GetMonth(),   xdatetime->GetYear());
  outtime.Format(__L("%02d:%02d:%02d"), xdatetime->GetHours(), xdatetime->GetMinutes(), xdatetime->GetSeconds());

  GEN_XFACTORY.DeleteDateTime(xdatetime);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::HardwareInfo_UpdateUptime(XSTRING& outmonths, XSTRING& outhours, XSTRING& outyears, XSTRING& outseconds)
* @brief      Builds the "Tiempo de funcionamiento del sistema" figures out of the elapsed apptimer.
* @note       Called from HardwareInfo_Compute(), on the background thread.
* @ingroup    EXAMPLES
*
* @param[out] outmonths  : elapsed months, as text.
* @param[out] outhours   : elapsed hours, as text.
* @param[out] outyears   : elapsed years, as text.
* @param[out] outseconds : elapsed seconds, as text.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::HardwareInfo_UpdateUptime(XSTRING& outmonths, XSTRING& outhours, XSTRING& outyears, XSTRING& outseconds)
{
  if(!xtimer) return false;

  XQWORD allseconds = xtimer->GetMeasureSeconds();

  XDWORD years   = XDATETIME_SECONDSYEARS(allseconds);
  XDWORD months  = XDATETIME_SECONDSMONTHS(allseconds);
  XDWORD hours   = (XDWORD)(allseconds / XDATETIME_SECONDSINHOUR);

  outyears.Format  (__L("%d"), years);
  outmonths.Format (__L("%d"), months);
  outhours.Format  (__L("%d"), hours);
  outseconds.Format(__L("%d"), (XDWORD)allseconds);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::HardwareInfo_UpdateConnection(bool& outisconnected, XSTRING& outstatus, XSTRING& outquality, XSTRING& outmark, XSTRING& outip)
* @brief      Checks the internet connection status, its latency and the local IP address.
* @note       Called from HardwareInfo_Compute(), on the background thread. This is the one most
*             worth having moved off the main thread: diocheckinternetconnection->Check() can
*             block on a real network check. No UI_ELEMENT touched here anymore -- outisconnected
*             is what HardwareInfo_Apply() uses to drive the status glyph/colour on the main thread.
* @ingroup    EXAMPLES
*
* @param[out] outisconnected : true if the connection check succeeded.
* @param[out] outstatus : "Conectado" / "Desconectado".
* @param[out] outquality : "Conexi\u00F3n estable" / "Sin conexi\u00F3n".
* @param[out] outmark : "OK" / "--".
* @param[out] outip : formatted "IP: x.x.x.x" (or "IP: --" if unavailable).
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::HardwareInfo_UpdateConnection(bool& outisconnected, XSTRING& outstatus, XSTRING& outquality, XSTRING& outmark, XSTRING& outip)
{
  outisconnected = false;

  if(diocheckinternetconnection)
    {
      outisconnected = diocheckinternetconnection->Check();
    }

  if(outisconnected)
    {
      outstatus.Set(__L("Conectado"));
      outquality.Set(__L("Conexi\u00F3n estable"));
      outmark.Set(__L("OK"));
    }
   else
    {
      outstatus.Set(__L("Desconectado"));
      outquality.Set(__L("Sin conexi\u00F3n"));
      outmark.Set(__L("--"));
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

          outip.Format(__L("IP: %s"), ipstring.Get());
        }
       else
        {
          outip.Set(__L("IP: --"));
        }

      GEN_DIOFACTORY.DeleteStreamEnumDevices(enumdevices);
    }
   else
    {
      outip.Set(__L("IP: --"));
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_SYSTEM::HardwareInfo_UpdateFooter(XSTRING& outequipo, XSTRING& outso, XSTRING& outuptime)
* @brief      Builds the status bar literals (equipment name, operative system and uptime summary).
* @note       Called from HardwareInfo_Compute(), on the background thread.
* @ingroup    EXAMPLES
*
* @param[out] outequipo : "Equipo: <domain>" (or "Equipo: --" if unavailable).
* @param[out] outso : "SO: <id>" (or "SO: --" if unavailable).
* @param[out] outuptime : "Uptime del sistema: <measure>".
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_SYSTEM::HardwareInfo_UpdateFooter(XSTRING& outequipo, XSTRING& outso, XSTRING& outuptime)
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
      outequipo.Format(__L("Equipo: %s"), domain.Get());
    }
   else
    {
      outequipo.Set(__L("Equipo: --"));                    // TODO: add a real hostname source for this platform
    }

  //--------------------------------------------------------------------------------------

  XSTRING operativesystemID;

  if(GEN_XSYSTEM.GetOperativeSystemID(operativesystemID) && (!operativesystemID.IsEmpty()))
    {
      // Shorten live Windows strings ("Microsoft Windows 11 Pro Build 26200") so the footer can show
      // Equipo | SO | Uptime without the huge fixed gaps the mockup used for short Linux IDs.
      XSTRING soid = operativesystemID;
      if(soid.Find(__L("Microsoft "), true) == 0) soid.DeleteCharacters(0, 10);
      int buildat = soid.Find(__L(" Build"), true);
      if(buildat >= 0) soid.DeleteCharactersToEnd((XDWORD)buildat);
      outso.Format(__L("SO: %s"), soid.Get());
    }
   else
    {
      outso.Set(__L("SO: --"));
    }

  //--------------------------------------------------------------------------------------

  if(xtimer)
    {
      XSTRING measure;

      xtimer->GetMeasureString(measure, true);

      if(!measure.IsEmpty())
            outuptime.Format(__L("Uptime del sistema: %s"), measure.Get());
       else outuptime.Set(__L("Uptime del sistema: 0 segundos"));
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
  // Official selection path: SetSelected on the hit-target button (CSS :selected wash) and on the nav-row
  // so descendant rules like `form.nav-row:selected .nav-label` restyle the label without C++ color hacks.
  // Legacy nav-*-hl / nav-*-bar overlays are removed from the layout; stylesheet is the source of truth.
  static XCHAR* navbtnnames[UI_SYSTEM_SECTIONID_MAX]    = { __L("nav-resumen-btn")       ,
                                                             __L("nav-cpu-btn")           ,
                                                             __L("nav-memoria-btn")       ,
                                                             __L("nav-red-btn")           ,
                                                             __L("nav-disco-btn")         ,
                                                             __L("nav-procesos-btn")      ,
                                                             __L("nav-alertas-btn")       ,
                                                             __L("nav-configuracion-btn")  };

  static XCHAR* navrownames[UI_SYSTEM_SECTIONID_MAX]    = { __L("nav-resumen-row")       ,
                                                             __L("nav-cpu-row")           ,
                                                             __L("nav-memoria-row")       ,
                                                             __L("nav-red-row")           ,
                                                             __L("nav-disco-row")         ,
                                                             __L("nav-procesos-row")      ,
                                                             __L("nav-alertas-row")       ,
                                                             __L("nav-configuracion-row")  };

  for(int c=0; c<UI_SYSTEM_SECTIONID_MAX; c++)
    {
      bool isactive = (c == (int)sectionID);

      UI_ELEMENT* element_btn = GEN_USERINTERFACE.Element_Get(navbtnnames[c], UI_ELEMENT_TYPE_BUTTON);
      if(element_btn) element_btn->SetSelected(isactive);

      UI_ELEMENT* element_row = GEN_USERINTERFACE.Element_Get(navrownames[c], UI_ELEMENT_TYPE_FORM);
      if(element_row)
        {
          element_row->SetSelected(isactive);
          // Redraw the row (accent + label) only -- not the overlay nav-*-btn. Forcing the buttons to
          // redraw at Ini/SelectSection made them OptionBackdrop-capture before/without nav ink and then
          // keep restoring a blank strip (video: sidebar empty until click).
          GEN_USERINTERFACE.Elements_SetToRedraw(element_row, true);
        }
    }

  currentsectionID = sectionID;

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

  //--------------------------------------------------------------------------------------
  // Every field read below is also written by HardwareInfo_Compute(), on the background
  // thread (see the note in UI_System.h) -- this runs on the main thread (called from inside
  // GEN_USERINTERFACE.Update(), during DrawFrame()'s redraw), so it needs the same mutex to
  // avoid reading a string the background thread is mid-Set()/Format() on.
  //--------------------------------------------------------------------------------------

  if(hardwareinfomutex) hardwareinfomutex->Lock();

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

  if(hardwareinfomutex) hardwareinfomutex->UnLock();

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

  dashboardloaded                = false;

  hardwareinfothread              = NULL;
  hardwareinfomutex               = NULL;

  hardwareinfoexiting             = false;
  hardwareinfo_forcenext          = false;
  hardwareinfo_haspending         = false;

  cpu_temperaturelevel            = 0.0f;
  cpu_usagelevel                  = 0.0f;
  ram_usagelevel                  = 0.0f;
  isconnected                     = false;

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
