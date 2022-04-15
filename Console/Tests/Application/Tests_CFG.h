/**-------------------------------------------------------------------------------------------------------------------
*
* @file        Tests_CFG.h
*
* @class       TESTS_CFG
* @brief       Tests Configuration
* @ingroup     SCRIPT
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

#ifndef _TESTSCFG_H_
#define _TESTSCFG_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "APPCFG.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define TESTSCFG_SECTION_DATABASE                         __L("database")
#define TESTSCFG_DATABASE_URL                             __L("url")
#define TESTSCFG_DATABASE_PORT                            __L("port")
#define TESTSCFG_DATABASE_DATABASENAME                    __L("databasename")
#define TESTSCFG_DATABASE_USER                            __L("user")
#define TESTSCFG_DATABASE_PASSWORD                        __L("password")
#define TESTSCFG_DATABASE_TIMEOUTCONNECTION               __L("timeoutconnection")

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class TESTS_CFG : public APPCFG
{
  public:


    static bool                     GetIsInstanced                          ();
    static TESTS_CFG&               GetInstance                             ();
    static bool                     DelInstance                             ();

    XSTRING*                        Database_GetURL                         ();
    XDWORD                          Database_GetPort                        ();
    XSTRING*                        Database_DatabaseName                   ();
    XSTRING*                        Database_GetUser                        ();
    XSTRING*                        Database_GetPassword                    ();
    int                             Database_GetTimeoutConnection           ();

    bool                            Default                                 ();

  private:
                                    TESTS_CFG                           (XCHAR* namefile);
                                    TESTS_CFG                           (TESTS_CFG const&);        // Don't implement
    virtual                        ~TESTS_CFG                           ();

    void                            operator =                              (TESTS_CFG const&);        // Don't implement


    void                            Clean                                   ();

    static TESTS_CFG*               instance;

    XSTRING                         db_URL;
    XDWORD                          db_port;
    XSTRING                         db_databasename;
    XSTRING                         db_user;
    XSTRING                         db_password;
    int                             db_timeoutconnection;
};



/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif


