/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       NetConn_CoreProtocol_Connection.cpp
* 
* @class      NETCONN_COREPROTOCOL_CONNECTION
* @brief      Net Connection Core Protocol Connection class (DIOCoreProtol example)
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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "NetConn_CoreProtocol_Connection.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         NETCONN_COREPROTOCOL_CONNECTION::NETCONN_COREPROTOCOL_CONNECTION()
* @brief      Constructor
* @ingroup    EXAMPLES
* 
* --------------------------------------------------------------------------------------------------------------------*/
NETCONN_COREPROTOCOL_CONNECTION::NETCONN_COREPROTOCOL_CONNECTION()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         NETCONN_COREPROTOCOL_CONNECTION::~NETCONN_COREPROTOCOL_CONNECTION()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    EXAMPLES
* 
* --------------------------------------------------------------------------------------------------------------------*/
NETCONN_COREPROTOCOL_CONNECTION::~NETCONN_COREPROTOCOL_CONNECTION()
{
  if(IsServer())
    {
      delete agentstate;
      delete testupdateclass;
    }

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         NETCONN_AGENTSTATE* NETCONN_COREPROTOCOL_CONNECTION::GetAgentState()
* @brief      GetAgentState
* @ingroup    EXAMPLES
* 
* @return     NETCONN_AGENTSTATE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
NETCONN_AGENTSTATE* NETCONN_COREPROTOCOL_CONNECTION::GetAgentState()
{
  return agentstate;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void NETCONN_COREPROTOCOL_CONNECTION::SetAgentState(NETCONN_AGENTSTATE* agentstate)
* @brief      SetAgentState
* @ingroup    EXAMPLES
* 
* @param[in]  agentstate : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void NETCONN_COREPROTOCOL_CONNECTION::SetAgentState(NETCONN_AGENTSTATE* agentstate)
{
  this->agentstate = agentstate;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         NETCONN_TESTUPDATECLASS* NETCONN_COREPROTOCOL_CONNECTION::GetTestUpdateClass()
* @brief      GetTestUpdateClass
* @ingroup    EXAMPLES
* 
* @return     NETCONN_TESTUPDATECLASS* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
NETCONN_TESTUPDATECLASS* NETCONN_COREPROTOCOL_CONNECTION::GetTestUpdateClass()
{
  return testupdateclass;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void NETCONN_COREPROTOCOL_CONNECTION::SetTestUpdateClass(NETCONN_TESTUPDATECLASS* testupdateclass)
* @brief      SetTestUpdateClass
* @ingroup    EXAMPLES
* 
* @param[in]  testupdateclass : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void NETCONN_COREPROTOCOL_CONNECTION::SetTestUpdateClass(NETCONN_TESTUPDATECLASS* testupdateclass)
{
  this->testupdateclass = testupdateclass;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void NETCONN_COREPROTOCOL_CONNECTION::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    EXAMPLES
* 
* --------------------------------------------------------------------------------------------------------------------*/
void NETCONN_COREPROTOCOL_CONNECTION::Clean()
{
  agentstate      = NULL;
  testupdateclass = NULL;
}


#pragma endregion

