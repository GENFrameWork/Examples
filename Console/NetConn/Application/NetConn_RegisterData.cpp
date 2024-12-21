/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       NetConn_RegisterData.cpp
* 
* @class      NETCONN_REGISTERDATA
* @brief      Net Connection Register Data class
* @ingroup    DATAIO
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
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "NetConn_RegisterData.h"

#include "XSystem.h"

#include "HashSHA2.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         NETCONN_REGISTERDATA::NETCONN_REGISTERDATA()
* @brief      Constructor
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
NETCONN_REGISTERDATA::NETCONN_REGISTERDATA()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         NETCONN_REGISTERDATA::~NETCONN_REGISTERDATA()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
NETCONN_REGISTERDATA::~NETCONN_REGISTERDATA()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCONN_REGISTERDATA::InitializeData(bool isserver)
* @brief      InitializeData
* @ingroup    EXAMPLES
* 
* @param[in]  isserver : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_REGISTERDATA::InitializeData(bool isserver)
{
  bool status = DIOCOREPROTOCOL_REGISTERDATA::InitializeData(isserver);

  if(isserver)
    {
      group    = __L("Main Group");
      subgroup = __L("Sub Group");
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* NETCONN_REGISTERDATA::GetGroup()
* @brief      GetGroup
* @ingroup    EXAMPLES
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* NETCONN_REGISTERDATA::GetGroup()
{
  return &group;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* NETCONN_REGISTERDATA::GetSubGroup()
* @brief      GetSubGroup
* @ingroup    EXAMPLES
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* NETCONN_REGISTERDATA::GetSubGroup()
{
  return &subgroup;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCONN_REGISTERDATA::Serialize()
* @brief      Serialize
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_REGISTERDATA::Serialize()
{ 
  bool status = DIOCOREPROTOCOL_REGISTERDATA::Serialize();

  Primitive_Add<XSTRING*>(&group   , NETCONN_REGISTERDATA_HEADER_VAR_GROUP);  
  Primitive_Add<XSTRING*>(&subgroup, NETCONN_REGISTERDATA_HEADER_VAR_SUBGROUP);  

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCONN_REGISTERDATA::Deserialize()
* @brief      Deserialize
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_REGISTERDATA::Deserialize()
{   
  bool status = DIOCOREPROTOCOL_REGISTERDATA::Deserialize();

  Primitive_Extract<XSTRING&>(group   , NETCONN_REGISTERDATA_HEADER_VAR_GROUP);
  Primitive_Extract<XSTRING&>(subgroup, NETCONN_REGISTERDATA_HEADER_VAR_SUBGROUP);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void NETCONN_REGISTERDATA::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
void NETCONN_REGISTERDATA::Clean()
{
}


#pragma endregion


