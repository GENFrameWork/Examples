/**-------------------------------------------------------------------------------------------------------------------
*
* @file        Canvas2D.cpp
*
* @class       CANVAS2D
* @brief       GEN Canvas 2D Example class
* @ingroup     GRAPHIC
*
* @author      Abraham J. Velez
* @date       01/03/2016 12:30
*
* @copyright   Copyright(c) 2008 - 2016 GEN Group.
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
#include "GRPXEvent.h"

#include "INPManager.h"

#include "APPLog.h"

#include "Canvas2D_CFG.h"
#include "Canvas2D.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

 APPLICATIONCREATEINSTANCE(CANVAS2D, canvas2d)

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         CANVAS2D::CANVAS2D
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
CANVAS2D::CANVAS2D() :  XFSMACHINE(0)
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         CANVAS2D::~CANVAS2D
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
CANVAS2D::~CANVAS2D()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         CANVAS2D::InitFSMachine
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
bool CANVAS2D::InitFSMachine()
{
  if(!AddState( CANVAS2D_XFSMSTATE_NONE           ,
                CANVAS2D_XFSMEVENT_INI            , CANVAS2D_XFSMSTATE_INI          ,
                CANVAS2D_XFSMEVENT_END            , CANVAS2D_XFSMSTATE_END          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( CANVAS2D_XFSMSTATE_INI            ,
                CANVAS2D_XFSMEVENT_NONE           , CANVAS2D_XFSMSTATE_NONE         ,
                CANVAS2D_XFSMEVENT_END            , CANVAS2D_XFSMSTATE_END          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( CANVAS2D_XFSMSTATE_END            ,
                CANVAS2D_XFSMEVENT_NONE           , CANVAS2D_XFSMSTATE_NONE         ,
                CANVAS2D_XFSMEVENT_INI            , CANVAS2D_XFSMSTATE_INI          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         CANVAS2D::AppProc_Ini
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
bool CANVAS2D::AppProc_Ini()
{
  XSTRING string;
  XSTRING stringresult;
//bool    status;

  //-------------------------------------------------------------------------------------------------

  GetApplicationName()->Set(APPLICATION_NAMEAPP);

  SetInitOptions( APPGRAPHICS_INIOPTION_CREATEMAINSCREEN    |
                  APPGRAPHICS_INIOPTION_SHOWMAINSCREEN      |
                  APPGRAPHICS_INIOPTION_INPUT);

  //--------------------------------------------------------------------------------------------------

  // ACTIVATEXTHREADGROUP(XTHREADGROUPID_SCHEDULER);
  // ACTIVATEXTHREADGROUP(XTHREADGROUPID_DIOSTREAM);

  //--------------------------------------------------------------------------------------------------

  XTRACE_SETAPPLICATIONNAME((*GetApplicationName()));
  XTRACE_SETAPPLICATIONVERSION(APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR);
  XTRACE_SETAPPLICATIONID(string);

  //--------------------------------------------------------------------------------------------------

  GEN_XPATHSMANAGER.AdjustRootPathDefault(APPDEFAULT_DIRECTORY_ROOT);

  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_GRAPHICS      , APPDEFAULT_DIRECTORY_GRAPHICS);
  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_FONTS         , APPDEFAULT_DIRECTORY_FONTS);
  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_UI_LAYOUTS    , APPDEFAULT_DIRECTORY_UI_LAYOUTS);


  GEN_XPATHSMANAGER.CreateAllPathSectionOnDisk();

  //--------------------------------------------------------------------------------------------------

  InitFSMachine();

  //--------------------------------------------------------------------------------------

  xtimer = GEN_XFACTORY.CreateTimer();
  if(!xtimer) return false;

  //--------------------------------------------------------------------------------------

  /*
  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathsection);
  xpath.Create(3 , xpathsection.Get(), SCRIPTS_LNG_NAMEFILE, XTRANSLATION_NAMEFILEEXT);

  if(!GEN_XTRANSLATION.Ini(xpath))
    {
      return false;
    }
  */

  GEN_XTRANSLATION.SetActual(XLANGUAGE_ISO_639_3_CODE_SPA);

  //--------------------------------------------------------------------------------------

  APP_CFG.SetAutomaticTraceTargets();

  //--------------------------------------------------------------------------------------

  if(APP_CFG.Log_IsActive())
    {
      APP_LOG.Ini(&APP_CFG, APPLICATION_NAMEFILE , APPLICATION_VERSION
                                                 , APPLICATION_SUBVERSION
                                                 , APPLICATION_SUBVERSIONERR);
    }

  //--------------------------------------------------------------------------------------

  SetEvent(CANVAS2D_XFSMEVENT_INI);

  return true;
}






