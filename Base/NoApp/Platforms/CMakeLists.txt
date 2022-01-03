# --------------------------------------------------------------------
# noapp : Example of console GEN FrameWork 
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.3.0)
project(noapp)


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

set(DEBUG_FEATURE                                       true    CACHE BOOL "Activate Debug mode"                                        FORCE)

set(XTRACE_FEATURE                                      true    CACHE BOOL "Activate XTrace"                                            FORCE)
set(XMEMORY_CONTROL_FEATURE                             true    CACHE BOOL "Activate XMemory Control"                                   FORCE)
                                    
set(DIO_FEATURE                                         true    CACHE BOOL "Activate Data Input/Output"                                 FORCE) 
set(DIO_STREAM_FEATURE                                  true    CACHE BOOL "Activate Data Input/Output Stream"                          FORCE)
set(DIO_STREAMUART_FEATURE                              true    CACHE BOOL "Activate Data Input/Output Stream UART"                     FORCE)
set(DIO_STREAMUSB_FEATURE                               true    CACHE BOOL "Activate Data Input/Output Stream USB"                      FORCE)

#set(APP_FEATURE                                        true    CACHE BOOL "Activate Application modules"                               FORCE)

# --------------------------------------------------------------------
# Source code of the GEN in this Application

include("${GEN_DIRECTORY}/GEN/GEN_CMakeLists.txt") 

                     
# --------------------------------------------------------------------
# Directorys of the Application

set(APP_DIRECTORY_APPLICATION   "../Application")
list(APPEND INCLUDES_DIR ${APP_DIRECTORY_APPLICATION})

# --------------------------------------------------------------------
# Source code of the Application

list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/NoApp.cpp")


# --------------------------------------------------------------------
# Create proyect 

include_directories(${INCLUDES_DIR})

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

# --------------------------------------------------------------------
# Add Libraries

include("${GEN_DIRECTORY}/GEN/GEN_CMakeLists_Librarys.txt") 

