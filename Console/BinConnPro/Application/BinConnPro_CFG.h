/**-------------------------------------------------------------------------------------------------------------------
*
* @file        BinConnPro_CFG.h
*
* @class       BINCONNPRO_CFG
* @brief       BinConnPro Configuration
* @ingroup     SCRIPT
*
* @author      Abraham J. Velez
* @date       01/03/2016 12:00
*
* @copyright   Copyright(c) 2008 - 2016 GEN Group.
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

#ifndef _BINCONNPROCFG_H_
#define _BINCONNPROCFG_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "APPCFG.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define BINCONNPRO_CFG_SECTION_PROTOCOL                            __L("protocol")
#define BINCONNPRO_CFG_PROTOCOL_ISACTIVE                           __L("isactive")
#define BINCONNPRO_CFG_PROTOCOL_ISLOCALENUMACTIVE                  __L("islocalenumactive")
#define BINCONNPRO_CFG_PROTOCOL_PORT                               __L("port")
#define BINCONNPRO_CFG_PROTOCOL_TARGET                             __L("target")

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class BINCONNPRO_CFG : public APPCFG
{
  public:


    static bool                     GetIsInstanced                          ();
    static BINCONNPRO_CFG&          GetInstance                             ();
    static bool                     DelInstance                             ();

    bool                            Protocol_IsActive                       ();
    bool                            Protocol_IsLocalEnumActive              ();
    int                             Protocol_GetPort                        ();
    XSTRING*                        Protocol_GetTarget                      ();

    bool                            Default                                 ();

  private:
                                    BINCONNPRO_CFG                          (XCHAR* namefile);
                                    BINCONNPRO_CFG                          (BINCONNPRO_CFG const&);        // Don't implement
    virtual                        ~BINCONNPRO_CFG                          ();

    void                            operator =                              (BINCONNPRO_CFG const&);        // Don't implement


    void                            Clean                                   ();

    static BINCONNPRO_CFG*          instance;

    bool                            protocol_isactive;
    bool                            protocol_islocalenumactive;
    int                             protocol_port;
    XSTRING                         protocol_target;

};



/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif


