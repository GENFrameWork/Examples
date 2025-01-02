/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       NetConn_AgentState.h
* 
* @class      NETCONN_AGENTSTATE
* @brief      Net Conn Agent State class
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

#ifndef _NETCONN_AGENTSTATE_H_
#define _NETCONN_AGENTSTATE_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XSerializable.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

#define NETCONN_AGENTSTATE_TOTALMEMORY_STR    __L("total_memory") 
#define NETCONN_AGENTSTATE_FREEMEMORY_STR     __L("free_memory")

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

class NETCONN_AGENTSTATE : public XSERIALIZABLE
{
  public:
                    NETCONN_AGENTSTATE                ();
    virtual        ~NETCONN_AGENTSTATE                ();

    XDWORD          GetTotalMemory                    ();
    void            SetTotalMemory                    (XDWORD total_memory);

    XDWORD          GetFreeMmemory                    ();
    void            SetFreeMemory                     (XDWORD free_memory);

    bool            Update                            ();  
  
    bool            Serialize                         ();    
    bool            Deserialize                       ();  

  private:
  
    void            Clean                             ();

    XDWORD          total_memory;
    XDWORD          free_memory;
};

#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif






