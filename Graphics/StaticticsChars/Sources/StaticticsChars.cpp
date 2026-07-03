/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       StaticticsChars.cpp
* 
* @class      STATICTICSCHARS
* @brief      Graphics UI Options Example class
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

#include "StaticticsChars.h"

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

#include "GRP2DCanvas.h"
#include "GRP2DPath.h"
#include "GRPScreen.h"
#include "GRPViewPort.h"
#include "GRPBitmapFile.h"
#include "GRPBitmapFileJPG.h"
#include "GRPVideoFileAVI.h"
#include "GRPVectorFile.h"

#include "GRPStatisticsChartColumns.h"
#include "GRPStatisticsChartLines.h"
#include "GRPStatisticsChartArea.h"
#include "GRPStatisticsChartBars.h"
#include "GRPStatisticsChartStackedColumns.h"
#include "GRPStatisticsChartPie.h"          
#include "GRPStatisticsChartColumns3D.h"
#include "GRPStatisticsChartLines3D.h"
#include "GRPStatisticsChartArea3D.h"
#include "GRPStatisticsChartBuilderSVG.h"

#include "GRPVectorFileSVG.h"
#include "GRPVectorFileSVGObj.h"
#include "GRPXEvent.h"

#include "APPFlowLog.h"
#include "APPFlowExtended.h"

#include "INPManager.h"
#include "INPDevice.h"

#include "StaticticsChars_CFG.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"




/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

 APPLICATIONCREATEINSTANCE(STATICTICSCHARS, canvas2d)



