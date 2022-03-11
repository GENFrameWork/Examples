/**-------------------------------------------------------------------------------------------------------------------
*
* @file       BinConnPro_Protocol_Device.cpp
*
* @class      BINCONNPRO_PROTOCOL_DEVICE
* @brief      Example Binary Connexion Protocol Device class
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @copyright  Copyright(c) 2008 - 2016 GEN Group.
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

#include "BinConnPro_Protocol_Device.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BINCONNPRO_PROTOCOL_DEVICE::BINCONNPRO_PROTOCOL_DEVICE()
* @brief      Constructor
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
BINCONNPRO_PROTOCOL_DEVICE::BINCONNPRO_PROTOCOL_DEVICE()
{
  Clean();

   type = BINCONNPRO_PROTOCOL_DEVICETYPE_GENERIC;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BINCONNPRO_PROTOCOL_DEVICE::~BINCONNPRO_PROTOCOL_DEVICE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
BINCONNPRO_PROTOCOL_DEVICE::~BINCONNPRO_PROTOCOL_DEVICE()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BINCONNPRO_PROTOCOL_DEVICETYPE BINCONNPRO_PROTOCOL_DEVICE::GetType()
* @brief      GetType
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     BINCONNPRO_PROTOCOL_DEVICETYPE :
*
*---------------------------------------------------------------------------------------------------------------------*/
BINCONNPRO_PROTOCOL_DEVICETYPE BINCONNPRO_PROTOCOL_DEVICE::GetType()
{
  return type;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void BINCONNPRO_PROTOCOL_DEVICE::SetType(BINCONNPRO_PROTOCOL_DEVICETYPE type)
* @brief      SetType
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  type :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void BINCONNPRO_PROTOCOL_DEVICE::SetType(BINCONNPRO_PROTOCOL_DEVICETYPE type)
{
  this->type = type;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD BINCONNPRO_PROTOCOL_DEVICE::GetID()
* @brief      GetID
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD BINCONNPRO_PROTOCOL_DEVICE::GetID()
{
  return ID;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void BINCONNPRO_PROTOCOL_DEVICE::SetID(XDWORD ID)
* @brief      SetID
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  ID :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void BINCONNPRO_PROTOCOL_DEVICE::SetID(XDWORD ID)
{
  this->ID = ID;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool BINCONNPRO_PROTOCOL_DEVICE::GetDeviceTypeInString(XSTRING& typename)
* @brief      GetDeviceTypeName
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  typename :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO_PROTOCOL_DEVICE::GetDeviceTypeInString(XSTRING& typestring)
{
  typestring.Empty();

  switch(type)
    {
      case BINCONNPRO_PROTOCOL_DEVICETYPE_UNKNOWN : typestring = __L("Desconocido");     break;
      case BINCONNPRO_PROTOCOL_DEVICETYPE_GENERIC : typestring = __L("Generic");         break;
                                        default   : return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void BINCONNPRO_PROTOCOL_DEVICE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void BINCONNPRO_PROTOCOL_DEVICE::Clean()
{
  type = BINCONNPRO_PROTOCOL_DEVICETYPE_UNKNOWN;
  ID   = 0;
}


