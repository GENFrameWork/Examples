/**-------------------------------------------------------------------------------------------------------------------
*
* @file       NetConn_Connections.h
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

#ifndef _NETCONN_CONNECTIONS_H_
#define _NETCONN_CONNECTIONS_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "DIOCoreProtocol_CFG.h"
#include "DIOCoreProtocol_ConnectionsManager.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/


class DIOCOREPROTOCOL_CFG;
class DIOCOREPROTOCOL_CONNECTIONSMANAGER;


class NETCONN_CONNECTIONS :  public DIOCOREPROTOCOL_CONNECTIONSMANAGER
{
  public:
                                          NETCONN_CONNECTIONS                   ();
                                         ~NETCONN_CONNECTIONS                   ();

    bool                                  Ini                                   (bool isserver);
    bool                                  End                                   ();

    DIOCOREPROTOCOL_CFG*                  GetProtocolCFG                        ();
   
  private:

    void                                  Clean                                 ();

    DIOCOREPROTOCOL_CFG                   protocolCFG;
 };

/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif
