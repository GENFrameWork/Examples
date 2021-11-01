/**-------------------------------------------------------------------------------------------------------------------
*
* @file       TestDataIO.cpp
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

#include "XFactory.h"
#include "XSleep.h"
#include "XRand.h"
#include "XPath.h"
#include "XDir.h"
#include "XFile.h"
#include "XTrace.h"
#include "XEEPROMMemoryManager.h"

#include "DIOFactory.h"
#include "DIOGPIO.h"
#include "DIOStreamUARTConfig.h"
#include "DIOStreamUART.h"
#include "DIOStreamUSBConfig.h"
#include "DIOStreamUSB.h"
#include "DIOStreamI2CConfig.h"
#include "DIOStreamI2C.h"
#include "DIOStreamSPIConfig.h"
#include "DIOStreamSPI.h"

#include "DIOI2C_Devices.h"

#include "DIOSPI_Devices.h"

#include "DIOLedNeoPixelWS2812B.h"

#ifdef WINDOWS
#include "TestDataIO_WindowsPlatform.h"
#endif

#ifdef LINUX
#include "TestDataIO_LinuxPlatform.h"
#endif  
  
#ifdef HW_STM32
#include "TestDataIO_STM32Platform.h"
#endif


#include "TestDataIO.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

APPLICATIONCREATEINSTANCE(TESTDATAIO, testdataio)

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TESTDATAIO::TESTDATAIO()
* @brief      Constructor
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
TESTDATAIO::TESTDATAIO()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TESTDATAIO::~TESTDATAIO()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
TESTDATAIO::~TESTDATAIO()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTDATAIO::AppProc_PlatformIni()
* @brief      AppProc_PlatformIni
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::AppProc_PlatformIni()
{
  //--------------------------------------------------------------------------------------
  
  #ifdef WINDOWS
  Windows_Platform_Ini();
  #endif  

  //--------------------------------------------------------------------------------------
  
  #ifdef LINUX
  Linux_Platform_Ini();    
  #endif  
  
  //--------------------------------------------------------------------------------------

  #ifdef HW_STM32
  STM32_Platform_Ini();
  #endif
  
  //--------------------------------------------------------------------------------------

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTDATAIO::AppProc_Ini()
* @brief      AppProc_Ini
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::AppProc_Ini()
{
  XSTRING string;

  string = TESTDATAIO_NAMEAPP;
  XTRACE_SETAPPLICATIONNAME(string);
  XTRACE_SETAPPLICATIONVERSION(TESTDATAIO_VERSION, TESTDATAIO_SUBVERSION, TESTDATAIO_SUBVERSIONERR);

  #ifdef MICROCONTROLLER
    XTRACE_SETTARGET(0, XTRACE_TYPE_SPECIAL , XTRACE_DEFAULT_SPECIALAIM);
  #else
    XTRACE_SETTARGET(0, XTRACE_TYPE_NET     , XTRACE_DEFAULT_NETAIM1);
  #endif

    
  XTRACE_SCREENCLEAR;
  XTRACE_STATUSCLEAR;
  
  XTRACE_PRINTCOLOR(1, __L("Start Application"));
  #ifdef HW_STM32
  STM32_Heap_Usage();  
  #endif

 
  //--------------------------------------------------------------------------------------------------
  
  //GEN_XPATHSMANAGER.AdjustRootPathDefault(APPDEFAULT_DIRECTORY_ROOT);
  
  //GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_SOUNDS        , APPDEFAULT_DIRECTORY_SOUNDS);
  
  //GEN_XPATHSMANAGER.CreateAllPathSectionOnDisk();
  
  //--------------------------------------------------------------------------------------------------
  
  /*
  XBYTE color[3] = { 0x55, 0xAA, 0xFF };

  XTRACE_PRINTSTATUSCOLOR(XTRACE_COLOR_BLUE, __L("Estado bolean"), true);
  XTRACE_PRINTSTATUSCOLOR(XTRACE_COLOR_BLUE, __L("Estado String"), __L("estado"));
  XTRACE_PRINTSTATUSCOLOR(XTRACE_COLOR_BLUE, __L("Estado DWORD"), (XDWORD)42);
  XTRACE_PRINTSTATUSCOLOR(XTRACE_COLOR_BLUE, __L("Estado Float"), 42.0f);
  XTRACE_PRINTSTATUSCOLOR(XTRACE_COLOR_BLUE, __L("Estado Color"), color);
  */


  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTDATAIO::AppProc_FirstUpdate()
