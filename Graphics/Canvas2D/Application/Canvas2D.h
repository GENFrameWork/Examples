/**-------------------------------------------------------------------------------------------------------------------
*
* @file        Canvas2D.h
*
* @class       CANVAS2D
* @brief       GEN Canvas 2D Example class
* @ingroup     GRAPHIC
*
* @author      Abraham J. Velez
* @date       01/03/2016 12:00
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

#ifndef _CANVAS2D_H_
#define _CANVAS2D_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XDateTime.h"
#include "XFSMachine.h"
#include "XString.h"
#include "XScheduler.h"

#include "DIOStream.h"
#include "DIOURL.h"

#include "APPGraphics.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum CANVAS2DXFSMEVENTS
{
  CANVAS2D_XFSMEVENT_NONE                 = 0 ,
  CANVAS2D_XFSMEVENT_INI                      ,
  CANVAS2D_XFSMEVENT_END                      ,

  CANVAS2D_LASTEVENT
};


enum CANVAS2DXFSMSTATES
{
  CANVAS2D_XFSMSTATE_NONE                 = 0 ,
  CANVAS2D_XFSMSTATE_INI                      ,
  CANVAS2D_XFSMSTATE_END                      ,

  CANVAS2D_LASTSTATE
};


enum CANVAS2DTASKID
{
  CANVAS2DTASKID_UNKNOWN                  = 0 ,
  CANVAS2DTASKID_CHECKMEMORYSTATUS            ,
};


enum CANVAS2D_BUTTONS
{
  CANVAS2D_BUTTON_UP                      = 0 ,
  CANVAS2D_BUTTON_DOWN                        ,
  CANVAS2D_BUTTON_LEFT                        ,
  CANVAS2D_BUTTON_RIGHT                       ,
  CANVAS2D_BUTTON_SPACE                       ,
  CANVAS2D_BUTTON_ESC                         ,
  CANVAS2D_BUTTON_MOUSE                       ,
  CANVAS2D_BUTTON_TOUCHSCREEN                 ,

  CANVAS2D_BUTTON_MAX
};



#define APPLICATION_VERSION                       0
#define APPLICATION_SUBVERSION                    1
#define APPLICATION_SUBVERSIONERR                 0

#define APPLICATION_NAMEAPP                       __L("Canvas2D")
#define APPLICATION_ENTERPRISE                    __L("GEN Group")

#define APPLICATION_NAMEFILE                      __L("canvas2d")


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XTIME;
class XTIMER;
class XRAND;
class XTHREAD;
class XDIR;
class XSCHEDULER;
class XSCHEDULER_XEVENT;
class DIOINTERNET;
class DIOCHECKTCPIPCONNECTIONS;
class DIOCHECKINTERNETCONNECTION;
class DIOSCRAPERWEBPUBLICIP;
class DIOSCRAPERWEBGEOLOCATIONIP;
class DIOSCRAPERWEBUSERAGENTID;
class GRPBITMAPSECUENCE;
class INPBUTTON;
class INPCURSOR;
class UI_XEVENT;
class GRPXEVENT;
class GRPBITMAP;
class GRPBITMAPSEQUENCE;
class CANVAS2D_CFG;


class CANVAS2D : public APPGRAPHICS, public XFSMACHINE
{
  public:
                                    CANVAS2D                                ();
    virtual                        ~CANVAS2D                                ();

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

    INPBUTTON*                      button[CANVAS2D_BUTTON_MAX];
    INPCURSOR*                      cursor;

    XSTRING                         makeaction;

    GRPBITMAP*                      backgroundbmp;
    GRPBITMAP*                      testbmp;
    GRPBITMAPSEQUENCE*              charactersecuence;
};


/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif

