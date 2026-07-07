/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       MiniWebServer_APIRest.cpp
* 
* @class      MINIWEBSERVER_APIREST
* @brief      Example Mini Web Server API Rest class
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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"



/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "MiniWebServer_APIRest.h"

#include "DIOWebServer_XEvent.h"

#include "MiniWebServer.h"



/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"




/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/



/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         MINIWEBSERVER_APIREST::MINIWEBSERVER_APIREST(MINIWEBSERVER* miniwebserver)
* @brief      Constructor.
* @ingroup    EXAMPLES
*
* @param[in]  miniwebserver : Miniwebserver value used by the operation.
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
MINIWEBSERVER_APIREST::MINIWEBSERVER_APIREST(MINIWEBSERVER* miniwebserver)
{
  Clean();

  this->miniwebserver = miniwebserver;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         MINIWEBSERVER_APIREST::~MINIWEBSERVER_APIREST()
* @brief      Destructor.
* @note       VIRTUAL
* @ingroup    EXAMPLES
*
* @return     Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
MINIWEBSERVER_APIREST::~MINIWEBSERVER_APIREST()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MINIWEBSERVER_APIREST::ResolveEndPoint(DIOWEBSERVER_XEVENT* event)
* @brief      Resolves an API REST endpoint.
* @ingroup    EXAMPLES
*
* @param[in]  event : Event information to process.
*
* @return     bool : true if the operation is successful; otherwise false.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool MINIWEBSERVER_APIREST::ResolveEndPoint(DIOWEBSERVER_XEVENT* event)
{
  if(!miniwebserver) return false;

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void MINIWEBSERVER_APIREST::Clean()
* @brief      Cleans the object internal state.
* @note       INTERNAL
* @ingroup    EXAMPLES
*
* @return     void : Does not return a value.
*
*---------------------------------------------------------------------------------------------------------------------*/
void MINIWEBSERVER_APIREST::Clean()
{
  miniwebserver = NULL;
}