/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         STATICTICSCHARS::STATICTICSCHARS
* @brief      Constructor
* @ingroup
*
* @param
* @return
*
*---------------------------------------------------------------------------------------------------------------------*/
STATICTICSCHARS::STATICTICSCHARS() :  XFSMACHINE(0)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         STATICTICSCHARS::~STATICTICSCHARS
* @brief      Destructor
* @ingroup
*
* @param
* @return
*
*---------------------------------------------------------------------------------------------------------------------*/
STATICTICSCHARS::~STATICTICSCHARS()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         STATICTICSCHARS::InitFSMachine
* @brief      Init FS Machine
* @ingroup
*
* @param
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool STATICTICSCHARS::InitFSMachine()
{
  if(!AddState( STATICTICSCHARS_XFSMSTATE_NONE           ,
                STATICTICSCHARS_XFSMEVENT_INI            , STATICTICSCHARS_XFSMSTATE_INI          ,
                STATICTICSCHARS_XFSMEVENT_END            , STATICTICSCHARS_XFSMSTATE_END          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( STATICTICSCHARS_XFSMSTATE_INI            ,
                STATICTICSCHARS_XFSMEVENT_NONE           , STATICTICSCHARS_XFSMSTATE_NONE         ,
                STATICTICSCHARS_XFSMEVENT_END            , STATICTICSCHARS_XFSMSTATE_END          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( STATICTICSCHARS_XFSMSTATE_END            ,
                STATICTICSCHARS_XFSMEVENT_NONE           , STATICTICSCHARS_XFSMSTATE_NONE         ,
                STATICTICSCHARS_XFSMEVENT_INI            , STATICTICSCHARS_XFSMSTATE_INI          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         STATICTICSCHARS::AppProc_Ini
* @brief      Ini Application
* @ingroup
*
* @param
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool STATICTICSCHARS::AppProc_Ini()
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

  SetEvent(STATICTICSCHARS_XFSMEVENT_INI);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         STATICTICSCHARS::AppProc_FirstUpdate
* @brief      First Update
* @ingroup
*
* @param
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool STATICTICSCHARS::AppProc_FirstUpdate()
{
  //--------------------------------------------------------------------------------------

  INPDEVICE* inpdevice;

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_KEYBOARD);
  if(inpdevice)
    {
      button[STATICTICSCHARS_BUTTON_UP]      = inpdevice->GetButton(INPBUTTON_ID_UP);
      button[STATICTICSCHARS_BUTTON_DOWN]    = inpdevice->GetButton(INPBUTTON_ID_DOWN);
      button[STATICTICSCHARS_BUTTON_LEFT]    = inpdevice->GetButton(INPBUTTON_ID_LEFT);
      button[STATICTICSCHARS_BUTTON_RIGHT]   = inpdevice->GetButton(INPBUTTON_ID_RIGHT);
      button[STATICTICSCHARS_BUTTON_SPACE]   = inpdevice->GetButton(INPBUTTON_ID_SPACE);
      button[STATICTICSCHARS_BUTTON_ESC]     = inpdevice->GetButton(INPBUTTON_ID_ESCAPE);
      button[STATICTICSCHARS_BUTTON_F1]      = inpdevice->GetButton(INPBUTTON_ID_F1);
      button[STATICTICSCHARS_BUTTON_F2]      = inpdevice->GetButton(INPBUTTON_ID_F2);
      button[STATICTICSCHARS_BUTTON_F5]      = inpdevice->GetButton(INPBUTTON_ID_F5);
      button[STATICTICSCHARS_BUTTON_F9]      = inpdevice->GetButton(INPBUTTON_ID_F9);
      button[STATICTICSCHARS_BUTTON_MINUS]   = inpdevice->GetButton(INPBUTTON_ID_WIIMOTE_MINUS);
      button[STATICTICSCHARS_BUTTON_PLUS]    = inpdevice->GetButton(INPBUTTON_ID_WIIMOTE_PLUS);

      button[STATICTICSCHARS_BUTTON_MOUSE]   = inpdevice->GetButton(INPBUTTON_ID_MOUSE_RIGHT);
    }

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_MOUSE);
  if(inpdevice)
    {
      button[STATICTICSCHARS_BUTTON_MOUSE] = inpdevice->GetButton(INPBUTTON_ID_MOUSE_LEFT);
      cursor = inpdevice->GetCursor(0);
    }

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_TOUCHSCREEN);
  if(inpdevice)
    {     
      button[STATICTICSCHARS_BUTTON_TOUCHSCREEN] = inpdevice->GetButton(INPBUTTON_ID_TOUCHSCREEN);     
      cursor = inpdevice->GetCursor(0);
    }

  //--------------------------------------------------------------------------------------
  
  xrand  = GEN_XFACTORY.CreateRand();
  if(!xrand)  return false;

  //--------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         STATICTICSCHARS::AppProc_Update
* @brief      Update Application
* @ingroup
*
* @param
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool STATICTICSCHARS::AppProc_Update()
{
  if(GetEvent()==STATICTICSCHARS_XFSMEVENT_NONE) // Not GEN_NEW event
    {
      switch(GetCurrentState())
        {
          case STATICTICSCHARS_XFSMSTATE_NONE      :  break;

          case STATICTICSCHARS_XFSMSTATE_INI       :  UpdateInput();
                                                      DrawFrame();
                                                      GetMainScreen()->UpdateViewports();
                                                      break;

          case STATICTICSCHARS_XFSMSTATE_END       :  break;

        }
    }
   else //  New event
    {
      if(GetEvent()<STATICTICSCHARS_LASTEVENT)
        {
          CheckTransition();

          switch(GetCurrentState())
            {
              case STATICTICSCHARS_XFSMSTATE_NONE  :  break;

              case STATICTICSCHARS_XFSMSTATE_INI   :  break;

              case STATICTICSCHARS_XFSMSTATE_END   :  break;
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         STATICTICSCHARS::AppProc_End
* @brief      End Application
* @ingroup
*
* @param
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool STATICTICSCHARS::AppProc_End()
{
  XSTRING string;
  XSTRING stringresult;

  //--------------------------------------------------------------------------------------

  SetCurrentState(STATICTICSCHARS_XFSMSTATE_END);

  //--------------------------------------------------------------------------------------
  
  if(vectorfile)
    {
      GEN_DELETE vectorfile;
      vectorfile = NULL;
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
* @fn         bool STATICTICSCHARS::UpdateInput()
* @brief      UpdateInput
* @ingroup
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool STATICTICSCHARS::UpdateInput()
{
   int  width  = GetMainScreen()->GetWidth();
   int  height = GetMainScreen()->GetHeight();

  if(cursor)    
    {  
      if(cursor->GetMotion()->IsReadyToTest(50))
        {
          cursor->GetMotion()->InvertYAxis(height);

       

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
                  
                }

              if(button[STATICTICSCHARS_BUTTON_MOUSE]->IsPressedWithRelease())
                {
                  
                  cursor->GetMotion()->Reset();       
                }
    
              if(button[STATICTICSCHARS_BUTTON_TOUCHSCREEN])
                {             
                  if(button[STATICTICSCHARS_BUTTON_TOUCHSCREEN]->IsPressed())
                    {  

                      cursor->GetMotion()->Reset();
                    }
                }
            }
        }
    }


  for(int c=0; c<STATICTICSCHARS_BUTTON_MOUSE; c++)
    {
      if(button[c])
        {
          if(button[c]->IsPressedWithRelease())
            {
              switch(c)
                {
                  case STATICTICSCHARS_BUTTON_F1     : break;

                  case STATICTICSCHARS_BUTTON_F2     : break;
                            
                  case STATICTICSCHARS_BUTTON_F5     : break;

              

                  case STATICTICSCHARS_BUTTON_ESC    : SetExitType(APPFLOWBASE_EXITTYPE_BY_USER);
                                                       break;
                }
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool STATICTICSCHARS::Ini_Graphics(GRPSCREEN* screen)
* @brief      Ini_Graphics
* @ingroup    GRAPHIC
* 
* 
* @param[in]  screen : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool STATICTICSCHARS::Ini_Graphics(GRPSCREEN* screen)
{
  screen->SetWidth(1024);
  screen->SetHeight(768);

  screen->GetTitle()->Set(__L("Statictics Chars Canvas"));  

  GetMainScreen()->CreateViewport(GRPVIEWPORT_ID_MAIN , 0.0f, 0.0f, (float)screen->GetWidth()   , (float)screen->GetHeight(), 0, 0, (screen->GetWidth()), (screen->GetHeight()));

  //--------------------------------------------------------------------------------------

  GRPVIEWPORT*    viewport = NULL;
  GRP2DCANVAS*    canvas = NULL;
  int             width = 0;
  int             height = 0;

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
  
  XPATH pathfont;

  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_FONTS, pathfont);
  pathfont.Slash_Add();             
  pathfont.Add(__L("Nunito-SemiBold.ttf"));

  
  canvas->VectorFont_Load(pathfont);


  vectorfile = GRPVECTORFILE::CreateInstance(GRPVECTORFILETYPE_SVG);
  if(vectorfile)
    {
      GRPSTATISTICSCHARTAREA3D chart;

      GRPSTATISTICSCHARTCONFIG* config = chart.GetConfig();
      if(config)
        {
          config->SetTitle(__L("Sales by quarter"));

          config->SetShowValues(true);
         
          config->SetShowLegend(true);
          config->SetLegendPosition(GRPSTATISTICSCHARTLEGENDPOSITION_LEFT);
          config->SetLegendFontSize(12.0);
          config->SetShowAxisLabels(true);
          config->SetAxisFontSize(11.0);
        }

      GRPSTATISTICSCHARTDATA* data = chart.GetData();
      if(data)
        {
          data->AddCategory(__L("Q1"));
          data->AddCategory(__L("Q2"));
          data->AddCategory(__L("Q3"));
          data->AddCategory(__L("Q4"));

          GRPSTATISTICSCHARTSERIE* serie2024 = data->AddSerie(__L("2024"));
          if(serie2024)
            {
              serie2024->AddValue( 45.0);
              serie2024->AddValue( 72.0);
              serie2024->AddValue( 58.0);
              serie2024->AddValue( 90.0);
            }

          GRPSTATISTICSCHARTSERIE* serie2025 = data->AddSerie(__L("2025"));
          if(serie2025)
            {
              serie2025->AddValue( 60.0);
              serie2025->AddValue( 55.0);
              serie2025->AddValue( 80.0);
              serie2025->AddValue(110.0);
            }
        }

      GRPSTATISTICSCHARTBUILDERSVG builder;

      if(chart.Generate(builder, 420.0, 420.0) == GRPVECTORFILERESULT_OK)
        {
          XSTRING content;

          if(builder.GetResult(content))
            {
              vectorfile->Load(content);
            }
        }
    }

  //--------------------------------------------------------------------------------------

                                          
  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool STATICTICSCHARS::DrawFrame()
* @brief      DrawFrame
* @ingroup
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool STATICTICSCHARS::DrawFrame()
{
  GRP2DCOLOR_RGBA8  colorblack(0, 0, 0);
  GRP2DCOLOR_RGBA8  colorwhite(255, 255, 255);
  GRP2DCOLOR_RGBA8  colorred(255, 0, 0);
  GRP2DCOLOR_RGBA8  colorgreen(0, 255, 0);
  GRP2DCOLOR_RGBA8  colorblue(0, 0, 255);
  GRP2DCOLOR_RGBA8  colorgray(10, 10, 10, 150);

  GRPSCREEN*     screen    = NULL;
  GRPVIEWPORT*   viewport  = NULL;
  GRP2DCANVAS*   canvas    = NULL;
  int            width     = 0;
  int            height    = 0;


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

  width  = screen->GetWidth();
  height = screen->GetHeight();

  canvas->ReleaseDrawFramerate();

  
   if(vectorfile)
    {      
      vectorfile_render.RenderCached(vectorfile, canvas, 50.0, 50.0, 420.0, 420.0);   

      //vectorfile_render.RenderCached(vectorfile, canvas, 30.0, 30.0, canvas->GetWidth()-130, canvas->GetHeight()-30);   
    }

  //--------------------------------------------------------------------------------------

  return true;
}






/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void STATICTICSCHARS::Graphics_HandleEvent(GRPXEVENT* event)
* @brief      Graphics_HandleEvent
* @ingroup
*
* @param[in]  event :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void STATICTICSCHARS::HandleEvent_Graphics(GRPXEVENT* event)
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
* @fn         STATICTICSCHARS::HandleEvent
* @brief      Handle Events
* @ingroup
*
* @param[]    xevent : event send to control
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void STATICTICSCHARS::HandleEvent(XEVENT* xevent)
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
* @fn         void STATICTICSCHARS::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void STATICTICSCHARS::Clean()
{
  xtimer       = NULL;
  xrand        = NULL;

  for(int c=0; c<STATICTICSCHARS_BUTTON_MAX; c++)
    {
      button[c] = NULL;
    }  

  vectorfile  = NULL;  
}