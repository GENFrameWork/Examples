/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       Canvas2D_CFG.cpp
* 
* @class      CANVAS2D_CFG
* @brief      Graphics Canvas 2D CFG Example class
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

#include "Canvas2D_CFG.h"

#include "XLog.h"

#include "Canvas2D.h"

#include "Canvas2D_CFG.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

CANVAS2D_CFG* CANVAS2D_CFG::instance = NULL;

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool CANVAS2D_CFG::GetIsInstanced()
* @brief      GetIsInstanced
* @ingroup
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool CANVAS2D_CFG::GetIsInstanced()
{
  return instance!=NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         CANVAS2D_CFG& CANVAS2D_CFG::GetInstance(bool ini)
* @brief      GetInstance
* @ingroup
*
* @return     CANVAS2D_CFG& :
*
*---------------------------------------------------------------------------------------------------------------------*/
CANVAS2D_CFG& CANVAS2D_CFG::GetInstance(bool ini)
{
  if(!instance) instance = new CANVAS2D_CFG(APPLICATION_NAMEFILE);

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool CANVAS2D_CFG::DelInstance()
* @brief      DelInstance
* @ingroup
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool CANVAS2D_CFG::DelInstance()
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
* @fn         bool CANVAS2D_CFG::DoVariableMapping()
* @brief      DoVariableMapping
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CANVAS2D_CFG::DoVariableMapping()
{
  if(!APPFLOWCFG::DoVariableMapping())
    {
      return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CANVAS2D_CFG::DoDefault()
* @brief      DoDefault
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CANVAS2D_CFG::DoDefault()
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

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         CANVAS2D_CFG::CANVAS2D_CFG(XCHAR* namefile) : APPLICATIONCFG(namefile)
* @brief      Constructor
* @ingroup
*
* @param[in]  XCHAR* : name of file of config
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
CANVAS2D_CFG::CANVAS2D_CFG(XCHAR* namefile) : APPFLOWCFG(namefile)
{
  Clean();

  if(namefile)
    {
      Ini<CANVAS2D_CFG>();
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         CANVAS2D_CFG::~CANVAS2D_CFG()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
CANVAS2D_CFG::~CANVAS2D_CFG()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void CANVAS2D_CFG::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void CANVAS2D_CFG::Clean()
{

}


#pragma endregion