* @brief      AppProc_FirstUpdate
* @ingroup    
* 
* @author     Abraham J. Velez 
* @date       10/10/2021 13:19:58
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::AppProc_FirstUpdate()
{
  // Test_Random();
  
  //Test_DirFunctions();  
  //Test_FileFunctions();
  
  // Test_DIOStreamUART();
  // Test_DIOStreamUSB();
  // Test_DIOStreamI2C();
  Test_DIOStreamSPI();
  // Test_DIOGPIO();

  // Test_DIOGPIO_Interrupt();

  // Test_EEPROMMemory();

  // Test_DIONeoPixel();
    
  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTDATAIO::AppProc_Update()
* @brief      AppProc_Update
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::AppProc_Update()
{
  return false;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTDATAIO::AppProc_End()
* @brief      AppProc_End
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::AppProc_End()
{
  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTDATAIO::AppProc_PlatformEnd()
* @brief      AppProc_PlatformEnd
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::AppProc_PlatformEnd()
{
  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTDATAIO::Test_Random()
* @brief      Test_Random
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::Test_Random()
{
  bool status = false;

  XRAND* xrand = GEN_XFACTORY.CreateRand();
  if(xrand)
    {
      if(xrand->Max(50) == 5) status = false;

      GEN_XFACTORY.DeleteRand(xrand);
    }

  if(status)
    {

    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTDATAIO::Test_DIOStreamUART()
* @brief      Test_DIOStreamUART
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::Test_DIOStreamUART()
{
  DIOSTREAMUARTCONFIG diostreamuartconfig;
  DIOSTREAMUART*      diostreamuart;

  diostreamuartconfig.SetPort(1);
  diostreamuartconfig.SetBaudRate(19200);
  diostreamuartconfig.SetDataBits(DIOSTREAMUARTDATABIT_8);
  diostreamuartconfig.SetParity(DIOSTREAMUARTPARITY_ODD);
  diostreamuartconfig.SetStopBits(DIOSTREAMUARTSTOPBITS_ONE);
  diostreamuartconfig.SetFlowControl(DIOSTREAMUARTFLOWCONTROL_NONE);

  diostreamuart = (DIOSTREAMUART*)GEN_DIOFACTORY.CreateStreamIO(&diostreamuartconfig);
  if(!diostreamuart) return false;

  if(!diostreamuart->Open()) return false;

  #define MAXSIZEMSG 64

  XBYTE  data[MAXSIZEMSG];
  int    br;
  bool   exit = false;

  while(!exit)
    {
      //XTRACE_PRINTCOLOR(1, __L("-1-"));

      br = diostreamuart->GetInXBuffer()->GetSize();
      if(br)
        {
          if(br > MAXSIZEMSG) br = MAXSIZEMSG;

          br = diostreamuart->Read(data, br);
          diostreamuart->Write(data, br);

          XTRACE_PRINTDATABLOCKCOLOR(1, data, br);

          /*
          for(int c=0; c<br; c++)
            {
              if(data[c] == 0x1B)
                {
                  exit = true;
                  break;
                }
            }
          */
        }
    }

  diostreamuart->Close();
  GEN_DIOFACTORY.DeleteStreamIO(diostreamuart);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTDATAIO::Test_DIOStreamUSBReadCommand(DIOSTREAM* diostream, XBUFFER& command)
* @brief      Test_DIOStreamUSBReadCommand
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @param[in]  diostream :
* @param[in]  command :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::Test_DIOStreamUSBReadCommand(DIOSTREAM* diostream, XBUFFER& command)
{
  #define IDLITTLEPROTOCOL 0xFE

  if(!diostream) return false;

  if(diostream->GetInXBuffer()->GetSize()<2) return false;

  XBYTE ID    = 0;
  XBYTE size  = 0;

  ID    = diostream->GetInXBuffer()->Get()[0];
  size  = diostream->GetInXBuffer()->Get()[1];

  if(ID != IDLITTLEPROTOCOL) return false;
  if(!size)                  return false;

  if(!diostream->WaitToFilledReadingBuffer(size, 4)) return false;

  command.Resize(size);

  if(diostream->Read(command) != size) return false;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTDATAIO::Test_DIOStreamUSB()
* @brief      Test_DIOStreamUSB
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::Test_DIOStreamUSB()
{
  DIOSTREAMUSBCONFIG  diostreamusbconfig;
  DIOSTREAMUSB*       diostreamusb;

  diostreamusbconfig.SetMode(DIOSTREAMMODE_CLIENT);
  diostreamusb = (DIOSTREAMUSB*)GEN_DIOFACTORY.CreateStreamIO(&diostreamusbconfig);
  if(!diostreamusb) return false;

  if(!diostreamusb->Open()) return false;

  XTRACE_PRINTCOLOR(1, __L("Open USB ..."));


  /*
  #define IDLITTLEPROTOCOL 0xFE

  XBUFFER xbuffer;
  bool    exit = false;

  while(!exit)
    {
      if(Test_DIOStreamUSBReadCommand(diostreamusb, xbuffer))
        {
          diostreamusb->Write(xbuffer);

        }
    }
  */


  #define MAXSIZEMSG 64

  XBYTE  data[MAXSIZEMSG];
  int    br;
  bool   exit = false;

  while(!exit)
    {
      br = diostreamusb->GetInXBuffer()->GetSize();
      if(br)
        {
          if(br >= MAXSIZEMSG) br = MAXSIZEMSG-1;

          memset(data, 0 , MAXSIZEMSG);

          br = diostreamusb->Read(data, br);
          diostreamusb->Write(data, br);


        }
    }

  diostreamusb->Close();
  GEN_DIOFACTORY.DeleteStreamIO(diostreamusb);

  return true;
}





/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTDATAIO::I2CTest_6AxisTrackingLSM303DLHC(int port, int timeout)
* @brief      I2CTest_6AxisTrackingLSM303DLHC
* @ingroup    
* 
* @author     Abraham J. Velez 
* @date       25/09/2021 13:08:22
* 
* @param[in]  port : 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::I2CTest_6AxisTrackingLSM303DLHC(int port, int timeout)
{
  bool status =  false;

  DIOI2C6AXISTRACKINGLSM303DLHC* lsm303dlhc = new DIOI2C6AXISTRACKINGLSM303DLHC();
  if(lsm303dlhc)
    {
      status = lsm303dlhc->Ini(port, DIOI2CLSM303DLHC_ADDR_ACCELEROMETER, DIOI2CLSM303DLHC_ADDR_COMPASS, timeout);        
      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("Connect I2C device 6 Axis Tracking LSM303DLHC Addr[ Accelerometer 0x%02X, Compass 0x%02X]: %s"), DIOI2CLSM303DLHC_ADDR_ACCELEROMETER, DIOI2CLSM303DLHC_ADDR_COMPASS, (status?__L("Ok."):__L("Error!")));      
      if(status)      
        {          
          lsm303dlhc->SetOffset(0.00f, 0.00f, 0.00f);
          lsm303dlhc->SetScale(1.00f, 1.00f, 1.00f);
          
          int c = 0;

          while(c < 100)
            {
              XWORD accelerometer_x = 0;
              XWORD accelerometer_y = 0;
              XWORD accelerometer_z = 0;

              XWORD compass_x       = 0;
              XWORD compass_y       = 0;
              XWORD compass_z       = 0;
              
              status = lsm303dlhc->Read(accelerometer_x, accelerometer_y, accelerometer_z, compass_x, compass_y, compass_z);

              XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE,__L("accelerometer: %d, %d, %d compass: %d, %d, %d"), (int)accelerometer_x, 
                                                                                                        (int)accelerometer_y, 
                                                                                                        (int)accelerometer_z, 
                                                                                                        (int)compass_x, 
                                                                                                        (int)compass_y, 
                                                                                                        (int)compass_z);

              //GEN_XSLEEP.MilliSeconds(200);
              if(!status) break;
              c++;             
            }

          lsm303dlhc->End();
        }

      delete lsm303dlhc;
    }    

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTDATAIO::I2CTest_6AxisTrackingBMI270(int port, int timeout)
* @brief      I2CTest_6AxisTrackingBMI270
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       29/09/2021 13:56:36
* 
* @param[in]  port : 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::I2CTest_6AxisTrackingBMI270(int port, int timeout)
{
  bool status =  false;


  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTDATAIO::I2CTest_AxisTrackingMPU9150(int port, int timeout)
* @brief      I2CTest_AxisTrackingMPU9150
* @ingroup    
* 
* @author     Abraham J. Velez 
* @date       25/09/2021 13:29:06
* 
* @param[in]  port : 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::I2CTest_AxisTrackingMPU9150(int port, int timeout)
{
  bool status =  false;


  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTDATAIO::I2CTest_ADDAConverterPCF8591(int port, int timeout)
* @brief      I2CTest_ADDAConverterPCF8591
* @ingroup    
* 
* @author     Abraham J. Velez 
* @date       25/09/2021 13:16:17
* 
* @param[in]  port : 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::I2CTest_ADDAConverterPCF8591(int port, int timeout)
{
  bool status =  false;

 	DIOI2CADDACONVERTERPCF8591* converterPCF8591 = new DIOI2CADDACONVERTERPCF8591;
	if(converterPCF8591) 
    {
      status = converterPCF8591->Ini(port, DIOI2CADDACONVERTERPCF8591_ADDR, timeout);
      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("Connect I2C device Analog/Digital-Digital/Analog converter PCF8591 Address [0x%02X]: %s"), DIOI2CADDACONVERTERPCF8591_ADDR, (status?__L("Ok."):__L("Error!")));        
      if(status)
        {	
          int c = 0;
          int d = 0xA0;
          
          while(c < 100)
            {
              for(; d<0xFF; d++)
                {
                  converterPCF8591->WriteDAChannel((XBYTE)d);														
                  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("DAChannel [0x%02X]"), d);        
                }

              for(; d>0xA0; d--)
                {
                  converterPCF8591->WriteDAChannel((XBYTE)d);														
                  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("DAChannel [0x%02X]"), d);        
                }
        
              c++;
            }
                   
          converterPCF8591->WriteDAChannel(0);	      
          
          converterPCF8591->End();
        }

      delete converterPCF8591;
    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTDATAIO::I2CTest_AirQualityCCS811(int port, int timeout)
* @brief      I2CTest_AirQualityCCS811
* @ingroup    
* 
* @author     Abraham J. Velez 
* @date       25/09/2021 13:11:50
* 
* @param[in]  port : 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::I2CTest_AirQualityCCS811(int port, int timeout)
{
  bool status =  false;

  //#define AIRQUALITYCCS811_NTC

  XTIMER* timerwakeup = GEN_XFACTORY.CreateTimer();
  if(!timerwakeup) return false;
  
  GEN_DIOGPIO.SetMode(TESTDATAIO_GPIOENTRYID_I2C_CCS811_WAKEUP, DIOGPIO_MODE_OUTPUT);  
  
  DIOI2CAIRQUALITYCCS811* airqualityCCS811 = new DIOI2CAIRQUALITYCCS811();
  if(airqualityCCS811)
    {      
      status = airqualityCCS811->Ini(port, DIOI2CAIRQUALITYCCS811_ADDR2, timeout);
      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("Connect I2C device Air Quality CCS811 Address [0x%02X]: %s"), DIOI2CAIRQUALITYCCS811_ADDR2, (status?__L("Ok."):__L("Error!")));        
      if(status)
        {
          XBYTE hwversion   = 0;
          XWORD bootversion = 0;
          XWORD appversion  = 0;
          bool  status;
          
          status = airqualityCCS811->GetHW_Version(hwversion);
          XTRACE_PRINTCOLOR((status?2:4), __L("Hardware Version    : %02X"), hwversion);

          status = airqualityCCS811->GetBoot_Version(bootversion);
          XTRACE_PRINTCOLOR((status?2:4), __L("Boot Version        : %04X"), bootversion);

          status = airqualityCCS811->GetApp_Version(appversion);
          XTRACE_PRINTCOLOR((status?2:4), __L("Application Version : %04X"), appversion);

          #ifdef AIRQUALITYCCS811_NTC
          float temperature;
          float resistance;
          airqualityCCS811->SetReferenceResistance(9950);
          #else
          airqualityCCS811->SetEnvironmentalData(50.00f, 22.00f);
          #endif

          if(airqualityCCS811->SetDriveMode(3))
            {
              GEN_DIOGPIO.SetValue(TESTDATAIO_GPIOENTRYID_I2C_CCS811_WAKEUP, false);
              timerwakeup->Reset();
              
              int c = 0;

              while(c < 100)
                {
                  if(timerwakeup->GetMeasureHours() > 4)                  
                    {                      
                      GEN_DIOGPIO.SetValue(TESTDATAIO_GPIOENTRYID_I2C_CCS811_WAKEUP, true);
                      timerwakeup->Reset();
                    }

                  if(!airqualityCCS811->HaveStatusError())
                    {
                      if(airqualityCCS811->IsDataAvailable())
                        {
                          XWORD TVOC   = 0;
                          XWORD CO2    = 0;

                          status = airqualityCCS811->ReadData(TVOC, CO2);
                          XTRACE_PRINTCOLOR((status?1:4),__L("Read data: TVOC %6d, CO2 %6d : %s"), TVOC, CO2, (status?__L("Ok!"):__L("Error!")));

                          #ifdef AIRQUALITYCCS811_NTC
                          status = airqualityCCS811->ReadNTC(temperature, resistance);
                          XTRACE_PRINTCOLOR((status?2:4),__L("NTC read: Temperature %f, Resistance %f. "), (double)temperature, (double)resistance);
                          if(status) airqualityCCS811->SetEnvironmentalData(50.00f, temperature);
                          #endif 
                          
                          c++;
                        }
                    }
                   else
                    {
                      XBYTE    errorcode = airqualityCCS811->GetStatusErrorCode();
                      XSTRING  errorstr;

                      switch(errorcode)
                        {
                          case DIOI2CAIRQUALITYCCS811_ERROR_WRITE_REG_INVALID   : errorstr = __L("The CCS811 received an I2C write request addressed to this station but with invalid register address ID");  break;
                          case DIOI2CAIRQUALITYCCS811_ERROR_READ_REG_INVALID    : errorstr = __L("The CCS811 received an I2C read request to a mailbox ID that is invalid");                                  break;
                          case DIOI2CAIRQUALITYCCS811_ERROR_MEASMODE_INVALID    : errorstr = __L("The CCS811 received an I2C request to write an unsupported mode to MEAS_MODE");                             break;
                          case DIOI2CAIRQUALITYCCS811_ERROR_MAX_RESISTANCE      : errorstr = __L("The sensor resistance measurement has reached or exceeded the maximum range");                              break;
                          case DIOI2CAIRQUALITYCCS811_ERROR_HEATER_FAULT        : errorstr = __L("The Heater current in the CCS811 is not in range");                                                         break;
                          case DIOI2CAIRQUALITYCCS811_ERROR_HEATER_SUPPLY       : errorstr = __L("The Heater voltage is not being applied correctly");                                                        break;
                          case DIOI2CAIRQUALITYCCS811_ERROR_RESERVED1           :
                          case DIOI2CAIRQUALITYCCS811_ERROR_RESERVED2           : errorstr = __L("Reserved for Future Use");                                                                                  break;
                        }

                      XTRACE_PRINTCOLOR(4, __L("Error [%d] in sensor: %s"), errorcode, errorstr.Get());
                    }

                  GEN_XSLEEP.Seconds(1);                                   
                  
                  GEN_DIOGPIO.SetValue(TESTDATAIO_GPIOENTRYID_I2C_CCS811_WAKEUP, false);                  
                }
            } 

          airqualityCCS811->End();

        } 
    }

  delete airqualityCCS811;
  
  GEN_XFACTORY.DeleteTimer(timerwakeup);  

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTDATAIO::I2CTest_EEprom24XXX(int port, int timeout)
* @brief      I2CTest_EEprom24XXX
* @ingroup    
* 
* @author     Abraham J. Velez 
* @date       25/09/2021 13:28:44
* 
* @param[in]  port : 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::I2CTest_EEprom24XXX(int port, int timeout)
{
  bool status =  false;

  DIOI2CEEPROM24XXX* eeprom24xxx = new DIOI2CEEPROM24XXX;
	if(eeprom24xxx)
    {
	    eeprom24xxx->SetType(DIOI2CEEPROM24XXXTYPE_08);

      status = eeprom24xxx->Ini(port, DIOI2CEEPROM2408_ADDR, timeout);
      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("Connect I2C device EEPROM 24XXX Address [0x%02X]: %s"), DIOI2CEEPROM2408_ADDR, (status?__L("Ok."):__L("Error!")));        
	    if(status)
		    {
          /*
			    XBYTE dataDPO2COMP[] = {	0xFF, 0xFF, 0xFF, 0xFF, 0x44, 0x50, 0x4F, 0x32, 0x43, 0x4F, 0x4D, 0x50, 0x00, 0xFF, 0xFF, 0xFF,  // DPO2COMP
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0x76, 0x31, 0x2E, 0x30, 0x30, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  // v1.00
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  																
														     };
										
			    XBYTE dataDPO2EMBD[] = {	0xFF, 0xFF, 0xFF, 0xFF, 0x44, 0x50, 0x4F, 0x32, 0x45, 0x4D, 0x42, 0x44, 0x00, 0xFF, 0xFF, 0xFF,  // DPO2EMBD
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0x76, 0x31, 0x2E, 0x30, 0x30, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  // v1.00
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  																
														     };
					*/
			    XBYTE dataDPO2AUTO[] = {	0xFF, 0xFF, 0xFF, 0xFF, 0x44, 0x50, 0x4F, 0x32, 0x41, 0x55, 0x54, 0x4F, 0x00, 0xFF, 0xFF, 0xFF,	 // DPO2AUTO
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0x76, 0x31, 0x2E, 0x30, 0x30, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  // v1.00
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  																
														     };
          /*
			    XBYTE dataDPO2EMPTY[] = {	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,	 
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
																    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  																
														     };
          */

          XBUFFER  datawrite;
		      XBUFFER  dataread;
		      XSTRING  string;
					
			
			    //datawrite.Add(dataDPO2EMBD , sizeof(dataDPO2EMBD));																
			    //datawrite.Add(dataDPO2COMP , sizeof(dataDPO2COMP));					
			    datawrite.Add(dataDPO2AUTO , sizeof(dataDPO2AUTO));

			    XDWORD c = 0;

          status = eeprom24xxx->Write(0x0, datawrite);
          XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("EEPROM 24XXX Write: %s"), (status?__L("Ok."):__L("Error!")));    
			    
		
			    //status = eeprom24xxx->Write(0x0, dataDPO2COMP, 16); 						
			    //XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("EEPROM 24XXX Write: %s"), (status?__L("Ok."):__L("Error!")));    
			    

			    for(c=0; c<eeprom24xxx->GetSize(); c+=128)
				    {		
					    dataread.Delete();			

					    status = eeprom24xxx->Read(c, 128, dataread);
              XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("EEPROM 24XXX Read: %s"), (status?__L("Ok."):__L("Error!")));    								 
					    XTRACE_PRINTDATABLOCK(XTRACE_COLOR_BLUE, dataread);
			    	}						
	
		    }

      eeprom24xxx->End();
	    delete eeprom24xxx;

    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTDATAIO::I2CTest_GPIOMCP2317(int port, int timeout)
* @brief      I2CTest_GPIOMCP2317
* @ingroup    
* 
* @author     Abraham J. Velez 
* @date       25/09/2021 13:28:53
* 
* @param[in]  port : 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::I2CTest_GPIOMCP2317(int port, int timeout)
{
  bool status =  false;
  
  DIOI2CGPIOMCP2317* mcp2317 = new DIOI2CGPIOMCP2317;
	if(mcp2317) 
    {
      status = mcp2317->Ini(port, DIOI2CGPIOMCP2317_ADDR, timeout);
      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("Connect I2C device GPIO Extended MCP2317 Address [0x%02X]: %s"), DIOI2CGPIOMCP2317_ADDR, (status?__L("Ok."):__L("Error!")));
      if(status)
        {         
          mcp2317->Configure();

          XBYTE   rvalue = 0;
          XBYTE   wvalue;
          int     c      = 0;

          while(c < 100)
            {																
              for(int d=0; d<2; d++)
                {	
                  wvalue = (!d)?0x01:0x80;

                  for(int c=0; c<8; c++)
                    {					                                          
                      if(mcp2317->ReadInputs(DIOI2CGPIOMCP2317PORT_A, rvalue)) 
                        {
                          XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Inputs: %02X"), rvalue); 
                        }
                       else 
                        {
                          XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("Inputs: No read.")); 
                        }
                      

                      mcp2317->WriteOutputs(DIOI2CGPIOMCP2317PORT_B, wvalue);
                      
                      if(!d) wvalue <<= 1; else wvalue >>= 1;                     
                    }
                }	
              
              c++;              
            }      
        }	
      
      mcp2317->End();
      
      delete mcp2317;
    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTDATAIO::I2CTest_GPIOPCF8574(int port, int timeout)
* @brief      I2CTest_GPIOPCF8574
* @ingroup    
* 
* @author     Abraham J. Velez 
* @date       25/09/2021 13:18:31
* 
* @param[in]  port : 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::I2CTest_GPIOPCF8574(int port, int timeout)
{
  bool status =  false;

  DIOI2CGPIOPCF8574* pcf8574 = new DIOI2CGPIOPCF8574;
	if(pcf8574) 
    {
      status =  pcf8574->Ini(port, DIOI2CGPIOPCF8574_ADDR, timeout);
      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("Connect I2C device GPIO Extended PCF8574 Address [0x%02X]: %s"), DIOI2CGPIOPCF8574_ADDR, (status?__L("Ok."):__L("Error!")));        
      if(status)
        {
          XBYTE data  = 0;
          XBYTE data2 = 0;
          int   c     = 0;
          
          while(c < 100)
            {
              for(int d=0; d<8; d++)
                {							
                  data = 0x01;

                  if(d) data <<= d;

                  pcf8574->Write(data); 
							 
                  pcf8574->Read(data2); 							 
                  
                  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Read [0x%02X]  Write [0x%02X] "), data2, data);        							 						
                  
                  //GEN_XSLEEP.MilliSeconds(150);			
                }
              
              c++;
						}					
				}
					
			pcf8574->End();
			
      delete pcf8574;
    }  

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTDATAIO::I2CTest_LightSensorTSL2561(int port, int timeout)
* @brief      I2CTest_LightSensorTSL2561
* @ingroup    
* 
* @author     Abraham J. Velez 
* @date       25/09/2021 13:07:15
* 
* @param[in]  port : 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::I2CTest_LightSensorTSL2561(int port, int timeout)
{
  bool status =  false;

  DIOI2CLIGHTSENSORTSL2561* lightsensor;

  lightsensor =  new DIOI2CLIGHTSENSORTSL2561();
  if(lightsensor)
    {
      status = lightsensor->Ini(port, DIOI2CLIGHTSENSORTSL2561_ADDR3, timeout);      
      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("Connect I2C device Light Sensor TSL2561 Addr[0x%02X]: %s"), DIOI2CLIGHTSENSORTSL2561_ADDR3, (status?__L("Ok."):__L("Error!")));      
      if(status) 
        {
          status = lightsensor->SetIntegrationTime(DIOI2CLIGHTSENSORTSL2561INTEGRATIONTIME_101MS);
          if(status)
            {
              status = lightsensor->SetGain(DIOI2CLIGHTSENSORTSL2561GAIN_1X);
              if(status)
                {
                  XWORD   fullspectrum = 0;
                  XWORD   infrared     = 0;
                  XDWORD  lux          = 0;          
                  
                  int     c = 0;
              
                  while(c < 100)
                    {
                      status = lightsensor->Get(fullspectrum, infrared, lux, false);
                      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("Broadband: %d - Inflared: %d - Lux: %d  [%s]"), fullspectrum, infrared, lux, (status?__L("Ok."):__L("Error!")));                      
                      if(!status) break;
                    
                      c++;
                    }
                }
            }

          lightsensor->End();
        }
  
      delete lightsensor;
    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTDATAIO::I2CTest_OLEDDisplaySSD1306(int port, int timeout)
* @brief      I2CTest_OLEDDisplaySSD1306
* @ingroup    
* 
* @author     Abraham J. Velez 
* @date       25/09/2021 13:09:54
* 
* @param[in]  port : 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::I2CTest_OLEDDisplaySSD1306(int port, int timeout)
{
  bool status =  false;

  DIOI2COLEDDISPLAYSSD1306* OLEDdisplaySSD1306 = new DIOI2COLEDDISPLAYSSD1306(128, 64);
  if(OLEDdisplaySSD1306) 
    {
      status = OLEDdisplaySSD1306->Ini(1, DIOI2COLEDDISPLAYSSD1306_ADDR, timeout);
      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("Connect I2C device Display OLED display SSD1306 Address [0x%02X]: %s"), DIOI2COLEDDISPLAYSSD1306_ADDR, (status?__L("Ok."):__L("Error!")));        
      if(status)
        {          
          XBYTE* buffer = new XBYTE[OLEDdisplaySSD1306->GetSizeBuffer()];
          if(buffer)
            {
              memset(buffer, 0x00, OLEDdisplaySSD1306->GetSizeBuffer());

              OLEDdisplaySSD1306->SetBuffer(buffer);

              for(int c=0; c<8; c++)
                {
                  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Put Pixel x3 ... "));        
                  
                  OLEDdisplaySSD1306->PutPixel(0+c,  0+c, true);
                  OLEDdisplaySSD1306->PutPixel((OLEDdisplaySSD1306->GetWidth()/2)-c-1, (OLEDdisplaySSD1306->GetHeight()/2)-c-1, true);
                  OLEDdisplaySSD1306->PutPixel(OLEDdisplaySSD1306->GetWidth()-c-1, OLEDdisplaySSD1306->GetHeight()-c-1, true);

                  OLEDdisplaySSD1306->Update(buffer);                  
                }
              
              XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Clear Display ... "));        
              status = OLEDdisplaySSD1306->Clear(0xFF);

              delete [] buffer;
            }

          OLEDdisplaySSD1306->End();
        }

      delete OLEDdisplaySSD1306;
    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTDATAIO::I2CTest_PWMControlerPCA9685(int port, int timeout)
* @brief      I2CTest_PWMControlerPCA9685
* @ingroup    
* 
* @author     Abraham J. Velez 
* @date       25/09/2021 13:20:56
* 
* @param[in]  port : 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::I2CTest_PWMControlerPCA9685(int port, int timeout)
{
  bool status =  false;

  DIOI2CPWMCONTROLERPCA9685* pca9685 = new DIOI2CPWMCONTROLERPCA9685;
	if(pca9685) 
    {	
      status = pca9685->Ini(port, DIOI2CPWMCONTROLERPCA9685_ADDR, timeout);
      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("Connect I2C device PWM Controler PCA9685 Address [0x%02X]: %s"), DIOI2CPWMCONTROLERPCA9685_ADDR, (status?__L("Ok."):__L("Error!")));          
	    if(status)
		    {			    
          int c = 0;

			    if(!pca9685->SetPWMFrequency(60)) 
				    {
					    XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L(" Error PWM frecuency! "));						
				    }
					       
          while(c < 10)
            {              
              for(int d=0; d<16; d++)
				        {
					        if(!pca9685->SetPWM(d, 10, 150))
						        {
							        XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("Channel %02d Error Set PWM!"), d);						
						        } 
                   else
                    {
                      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Channel %02d Set PWM"), d);		
                    }
				        }
  				
			        for(int d=0; d<16; d++)
				        {
					        if(!pca9685->SetPWM(d, 30, 130))
						        {
							        XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("Channel %02d Error Set PWM!"), d);						
						        }
                   else
                    {
                      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Channel %02d Set PWM"), d);		
                    }
				        }

              c++;
		        }

          for(int d=0; d<16; d++)
				    {
					    if(!pca9685->SetPWM(d, 0, 0))
						    {
							    XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("Channel %02d Error Set PWM to zero!"), d);						
						    } 
                else
                {
                  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Channel %02d Set PWM to zero"), d);		
                }
				    }  							   			   
        } 

       pca9685->End();
				  
	     delete pca9685;
    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTDATAIO::I2CTest_TemHumSensorAM2315(int port, int timeout)
* @brief      I2CTest_TemHumSensorAM2315
* @ingroup    
* 
* @author     Abraham J. Velez 
* @date       25/09/2021 13:22:25
* 
* @param[in]  port : 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::I2CTest_TemHumSensorAM2315(int port, int timeout)
{
  bool status =  false;

  DIOI2CTEMHUMSENSORAM2315* temhumsensorAM2315 = new DIOI2CTEMHUMSENSORAM2315();
  if(temhumsensorAM2315)
    { 
      status = temhumsensorAM2315->Ini(port, DIOI2CTEMHUMSENSORAM2315_ADDRESS, timeout);
      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("Connect I2C device Temperature Humidity AM 2315 Address [0x%02X]: %s"), DIOI2CTEMHUMSENSORAM2315_ADDRESS, (status?__L("Ok."):__L("Error!")));          
      if(status)
        {          
          int c = 0;

          while(c < 100)
            {
              float temperature = 0.0f;
              float humidity    = 0.0f;

              if(temhumsensorAM2315->Read(temperature, humidity))
                {
                  XTRACE_PRINTCOLOR(1,__L("AM2315 Read Temperature: %2.2fC Relative Humidity %3.2f%% "), temperature, humidity);

                } else XTRACE_PRINTCOLOR(4,__L("Error read I2C device..."));
              
              c++;
            }               
        } 
      
      temhumsensorAM2315->End();
      
      delete temhumsensorAM2315;
    }
   
  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTDATAIO::I2CTest_TemHumSensorSHT20(int port, int timeout)
* @brief      I2CTest_TemHumSensorSHT20
* @ingroup    
* 
* @author     Abraham J. Velez 
* @date       25/09/2021 13:23:03
* 
* @param[in]  port : 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::I2CTest_TemHumSensorSHT20(int port, int timeout)
{
  bool status =  false;
  
  DIOI2CTEMHUMSENSORSHT20* temhumsensorSHT20 = new DIOI2CTEMHUMSENSORSHT20();
  if(temhumsensorSHT20)
    {
      if(temhumsensorSHT20->Ini(1, DIOI2CTEMHUMSENSORSHT20_ADDRESS, 3))
        {
          XTRACE_PRINTCOLOR(1, __L("Connect I2C device... Ok!"));
          
          int c = 0;

          while(c<100)
            {
              float temperature = 0.0f;
              float humidity    = 0.0f;

              if(temhumsensorSHT20->Read(temperature, humidity))
                {
                  XTRACE_PRINTCOLOR(1,__L("SHT20 Read Temperature: %2.2fC Relative Humidity %3.2f%% "), temperature, humidity);

                } else XTRACE_PRINTCOLOR(4,__L("Error read I2C device..."));

              GEN_XSLEEP.Seconds(1);

            }

          temhumsensorSHT20->End();
          
          c++;

        } else XTRACE_PRINTCOLOR(4,__L("Error to connect I2C device..."));

      delete temhumsensorSHT20;
    }
  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTDATAIO::I2CTest_MonitorGaugeLTC2942(int port, int timeout)
* @brief      I2CTest_MonitorGaugeLTC2942
* @ingroup    
* 
* @author     Abraham J. Velez 
* @date       25/09/2021 13:23:44
* 
* @param[in]  port : 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::I2CTest_MonitorGaugeLTC2942(int port, int timeout)
{
  bool status =  false;

  DIOI2CMONITORGAUGELTC2942* monitorgaugeLTC2942 = new DIOI2CMONITORGAUGELTC2942();
  if(monitorgaugeLTC2942)
    {      
      status = monitorgaugeLTC2942->Ini(port, DIOI2CMONITORGAUGELTC2942_ADDR, timeout);
      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("Connect I2C device Monitor Gauge LTC2942 Address [0x%02X]: %s"), DIOI2CMONITORGAUGELTC2942_ADDR, (status?__L("Ok."):__L("Error!")));          
      if(status)
        {
          int c = 0;
          
          while(c < 100)
            {          
              XWORD ACvalue = monitorgaugeLTC2942->GetAC();                   
              XTRACE_PRINTCOLOR(1,__L("AC Value: %d "), ACvalue);                
              
              c++;
            }          
        }
      
      monitorgaugeLTC2942->End();
      
      delete monitorgaugeLTC2942;
    }

  return status;
}




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTDATAIO::I2CTest_BatteryChargerBQ24295(int port, int timeout)
* @brief      I2CTest_BatteryChargerBQ24295
* @ingroup    
* 
* @author     Abraham J. Velez 
* @date       27/09/2021 9:47:49
* 
* @param[in]  port : 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::I2CTest_BatteryChargerBQ24295(int port, int timeout)
{
  bool status =  false;

  DIOI2CBATTERYCHARGERBQ24295* batterychargerBQ24295 = new DIOI2CBATTERYCHARGERBQ24295();
  if(batterychargerBQ24295)
    {            
      batterychargerBQ24295->SetGPIOEntryID(DIOI2CBATTERYCHARGERBQ24295_GPIOENTRYID_DET   , DIOGPIO_ID_NOTDEFINED);
      batterychargerBQ24295->SetGPIOEntryID(DIOI2CBATTERYCHARGERBQ24295_GPIOENTRYID_STAT  , DIOGPIO_ID_NOTDEFINED);
      batterychargerBQ24295->SetGPIOEntryID(DIOI2CBATTERYCHARGERBQ24295_GPIOENTRYID_QON   , DIOGPIO_ID_NOTDEFINED);
      batterychargerBQ24295->SetGPIOEntryID(DIOI2CBATTERYCHARGERBQ24295_GPIOENTRYID_CE    , DIOGPIO_ID_NOTDEFINED);
      batterychargerBQ24295->SetGPIOEntryID(DIOI2CBATTERYCHARGERBQ24295_GPIOENTRYID_INT   , DIOGPIO_ID_NOTDEFINED);

      status = batterychargerBQ24295->Ini(port, DIOI2CBATTERYCHARGERBQ24295_ADDR, timeout);
      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("Connect I2C device Battery Charger BQ24295 Address [0x%02X]: %s"), DIOI2CBATTERYCHARGERBQ24295_ADDR, (status?__L("Ok."):__L("Error!")));          
      if(status)
        {
          int c = 0;
          
          while(c < 100)
            {          

              c++;
            }          
        }
      
      batterychargerBQ24295->End();
      
      delete batterychargerBQ24295;
    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTDATAIO::I2CTest_TouchSensorAT42QT1060(int port, int timeout)
* @brief      I2CTest_TouchSensorAT42QT1060
* @ingroup    
* 
* @author     Abraham J. Velez 
* @date       27/09/2021 14:36:36
* 
* @param[in]  port : 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::I2CTest_TouchSensorAT42QT1060(int port, int timeout)
{
  bool status =  false;

  DIOI2CTOUCHSENSORAT42QT1060* touchsensorAT42QT1060 = new DIOI2CTOUCHSENSORAT42QT1060();
  if(touchsensorAT42QT1060)
    {            
      touchsensorAT42QT1060->SetGPIOInterruptEntryID(DIOGPIO_ID_NOTDEFINED);
      
      status = touchsensorAT42QT1060->Ini(port, DIOI2CBATTERYCHARGERBQ24295_ADDR, timeout);
      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("Connect I2C device Touch Sensor AT42QT1060 Address [0x%02X]: %s"), DIOI2CBATTERYCHARGERBQ24295_ADDR, (status?__L("Ok."):__L("Error!")));          
      if(status)
        {
          int c = 0;
          
          while(c < 100)
            {          

              c++;
            }          
        }
      
      touchsensorAT42QT1060->End();
      
      delete touchsensorAT42QT1060;
    }

  return status;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTDATAIO::Test_DIOStreamI2C()
* @brief      Test_DIOStreamI2C
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::Test_DIOStreamI2C()
{  
  #define TEST_I2C_TIMEOUT  3
  
  int   port      = 1; 
  int   timeout   = TEST_I2C_TIMEOUT;
  bool  status    = false; 
 
  //----------------------------------------------------------------------------
  /*
  DIOSTREAMI2CCONFIG  diostreami2cconfig;
  DIOSTREAMI2C*       diostreami2c;

  diostreami2cconfig.SetMode(DIOSTREAMMODE_SLAVE);
  diostreami2cconfig.SetPort(1);
  diostreami2cconfig.SetLocalAddress(0x30);

  diostreami2c = (DIOSTREAMI2C*)GEN_DIOFACTORY.CreateStreamIO(&diostreami2cconfig);
  if(!diostreami2c) return false;

  if(!diostreami2c->Open()) return false;

  XBYTE  data[16];
  int    br;
  bool   exit = false;

  while(!exit)
    {
      if(diostreami2c->WaitToFilledReadingBuffer(8, 1))
        {
          memset(data, 0, 16);

          br = diostreami2c->Read(data, 8);
          if(br)
            {
              XTRACE_PRINTDATABLOCKCOLOR(2, data, br);

              //diostreami2c->Write(data, 4);
              //diostreami2c->WaitToFlushOutXBuffer(3);
              //XDEBUG_PRINTDATABLOCK(4 , data, 4);

              if(data[0] == 0x1B)
                {
                  exit = true;
                  break;
                }
            }
        }
    }

  diostreami2c->Close();
  GEN_DIOFACTORY.DeleteStreamIO(diostreami2c);
  */ 

  //----------------------------------------------------------------------------  
  
  // status = I2CTest_6AxisTrackingLSM303DLHC(port,timeout);*/
  // status = I2CTest_AxisTrackingMPU9150(port, timeout);
  // status = I2CTest_ADDAConverterPCF8591(port, timeout);
  // status = I2CTest_AirQualityCCS811(port, timeout);
  // status = I2CTest_EEprom24XXX(port, timeout);
  // status = I2CTest_GPIOMCP2317(port, timeout);
  // status = I2CTest_GPIOPCF8574(port, timeout);
  // status = I2CTest_LightSensorTSL2561(port, timeout);
  status = I2CTest_OLEDDisplaySSD1306(port, timeout);
  // status = I2CTest_PWMControlerPCA9685(port, timeout);
  // status = I2CTest_TemHumSensorAM2315(port, timeout);
  // status = I2CTest_TemHumSensorSHT20(port, timeout);    
  // status = I2CTest_MonitorGaugeLTC2942(port, timeout);
  // status = I2CTest_BatteryChargerBQ24295(port, timeout);
  // status = I2CTest_TouchSensorAT42QT1060(port, timeout);
   
  //----------------------------------------------------------------------------
  
  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTDATAIO::SPITest_GPIOMCP23S17(int port, int chipselect, int timeout)
* @brief      SPITest_GPIOMCP23S17
* @ingroup    
* 
* @author     Abraham J. Velez 
* @date       25/09/2021 19:30:46
* 
* @param[in]  GPIO_entry[] : 
* @param[in]  port : 
* @param[in]  chipselect : 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::SPITest_GPIOMCP23S17(int port, int chipselect, int timeout)
{
  bool status = false;    
  
  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTDATAIO::SPITest_LCDDisplayPCF8833(int port, int chipselect, int timeout)
* @brief      SPITest_LCDDisplayPCF8833
* @ingroup    
* 
* @author     Abraham J. Velez 
* @date       25/09/2021 19:33:10
* 
* @param[in]  GPIO_entry[] : 
* @param[in]  port : 
* @param[in]  chipselect : 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::SPITest_LCDDisplayPCF8833(int port, int chipselect, int timeout)
{
  bool status = false; 

  DIOSPILCDDISPLAYPCF8833* LCDdisplayPCF8833 =  new DIOSPILCDDISPLAYPCF8833(DIOSPILCDDISPLAYPCF8833_PHILLIPS); 
  if(LCDdisplayPCF8833)  
    {   
      LCDdisplayPCF8833->SetGPIOEntryID(DIODISPLAYDEVICE_INDEX_GPIOENTRYID_RESET, TESTDATAIO_GPIOENTRYID_SPI_DISPLAY_RESET); 
      
      status  = LCDdisplayPCF8833->Ini(port, chipselect, timeout);
      XTRACE_PRINTCOLOR(1, __L("[LCD Display PCF8833] Ini Port [%d] Chipselect [%d]  : %s "), port, chipselect, status?__L("Ok!"):__L("Error!"));
      if(status)
        {
          XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("[LCD Display PCF8833] Resolution %d x %d"), LCDdisplayPCF8833->GetWidth(), LCDdisplayPCF8833->GetHeight());

          status = LCDdisplayPCF8833->Clear(DIOSPILCDDISPLAYPCF8833_COLOR_RED);
          XTRACE_PRINTCOLOR(1, __L("Send display Clean : %s "), status?__L("Ok!"):__L("Error!"));
          GEN_XSLEEP.Seconds(1);

          status = LCDdisplayPCF8833->Clear(DIOSPILCDDISPLAYPCF8833_COLOR_GREEN);
          XTRACE_PRINTCOLOR(1, __L("Send display Clean : %s "), status?__L("Ok!"):__L("Error!"));
          GEN_XSLEEP.Seconds(1);

          status = LCDdisplayPCF8833->Clear(DIOSPILCDDISPLAYPCF8833_COLOR_BLUE);
          XTRACE_PRINTCOLOR(1, __L("Send display Clean : %s "), status?__L("Ok!"):__L("Error!"));
          GEN_XSLEEP.Seconds(1);

          /*  
          XRAND* rnd = GEN_XFACTORY.CreateRand();
          if(rnd)
            {
              for(int y=0; y< LCDdisplayPCF8833->GetHeight(); y++)
                {
                  for(int x=0; x< LCDdisplayPCF8833->GetWidth(); x++)
                    {
                      LCDdisplayPCF8833->PutPixel(x , y, rnd->Between(0,65535));
                    }
                }


              XWORD*  buffer = NULL;
              XTRACE_PRINTCOLOR(1, __L("Create Random..."));

              buffer = new XWORD[LCDdisplayPCF8833->GetNPixels()];
              if(buffer)
                {
                  XTRACE_PRINTCOLOR(1, __L("Create Buffer Random..."));

                  int nframes = 0;

                  while(nframes < 5)
                    {
                      for(XDWORD c=0; c<LCDdisplayPCF8833->GetNPixels(); c++)
                        {
                          buffer[c] = rnd->Between(0,65535);
                        }

                      LCDdisplayPCF8833->Update((XBYTE*)buffer);
                      XTRACE_PRINTCOLOR(1, __L("Send display Update: %05d  %s    "), nframes,  status?__L("Ok!"):__L("Error!"));

                      nframes++;
                    }  

                  delete [] buffer;

                } else XTRACE_PRINTCOLOR(1, __L("Error Create Buffer Random..."));
           
            } else XTRACE_PRINTCOLOR(1, __L("Error Create Random..."));

          GEN_XFACTORY.DeleteRand(rnd);         
          */

        }

      status = LCDdisplayPCF8833->End();
      XTRACE_PRINTCOLOR(1, __L("[LCD Display PCF8833] End : %s "), status?__L("Ok!"):__L("Error!"));

      delete LCDdisplayPCF8833;
    }
     
  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTDATAIO::SPITest_OLEDDisplaySSD1306(int port, int chipselect, int timeout)
* @brief      SPITest_OLEDDisplaySSD1306
* @ingroup    
* 
* @author     Abraham J. Velez 
* @date       25/09/2021 19:35:07
* 
* @param[in]  GPIO_entry[] : 
* @param[in]  port : 
* @param[in]  chipselect : 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::SPITest_OLEDDisplaySSD1306(int port, int chipselect, int timeout)
{
  bool status = false;    

  DIOSPIOLEDDISPLAYSSD1306* OLEDdisplaySSD1306 = new DIOSPIOLEDDISPLAYSSD1306(128, 64);
  if(OLEDdisplaySSD1306) 
    {          

      OLEDdisplaySSD1306->SetGPIOEntryID(DIODISPLAYDEVICE_INDEX_GPIOENTRYID_RESET , TESTDATAIO_GPIOENTRYID_SPI_DISPLAY_RESET);
      OLEDdisplaySSD1306->SetGPIOEntryID(DIODISPLAYDEVICE_INDEX_GPIOENTRYID_DC    , TESTDATAIO_GPIOENTRYID_SPI_DISPLAY_DC);
      
      status = OLEDdisplaySSD1306->Ini(port, chipselect, timeout);
      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("[Oled Display SSD1306] Ini  Port [%d] Chipselect [%d]  : %s "), port, chipselect, status?__L("Ok!"):__L("Error!"));
      if(status)
        {     
          XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("[Oled Display SSD1306] Resolution %d x %d"), OLEDdisplaySSD1306->GetWidth(), OLEDdisplaySSD1306->GetHeight());
          XBYTE* buffer = new XBYTE[OLEDdisplaySSD1306->GetSizeBuffer()];
          if(buffer)
            {
                
              memset(buffer, 0x00, OLEDdisplaySSD1306->GetSizeBuffer());           

              for(int c=0; c<3; c++)
                {
                  status = OLEDdisplaySSD1306->Clear(0x00);                

                  XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("[Oled Display SSD1306] Clear FULL 0x00: %s"), status?__L("Ok!"):__L("Error!"));

                  OLEDdisplaySSD1306->PutPixel( 0+c,  0+c, true);
                  OLEDdisplaySSD1306->PutPixel(64-c-1, 32-c-1, true);
                  OLEDdisplaySSD1306->PutPixel(OLEDdisplaySSD1306->GetWidth()-c-1, OLEDdisplaySSD1306->GetHeight()-c-1, true);

                  status = OLEDdisplaySSD1306->Update(buffer);
                  XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("[Oled Display SSD1306] Update : %s"), status?__L("Ok!"):__L("Error!"));

                  status = OLEDdisplaySSD1306->Clear(0xFF);                
                  XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("[Oled Display SSD1306] Clear FULL 0xFF: %s"), status?__L("Ok!"):__L("Error!"));

                  GEN_XSLEEP.Seconds(1);
                }

              delete [] buffer;
            }
     
        } 

      
      status = OLEDdisplaySSD1306->End();
      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("[Oled Display SSD1306] End : %s "), status?__L("Ok!"):__L("Error!"));      

      delete OLEDdisplaySSD1306;      
    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTDATAIO::SPITest_OLEDDisplaySSD1331(int port, int chipselect, int timeout)
* @brief      SPITest_OLEDDisplaySSD1331
* @ingroup    
* 
* @author     Abraham J. Velez 
* @date       25/09/2021 19:35:19
* 
* @param[in]  GPIO_entry[] : 
* @param[in]  port : 
* @param[in]  chipselect : 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::SPITest_OLEDDisplaySSD1331(int port, int chipselect, int timeout)
{
  bool status = false;    

  DIOSPIOLEDDISPLAYSSD1331* OLEDdisplaySSD1331 = new DIOSPIOLEDDISPLAYSSD1331();
  if(OLEDdisplaySSD1331)
    {          
      OLEDdisplaySSD1331->SetGPIOEntryID(DIODISPLAYDEVICE_INDEX_GPIOENTRYID_RESET , TESTDATAIO_GPIOENTRYID_SPI_DISPLAY_RESET);
      OLEDdisplaySSD1331->SetGPIOEntryID(DIODISPLAYDEVICE_INDEX_GPIOENTRYID_DC    , TESTDATAIO_GPIOENTRYID_SPI_DISPLAY_DC);

      status  =  OLEDdisplaySSD1331->Ini(port, chipselect, timeout);
      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("[Oled Display SSD1331] Ini  Port [%d] Chipselect [%d]  : %s "), port, chipselect, status?__L("Ok!"):__L("Error!"));
      if(status)
        {
          XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("[Oled Display SSD1331] Resolution %d x %d"), OLEDdisplaySSD1331->GetWidth(), OLEDdisplaySSD1331->GetHeight());
          for(int c=0; c<5; c++)
            {
              status = OLEDdisplaySSD1331->Clear(DIOSPIOLEDDISPLAYSSD1331_COLOR_RED);
              XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("[Oled Display SSD1331] Clear RED: %s"), status?__L("Ok!"):__L("Error!"));
              GEN_XSLEEP.Seconds(1); 
              
              status = OLEDdisplaySSD1331->Clear(DIOSPIOLEDDISPLAYSSD1331_COLOR_GREEN);
              XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("[Oled Display SSD1331] Clear GREEN: %s"), status?__L("Ok!"):__L("Error!"));
              GEN_XSLEEP.Seconds(1); 
              
              status = OLEDdisplaySSD1331->Clear(DIOSPIOLEDDISPLAYSSD1331_COLOR_BLUE);
              XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("[Oled Display SSD1331] Clear BLUE: %s"), status?__L("Ok!"):__L("Error!"));
              GEN_XSLEEP.Seconds(1); 
              
              c++;
            }

          status = OLEDdisplaySSD1331->End();
          XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("[Oled Display SSD1331] End : %s "), status?__L("Ok!"):__L("Error!"));      
        }
      
      delete OLEDdisplaySSD1331;
    }        

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTDATAIO::SPITest_TFTDisplayILI9341(int port, int chipselect, int timeout)
* @brief      SPITest_TFTDisplayILI9341
* @ingroup    
* 
* @author     Abraham J. Velez 
* @date       25/09/2021 19:35:31
* 
* @param[in]  GPIO_entry[] : 
* @param[in]  port : 
* @param[in]  chipselect : 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::SPITest_TFTDisplayILI9341(int port, int chipselect, int timeout)
{
  bool status = false;    
   
  DIOSPITFTDISPLAYILI9341* TFTdisplayILI9341 = new DIOSPITFTDISPLAYILI9341();
  if(TFTdisplayILI9341)
    {      
      TFTdisplayILI9341->SetGPIOEntryID(DIODISPLAYDEVICE_INDEX_GPIOENTRYID_RESET , TESTDATAIO_GPIOENTRYID_SPI_DISPLAY_RESET);
      TFTdisplayILI9341->SetGPIOEntryID(DIODISPLAYDEVICE_INDEX_GPIOENTRYID_DC    , TESTDATAIO_GPIOENTRYID_SPI_DISPLAY_DC);                 
      
      status  = TFTdisplayILI9341->Ini(port, chipselect, timeout);
      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("[TFT Display ILI9341] Ini  Port [%d] Chipselect [%d]  : %s "), port, chipselect, status?__L("Ok!"):__L("Error!"));
      if(status)
        {
          XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("[TFT Display ILI9341] Resolution %d x %d"), TFTdisplayILI9341->GetWidth(), TFTdisplayILI9341->GetHeight());

          status = TFTdisplayILI9341->Clear(DIOSPITFTDISPLAYILI9341_COLOR_RED);
          XTRACE_PRINTCOLOR(1, __L("[TFT Display ILI9341] Clean RED  : %s "), status?__L("Ok!"):__L("Error!"));
          GEN_XSLEEP.Seconds(1);

          status = TFTdisplayILI9341->Clear(DIOSPITFTDISPLAYILI9341_COLOR_GREEN);
          XTRACE_PRINTCOLOR(1, __L("[TFT Display ILI9341] Clean GREEN: %s "), status?__L("Ok!"):__L("Error!"));
          GEN_XSLEEP.Seconds(1);

          status = TFTdisplayILI9341->Clear(DIOSPITFTDISPLAYILI9341_COLOR_BLUE);
          XTRACE_PRINTCOLOR(1, __L("[TFT Display ILI9341] Clean BLUE : %s "), status?__L("Ok!"):__L("Error!"));
          GEN_XSLEEP.Seconds(1);


          TFTdisplayILI9341->PutPixel(10, 10, DIOSPITFTDISPLAYILI9341_COLOR_WHITE);
          GEN_XSLEEP.Seconds(2);

          status = TFTdisplayILI9341->End();
          XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("[TFT Display ILI9341] End : %s "), status?__L("Ok!"):__L("Error!"));      
        }

      delete TFTdisplayILI9341;
    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTDATAIO::SPITest_TFTDisplayST7789(int port, int chipselect, int timeout)
