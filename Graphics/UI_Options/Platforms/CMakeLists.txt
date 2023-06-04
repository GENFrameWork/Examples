# --------------------------------------------------------------------
# UI_Options : Example of GEN FrameWork graphics(User Interface example 
# --------------------------------------------------------------------

 cmake_minimum_required(VERSION 3.3.0)
 project(ui_options)


 set(GEN_DIRECTORY "../../../../") 


#set(ANDROID_NDK_ROOT "C:/Users/sirgraham/AppData/Local/Android/Sdk/ndk/21.0.6113669")
#set(ANDROID_NDK_ROOT  "C:/Users/sirgraham/AppData/Local/Android/Sdk/ndk/21.3.6528147")
set(ANDROID_NDK_ROOT "/mnt/GENFrameWork/ThirdPartyLibraries/android-ndk-r21b")
#set(ANDROID_NDK_ROOT "/mnt/AndroidSDK")


# --------------------------------------------------------------------
# Compile Selection

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Platform-Compiler.txt") 


# --------------------------------------------------------------------
# Activate features/Defines


 option(DEBUG_FEATURE                                       "Activate Debug mode"                                        true )
 option(XTRACE_FEATURE                                      "Activate XTrace"                                            true )
 option(XMEMORY_CONTROL_FEATURE                             "Activate XMemory Control"                                   true )

 option(LINUX_X11_FEATURE                                   "Activate Linux X11"                                         true )

 option(USERINTERFACE_FEATURE                               "Activate User Interace"                                     true )
#option(USERINTERFACE_DEBUG_FEATURE                         "Activate Debug User Interace"                               true )
        
 option(APP_FEATURE                                         "Activate Application modules"                               true )
 option(APP_LOG_FEATURE                                     "Activate Application Log"                                   true )
 option(APP_GRAPHICS_FEATURE                                "Activate Application Graphics"                              true )

 option(APP_CFG_GENERAL_FEATURE                             "Activate Application CFG General"                           true )
 option(APP_CFG_LOG_FEATURE                                 "Activate Application CFG LOG"                               true )

 option(GRP_FEATURE                                         "Activate Graphics"                                          true )
 option(GRP_FILE_FEATURE                                    "Activate Graphics File"                                     true )
 option(GRP_2D_FEATURE                                      "Activate Graphics 2D"                                       true )

 option(INP_FEATURE                                         "Activate Inputs"                                            true )



# --------------------------------------------------------------------
# Config Application Macro

 set(APP_CFG_UI_OPTIONS "-DAPP_CFG=UI_OPTIONS_CFG::GetInstance()")
 add_definitions(${APP_CFG_UI_OPTIONS})


# --------------------------------------------------------------------
# Source code of the GEN in this Application

include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists.txt") 
                   
                   
# --------------------------------------------------------------------
# Directorys of the Application

set(APP_DIRECTORY_APPLICATION   "../Application")
list(APPEND INCLUDES_DIR ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application

list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/UI_Options.cpp")
list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/UI_Options_CFG.cpp")


# --------------------------------------------------------------------
# Warnings control

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Warnings.txt") 


# --------------------------------------------------------------------
# Create proyect 

 include_directories(${INCLUDES_DIR})

 add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})


# --------------------------------------------------------------------
# Add Libraries

include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Libraries.txt") 
