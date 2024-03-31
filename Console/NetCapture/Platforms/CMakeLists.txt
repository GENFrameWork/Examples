# --------------------------------------------------------------------
# NetCapture : Example of console of net capture
# GEN FrameWork
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.14.0)
project(netcapture)


set(GEN_DIRECTORY "../../../../") 


# --------------------------------------------------------------------
# Activate features/Defines

option(DEBUG_FEATURE                                            "Debug mode"                                              true )
option(XTRACE_FEATURE                                           "XTrace"                                                  true )
option(XTRACE_NOINTERNET_FEATURE                                "No need for trace dependencies with Internet"            true )                  
option(XMEMORY_CONTROL_FEATURE                                  "XMemory Control"                                         true )
                 
option(APP_FEATURE                                              "Application modules"                                     true )
option(APP_CONSOLE_FEATURE                                      "Application Console"                                     true )
option(APP_LOG_FEATURE                                          "Application Log"                                         true )

option(APP_CFG_GENERAL_FEATURE                                  "Application CFG General"                                 true )
option(APP_CFG_LOG_FEATURE                                      "Application CFG LOG"                                     true )

option(DIO_PCAP_FEATURE                                         "PCap Library"                                            true )
 

# --------------------------------------------------------------------
# Config Application Macro

set(APP_CFG_SCRIPTS "-DAPP_CFG=NETCAPTURE_CFG::GetInstance()")
add_definitions(${APP_CFG_SCRIPTS})


# --------------------------------------------------------------------
# Main CMakeList of GEN

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_Main.txt")
                   

# --------------------------------------------------------------------
# Directorys of the Application
       
set(APP_DIRECTORY_APPLICATION   "../Application")
list(APPEND GEN_INCLUDES_DIR_LIST ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/NetCapture.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/NetCapture_CFG.cpp")
 

# --------------------------------------------------------------------
# Create proyect 

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_CreateProject.txt") 


# --------------------------------------------------------------------
# Add Libraries

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_Libraries.txt") 
