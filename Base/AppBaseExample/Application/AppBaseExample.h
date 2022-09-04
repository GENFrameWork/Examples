/**-------------------------------------------------------------------------------------------------------------------
*
* @file       AppBaseExample.h
*
* @class      AppBaseExample
* @brief      Application Base Example
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

#ifndef _AppBaseExample_H_
#define _AppBaseExample_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "APPBase.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define APPLICATION_VERSION                       0
#define APPLICATION_SUBVERSION                    1
#define APPLICATION_SUBVERSIONERR                 0

#define APPLICATION_NAMEAPP                       __L("App Base Example")
#define APPLICATION_NAMEFILE                      __L("AppBaseExample")

#define APPLICATION_OWNER                         __L("GEN Group")

#define APPLICATION_YEAROFCREATION                2022


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class APPBASEEXAMPLE: public APPBASE
{
  public:
                        APPBASEEXAMPLE                      ();
    virtual            ~APPBASEEXAMPLE                      ();

    bool                AppProc_Ini                         ();
    bool                AppProc_FirstUpdate                 ();
    bool                AppProc_Update                      ();
    bool                AppProc_LastUpdate                  ();  
    bool                AppProc_End                         ();
   
  private:

    void                Clean                               ();
};


/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/


#endif



