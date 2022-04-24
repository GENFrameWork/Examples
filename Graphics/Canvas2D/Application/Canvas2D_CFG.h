/**-------------------------------------------------------------------------------------------------------------------
*
* @file       Canvas2D_CFG.h
*
* @class      CANVAS2D_CFG
* @brief      GEN Canvas 2D Config Example class
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

#ifndef _CANVAS2DCFG_H_
#define _CANVAS2DCFG_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "APPCFG.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define CANVAS2DCFG_SECTIONGENERAL    __L("general")

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class CANVAS2D_CFG : public APPCFG
{
  public:

    static bool                     GetIsInstanced                          ();
    static CANVAS2D_CFG&            GetInstance                             ();
    static bool                     DelInstance                             ();

    bool                            Default                                 ();

  private:

                                    CANVAS2D_CFG                            (XCHAR* namefile);
                                    CANVAS2D_CFG                            (CANVAS2D_CFG const&);       // Don't implement
    virtual                        ~CANVAS2D_CFG                            ();

    void                            operator =                              (CANVAS2D_CFG const&);       // Don't implement

    void                            Clean                                   ();

    static CANVAS2D_CFG*            instance;
};



/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif


