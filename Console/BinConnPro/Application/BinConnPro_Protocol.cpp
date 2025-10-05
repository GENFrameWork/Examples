/**-------------------------------------------------------------------------------------------------------------------
*
* @file       BinConnPro_Protocol.cpp
*
* @class      BINCONNPRO_PROTOCOL
* @brief      Example Binary Connexion Protocol class
* @ingroup    EXAMPLES
*
* @copyright  GEN Group. All right reserved.
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

#include "XFactory.h"
#include "XVariant.h"

#include "BinConnPro_Protocol.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         BINCONNPRO_PROTOCOL::BINCONNPRO_PROTOCOL(DIOSTREAM* diostream) : DIOPROTOCOL(diostream)
* @brief      Constructor
* @ingroup    EXAMPLES
* 
* @param[in]  DIOSTREAM* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
BINCONNPRO_PROTOCOL::BINCONNPRO_PROTOCOL(DIOSTREAM* diostream) : DIOPROTOCOL(diostream)
{
  AddCommand(BINCONNPRO_PROTOCOL_CMDTYPE_GETDEVICETYPEANDID       , __L("")           , __L("DD")                 , RCV_GetDeviceTypeAndID        , __L("GetDeviceTypeAndID")         );
  AddCommand(BINCONNPRO_PROTOCOL_CMDTYPE_GETCENTERNAME            , __L("")           , __L("S")                  , RCV_GetCenterName             , __L("GetCenterName")              );
  AddCommand(BINCONNPRO_PROTOCOL_CMDTYPE_GETLOCATION              , __L("")           , __L("SSSSD")              , RCV_GetLocation               , __L("GetLocation")                );
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BINCONNPRO_PROTOCOL::~BINCONNPRO_PROTOCOL()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
BINCONNPRO_PROTOCOL::~BINCONNPRO_PROTOCOL()
{

}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool BINCONNPRO_PROTOCOL::CMD_GetDeviceTypeAndID(XDWORD& devicetype, XDWORD& deviceID)
* @brief      CMD_GetPOSDeviceTypeAndID
* @ingroup
*
* @param[in]  devicetype :
* @param[in]  deviceID :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO_PROTOCOL::CMD_GetDeviceTypeAndID(XDWORD& devicetype, XDWORD& deviceID)
{
  DIOPROTOCOL_COMMAND* cmd = GetCommand(BINCONNPRO_PROTOCOL_CMDTYPE_GETDEVICETYPEANDID);
  if(!cmd) return false;

  XBUFFER xbuffer;
  bool    result = false;

  if(Command(cmd->GetType(), xbuffer))
    {
      xbuffer.GetWithMask(cmd->GetSOUTMask(), 0, &devicetype, &deviceID);
      result = true;
    }

  SendEventCommand(this, DIOPROTOCOL_DIRECTION_GET, cmd->GetType(), result, NULL, 0);

  return result;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int BINCONNPRO_PROTOCOL::RCV_GetDeviceTypeAndID(DIOPROTOCOL* protocol, DIOPROTOCOL_COMMAND* cmd, XBUFFER& xbuffer, XDWORD rID, XDWORD& param)
* @brief      RCV_GetPOSDeviceTypeAndID
* @ingroup
*
* @param[in]  protocol :
* @param[in]  cmd :
* @param[in]  xbuffer :
* @param[in]  rID :
* @param[in]  param :
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int BINCONNPRO_PROTOCOL::RCV_GetDeviceTypeAndID(DIOPROTOCOL* protocol, DIOPROTOCOL_COMMAND* cmd, XBUFFER& xbuffer, XDWORD rID, XDWORD& param)
{
  if(!protocol) return 0;

  BINCONNPRO_APPLICATIONDATA* applicationdata =   (BINCONNPRO_APPLICATIONDATA*)protocol->GetApplicationData();
  if(!applicationdata) return DIOPROTOCOL_ERRORRECEIVED;

  xbuffer.Delete();

  XDWORD devicetype = (XDWORD)applicationdata->device.GetType();
  XDWORD deviceID   = (XDWORD)applicationdata->device.GetID();

  return xbuffer.AddWithMask(cmd->GetSOUTMask(), devicetype, deviceID);
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool BINCONNPRO_PROTOCOL::CMD_GetCenterName(XSTRING& centername)
* @brief      CMD_GetCenterName
* @ingroup
*
* @param[in]  centername :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO_PROTOCOL::CMD_GetCenterName(XSTRING& centername)
{
  DIOPROTOCOL_COMMAND* cmd = GetCommand(BINCONNPRO_PROTOCOL_CMDTYPE_GETCENTERNAME);
  if(!cmd) return false;

  XBUFFER xbuffer;
  bool    result = false;

  if(Command(cmd->GetType(), xbuffer))
    {
      xbuffer.GetWithMask(cmd->GetSOUTMask(), 0, &centername);
      result = true;
    }

  SendEventCommand(this, DIOPROTOCOL_DIRECTION_GET, cmd->GetType(), result, NULL, 0);

  return result;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int BINCONNPRO_PROTOCOL::RCV_GetCenterName(DIOPROTOCOL* protocol, DIOPROTOCOL_COMMAND* cmd, XBUFFER& xbuffer, XDWORD rID, XDWORD& param)
* @brief      RCV_GetCenterName
* @ingroup
*
* @param[in]  protocol :
* @param[in]  cmd :
* @param[in]  xbuffer :
* @param[in]  rID :
* @param[in]  param :
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int BINCONNPRO_PROTOCOL::RCV_GetCenterName(DIOPROTOCOL* protocol, DIOPROTOCOL_COMMAND* cmd, XBUFFER& xbuffer, XDWORD rID, XDWORD& param)
{
  if(!protocol) return 0;

  BINCONNPRO_APPLICATIONDATA* applicationdata =   (BINCONNPRO_APPLICATIONDATA*)protocol->GetApplicationData();
  if(!applicationdata) return DIOPROTOCOL_ERRORRECEIVED;

  xbuffer.Delete();
  return xbuffer.AddWithMask(cmd->GetSOUTMask(), &applicationdata->centername);
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool BINCONNPRO_PROTOCOL::CMD_GetLocation(XSTRING& street, XSTRING& city, XSTRING& state, XSTRING& country, XDWORD& postalcode)
* @brief      CMD_GetLocation
* @ingroup
*
* @param[in]  street :
* @param[in]  city :
* @param[in]  state :
* @param[in]  country :
* @param[in]  postalcode :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO_PROTOCOL::CMD_GetLocation(XSTRING& street, XSTRING& city, XSTRING& state, XSTRING& country, XDWORD& postalcode)
{
  DIOPROTOCOL_COMMAND* cmd = GetCommand(BINCONNPRO_PROTOCOL_CMDTYPE_GETLOCATION);
  if(!cmd) return false;

  XBUFFER xbuffer;
  bool    result = false;

  if(Command(cmd->GetType(), xbuffer))
    {
      xbuffer.GetWithMask(cmd->GetSOUTMask(), 0, &street, &city, &state, &country, &postalcode);
      result = true;
    }

  SendEventCommand(this, DIOPROTOCOL_DIRECTION_GET, cmd->GetType(), result, NULL, 0);

  return result;
}




/*-------------------------------------------------------------------
//  MACHINEPROTOCOL::RCV_GetLocation
*/
/**
//
//
//
//  ""
//  @version      24/09/2015 11:08:33
//
//  @return       int :
//
//  @param        protocol :
//  @param        cmd :
//  @param        xbuffer :
//  @param        rID :
//  @param        param :
*/
/*-----------------------------------------------------------------*/
int BINCONNPRO_PROTOCOL::RCV_GetLocation(DIOPROTOCOL* protocol, DIOPROTOCOL_COMMAND* cmd, XBUFFER& xbuffer, XDWORD rID, XDWORD& param)
{
  if(!protocol) return 0;

  BINCONNPRO_APPLICATIONDATA* applicationdata =   (BINCONNPRO_APPLICATIONDATA*)protocol->GetApplicationData();
  if(!applicationdata) return DIOPROTOCOL_ERRORRECEIVED;

  xbuffer.Delete();
  return xbuffer.AddWithMask(cmd->GetSOUTMask(), applicationdata->location.GetStreet()
                                               , applicationdata->location.GetCity()
                                               , applicationdata->location.GetState()
                                               , applicationdata->location.GetCountry()
                                               , applicationdata->location.GetPostalCode());
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void BINCONNPRO_PROTOCOL::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void BINCONNPRO_PROTOCOL::Clean()
{

}


