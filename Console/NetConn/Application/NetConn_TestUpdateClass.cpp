/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       NetConn_TestUpdateClass.cpp
* 
* @class      NETCONN_TESTUPDATECLASS
* @brief      Net Conn Test UpdateClass  class
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

#include "NetConn_TestUpdateClass.h"

#include "XFactory.h"
#include "XRand.h"

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
* @fn         NETCONN_TESTUPDATECLASS::NETCONN_TESTUPDATECLASS()
* @brief      Constructor
* @ingroup    EXAMPLES
* 
* --------------------------------------------------------------------------------------------------------------------*/
NETCONN_TESTUPDATECLASS::NETCONN_TESTUPDATECLASS()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         NETCONN_TESTUPDATECLASS::~NETCONN_TESTUPDATECLASS()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    EXAMPLES
* 
* --------------------------------------------------------------------------------------------------------------------*/
NETCONN_TESTUPDATECLASS::~NETCONN_TESTUPDATECLASS()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD NETCONN_TESTUPDATECLASS::GetNumber()
* @brief      GetNumber
* @ingroup    EXAMPLES
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD NETCONN_TESTUPDATECLASS::GetNumber()
{
  return number;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void NETCONN_TESTUPDATECLASS::SetNumber(XDWORD number)
* @brief      SetNumber
* @ingroup    EXAMPLES
* 
* @param[in]  number : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void NETCONN_TESTUPDATECLASS::SetNumber(XDWORD number)
{
  this->number = number;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* NETCONN_TESTUPDATECLASS::GetString()
* @brief      GetString
* @ingroup    EXAMPLES
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* NETCONN_TESTUPDATECLASS::GetString()
{
  return &string;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCONN_TESTUPDATECLASS::Update()
* @brief      Update
* @ingroup    EXAMPLES
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_TESTUPDATECLASS::Update()
{
  XRAND* rand = GEN_XFACTORY.CreateRand();
  if(rand)
    {
      rand->Ini();

      number = rand->Between(0, 1024);

      switch(rand->Between(0, 3))
        {              
          case  0 : string = __L("hello, how are you?");    break;
          case  1 : string = __L("hello, Tests 1");         break;
          case  2 : string = __L("hello, Tests 2");         break;
          case  3 : string = __L("hello, Tests 3");         break;        
        }

      GEN_XFACTORY.DeleteRand(rand);
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCONN_TESTUPDATECLASS::Serialize()
* @brief      Serialize
* @ingroup    EXAMPLES
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_TESTUPDATECLASS::Serialize()
{
  Primitive_Add<XDWORD>(number    , NETCONN_TESTUPDATECLASS_NUMBER_STR);  
  Primitive_Add<XSTRING*>(&string  , NETCONN_TESTUPDATECLASS_STRING_STR);  

  return true;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCONN_TESTUPDATECLASS::Deserialize()
* @brief      Deserialize
* @ingroup    EXAMPLES
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_TESTUPDATECLASS::Deserialize()
{
  Primitive_Extract<XDWORD>(number   , NETCONN_TESTUPDATECLASS_NUMBER_STR);
  Primitive_Extract<XSTRING>(string  , NETCONN_TESTUPDATECLASS_STRING_STR);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void NETCONN_TESTUPDATECLASS::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    EXAMPLES
* 
* --------------------------------------------------------------------------------------------------------------------*/
void NETCONN_TESTUPDATECLASS::Clean()
{
  number = 0;  
}


#pragma endregion


