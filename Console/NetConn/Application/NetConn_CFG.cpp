/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       NetConn_CFG.cpp
* 
* @class      NETCONN_CFG
* @brief      Net Connection CFG class (DIOCoreProtol example)
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

#include "NetConn_CFG.h"

#include "XLog.h"

#include "NetConn.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

NETCONN_CFG* NETCONN_CFG::instance = NULL;

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool NETCONN_CFG::GetIsInstanced()
* @brief      GetIsInstanced
* @ingroup
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_CFG::GetIsInstanced()
{
  return instance!=NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         NETCONN_CFG& NETCONN_CFG::GetInstance(bool ini)
* @brief      GetInstance
* @ingroup
*
* @return     NETCONN_CFG& :
*
*---------------------------------------------------------------------------------------------------------------------*/
NETCONN_CFG& NETCONN_CFG::GetInstance(bool ini)
{
  if(!instance) instance = new NETCONN_CFG(ini?APPLICATION_NAMEFILE:NULL);

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool NETCONN_CFG::DelInstance()
* @brief      DelInstance
* @ingroup
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_CFG::DelInstance()
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
* @fn         bool NETCONN_CFG::DoVariableMapping()
* @brief      DoVariableMapping
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_CFG::DoVariableMapping()
{
  if(!APPFLOWCFG::DoVariableMapping())
    {
      return false;
    }

  //-----------------------------------------------------
  // Connection

  AddValue(XFILECFG_VALUETYPE_BOOLEAN   , NETCONN_CFG_SECTION_CONNECTION        , NETCONN_CFG_CONNECTION_ISSERVER                , &connection_isserver                                 , __L("Is server active")                                                                 , APPFLOW_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_STRING    , NETCONN_CFG_SECTION_CONNECTION        , NETCONN_CFG_CONNECTION_TRANSPORTTYPE           , &connection_transporttype                            , __L("Transport type")                                                                   , APPFLOW_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_STRING    , NETCONN_CFG_SECTION_CONNECTION        , NETCONN_CFG_CONNECTION_TRANSPORTCONFIG         , &connection_transportconfig                          , __L("Transport config")                                                                 , APPFLOW_CFG_DEFAULT_REMARK_COLUMN);
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCONN_CFG::DoDefault()
* @brief      DoDefault
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_CFG::DoDefault()
{
  if(!APPFLOWCFG::DoDefault()) 
    {
      return false;
    }

  //------------------------------------------------------------------------------

  GEN_XTRACE_NET_CFG_DEFAULT_01

  //------------------------------------------------------------------------------

  connection_isserver         = true;  
  connection_transporttype    = __L("TCPIP");
  connection_transportconfig  = __L("192.168.1.3:1234");

  //------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCONN_CFG::Connection_IsServer()
* @brief      connection  is server
* @ingroup    EXAMPLES
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_CFG::Connection_IsServer()
{
  return connection_isserver;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* NETCONN_CFG::Connection_GetTransportType()
* @brief      connection  get transport type
* @ingroup    EXAMPLES
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* NETCONN_CFG::Connection_GetTransportType()
{
  return &connection_transporttype;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* NETCONN_CFG::Connection_GetTransportConfig()
* @brief      connection  get transport config
* @ingroup    EXAMPLES
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* NETCONN_CFG::Connection_GetTransportConfig()
{
  return &connection_transportconfig;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         NETCONN_CFG::NETCONN_CFG(XCHAR* namefile) : APPFLOWCFG(namefile)
* @brief      Constructor
* @ingroup    EXAMPLES
* 
* @param[in]  namefile : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
NETCONN_CFG::NETCONN_CFG(XCHAR* namefile) : APPFLOWCFG(namefile)
{
  Clean();

 if(namefile)
   {
     Ini<NETCONN_CFG>();
   }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         NETCONN_CFG::~NETCONN_CFG()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
NETCONN_CFG::~NETCONN_CFG()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void NETCONN_CFG::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void NETCONN_CFG::Clean()
{
  connection_isserver         = false;  
  connection_transporttype    = __L("");
  connection_transportconfig  = __L("");
}


#pragma endregion

