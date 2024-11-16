/**-------------------------------------------------------------------------------------------------------------------
*
* @file       NetConn.h
*
* @class      NETCONN
* @brief      Net Connection CFG class (DIOCoreProtol example)
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

#ifndef _NETCONN_H_
#define _NETCONN_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XDateTime.h"
#include "XFSMachine.h"
#include "XString.h"
#include "XScheduler.h"

#include "DIOStream.h"
#include "DIOURL.h"

#include "APPConsole.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum NETCONNXFSMEVENTS
{
  NETCONN_XFSMEVENT_NONE                 = 0 ,
  NETCONN_XFSMEVENT_INI                      ,
  NETCONN_XFSMEVENT_END                      ,

  NETCONN_LASTEVENT
};


enum NETCONNXFSMSTATES
{
  NETCONN_XFSMSTATE_NONE                 = 0 ,
  NETCONN_XFSMSTATE_INI                      ,
  NETCONN_XFSMSTATE_END                      ,

  NETCONN_LASTSTATE
};


enum NETCONNTASKID
{
  NETCONNTASKID_UNKNOWN                  = 0 ,
  NETCONNTASKID_CHECKINTERNETCONNECTION      ,
  NETCONNTASKID_CHECKMEMORYSTATUS            ,
};


#define APPLICATION_VERSION                       0
#define APPLICATION_SUBVERSION                    1
#define APPLICATION_SUBVERSIONERR                 0

#define APPLICATION_NAMEAPP                       __L("Net Conn")
#define APPLICATION_NAMEFILE                      __L("netconn")

#define APPLICATION_OWNER                         __L("GEN Group")

#define APPLICATION_YEAROFCREATION                2024


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
class APPINTERNETSERVICES;
class NETCONN_CONNECTIONSMANAGER;


class NETCONN : public APPCONSOLE, public XOBSERVER, public XFSMACHINE
{
  public:
                                    NETCONN                                 ();
    virtual                        ~NETCONN                                 ();

    bool                            InitFSMachine                           ();

    bool                            AppProc_Ini                             ();
    bool                            AppProc_FirstUpdate                     ();
    bool                            AppProc_Update                          ();
    bool                            AppProc_End                             ();

    bool                            KeyValidSecuences                       (int key);  

    bool                            Show_ConnectionsStatus                  ();
    bool                            Show_AllStatus                          ();

  private:

    void                            HandleEvent                             (XEVENT* xevent);

    void                            Clean                                   ();

    XTIMER*                         xtimerupdateconsole;
    XMUTEX*                         xmutexshowallstatus;    

    bool                            modeserver;   

    NETCONN_CONNECTIONSMANAGER*     connectionsmanager; 
};


/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif

