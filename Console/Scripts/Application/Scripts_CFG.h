/**-------------------------------------------------------------------------------------------------------------------
*
* @file       Scripts_CFG.h
*
* @class      SCRIPTS_CFG
* @brief      Scripts Configuration
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

#ifndef _SCRIPTSCFG_H_
#define _SCRIPTSCFG_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "APPCFG.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define SCRIPTSCFG_SECTIONGENERAL     __L("general")

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class SCRIPTS_CFG : public APPCFG
{
  public:

    static bool                     GetIsInstanced                          ();
    static SCRIPTS_CFG&             GetInstance                             (bool ini = true);
    static bool                     DelInstance                             ();

    bool                            DoVariableMapping                       (); 
    bool                            DoDefault                               ();

  private:
                                    SCRIPTS_CFG                             (XCHAR* namefile);
                                    SCRIPTS_CFG                             (SCRIPTS_CFG const&);        // Don't implement
    virtual                        ~SCRIPTS_CFG                             ();

    void                            operator =                              (SCRIPTS_CFG const&);        // Don't implement

    void                            Clean                                   ();

     static SCRIPTS_CFG*            instance;
};



/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif


