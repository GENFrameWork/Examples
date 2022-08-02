# --------------------------------------------------------------------
# NotAppExample : Not Application Example  
# --------------------------------------------------------------------

 cmake_minimum_required(VERSION 3.3.0)
 project(notappexample)


 set(GEN_DIRECTORY "../../../../") 

# --------------------------------------------------------------------
# Compile Selection
 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Compile.txt") 


# --------------------------------------------------------------------
# Activate features/Defines

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Default.txt") 

 set(DEBUG_FEATURE                                       true    CACHE BOOL "Activate Debug mode"                                        FORCE) 
 set(XTRACE_FEATURE                                      true    CACHE BOOL "Activate XTrace"                                            FORCE)
 set(XMEMORY_CONTROL_FEATURE                             true    CACHE BOOL "Activate XMemory Control"                                   FORCE)

 set(XSLEEP_FEATURE                                      true    CACHE BOOL "Activate Sleep functions"                                   FORCE)                                    

# --------------------------------------------------------------------
# Source code of the GEN in this Application

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists.txt") 
                     
# --------------------------------------------------------------------
# Directorys of the Application

 set(APP_DIRECTORY_APPLICATION   "../Application")
 list(APPEND INCLUDES_DIR ${APP_DIRECTORY_APPLICATION})

# --------------------------------------------------------------------
# Source code of the Application

 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/NotAppExample.cpp")
 
# --------------------------------------------------------------------
# Warnings control
 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Warnings.txt") 


# --------------------------------------------------------------------
# Create proyect 

 include_directories(${INCLUDES_DIR})

 add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

# --------------------------------------------------------------------
# Add Libraries

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Librarys.txt") 

