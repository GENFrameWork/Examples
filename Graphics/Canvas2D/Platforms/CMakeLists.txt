# --------------------------------------------------------------------
# Tests : Example of console GEN FrameWork
# 
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.7.0)
project(canvas2D)


set(GEN_DIRECTORY "../../../../../GENFrameWork") 

#set(ANDROID_NDK_ROOT "${GEN_DIRECTORY}/ThirdPartyLibraries/android-ndk")
#set(ANDROID_NDK_ROOT "/mnt/GENFrameWork/ThirdPartyLibraries/android-ndk-r21e_linux")
#set(ANDROID_NDK_ROOT "C:/Users/sirgraham/AppData/Local/Android/Sdk/ndk/21.3.6528147")

# --------------------------------------------------------------------
# Compile Selection
include("${GEN_DIRECTORY}/GEN/GEN_CMakeLists_Compile.txt") 

# --------------------------------------------------------------------
# Warnings control
include("${GEN_DIRECTORY}/GEN/GEN_CMakeLists_Warnings.txt") 


# --------------------------------------------------------------------
# Activate features/Defines

include("${GEN_DIRECTORY}/GEN/GEN_CMakeLists_Default.txt") 


set(DEBUG_FEATURE                                       true    CACHE BOOL "Activate Debug mode"                            FORCE)

set(XTRACE_FEATURE                                      true    CACHE BOOL "Activate XTrace"                                FORCE)
set(XMEMORY_CONTROL_FEATURE                             true    CACHE BOOL "Activate XMemory Control"                       FORCE)

#set(LINUX_X11_FEATURE                                   true    CACHE BOOL "Activate Linux X11"                             FORCE)
        
set(APP_FEATURE                                         true    CACHE BOOL "Activate Application modules"                   FORCE)
set(APP_LOG_FEATURE                                     true    CACHE BOOL "Activate Application Log"                       FORCE)
set(APP_GRAPHICS_FEATURE                                true    CACHE BOOL "Activate Application Graphics"                  FORCE)

set(APP_CFG_GENERAL_FEATURE                             true    CACHE BOOL "Activate Application CFG General"               FORCE)  
set(APP_CFG_LOG_FEATURE                                 true    CACHE BOOL "Activate Application CFG LOG"                   FORCE)

set(GRP_FEATURE                                         true    CACHE BOOL "Activate Graphics"                              FORCE)
set(GRP_FILE_FEATURE                                    true    CACHE BOOL "Activate Graphics File"                         FORCE)
set(GRP_2D_FEATURE                                      true    CACHE BOOL "Activate Graphics 2D"                           FORCE)

set(INP_FEATURE                                         true    CACHE BOOL "Activate Inputs"                                FORCE)



# --------------------------------------------------------------------
# Config Application Macro

set(APP_CFG_CANVAS2D "-DAPP_CFG=CANVAS2D_CFG::GetInstance()")
add_definitions(${APP_CFG_CANVAS2D})


# --------------------------------------------------------------------
# Source code of the GEN in this Application

include("${GEN_DIRECTORY}/GEN/GEN_CMakeLists.txt") 
                   
                   
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

include_directories(${INCLUDES_DIR})

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

# --------------------------------------------------------------------
# Add Libraries

include("${GEN_DIRECTORY}/GEN/GEN_CMakeLists_Librarys.txt") 