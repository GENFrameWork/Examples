# --------------------------------------------------------------------
# Tests : Example of console GEN FrameWork
# 
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.3.0)
project(scripts)


set(GEN_DIRECTORY "../../../../../GENFrameWork") 

# --------------------------------------------------------------------
# Compile Selection
include("${GEN_DIRECTORY}/GEN/GEN_CMakeLists_Compile.txt") 

# --------------------------------------------------------------------
# Warnings control
include("${GEN_DIRECTORY}/GEN/GEN_CMakeLists_Warnings.txt") 


# --------------------------------------------------------------------
# Activate features/Defines

include("${GEN_DIRECTORY}/GEN/GEN_CMakeLists_Default.txt") 


set(DEBUG_FEATURE                           true    CACHE BOOL "Activate Debug mode"                            FORCE)

set(XTRACE_FEATURE                          true    CACHE BOOL "Activate XTrace"                                FORCE)
set(XMEMORY_CONTROL_FEATURE                 true    CACHE BOOL "Activate XMemory Control"                       FORCE)
                  
set(APP_FEATURE                             true    CACHE BOOL "Activate Application modules"                   FORCE)
set(APP_CONSOLE_FEATURE                     true    CACHE BOOL "Activate Application Console"                   FORCE)
set(APP_LOG_FEATURE                         true    CACHE BOOL "Activate Application Log"                       FORCE)

set(APP_CFG_GENERAL_FEATURE                 true    CACHE BOOL "Activate Application CFG General"               FORCE)  
set(APP_CFG_LOG_FEATURE                     true    CACHE BOOL "Activate Application CFG LOG"                   FORCE)

set(SCRIPT_FEATURE                          true    CACHE BOOL "Activate Scripts"                               FORCE)
set(SCRIPT_LUA_FEATURE                      true    CACHE BOOL "Activate Script LUA Language"                   FORCE)
set(SCRIPT_JAVASCRIPT_FEATURE               true    CACHE BOOL "Activate Script Javascript Language"            FORCE)


# --------------------------------------------------------------------
# Config Application Macro

set(APP_CFG_SCRIPTS "-DAPP_CFG=SCRIPTS_CFG::GetInstance()")
add_definitions(${APP_CFG_SCRIPTS})


# --------------------------------------------------------------------
# Source code of the GEN in this Application

include("${GEN_DIRECTORY}/GEN/GEN_CMakeLists.txt") 
                   
                   
# --------------------------------------------------------------------
# Directorys of the Application

set(APP_DIRECTORY_APPLICATION   "../Application")
list(APPEND INCLUDES_DIR ${APP_DIRECTORY_APPLICATION})

# --------------------------------------------------------------------
# Source code of the Application

list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/Scripts.cpp")
list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/Scripts_CFG.cpp")


# --------------------------------------------------------------------
# Create proyect 

include_directories(${INCLUDES_DIR})

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

# --------------------------------------------------------------------
# Add Libraries

include("${GEN_DIRECTORY}/GEN/GEN_CMakeLists_Librarys.txt") 