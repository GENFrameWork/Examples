/**-------------------------------------------------------------------------------------------------------------------/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       NetConn_Register.h
* 
* @class      NETCONN_REGISTERDATA
* @brief      Net Connection Register Data class
* @ingroup    DATAIO
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

#ifndef _NETCONN_REGISTERDATA_H_
#define _NETCONN_REGISTERDATA_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIOCoreProtocol_RegisterData.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

#define NETCONN_REGISTERDATA_HEADER_VAR_GROUP       __L("group")
#define NETCONN_REGISTERDATA_HEADER_VAR_SUBGROUP    __L("subgroup")

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

class NETCONN_REGISTERDATA : public DIOCOREPROTOCOL_REGISTERDATA
{
  public:
                            NETCONN_REGISTERDATA            ();
    virtual                ~NETCONN_REGISTERDATA            ();

    bool                    InitializeData                  (bool isserver);

    XSTRING*                GetGroup                        ();
    XSTRING*                GetSubGroup                     ();    
    
    bool                    Serialize                       ();    
    bool                    Deserialize                     ();  

  private:

    void                    Clean                           ();
  
    XSTRING                 group;
    XSTRING                 subgroup;  
};

#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

