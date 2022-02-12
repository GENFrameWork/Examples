# --------------------------------------------------------------------
# Tests : Example of console GEN FrameWork
# 
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.3.0)
project(tests)

set(GEN_DIRECTORY "../../../../../GENFrameWork") 

# --------------------------------------------------------------------
# Compile Selection
include("${GEN_DIRECTORY}/GEN/GEN_CMakeLists_Compile.txt") 

# --------------------------------------------------------------------
# Warnings control
include("${GEN_DIRECTORY}/GEN/GEN_CMakeLists_Warnings.txt") 


# --------------------------------------------------------------------
# Activate features/Defines

include("${GEN_DIRECTORY}/GEN/GEN_CMakeLists_Default.txt") 


set(DEBUG_FEATURE                                       true    CACHE BOOL "Activate Debug mode"                                        FORCE)
set(XTRACE_FEATURE                                      true    CACHE BOOL "Activate XTrace"                                            FORCE)
set(XTRACE_NOINTERNET_FEATURE                           true    CACHE BOOL "Activate No need for trace dependencies with the Internet"  FORCE)                        
set(XMEMORY_CONTROL_FEATURE                             true    CACHE BOOL "Activate XMemory Control"                                   FORCE)

set(XSHAREDMEMORYMANAGER_FEATURE                        true    CACHE BOOL "Activate Shared Memory Manager"                             FORCE)
set(XPROCESSMANAGER_FEATURE                             true    CACHE BOOL "Activate Process Manager"                                   FORCE)

set(XFILE_HEX_FEATURE                                   true    CACHE BOOL "Activate XFile HEX format"                                  FORCE)  
set(XFILE_DFU_FEATURE                                   true    CACHE BOOL "Activate XFile DFU format"                                  FORCE)  
set(XFILE_RIFF_FEATURE                                  true    CACHE BOOL "Activate XFile RIFF format"                                 FORCE)  


set(HASH_SHA1_FEATURE                                   true    CACHE BOOL "Activate Hash SHA1"                                         FORCE)    
set(HASH_SHA2_FEATURE                                   true    CACHE BOOL "Activate Hash SHA2"                                         FORCE)
set(HASH_WHIRLPOOL_FEATURE                              true    CACHE BOOL "Activate Hash Whirlpool"                                    FORCE)  
                  
set(DIO_FEATURE                                         true    CACHE BOOL "Activate Data Input/Output"                                 FORCE) 
set(DIO_STREAMUART_FEATURE                              true    CACHE BOOL "Activate Data Input/Output Stream UART"                     FORCE)
set(DIO_STREAMBLUETOOTH_FEATURE                         true    CACHE BOOL "Activate Data Input/Output Stream Bluetooth"                FORCE)
set(DIO_STREAMBLUETOOTHLE_FEATURE                       true    CACHE BOOL "Activate Data Input/Output Stream Bluetooth LE"             FORCE)
set(DIO_STREAMWIFI_FEATURE                              true    CACHE BOOL "Activate Data Input/Output Stream Wifi"                     FORCE)
set(DIO_CHECKCONNECTIONS_FEATURE                        true    CACHE BOOL "Activate Check Connections"                                 FORCE)
set(DIO_NETWORKTINEPROTOCOL_FEATURE                     true    CACHE BOOL "Activate Network Time Protocol"                             FORCE)
set(DIO_DYNDNS_FEATURE                                  true    CACHE BOOL "Activate DynDNS"                                            FORCE)
set(DIO_SCRAPERWEB_FEATURE                              true    CACHE BOOL "Activate Scraper Web"                                       FORCE)
set(DIO_GPIO_FEATURE                                    true    CACHE BOOL "Activate Data Input/Output GPIO"                            FORCE)
set(DIO_STREAMI2C_FEATURE                               true    CACHE BOOL "Activate Data Input/Output Stream I2C"                      FORCE)
set(DIO_I2C_GPIO_MCP2317_FEATURE                        true    CACHE BOOL "Activate Data I2C GPIO MCP2317"                             FORCE)
set(DIO_STREAMSPI_FEATURE                               true    CACHE BOOL "Activate Data Input/Output Stream SPI"                      FORCE)
set(DIO_SPI_GPIO_MCP23S17_FEATURE                       true    CACHE BOOL "Activate Data SPI GPIO MCP23S17"                            FORCE)   
set(DIO_ATCMD_FEATURE                                   true    CACHE BOOL "Activate AT Commands"                                       FORCE)
set(DIO_WAKEONLAN_FEATURE                               true    CACHE BOOL "Activate Data Input/Output WakeON Lan"                      FORCE)
set(DIO_MPSSE_FEATURE                                   true    CACHE BOOL "Activate Data Input/Output MPSSE"                           FORCE)     
set(DIO_STREAMTLS_FEATURE                               true    CACHE BOOL "Activate Data Input/Output Stream TLS"                      FORCE)
set(DIO_ALERTS_FEATURE                                  true    CACHE BOOL "Activate Data Input/Output Alerts"                          FORCE)  
set(DIO_ONOTIFICATIONS_MANAGER_FEATURE                  true    CACHE BOOL "Activate Notifications Nanager"                             FORCE)
set(DIO_WIFIMANAGERMODE_FEATURE                         true    CACHE BOOL "Activate Data Input/Output Wifi Manager Mode"               FORCE) 
set(DIO_SNMP_FEATURE                                    true    CACHE BOOL "Activate SNMP (Simple Network Management Protocol)"         FORCE)
set(DIO_LEDNEOPIXELWS2812B_FEATURE                      true    CACHE BOOL "Activate Data Input/Output Led Neopixel WS2812B"            FORCE)
set(DIO_PCAP_FEATURE                                    true    CACHE BOOL "Activate Data Input/Output Cap"                             FORCE)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(DIO_LINUX_DBUS_FEATURE                              true    CACHE BOOL "Activate Linux DBus"                                        FORCE) 
set(DIO_LINUX_NETWORKMANAGER_FEATURE                    true    CACHE BOOL "Activate Linux Network Manager"                             FORCE)
endif()