/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         CANVAS2D::AppProc_FirstUpdate
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
bool CANVAS2D::AppProc_FirstUpdate()
{
  //--------------------------------------------------------------------------------------

  INPDEVICE* inpdevice;

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_KEYBOARD);
  if(inpdevice)
    {
      button[CANVAS2D_BUTTON_UP]      = inpdevice->GetButton(INPBUTTON_ID_UP);
      button[CANVAS2D_BUTTON_DOWN]    = inpdevice->GetButton(INPBUTTON_ID_DOWN);
      button[CANVAS2D_BUTTON_LEFT]    = inpdevice->GetButton(INPBUTTON_ID_LEFT);
      button[CANVAS2D_BUTTON_RIGHT]   = inpdevice->GetButton(INPBUTTON_ID_RIGHT);
      button[CANVAS2D_BUTTON_SPACE]   = inpdevice->GetButton(INPBUTTON_ID_SPACE);
      button[CANVAS2D_BUTTON_ESC]     = inpdevice->GetButton(INPBUTTON_ID_ESCAPE);
      button[CANVAS2D_BUTTON_MOUSE]   = inpdevice->GetButton(INPBUTTON_ID_MOUSE_RIGHT);
    }

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_MOUSE);
  if(inpdevice)
    {
      button[CANVAS2D_BUTTON_MOUSE] = inpdevice->GetButton(INPBUTTON_ID_MOUSE_LEFT);
      cursor = inpdevice->GetCursor(0);
    }

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_TOUCHSCREEN);
  if(inpdevice)
    {     
      button[CANVAS2D_BUTTON_TOUCHSCREEN] = inpdevice->GetButton(INPBUTTON_ID_TOUCHSCREEN);     
      cursor = inpdevice->GetCursor(0);
    }  

  //--------------------------------------------------------------------------------

  GRPVIEWPORT*      viewport = NULL;
  GRPCANVAS*        canvas   = NULL;

  viewport = GetMainScreen()->GetViewport(0);
  if(viewport) canvas =   viewport->GetCanvas();

  if(canvas)
    {
      if(backgroundbmp) canvas->PutBitmapNoAlpha(0, 0, backgroundbmp);

      canvas->RasterFont_Select(__L("verdana18"));
    }

  //--------------------------------------------------------------------------------

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         CANVAS2D::AppProc_Update
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
bool CANVAS2D::AppProc_Update()
{
  if(GetEvent()==CANVAS2D_XFSMEVENT_NONE) // Not new event
    {
      switch(GetCurrentState())
        {
          case CANVAS2D_XFSMSTATE_NONE      : break;

          case CANVAS2D_XFSMSTATE_INI       : { 
                                                UpdateInput();

                                                DrawFrame();

                                                GetMainScreen()->UpdateViewports();
                                              }
                                              break;

          case CANVAS2D_XFSMSTATE_END       : break;

        }
    }
   else //  New event
    {
      if(GetEvent()<CANVAS2D_LASTEVENT)
        {
          CheckTransition();

          switch(GetCurrentState())
            {
              case CANVAS2D_XFSMSTATE_NONE  : break;

              case CANVAS2D_XFSMSTATE_INI   : break;

              case CANVAS2D_XFSMSTATE_END   : break;
            }
        }
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         CANVAS2D::AppProc_End
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
bool CANVAS2D::AppProc_End()
{
  XSTRING string;
  XSTRING stringresult;

  //--------------------------------------------------------------------------------------

  SetCurrentState(CANVAS2D_XFSMSTATE_END);

  //--------------------------------------------------------------------------------------

  if(backgroundbmp)
    {
      delete backgroundbmp;
      backgroundbmp = NULL;
    }

  if(testbmp)
    {
      delete testbmp;
      testbmp = NULL;
    }

  if(charactersecuence)
    {
      delete charactersecuence;
      charactersecuence = NULL;
    }

  //--------------------------------------------------------------------------------------

  if(xtimer)
    {
      GEN_XFACTORY.DeleteTimer(xtimer);
      xtimer = NULL;
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
* @fn         bool CANVAS2D::UpdateInput()
* @brief      UpdateInput
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool CANVAS2D::UpdateInput()
{
 
  if(cursor)
    {     
      if(cursor->GetMotion()->IsReadyToTest())
        {
          INPCURSORMOTION_DIR motiondir = cursor->GetMotion()->GetDirectionByAngle(true);
          if(motiondir != INPCURSORMOTION_DIR_UNKNOWN)
            {
              switch(motiondir)
                {
                  case INPCURSORMOTION_DIR_DOWN       :
                  case INPCURSORMOTION_DIR_RIGHTUP    : makeaction = __L("WALK NORTH");
                                                        break;

                  case INPCURSORMOTION_DIR_RIGHT      :
                  case INPCURSORMOTION_DIR_LEFTUP     : makeaction = __L("WALK WEST" );
                                                        break;

                  case INPCURSORMOTION_DIR_LEFT       :
                  case INPCURSORMOTION_DIR_RIGHTDOWN  : makeaction = __L("WALK EAST" );
                                                        break;

                  case INPCURSORMOTION_DIR_UP         :
                  case INPCURSORMOTION_DIR_LEFTDOWN   : makeaction = __L("WALK SOUTH");
                                                        break;

                                          default     : break;
                }

              cursor->GetMotion()->Reset();
            }
        }
    }


  for(int c=0;c<CANVAS2D_BUTTON_MAX;c++)
    {
      if(button[c])
        {
          if(button[c]->IsPressedWithRelease())
            {
              switch(c)
                {
                  case CANVAS2D_BUTTON_ESC      : SetExitType(APPBASE_EXITTYPE_BY_USER);
                                                  break;
                }
            }

          if(button[c]->IsPressed())
            {
              switch(c)
                {
                  case CANVAS2D_BUTTON_UP     : makeaction = __L("WALK NORTH");   break;
                  case CANVAS2D_BUTTON_DOWN   : makeaction = __L("WALK SOUTH");   break;
                  case CANVAS2D_BUTTON_LEFT   : makeaction = __L("WALK WEST" );   break;
                  case CANVAS2D_BUTTON_RIGHT  : makeaction = __L("WALK EAST" );   break;
                  case CANVAS2D_BUTTON_SPACE  : break;
                }
            }
        }
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CANVAS2D::Ini_Graphics(GRPSCREEN* screen)
* @brief      Ini_Graphics
* @ingroup    GRAPHIC
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:30
* 
* @param[in]  screen : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool CANVAS2D::Ini_Graphics(GRPSCREEN* screen)
{
  //--------------------------------------------------------------------------------------

  XPATH           xpath;
  GRPBITMAPFILE*  bitmapfile;

  bitmapfile = new GRPBITMAPFILE();
  if(!bitmapfile) return false;

  if(!backgroundbmp)
    {
      GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_GRAPHICS, xpath);
      xpath.Slash_Add();
      xpath.Add(__L("background.jpg"));

      backgroundbmp = bitmapfile->Load(xpath, GetMainScreen()->GetMode());
      if(!backgroundbmp) return false;
    }
   

  if(!testbmp)
    {
      GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_GRAPHICS, xpath);
      xpath.Slash_Add();
      xpath.Add(__L("test.tga"));
      testbmp = bitmapfile->Load(xpath);
    }

  
  if(!charactersecuence)
    {
      GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_GRAPHICS, xpath);
      xpath.Slash_Add();
      xpath.Add(__L("gigolord_walk0"));

      bitmapfile->SetPath(xpath);

      charactersecuence = bitmapfile->LoadSequence(__L("LF-WxWalk_01%02d.png"), 1);

      if(charactersecuence) charactersecuence->Play();
    }

  delete bitmapfile;

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Main Screen: Width %d, height %d"),  screen->GetWidth(), screen->GetHeight());


  #ifndef ANDROID 
  if(backgroundbmp)
    {
      screen->SetWidth(backgroundbmp->GetWidth());
      screen->SetHeight(backgroundbmp->GetHeight());
    }
    else
    {
      screen->SetHeight(1024);
      screen->SetHeight(768);
    } 

  GetMainScreen()->CreateViewport(GRPVIEWPORT_ID_MAIN , 0.0f, 0.0f, (float)screen->GetWidth()   , (float)screen->GetHeight(),  0,  0, (backgroundbmp->GetWidth()) , (backgroundbmp->GetHeight()));

  #else

  screen->SetWidth(1024);
  screen->SetHeight(768);  
 
  #endif 
 

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool CANVAS2D::DrawFrame()
* @brief      DrawFrame
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool CANVAS2D::DrawFrame()
{
  GRP2DCOLOR_RGBA8  colorblack(0, 0, 0);
  GRP2DCOLOR_RGBA8  colorwhite(255, 255, 255);
  GRP2DCOLOR_RGBA8  colorred(255, 0, 0);
  GRP2DCOLOR_RGBA8  colorgreen(0, 255, 0);
  GRP2DCOLOR_RGBA8  colorblue(0, 0, 255);
  GRP2DCOLOR_RGBA8  colorgray(10, 10, 10, 150);

  GRPVIEWPORT*      viewport = NULL;
  GRPCANVAS*        canvas   = NULL;
  GRPRECTINT*       rect     = NULL;

  viewport = GetMainScreen()->GetViewport(0);
  if(viewport) canvas =   viewport->GetCanvas();
  if(!canvas) return false;

  int width  = GetMainScreen()->GetWidth();
  int height = GetMainScreen()->GetHeight();

  canvas->ReleaseDrawFramerate();  

  rect = canvas->GetScreenZone();
  if(rect)
    {
      if(makeaction.Compare(__L("WALK NORTH"), true))   { rect->y1++; rect->y2++; }
      if(makeaction.Compare(__L("WALK WEST" ), true))   { rect->x1++; rect->x2++; }
      if(makeaction.Compare(__L("WALK EAST" ), true))   { rect->x1--; rect->x2--; }
      if(makeaction.Compare(__L("WALK SOUTH"), true))   { rect->y1--; rect->y2--; }
    }

  if(rect->x1 < 0)
    {
      rect->x1 = 0;
      rect->x2 = width;
      makeaction.Empty();
    }

  if(rect->y1 < 0)
    {
      rect->y1 = 0;
      rect->y2 = height;
      makeaction.Empty();
    }

  if((rect->x1 + width) > (int)canvas->GetWidth())
    {
      rect->x2 = canvas->GetWidth();
      rect->x1 = rect->x2 - width;
    }

  if((rect->y1 + height) > (int)canvas->GetHeight())
    {
      rect->y2 = canvas->GetHeight();
      rect->y1 = rect->y2 - height;
    }

  //canvas->Clear(&colorwhite);  

  canvas->RebuildAllAreas();
  canvas->DeleteAllRebuildAreas();

  static int x = 950;
  static int y = 310;

  canvas->CreateRebuildArea(x, y, charactersecuence->GetActualFrame()->GetBitmap()->GetWidth(), charactersecuence->GetActualFrame()->GetBitmap()->GetHeight());
  canvas->PutBitmapFrame(x, y, charactersecuence->GetActualFrame());

  if(xtimer->GetMeasureMilliSeconds() > 30)
    {
      charactersecuence->Update();
      xtimer->Reset();
      x -= 4;
      if(x<-100) x = 950;
    }



  canvas->CreateRebuildArea(rect->x1 + 50, 50, rect->x1 + 450, 150);

  canvas->SetLineWidth(1.5f);
  canvas->SetLineColor(&colorwhite);
  canvas->SetFillColor(&colorgray);

  canvas->RoundRect(rect->x1 + 50, 50, rect->x1 + 450, 150, 20, true);


  canvas->RasterFont_SetColor(&colorwhite);
  canvas->RasterFont_Printf(rect->x1 + 60, 80, __L("Erase una vez ... "));


  canvas->DrawFramerate(2,20, GetMainScreen());

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void CANVAS2D::Graphics_HandleEvent(GRPXEVENT* event)
* @brief      Graphics_HandleEvent
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param[in]  event :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void CANVAS2D::HandleEvent_Graphics(GRPXEVENT* event)
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
* @fn         CANVAS2D::HandleEvent
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
void CANVAS2D::HandleEvent(XEVENT* xevent)
{
  if(!xevent) return;

  switch(xevent->GetEventFamily())
    {
      case XEVENT_TYPE_GRAPHICS       : { GRPXEVENT* event = (GRPXEVENT*)xevent;
                                          if(!event) return;

                                          HandleEvent_Graphics(event);
                                        }
                                        break;
    }
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void CANVAS2D::Clean()
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
void CANVAS2D::Clean()
{
  xtimer                      = NULL;

  for(int c=0; c<CANVAS2D_BUTTON_MAX; c++)
    {
      button[c] = NULL;
    }

  cursor                      = NULL;

  backgroundbmp               = NULL;
  testbmp                     = NULL;
  charactersecuence           = NULL;
}
