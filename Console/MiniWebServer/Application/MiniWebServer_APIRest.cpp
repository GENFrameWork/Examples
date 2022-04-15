/**-------------------------------------------------------------------------------------------------------------------
*
* @file       MiniWebServer_APIRest.cpp
*
* @class      MINIWEBSERVER_APIREST
* @brief      Example Mini Web Server API Rest class
* @ingroup
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "MiniWebServer_APIRest.h"
#include "MiniWebServer.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         MINIWEBSERVER_APIREST::MINIWEBSERVER_APIREST()
* @brief      Constructor
* @ingroup    APPLICATION
*
* @return     Does not return anything.
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
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    APPLICATION
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
MINIWEBSERVER_APIREST::~MINIWEBSERVER_APIREST()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MINIWEBSERVER_APIREST::ResolveEndPoint(DIOWEBSERVER_REQUEST* request, DIOWEBSERVER_QUERYSTRINGS* querystring, DIOWEBHEADER_RESULT* result, XSTRING* output)
* @brief      ResolveEndPoint
* @ingroup    APPLICATION
*
* @param[in]  request :
* @param[in]  querystring :
* @param[in]  result :
* @param[in]  output :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool MINIWEBSERVER_APIREST::ResolveEndPoint(DIOWEBSERVER_REQUEST* request, DIOWEBSERVER_QUERYSTRINGS* querystring, DIOWEBHEADER_RESULT* result, XSTRING* output)
{
  if(!miniwebserver) return false;

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void MINIWEBSERVER_APIREST::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    APPLICATION
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void MINIWEBSERVER_APIREST::Clean()
{
  miniwebserver = NULL;
}
