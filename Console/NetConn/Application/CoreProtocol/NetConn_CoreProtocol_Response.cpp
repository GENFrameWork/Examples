/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       NetConn_CoreProtocol_Response.cpp
* 
* @class      NETCONN_COREPROTOCOL_RESPONSE
* @brief      Net Conn Core Protocol Response class
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

#include "NetConn_CoreProtocol_Response.h"

#include "DIOCoreProtocol_ConnectionsManager_XEvent.h"
#include "DIOCoreProtocol_ConnectionsManager.h"

#include "NetConn_CoreProtocol.h"
#include "NetConn_CoreProtocol_Connection.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/

#pragma region CLASS_NETCONN_COREPROTOCOL_RESPONSE


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         NETCONN_COREPROTOCOL_RESPONSE::NETCONN_COREPROTOCOL_RESPONSE()
* @brief      Constructor
* @ingroup    EXAMPLES
* 
* --------------------------------------------------------------------------------------------------------------------*/
NETCONN_COREPROTOCOL_RESPONSE::NETCONN_COREPROTOCOL_RESPONSE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         NETCONN_COREPROTOCOL_RESPONSE::~NETCONN_COREPROTOCOL_RESPONSE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    EXAMPLES
* 
* --------------------------------------------------------------------------------------------------------------------*/
NETCONN_COREPROTOCOL_RESPONSE::~NETCONN_COREPROTOCOL_RESPONSE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCONN_COREPROTOCOL_RESPONSE::CommandResponse(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT* event)
* @brief      CommandResponse
* @ingroup    EXAMPLES
* 
* @param[in]  event : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_COREPROTOCOL_RESPONSE::CommandResponse(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT* event)
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
                  case NETCONN_COREPROTOCOL_COMMAND_TYPE_GETVERSION     : status = CommandResponse_GetVersion(event); 
                                                                          break;

                  case NETCONN_COREPROTOCOL_COMMAND_TYPE_OTHERCOMMAND   : status = CommandResponse_OtherCommand(event); 
                                                                          break;    
                }
            }
             
                                                                              
        }                                                                            
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCONN_COREPROTOCOL_RESPONSE::CommandResponse_GetVersion(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT* event)
* @brief      CommandResponse_GetVersion
* @ingroup    EXAMPLES
* 
* @param[in]  event : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_COREPROTOCOL_RESPONSE::CommandResponse_GetVersion(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT* event)
{
  event->GetContentResponseString()->Format(__L("protocol version %d.%d"), NETCONN_COREPROTOCOL_VERSION, NETCONN_COREPROTOCOL_SUBVERSION);      

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCONN_COREPROTOCOL_RESPONSE::CommandResponse_OtherCommand(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT* event)
* @brief      CommandResponse_OtherCommand
* @ingroup    EXAMPLES
* 
* @param[in]  event : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_COREPROTOCOL_RESPONSE::CommandResponse_OtherCommand(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT* event)
{
  event->GetContentResponseString()->Format(__L("Other command"));      

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCONN_COREPROTOCOL_RESPONSE::UpdateClassResponse(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT* event)
* @brief      UpdateClassResponse
* @ingroup    EXAMPLES
* 
* @param[in]  event : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NETCONN_COREPROTOCOL_RESPONSE::UpdateClassResponse(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT* event)
{
  bool status = false;

  DIOCOREPROTOCOL_MESSAGE* message = event->GetMsg();
  if(!message)
    {
      return status;
    }

  NETCONN_COREPROTOCOL_CONNECTION* connection = (NETCONN_COREPROTOCOL_CONNECTION*)event->GetConnection();
  if(!connection)
    {
      return status;
    }

  DIOCOREPROTOCOL* protocol = connection->GetCoreProtocol();
  if(protocol)
    {
      if(!message->GetHeader()->GetOperationParam()->Compare(__L("testupdateclass"), true))
        {
          status = DIOCOREPROTOCOL_CONNECTIONSMANAGER::UpdateClass_Deserialize(message, connection->GetTestUpdateClass());
        }
    }

  return status; 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void NETCONN_COREPROTOCOL_RESPONSE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    EXAMPLES
* 
* --------------------------------------------------------------------------------------------------------------------*/
void NETCONN_COREPROTOCOL_RESPONSE::Clean()
{

}


#pragma endregion


