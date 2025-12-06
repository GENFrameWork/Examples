/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       MemCtrlExample.cpp
* 
* @class      MEMCTRLEXAMPLE
* @brief      Memory Control Example
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

#include "MemCtrlExample.h"

#include <stdio.h>
#include <malloc.h>

#include "VersionFrameWork.h"

#include "XFactory.h"
#include "XSleep.h"
#include "XTrace.h"

#include "MainProc.h"

//#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         MEMCTRLEXAMPLE::MEMCTRLEXAMPLE()
* @brief      Constructor
* @ingroup    APPLICATION
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
MEMCTRLEXAMPLE::MEMCTRLEXAMPLE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         MEMCTRLEXAMPLE::~MEMCTRLEXAMPLE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    APPLICATION
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
MEMCTRLEXAMPLE::~MEMCTRLEXAMPLE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void MEMCTRLEXAMPLE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    TEST
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void MEMCTRLEXAMPLE::Clean()
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
  GEN_SET_VERSION(APPLICATION_NAMEAPP, APPLICATION_NAMEFILE, APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR, APPLICATION_OWNER, APPLICATION_YEAROFCREATION)


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

  // -----------------------------------------------------------------------------------
  //  new

  char*  string1  = new char[256];   
  if(string1)
    {  
      memset(string1, 0, 256);
      strcpy(string1, "Hello, World [new]");
    }

  // -----------------------------------------------------------------------------------



  // -----------------------------------------------------------------------------------
  // malloc

  char*  string2  = (char*)MALLOC(256);   
  if(string2)
    {  
      memset(string2, 0, 256);
      strcpy(string2, "Hello, World [malloc]");
    }

  // -----------------------------------------------------------------------------------



  // -----------------------------------------------------------------------------------
  // calloc

  char*  string3  = (char*)CALLOC(256, sizeof(char));   
  if(string3)
    {
      memset(string3, 0, 256 * sizeof(char));
      strcpy(string3, "Hello, World  [calloc]");
    }

  // -----------------------------------------------------------------------------------



  // -----------------------------------------------------------------------------------
  // realloc

  char*  string4  = (char*)MALLOC(128);   
  if(string4)
    {  
      string4  = (char*)REALLOC(string4, 256);    
      if(string4)
        {
          memset(string4, 0, 256);
          strcpy(string4, "Hello, World [realloc]");
        }
    }

  // -----------------------------------------------------------------------------------



  // -----------------------------------------------------------------------------------

  /*
  delete string1;
  FREE(string2);
  FREE(string3);
  FREE(string4);
  */

  // -----------------------------------------------------------------------------------

  GEN_XSLEEP.Seconds(1);

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


#pragma endregion