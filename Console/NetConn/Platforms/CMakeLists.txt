# --------------------------------------------------------------------
# NetConn : Example of console: Core protocol example
# GEN FrameWork
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.14.0)
project(netconn)


set(GEN_DIRECTORY "../../../../") 


# --------------------------------------------------------------------
# features/Defines

option(DEBUG_FEATURE                                            "Debug mode"                                              ON )
option(XTRACE_FEATURE                                           "XTrace"                                                  ON )
option(XTRACE_NOINTERNET_FEATURE                                "No need for trace dependencies with Internet"            ON )
option(XMEMORY_CONTROL_FEATURE                                  "XMemory Control"                                         ON )
                    
option(DIO_FEATURE                                              "Data Input/Output"                                       ON ) 
option(DIO_CHECKCONNECTIONS_FEATURE                             "Check Connections"                                       ON )
option(DIO_NETWORKTIMEPROTOCOL_FEATURE                          "Network Time Protocol"                                   ON )
option(DIO_DYNDNS_FEATURE                                       "DynDNS"                                                  ON )
option(DIO_SCRAPERWEB_FEATURE                                   "Scraper Web"                                             ON )
option(DIO_COREPROTOCOL_FEATURE                                 "Data Input/Output Protocol"                              ON )

option(HASH_SHA2_FEATURE                                        "Hash SHA2"                                               ON )
option(CIPHER_SYMMETRIC_AES_FEATURE                             "Cipher Symetric AES"                                     ON )
    
option(APP_FEATURE                                              "Application modules"                                     ON )
option(APP_CONSOLE_FEATURE                                      "Application Console"                                     ON )
option(APP_EXTENDED_FEATURE                                     "Application Extended"                                    ON )  
option(APP_EXTENDED_APPLICATIONHEADER_FEATURE                   "Application Extended Aplication Header"                  ON )  
option(APP_EXTENDED_APPLICATIONSTATUS_FEATURE                   "Application Extended Aplication Status"                  ON )  
option(APP_EXTENDED_INTERNETSTATUS_FEATURE                      "Application Extended Internet Status"                    ON )  
option(APP_CHECKRESOURCESHARDWARE_FEATURE                       "Application Check Resources Hardwar"                     ON )
option(APP_INTERNETSERVICES_FEATURE                             "Application Internet Services"                           ON )
option(APP_LOG_FEATURE                                          "Application Log"                                         ON )
    
option(APP_CFG_GENERAL_FEATURE                                  "Application CFG General"                                 ON )  
option(APP_CFG_LOG_FEATURE                                      "Application CFG LOG"                                     ON )
option(APP_CFG_INTERNETSERVICES_FEATURE                         "Application CFG Internet services"                       ON )      
option(APP_CFG_CHECKRESOURCESHARDWARE_FEATURE                   "Application CFG Check Resorces HW"                       ON )  
option(APP_CFG_DNSRESOLVER_FEATURE                              "Application CFG DNS "                                    ON )   
option(APP_CFG_DIOLOCATION_FEATURE                              "Application CFG DIO Location"                            ON )          

# --------------------------------------------------------------------
# Config Application Macro

set(APP_CFG_NETCONN "-DAPP_CFG=NETCONN_CFG::GetInstance()")
add_definitions(${APP_CFG_NETCONN})


# --------------------------------------------------------------------
# Main CMakeList of GEN

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_Main.txt") 
                   
                   
# --------------------------------------------------------------------
# Directorys of the Application

set(APP_DIRECTORY_APPLICATION               "../Application")
set(APP_DIRECTORY_APPLICATION_COREPROTOCOL  "${APP_DIRECTORY_APPLICATION}/CoreProtocol")

list(APPEND GEN_INCLUDES_DIR_LIST ${APP_DIRECTORY_APPLICATION})
list(APPEND GEN_INCLUDES_DIR_LIST ${APP_DIRECTORY_APPLICATION_COREPROTOCOL})

# --------------------------------------------------------------------
# Source code of the Application

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/NetConn.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/NetConn_CFG.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/NetConn_AgentState.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/NetConn_TestUpdateClass.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION_COREPROTOCOL}/NetConn_CoreProtocol_Response.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION_COREPROTOCOL}/NetConn_CoreProtocol_RegisterData.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION_COREPROTOCOL}/NetConn_CoreProtocol.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION_COREPROTOCOL}/NetConn_CoreProtocol_Connection.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION_COREPROTOCOL}/NetConn_CoreProtocol_ConnectionsManager.cpp")


# --------------------------------------------------------------------
# Create proyect 

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_CreateProject.txt") 


# --------------------------------------------------------------------
# Add Libraries

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_Libraries.txt") 