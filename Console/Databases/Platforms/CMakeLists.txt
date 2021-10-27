# --------------------------------------------------------------------
# Tests : Example of console GEN FrameWork
# 
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.3.0)
project(databases)


set(GEN_DIRECTORY "../../../../../GENFrameWork") 

# --------------------------------------------------------------------
# Activate features/Defines

include("${GEN_DIRECTORY}/GEN/GEN_CMakeLists_Default.txt") 


set(DEBUG_FEATURE                                       true    CACHE BOOL "Activate Debug mode"                                        FORCE)

set(XTRACE_FEATURE                                      true    CACHE BOOL "Activate XTrace"                                            FORCE)
set(XMEMORY_CONTROL_FEATURE                             true    CACHE BOOL "Activate XMemory Control"                                   FORCE)
                  
set(APP_FEATURE                                         true    CACHE BOOL "Activate Application modules"                               FORCE)
set(APP_CONSOLE_FEATURE                                 true    CACHE BOOL "Activate Application Console"                               FORCE)
set(APP_LOG_FEATURE                                     true    CACHE BOOL "Activate Application Log"                                   FORCE)

set(APP_CFG_GENERAL_FEATURE                             true    CACHE BOOL "Activate Application CFG General"                           FORCE)  
set(APP_CFG_LOG_FEATURE                                 true    CACHE BOOL "Activate Application CFG LOG"                               FORCE)

set(DATABASES_SQL_FEATURE                               true    CACHE BOOL "Activate DataBases SQL"                                     FORCE)
set(DATABASES_SQL_SQLITE_FEATURE                        true    CACHE BOOL "Activate DataBases SQLite"                                  FORCE)
set(DATABASES_SQL_MYSQL_FEATURE                         true    CACHE BOOL "Activate DataBases MySQL"                                   FORCE)
set(DATABASES_SQL_POSTGRESQL_FEATURE                    true    CACHE BOOL "Activate DataBases PostgreSQL"                              FORCE)



# --------------------------------------------------------------------
# Config Application Macro

set(APP_CFG_DATABASES "-DAPP_CFG=DATABASES_CFG::GetInstance()")
add_definitions(${APP_CFG_DATABASES})


# --------------------------------------------------------------------
# Source code of the GEN in this Application

include("${GEN_DIRECTORY}/GEN/GEN_CMakeLists.txt") 
                   
                   
# --------------------------------------------------------------------
# Directorys of the Application

set(APP_DIRECTORY_APPLICATION   "../Application")
list(APPEND INCLUDES_DIR ${APP_DIRECTORY_APPLICATION})

# --------------------------------------------------------------------
# Source code of the Application

list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/Databases.cpp")
list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/Databases_CFG.cpp")


# --------------------------------------------------------------------
# Create proyect 

include_directories(${INCLUDES_DIR})

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

# --------------------------------------------------------------------
# Add Libraries

include("${GEN_DIRECTORY}/GEN/GEN_CMakeLists_Librarys.txt") 