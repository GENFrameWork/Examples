/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       NetConn_Protocol.cpp
* 
* @class      NETCONN_PROTOCOL
* @brief      Net Connection Protocol class (DIOCoreProtol example)
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
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "NetConn_Protocol.h"

#include "XFactory.h"
#include "XRand.h"

#include "CipherAES.h"


#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         NETCONN_PROTOCOL::NETCONN_PROTOCOL(DIOCOREPROTOCOL_CFG* protocolCFG)
* @brief      Constructor
* @ingroup    EXAMPLES
* 
* @param[in]  DIOCOREPROTOCOL_CFG* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
NETCONN_PROTOCOL::NETCONN_PROTOCOL(DIOCOREPROTOCOL_CFG* protocolCFG, DIOSTREAM* diostream, XUUID* ID_machine) : DIOCOREPROTOCOL(protocolCFG, diostream, ID_machine)
{
  Clean();

  Commands_Add(NETCONN_PROTOCOL_COMMAND_TYPE_GETVERSION    , NETCONN_PROTOCOL_COMMAND_TYPE_STRING_GETVERSION, DIOCOREPROTOCOL_COMMAND_BIDIRECTIONALITYMODE_BOTH);
  Commands_Add(NETCONN_PROTOCOL_COMMAND_TYPE_OTHERCOMMAND  , NETCONN_PROTOCOL_COMMAND_TYPE_STRING_OTHERCOMMAND, DIOCOREPROTOCOL_COMMAND_BIDIRECTIONALITYMODE_TOCLIENT);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         NETCONN_PROTOCOL::~NETCONN_PROTOCOL()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    EXAMPLES
* 
* --------------------------------------------------------------------------------------------------------------------*/
NETCONN_PROTOCOL::~NETCONN_PROTOCOL()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCONN_PROTOCOL::GenerateAuthenticationChallenge(XBUFFER& autentication_challange)
* @brief      GenerateAuthenticationChallenge
* @ingroup    EXAMPLES
* 
* @param[in]  autentication_challange : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_PROTOCOL::GenerateAuthenticationChallenge(XBUFFER& autentication_challange)
{
  XRAND* rand = GEN_XFACTORY.CreateRand();
  if(!rand)
    {
      return false;
    }

  rand->Ini();

  for(XDWORD c=0; c<NETCONN_PROTOCOL_MAXCHALLANGE; c++)
    {  
      autentication_challange.Add((XBYTE)rand->Max(255));
    }

  GEN_XFACTORY.DeleteRand(rand);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCONN_PROTOCOL::GenerateAuthenticationResponse(XBUFFER& autentication_challange, XBUFFER& autentication_response)
* @brief      GenerateAuthenticationResponse
* @ingroup    EXAMPLES
* 
* @param[in]  autentication_challange : 
* @param[in]  autentication_response : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_PROTOCOL::GenerateAuthenticationResponse(XBUFFER& autentication_challange, XBUFFER& autentication_response)
{
  XBYTE                 ini_data[] = NETCONN_PROTOCOL_AUTHENTICATION_INI;
  XBYTE                 key_data[] = NETCONN_PROTOCOL_AUTHENTICATION_KEY;
  CIPHERKEYSYMMETRICAL  key;
  bool                  status     = false;

  MaskKey(ini_data, sizeof(ini_data), NETCONN_PROTOCOL_VERSION);
  MaskKey(key_data, sizeof(key_data), NETCONN_PROTOCOL_SUBVERSION);

  cipherAES.SetChainingMode(CIPHERCHAININGMODE_CBC);
  cipherAES.SetPaddingType(XBUFFER_PADDINGTYPE_ZEROS);
  cipherAES.SetInitVector(ini_data, sizeof(ini_data));

  key.Set(key_data, sizeof(key_data));

  cipherAES.SetKey(&key);
  cipherAES.Cipher(autentication_challange);
  
  int    resultsize;
  XBYTE* result = cipherAES.GetResult(resultsize);
  if(result)
    {
      autentication_response.Empty();
      autentication_response.Add(result, NETCONN_PROTOCOL_MAXCHALLANGE);

      status = true;
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void NETCONN_PROTOCOL::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    EXAMPLES
* 
* --------------------------------------------------------------------------------------------------------------------*/
void NETCONN_PROTOCOL::Clean()
{

}


#pragma endregion


