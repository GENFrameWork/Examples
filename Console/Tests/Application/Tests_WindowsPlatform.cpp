/**-------------------------------------------------------------------------------------------------------------------
*
* @file       Tests_WindowsPlatform.cpp
*
* @class      TESTS_WINDOWSPLATFORM
* @brief      Tests WINDOWS Platform functions
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @copyright  Copyright(c) 2008 - 2016 GEN Group.
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


#include "DIOGPIO.h"

#include "Tests.h"

#include "Tests_WindowsPlatform.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int Windows_Platform_Main(void)
* @brief      Windows_Platform_Main
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param[in]  void :
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int Windows_Platform_Ini(void)
{
  GEN_DIOGPIO.GPIOEntry_CreateByPin(TESTS_GPIOENTRYID_TESTGPIO               , 1);
  GEN_DIOGPIO.GPIOEntry_CreateByPin(TESTS_GPIOENTRYID_LED_NEOPIXEL           , 6); 

  return 1;
}


