/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       IniBase.h
* 
* @class      INIBASE
* @brief      Ini Base (Start to make new APP)
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

#ifndef _INIBASE_H_
#define _INIBASE_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XDateTime.h"
#include "XFSMachine.h"
#include "XString.h"
#include "XScheduler.h"

#include "DIOStream.h"
#include "DIOURL.h"

#include "APPFlowConsole.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


enum INIBASEXFSMEVENTS
{
  INIBASE_XFSMEVENT_NONE                 = 0 ,
  INIBASE_XFSMEVENT_INI                      ,
  INIBASE_XFSMEVENT_UPDATE                   ,
  INIBASE_XFSMEVENT_END                      ,

  INIBASE_LASTEVENT
};


enum INIBASEXFSMSTATES
{
  INIBASE_XFSMSTATE_NONE                 = 0 ,
  INIBASE_XFSMSTATE_INI                      ,
  INIBASE_XFSMSTATE_UPDATE                   ,
  INIBASE_XFSMSTATE_END                      ,

  INIBASE_LASTSTATE
};


enum INIBASETASKID
{
  INIBASETASKID_UNKNOWN                  = 0 ,
  INIBASETASKID_CHECKINTERINIBASEECTION      ,
  INIBASETASKID_CHECKMEMORYSTATUS            ,
};


#define APPLICATION_VERSION                       0
#define APPLICATION_SUBVERSION                    1
#define APPLICATION_SUBVERSIONERR                 0

#define APPLICATION_NAMEAPP                       __L("Ini Base")
#define APPLICATION_NAMEFILE                      __L("inibase")

#define APPLICATION_OWNER                         __L("EndoraSoft")

#define APPLICATION_YEAROFCREATION                2024


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

class XTIME;
class XTIMER;
class XRAND;
class XTHREAD;
class XDIR;
class XSCHEDULER;
class XSCHEDULER_XEVENT;
class DIOINTERNET;
class DIOCHECKTCPIPCONNECTIONS;
class DIOCHECKINTERINIBASEECTION;
class DIOSCRAPERWEBPUBLICIP;
class DIOSCRAPERWEBGEOLOCATIONIP;
class DIOSCRAPERWEBUSERAGENTID;
class DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT;
class APPFLOWINTERNETSERVICES;
class INIBASE_COREPROTOCOL_CONNECTIONSMANAGER;
class INIBASE_AGENTSTATE;
class INIBASE_TESTUPDATECLASS;


class INIBASE : public APPFLOWCONSOLE, public XOBSERVER, public XFSMACHINE
{
  public:
                              INIBASE                                       ();
    virtual                  ~INIBASE                                       ();

    bool                      InitFSMachine                                 ();

    bool                      AppProc_Ini                                   ();
    bool                      AppProc_FirstUpdate                           ();
    bool                      AppProc_Update                                ();
    bool                      AppProc_End                                   ();

    static bool               IsServer                                      ();      

    bool                      KeyValidSecuences                             (int key); 
    
    bool                      Show_AllStatus                                ();

  private:

    void                      HandleEvent                                   (XEVENT* xevent);

    void                      Clean                                         ();

    XTIMER*                   xtimerupdateconsole;
    XMUTEX*                   xmutexshowallstatus;        
};

#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES

extern INIBASE* inibase;

#pragma endregion


#endif
