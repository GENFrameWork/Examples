/**-------------------------------------------------------------------------------------------------------------------
*
* @file       TestDataIO_WindowsPlatform.cpp
*
* @class      TESTDATAIO_WINDOWSPLATFORM
* @brief      Test Data IO WINDOWS Platform functions
* @ingroup    DATAIO
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


#include "DIOGPIO.h"

#include "TestDataIO.h"

#include "TestDataIO_WindowsPlatform.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int Windows_Platform_Main(void)
* @brief      Windows_Platform_Main
* @ingroup    DATAIO
*
* @param[in]  void :
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int Windows_Platform_Ini(void)
{
  GEN_DIOGPIO.GPIOEntry_CreateByPin(TESTDATAIO_GPIOENTRYID_LED_RED                , 1);
  GEN_DIOGPIO.GPIOEntry_CreateByPin(TESTDATAIO_GPIOENTRYID_LED_BLUE               , 2);
  GEN_DIOGPIO.GPIOEntry_CreateByPin(TESTDATAIO_GPIOENTRYID_LED_ORANGE             , 3);
  GEN_DIOGPIO.GPIOEntry_CreateByPin(TESTDATAIO_GPIOENTRYID_LED_GREEN              , 4);
  GEN_DIOGPIO.GPIOEntry_CreateByPin(TESTDATAIO_GPIOENTRYID_BTN_BLUE               , 5);

  GEN_DIOGPIO.GPIOEntry_CreateByPin(TESTDATAIO_GPIOENTRYID_FATSD_CS               , 7); 
  GEN_DIOGPIO.GPIOEntry_CreateByPin(TESTDATAIO_GPIOENTRYID_FATSD_SWITCH           , 8); 

  GEN_DIOGPIO.GPIOEntry_CreateByPin(TESTDATAIO_GPIOENTRYID_TEST_INTERRUPT         , 6); 
  
  GEN_DIOGPIO.GPIOEntry_CreateByPin(TESTDATAIO_GPIOENTRYID_LED_NEOPIXEL           , 6); 

  GEN_DIOGPIO.GPIOEntry_CreateByPin(TESTDATAIO_GPIOENTRYID_I2C_CCS811_WAKEUP      , 6);
  
  GEN_DIOGPIO.GPIOEntry_CreateByPin(TESTDATAIO_GPIOENTRYID_SPI_DISPLAY_RESET      , 5);
  GEN_DIOGPIO.GPIOEntry_CreateByPin(TESTDATAIO_GPIOENTRYID_SPI_DISPLAY_DC         , 6);
  GEN_DIOGPIO.GPIOEntry_CreateByPin(TESTDATAIO_GPIOENTRYID_SPI_DISPLAY_BACKLIGHT  , 7);

  return 1;
}


