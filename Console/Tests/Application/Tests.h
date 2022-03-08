
/**-------------------------------------------------------------------------------------------------------------------
*
* @file       Tests.h
*
* @class      TESTS
* @brief      GEN Tests Example class
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @copyright  Copyright(c) 2008 - 2016 GEN Group.
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

#ifndef _TESTS_H_
#define _TESTS_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XDateTime.h"
#include "XFSMachine.h"
#include "XString.h"
#include "XTree.h"
#include "XProperty.h"
#include "XScheduler.h"

#include "DIOStream.h"
#include "DIOPCap.h"
#include "DIOURL.h"
#include "DIOGPIO.h"

#include "APPConsole.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum TESTSXFSMEVENTS
{
  TESTS_XFSMEVENT_NONE              = 0 ,
  TESTS_XFSMEVENT_INI                   ,
  TESTS_XFSMEVENT_END                   ,

  TESTS_LASTEVENT
};


enum TESTSXFSMSTATES
{
  TESTS_XFSMSTATE_NONE              = 0 ,
  TESTS_XFSMSTATE_INI                   ,
  TESTS_XFSMSTATE_END                   ,

  TESTS_LASTSTATE
};



enum TESTS_GPIOENTRYID
{
  TESTS_GPIOENTRYID_TESTGPIO             = DIOGPIO_ID_NOTDEFINED + 1 ,   
  TESTS_GPIOENTRYID_LED_NEOPIXEL                                             
};



#define APPLICATION_VERSION                       0
#define APPLICATION_SUBVERSION                    1
#define APPLICATION_SUBVERSIONERR                 0

#define APPLICATION_NAMEAPP                       __L("Tests")
#define APPLICATION_NAMEFILE                      __L("tests")

#define APPLICATION_YEAROFCREATION                2019

#define TESTS_ENTERPRISE                          __L("GEN Group")

//#define TESTS_NOKEY


class TESTS;
typedef bool (*TESTS_FUNCTION)(TESTS* tests);


typedef struct
{
  bool            active;
  TESTS_FUNCTION  function;
  XCHAR*          namefunction;

} TESTS_LIST_FUNCTION;



typedef struct TESTS_PROPERTY
{ 

  double              x_;
  double              y_;
  double              z_;

  public:                                     

                      TESTS_PROPERTY          () : x(this), y(this), z(this)
                      {
                        x_ = 0.0f;
                        y_ = 0.0f;
                        z_ = 10.0f;
                      }

                      TESTS_PROPERTY          (double x0, double y0) : x_(x0), y_(y0), x(this), y(this), z(this)
                      {
                        z_ = 10.0f;
                      } 

    void              SetX                    (double x) 
                      { 
                        x_ = x; 
                      }

    double            GetX                    () 
                      { 
                        return x_; 
                      } 

    XPROPERTY<TESTS_PROPERTY, double, &TESTS_PROPERTY::GetX, &TESTS_PROPERTY::SetX> x;

    void              SetY                    (double y) 
                      { 
                        y_ = y;                       
                      }

    double            GetY                    () 
                      { 
                        return y_; 
                      }

   
    XPROPERTY<TESTS_PROPERTY, double, &TESTS_PROPERTY::GetY, &TESTS_PROPERTY::SetY> y;


    double            GetZ                    ()
                      {
                        return z_;
                      }


    XPROPERTYG<TESTS_PROPERTY, double, &TESTS_PROPERTY::GetZ> z;

   
} TYPE_PROPERTY;




typedef struct TESTS_PROPERTY2
{
  public:
                      TESTS_PROPERTY2         () :  data(this)
                      {

                      }

                      TESTS_PROPERTY2         (TESTS_PROPERTY data0) : data_(data0), data(this)
                      {
                      }

    void              Set                     (TESTS_PROPERTY data)
                      {
                        data_.x = data.x;
                      }

    TESTS_PROPERTY    Get                     ()
                      {
                        return data_;
                      }

    
    XPROPERTY<TESTS_PROPERTY2, TESTS_PROPERTY, &TESTS_PROPERTY2::Get, &TESTS_PROPERTY2::Set>  data;

    TESTS_PROPERTY    data2;


  private:

    TESTS_PROPERTY    data_;

} TYPE_PROPERTY2;




#define TESTS_MAXNTHREADS                         5


typedef XTREE_NODE<XSTRING*>                      XTREE_NODE_TEST;
typedef XTREE_NODE_ITERATOR<XSTRING*>             XTREE_NODE_ITERATOR_TEST;
typedef XTREE<XSTRING*>                           XTREE_TEST;

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XTIME;
class XTIMER;
class XRAND;
class XTHREAD;
class XDIR;
class XSCHEDULER;
class XSCHEDULER_XEVENT;
class HASH;
class DIOWEBCLIENT_XEVENT;
class APPCHECKRESOURCESHARDWARE;
class APPINTERNETSERVICES;
class APPALERTS;


class TESTS : public APPCONSOLE, public XFSMACHINE
{
  public:
                                    TESTS                               ();
    virtual                        ~TESTS                               ();

    bool                            InitFSMachine                       ();

    bool                            AppProc_PlatformIni                 ();
    bool                            AppProc_Ini                         ();
    bool                            AppProc_FirstUpdate                 ();
    bool                            AppProc_Update                      ();
    bool                            AppProc_End                         ();
    bool                            AppProc_PlatformEnd                 ();

    bool                            KeyValidSecuences                   (int key);

    bool                            Show_Line                           (XSTRING& string, XSTRING& string2, int tab = 3, bool linefeed = true);
    bool                            Show_Header                         (bool separator);
    bool                            Show_AppStatus                      ();
    bool                            Show_AllStatus                      ();

    bool                            Do_Tests                            ();

    bool                            Params_IsModeServer                 ();

    static bool                     Test_XString                        (TESTS* tests);
    static bool                     Test_XBuffer                        (TESTS* tests);
    static bool                     Test_XRand                          (TESTS* tests);
    static bool                     Test_XTrace                         (TESTS* tests);
    static bool                     Test_XLogs                          (TESTS* tests);
    static bool                     Test_XVector                        (TESTS* tests);
    bool                            Test_XTree_AddChilds                (XTREE_NODE_TEST* node, int nchild);
    bool                            Test_XTree_InsertChilds             (XTREE_NODE_TEST* node, int indexchild);
    static bool                     Test_XTree                          (TESTS* tests);
    static bool                     Test_XDir                           (TESTS* tests);
    static bool                     Test_Threads                        (TESTS* tests);
    static bool                     Test_DateTime                       (TESTS* tests);
    static bool                     Test_HASH                           (TESTS* tests);
    static bool                     Test_DIOStreamTCPIPConnection       (TESTS* tests);
    static bool                     Test_XSystem                        (TESTS* tests);
    static bool                     Test_SharedMemory                   (TESTS* tests);    
    static bool                     Test_GPIO                           (TESTS* tests);
    static bool                     Test_WebClient                      (TESTS* tests);
    static bool                     Test_ScraperWeb                     (TESTS* tests);
    static bool                     Test_MPSSE                          (TESTS* tests);
    static bool                     Test_DNSProtocol                    (TESTS* tests);
    static bool                     Test_DIOCheckTCPIPConnections       (TESTS* tests);
    static bool                     Test_WifiEnum                       (TESTS* tests);
    static bool                     Test_WakeOnLAN                      (TESTS* tests);
    static bool                     Test_DIOStreamTLS                   (TESTS* tests);
    static bool                     Test_SystemCPUUsage                 (TESTS* tests);
    static bool                     Test_AppAlerts                      (TESTS* tests);
    static bool                     Test_BluetoothEnum                  (TESTS* tests);
    static bool                     Test_BluetoothLEEnum                (TESTS* tests);
    static bool                     Test_NTP_InternetServices           (TESTS* tests);
    static bool                     Test_Sound                          (TESTS* tests);
    static bool                     Test_ProcessManager                 (TESTS* tests);
    static bool                     Test_GetUserAndDomain               (TESTS* tests);  
    static bool                     Test_I2C_GPIO_MCP2317               (TESTS* tests);
    static bool                     Test_SPI_GPIO_MCP2317               (TESTS* tests);
    static bool                     Test_WifiManagerMode                (TESTS* tests);
    static bool                     Test_NotificationsManager           (TESTS* tests);
    static bool                     Test_ATCommandGSM                   (TESTS* tests);
    static bool                     Test_SNMP                           (TESTS* tests);
    static bool                     Test_XFileXML                       (TESTS* tests);
    static bool                     Test_XFileRIFF                      (TESTS* tests);
    static bool                     Test_DIOStreamUSBConnection         (TESTS* tests);
    static bool                     Test_XFileDFU                       (TESTS* tests);  
    static bool                     Test_SystemHostFile                 (TESTS* tests);  
    static bool                     Test_SystemBatteryLevel             (TESTS* tests);      
    static bool                     Test_LedNeoPixelWS2812B             (TESTS* tests);  
    static bool                     Test_DIOPCap                        (TESTS* tests);
    static bool                     Test_XProperty                      (TESTS* tests);
    static bool                     Test_XLicense                       (TESTS* tests);

    #ifdef WINDOWS
    static bool                     Test_WindowsACL                     (TESTS* tests);
    #endif

    #ifdef LINUX
    static bool                     Test_DBUS                           (TESTS* tests); 
    static bool                     Test_NetWorkManager                 (TESTS* tests);
    static bool                     Test_DeviceBusInputFile             (TESTS* tests);   
    #endif


  private:

    bool                            Test_Hash                           (HASH* HASH, XBUFFER& input, XCHAR* leyend);

    void                            HandleEvent_Scheduler               (XSCHEDULER_XEVENT* event);
    void                            HandleEvent_WebClient               (DIOWEBCLIENT_XEVENT* event);
    void                            HandleEvent                         (XEVENT* xevent);

    static void                     ThreadRunFunction                   (void* param);

    void                            Clean                               ();
    
    APPCHECKRESOURCESHARDWARE*      appcheckresourceshardware;
    APPINTERNETSERVICES*            appinternetservices;

    XTIMER*                         xtimerupdateconsole;
    XMUTEX*                         xmutexshowallstatus;
};


/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif

