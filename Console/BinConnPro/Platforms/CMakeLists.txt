# --------------------------------------------------------------------
# BinConnPro : Example of console: Binary protocol example
# GEN FrameWork
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.14.0)
project(binconnpro)


set(GEN_DIRECTORY "../../../../") 


# --------------------------------------------------------------------
# features/Defines

option(DEBUG_FEATURE                                          "Debug mode"                                              true )
option(XTRACE_FEATURE                                         "XTrace"                                                  true )
option(XTRACE_NOINTERNET_FEATURE                              "No need for trace dependencies with Internet"            true )
option(XMEMORY_CONTROL_FEATURE                                "XMemory Control"                                         true )
                    
option(DIO_FEATURE                                            "Data Input/Output"                                       true ) 
option(DIO_CHECKCONNECTIONS_FEATURE                           "Check Connections"                                       true )
option(DIO_NETWORKTIMEPROTOCOL_FEATURE                        "Network Time Protocol"                                   true )
option(DIO_DYNDNS_FEATURE                                     "DynDNS"                                                  true )
option(DIO_SCRAPERWEB_FEATURE                                 "Scraper Web"                                             true )
    
option(DIO_PROTOCOL_FEATURE                                   "Data Input/Output Protocol"                              true )
    
option(APP_FEATURE                                            "Application modules"                                     true )
option(APP_CHECKRESOURCESHARDWARE_FEATURE                     "Application Check Resources Hardwar"                     true )
option(APP_CONSOLE_FEATURE                                    "Application Console"                                     true )
option(APP_INTERNETSERVICES_FEATURE                           "Application Internet Services"                           true )
option(APP_LOG_FEATURE                                        "Application Log"                                         true )
    
option(APP_CFG_GENERAL_FEATURE                                "Application CFG General"                                 true )  
option(APP_CFG_LOG_FEATURE                                    "Application CFG LOG"                                     true )
option(APP_CFG_INTERNETSERVICES_FEATURE                       "Application CFG Internet services"                       true )      
option(APP_CFG_CHECKRESOURCESHARDWARE_FEATURE                 "Application CFG Check Resorces HW"                       true )  
option(APP_CFG_DNSRESOLVER_FEATURE                            "Application CFG DNS "                                    true )   
option(APP_CFG_DIOLOCATION_FEATURE                            "Application CFG DIO Location"                            true )          

# --------------------------------------------------------------------
# Config Application Macro

set(APP_CFG_BINCONNPRO "-DAPP_CFG=BINCONNPRO_CFG::GetInstance()")
add_definitions(${APP_CFG_BINCONNPRO})


# --------------------------------------------------------------------
# Main CMakeList of GEN

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_Main.txt") 
                   
                   
# --------------------------------------------------------------------
# Directorys of the Application

set(APP_DIRECTORY_APPLICATION   "../Application")
list(APPEND GEN_INCLUDES_DIR_LIST ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/BinConnPro.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/BinConnPro_CFG.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/BinConnPro_ApplicationData.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/BinConnPro_ConnectionsManager.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/BinConnPro_Protocol.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/BinConnPro_Protocol_Device.cpp")


# --------------------------------------------------------------------
# Create proyect 

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_CreateProject.txt") 


# --------------------------------------------------------------------
# Add Libraries

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_Libraries.txt") 