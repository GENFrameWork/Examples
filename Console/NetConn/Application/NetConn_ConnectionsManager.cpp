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
#include "DIOCoreProtocol.h"
#include "DIOCoreProtocol_ConnectionsManager_XEvent.h"
#include "DIOCoreProtocol_ConnectionsManager.h"

#include "CipherAES.h"

#include "NetConn_Protocol.h"
#include "NetConn_RegisterData.h"

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
  bool status = false;

  // ------------------------------------------------------------------------------------------------------

  protocolCFG.SetIsServer(isserver);  
  protocolCFG.SetIsCipher(true);
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

  status = DIOCOREPROTOCOL_CONNECTIONSMANAGER::Ini(); 

  // ------------------------------------------------------------------------------------------------------

  return status;
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
* @fn         void NETCONN_CONNECTIONSMANAGER::HandleEvent_CoreProtocolConnectionsManager(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT* event)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL  (Only Information)
* @ingroup    EXAMPLES
* 
* @param[in]  event : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void NETCONN_CONNECTIONSMANAGER::HandleEvent_CoreProtocolConnectionsManager(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT* event)
{
  if(!event) 
    {
      return;
    }

  switch(event->GetEventType())
    {
      case DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_CREATECONNECTION  : { DIOCOREPROTOCOL_CONNECTION* connection = event->GetConnection();                                                                                                 
                                                                                if(connection)          
                                                                                  {
                                                                                    if(!connection->GetRegisterData())
                                                                                      {
                                                                                        NETCONN_REGISTERDATA* registerdata = new NETCONN_REGISTERDATA();
                                                                                        if(registerdata)
                                                                                          {
                                                                                            connection->SetRegisterData(registerdata);
                                                                                          }
                                                                                      }

                                                                                    XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Net Conn] Create connection"));
                                                                                  }
                                                                              }
                                                                              break;


      case DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_STATUSCHANGE      : { DIOCOREPROTOCOL_CONNECTION* connection = event->GetConnection();                                                                                                 
                                                                                if(connection)          
                                                                                  {
                                                                                    XSTRING actualstatusstring;
                                                                                    XSTRING nextstatusstring;

                                                                                    connection->Status_GetString(event->GetActualStatus(), actualstatusstring);
                                                                                    connection->Status_GetString(event->GetNextStatus()  , nextstatusstring);

                                                                                    XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Net Conn] Change connection status: %s --> %s"), actualstatusstring.Get(), nextstatusstring.Get());
                                                                                  }
                                                                              }
                                                                              break;

      case DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_READMSG           :
      case DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_WRITEMSG          : { DIOCOREPROTOCOL_CONNECTION* connection = event->GetConnection();                                                                                                 
                                                                                if(connection)          
                                                                                  {
                                                                                    DIOCOREPROTOCOL*         protocol = connection->GetCoreProtocol();
                                                                                    DIOCOREPROTOCOL_MESSAGE* message  = event->GetMsg(); 
                                                                                    if(message && protocol)
                                                                                      {    
                                                                                        DIOCOREPROTOCOL_HEADER* header  = message->GetHeader();
                                                                                        XBUFFER*                content = message->GetContent();

                                                                                        if(protocol && header && content)
                                                                                          {                                                                                            
                                                                                            switch(event->GetEventType())
                                                                                              {
                                                                                                case DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_READMSG   : protocol->ShowDebug(false, header, (*content), false);        
                                                                                                                                                                break;
    
                                                                                                case DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_WRITEMSG  : protocol->ShowDebug(true, header, (*content), false);  
                                                                                                                                                                break;  
                                                                                              }                                                                                                     
                                                                                          }
                                                                                      }
                                                                                  }

                                                                              }
                                                                              break;
    }
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