* @brief      SPITest_TFTDisplayST7789
* @ingroup    
* 
* @author     Abraham J. Velez 
* @date       25/09/2021 19:35:40
* 
* @param[in]  GPIO_entry[] : 
* @param[in]  port : 
* @param[in]  chipselect : 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::SPITest_TFTDisplayST7789(int port, int chipselect, int timeout)
{
  bool status = false;    

  DIOSPITFTDISPLAYST7789* TFTdisplayST7789 = new DIOSPITFTDISPLAYST7789(240,240);
  if(TFTdisplayST7789)
    {                    
      TFTdisplayST7789->SetGPIOEntryID(DIODISPLAYDEVICE_INDEX_GPIOENTRYID_RESET       , TESTDATAIO_GPIOENTRYID_SPI_DISPLAY_RESET);
      TFTdisplayST7789->SetGPIOEntryID(DIODISPLAYDEVICE_INDEX_GPIOENTRYID_DC          , TESTDATAIO_GPIOENTRYID_SPI_DISPLAY_DC);    
      TFTdisplayST7789->SetGPIOEntryID(DIODISPLAYDEVICE_INDEX_GPIOENTRYID_BACKLIGHT   , TESTDATAIO_GPIOENTRYID_SPI_DISPLAY_BACKLIGHT);    

      status  = TFTdisplayST7789->Ini(port, chipselect, timeout);
      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("[TFT Display ST7789] Ini Port [%d] Chipselect [%d]  : %s "), port, chipselect, status?__L("Ok!"):__L("Error!"));
      if(status)
        {
          XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("TFT Display ST7789] Resolution %d x %d"), TFTdisplayST7789->GetWidth(), TFTdisplayST7789->GetHeight());


             
          status = TFTdisplayST7789->Clear(DIOSPITFTDISPLAYST7789_COLOR_RED);
          XTRACE_PRINTCOLOR(1, __L("[TFT Display ST7789] Clean RED  : %s "), status?__L("Ok!"):__L("Error!"));
          GEN_XSLEEP.Seconds(1);

          status = TFTdisplayST7789->Clear(DIOSPITFTDISPLAYST7789_COLOR_GREEN);
          XTRACE_PRINTCOLOR(1, __L("[TFT Display ST7789] Clean GREEN: %s "), status?__L("Ok!"):__L("Error!"));
          GEN_XSLEEP.Seconds(1);

          status = TFTdisplayST7789->Clear(DIOSPITFTDISPLAYST7789_COLOR_BLUE);
          XTRACE_PRINTCOLOR(1, __L("[TFT Display ST7789] Clean BLUE : %s "), status?__L("Ok!"):__L("Error!"));
          GEN_XSLEEP.Seconds(1);
                     

          for(int c=0; c<100; c++)   
            { 
              TFTdisplayST7789->PutPixel(c, c, DIOSPITFTDISPLAYST7789_COLOR_WHITE);
            }
          GEN_XSLEEP.Seconds(2);

          status = TFTdisplayST7789->End();
          XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("[TFT Display ST7789] End : %s "), status?__L("Ok!"):__L("Error!"));  

        }

      delete TFTdisplayST7789;
    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTDATAIO::SPITest_TouchScreenSTMPE610(int port, int chipselect, int timeout)
