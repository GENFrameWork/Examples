# --------------------------------------------------------------------
# NotAppExample : Not Application Example  
# --------------------------------------------------------------------

 cmake_minimum_required(VERSION 3.3.0)
 project(notappexample)


 set(GEN_DIRECTORY "../../../../") 


# --------------------------------------------------------------------
# Compile Selection
 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Platform-Compiler.txt") 


 option(DEBUG_FEATURE                                       "Activate Debug mode"                                        true ) 
 option(XTRACE_FEATURE                                      "Activate XTrace"                                            true )
 option(XMEMORY_CONTROL_FEATURE                             "Activate XMemory Control"                                   true )

 option(XSLEEP_FEATURE                                      "Activate Sleep functions"                                   true )                                    

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

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Libraries.txt") 

