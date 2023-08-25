# --------------------------------------------------------------------
# Canvas2DDisplay : Example of console (Canvas minimal app)
# GEN FrameWork 
# --------------------------------------------------------------------

 cmake_minimum_required(VERSION 3.6.0)
 project(canvas2ddisplay)


 set(GEN_DIRECTORY "../../../../") 


# --------------------------------------------------------------------
# Compile Selection

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Platform-Compiler.txt") 


# --------------------------------------------------------------------
# Activate features/Defines

 option(DEBUG_FEATURE                                       "Activate Debug mode"                                        true )
 option(XTRACE_FEATURE                                      "Activate XTrace"                                            true )
 option(XMEMORY_CONTROL_FEATURE                             "Activate XMemory Control"                                   true )
                                    
 option(DIO_FEATURE                                         "Activate Data Input/Output"                                 true ) 
 option(DIO_STREAM_FEATURE                                  "Activate Data Input/Output Stream"                          true )
 option(DIO_STREAMUART_FEATURE                              "Activate Data Input/Output Stream UART"                     true )
 option(DIO_STREAMUSB_FEATURE                               "Activate Data Input/Output Stream USB"                      true )

 option(APP_FEATURE                                         "Activate Application modules"                               true )


# --------------------------------------------------------------------
# Main CMakeList of GEN

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Main.txt") 

                     
# --------------------------------------------------------------------
# Directorys of the Application

 set(APP_DIRECTORY_APPLICATION   "../Application")
 list(APPEND INCLUDES_DIR ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application

 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/Canvas2DDisplay.cpp")


# --------------------------------------------------------------------
# Warnings control
 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Warnings.txt") 
 
 
# --------------------------------------------------------------------
# Create proyect 

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_CreateProject.txt") 


# --------------------------------------------------------------------
# Add Libraries

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Libraries.txt") 

