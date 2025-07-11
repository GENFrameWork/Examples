# --------------------------------------------------------------------
# ScriptsExample : Example of console of Scripts
# GEN FrameWork
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.16.0)
project(scriptsexample)

set(GEN_DIRECTORY "../../../../") 


# --------------------------------------------------------------------
# Activate features/Defines

option(DEBUG_FEATURE                                            "Activate Debug mode"                                     ON )
option(XTRACE_FEATURE                                           "Activate XTrace"                                         ON )
option(XTRACE_NOINTERNET_FEATURE                                "No need for trace dependencies with Internet"            ON )
option(XMEMORY_CONTROL_FEATURE                                  "Activate XMemory Control"                                ON )
            
option(DIO_FEATURE                                              "Input/Output"                                            ON )
option(DIO_PUBLICINTERNETIP_FEATURE                             "Public Internet IP"                                      ON )

option(APPFLOW_FEATURE                                          "Application Flow modules"                                ON )
option(APPFLOW_EXTENDED_FEATURE                                 "Application Flow Extended"                               ON )  
option(APPFLOW_EXTENDED_APPLICATIONHEADER_FEATURE               "Application Flow Extended Aplication Header"             ON )  
option(APPFLOW_EXTENDED_APPLICATIONSTATUS_FEATURE               "Application Flow Extended Aplication Status"             ON )  
option(APPFLOW_CONSOLE_FEATURE                                  "Application Flow Console"                                ON )
option(APPFLOW_LOG_FEATURE                                      "Application Flow Log"                                    ON )
                                                                             
option(APPFLOW_CFG_GENERAL_FEATURE                              "Application Flow CFG General"                            ON )
option(APPFLOW_CFG_LOG_FEATURE                                  "Application Flow CFG LOG"                                ON )
option(APPFLOW_CFG_SCRIPTS_FEATURE                              "Application Flow Scripts List"                           ON )  

option(LINUX_X11_FEATURE                                        "Linux X11"                                               ON )
    
option(SCRIPT_FEATURE                                           "Activate Scripts"                                        ON )
option(SCRIPT_G_FEATURE                                         "Activate Script G Language"                              ON )
option(SCRIPT_LUA_FEATURE                                       "Activate Script LUA Language"                            ON )
option(SCRIPT_JAVASCRIPT_FEATURE                                "Activate Script Javascript Language"                     ON )
option(SCRIPT_CACHE_FEATURE                                     "Activate Script Cache"                                   ON )
option(SCRIPT_LIB_SYSTEM_FEATURE                                "Script Lib System"                                       ON )    
option(SCRIPT_LIB_PROCESS_FEATURE                               "Script Lib Process"                                      ON )    
option(SCRIPT_LIB_LOG_FEATURE                                   "Script Lib Log"                                          ON )    
option(SCRIPT_LIB_CONSOLE_FEATURE                               "Script Lib Console"                                      ON ) 
option(SCRIPT_LIB_CFG_FEATURE                                   "Script Lib Config File"                                  ON )          
option(SCRIPT_LIB_WINDOW_FEATURE                                "Script Lib Window"                                       ON ) 
option(SCRIPT_LIB_INPUTSIMULATE_FEATURE                         "Script Lib Input Simulated"                              ON )   
option(SCRIPT_LIB_DEVTEST_FEATURE                               "Script Lib Developed Test Funcions"                      ON )    

option(DIO_FEATURE                                              "Input/Output"                                            ON )


# --------------------------------------------------------------------
# Config Application Macro

set(APP_CFG_SCRIPTS "-DAPPFLOW_CFG=SCRIPTSEXAMPLE_CFG::GetInstance()")
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

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/ScriptsExample.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/ScriptsExample_CFG.cpp")


# --------------------------------------------------------------------
# Create proyect 

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_CreateProject.txt") 


# --------------------------------------------------------------------
# Add Libraries

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_Libraries.txt") 
