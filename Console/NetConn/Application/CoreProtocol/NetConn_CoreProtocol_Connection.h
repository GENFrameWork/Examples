/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       NetConn_CoreProtocol_Connection.h
* 
* @class      NETCONN_COREPROTOCOL_CONNECTION
* @brief      Net Connection Core Protocol Connection class (DIOCoreProtol example)
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

#ifndef _NETCONN_COREPROTOCOL_CONNECTION_H_
#define _NETCONN_COREPROTOCOL_CONNECTION_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIOCoreProtocol_Connection.h"

#include "NetConn_AgentState.h"
#include "NetConn_TestUpdateClass.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

class NETCONN_COREPROTOCOL_CONNECTION : public DIOCOREPROTOCOL_CONNECTION 
{
  public:
                                  NETCONN_COREPROTOCOL_CONNECTION     ();
    virtual                      ~NETCONN_COREPROTOCOL_CONNECTION     ();

    NETCONN_AGENTSTATE*           GetAgentState                       ();
    void                          SetAgentState                       (NETCONN_AGENTSTATE* agentstate);

    NETCONN_TESTUPDATECLASS*      GetTestUpdateClass                  ();
    void                          SetTestUpdateClass                  (NETCONN_TESTUPDATECLASS* testupdateclass);

  private:

    void                          Clean                               ();

    NETCONN_AGENTSTATE*           agentstate;
    NETCONN_TESTUPDATECLASS*      testupdateclass;
};

#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

