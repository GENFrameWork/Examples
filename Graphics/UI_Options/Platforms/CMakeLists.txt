# --------------------------------------------------------------------
# UI_Options : Example of graphics: User Interface example. 
# GEN FrameWork
# --------------------------------------------------------------------

 cmake_minimum_required(VERSION 3.14.0)
 project(ui_options)


 set(GEN_DIRECTORY "../../../../") 

#set(ANDROID_NDK_ROOT "C:/Users/sirgraham/AppData/Local/Android/Sdk/ndk/21.0.6113669")
#set(ANDROID_NDK_ROOT  "C:/Users/sirgraham/AppData/Local/Android/Sdk/ndk/21.3.6528147")
 set(ANDROID_NDK_ROOT "/mnt/GENFrameWork/ThirdPartyLibraries/android-ndk-r21b")
#set(ANDROID_NDK_ROOT "/mnt/AndroidSDK")


# --------------------------------------------------------------------
# features/Defines

 option(DEBUG_FEATURE                                       "Debug mode"                                                true )
 option(XTRACE_FEATURE                                      "XTrace"                                                    true )
 option(XTRACE_NOINTERNET_FEATURE                           "No need for trace dependencies with Internet"              true )
 option(XTHREADCOLLECTED_FEATURE                            "Thread Collected"                                          true )
 option(XMEMORY_CONTROL_FEATURE                             "XMemory Control"                                           true )

 option(LINUX_X11_FEATURE                                   "Linux X11"                                                 true )

 option(USERINTERFACE_FEATURE                               "User Interace"                                             true )
#option(USERINTERFACE_DEBUG_FEATURE                         "Debug User Interace"                                       true )
        
 option(APP_FEATURE                                         "Application modules"                                       true )
 option(APP_LOG_FEATURE                                     "Application Log"                                           true )
 option(APP_GRAPHICS_FEATURE                                "Application Graphics"                                      true )

 option(APP_CFG_GENERAL_FEATURE                             "Application CFG General"                                   true )
 option(APP_CFG_LOG_FEATURE                                 "Application CFG LOG"                                       true )

 option(GRP_FEATURE                                         "Graphics"                                                  true )
 option(GRP_BITMAP_FILE_FEATURE                             "Graphics Files Bitmap Type"                                true )
 option(GRP_VIDEO_FILE_FEATURE                              "Graphics Video File"                                       true )
 option(GRP_VIDEO_FILE_AVI_FEATURE                          "Graphics Video File AVI"                                   true )
 option(GRP_2D_FEATURE                                      "Graphics 2D"                                               true )

 option(INP_FEATURE                                         "Inputs"                                                    true )


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
 list(APPEND GEN_INCLUDES_DIR_LIST ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application

 list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UI_Options.cpp")
 list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UI_Options_CFG.cpp")


# --------------------------------------------------------------------
# Create proyect 

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_CreateProject.txt")


# --------------------------------------------------------------------
# Add Libraries

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Libraries.txt") 
