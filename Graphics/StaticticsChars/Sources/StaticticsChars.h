/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       StaticticsChars.h
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

#pragma once

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XDateTime.h"
#include "XFSMachine.h"
#include "XString.h"
#include "XScheduler.h"

#include "DIOStream.h"
#include "DIOURL.h"

#include "APPFlowGraphics.h"

#include "GRP2DVectorFileRenderAGG.h"



/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum STATICTICSCHARSXFSMEVENTS
{
  STATICTICSCHARS_XFSMEVENT_NONE                 = 0 ,
  STATICTICSCHARS_XFSMEVENT_INI                      ,
  STATICTICSCHARS_XFSMEVENT_END                      ,

  STATICTICSCHARS_LASTEVENT
};


enum STATICTICSCHARSXFSMSTATES
{
  STATICTICSCHARS_XFSMSTATE_NONE                 = 0 ,
  STATICTICSCHARS_XFSMSTATE_INI                      ,
  STATICTICSCHARS_XFSMSTATE_END                      ,

  STATICTICSCHARS_LASTSTATE
};


enum STATICTICSCHARSTASKID
{
  STATICTICSCHARSTASKID_UNKNOWN                  = 0 ,
  STATICTICSCHARSTASKID_CHECKMEMORYSTATUS            ,
};


enum STATICTICSCHARS_BUTTONS
{
  STATICTICSCHARS_BUTTON_UP                      = 0 ,
  STATICTICSCHARS_BUTTON_DOWN                        ,
  STATICTICSCHARS_BUTTON_LEFT                        ,
  STATICTICSCHARS_BUTTON_RIGHT                       ,
  STATICTICSCHARS_BUTTON_SPACE                       ,
  STATICTICSCHARS_BUTTON_ESC                         ,
  STATICTICSCHARS_BUTTON_F1                          ,
  STATICTICSCHARS_BUTTON_F2                          ,
  STATICTICSCHARS_BUTTON_F5                          ,
  STATICTICSCHARS_BUTTON_F9                          ,
  STATICTICSCHARS_BUTTON_PLUS                        ,
  STATICTICSCHARS_BUTTON_MINUS                       ,

  STATICTICSCHARS_BUTTON_MOUSE                       ,

  STATICTICSCHARS_BUTTON_TOUCHSCREEN                 ,

  STATICTICSCHARS_BUTTON_MAX
};


#define XTHREADGROUPID_STATICTICSCHARS_DRAWFRAME       XTHREADGROUPID_APPOWNER + 100

#define APPLICATION_VERSION                       0
#define APPLICATION_SUBVERSION                    1
#define APPLICATION_SUBVERSIONERR                 1

#define APPLICATION_NAMEAPP                       __L("StaticticsChars")
#define APPLICATION_NAMEFILE                      __L("staticticschars")

#define APPLICATION_OWNER                         __L("EndoraSoft")

#define APPLICATION_YEAROFCREATION                2018



/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XTIME;
class XTIMER;
class XRAND;
class XTHREAD;
class XDIR;
class XSCHEDULER;
class XSCHEDULER_XEVENT;
class XRAND;
class DIOINTERNET;
class DIOCHECKTCPIPCONNECTIONS;
class DIOCHECKINTERNETCONNECTION;
class DIOSCRAPERWEBPUBLICIP;
class DIOSCRAPERWEBGEOLOCATIONIP;
class DIOSCRAPERWEBUSERAGENTID;
class GRPBITMAPSECUENCE;
class GRPXEVENT;
class GRPBITMAP;
class GRPBITMAPSEQUENCE;
class GRPVECTORFILESVG;
class INPBUTTON;
class INPCURSOR;
class UI_XEVENT;
class UI_ELEMENT;
class UI_ELEMENT_TEXT;
class STATICTICSCHARS_CFG;


class STATICTICSCHARS : public APPFLOWGRAPHICS, public XFSMACHINE
{
  public:
                                    STATICTICSCHARS                              ();
    virtual                        ~STATICTICSCHARS                              ();

    bool                            InitFSMachine                           ();

    bool                            AppProc_Ini                             ();
    bool                            AppProc_FirstUpdate                     ();
    bool                            AppProc_Update                          ();
    bool                            AppProc_End                             ();
   
  private:
    
    bool                            UpdateInput                             ();

    bool                            Ini_Graphics                            (GRPSCREEN* screen);


    bool                            DrawFrame                               ();

    void                            HandleEvent_Graphics                    (GRPXEVENT* event);
    void                            HandleEvent                             (XEVENT* xevent);
    
    void                            Clean                                   ();

    XTIMER*                         xtimer;

    XRAND*                          xrand;

    INPBUTTON*                      button[STATICTICSCHARS_BUTTON_MAX];
    INPCURSOR*                      cursor;

    GRPVECTORFILE*                  vectorfile; 
    GRP2DVECTORFILERENDERAGG        vectorfile_render;

};




/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/





