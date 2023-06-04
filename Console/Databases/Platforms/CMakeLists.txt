# --------------------------------------------------------------------
# DataBases : Example of console GEN FrameWork (Databases connector example) 
# --------------------------------------------------------------------

 cmake_minimum_required(VERSION 3.3.0)
 project(databases)


 set(GEN_DIRECTORY "../../../../") 


# --------------------------------------------------------------------
# Compile Selection
 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Platform-Compiler.txt") 


 option(DEBUG_FEATURE                                       "Activate Debug mode"                                        true )
 option(XTRACE_FEATURE                                      "Activate XTrace"                                            true )
 option(XMEMORY_CONTROL_FEATURE                             "Activate XMemory Control"                                   true )
                  
 option(APP_FEATURE                                         "Activate Application modules"                               true )
 option(APP_CONSOLE_FEATURE                                 "Activate Application Console"                               true )
 option(APP_LOG_FEATURE                                     "Activate Application Log"                                   true )

 option(APP_CFG_GENERAL_FEATURE                             "Activate Application CFG General"                           true )
 option(APP_CFG_LOG_FEATURE                                 "Activate Application CFG LOG"                               true )

 option(DATABASES_SQL_FEATURE                               "Activate DataBases SQL"                                     true )
 option(DATABASES_SQL_SQLITE_FEATURE                        "Activate DataBases SQLite"                                  true )
 option(DATABASES_SQL_MYSQL_FEATURE                         "Activate DataBases MySQL"                                   true )
 option(DATABASES_SQL_POSTGRESQL_FEATURE                    "Activate DataBases PostgreSQL"                              true )


# --------------------------------------------------------------------
# Config Application Macro

 set(APP_CFG_DATABASES "-DAPP_CFG=DATABASES_CFG::GetInstance()")
 add_definitions(${APP_CFG_DATABASES})


# --------------------------------------------------------------------
# Source code of the GEN in this Application

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists.txt") 
                   
                   
# --------------------------------------------------------------------
# Directorys of the Application

 set(APP_DIRECTORY_APPLICATION   "../Application")
 list(APPEND INCLUDES_DIR ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application

 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/Databases.cpp")
 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/Databases_CFG.cpp")


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
 