* @brief      SPITest_TouchScreenSTMPE610
* @ingroup    
* 
* @author     Abraham J. Velez 
* @date       25/09/2021 19:35:58
* 
* @param[in]  GPIO_entry[] : 
* @param[in]  port : 
* @param[in]  chipselect : 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::SPITest_TouchScreenSTMPE610(int port, int chipselect, int timeout)
{
  bool status = false;    
  
  return status;
}
    




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTDATAIO::Test_DIOStreamSPI()
* @brief      Test_DIOStreamSPI
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::Test_DIOStreamSPI()
{  
  #define TEST_SPI_TIMEOUT  3

  int   port        = 1;
  int   chipselect  = 0;  
  int   timeout     = TEST_SPI_TIMEOUT;
  bool  status      = false;

  //----------------------------------------------------------------------------
  
  /*
  DIOSTREAMSPICONFIG  diostreamspiconfig;
  DIOSTREAMSPI*       diostreamspi;

  diostreamspiconfig.SetMode(DIOSTREAMMODE_MASTER);
  diostreamspiconfig.SetPort(1);
  diostreamspiconfig.SetChipSelect(0);
  diostreamspiconfig.SetSPIMode(DIOSTREAMSPI_MODE_0);
  diostreamspiconfig.SetNBitsWord(8);
  diostreamspiconfig.SetSpeed(8*1000*1000);
  diostreamspiconfig.SetDelay(0);
  diostreamspiconfig.SetIsOnlyWrite(true);

  diostreamspiconfig.SetLocalDeviceNameByPort();


  diostreamspi = (DIOSTREAMSPI*)GEN_DIOFACTORY.CreateStreamIO(&diostreamspiconfig);
  if(!diostreamspi) return false;

  if(!diostreamspi->Open()) return false;

  XBUFFER databuffer;

  databuffer.Delete();
  databuffer.Bit_SetNBits(9);
  databuffer.Bit_SetBitsFree(0);

  databuffer.Bit_AddData((XWORD)0x01AA);
  databuffer.Bit_AddData((XWORD)0x0055);
  databuffer.Bit_AddData((XWORD)0x01CA);
  databuffer.Bit_AddData((XWORD)0x00FE);
  databuffer.Bit_AddData((XWORD)0x01FF);
  databuffer.Bit_AddData((XWORD)0x00FF);

  while(1)
    {
      diostreamspi->Write(databuffer.Get(), databuffer.GetSize());
      status = diostreamspi->WaitToFlushOutXBuffer(5);
      if(!status) break;

      GEN_XSLEEP.Seconds(1);
    }

  diostreamspi->Close();
  GEN_DIOFACTORY.DeleteStreamIO(diostreamspi);
  */

  //----------------------------------------------------------------------------
 

  //----------------------------------------------------------------------------
   
  //  status = SPITest_GPIOMCP23S17(port, chipselect, timeout); 
  //  status = SPITest_LCDDisplayPCF8833(port, chipselect, timeout); 
  //  status = SPITest_OLEDDisplaySSD1306(port, chipselect, timeout); 
  //  status = SPITest_OLEDDisplaySSD1331(port, chipselect, timeout); 
  //  status = SPITest_TFTDisplayILI9341(port, chipselect, timeout); 
      status = SPITest_TFTDisplayST7789(port, chipselect, timeout); 
  //  status = SPITest_TouchScreenSTMPE610(port, chipselect, timeout); 
 
  //----------------------------------------------------------------------------

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTDATAIO::Test_DIOGPIO()
* @brief      Test_DIOGPIO
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::Test_DIOGPIO()
{  
  GEN_DIOGPIO.SetMode(TESTDATAIO_GPIOENTRYID_LED_RED    , DIOGPIO_MODE_OUTPUT);  
  GEN_DIOGPIO.SetMode(TESTDATAIO_GPIOENTRYID_LED_BLUE   , DIOGPIO_MODE_OUTPUT);
  GEN_DIOGPIO.SetMode(TESTDATAIO_GPIOENTRYID_LED_ORANGE , DIOGPIO_MODE_OUTPUT);  
  GEN_DIOGPIO.SetMode(TESTDATAIO_GPIOENTRYID_LED_GREEN  , DIOGPIO_MODE_OUTPUT);
  GEN_DIOGPIO.SetMode(TESTDATAIO_GPIOENTRYID_BTN_BLUE   , DIOGPIO_MODE_INPUT);

  int counter = 0;
  int final   = 0;
  while(final<30)
    {
      bool press_btn = GEN_DIOGPIO.GetValue(TESTDATAIO_GPIOENTRYID_BTN_BLUE);
      
      if(press_btn) 
        {
          XTRACE_PRINTCOLOR(XTRACE_COLOR_PURPLE, __L("[Press button Blue]"));
        }
      
      switch(counter)
        {
          case 0 :  GEN_DIOGPIO.SetValue(TESTDATAIO_GPIOENTRYID_LED_RED   , true);
                    GEN_XSLEEP.MilliSeconds(100);

                    GEN_DIOGPIO.SetValue(TESTDATAIO_GPIOENTRYID_LED_RED   , false);
                    GEN_XSLEEP.MilliSeconds(100);
                    break;

          case 2 :  GEN_DIOGPIO.SetValue(TESTDATAIO_GPIOENTRYID_LED_BLUE  , true);
                    GEN_XSLEEP.MilliSeconds(100);

                    GEN_DIOGPIO.SetValue(TESTDATAIO_GPIOENTRYID_LED_BLUE  , false);
                    GEN_XSLEEP.MilliSeconds(100);
                    break;

          case 1 :  GEN_DIOGPIO.SetValue(TESTDATAIO_GPIOENTRYID_LED_ORANGE, true);
                    GEN_XSLEEP.MilliSeconds(100);

                    GEN_DIOGPIO.SetValue(TESTDATAIO_GPIOENTRYID_LED_ORANGE, false);
                    GEN_XSLEEP.MilliSeconds(100);
                    break;

          case 3 :  GEN_DIOGPIO.SetValue(TESTDATAIO_GPIOENTRYID_LED_GREEN , true);
                    GEN_XSLEEP.MilliSeconds(100);

                    GEN_DIOGPIO.SetValue(TESTDATAIO_GPIOENTRYID_LED_GREEN , false);
                    GEN_XSLEEP.MilliSeconds(100);
                    break;
        }

      counter++;
      if(counter >= 4) counter =0;
      
      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Counter %d"), counter);
      
      final++;
    }
  
  return true;

}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTDATAIO::Test_DIOGPIO_Interrupt()
* @brief      Test_DIOGPIO_Interrupt
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       14/09/2021 19:44:14
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::Test_DIOGPIO_Interrupt()
{
  DIOGPIO_ENTRY* GPIOentry = GEN_DIOGPIO.GPIOEntry_GetByID(TESTDATAIO_GPIOENTRYID_TEST_INTERRUPT);
  if(!GPIOentry) return false;

  GPIOentry->SetIntFunctionPointer(TESTDATAIO::Test_Callback_Interrupt);
  GPIOentry->SetIntParamPointer((void*)this);

  GEN_DIOGPIO.SetMode(TESTDATAIO_GPIOENTRYID_TEST_INTERRUPT,  DIOGPIO_MODE_INTERRUPT);  
    
  int c=0;
  while(c<100)
    {
      
      GEN_XSLEEP.Seconds(1);      
      c++;
    }
  
  return true;
}





/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTDATAIO::Test_EEPROMMemory()
* @brief      Test_EEPROMMemory
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::Test_EEPROMMemory()
{
  
  #define SRAMMARK 0xAA55CAFE

  XDWORD                  mark          = 0;
  XBYTE                   data[8];
  
  if(!GEN_XEEPROMMEMORYMANAGER.Ini()) return false;
    
  //GEN_XEEPROMMEMORYMANAGER.EraseAll();

  memset(data, 0, 8);

  GEN_XEEPROMMEMORYMANAGER.Read(0, mark);
  if(mark != SRAMMARK)
    {
      XTRACE_PRINTCOLOR(3, __L("SRAM Mark NOT found 0x%X."), mark);

      XBYTE data2[8] = { 1,2,3,4,5,6,7,8 };

      mark = SRAMMARK;

      GEN_XEEPROMMEMORYMANAGER.Write(0, mark);
      GEN_XEEPROMMEMORYMANAGER.Write(4, data2, 8);


      mark = 0;
      GEN_XEEPROMMEMORYMANAGER.Read(0, mark);

      XTRACE_PRINTCOLOR(2, __L("SRAM Mark Set 0x%X."), mark);

    }
    else
    {
      XTRACE_PRINTCOLOR(2, __L("SRAM Mark FOUND  !!!"));
    }

  GEN_XEEPROMMEMORYMANAGER.Read(4, data, 8);

  XTRACE_PRINTCOLOR(2, __L("SRAM data:"));
  XTRACE_PRINTDATABLOCKCOLOR(2, data, 8);

  GEN_XEEPROMMEMORYMANAGER.End();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void TESTDATAIO::Test_DIONeoPixel()
* @brief      Test_DIONeoPixel
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::Test_DIONeoPixel()
{
  DIOLEDNEOPIXELWS2812B* ledneopixelws2812b = GEN_DIOFACTORY.CreateLedNeopixelWS2812B(); 
  if(!ledneopixelws2812b)  return false;
  
  ledneopixelws2812b->SetDataGPIOEntryID(TESTDATAIO_GPIOENTRYID_LED_NEOPIXEL);
  
  if(ledneopixelws2812b->Ini(8))
    {      
      for(int c=0; c<30000; c++)
        {
          XBYTE data1[] = { 0xFF, 0xFF, 0xFF,  // White    
                            0x00, 0x20, 0x00,  // Red
                            0xFF, 0x00, 0x00,  // Green   
                            0x00, 0x00, 0xFF,  // Blue                             
                                                    
                            0xFF, 0xFF, 0xFF,  
                            0x00, 0xFF, 0x00,
                            0xFF, 0x00, 0x00,
                            0x00, 0x00, 0xFF,                            
                                                      
                          };

          ledneopixelws2812b->SendData(data1, sizeof(data1));
          GEN_XSLEEP.Seconds(1);

          XBYTE data2[] = { 0x00, 0x10, 0x00, 
                            0x00, 0x20, 0x00, 
                            0x00, 0x40, 0x00, 
                            0x00, 0x80, 0x00, 
                            0x00, 0xA4, 0x00, 
                            0x00, 0xC0, 0x00, 
                            0x00, 0xE0, 0x00, 
                            0x00, 0xFF, 0x00, 
                          };

          ledneopixelws2812b->SendData(data2, sizeof(data2));
          GEN_XSLEEP.Seconds(1);
          
          
          
          XBYTE data3[] = { 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00,
                          };

          ledneopixelws2812b->SendData(data3, sizeof(data3));
          GEN_XSLEEP.Seconds(1);

        }

      ledneopixelws2812b->End();
    }

  GEN_DIOFACTORY.DeleteLedNeopixelWS2812B(ledneopixelws2812b);
  
  return true;  
}




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTDATAIO::Test_DirFunctions()
* @brief      Test_DirFunctions
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       05/09/2021 12:02:54
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::Test_DirFunctions()
{
  XPATH       xpath;
  XDIR*       xdir;
  XDIRELEMENT element;

  xdir = GEN_XFACTORY.Create_Dir();
  if(xdir)
    {
      GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpath);
      xpath.Slash_Add();
                       
      if(xdir->FirstSearch(xpath,__L("*"), &element))
        {
          do{ XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[%s] %s"), (element.GetType()==XDIRELEMENTTYPE_DIR?__L("dir"):__L("fil")),  element.GetNameFile()->Get());

            } while(xdir->NextSearch(&element));          
        }

      xdir->Make(__L("TestDir\\Prueba\\"), true);
      xdir->Delete(__L("TestDir"), true);
      

      GEN_XFACTORY.Delete_Dir(xdir);  
    }

  return true;
}





/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TESTDATAIO::Test_FileFunctions()
* @brief      Test_FileFunctions
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       05/09/2021 12:03:02
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool TESTDATAIO::Test_FileFunctions()
{
  XPATH    xpath;
  XFILE*   xfile;
  XBUFFER  xbuffer;  
  bool     status = false;

  xfile = GEN_XFACTORY.Create_File();
  if(xfile)
    {
      GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpath);
      xpath.Slash_Add();
      xpath += __L("testfile.txt");
            
      if(xfile->Create(xpath))
        {
          XSTRING text;
            
          text = __L("Hola Radiola");

          XSTRING_CREATEOEM(text, chartext);
          xbuffer.Add((XBYTE*)chartext, text.GetSize());
          XSTRING_DELETEOEM(text, chartext);

          status = xfile->Write(xbuffer);

          xfile->Close();
        }
      
      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("Create/Write file [%s] : %s"), xpath.Get(), (status?__L("Ok"):__L("Error!")));
        
      status = false;
      xbuffer.Empty();

      if(xfile->Open(xpath, true))
        {
          XSTRING text;

          XDWORD  size = (XDWORD)xfile->GetSize();

          xbuffer.Resize(size);

          status = xfile->Read(xbuffer.Get(), size);

          xfile->Close();          
        }
      
      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("Open/Read file [%s] : %s"), xpath.Get(), (status?__L("Ok"):__L("Error!")));

      GEN_XFACTORY.Delete_File(xfile);
    }

  return status;
}




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void TESTDATAIO::Test_Callback_Interrupt(void* param)
* @brief      Test_Callback_Interrupt
* @ingroup    
* 
* @author     Abraham J. Velez 
* @date       28/09/2021 14:35:31
* 
* @param[in]  param : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void TESTDATAIO::Test_Callback_Interrupt(void* param)
{
  XTRACE_PRINTCOLOR(XTRACE_COLOR_PURPLE, __L("Interrupt made!"));
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void TESTDATAIO::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    TEST
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void TESTDATAIO::Clean()
{

}


