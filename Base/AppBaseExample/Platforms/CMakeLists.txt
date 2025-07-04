# --------------------------------------------------------------------
# appbaseexample : minimal base example with APP class
# GEN FrameWork
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.16.0)
project(appbaseexample)


set(GEN_DIRECTORY "../../../../../GENFrameWork") 


# --------------------------------------------------------------------
# Activate features/Defines

option(DEBUG_FEATURE                                            "Debug mode"                                                                                      ON )
option(XTRACE_FEATURE                                           "XTrace"                                                                                          ON )
option(XMEMORY_CONTROL_FEATURE                                  "XMemory Control"                                                                                 ON )
    
option(LINUX_VISUALSTUDIOCODEPAGE_FEATURE                       "Linux CodePage Editor Visual Studio CP1252"                                                      ON )   
                                
option(APPFLOW_FEATURE                                          "Application Flow modules"                                                                        ON )


# --------------------------------------------------------------------
# Main CMakeList of GEN

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_Main.txt") 

                     
# --------------------------------------------------------------------
# Directorys of the Application

set(APP_DIRECTORY_APPLICATION   "../Application")
list(APPEND GEN_INCLUDES_DIR_LIST ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/AppBaseExample.cpp")
 

# --------------------------------------------------------------------
# Create proyect 

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_CreateProject.txt") 


# --------------------------------------------------------------------
# Add Libraries

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_Libraries.txt") 

