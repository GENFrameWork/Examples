/**-------------------------------------------------------------------------------------------------------------------
*
* @file       TestDataIO_STM32Platform.h
*
* @class      TESTDATAIO_STM32PLATFORM
* @brief      Test Data IO STM32 Platform functions
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

#ifndef _TESTDATAIO_STM32PLATFORM_H_
#define _TESTDATAIO_STM32PLATFORM_H_


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "diskio.h"

#include "XSTM32_HAL.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/


/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" 
{
#endif
  
  int         STM32_Platform_Ini                    (void);
  void        STM32_Platform_NonPreemptiveDoTasks   (void);
  
  void*       STM32_Platform_GetI2C1                (void);
  void*       STM32_Platform_GetI2C3                (void);

  void*       STM32_Platform_GetSPI1                (void);
  void*       STM32_Platform_GetSPI2                (void);

    
  DSTATUS     STM32_SD_Disk_Initialize              (BYTE drive);
  DSTATUS     STM32_SD_Disk_Status                  (BYTE drive);
  DRESULT     STM32_SD_Disk_Read                    (BYTE pdrive, BYTE* buffer, DWORD sector, UINT count);
  DRESULT     STM32_SD_Disk_Write                   (BYTE pdrive, const BYTE* buffer, DWORD sector, UINT count);
  DRESULT     STM32_SD_Disk_IOTCL                   (BYTE drive, BYTE ctrl, void* buffer);
  
  void        STM32_Platform_Trace                  (int iserror, const char* mask, ...);
  void        STM32_Heap_Usage                      ();

  int         STM32_Platform_End                    (void);
  
  void        HAL_GPIO_EXTI_Callback                (uint16_t GPIO_Pin);

#ifdef __cplusplus
}
#endif

#endif

