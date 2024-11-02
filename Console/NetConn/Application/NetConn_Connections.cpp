/**-------------------------------------------------------------------------------------------------------------------
*
* @file       NetConn_Connections.cpp
*
* @class      NETCONN_CONNECTIONS
* @brief      Net Connection Connections class (DIOCoreProtol example)
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

#include "NetConn_Connections.h"

#include "XPublisher.h"

#include "DIOFactory.h"
#include "DIOStreamTCPIPConfig.h"
#include "DIOStream.h"
#include "DIOCoreProtocol_ConnectionsManager.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         NETCONN_CONNECTIONS::NETCONN_CONNECTIONS
* @brief      Constructor
* @ingroup    PLATFORM_COMMON
*
* @param
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
NETCONN_CONNECTIONS::NETCONN_CONNECTIONS() 
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
NETCONN_CONNECTIONS::~NETCONN_CONNECTIONS()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         NETCONN_CONNECTIONS::Ini
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
bool NETCONN_CONNECTIONS::Ini(bool isserver)
{  
  protocolCFG.SetIsServer(isserver);  
  protocolCFG.SetCompressContent(true);

  // ------------------------------------------------------------------------------------------------------

  DIOSTREAMTCPIPCONFIG*  diostreamTCPIPCFG = new DIOSTREAMTCPIPCONFIG();
  DIOSTREAM*             diostreamTCPIP    = NULL;
  
  diostreamTCPIPCFG->GetRemoteURL()->Set(__L("127.0.0.1"));
  diostreamTCPIPCFG->SetMode(isserver?DIOSTREAMMODE_SERVERMULTISOCKET:DIOSTREAMMODE_CLIENT);
  diostreamTCPIPCFG->SetRemotePort(1230);

  diostreamTCPIP = GEN_DIOFACTORY.CreateStreamIO(diostreamTCPIPCFG);
  if(!diostreamTCPIP) 
    {
      delete diostreamTCPIPCFG;
      return false;
    }

  if(!protocolCFG.DIOStream_Add(diostreamTCPIPCFG, diostreamTCPIP))
    {
      delete diostreamTCPIPCFG;
      delete diostreamTCPIP;

      return false;
    }

  // ------------------------------------------------------------------------------------------------------

  return DIOCOREPROTOCOL_CONNECTIONSMANAGER::Ini(&protocolCFG);  
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         NETCONN_CONNECTIONS::End
* @brief      End Connection manager
* @ingroup    PLATFORM_COMMON
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_CONNECTIONS::End()
{
  bool status =  false;

  status = DIOCOREPROTOCOL_CONNECTIONSMANAGER::End();

  protocolCFG.DIOStream_DeleteAll();
    
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_CFG* NETCONN_CONNECTIONS::GetProtocolCFG()
* @brief      GetProtocolCFG
* @ingroup    EXAMPLES
* 
* @return     DIOCOREPROTOCOL_CFG* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_CFG* NETCONN_CONNECTIONS::GetProtocolCFG()
{
  return &protocolCFG;
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
void NETCONN_CONNECTIONS::Clean()
{
  
}

