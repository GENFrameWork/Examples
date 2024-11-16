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

  for(XDWORD c=0; c<64; c++)
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
  #define NETCONN_INI   { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F }
  #define NETCONN_KEY   { 0x60, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe, 0x2b, 0x73, 0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81, 0x1f, 0x35, 0x2c, 0x07, 0x3b, 0x61, 0x08, 0xd7, 0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14, 0xdf, 0xf4 }

  XBYTE                 ini_data[] = NETCONN_INI;
  XBYTE                 key_data[] = NETCONN_KEY;
  CIPHERKEYSYMMETRICAL  key;
  bool                  status     = false;

  CIPHERAES* cipher = new CIPHERAES();
  if(!cipher) 
    {
      return false;
    }

  cipher->SetChainingMode(CIPHERCHAININGMODE_CBC);
  cipher->SetPaddingType(XBUFFER_PADDINGTYPE_ZEROS);
  cipher->SetInitVector(ini_data, sizeof(ini_data));

  key.Set(key_data, sizeof(key_data));

  cipher->SetKey(&key);

  cipher->Cipher(autentication_challange);
  
  int    resultsize;
  XBYTE* result = cipher->GetResult(resultsize);
  if(result)
    {
      autentication_response.Empty();
      autentication_response.Add(result, resultsize);

      status = true;
    }

  delete cipher;

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


