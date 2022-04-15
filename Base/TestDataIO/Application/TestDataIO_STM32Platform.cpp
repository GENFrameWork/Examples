/**-------------------------------------------------------------------------------------------------------------------
*
* @file       TestDataIO_STM32Platform.cpp
*
* @class      TESTDATAIO_STM32PLATFORM
* @brief      Test Data IO STM32 Platform functions
* @ingroup    Examples
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
#include <stdlib.h>
#include <stdarg.h>

#include "XSTM32Trace.h"
#include "XSTM32_FATSD_SPI.h"
#include "DIOSTM32GPIO.h"
#include "DIOSTM32StreamI2C.h"
#include "DIOSTM32StreamSPI.h"

#include "MainProcSTM32.h"

#include "XTrace.h"
#include "XThreadListNonPreemptive.h"

#include "main.h"
#include "TestDataIO.h"

#include "TestDataIO_STM32Platform.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

XSTM32_FATSD_SPI  FATSD_SPI;

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int STM32_Platform_Main(void)
* @brief      TM32_Platform_Main
* @ingroup    DATAIO
*
* @param[in]  void :
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int STM32_Platform_Ini(void)
{
  _main();
  
  #ifdef XTRACE_ACTIVE
  STM32trace.SetHuart(&huart1);
  #endif
    
  //-------------------------------------------------------------------------------------------------------------------
  
  GEN_DIOGPIO.GPIOEntry_CreateByPin(TESTDATAIO_GPIOENTRYID_LED_RED                , GPIO_PIN_6  , DIOGPIO_PINSGROUP_C);
  GEN_DIOGPIO.GPIOEntry_CreateByPin(TESTDATAIO_GPIOENTRYID_LED_BLUE               , GPIO_PIN_7  , DIOGPIO_PINSGROUP_C); 
  GEN_DIOGPIO.GPIOEntry_CreateByPin(TESTDATAIO_GPIOENTRYID_LED_ORANGE             , GPIO_PIN_8  , DIOGPIO_PINSGROUP_C); 
  GEN_DIOGPIO.GPIOEntry_CreateByPin(TESTDATAIO_GPIOENTRYID_LED_GREEN              , GPIO_PIN_9  , DIOGPIO_PINSGROUP_C);   
  GEN_DIOGPIO.GPIOEntry_CreateByPin(TESTDATAIO_GPIOENTRYID_BTN_BLUE               , GPIO_PIN_10 , DIOGPIO_PINSGROUP_C); 
 
  //-------------------------------------------------------------------------------------------------------------------
  
  GEN_DIOGPIO.GPIOEntry_CreateByPin(TESTDATAIO_GPIOENTRYID_FATSD_CS               , GPIO_PIN_4  , DIOGPIO_PINSGROUP_A); 
  GEN_DIOGPIO.GPIOEntry_CreateByPin(TESTDATAIO_GPIOENTRYID_FATSD_SWITCH           , GPIO_PIN_8  , DIOGPIO_PINSGROUP_A); 
  
  FATSD_SPI.Ini(&hspi1, TESTDATAIO_GPIOENTRYID_FATSD_CS, TESTDATAIO_GPIOENTRYID_FATSD_SWITCH);
  
  //-------------------------------------------------------------------------------------------------------------------
  
  GEN_DIOGPIO.GPIOEntry_CreateByPin(TESTDATAIO_GPIOENTRYID_LED_NEOPIXEL           , GPIO_PIN_0  , DIOGPIO_PINSGROUP_A); 
  
  //-------------------------------------------------------------------------------------------------------------------

  DIOGPIO_ENTRY* int_entry = GEN_DIOGPIO.GPIOEntry_CreateByPin(TESTDATAIO_GPIOENTRYID_TEST_INTERRUPT, GPIO_PIN_2, DIOGPIO_PINSGROUP_A);  
  if(int_entry) 
    {
      int_entry->SetIntIRQ(EXTI2_IRQn);
      int_entry->SetIntPriority(2);
    }

  //-------------------------------------------------------------------------------------------------------------------
  
  GEN_DIOGPIO.GPIOEntry_CreateByPin(TESTDATAIO_GPIOENTRYID_I2C_CCS811_WAKEUP      , GPIO_PIN_9  , DIOGPIO_PINSGROUP_A);   
  
  //-------------------------------------------------------------------------------------------------------------------
  
  GEN_DIOGPIO.GPIOEntry_CreateByPin(TESTDATAIO_GPIOENTRYID_SPI_DISPLAY_CS         , GPIO_PIN_4  , DIOGPIO_PINSGROUP_A);
  GEN_DIOGPIO.GPIOEntry_CreateByPin(TESTDATAIO_GPIOENTRYID_SPI_DISPLAY_RESET      , GPIO_PIN_0  , DIOGPIO_PINSGROUP_A);
  GEN_DIOGPIO.GPIOEntry_CreateByPin(TESTDATAIO_GPIOENTRYID_SPI_DISPLAY_DC         , GPIO_PIN_2  , DIOGPIO_PINSGROUP_A);
  GEN_DIOGPIO.GPIOEntry_CreateByPin(TESTDATAIO_GPIOENTRYID_SPI_DISPLAY_BACKLIGHT  , GPIO_PIN_3  , DIOGPIO_PINSGROUP_A);
  
  //-------------------------------------------------------------------------------------------------------------------
   
  
  return 1;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void STM32_Platform_NonPreemptiveDoTasks(void)
* @brief      TM32_Platform_NonPreemptiveDoTasks
* @ingroup    DATAIO
* 
* 
* @param[in]  void : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void STM32_Platform_NonPreemptiveDoTasks(void)
{
  __disable_irq();

  XTHREADLISTNONPREEMPTIVE::GetInstance().ExecuteFunctions();

  __enable_irq();   
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void* STM32_Platform_GetI2C1(void)
* @brief      STM32_Platform_GetI2C1
* @ingroup    
* 
* 
* @param[in]  void : 
* 
* @return     void* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void* STM32_Platform_GetI2C1(void)
{
  if(!DIOSTM32STREAMI2C::ports[0]) return NULL; 
  return DIOSTM32STREAMI2C::ports[0]->GetHandleI2C();
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void* STM32_Platform_GetI2C2(void)
* @brief      STM32_Platform_GetI2C2
* @ingroup    
* 
* 
* @param[in]  void : 
* 
* @return     void* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void* STM32_Platform_GetI2C3(void)
{
  if(!DIOSTM32STREAMI2C::ports[2]) return NULL; 
  return DIOSTM32STREAMI2C::ports[2]->GetHandleI2C();
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void* STM32_Platform_GetSPI1(void)
* @brief      TM32_Platform_GetSPI1
* @ingroup    DATAIO
* 
* 
* @param[in]  void : 
* 
* @return     void* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void* STM32_Platform_GetSPI1(void)
{
  if(!DIOSTM32STREAMSPI::ports[0]) return NULL; 
  return DIOSTM32STREAMSPI::ports[0]->GetHandleSPI();
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void* STM32_Platform_GetSPI2(void)
* @brief      TM32_Platform_GetSPI2
* @ingroup    DATAIO
* 
* 
* @param[in]  void : 
* 
* @return     void* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void* STM32_Platform_GetSPI2(void)
{
  if(!DIOSTM32STREAMSPI::ports[1]) return NULL; 
  return DIOSTM32STREAMSPI::ports[1]->GetHandleSPI();
}




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DSTATUS STM32_SD_Disk_Initialize(BYTE drive)
* @brief      STM32_SD_Disk_Initialize
* @ingroup    DATAIO
* 
* 
* @param[in]  drive : 
* 
* @return     DSTATUS : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DSTATUS STM32_SD_Disk_Initialize(BYTE drive)
{
  return FATSD_SPI.Disk_Initialize((XBYTE)drive);
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DSTATUS SD_Disk_Status(BYTE drive)
* @brief      STM32_SD_Disk_Status
* @ingroup    DATAIO
* 
* 
* @param[in]  drive : 
* 
* @return     DSTATUS : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DSTATUS STM32_SD_Disk_Status(BYTE drive)
{
  return FATSD_SPI.Disk_Status((XBYTE)drive);
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DRESULT STM32_SD_Disk_Read(BYTE pdrive, BYTE* buffer, DWORD sector, UINT count)
* @brief      STM32_SD_Disk_Read
* @ingroup    DATAIO
* 
* 
* @param[in]  pdrive : 
* @param[in]  buffer : 
* @param[in]  sector : 
* @param[in]  count : 
* 
* @return     DRESULT : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DRESULT STM32_SD_Disk_Read(BYTE pdrive, BYTE* buffer, DWORD sector, UINT count)
{
  return FATSD_SPI.Disk_Read((XBYTE)pdrive, (XBYTE*)buffer, (XDWORD)sector, (XDWORD)count);
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DRESULT SD_Disk_Write(BYTE pdrive, const BYTE* buffer, DWORD sector, UINT count)
* @brief      STM32_SD_Disk_Write
* @ingroup    DATAIO
* 
* 
* @param[in]  pdrive : 
* @param[in]  BYTE* buffer : 
* @param[in]  sector : 
* @param[in]  count : 
* 
* @return     DRESULT : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DRESULT STM32_SD_Disk_Write(BYTE pdrive, const BYTE* buffer, DWORD sector, UINT count)
{
  return FATSD_SPI.Disk_Write((XBYTE)pdrive, (const XBYTE*)buffer, (XDWORD)sector, (XDWORD) count);
}




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DRESULT STM32_SD_Disk_IOTCL(BYTE drive, BYTE ctrl, void* buffer)
* @brief      STM32_SD_Disk_IOTCL
* @ingroup    DATAIO
* 
* 
* @param[in]  drive : 
* @param[in]  ctrl : 
* @param[in]  buffer : 
* 
* @return     DRESULT : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DRESULT STM32_SD_Disk_IOTCL(BYTE drive, BYTE ctrl, void* buffer)
{
  return FATSD_SPI.Disk_IOTCL((XBYTE)drive, (XBYTE)ctrl, buffer);
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void STM32_Platform_Trace(const char* mask, ...)
* @brief      TM32_Platform_Trace
* @ingroup    
* 
* 
* @param[in]  char* mask : 
* @param[in]  ... : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void STM32_Platform_Trace(int iserror, const char* mask, ...)
{
  XSTRING   concat;
  XSTRING   _mask;
  va_list   arg;

  _mask = mask;
  
  va_start(arg, mask);

  concat.FormatArg(_mask.Get(), &arg);

  va_end(arg);
   
  XTRACE_PRINTCOLOR((iserror == TRUE?XTRACE_COLOR_RED:XTRACE_COLOR_BLUE), __L("%s"), concat.Get());                   
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void STM32_Heap_Usage()
* @brief      TM32_Heap_Usage
* @ingroup    
* 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void STM32_Heap_Usage()
{    
  struct mallinfo m;
  m = __iar_dlmallinfo();
  
  XDWORD total = m.uordblks + m.fordblks;
  XDWORD free  = m.fordblks;
    
  STM32_Platform_Trace(FALSE,"RAM Memory Total %u, (%uk) / Free: %u, (%uk)" , total, (total/1024), free, (free/1024));
    
  // __iar_dlmalloc_stats();
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int STM32_Platform_End(void)
* @brief      TM32_Platform_End
* @ingroup    DATAIO
* 
* 
* @param[in]  void : 
* 
* @return     int : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
int STM32_Platform_End(void)
{
  return 1;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void HAL_GPIO_EXTI_Callback(uint16_t GPIO_pin)
* @brief      AL_GPIO_EXTI_Callback
* @ingroup    DATAIO
* 
* 
* @param[in]  GPIO_pin : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_pin)
{
  DIOGPIO_ENTRY* int_GPIOentry = GEN_DIOGPIO.GPIOEntry_GetInterruptByPin(GPIO_pin);
  if(int_GPIOentry) 
    {
      DIOGPIO_INT_FUNCPTR funcptr = int_GPIOentry->GetIntFunctionPointer();
      if(funcptr) funcptr(int_GPIOentry->GetIntParamPointer());
    }  
}





