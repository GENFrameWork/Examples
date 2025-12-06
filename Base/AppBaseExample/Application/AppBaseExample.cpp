/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       AppBaseExample.cpp
* 
* @class      APPBASEEXAMPLE
* @brief      Application Base Example 
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
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "AppBaseExample.h"

#include "VersionFrameWork.h"

#include "XFactory.h"
#include "XSleep.h"
#include "XTrace.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

APPLICATIONCREATEINSTANCE(APPBASEEXAMPLE, appbaseexample)

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPBASEEXAMPLE::APPBASEEXAMPLE()
* @brief      Constructor
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
APPBASEEXAMPLE::APPBASEEXAMPLE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPBASEEXAMPLE::~APPBASEEXAMPLE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
APPBASEEXAMPLE::~APPBASEEXAMPLE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPBASEEXAMPLE::AppProc_Ini()
* @brief      AppProc_Ini
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool APPBASEEXAMPLE::AppProc_Ini()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPBASEEXAMPLE::AppProc_FirstUpdate()
* @brief      AppProc_FirstUpdate
* @ingroup    
* 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool APPBASEEXAMPLE::AppProc_FirstUpdate()
{
  //-------------------------------------------------------------------------------------------------

  GEN_SET_VERSION(APPLICATION_NAMEAPP, APPLICATION_NAMEFILE, APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR, APPLICATION_OWNER, APPLICATION_YEAROFCREATION)
  
  //-------------------------------------------------------------------------------------------------

  XTRACE_SETAPPLICATIONNAME(APPLICATION_NAMEAPP);
  XTRACE_SETAPPLICATIONVERSION(APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR);

  XTRACE_ADDTARGET(XTRACE_TYPE_NET, GEN_XTRACE_NET_DEFAULT_01);

  XTRACE_CLEARSCREEN;
  XTRACE_CLEARMSGSSTATUS;

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Application ROOT path: %s"),  GEN_XPATHSMANAGER.GetPathSection(XPATHSMANAGERSECTIONTYPE_ROOT)->xpath->Get());

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPBASEEXAMPLE::AppProc_Update()
* @brief      AppProc_Update
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool APPBASEEXAMPLE::AppProc_Update()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPBASEEXAMPLE::AppProc_LastUpdate()
* @brief      AppProc_LastUpdate
* @ingroup    DATAIO
* 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool APPBASEEXAMPLE::AppProc_LastUpdate()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPBASEEXAMPLE::AppProc_End()
* @brief      AppProc_End
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool APPBASEEXAMPLE::AppProc_End()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPBASEEXAMPLE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    TEST
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void APPBASEEXAMPLE::Clean()
{

}


#pragma endregion

