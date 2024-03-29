# --------------------------------------------------------------------
# Canvas2D : Example of graphics Canvas 2D example  
# GEN FrameWork 
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.14.0)
project(canvas2D)


set(GEN_DIRECTORY "../../../../") 


option(DEBUG_FEATURE                                          "Debug mode"                                              true )
option(XTRACE_FEATURE                                         "XTrace"                                                  true )
option(XTRACE_NOINTERNET_FEATURE                              "No need for trace dependencies with Internet"            true )
option(XTHREADCOLLECTED_FEATURE                               "Thread Collected"                                        true )
option(XMEMORY_CONTROL_FEATURE                                "XMemory Control"                                         true )

option(LINUX_X11_FEATURE                                      "Linux X11"                                               true )
        
option(APP_FEATURE                                            "Application modules"                                     true )
option(APP_LOG_FEATURE                                        "Application Log"                                         true )
option(APP_GRAPHICS_FEATURE                                   "Application Graphics"                                    true )

option(APP_CFG_GENERAL_FEATURE                                "Application CFG General"                                 true )  
option(APP_CFG_LOG_FEATURE                                    "Application CFG LOG"                                     true )

option(GRP_FEATURE                                            "Graphics"                                                true )
option(GRP_BITMAP_FILE_BMP_FEATURE                            "Graphics Bitmap File BMP"                                true )
option(GRP_BITMAP_FILE_JPG_FEATURE                            "Graphics Bitmap File JPG"                                true )
option(GRP_BITMAP_FILE_PNG_FEATURE                            "Graphics Bitmap File PNG"                                true )
option(GRP_BITMAP_FILE_TGA_FEATURE                            "Graphics Bitmap File TGA"                                true )
option(GRP_2D_FEATURE                                         "Graphics 2D"                                             true )

option(INP_FEATURE                                            "Inputs"                                                  true )

option(SND_FEATURE                                            "Sound"                                                   true )
option(SND_FILE_WAV_FEATURE                                   "Sound WAV file"                                          true )
option(SND_FILE_OGG_FEATURE                                   "Sound OGG file"                                          true )


# --------------------------------------------------------------------
# Config Application Macro

set(APP_CFG_CANVAS2D "-DAPP_CFG=CANVAS2D_CFG::GetInstance()")
add_definitions(${APP_CFG_CANVAS2D})


# --------------------------------------------------------------------
# Main CMakeList of GEN

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_Main.txt") 
                   
                   
# --------------------------------------------------------------------
# Directorys of the Application

set(APP_DIRECTORY_APPLICATION   "../Application")
list(APPEND GEN_INCLUDES_DIR_LIST ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/Canvas2D.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/Canvas2D_CFG.cpp")


# --------------------------------------------------------------------
# Create proyect 

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_CreateProject.txt")


# --------------------------------------------------------------------
# Add Libraries

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_Libraries.txt") 

