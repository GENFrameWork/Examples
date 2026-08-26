/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       MiniWebServer_CFG.h
* 
* @class      MINIWEBSERVER_CFG
* @brief      Example Mini Web Server Configuration class
* @ingroup    EXAMPLES
* 
* @copyright  EndoraSoft. All rights reserved.
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

#pragma once

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "APPFlowCFG.h"



/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define MINIWEBSERVER_CFG_SECTION_PROTOCOL                            __L("protocol")
#define MINIWEBSERVER_CFG_PROTOCOL_ISACTIVE                           __L("isactive")
#define MINIWEBSERVER_CFG_PROTOCOL_ISLOCALENUMACTIVE                  __L("islocalenumactive")
#define MINIWEBSERVER_CFG_PROTOCOL_PORT                               __L("port")
#define MINIWEBSERVER_CFG_PROTOCOL_TARGET                             __L("target")

// NOTE: the HTTPS (TLS 1.3) listener configuration (isactive/port/pathprivatekey/pathcertificate) that used to
// live here in its own "[webserverhttps]" section has been merged into APPFLOWCFG's "[webserver]" section
// (see APPFLOW_CFG_WEBSERVER_PATH_PRIVATEKEY / APPFLOW_CFG_WEBSERVER_PATH_CERTIFICATE in APPFlowCFG.h, guarded
// by DIO_STREAMTLS_ACTIVE), since it is shared functionality and no longer specific to this example. There is
// no "istls" value of its own: TLS is used automatically whenever both paths are configured (the normal case);
// leave either one empty in the .ini to run plain HTTP instead. Use APPFLOW_CFG.WebServer_IsTLS() (derived from
// those two paths) / WebServer_PathPrivateKey() / WebServer_PathCertificate().



/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class MINIWEBSERVER_CFG : public APPFLOWCFG
{
  public:


    static bool                     GetIsInstanced                          ();
    static MINIWEBSERVER_CFG&       GetInstance                             (bool ini = true);
    static bool                     DelInstance                             ();

    bool                            DoVariableMapping                       ();
    bool                            DoDefault                               ();

  private:
                                    MINIWEBSERVER_CFG                       (XCHAR* namefile);
                                    MINIWEBSERVER_CFG                       (MINIWEBSERVER_CFG const&);        // Don't implement
    virtual                        ~MINIWEBSERVER_CFG                       ();

    void                            operator =                              (MINIWEBSERVER_CFG const&);        // Don't implement


    void                            Clean                                   ();

    static MINIWEBSERVER_CFG*       instance;

};



/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/




