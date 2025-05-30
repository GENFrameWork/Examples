/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       Databases_CFG.h
* 
* @class      DATABASES_CFG
* @brief      Example Databases Config class
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

#ifndef _DATABASES_CFG_H_
#define _DATABASES_CFG_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "APPFlowCFG.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

#define DATABASESCFG_SECTION_DATABASE                         __L("database")
#define DATABASESCFG_DATABASE_URL                             __L("url")
#define DATABASESCFG_DATABASE_PORT                            __L("port")
#define DATABASESCFG_DATABASE_DATABASENAME                    __L("databasename")
#define DATABASESCFG_DATABASE_USER                            __L("user")
#define DATABASESCFG_DATABASE_PASSWORD                        __L("password")
#define DATABASESCFG_DATABASE_TIMEOUTCONNECTION               __L("timeoutconnection")

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

class DATABASES_CFG : public APPFLOWCFG
{
  public:


    static bool                     GetIsInstanced                          ();
    static DATABASES_CFG&           GetInstance                             (bool ini = true);
    static bool                     DelInstance                             ();

    bool                            DoVariableMapping                       (); 
    bool                            DoDefault                               ();

    XSTRING*                        Database_GetURL                         ();
    XDWORD                          Database_GetPort                        ();
    XSTRING*                        Database_DatabaseName                   ();
    XSTRING*                        Database_GetUser                        ();
    XSTRING*                        Database_GetPassword                    ();
    int                             Database_GetTimeoutConnection           ();

  private:
                                    DATABASES_CFG                           (XCHAR* namefile);
                                    DATABASES_CFG                           (DATABASES_CFG const&);        // Don't implement
    virtual                        ~DATABASES_CFG                           ();

    void                            operator =                              (DATABASES_CFG const&);        // Don't implement


    void                            Clean                                   ();

    static DATABASES_CFG*           instance;

    XSTRING                         db_URL;
    XDWORD                          db_port;
    XSTRING                         db_databasename;
    XSTRING                         db_user;
    XSTRING                         db_password;
    int                             db_timeoutconnection;
};

#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

