/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DataAIOStream.h
*
* @class      NOAPP
* @brief      Data I/O stream UART / USB MICROCONTROLLER example class
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

#ifndef _NOAPP_H_
#define _NOAPP_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XBuffer.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define APPLICATION_VERSION               0
#define APPLICATION_SUBVERSION            1
#define APPLICATION_SUBVERSIONERR         0
#define APPLICATION_NAMEAPP               __L("NoApp")

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/


class NOAPP
{
  public:
                        NOAPP                           ();
    virtual            ~NOAPP                           ();


  private:

    void                Clean                               ();
};


/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif



