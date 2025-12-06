/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       Databases_CFG.cpp
* 
* @class      DATABASES_CFG
* @brief      Example Databases Config class
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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "Databases_CFG.h"

#include "XLog.h"

#include "Databases.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

DATABASES_CFG* DATABASES_CFG::instance = NULL;

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DATABASES_CFG::GetIsInstanced()
* @brief      GetIsInstanced
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DATABASES_CFG::GetIsInstanced()
{
  return instance!=NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DATABASES_CFG& DATABASES_CFG::GetInstance(bool ini)
* @brief      GetInstance
* @ingroup    APPLICATION
* 
* @param[in]  ini : 
* 
* @return     DATABASES_CFG& : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DATABASES_CFG& DATABASES_CFG::GetInstance(bool ini)
{
  if(!instance) instance = new DATABASES_CFG(ini?APPLICATION_NAMEFILE:NULL);

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DATABASES_CFG::DelInstance()
* @brief      DelInstance
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DATABASES_CFG::DelInstance()
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
* @fn         bool DATABASES_CFG::DoVariableMapping()
* @brief      DoVariableMapping
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DATABASES_CFG::DoVariableMapping()
{
  if(!APPFLOWCFG::DoVariableMapping())
    {
      return false;
    }

  //-----------------------------------------------------
  // DATABASE

  AddValue(XFILECFG_VALUETYPE_STRING  , DATABASESCFG_SECTION_DATABASE      , DATABASESCFG_DATABASE_URL                , &db_URL);
  AddValue(XFILECFG_VALUETYPE_INT     , DATABASESCFG_SECTION_DATABASE      , DATABASESCFG_DATABASE_PORT               , &db_port);
  AddValue(XFILECFG_VALUETYPE_STRING  , DATABASESCFG_SECTION_DATABASE      , DATABASESCFG_DATABASE_DATABASENAME       , &db_databasename);
  AddValue(XFILECFG_VALUETYPE_STRING  , DATABASESCFG_SECTION_DATABASE      , DATABASESCFG_DATABASE_USER               , &db_user);
  AddValue(XFILECFG_VALUETYPE_STRING  , DATABASESCFG_SECTION_DATABASE      , DATABASESCFG_DATABASE_PASSWORD           , &db_password);
  AddValue(XFILECFG_VALUETYPE_INT     , DATABASESCFG_SECTION_DATABASE      , DATABASESCFG_DATABASE_TIMEOUTCONNECTION  , &db_timeoutconnection);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DATABASES_CFG::DoDefault()
* @brief      DoDefault
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DATABASES_CFG::DoDefault()
{
  if(!APPFLOWCFG::DoDefault()) 
    {
      return false;
    }

  //------------------------------------------------------------------------------

  GEN_XTRACE_NET_CFG_DEFAULT_01
  
  //------------------------------------------------------------------------------

  log_isactive                            = true;
  log_backupisactive                      = true;
  log_backupmaxfiles                      = 10;
  log_backupiscompress                    = true;

  log_activesectionsID.Empty();

  log_activesectionsID                  += APPFLOW_CFG_LOG_SECTIONID_INITIATION;
  log_activesectionsID                  += __L(",");
  log_activesectionsID                  += APPFLOW_CFG_LOG_SECTIONID_GENERIC;
  log_activesectionsID                  += __L(",");
  log_activesectionsID                  += APPFLOW_CFG_LOG_SECTIONID_STATUSAPP;
  log_activesectionsID                  += __L(",");
  log_activesectionsID                  += APPFLOW_CFG_LOG_SECTIONID_ENDING;

  log_levelmask                         = XLOGLEVEL_ALL;
  log_maxsize                           = 3000;
  log_reductionpercent                  = 10;

  //------------------------------------------------------------------------------

  db_URL                                = __L("");
  db_port                               = 0;
  db_databasename                       = __L("");
  db_user                               = __L("");
  db_password                           = __L("");
  db_timeoutconnection                  = 30;

  //------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* DATABASES_CFG::Database_GetURL()
* @brief      Database_GetURL
* @ingroup    APPLICATION
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DATABASES_CFG::Database_GetURL()
{
  return &db_URL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DATABASES_CFG::Database_GetPort()
* @brief      Database_GetPort
* @ingroup    APPLICATION
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DATABASES_CFG::Database_GetPort()
{
  return db_port;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* DATABASES_CFG::Database_DatabaseName()
* @brief      Database_DatabaseName
* @ingroup    APPLICATION
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DATABASES_CFG::Database_DatabaseName()
{
  return &db_databasename;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* DATABASES_CFG::Database_GetUser()
* @brief      Database_GetUser
* @ingroup    APPLICATION
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DATABASES_CFG::Database_GetUser()
{
  return &db_user;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* DATABASES_CFG::Database_GetPassword()
* @brief      Database_GetPassword
* @ingroup    APPLICATION
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DATABASES_CFG::Database_GetPassword()
{
  return &db_password;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int DATABASES_CFG::Database_GetTimeoutConnection()
* @brief      Database_GetTimeoutConnection
* @ingroup    APPLICATION
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int DATABASES_CFG::Database_GetTimeoutConnection()
{
  return db_timeoutconnection;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DATABASES_CFG::DATABASES_CFG(XCHAR* namefile) : APPFLOWCFG(namefile)
* @brief      Constructor
* @ingroup    APPLICATION
* 
* @param[in]  XCHAR* : 
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DATABASES_CFG::DATABASES_CFG(XCHAR* namefile) : APPFLOWCFG(namefile)
{
  Clean();

  if(namefile)
    {
      Ini<DATABASES_CFG>();
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DATABASES_CFG::~DATABASES_CFG()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    APPLICATION
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DATABASES_CFG::~DATABASES_CFG()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DATABASES_CFG::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    APPLICATION
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DATABASES_CFG::Clean()
{

}

#pragma endregion


