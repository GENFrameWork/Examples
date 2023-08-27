# --------------------------------------------------------------------
# UI_Options : Example of graphics: User Interface example. 
# GEN FrameWork
# --------------------------------------------------------------------

 cmake_minimum_required(VERSION 3.6.0)
 project(ui_options)


 set(GEN_DIRECTORY "../../../../") 

#set(ANDROID_NDK_ROOT "C:/Users/sirgraham/AppData/Local/Android/Sdk/ndk/21.0.6113669")
#set(ANDROID_NDK_ROOT  "C:/Users/sirgraham/AppData/Local/Android/Sdk/ndk/21.3.6528147")
 set(ANDROID_NDK_ROOT "/mnt/GENFrameWork/ThirdPartyLibraries/android-ndk-r21b")
#set(ANDROID_NDK_ROOT "/mnt/AndroidSDK")


# --------------------------------------------------------------------
# Activate features/Defines

 option(DEBUG_FEATURE                                       "Activate Debug mode"                                       true )
 option(XTRACE_FEATURE                                      "Activate XTrace"                                           true )
 option(XMEMORY_CONTROL_FEATURE                             "Activate XMemory Control"                                  true )

 option(LINUX_X11_FEATURE                                   "Activate Linux X11"                                        true )

 option(USERINTERFACE_FEATURE                               "Activate User Interace"                                    true )
#option(USERINTERFACE_DEBUG_FEATURE                         "Activate Debug User Interace"                              true )
        
 option(APP_FEATURE                                         "Activate Application modules"                              true )
 option(APP_LOG_FEATURE                                     "Activate Application Log"                                  true )
 option(APP_GRAPHICS_FEATURE                                "Activate Application Graphics"                             true )

 option(APP_CFG_GENERAL_FEATURE                             "Activate Application CFG General"                          true )
 option(APP_CFG_LOG_FEATURE                                 "Activate Application CFG LOG"                              true )

 option(GRP_FEATURE                                         "Activate Graphics"                                         true )
 option(GRP_FILE_FEATURE                                    "Activate Graphics File"                                    true )
 option(GRP_VIDEO_FILE_FEATURE                              "Graphics Video File"                                       true )
 option(GRP_VIDEO_FILE_AVI_FEATURE                          "Graphics Video File AVI"                                   true )
 option(GRP_2D_FEATURE                                      "Activate Graphics 2D"                                      true )

 option(INP_FEATURE                                         "Activate Inputs"                                           true )


# --------------------------------------------------------------------
# Config Application Macro

 set(APP_CFG_UI_OPTIONS "-DAPP_CFG=UI_OPTIONS_CFG::GetInstance()")
 add_definitions(${APP_CFG_UI_OPTIONS})


# --------------------------------------------------------------------
# Main CMakeList of GEN

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Main.txt") 
                   
                   
# --------------------------------------------------------------------
# Directorys of the Application

 set(APP_DIRECTORY_APPLICATION   "../Application")
 list(APPEND INCLUDES_DIR ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application

 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/UI_Options.cpp")
 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/UI_Options_CFG.cpp")


# --------------------------------------------------------------------
# Create proyect 

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_CreateProject.txt")


# --------------------------------------------------------------------
# Add Libraries

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Libraries.txt") 
