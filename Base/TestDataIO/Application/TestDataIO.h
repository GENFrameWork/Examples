/**-------------------------------------------------------------------------------------------------------------------
*
* @file       TestDataIO.h
*
* @class      TESTDATAIO
* @brief      Test Data I/O  UART / USB / I2C / GPIO (include microcontroller) class
* @ingroup
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

#ifndef _TESTDATAIO_H_
#define _TESTDATAIO_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XBuffer.h"
#include "APPBase.h"

#include "DIOGPIO.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define TESTDATAIO_VERSION            0
#define TESTDATAIO_SUBVERSION         1
#define TESTDATAIO_SUBVERSIONERR      0
#define TESTDATAIO_NAMEAPP            __L("TestDataIO")


enum TESTDATAIO_GPIOENTRYID
{
  TESTDATAIO_GPIOENTRYID_LED_RED                  = DIOGPIO_ID_NOTDEFINED + 1 ,
  TESTDATAIO_GPIOENTRYID_LED_BLUE                                             ,
  TESTDATAIO_GPIOENTRYID_LED_ORANGE                                           ,
  TESTDATAIO_GPIOENTRYID_LED_GREEN                                            ,
  TESTDATAIO_GPIOENTRYID_BTN_BLUE                                             ,  

  TESTDATAIO_GPIOENTRYID_FATSD_CS                                             ,  
  TESTDATAIO_GPIOENTRYID_FATSD_SWITCH                                         ,  
   
  TESTDATAIO_GPIOENTRYID_LED_NEOPIXEL                                         ,  

  TESTDATAIO_GPIOENTRYID_TEST_INTERRUPT                                       ,  

  TESTDATAIO_GPIOENTRYID_I2C_CCS811_WAKEUP                                    ,
  
  TESTDATAIO_GPIOENTRYID_SPI_DISPLAY_CS                                       ,                                                      
  TESTDATAIO_GPIOENTRYID_SPI_DISPLAY_RESET                                    ,  
  TESTDATAIO_GPIOENTRYID_SPI_DISPLAY_DC                                       ,
  TESTDATAIO_GPIOENTRYID_SPI_DISPLAY_BACKLIGHT                  
};


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class DIOSTREAM;
class MAIN;

class TESTDATAIO : public APPBASE
{
  public:
                        TESTDATAIO                          ();
    virtual            ~TESTDATAIO                          ();

    bool                AppProc_PlatformIni                 ();
    bool                AppProc_Ini                         ();
    bool                AppProc_FirstUpdate                 ();
    bool                AppProc_Update                      ();
    bool                AppProc_End                         ();
    bool                AppProc_PlatformEnd                 ();

    bool                Test_Random                         ();

    bool                Test_DIOStreamUART                  ();

    bool                Test_DIOStreamUSBReadCommand        (DIOSTREAM* diostream, XBUFFER& command);
    bool                Test_DIOStreamUSB                   ();


    bool                I2CTest_6AxisTrackingLSM303DLHC     (int port, int timeout);
    bool                I2CTest_6AxisTrackingBMI270         (int port, int timeout);
    bool                I2CTest_AxisTrackingMPU9150         (int port, int timeout);
    bool                I2CTest_ADDAConverterPCF8591        (int port, int timeout);
    bool                I2CTest_AirQualityCCS811            (int port, int timeout);
    bool                I2CTest_EEprom24XXX                 (int port, int timeout);
    bool                I2CTest_GPIOMCP2317                 (int port, int timeout);
    bool                I2CTest_GPIOPCF8574                 (int port, int timeout);
    bool                I2CTest_LightSensorTSL2561          (int port, int timeout);
    bool                I2CTest_OLEDDisplaySSD1306          (int port, int timeout);
    bool                I2CTest_PWMControlerPCA9685         (int port, int timeout);
    bool                I2CTest_TemHumSensorAM2315          (int port, int timeout);
    bool                I2CTest_TemHumSensorSHT20           (int port, int timeout);    
    bool                I2CTest_MonitorGaugeLTC2942         (int port, int timeout);
    bool                I2CTest_BatteryChargerBQ24295       (int port, int timeout);
    bool                I2CTest_TouchSensorAT42QT1060       (int port, int timeout);
    
    bool                Test_DIOStreamI2C                   ();


    bool                SPITest_GPIOMCP23S17                (int port, int chipselect, int timeout); 
    bool                SPITest_LCDDisplayPCF8833           (int port, int chipselect, int timeout); 
    bool                SPITest_OLEDDisplaySSD1306          (int port, int chipselect, int timeout); 
    bool                SPITest_OLEDDisplaySSD1331          (int port, int chipselect, int timeout);   
    bool                SPITest_TFTDisplayILI9341           (int port, int chipselect, int timeout); 
    bool                SPITest_TFTDisplayST7789            (int port, int chipselect, int timeout); 
    bool                SPITest_TouchScreenSTMPE610         (int port, int chipselect, int timeout);   
      
    bool                Test_DIOStreamSPI                   ();
    
    

    bool                Test_DIOGPIO                        (); 
    bool                Test_DIOGPIO_Interrupt              ();

    bool                Test_EEPROMMemory                   ();

   

    bool                Test_DIONeoPixel                    ();

    bool                Test_DirFunctions                   ();
    bool                Test_FileFunctions                  ();


    static void         Test_Callback_Interrupt             (void* param);

  private:

    void                Clean                               ();

};


/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/


#endif



