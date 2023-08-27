# --------------------------------------------------------------------
# MiniWebServer : Example of console: Web Server example
# GEN FrameWork
# --------------------------------------------------------------------

 cmake_minimum_required(VERSION 3.6.0)
 project(miniwebserver)


 set(GEN_DIRECTORY "../../../../") 


# --------------------------------------------------------------------
# Activate features/Defines

 option(DEBUG_FEATURE                           "Activate Debug mode"                            true )
 option(XTRACE_FEATURE                          "Activate XTrace"                                true )
 option(XMEMORY_CONTROL_FEATURE                 "Activate XMemory Control"                       true )
 option(XSERIALIZABLE_JSON_FEATURE              "Activate Serializable JSON"                     true ) 
                  
 option(DIO_FEATURE                             "Activate Data Input/Output"                     true )
 option(DIO_CHECKCONNECTIONS_FEATURE            "Activate Check Connections"                     true )
 option(DIO_NETWORKTINEPROTOCOL_FEATURE         "Activate Network Time Protocol"                 true )
 option(DIO_DYNDNS_FEATURE                      "Activate DynDNS"                                true )
 option(DIO_WEBSERVER_FEATURE                   "Activate Web Server"                            true )
 option(DIO_SCRAPERWEB_FEATURE                  "Activate Scraper Web"                           true )

 option(APP_FEATURE                             "Activate Application modules"                   true )
 option(APP_CONSOLE_FEATURE                     "Activate Application Console"                   true )
 option(APP_INTERNETSERVICES_FEATURE            "Activate Application Internet Services"         true )
 option(APP_LOG_FEATURE                         "Activate Application Log"                       true )
 option(APP_WEBSERVER_FEATURE                   "Activate Application Web Server"                true )

 option(APP_CFG_GENERAL_FEATURE                 "Activate Application CFG General"               true )
 option(APP_CFG_LOG_FEATURE                     "Activate Application CFG LOG"                   true )
 option(APP_CFG_INTERNETSERVICES_FEATURE        "Activate Application CFG Internet services"     true )
 option(APP_CFG_DYNDNSMANAGER_FEATURE           "Activate Application CFG DynDNS Manager"        true )
 option(APP_CFG_WEBSERVER_FEATURE               "Activate Application CFG Web Server"            true )


# --------------------------------------------------------------------
# Config Application Macro

 set(APP_CFG_MINISERVERWEB "-DAPP_CFG=MINIWEBSERVER_CFG::GetInstance()")
 add_definitions(${APP_CFG_MINISERVERWEB})


# --------------------------------------------------------------------
# Main CMakeList of GEN

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Main.txt") 
                   
                   
# --------------------------------------------------------------------
# Directorys of the Application

 set(APP_DIRECTORY_APPLICATION   "../Application")
 list(APPEND INCLUDES_DIR ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application

 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/MiniWebServer.cpp")
 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/MiniWebServer_CFG.cpp")
 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/MiniWebServer_APIRest.cpp")


# --------------------------------------------------------------------
# Create proyect 

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_CreateProject.txt") 


# --------------------------------------------------------------------
# Add Libraries

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Libraries.txt") 
 