#set(SND_FEATURE                                         true    CACHE BOOL "Activate Sound"                                             FORCE)

set(APP_FEATURE                                         true    CACHE BOOL "Activate Application modules"                               FORCE)
set(APP_CHECKRESOURCESHARDWARE_FEATURE                  true    CACHE BOOL "Activate Application Check Resources Hardwar"               FORCE)
set(APP_CONSOLE_FEATURE                                 true    CACHE BOOL "Activate Application Console"                               FORCE)
set(APP_INTERNETSERVICES_FEATURE                        true    CACHE BOOL "Activate Application Internet Services"                     FORCE)
set(APP_LOG_FEATURE                                     true    CACHE BOOL "Activate Application Log"                                   FORCE)
set(APP_ALERTS_FEATURE                                  true    CACHE BOOL "Activate Application Alerts"                                FORCE)

set(APP_CFG_GENERAL_FEATURE                             true    CACHE BOOL "Activate Application CFG General"                           FORCE)  
set(APP_CFG_LOG_FEATURE                                 true    CACHE BOOL "Activate Application CFG LOG"                               FORCE)
set(APP_CFG_INTERNETSERVICES_FEATURE                    true    CACHE BOOL "Activate Application CFG Internet services"                 FORCE)      
set(APP_CFG_DYNDNSMANAGER_FEATURE                       true    CACHE BOOL "Activate Application CFG DynDNS Manager"                    FORCE)
set(APP_CFG_CHECKRESOURCESHARDWARE_FEATURE              true    CACHE BOOL "Activate Application CFG Check Resorces HW"                 FORCE)  
set(APP_CFG_DNSRESOLVED_FEATURE                         true    CACHE BOOL "Activate Application CFG DNS Resolved"                      FORCE)  
set(APP_CFG_ALERTS_FEATURE                              true    CACHE BOOL "Activate Application CFG Alerts"                            FORCE)  





# --------------------------------------------------------------------
# Config Application Macro

set(APP_CFG_TESTS "-DAPP_CFG=TESTS_CFG::GetInstance()")
add_definitions(${APP_CFG_TESTS})


# --------------------------------------------------------------------
# Source code of the GEN in this Application

include("${GEN_DIRECTORY}/GEN/GEN_CMakeLists.txt") 
                   
                   
# --------------------------------------------------------------------
# Directorys of the Application

set(APP_DIRECTORY_APPLICATION   "../Application")
list(APPEND INCLUDES_DIR ${APP_DIRECTORY_APPLICATION})

# --------------------------------------------------------------------
# Source code of the Application

list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/Tests.cpp")
list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/Tests_CFG.cpp")


if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/Tests_WindowsPlatform.cpp")
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")  
list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/Tests_LinuxPlatform.cpp")
endif()




# --------------------------------------------------------------------
# Create proyect 

include_directories(${INCLUDES_DIR})

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

# --------------------------------------------------------------------
# Add Libraries

include("${GEN_DIRECTORY}/GEN/GEN_CMakeLists_Librarys.txt") 