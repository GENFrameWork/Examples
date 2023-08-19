/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       TSA_CFG.cpp
* 
* @class      TSA_CFG
* @brief      GEN TSA (Test Script Automatic) Example Config
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

/*---- PRECOMPILATION INCLUDES ----------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#include "TSA_CFG.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XLog.h"

#include "TSA.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

TSA_CFG* TSA_CFG::instance = NULL;

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TSA_CFG::GetIsInstanced()
* @brief      GetIsInstanced
* @ingroup    EXAMPLES
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool TSA_CFG::GetIsInstanced()
{
  return instance!=NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TSA_CFG& TSA_CFG::GetInstance(bool ini)
* @brief      GetInstance
* @ingroup    EXAMPLES
* 
* @param[in]  ini : 
* 
* @return     TSA_CFG& : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TSA_CFG& TSA_CFG::GetInstance(bool ini)
{
  if(!instance) instance = new TSA_CFG(ini?APPLICATION_NAMEFILE:NULL);

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TSA_CFG::DelInstance()
* @brief      DelInstance
* @ingroup    EXAMPLES
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool TSA_CFG::DelInstance()
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
* @fn         bool TSA_CFG::DoVariableMapping()
* @brief      DoVariableMapping
* @ingroup    EXAMPLES
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool TSA_CFG::DoVariableMapping()
{
  if(!APPCFG::DoVariableMapping())
    {
      return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TSA_CFG::DoDefault()
* @brief      DoDefault
* @ingroup    EXAMPLES
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool TSA_CFG::DoDefault()
{
  if(!APPCFG::DoDefault()) 
    {
      return false;
    }

  //------------------------------------------------------------------------------

  GEN_XTRACE_NET_CFG_DEFAULT_01
  
  //------------------------------------------------------------------------------

  log_isactive                          = true;
  log_backupisactive                    = true;
  log_backupmaxfiles                    = 10;
  log_backupiscompress                  = true;

  log_activesectionsID.Empty();

  log_activesectionsID                 += APP_CFG_LOG_SECTIONID_INITIATION;
  log_activesectionsID                 += __L(",");
  log_activesectionsID                 += APP_CFG_LOG_SECTIONID_GENERIC;
  log_activesectionsID                 += __L(",");
  log_activesectionsID                 += APP_CFG_LOG_SECTIONID_STATUSAPP;
  log_activesectionsID                 += __L(",");
  log_activesectionsID                 += APP_CFG_LOG_SECTIONID_ENDING;

  log_levelmask                         = XLOGLEVEL_ALL;
  log_maxsize                           = 3000;
  log_reductionpercent                  = 10;

  //------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TSA_CFG::TSA_CFG(XCHAR* namefile)
* @brief      Constructor
* @ingroup    EXAMPLES
* 
* @param[in]  XCHAR* : 
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TSA_CFG::TSA_CFG(XCHAR* namefile) : APPCFG(namefile)
{
  Clean();

  if(namefile)
    {
      Ini<TSA_CFG>();
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TSA_CFG::~TSA_CFG()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    EXAMPLES
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TSA_CFG::~TSA_CFG()

{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void TSA_CFG::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    EXAMPLES
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void TSA_CFG::Clean()
{

}


#pragma endregion

