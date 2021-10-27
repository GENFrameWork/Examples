/**-------------------------------------------------------------------------------------------------------------------
*
* @file        Tests_CFG.cpp
*
* @class       TESTS_CFG
* @brief       Tests Configuration
* @ingroup     SCRIPT
*
* @author      Abraham J. Velez
* @date       01/03/2016 12:30
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


/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XLog.h"

#include "Tests.h"

#include "Tests_CFG.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

TESTS_CFG* TESTS_CFG::instance = NULL;

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS_CFG::GetIsInstanced()
* @brief      GetIsInstanced
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS_CFG::GetIsInstanced()
{
  return instance!=NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TESTS_CFG& TESTS_CFG::GetInstance()
* @brief      GetInstance
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     TESTS_CFG& :
*
*---------------------------------------------------------------------------------------------------------------------*/
TESTS_CFG& TESTS_CFG::GetInstance()
{
  if(!instance) instance = new TESTS_CFG(APPLICATION_NAMEFILE);

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS_CFG::DelInstance()
* @brief      DelInstance
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS_CFG::DelInstance()
{
  if(instance)
    {
      delete instance;
      instance = NULL;

      return true;
    }

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* TESTS_CFG::Database_GetURL()
* @brief      Database_GetURL
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* TESTS_CFG::Database_GetURL()
{
  return &db_URL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD TESTS_CFG::Database_GetPort()
* @brief      Database_GetPort
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD TESTS_CFG::Database_GetPort()
{
  return db_port;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* TESTS_CFG::Database_DatabaseName()
* @brief      Database_DatabaseName
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* TESTS_CFG::Database_DatabaseName()
{
  return &db_databasename;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* TESTS_CFG::Database_GetUser()
* @brief      Database_GetUser
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* TESTS_CFG::Database_GetUser()
{
  return &db_user;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* TESTS_CFG::Database_GetPassword()
* @brief      Database_GetPassword
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* TESTS_CFG::Database_GetPassword()
{
  return &db_password;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int TESTS_CFG::Database_GetTimeoutConnection()
* @brief      Database_GetTimeoutConnection
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int TESTS_CFG::Database_GetTimeoutConnection()
{
  return db_timeoutconnection;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS_CFG::Default()
* @brief      Default config
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTS_CFG::Default()
{
  //------------------------------------------------------------------------------

  checkresourceshardware_memstatuscheckcadence    = 30;
  checkresourceshardware_memstatuslimitpercent    = 5;
  checkresourceshardware_cpuusagecheckcadence     = 20;
  checkresourceshardware_cpuusagelimitpercent     = 70;  
  checkresourceshardware_cpuusageprocessname     = APPLICATION_NAMEAPP; 


  GEN_XTRACE_NET_CFG_DEFAULT_01
  GEN_XTRACE_NET_CFG_DEFAULT_LOCAL

  //------------------------------------------------------------------------------

  log_isactive                                    = true;
  log_backupisactive                              = true;
  log_backupmaxfiles                              = 10;
  log_backupiscompress                            = true;

  log_activesectionsID.Empty();

  log_activesectionsID                           += APP_CFG_LOG_SECTIONID_INITIATION;
  log_activesectionsID                           += __L(",");
  log_activesectionsID                           += APP_CFG_LOG_SECTIONID_GENERIC;
  log_activesectionsID                           += __L(",");
  log_activesectionsID                           += APP_CFG_LOG_SECTIONID_STATUSAPP;
  log_activesectionsID                           += __L(",");
  log_activesectionsID                           += APP_CFG_LOG_SECTIONID_ENDING;

  log_levelmask                                   = XLOGLEVEL_ALL;
  log_maxsize                                     = 3000;
  log_reductionpercent                            = 10;

  //------------------------------------------------------------------------------

  db_URL                                          = __L("");
  db_port                                         = 0;
  db_databasename                                 = __L("");
  db_user                                         = __L("");
  db_password                                     = __L("");
  db_timeoutconnection                            = 30;

  //------------------------------------------------------------------------------

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TESTS_CFG::TESTS_CFG(XCHAR* namefile) : APPLICATIONCFG(namefile)
* @brief      Constructor
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param[in]  XCHAR* : name of file of config
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
TESTS_CFG::TESTS_CFG(XCHAR* namefile) : APPCFG(namefile)
{
  Clean();

  //-----------------------------------------------------
  // DATABASE

  AddValue(XFILECFG_VALUETYPE_STRING  , TESTSCFG_SECTION_DATABASE      , TESTSCFG_DATABASE_URL                , &db_URL);
  AddValue(XFILECFG_VALUETYPE_INT     , TESTSCFG_SECTION_DATABASE      , TESTSCFG_DATABASE_PORT               , &db_port);
  AddValue(XFILECFG_VALUETYPE_STRING  , TESTSCFG_SECTION_DATABASE      , TESTSCFG_DATABASE_DATABASENAME       , &db_databasename);
  AddValue(XFILECFG_VALUETYPE_STRING  , TESTSCFG_SECTION_DATABASE      , TESTSCFG_DATABASE_USER               , &db_user);
  AddValue(XFILECFG_VALUETYPE_STRING  , TESTSCFG_SECTION_DATABASE      , TESTSCFG_DATABASE_PASSWORD           , &db_password);
  AddValue(XFILECFG_VALUETYPE_INT     , TESTSCFG_SECTION_DATABASE      , TESTSCFG_DATABASE_TIMEOUTCONNECTION  , &db_timeoutconnection);

  Default();

  Ini();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TESTS_CFG::~TESTS_CFG()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
TESTS_CFG::~TESTS_CFG()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void TESTS_CFG::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void TESTS_CFG::Clean()
{

}


