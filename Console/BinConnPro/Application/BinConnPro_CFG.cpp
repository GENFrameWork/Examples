/**-------------------------------------------------------------------------------------------------------------------
*
* @file       BinConnPro_CFG.cpp
*
* @class      BINCONNPRO_CFG
* @brief      BinConnPro Configuration
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
*---------------------------------------------------------------------------------------------------------------------*/


/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XLog.h"

#include "BinConnPro_ConnectionsManager.h"
#include "BinConnPro.h"

#include "BinConnPro_CFG.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

BINCONNPRO_CFG* BINCONNPRO_CFG::instance = NULL;

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool BINCONNPRO_CFG::GetIsInstanced()
* @brief      GetIsInstanced
* @ingroup
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO_CFG::GetIsInstanced()
{
  return instance!=NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BINCONNPRO_CFG& BINCONNPRO_CFG::GetInstance(bool ini)
* @brief      GetInstance
* @ingroup
*
* @return     BINCONNPRO_CFG& :
*
*---------------------------------------------------------------------------------------------------------------------*/
BINCONNPRO_CFG& BINCONNPRO_CFG::GetInstance(bool ini)
{
  if(!instance) instance = new BINCONNPRO_CFG(ini?APPLICATION_NAMEFILE:NULL);

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool BINCONNPRO_CFG::DelInstance()
* @brief      DelInstance
* @ingroup
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO_CFG::DelInstance()
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
* @fn         bool BINCONNPRO_CFG::DoVariableMapping()
* @brief      DoVariableMapping
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO_CFG::DoVariableMapping()
{
  if(!APPFLOWCFG::DoVariableMapping())
    {
      return false;
    }
  
  //-----------------------------------------------------
  // MACHINE PROTOCOL

  AddValue(XFILECFG_VALUETYPE_BOOLEAN , BINCONNPRO_CFG_SECTION_PROTOCOL       , BINCONNPRO_CFG_PROTOCOL_ISACTIVE                      , &protocol_isactive);
  AddValue(XFILECFG_VALUETYPE_BOOLEAN , BINCONNPRO_CFG_SECTION_PROTOCOL       , BINCONNPRO_CFG_PROTOCOL_ISLOCALENUMACTIVE             , &protocol_islocalenumactive);
  AddValue(XFILECFG_VALUETYPE_INT     , BINCONNPRO_CFG_SECTION_PROTOCOL       , BINCONNPRO_CFG_PROTOCOL_PORT                          , &protocol_port);
  AddValue(XFILECFG_VALUETYPE_STRING  , BINCONNPRO_CFG_SECTION_PROTOCOL       , BINCONNPRO_CFG_PROTOCOL_TARGET                        , &protocol_target);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool BINCONNPRO_CFG::DoDefault()
* @brief      DoDefault
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO_CFG::DoDefault()
{
  if(!APPFLOWCFG::DoDefault()) 
    {
      return false;
    }

  //------------------------------------------------------------------------------

  GEN_XTRACE_NET_CFG_DEFAULT_01

  //------------------------------------------------------------------------------

  protocol_isactive                               = false;
  protocol_islocalenumactive                      = false;
  protocol_port                                   = BINCONNPRO_CONNECTIONSMANAGER_PROTOCOLPORTBASE;

  //------------------------------------------------------------------------------


  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool BINCONNPRO_CFG::Protocol_IsActive()
* @brief      Protocol_IsActive
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO_CFG::Protocol_IsActive()
{
  return protocol_isactive;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool BINCONNPRO_CFG::Protocol_IsLocalEnumActive()
* @brief      Protocol_IsLocalEnumActive
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO_CFG::Protocol_IsLocalEnumActive()
{
  return protocol_islocalenumactive;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int BINCONNPRO_CFG::Protocol_GetPort()
* @brief      Protocol_GetPort
* @ingroup    APPLICATION
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int BINCONNPRO_CFG::Protocol_GetPort()
{
  return protocol_port;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* BINCONNPRO_CFG::Protocol_GetTarget()
* @brief      Protocol_GetTarget
* @ingroup    APPLICATION
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* BINCONNPRO_CFG::Protocol_GetTarget()
{
  return &protocol_target;
}





/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BINCONNPRO_CFG::BINCONNPRO_CFG(XCHAR* namefile) : APPLICATIONCFG(namefile)
* @brief      Constructor
* @ingroup
*
* @param[in]  XCHAR* : name of file of config
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
BINCONNPRO_CFG::BINCONNPRO_CFG(XCHAR* namefile) : APPFLOWCFG(namefile)
{
  Clean();

 if(namefile)
   {
     Ini<BINCONNPRO_CFG>();
   }
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BINCONNPRO_CFG::~BINCONNPRO_CFG()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
BINCONNPRO_CFG::~BINCONNPRO_CFG()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void BINCONNPRO_CFG::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void BINCONNPRO_CFG::Clean()
{
  protocol_isactive            = false;
  protocol_islocalenumactive   = false;
  protocol_port                = 0;
}

