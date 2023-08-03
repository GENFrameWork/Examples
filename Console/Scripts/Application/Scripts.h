/**-------------------------------------------------------------------------------------------------------------------
*
* @file       Scripts.h
*
* @class      SCRIPTS
* @brief      GEN Scripts Example class
* @ingroup    EXAMPLES
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

#ifndef _SCRIPTS_H_
#define _SCRIPTS_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XDateTime.h"
#include "XFSMachine.h"
#include "XString.h"
#include "XScheduler.h"

#include "DIOStream.h"
#include "DIOURL.h"

#include "Script_XEvent.h"
#include "Script_Lib_IO.h"
#include "Script_Lib_Math.h"
#include "Script_Lib_Path.h"
#include "Script_Lib_Rand.h"
#include "Script_Lib_String.h"
#include "Script_Lib_Timer.h"
#include "Script_Lib_Process.h"
#include "Script_Lib_Window.h"
#include "Script_Lib_InputSimulate.h"


#include "APPConsole.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum SCRIPTSXFSMEVENTS
{
  SCRIPTS_XFSMEVENT_NONE                = 0 ,
  SCRIPTS_XFSMEVENT_INI                     ,
  SCRIPTS_XFSMEVENT_UPDATE                  ,
  SCRIPTS_XFSMEVENT_END                     ,

  SCRIPTS_LASTEVENT
};


enum SCRIPTSXFSMSTATES
{
  SCRIPTS_XFSMSTATE_NONE                = 0 ,
  SCRIPTS_XFSMSTATE_INI                     ,
  SCRIPTS_XFSMSTATE_UPDATE                  ,
  SCRIPTS_XFSMSTATE_END                     ,

  SCRIPTS_LASTSTATE
};


enum SCRIPTSTASKID
{
  SCRIPTSTASKID_UNKNOWN                 = 0 ,
  SCRIPTSTASKID_CHECKMEMORYSTATUS           ,
};


#define APPLICATION_VERSION                       0
#define APPLICATION_SUBVERSION                    1
#define APPLICATION_SUBVERSIONERR                 0

#define APPLICATION_NAMEAPP                       __L("Scripts")
#define APPLICATION_NAMEFILE                      __L("scripts")

#define APPLICATION_OWNER                         __L("GEN Group")

#define APPLICATION_YEAROFCREATION                2018


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XTIME;
class XTIMER;
class XRAND;
class XTHREAD;
class XDIR;
class XSCHEDULER;
class XSCHEDULER_XEVENT;
class DIOCHECKTCPIPCONNECTIONS;
class DIOCHECKINTERNETCONNECTION;
class DIOSCRAPERWEBPUBLICIP;
class DIOSCRAPERWEBGEOLOCATIONIP;
class DIOSCRAPERWEBUSERAGENTID;
class GRPBITMAPSECUENCE;
class GRPXEVENT;
class SCRIPTS_CFG;
class SCRIPT;


class SCRIPTS : public APPCONSOLE, public XFSMACHINE
{
  public:
                                    SCRIPTS                                 ();
    virtual                        ~SCRIPTS                                 ();

    bool                            InitFSMachine                           ();

    bool                            AppProc_Ini                             ();
    bool                            AppProc_FirstUpdate                     ();
    bool                            AppProc_Update                          ();
    bool                            AppProc_End                             ();

    bool                            KeyValidSecuences                       (int key);

    bool                            CreateScripToExec                       ();
    bool                            DeleteScripToExec                       ();

    bool                            Show_AppStatus                          ();
    bool                            Show_ScriptStatus                       ();
    bool                            Show_AllStatus                          ();

  private:

    void                            Clean                                   ();

    void                            HandleEvent_Script                      (SCRIPT_XEVENT* event);
    void                            HandleEvent                             (XEVENT* xevent);

    XTIMER*                         xtimerupdateconsole;
    XTIMER*                         xtimerscriptrun;

    XMUTEX*                         xmutexshowallstatus;

    SCRIPT_LIB_IO*                  scriptlibio;
    SCRIPT_LIB_MATH*                scriptlibmath;
    SCRIPT_LIB_PATH*                scriptlibpath;
    SCRIPT_LIB_RAND*                scriptlibrand;
    SCRIPT_LIB_STRING*              scriptlibstring;
    SCRIPT_LIB_TIMER*               scriptlibtimer;
    SCRIPT_LIB_PROCESS*             scriptlibprocess;
    SCRIPT_LIB_WINDOW*              scriptlibwindow;
    SCRIPT_LIB_INPUTSIMULATE*       scriptlibinputsimulate;
    SCRIPT*                         script;

};


/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif

