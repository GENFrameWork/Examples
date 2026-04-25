/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       IiniBase_CFG.cpp
* 
* @class      INIBASE_CFG
* @brief      Ini Base (Start to make GEN_NEW APP) (CFG class)
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

#include "GEN_Defines.h"



/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "IniBase_CFG.h"

#include "XLog.h"

#include "IniBase.h"



/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"




/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

INIBASE_CFG* INIBASE_CFG::instance = NULL;



/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INIBASE_CFG::GetIsInstanced()
* @brief      GetIsInstanced
* @ingroup
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool INIBASE_CFG::GetIsInstanced()
{
  return instance!=NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INIBASE_CFG& INIBASE_CFG::GetInstance(bool ini)
* @brief      GetInstance
* @ingroup
*
* @return     INIBASE_CFG& :
*
*---------------------------------------------------------------------------------------------------------------------*/
INIBASE_CFG& INIBASE_CFG::GetInstance(bool ini)
{
  if(!instance) instance = GEN_NEW INIBASE_CFG(ini?APPLICATION_NAMEFILE:NULL);

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INIBASE_CFG::DelInstance()
* @brief      DelInstance
* @ingroup
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool INIBASE_CFG::DelInstance()
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
* @fn         bool INIBASE_CFG::DoVariableMapping()
* @brief      DoVariableMapping
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INIBASE_CFG::DoVariableMapping()
{
  if(!APPFLOWCFG::DoVariableMapping())
    {
      return false;
    }

  //-----------------------------------------------------
  // Connection

  //AddValue(XFILECFG_VALUETYPE_BOOLEAN   , INIBASE_CFG_SECTION_CONNECTION        , INIBASE_CFG_CONNECTION_ISSERVER                , &connection_isserver                                 , __L("Is server active")                                                                 , APPFLOW_CFG_DEFAULT_REMARK_COLUMN);
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INIBASE_CFG::DoDefault()
* @brief      DoDefault
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INIBASE_CFG::DoDefault()
{
  if(!APPFLOWCFG::DoDefault()) 
    {
      return false;
    }

  //------------------------------------------------------------------------------

  GEN_XTRACE_NET_CFG_DEFAULT_01
  
  //------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         INIBASE_CFG::INIBASE_CFG(XCHAR* namefile) : APPFLOWCFG(namefile)
* @brief      Constructor
* @ingroup    EXAMPLES
* 
* @param[in]  namefile : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
INIBASE_CFG::INIBASE_CFG(XCHAR* namefile) : APPFLOWCFG(namefile)
{
  Clean();

 if(namefile)
   {
     Ini<INIBASE_CFG>();
   }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INIBASE_CFG::~INIBASE_CFG()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
INIBASE_CFG::~INIBASE_CFG()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void INIBASE_CFG::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void INIBASE_CFG::Clean()
{

}



