/**-------------------------------------------------------------------------------------------------------------------
*
* @file       NetConn_ConnectionsManager.cpp
*
* @class      NETCONN_CONNECTIONSMANAGER
* @brief      Net Connection Connections Manager class (DIOCoreProtol example)
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

#include "NetConn_ConnectionsManager.h"

#include "XFactory.h"
#include "XPublisher.h"
#include "XRand.h"
#include "XSleep.h"

#include "DIOFactory.h"
#include "DIOStreamTCPIPConfig.h"
#include "DIOStream.h"
#include "DIOCoreProtocol_ConnectionsManager.h"

#include "CipherAES.h"

#include "NetConn_Protocol.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         NETCONN_CONNECTIONSMANAGER::NETCONN_CONNECTIONSMANAGER
* @brief      Constructor
* @ingroup    PLATFORM_COMMON
*
* @param
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
NETCONN_CONNECTIONSMANAGER::NETCONN_CONNECTIONSMANAGER() 
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         NETCONN_CONNECTIONS::~NETCONN_CONNECTIONS
* @brief      Destructor
* @ingroup    PLATFORM_COMMON
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
NETCONN_CONNECTIONSMANAGER::~NETCONN_CONNECTIONSMANAGER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         NETCONN_CONNECTIONSMANAGER::Ini
* @brief      Initialize connection manager
* @ingroup    PLATFORM_COMMON
*
* @param[in]    isserver : is Server or client mode
* @param[in]    isenumlocalactive : Is active the enum (local)
* @param[in]    port : port connection.
* @param[in]    applicationdata : application data global
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_CONNECTIONSMANAGER::Ini(bool isserver)
{  
  protocolCFG.SetIsServer(isserver);  
  protocolCFG.SetCompressHeader(true);
  protocolCFG.SetCompressContent(true);

  // ------------------------------------------------------------------------------------------------------

  DIOSTREAMTCPIPCONFIG*  diostreamTCPIPCFG = NULL;
  DIOSTREAM*             diostreamTCPIP    = NULL;
  
  diostreamTCPIPCFG = new DIOSTREAMTCPIPCONFIG();
  if(!diostreamTCPIPCFG)
    {
      return false;
    }

  diostreamTCPIPCFG->GetRemoteURL()->Set(__L("127.0.0.1"));
  diostreamTCPIPCFG->SetMode(isserver?DIOSTREAMMODE_SERVERMULTISOCKET:DIOSTREAMMODE_CLIENT);
  diostreamTCPIPCFG->SetRemotePort(1230);

  diostreamTCPIP = GEN_DIOFACTORY.CreateStreamIO(diostreamTCPIPCFG);
  if(!diostreamTCPIP) 
    {
      delete diostreamTCPIPCFG;
      return false;
    }

  if(!DIOStream_Add(diostreamTCPIPCFG, diostreamTCPIP))
    {
      delete diostreamTCPIPCFG;
      delete diostreamTCPIP;

      return false;
    }

  // ------------------------------------------------------------------------------------------------------

  return DIOCOREPROTOCOL_CONNECTIONSMANAGER::Ini();  
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         NETCONN_CONNECTIONSMANAGER::End
* @brief      End Connection manager
* @ingroup    PLATFORM_COMMON
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_CONNECTIONSMANAGER::End()
{
  bool status =  false;

  status = DIOCOREPROTOCOL_CONNECTIONSMANAGER::End();

  DIOStream_DeleteAll();
    
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL* NETCONN_CONNECTIONSMANAGER::CreateProtocol(DIOSTREAM* diostream, XUUID* ID_machine)
* @brief      CreateProtocol
* @ingroup    EXAMPLES
* 
* @param[in]  diostream : 
* @param[in]  ID_machine : 
* 
* @return     DIOCOREPROTOCOL* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL* NETCONN_CONNECTIONSMANAGER::CreateProtocol(DIOSTREAM* diostream, XUUID* ID_machine)
{
  DIOCOREPROTOCOL* protocol = (DIOCOREPROTOCOL*)new NETCONN_PROTOCOL(&protocolCFG, diostream, ID_machine);

  return protocol;  
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void NETCONN_CONNECTIONS::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void NETCONN_CONNECTIONSMANAGER::Clean()
{
  
}
