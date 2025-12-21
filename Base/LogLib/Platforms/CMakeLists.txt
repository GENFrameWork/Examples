# --------------------------------------------------------------------
# LogLib : Log Library 
# GEN FrameWork
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.16.0)
project(loglib)


set(GEN_DIRECTORY "../../../../../GEN_FrameWork") 


# --------------------------------------------------------------------
# Activate features/Defines

option(DEBUG_FEATURE                                            "Debug mode"                                              ON )
option(XTRACE_FEATURE                                           "XTrace"                                                  ON )
#option(XMEMORY_CONTROL_FEATURE                                  "XMemory Control"                                         ON )
#option(XFEEDBACK_CONTROL_FEATURE                                "XFeedback Control"                                       ON )   

option(XPUBLISHER_FEATURE                                       "XPublisher"                                              ON )

option(APPMODE_LIBRARY_DINAMIC_FEATURE                          "Application Library Dinamic mode"                        ON )
    
option(LINUX_VISUALSTUDIOCODEPAGE_FEATURE                       "Linux CodePage Editor Visual Studio CP1252"              ON )   
                                
option(XLOG_FEATURE                                             "LOG File"                                                ON )  


# --------------------------------------------------------------------
# Main CMakeList of GEN

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_Main.txt") 

                     
# --------------------------------------------------------------------
# Directorys of the Application

set(APP_DIRECTORY_APPLICATION   "../Application")
list(APPEND GEN_INCLUDES_DIR_LIST ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application

#list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/AppBaseExample.cpp")
 

# --------------------------------------------------------------------
# Create proyect 

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_CreateProject.txt") 


# --------------------------------------------------------------------
# Add Libraries

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_Libraries.txt") 

