/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UI_Options_CFG.h
*
* @class      UI_OPTIONS_CFG
* @brief      GEN UI Options Config Example class
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

#ifndef _UI_OPTIONSCFG_H_
#define _UI_OPTIONSCFG_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "APPCFG.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define UI_OPTIONSCFG_SECTIONGENERAL    __L("general")

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class UI_OPTIONS_CFG : public APPCFG
{
  public:

    static bool                     GetIsInstanced                          ();
    static UI_OPTIONS_CFG&          GetInstance                             ();
    static bool                     DelInstance                             ();

    bool                            Default                                 ();

  private:

                                    UI_OPTIONS_CFG                            (XCHAR* namefile);
                                    UI_OPTIONS_CFG                            (UI_OPTIONS_CFG const&);       // Don't implement
    virtual                        ~UI_OPTIONS_CFG                            ();

    void                            operator =                              (UI_OPTIONS_CFG const&);       // Don't implement

    void                            Clean                                   ();

    static UI_OPTIONS_CFG*          instance;
};



/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif


