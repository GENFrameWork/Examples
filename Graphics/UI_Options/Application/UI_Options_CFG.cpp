/**-------------------------------------------------------------------------------------------------------------------
*
* @file        UI_Options_CFG.cpp
*
* @class       UI_OPTIONS_CFG
* @brief       GEN UI Options Config Example class
* @ingroup     GRAPHIC
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

#include "UI_Options.h"

#include "UI_Options_CFG.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

UI_OPTIONS_CFG* UI_OPTIONS_CFG::instance = NULL;

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_OPTIONS_CFG::GetIsInstanced()
* @brief      GetIsInstanced
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_OPTIONS_CFG::GetIsInstanced()
{
  return instance!=NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         UI_OPTIONS_CFG& UI_OPTIONS_CFG::GetInstance()
* @brief      GetInstance
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     UI_OPTIONS_CFG& :
*
*---------------------------------------------------------------------------------------------------------------------*/
UI_OPTIONS_CFG& UI_OPTIONS_CFG::GetInstance()
{
  if(!instance) instance = new UI_OPTIONS_CFG(APPLICATION_NAMEFILE);

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UI_OPTIONS_CFG::DelInstance()
* @brief      DelInstance
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_OPTIONS_CFG::DelInstance()
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
* @fn         bool UI_OPTIONS_CFG::Default()
* @brief      Default config
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UI_OPTIONS_CFG::Default()
{

  //------------------------------------------------------------------------------

  GEN_XTRACE_NET_CFG_DEFAULT_01

  //------------------------------------------------------------------------------

  log_isactive                            = true;
  log_backupisactive                      = true;
  log_backupmaxfiles                      = 10;
  log_backupiscompress                    = true;

  log_activesectionsID.Empty();

  log_activesectionsID                  += APP_CFG_LOG_SECTIONID_INITIATION;
  log_activesectionsID                  += __L(",");
  log_activesectionsID                  += APP_CFG_LOG_SECTIONID_GENERIC;
  log_activesectionsID                  += __L(",");
  log_activesectionsID                  += APP_CFG_LOG_SECTIONID_STATUSAPP;
  log_activesectionsID                  += __L(",");
  log_activesectionsID                  += APP_CFG_LOG_SECTIONID_ENDING;

  log_levelmask                         = XLOGLEVEL_ALL;
  log_maxsize                           = 3000;
  log_reductionpercent                  = 10;

  //------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         UI_OPTIONS_CFG::UI_OPTIONS_CFG(XCHAR* namefile) : APPLICATIONCFG(namefile)
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
UI_OPTIONS_CFG::UI_OPTIONS_CFG(XCHAR* namefile) : APPCFG(namefile)
{
  Clean();

  Default();

  Ini();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         UI_OPTIONS_CFG::~UI_OPTIONS_CFG()
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
UI_OPTIONS_CFG::~UI_OPTIONS_CFG()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void UI_OPTIONS_CFG::Clean()
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
void UI_OPTIONS_CFG::Clean()
{

}



