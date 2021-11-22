# --------------------------------------------------------------------
# testdataio : Example of console GEN FrameWork 
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.3.0)
project(testdataio)


set(GEN_DIRECTORY "../../../../../GENFrameWork") 

# --------------------------------------------------------------------
# Activate features/Defines

include("${GEN_DIRECTORY}/GEN/GEN_CMakeLists_Default.txt") 

set(DEBUG_FEATURE                                       true    CACHE BOOL "Activate Debug mode"                                        FORCE)

set(XTRACE_FEATURE                                      true    CACHE BOOL "Activate XTrace"                                            FORCE)
set(XMEMORY_CONTROL_FEATURE                             true    CACHE BOOL "Activate XMemory Control"                                   FORCE)

set(LINUX_VISUALSTUDIOCODEPAGE_FEATURE                  true    CACHE BOOL "Activate Linux CodePage Editor Visual Studio CP1252"        FORCE)   
                                    
set(DIO_FEATURE                                         true    CACHE BOOL "Activate Data Input/Output"                                 FORCE) 
set(DIO_STREAM_FEATURE                                  true    CACHE BOOL "Activate Data Input/Output Stream"                          FORCE)
set(DIO_STREAMUART_FEATURE                              true    CACHE BOOL "Activate Data Input/Output Stream UART"                     FORCE)
set(DIO_STREAMUSB_FEATURE                               true    CACHE BOOL "Activate Data Input/Output Stream USB"                      FORCE)
set(DIO_GPIO_FEATURE                                    true    CACHE BOOL "Activate GPIO"                                              FORCE)
#set(DIO_GPIO_PCPARALLEL_FEATURE                         true    CACHE BOOL "Activate Data Input/Output GPIO PC Parallel"                FORCE)

set(DIO_STREAMI2C_FEATURE                               true    CACHE BOOL "Activate Data Input/Output Stream I2C"                      FORCE)
set(DIO_I2C_6AXISTRACKING_BMI270_FEATURE                true    CACHE BOOL "Activate Data I2C 6 axis tracking BMI270"                   FORCE)
set(DIO_I2C_6AXISTRACKING_LSM303DLHC_FEATURE            true    CACHE BOOL "Activate Data I2C 6 axis tracking LSM303DLHC"               FORCE)
set(DIO_I2C_9AXISTRACKING_MPU9150_FEATURE               true    CACHE BOOL "Activate Data I2C 9 axis tracking MPU9150"                  FORCE)
set(DIO_I2C_ADDACONVERTER_PCF8591_FEATURE               true    CACHE BOOL "Activate Data I2C ADDA converter PCF8591"                   FORCE)
set(DIO_I2C_AIRQUALITY_CCS811_FEATURE                   true    CACHE BOOL "Activate Data I2C Air quality CCS811"                       FORCE)
set(DIO_I2C_EEPROM_24XXX_FEATURE                        true    CACHE BOOL "Activate Data I2C EEPROM 24XXX"                             FORCE)
set(DIO_I2C_GPIO_MCP2317_FEATURE                        true    CACHE BOOL "Activate Data I2C GPIO MCP2317"                             FORCE)
set(DIO_I2C_GPIO_PCF8574_FEATURE                        true    CACHE BOOL "Activate Data I2C GPIO PCF8574"                             FORCE)
set(DIO_I2C_LIGHTSENSOR_TSL2561_FEATURE                 true    CACHE BOOL "Activate Data I2C Light sensor TSL2561"                     FORCE)
set(DIO_I2C_OLEDDISPLAY_SSD1306_FEATURE                 true    CACHE BOOL "Activate Data I2C OLED Display SSD1306"                     FORCE)
set(DIO_I2C_PWMCONTROLER_PCA9685_FEATURE                true    CACHE BOOL "Activate Data I2C PWM Controler PCA9685"                    FORCE)
set(DIO_I2C_TEMHUMSENSOR_AM2315_FEATURE                 true    CACHE BOOL "Activate Data I2C Temperature Humidity Sensor AM2315"       FORCE)
set(DIO_I2C_TEMHUMSENSOR_SHT20_FEATURE                  true    CACHE BOOL "Activate Data I2C Temperature Humidity Sensor SHT20"        FORCE)
set(DIO_I2C_MONITORGAUGE_LTC2942_FEATURE                true    CACHE BOOL "Activate Data I2C Monitor Gauge LTC2942"                    FORCE)
set(DIO_I2C_BATTERYCHARGER_BQ24295_FEATURE              true    CACHE BOOL "Activate Data I2C Battery Charger BQ24295"                  FORCE)  
set(DIO_I2C_TOUCHSENSOR_AT42QT1060_FEATURE              true    CACHE BOOL "Activate Data I2C Touch Sensor AT42QT1060"                  FORCE)   

set(DIO_STREAMSPI_FEATURE                               true    CACHE BOOL "Activate Data Input/Output Stream SPI"                      FORCE)
set(DIO_SPI_GPIO_MCP23S17_FEATURE                       true    CACHE BOOL "Activate Data SPI GPIO MCP23S17"                            FORCE)
set(DIO_SPI_LCDDISPLAY_PCF8833_FEATURE                  true    CACHE BOOL "Activate Data SPI LCD Display PCF8833"                      FORCE)  
set(DIO_SPI_OLEDDISPLAY_SSD1306_FEATURE                 true    CACHE BOOL "Activate Data SPI OLED Display SSD1306"                     FORCE)
set(DIO_SPI_OLEDDISPLAY_SSD1331_FEATURE                 true    CACHE BOOL "Activate Data SPI OLED Display SSD1331"                     FORCE)
set(DIO_SPI_TFTDISPLAY_ILI9341_FEATURE                  true    CACHE BOOL "Activate Data SPI TFT Display ILI9341"                      FORCE)
set(DIO_SPI_TFTDISPLAY_ST7789_FEATURE                   true    CACHE BOOL "Activate Data SPI TFT Display ST7789"                       FORCE)
set(DIO_SPI_TOUCHSCREEN_STMPE610_FEATURE                true    CACHE BOOL "Activate Data SPI Touch Screen STMPE610"                    FORCE)


set(DIO_LEDNEOPIXELWS2812B_FEATURE                      true    CACHE BOOL "Activate Data Input/Output Led Neopixel WS2812B"            FORCE)

set(XEEPROMMEMORYMANAGER_FEATURE                        true    CACHE BOOL "Activate EEPROM Memory Manager"                             FORCE)

set(APP_FEATURE                                         true    CACHE BOOL "Activate Application modules"                               FORCE)

# --------------------------------------------------------------------
# Source code of the GEN in this Application

include("${GEN_DIRECTORY}/GEN/GEN_CMakeLists.txt") 

                     
# --------------------------------------------------------------------
# Directorys of the Application

set(APP_DIRECTORY_APPLICATION   "../Application")
list(APPEND INCLUDES_DIR ${APP_DIRECTORY_APPLICATION})

# --------------------------------------------------------------------
# Source code of the Application

list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/TestDataIO.cpp")

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/TestDataIO_WindowsPlatform.cpp")
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")  
list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/TestDataIO_LinuxPlatform.cpp")
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "STM32")
list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/TestDataIO_STM32Platform.cpp")
endif()



# --------------------------------------------------------------------
# Create proyect 

include_directories(${INCLUDES_DIR})

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

# --------------------------------------------------------------------
# Add Libraries

include("${GEN_DIRECTORY}/GEN/GEN_CMakeLists_Librarys.txt") 

