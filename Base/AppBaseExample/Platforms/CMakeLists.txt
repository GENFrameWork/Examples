# --------------------------------------------------------------------
# appbaseexample : minimal base example with APP class
# GEN FrameWork
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.14.0)
project(appbaseexample)


set(GEN_DIRECTORY "../../../../../GENFrameWork") 


# --------------------------------------------------------------------
# Activate features/Defines

option(DEBUG_FEATURE                                          "Activate Debug mode"                                     ON )
option(XTRACE_FEATURE                                         "Activate XTrace"                                         ON )
option(XMEMORY_CONTROL_FEATURE                                "Activate XMemory Control"                                ON )
    
option(LINUX_VISUALSTUDIOCODEPAGE_FEATURE                     "Activate Linux CodePage Editor Visual Studio CP1252"     ON )   
                                
option(APP_FEATURE                                            "Activate Application modules"                            ON )


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

