/**-------------------------------------------------------------------------------------------------------------------
*
* @file       NOTAPPEXAMPLE.cpp
*
* @class      NOTAPPEXAMPLE
* @brief      Not Application Example (aplication simple without "application" class of GEN) 
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

#include "XFactory.h"
#include "XSleep.h"
#include "XTrace.h"

#include "MainProc.h"

#include "NotAppExample.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         NOTAPPEXAMPLE::NOTAPPEXAMPLE()
* @brief      Constructor
* @ingroup    APPLICATION
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
NOTAPPEXAMPLE::NOTAPPEXAMPLE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         NOTAPPEXAMPLE::~NOTAPPEXAMPLE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    APPLICATION
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
NOTAPPEXAMPLE::~NOTAPPEXAMPLE()

{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void NOTAPPEXAMPLE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    TEST
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void NOTAPPEXAMPLE::Clean()
{
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool Proc_Main_Ini(MAINPROC* main)
* @brief      roc_Main_Ini
* @ingroup    APPLICATION
*
* @param[in]  main :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool Proc_Main_Ini(MAINPROC* main)
{
  XTRACE_SETAPPLICATIONNAME(APPLICATION_NAMEAPP);
  XTRACE_SETAPPLICATIONVERSION(APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR);

  XTRACE_ADDTARGET(XTRACE_TYPE_NET, XTRACE_DEFAULT_NETAIM1);

  XTRACE_SCREENCLEAR;
  XTRACE_STATUSCLEAR;

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Application ROOT path: %s"),  GEN_XPATHSMANAGER.GetPathSection(XPATHSMANAGERSECTIONTYPE_ROOT)->xpath->Get());

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool Proc_Main_Update(MAINPROC* main)
* @brief      roc_Main_Update
* @ingroup    APPLICATION
*
* @param[in]  main :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool Proc_Main_Update(MAINPROC* main)
{
  GEN_XSLEEP.Seconds(3);

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool Proc_Main_End(MAINPROC* main)
* @brief      roc_Main_End
* @ingroup    APPLICATION
*
* @param[in]  main :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool Proc_Main_End(MAINPROC* main)
{
  return true;
}
