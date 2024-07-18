# --------------------------------------------------------------------
# MiniWebServer : Example of console: Web Server example
# GEN FrameWork
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.14.0)
project(miniwebserver)


set(GEN_DIRECTORY "../../../../") 


# --------------------------------------------------------------------
# Activate features/Defines

option(DEBUG_FEATURE                                          "Activate Debug mode"                                     ON )
option(XTRACE_FEATURE                                         "Activate XTrace"                                         ON )
option(XTRACE_NOINTERNET_FEATURE                              "No need for trace dependencies with Internet"            ON )
option(XMEMORY_CONTROL_FEATURE                                "Activate XMemory Control"                                ON )
option(XSERIALIZABLE_JSON_FEATURE                             "Activate Serializable JSON"                              ON ) 
                    
option(DIO_FEATURE                                            "Activate Data Input/Output"                              ON )
option(DIO_CHECKCONNECTIONS_FEATURE                           "Activate Check Connections"                              ON )
option(DIO_NETWORKTIMEPROTOCOL_FEATURE                        "Activate Network Time Protocol"                          ON )
option(DIO_DYNDNS_FEATURE                                     "Activate DynDNS"                                         ON )
option(DIO_WEBSERVER_FEATURE                                  "Activate Web Server"                                     ON )
option(DIO_SCRAPERWEB_FEATURE                                 "Activate Scraper Web"                                    ON )
    
option(APP_FEATURE                                            "Activate Application modules"                            ON )
option(APP_CONSOLE_FEATURE                                    "Activate Application Console"                            ON )
option(APP_INTERNETSERVICES_FEATURE                           "Activate Application Internet Services"                  ON )
option(APP_LOG_FEATURE                                        "Activate Application Log"                                ON )
option(APP_WEBSERVER_FEATURE                                  "Activate Application Web Server"                         ON )
    
option(APP_CFG_GENERAL_FEATURE                                "Activate Application CFG General"                        ON )
option(APP_CFG_LOG_FEATURE                                    "Activate Application CFG LOG"                            ON )
option(APP_CFG_INTERNETSERVICES_FEATURE                       "Activate Application CFG Internet services"              ON )
option(APP_CFG_DYNDNSMANAGER_FEATURE                          "Activate Application CFG DynDNS Manager"                 ON )
option(APP_CFG_WEBSERVER_FEATURE                              "Activate Application CFG Web Server"                     ON )


# --------------------------------------------------------------------
# Config Application Macro

set(APP_CFG_MINISERVERWEB "-DAPP_CFG=MINIWEBSERVER_CFG::GetInstance()")
add_definitions(${APP_CFG_MINISERVERWEB})


# --------------------------------------------------------------------
# Main CMakeList of GEN

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_Main.txt") 
                   
                   
# --------------------------------------------------------------------
# Directorys of the Application

set(APP_DIRECTORY_APPLICATION   "../Application")
list(APPEND GEN_INCLUDES_DIR_LIST ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/MiniWebServer.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/MiniWebServer_CFG.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/MiniWebServer_APIRest.cpp")


# --------------------------------------------------------------------
# Create proyect 

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_CreateProject.txt") 


# --------------------------------------------------------------------
# Add Libraries

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_Libraries.txt") 
 