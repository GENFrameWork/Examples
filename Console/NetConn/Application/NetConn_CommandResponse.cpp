/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       NetConn_CommandResponse.cpp
* 
* @class      NETCONN_COMMANDRESPONSE
* @brief      Net Conn Command Response class
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

#include "NetConn_CommandResponse.h"

#include "DIOCoreProtocol_ConnectionsManager_XEvent.h"

#include "NetConn_Protocol.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         NETCONN_COMMANDRESPONSE::NETCONN_COMMANDRESPONSE()
* @brief      Constructor
* @ingroup    EXAMPLES
* 
* --------------------------------------------------------------------------------------------------------------------*/
NETCONN_COMMANDRESPONSE::NETCONN_COMMANDRESPONSE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         NETCONN_COMMANDRESPONSE::~NETCONN_COMMANDRESPONSE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    EXAMPLES
* 
* --------------------------------------------------------------------------------------------------------------------*/
NETCONN_COMMANDRESPONSE::~NETCONN_COMMANDRESPONSE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCONN_COMMANDRESPONSE::Response(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT* event)
* @brief      Response
* @ingroup    EXAMPLES
* 
* @param[in]  event : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_COMMANDRESPONSE::Response(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT* event)
{
  bool status = false;

  DIOCOREPROTOCOL_MESSAGE* message = event->GetMsg();
  if(!message)
    {
      return status;
    }

  DIOCOREPROTOCOL_CONNECTION* connection = event->GetConnection();
  if(!connection)
    {
      return status;
    }

  DIOCOREPROTOCOL* protocol = connection->GetCoreProtocol();
  if(protocol)
    {
      for(XDWORD c=DIOCOREPROTOCOL_COMMAND_TYPE_LASTINTERNAL; c<protocol->Commands_GetAll()->GetSize()+1; c++)        
        {  
          if(!message->GetHeader()->GetOperationParam()->Compare(protocol->Commands_Get(c), true))
            {
              switch(c)
                {
                  case NETCONN_PROTOCOL_COMMAND_TYPE_GETVERSION     : status = Response_GetVersion(event); 
                                                                      break;

                  case NETCONN_PROTOCOL_COMMAND_TYPE_OTHERCOMMAND   : status = Response_OtherCommand(event); 
                                                                      break;    
                }
            }
             
                                                                              
        }                                                                            
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCONN_COMMANDRESPONSE::Response_GetVersion(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT* event)
* @brief      Response_GetVersion
* @ingroup    EXAMPLES
* 
* @param[in]  event : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_COMMANDRESPONSE::Response_GetVersion(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT* event)
{
  event->GetContenteResponseString()->Format(__L("protocol version %d.%d"), NETCONN_PROTOCOL_VERSION, NETCONN_PROTOCOL_SUBVERSION);      

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCONN_COMMANDRESPONSE::Response_OtherCommand(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT* event)
* @brief      Response_OtherCommand
* @ingroup    EXAMPLES
* 
* @param[in]  event : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_COMMANDRESPONSE::Response_OtherCommand(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT* event)
{
  event->GetContenteResponseString()->Format(__L("Other command"));      

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void NETCONN_COMMANDRESPONSE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    EXAMPLES
* 
* --------------------------------------------------------------------------------------------------------------------*/
void NETCONN_COMMANDRESPONSE::Clean()
{
}


#pragma endregion


