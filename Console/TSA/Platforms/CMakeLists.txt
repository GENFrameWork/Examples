# --------------------------------------------------------------------
# TSA : Example of console: Scripts example
# GEN FrameWork
# --------------------------------------------------------------------

 cmake_minimum_required(VERSION 3.6.0)
 project(tsa)


 set(GEN_DIRECTORY "../../../../") 


# --------------------------------------------------------------------
# Compile Selection

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Platform-Compiler.txt") 


# --------------------------------------------------------------------
# Activate features/Defines

 option(DEBUG_FEATURE                                       "Activate Debug mode"                                       true )
 option(XTRACE_FEATURE                                      "Activate XTrace"                                           true )
 option(XMEMORY_CONTROL_FEATURE                             "Activate XMemory Control"                                  true )
                  
 option(APP_FEATURE                                         "Activate Application modules"                              true )
 option(APP_CONSOLE_FEATURE                                 "Activate Application Console"                              true )
 option(APP_LOG_FEATURE                                     "Activate Application Log"                                  true )

 option(APP_CFG_GENERAL_FEATURE                             "Activate Application CFG General"                          true )
 option(APP_CFG_LOG_FEATURE                                 "Activate Application CFG LOG"                              true )
 
 option(SCRIPT_FEATURE                                      "Activate Scripts"                                          true )
 option(SCRIPT_G_FEATURE                                    "Activate Script G Language"                                true )
 option(SCRIPT_LUA_FEATURE                                  "Activate Script LUA Language"                              true )
 option(SCRIPT_JAVASCRIPT_FEATURE                           "Activate Script Javascript Language"                       true )
 option(SCRIPT_LIB_SYSTEM_FEATURE                           "Script Lib System"                                         true )    
 option(SCRIPT_LIB_PROCESS_FEATURE                          "Script Lib Process"                                        true )    
 option(SCRIPT_LIB_LOG_FEATURE                              "Script Lib Log"                                            true )    
 option(SCRIPT_LIB_CONSOLE_FEATURE                          "Script Lib Console"                                        true ) 
 option(SCRIPT_LIB_WINDOW_FEATURE                           "Script Lib Window"                                         true ) 
 option(SCRIPT_LIB_INPUTSIMULATE_FEATURE                    "Script Lib Input Simulated"                                true )    


# --------------------------------------------------------------------
# Config Application Macro

 set(APP_CFG_SCRIPTS "-DAPP_CFG=TSA_CFG::GetInstance()")
 add_definitions(${APP_CFG_SCRIPTS})


# --------------------------------------------------------------------
# Main CMakeList of GEN

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Main.txt") 
                   
                   
# --------------------------------------------------------------------
# Directorys of the Application

 set(APP_DIRECTORY_APPLICATION   "../Application")
 list(APPEND INCLUDES_DIR ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application

 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/TSA.cpp")
 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/TSA_CFG.cpp")


# --------------------------------------------------------------------
# Warnings control

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Warnings.txt") 


# --------------------------------------------------------------------
# Create proyect 

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_CreateProject.txt") 


# --------------------------------------------------------------------
# Add Libraries

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Libraries.txt") 
