/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       MiniWebServer.h
* 
* @class      MINIWEBSERVER
* @brief      Example Mini Web Server class
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

#ifndef _MINIWEBSERVER_H_
#define _MINIWEBSERVER_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XDateTime.h"
#include "XFSMachine.h"
#include "XString.h"

#include "DIOStream.h"
#include "DIOURL.h"

#include "APPConsole.h"

#include "MiniWebServer_APIRest.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

enum MINIWEBSERVERXFSMEVENTS
{
  MINIWEBSERVER_XFSMEVENT_NONE                  = 0 ,
  MINIWEBSERVER_XFSMEVENT_INI                       ,
  MINIWEBSERVER_XFSMEVENT_END                       ,

  MINIWEBSERVER_LASTEVENT
};


enum MINIWEBSERVERXFSMSTATES
{
  MINIWEBSERVER_XFSMSTATE_NONE                  = 0 ,
  MINIWEBSERVER_XFSMSTATE_INI                       ,
  MINIWEBSERVER_XFSMSTATE_END                       ,

  MINIWEBSERVER_LASTSTATE
};


enum MINIWEBSERVERTASKID
{
  MINIWEBSERVER_TASKID_UNKNOWN                  = 0 ,
  MINIWEBSERVER_TASKID_CHECKMEMORYSTATUS
};


#define APPLICATION_VERSION                       0
#define APPLICATION_SUBVERSION                    1
#define APPLICATION_SUBVERSIONERR                 0

#define APPLICATION_NAMEAPP                       __L("Mini Web Server")
#define APPLICATION_NAMEFILE                      __L("miniwebserver")

#define APPLICATION_OWNER                         __L("GEN Group")

#define APPLICATION_YEAROFCREATION                2018


#define APPLICATION_DIRECTORY_WEB                 __L("web")

#define MINIWEBSERVER_TABLE_TEST_NAME             __L("TableTest")
#define MINIWEBSERVER_TABLE_MAXFIELDS             16

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
class DIOWEBSERVER_XEVENT;
class APPINTERNETSERVICES;
class APPWEBSERVER;


class MINIWEBSERVER : public APPCONSOLE, public XOBSERVER, public XFSMACHINE
{
  public:
                                    MINIWEBSERVER                           ();
    virtual                        ~MINIWEBSERVER                           ();

    bool                            InitFSMachine                           ();

    bool                            AppProc_Ini                             ();
    bool                            AppProc_FirstUpdate                     ();
    bool                            AppProc_Update                          ();
    bool                            AppProc_End                             ();

    bool                            KeyValidSecuences                       (int key);
   
    bool                            Show_WebServerConfig                    ();
    bool                            Show_WebSocketConfig                    ();

    bool                            Show_AllStatus                          ();

  private:

    void                            HandleEvent_WebServer                   (DIOWEBSERVER_XEVENT* event);
    void                            HandleEvent                             (XEVENT* xevent);

    void                            Clean                                   ();

    XTIMER*                         xtimerupdateconsole;
    XMUTEX*                         xmutexshowallstatus;
    
    APPWEBSERVER*                   appwebserver;
    MINIWEBSERVER_APIREST*          apirest;
    APPWEBSERVER*                   appwebsocket;
};

#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

