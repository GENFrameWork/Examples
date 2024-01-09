/**-------------------------------------------------------------------------------------------------------------------
*
* @file       BinConnPro_ApplicationData.h
*
* @class      BINCONNPRO_APPLICATIONDATA
* @brief      Example Binary Connexion Protocol Application Data class
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

#ifndef _BINCONNPRO_APPLICATIONDATA_H_
#define _BINCONNPRO_APPLICATIONDATA_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XBase.h"
#include "XFactory.h"
#include "LocationAddress.h"

#include "DIOProtocol_ApplicationData.h"

#include "BinConnPro_Protocol_Device.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class BINCONNPRO_APPLICATIONDATA : public DIOPROTOCOL_APPLICATIONDATA
{
  public:
                                  BINCONNPRO_APPLICATIONDATA      ();
    virtual                      ~BINCONNPRO_APPLICATIONDATA      ();

    BINCONNPRO_PROTOCOL_DEVICE    device;
    XSTRING                       centername;
    LOCATIONADDRESS               location;

  private:

    void                          Clean                           ();
};


/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif


