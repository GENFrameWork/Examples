/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_Options.cpp
* 
* @class      UI_OPTIONS
* @brief      Graphics UI Options Example class
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

#include "UI_Options.h"

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
#include "XThreadCollected.h"
#include "XThread.h"
#include "XTrace.h"

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

#include "GRPCanvas.h"
#include "GRPScreen.h"
#include "GRPViewPort.h"
#include "GRPBitmapFile.h"
#include "GRPBitmapFileJPG.h"
#include "GRPVideoFileAVI.h"
#include "GRPXEvent.h"

#include "INPManager.h"

#include "UI_XEvent.h"
#include "UI_Manager.h"
#include "UI_Element.h"
#include "UI_Element_Animation.h"
#include "UI_Element_Option.h"
#include "UI_Element_Menu.h"
#include "UI_Element_ListBox.h"
#include "UI_Element_Button.h"
#include "UI_Element_ProgressBar.h"
#include "UI_SkinCanvas.h"

#include "APPFlowLog.h"
#include "APPFlowExtended.h"

#include "UI_Options_CFG.h"
#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

 APPLICATIONCREATEINSTANCE(UI_OPTIONS, canvas2d)

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         UI_OPTIONS::UI_OPTIONS
* @brief      Constructor
* @ingroup
*
* @param
* @return
*
*---------------------------------------------------------------------------------------------------------------------*/
UI_OPTIONS::UI_OPTIONS() :  XFSMACHINE(0)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         UI_OPTIONS::~UI_OPTIONS
* @brief      Destructor
* @ingroup
*
* @param
* @return
*
*---------------------------------------------------------------------------------------------------------------------*/
UI_OPTIONS::~UI_OPTIONS()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         UI_OPTIONS::InitFSMachine
* @brief      Init FS Machine
* @ingroup
*
* @param
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_OPTIONS::InitFSMachine()
{
  if(!AddState( UI_OPTIONS_XFSMSTATE_NONE           ,
                UI_OPTIONS_XFSMEVENT_INI            , UI_OPTIONS_XFSMSTATE_INI          ,
                UI_OPTIONS_XFSMEVENT_END            , UI_OPTIONS_XFSMSTATE_END          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( UI_OPTIONS_XFSMSTATE_INI            ,
                UI_OPTIONS_XFSMEVENT_NONE           , UI_OPTIONS_XFSMSTATE_NONE         ,
                UI_OPTIONS_XFSMEVENT_END            , UI_OPTIONS_XFSMSTATE_END          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( UI_OPTIONS_XFSMSTATE_END            ,
                UI_OPTIONS_XFSMEVENT_NONE           , UI_OPTIONS_XFSMSTATE_NONE         ,
                UI_OPTIONS_XFSMEVENT_INI            , UI_OPTIONS_XFSMSTATE_INI          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         UI_OPTIONS::AppProc_Ini
* @brief      Ini Application
* @ingroup
*
* @param
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_OPTIONS::AppProc_Ini()
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

  // ACTIVATEXTHREADGROUP(XTHREADGROUPID_SCHEDULER);
  // ACTIVATEXTHREADGROUP(XTHREADGROUPID_DIOSTREAM);

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

    GEN_XTRANSLATION.SetActual(XLANGUAGE_ISO_639_3_CODE_ENG);
  }

  //--------------------------------------------------------------------------------------

  APPFLOW_CFG_SETAUTOMATICTRACETARGETS

  //--------------------------------------------------------------------------------------

  APPFLOW_EXTENDED.APPStart(&APPFLOW_CFG);

  //--------------------------------------------------------------------------------------

  SetEvent(UI_OPTIONS_XFSMEVENT_INI);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         UI_OPTIONS::AppProc_FirstUpdate
* @brief      First Update
* @ingroup
*
* @param
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_OPTIONS::AppProc_FirstUpdate()
{
  //--------------------------------------------------------------------------------------

  INPDEVICE* inpdevice;

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_KEYBOARD);
  if(inpdevice)
    {
      button[UI_OPTIONS_BUTTON_UP]      = inpdevice->GetButton(INPBUTTON_ID_UP);
      button[UI_OPTIONS_BUTTON_DOWN]    = inpdevice->GetButton(INPBUTTON_ID_DOWN);
      button[UI_OPTIONS_BUTTON_LEFT]    = inpdevice->GetButton(INPBUTTON_ID_LEFT);
      button[UI_OPTIONS_BUTTON_RIGHT]   = inpdevice->GetButton(INPBUTTON_ID_RIGHT);
      button[UI_OPTIONS_BUTTON_SPACE]   = inpdevice->GetButton(INPBUTTON_ID_SPACE);
      button[UI_OPTIONS_BUTTON_ESC]     = inpdevice->GetButton(INPBUTTON_ID_ESCAPE);
      button[UI_OPTIONS_BUTTON_F1]      = inpdevice->GetButton(INPBUTTON_ID_F1);
      button[UI_OPTIONS_BUTTON_F2]      = inpdevice->GetButton(INPBUTTON_ID_F2);
      button[UI_OPTIONS_BUTTON_F5]      = inpdevice->GetButton(INPBUTTON_ID_F5);
      button[UI_OPTIONS_BUTTON_F9]      = inpdevice->GetButton(INPBUTTON_ID_F9);
      button[UI_OPTIONS_BUTTON_MINUS]   = inpdevice->GetButton(INPBUTTON_ID_WIIMOTE_MINUS);
      button[UI_OPTIONS_BUTTON_PLUS]    = inpdevice->GetButton(INPBUTTON_ID_WIIMOTE_PLUS);

      button[UI_OPTIONS_BUTTON_MOUSE]   = inpdevice->GetButton(INPBUTTON_ID_MOUSE_RIGHT);
    }

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_MOUSE);
  if(inpdevice)
    {
      button[UI_OPTIONS_BUTTON_MOUSE] = inpdevice->GetButton(INPBUTTON_ID_MOUSE_LEFT);
      cursor = inpdevice->GetCursor(0);
    }

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_TOUCHSCREEN);
  if(inpdevice)
    {     
      button[UI_OPTIONS_BUTTON_TOUCHSCREEN] = inpdevice->GetButton(INPBUTTON_ID_TOUCHSCREEN);     
      cursor = inpdevice->GetCursor(0);
    }

  //--------------------------------------------------------------------------------------

  if(!Ini_UserInterface(true)) return false;

  //--------------------------------------------------------------------------------------
  
  xrand  = GEN_XFACTORY.CreateRand();
  if(!xrand)  return false;

  //--------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         UI_OPTIONS::AppProc_Update
* @brief      Update Application
* @ingroup
*
* @param
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_OPTIONS::AppProc_Update()
{
  if(GetEvent()==UI_OPTIONS_XFSMEVENT_NONE) // Not new event
    {
      switch(GetCurrentState())
        {
          case UI_OPTIONS_XFSMSTATE_NONE      : break;

          case UI_OPTIONS_XFSMSTATE_INI       : UpdateInput();
                                                DrawFrame();
                                                GetMainScreen()->UpdateViewports();
                                                break;

          case UI_OPTIONS_XFSMSTATE_END       : break;

        }
    }
   else //  New event
    {
      if(GetEvent()<UI_OPTIONS_LASTEVENT)
        {
          CheckTransition();

          switch(GetCurrentState())
            {
              case UI_OPTIONS_XFSMSTATE_NONE  : break;

              case UI_OPTIONS_XFSMSTATE_INI   : break;

              case UI_OPTIONS_XFSMSTATE_END   : break;
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         UI_OPTIONS::AppProc_End
* @brief      End Application
* @ingroup
*
* @param
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_OPTIONS::AppProc_End()
{
  XSTRING string;
  XSTRING stringresult;

  //--------------------------------------------------------------------------------------

  SetCurrentState(UI_OPTIONS_XFSMSTATE_END);

  //--------------------------------------------------------------------------------------
  
  Ini_UserInterface(false);

  //--------------------------------------------------------------------------------------

  if(testbmp)
    {
      delete testbmp;
      testbmp = NULL;
    }

  //--------------------------------------------------------------------------------------

  if(xrand)
    {
      GEN_XFACTORY.DeleteRand(xrand);
      xrand = NULL;  
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
* @fn         bool UI_OPTIONS::UpdateInput()
* @brief      UpdateInput
* @ingroup
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_OPTIONS::UpdateInput()
{
   int  width  = GetMainScreen()->GetWidth();
   int  height = GetMainScreen()->GetHeight();

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

              if(button[UI_OPTIONS_BUTTON_MOUSE]->IsPressedWithRelease())
                {
                  GEN_USERINTERFACE.SendEvent(UI_XEVENT_TYPE_INPUT_SELECCTION,  cursor_x,  cursor_y);   

                  cursor->GetMotion()->Reset();       
                }
    
              if(button[UI_OPTIONS_BUTTON_TOUCHSCREEN])
                {             
                  if(button[UI_OPTIONS_BUTTON_TOUCHSCREEN]->IsPressed())
                    {             
                      GEN_USERINTERFACE.SendEvent(UI_XEVENT_TYPE_INPUT_CURSOR_MOVE,  cursor_x,  cursor_y);
                      GEN_USERINTERFACE.SendEvent(UI_XEVENT_TYPE_INPUT_SELECCTION,   cursor_x, cursor_y);          

                      cursor->GetMotion()->Reset();
                    }
                }
            }
        }
    }


  for(int c=0; c<UI_OPTIONS_BUTTON_MOUSE; c++)
    {
      if(button[c])
        {
          if(button[c]->IsPressedWithRelease())
            {
              switch(c)
                {
                  
                  case UI_OPTIONS_BUTTON_F1       : { UI_ELEMENT_PROGRESSBAR* element_progressbar = (UI_ELEMENT_PROGRESSBAR*)GEN_USERINTERFACE.Element_Get(__L("progressbarID"), UI_ELEMENT_TYPE_PROGRESSBAR);
                                                      if(element_progressbar) 
                                                        { 
                                                          float level =element_progressbar->GetLevel();
                                                          level++;                                                          
                                                          element_progressbar->SetLevel(level);

                                                          GEN_USERINTERFACE.Elements_SetToRedraw(element_progressbar); 
                                                        }
                                                    }
                                                    break;

                  case UI_OPTIONS_BUTTON_F2       : { UI_ELEMENT_PROGRESSBAR* element_progressbar = (UI_ELEMENT_PROGRESSBAR*)GEN_USERINTERFACE.Element_Get(__L("progressbarID"), UI_ELEMENT_TYPE_PROGRESSBAR);
                                                      if(element_progressbar) 
                                                        { 
                                                          float level =element_progressbar->GetLevel();
                                                          level--;                                                          
                                                          element_progressbar->SetLevel(level);

                                                          GEN_USERINTERFACE.Elements_SetToRedraw(element_progressbar); 
                                                        }
                                                    }
                                                    break;
                            
                  case UI_OPTIONS_BUTTON_F5       : Ini_UserInterface(false);
                                                    Ini_UserInterface(true);                      
                                                    break;

                  case UI_OPTIONS_BUTTON_F9       : { 
                                                      /*  
                                                      static bool on = false;

                                                      UI_ELEMENT_ANIMATION* element = (UI_ELEMENT_ANIMATION*)GEN_USERINTERFACE.GetElement(__L("image"), UI_ELEMENT_TYPE_ANIMATION);
                                                      if(element) element->SetVisible(on);      

                                                      on = !on;
                                                      */ 

                                                      // UnitTest_AVIVideoWrite();
                                                    }
                                                    break;

                  case UI_OPTIONS_BUTTON_ESC      : SetExitType(APPFLOWBASE_EXITTYPE_BY_USER);
                                                    break;
                }
            }

          if(button[c]->IsPressed())
            {
              switch(c)
                {
                  case UI_OPTIONS_BUTTON_UP     : 
                  case UI_OPTIONS_BUTTON_DOWN   : { UI_ELEMENT_MENU* element_menu = (UI_ELEMENT_MENU*)GEN_USERINTERFACE.Element_Get(__L("ListBoxMenuID"), UI_ELEMENT_TYPE_MENU);
                                                    if(element_menu) 
                                                      {                                                                                                                         
                                                        UI_PROPERTY_SCROLLEABLE* property_scrolleable = dynamic_cast<UI_PROPERTY_SCROLLEABLE*>(element_menu);
                                                        if(property_scrolleable) 
                                                          {
                                                            property_scrolleable->Scroll_SetStep(UI_PROPERTY_SCROLLEABLE_TYPE_VERTICAL, ((c==UI_OPTIONS_BUTTON_DOWN)?1:-1));   
                                                            GEN_USERINTERFACE.Elements_SetToRedraw(element_menu);                                                                                                                 
                                                          }
                                                                                                                                                                        
                                                      }
                                                  }
                                                  break;    

                  case UI_OPTIONS_BUTTON_LEFT   : makeaction = __L("WALK WEST" );   break;
                  case UI_OPTIONS_BUTTON_RIGHT  : makeaction = __L("WALK EAST" );   break;
                  case UI_OPTIONS_BUTTON_SPACE  : break;
                  
                }
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_OPTIONS::Ini_Graphics(GRPSCREEN* screen)
* @brief      Ini_Graphics
* @ingroup    GRAPHIC
* 
* 
* @param[in]  screen : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_OPTIONS::Ini_Graphics(GRPSCREEN* screen)
{
  screen->SetWidth(1024);
  screen->SetHeight(768);

  screen->GetTitle()->Set(__L("User Interface Canvas"));  
  screen->SetDesktopScreenSelected(GRPSCREENTYPE_DESKTOP_MAIN);

  GetMainScreen()->CreateViewport(GRPVIEWPORT_ID_MAIN , 0.0f, 0.0f, (float)screen->GetWidth()   , (float)screen->GetHeight(), 0, 0, (screen->GetWidth()), (screen->GetHeight()));
                                          
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_OPTIONS::Ini_UserInterface(bool on)
* @brief      Ini_UserInterface
* @ingroup    GRAPHIC
* 
* 
* @param[in]  on : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_OPTIONS::Ini_UserInterface(bool on)
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
  GRPCANVAS*    canvas    = NULL;
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
  xpath.Add(__L("example.zip"));
    
  if(!GEN_USERINTERFACE.Load(xpath, screen, 0)) 
    {
      return false;
    }

  GEN_USERINTERFACE.SubscribeInputEvents(true);
  GEN_USERINTERFACE.SubscribeOutputEvents(true, this, &GEN_USERINTERFACE.GetInstance());   

  GEN_USERINTERFACE.CreaterVirtualKeyboard(GEN_USERINTERFACE.Layouts_Get(__L("example")), screen);   

  GEN_USERINTERFACE.Layout_PutBackground();

  GEN_USERINTERFACE.Elements_SetToRedraw();
        
  UI_ELEMENT_MENU* element_menu = (UI_ELEMENT_MENU*)GEN_USERINTERFACE.Element_Get(__L("ListBoxMenuID"), UI_ELEMENT_TYPE_MENU);
  if(element_menu)
    {
      XSTRING                     option_text; 
      double                      option_marginheight = 10; 
      double                      option_height       = 35; 
      UI_ELEMENT_MENU_OPTION_CFG  option_cfg;

      for(int c=0; c<8; c++)
        {      
          option_text.Format(__L("Option %02d"), c+1);

          option_cfg.index        = c+1;
          option_cfg.nameoption   = option_text.Get();
          option_cfg.leyend       = option_text.Get();
          option_cfg.colorstr     = __L("white,255");
          option_cfg.sizefont     = 22;
          option_cfg.marginwidth  = 10;
          option_cfg.marginheight = 15;
          option_cfg.width        = element_menu->GetBoundaryLine()->width-30;
          option_cfg.height       = option_height;

          UI_ELEMENT_OPTION* element_option = element_menu->Option_AddText(option_cfg);   
          if(element_option)
            {
              //element_option->SetVisibleLimitType(element_option->GetVisibleLimitType() | UI_ELEMENT_OPTION_VISIBLE_LIMIT_ACTIVE);     
              //element_option->SetVisibleLimitType(element_option->GetVisibleLimitType() | UI_ELEMENT_OPTION_VISIBLE_LIMIT_DEACTIVE);
              element_option->SetVisibleLimitType(element_option->GetVisibleLimitType() | UI_ELEMENT_OPTION_VISIBLE_LIMIT_PRESELECT);
              element_option->SetVisibleLimitType(element_option->GetVisibleLimitType() | UI_ELEMENT_OPTION_VISIBLE_LIMIT_SELECT);                          
            }
        }
                     
      GEN_USERINTERFACE.Layouts_Get(__L("example"))->GetSkin()->CalculeBoundaryLine_AllElements(element_menu, true); 

      UI_PROPERTY_SCROLLEABLE* property_scrolleable = dynamic_cast<UI_PROPERTY_SCROLLEABLE*>(element_menu);
      if(property_scrolleable) 
        {
          //property_scrolleable->SetLimit(UI_PROPERTY_SCROLLEABLE_TYPE_VERTICAL, -((double)element_menu->GetComposeElements()->GetSize() * (double)(option_height-option_marginheight)) - option_marginheight);

          //double fullheight = (option_cfg.height + option_cfg.marginheight);  
          double fullheight = (element_menu->GetComposeElements()->GetSize() * (option_height + option_cfg.marginheight))  - element_menu->GetBoundaryLine()->height + option_cfg.marginheight;
          property_scrolleable->Scroll_SetLimit(UI_PROPERTY_SCROLLEABLE_TYPE_VERTICAL, -fullheight);
        }
          
      element_menu->GetVisibleRect()->CopyFrom((*element_menu->GetBoundaryLine()));
      element_menu->GetVisibleRect()->x = element_menu->GetXPosition();
      element_menu->GetVisibleRect()->y = element_menu->GetYPosition();
    
      element_menu->SetFather(NULL);   

      //UI_ELEMENT_PROGRESSBAR* element_progressbar = (UI_ELEMENT_PROGRESSBAR*)GEN_USERINTERFACE.GetElement(__L("progressbarID"), UI_ELEMENT_TYPE_PROGRESSBAR);
      //if(element_progressbar)  element_progressbar->ContinuousCycle_Set(true, 33, 10, 10); 
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_OPTIONS::DrawFrame()
* @brief      DrawFrame
* @ingroup
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_OPTIONS::DrawFrame()
{
  GRP2DCOLOR_RGBA8  colorblack(0, 0, 0);
  GRP2DCOLOR_RGBA8  colorwhite(255, 255, 255);
  GRP2DCOLOR_RGBA8  colorred(255, 0, 0);
  GRP2DCOLOR_RGBA8  colorgreen(0, 255, 0);
  GRP2DCOLOR_RGBA8  colorblue(0, 0, 255);
  GRP2DCOLOR_RGBA8  colorgray(10, 10, 10, 150);

  GRPSCREEN*    screen    = NULL;
  GRPVIEWPORT*  viewport  = NULL;
  GRPCANVAS*    canvas    = NULL;
  int           width     = 0;
  int           height    = 0;


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

  canvas =   viewport->GetCanvas();
  if(!canvas) 
    {
      return false;
    }
 
  width  = screen->GetWidth();
  height = screen->GetHeight();

  canvas->ReleaseDrawFramerate();

  /*
  static double x_pos = -150;
  static double y_pos =  400;
  static bool  direction = true;

  if(direction)
    {
      if(x_pos < 400)  x_pos+=5;  else  direction = false;
    }
   else 
    {
      if(x_pos > -150)  x_pos-=5;  else  direction = true;
    }

  //y_pos += xrand->Between(1,4) - xrand->Between(1,4);

  UI_ELEMENT_MENU* element_menu = (UI_ELEMENT_MENU*)GEN_USERINTERFACE.GetElement(__L("ListBoxMenuID"), UI_ELEMENT_TYPE_MENU);
  if(element_menu)
    {
      GEN_USERINTERFACE.Skin_Selected()->SetElementPosition(element_menu, x_pos, y_pos);
    }
  */

  UI_ELEMENT_BUTTON* element_button_mainmenu = (UI_ELEMENT_BUTTON*)GEN_USERINTERFACE.Element_Get(__L("menu-btn"), UI_ELEMENT_TYPE_BUTTON);
  if(element_button_mainmenu) GEN_USERINTERFACE.Elements_SetToRedraw(element_button_mainmenu);    


/*
  GRP2DCOLOR_RGBA8  linecolor(0, 0, 0, 100);
  GRP2DCOLOR_RGBA8  bkgcolor (255, 255,  255, 100);
          
  canvas->SetLineColor(&linecolor);
  canvas->SetFillColor(&bkgcolor);

  canvas->Rectangle(100, 100, 250, 150, true);
  */
  
  GEN_USERINTERFACE.Elements_RebuildDrawAreas();
  
  GEN_USERINTERFACE.Update();

  canvas->DrawFramerate(screen, 6, 20);

  // --------------------------------------------------------------------
  // center

  /*
  canvas->SetLineWidth(0.5f);
  canvas->SetLineColor(&colorblue);
  canvas->Circle((width/2), (height/2), 5);               
  canvas->PutPixel((width/2), (height/2), &colorblack);               
  */

  // --------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_OPTIONS::UserInterface_ElementSelected(UI_ELEMENT* element)
* @brief      UserInterface_ElementSelected
* @ingroup    
* 
* 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_OPTIONS::UserInterface_ElementSelected(UI_ELEMENT* element)
{
  if(!element) return false;

  XSTRING elementname;

  elementname = element->GetName()->Get();

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("UI Element [%s]: Selected! "), element->GetName()->Get());
                                                            
  if(!elementname.Compare(__L("menu-btn"), true))
    {
      UI_LAYOUT* layout = GEN_USERINTERFACE.Layouts_Get(__L("example"));
      if(layout) 
        {
          UI_ELEMENT* _element = layout->Elements_Get(__L("menu_horz"));
          if(_element)
            {                                                                                                                                           
              _element->SetVisible(!_element->IsVisible());   
            }  
        }
    } 
                                                      
  if(elementname.Find(__L("ListBoxMenuButtonID"), true) != XSTRING_NOTFOUND)
    {
      UI_LAYOUT* layout = GEN_USERINTERFACE.Layouts_Get(__L("example"));
      if(layout) 
        {
          UI_ELEMENT_LISTBOX* element_listbox = (UI_ELEMENT_LISTBOX*)layout->Elements_Get(__L("ListBoxID"));
          if(element_listbox)
            {
              UI_LAYOUT* layout_menu = GEN_USERINTERFACE.Element_GetLayout(__L("ListBoxMenuID"), UI_ELEMENT_TYPE_MENU);

              UI_ELEMENT_TEXT* element_text = (UI_ELEMENT_TEXT*)element->GetComposeElements()->Get(0);
              if(element_text) 
                {
                  element_listbox->GetText()->Set(element_text->GetText()->Get());                                                                       
                  GEN_USERINTERFACE.Elements_SetToRedraw(element_listbox);                                                                    
                }

              GEN_USERINTERFACE.Elements_SetToRedraw();
              GEN_USERINTERFACE.Element_SetModal(NULL);
              if(element->GetFather()) element->GetFather()->SetVisible(false);
            }
        }
    }                        

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_OPTIONS::UserInterface_ChangeLiteralText(UI_ELEMENT_TEXT* element_text, XSTRING* maskvalue, XSTRING* maskresolved)
* @brief      UserInterface_ChangeLiteralText
* @ingroup    
* 
* 
* @param[in]  element_text : 
* @param[in]  maskvalue : 
* @param[in]  maskresolved : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_OPTIONS::UserInterface_ChangeLiteralText(UI_ELEMENT_TEXT* element_text, XSTRING* maskvalue, XSTRING* maskresolved)
{
  if(!element_text)   return false;
  if(!maskvalue)      return false;
  if(!maskresolved)   return false;

  if(!maskvalue->Compare(__L("VERSION"), true))
    {
      maskresolved->Format(__L("%d.%d.%d"), APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR);      
      if(APPLICATION_VERSION < 1) maskresolved->AddFormat(__L(" Beta"));             
    }

  if(!maskvalue->Compare(__L("TEST_TEXT"), true))
    {
      maskresolved->Set(__L("Tests"));      
    }

  if(!maskvalue->Compare(__L("TEST_TEXT2"), true))
    {
      static int counter = 0;

      maskresolved->Format(__L("%d"), counter);      

      counter++;
    }
 
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_OPTIONS::UnitTest_AVIVideoWrite()
* @brief      UnitTest_AVIVideoWrite
* @ingroup    GRAPHIC
* 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_OPTIONS::UnitTest_AVIVideoWrite()
{  
  // -------------------------------------------------------------------------------
  // Write AVI 

  XPATH               xpath;
  XVECTOR<XBUFFER*>   dataimgs;

  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_GRAPHICS, xpath);
  xpath.Slash_Add();
  
  XFILE* fileimg = GEN_XFACTORY.Create_File();
  if(fileimg)  
    {
      XPATH xpath_img;  
      XPATH name_img;  

      for(int c=1; c<150; c++)  
        {
          XBUFFER*  dataimg = NULL;
          dataimg = new XBUFFER();
          if(dataimg)
            {
              xpath_img = xpath;

              name_img.Format(__L("frames/ezgif-frame-%03d.jpg"), c);
              xpath_img += name_img;

              if(fileimg->Open(xpath_img))
                { 
                  dataimg->Resize((XDWORD)fileimg->GetSize());

                  fileimg->Read(dataimg->Get(), dataimg->GetSize());

                  fileimg->Close();

                  dataimgs.Add(dataimg);        
                } 
               else 
                { 
                  delete dataimg;
                  break;  
                }         
     
             } 
            else 
             {  
                break;
             }
         }
                                                              
       GEN_XFACTORY.Delete_File(fileimg);      
    }

  GRPVIDEOFILEAVI* xfileAVI;
                                                      
  xfileAVI = new GRPVIDEOFILEAVI();
  if(!xfileAVI) return false;                                         
                     
  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_GRAPHICS, xpath);
  xpath.Slash_Add();
  xpath.Add(__L("prueba.avi"));

  GRPVIDEOFILE_PROPERTYS propertys;

  propertys.width     = 480;
  propertys.height    = 480;
  propertys.codecstr  = __L("MJPG");

  if(xfileAVI->Create(xpath.Get(), propertys))
    {      
      for(int c=0; c<dataimgs.GetSize(); c++)
        {         
          xfileAVI->AddFrame(dataimgs.Get(c)->Get(), dataimgs.Get(c)->GetSize());  
        }

      xfileAVI->Close();
    }

  delete xfileAVI;                                                      

  dataimgs.DeleteContents();
  dataimgs.DeleteAll();  
     
  /*              
  // -------------------------------------------------------------------------------
  // Read AVI 
                                                                                                                                               
  xfileAVI = new GRPVIDEOFILEAVI();
  if(!xfileAVI) return false;

  if(xfileAVI->Open(xpath.Get()))
    {           
      GRPBITMAPFILEJPG  jpg;

      for(int c=0; c<xfileAVI->GetPropertys()->nframes; c++)           
        {
          XDWORD sizeframe  = 0;
          XBYTE* data       = xfileAVI->GetDataFrame(c, sizeframe); 

          GRPBITMAP* bitmap = jpg.CreateBitmapFromBuffer(data, sizeframe, GetMainScreen()->GetMode());
          if(bitmap) 
            {
              GRPSCREEN*   screen   = NULL;
              GRPVIEWPORT* viewport = NULL;
              GRPCANVAS*   canvas   = NULL;  

              screen   = GetMainScreen();
              if(!screen) return false;

              viewport = screen->GetViewport(0);
              if(viewport) canvas = viewport->GetCanvas();
              if(!canvas) return false;
  
              canvas->PutBitmap(10,300, bitmap);      

              delete bitmap;       
            } 

          delete [] data;
        }
                                                              
      xfileAVI->Close();
    }

  delete xfileAVI;
  */
                                                      
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_OPTIONS::HandleEvent_UserInterface(UI_XEVENT* event)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    GRAPHIC
* 
* 
* @param[in]  event : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_OPTIONS::HandleEvent_UserInterface(UI_XEVENT* event)
{
  switch(event->GetEventType())
    {
      case  UI_XEVENT_TYPE_OUTPUT_SELECTED        : { UI_ELEMENT* element = event->GetElement();
                                                      if(element) UserInterface_ElementSelected(element);                                                      
                                                    }
                                                    break;

      case UI_XEVENT_TYPE_OUTPUT_TEXTTOCHANGE     : { UI_ELEMENT_TEXT* element_text = (UI_ELEMENT_TEXT*)event->GetElement();
                                                      XSTRING          maskvalue;
                                                    
                                                      if(UserInterface_ChangeLiteralText(element_text, event->GetMaskTextValue(), event->GetMaskTextResolved()))
                                                        {
                                                        
                                                        }
                                                    } 
                                                    break;

      case UI_XEVENT_TYPE_OUTPUT_CHANGECONTENTS   : { int a=0;
                                                      a++;

                                                    }
                                                    break;
      
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void UI_OPTIONS::Graphics_HandleEvent(GRPXEVENT* event)
* @brief      Graphics_HandleEvent
* @ingroup
*
* @param[in]  event :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void UI_OPTIONS::HandleEvent_Graphics(GRPXEVENT* event)
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
* @fn         UI_OPTIONS::HandleEvent
* @brief      Handle Events
* @ingroup
*
* @param[]    xevent : event send to control
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void UI_OPTIONS::HandleEvent(XEVENT* xevent)
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
* @fn         void UI_OPTIONS::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void UI_OPTIONS::Clean()
{
  xtimer       = NULL;
  xrand        = NULL;

  for(int c=0; c<UI_OPTIONS_BUTTON_MAX; c++)
    {
      button[c] = NULL;
    }
  
  testbmp     = NULL;    
}


#pragma endregion

