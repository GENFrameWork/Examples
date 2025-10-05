/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       NetConn_AgentState.cpp
* 
* @class      NETCONN_AGENTSTATE
* @brief      Net Conn Agent State class
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

#include "NetConn_AgentState.h"

#include "XSystem.h"

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
* @fn         NETCONN_AGENTSTATE::NETCONN_AGENTSTATE()
* @brief      Constructor
* @ingroup    EXAMPLES
* 
* --------------------------------------------------------------------------------------------------------------------*/
NETCONN_AGENTSTATE::NETCONN_AGENTSTATE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         NETCONN_AGENTSTATE::~NETCONN_AGENTSTATE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    EXAMPLES
* 
* --------------------------------------------------------------------------------------------------------------------*/
NETCONN_AGENTSTATE::~NETCONN_AGENTSTATE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD NETCONN_AGENTSTATE::GetTotalMemory()
* @brief      GetTotalMemory
* @ingroup    EXAMPLES
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD NETCONN_AGENTSTATE::GetTotalMemory()
{
  return total_memory;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void NETCONN_AGENTSTATE::SetTotalMemory(XDWORD total_memory)
* @brief      SetTotalMemory
* @ingroup    EXAMPLES
* 
* @param[in]  total_memory : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void NETCONN_AGENTSTATE::SetTotalMemory(XDWORD total_memory)
{
  this->total_memory = total_memory;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD NETCONN_AGENTSTATE::GetFreeMmemory()
* @brief      GetFreeMmemory
* @ingroup    EXAMPLES
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD NETCONN_AGENTSTATE::GetFreeMmemory()
{
  return free_memory;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void NETCONN_AGENTSTATE::SetFreeMemory(XDWORD free_memory)
* @brief      SetFreeMemory
* @ingroup    EXAMPLES
* 
* @param[in]  free_memory : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void NETCONN_AGENTSTATE::SetFreeMemory(XDWORD free_memory)
{
  this->free_memory = free_memory;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCONN_AGENTSTATE::Update()
* @brief      Update
* @ingroup    EXAMPLES
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_AGENTSTATE::Update()
{
  GEN_XSYSTEM.GetMemoryInfo(total_memory, free_memory);

  return true;
}


  
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCONN_AGENTSTATE::Serialize()
* @brief      Serialize
* @ingroup    EXAMPLES
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_AGENTSTATE::Serialize()
{
  Primitive_Add<XDWORD>(total_memory  , NETCONN_AGENTSTATE_TOTALMEMORY_STR);  
  Primitive_Add<XDWORD>(free_memory   , NETCONN_AGENTSTATE_FREEMEMORY_STR);  

  return true;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCONN_AGENTSTATE::Deserialize()
* @brief      Deserialize
* @ingroup    EXAMPLES
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_AGENTSTATE::Deserialize()
{
  Primitive_Extract<XDWORD>(total_memory , NETCONN_AGENTSTATE_TOTALMEMORY_STR);
  Primitive_Extract<XDWORD>(free_memory  , NETCONN_AGENTSTATE_FREEMEMORY_STR);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void NETCONN_AGENTSTATE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    EXAMPLES
* 
* --------------------------------------------------------------------------------------------------------------------*/
void NETCONN_AGENTSTATE::Clean()
{
  total_memory  = 0;
  free_memory   = 0;
}


#pragma endregion


