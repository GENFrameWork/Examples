# --------------------------------------------------------------------
# Canvas2D : Example of graphics: Canvas 2D example  
# GEN FrameWork 
# --------------------------------------------------------------------

 cmake_minimum_required(VERSION 3.14.0)
 project(canvas2D)


 set(GEN_DIRECTORY "../../../../") 

#set(ANDROID_NDK_ROOT "${GEN_DIRECTORY}/ThirdPartyLibraries/android-ndk")
#set(ANDROID_NDK_ROOT "/mnt/GENFrameWork/ThirdPartyLibraries/android-ndk-r21e_linux")
#set(ANDROID_NDK_ROOT "${GEN_DIRECTORY}/ThirdPartyLibraries/android-ndk-r23b")
 set(ANDROID_NDK_ROOT "C:/Microsoft/AndroidNDK/android-ndk-r21e")


# --------------------------------------------------------------------
# Activate features/Defines

 option(DEBUG_FEATURE                                       "Activate Debug mode"                                       true )
 option(XTRACE_FEATURE                                      "Activate XTrace"                                           true )
 option(XTRACE_NOINTERNET_FEATURE                           "No need for trace dependencies with Internet"              true )
 option(XMEMORY_CONTROL_FEATURE                             "Activate XMemory Control"                                  true )

 option(LINUX_X11_FEATURE                                   "Activate Linux X11"                                        true )
        
 option(APP_FEATURE                                         "Activate Application modules"                              true )
 option(APP_LOG_FEATURE                                     "Activate Application Log"                                  true )
 option(APP_GRAPHICS_FEATURE                                "Activate Application Graphics"                             true )

 option(APP_CFG_GENERAL_FEATURE                             "Activate Application CFG General"                          true )  
 option(APP_CFG_LOG_FEATURE                                 "Activate Application CFG LOG"                              true )

 option(GRP_FEATURE                                         "Activate Graphics"                                         true )
 option(GRP_FILE_FEATURE                                    "Activate Graphics File"                                    true )
 option(GRP_2D_FEATURE                                      "Activate Graphics 2D"                                      true )

 option(INP_FEATURE                                         "Activate Inputs"                                           true )


# --------------------------------------------------------------------
# Config Application Macro

 set(APP_CFG_CANVAS2D "-DAPP_CFG=CANVAS2D_CFG::GetInstance()")
 add_definitions(${APP_CFG_CANVAS2D})


# --------------------------------------------------------------------
# Main CMakeList of GEN

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Main.txt") 
                   
                   
# --------------------------------------------------------------------
# Directorys of the Application

 set(APP_DIRECTORY_APPLICATION   "../Application")
 list(APPEND INCLUDES_DIR ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application

 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/Canvas2D.cpp")
 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/Canvas2D_CFG.cpp")


# --------------------------------------------------------------------
# Create proyect 

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_CreateProject.txt")


# --------------------------------------------------------------------
# Add Libraries

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Libraries.txt") 

