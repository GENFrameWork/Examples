# --------------------------------------------------------------------
# BinConnPro : Example of console GEN FrameWork (Binary protocol example)
# --------------------------------------------------------------------

 cmake_minimum_required(VERSION 3.3.0)
 project(binconnpro)


 set(GEN_DIRECTORY "../../../../") 


# --------------------------------------------------------------------
# Compile Selection
 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Compile.txt") 


 option(DEBUG_FEATURE                           "Activate Debug mode"                            true )
 option(XTRACE_FEATURE                          "Activate XTrace"                                true )
 option(XMEMORY_CONTROL_FEATURE                 "Activate XMemory Control"                       true )
                  
 option(DIO_FEATURE                             "Activate Data Input/Output"                     true ) 
 option(DIO_CHECKCONNECTIONS_FEATURE            "Activate Check Connections"                     true )
 option(DIO_NETWORKTINEPROTOCOL_FEATURE         "Activate Network Time Protocol"                 true )
 option(DIO_DYNDNS_FEATURE                      "Activate DynDNS"                                true )
 option(DIO_SCRAPERWEB_FEATURE                  "Activate Scraper Web"                           true )

 option(DIO_PROTOCOL_FEATURE                    "Activate Data Input/Output Protocol"            true )

 option(APP_FEATURE                             "Activate Application modules"                   true )
 option(APP_CHECKRESOURCESHARDWARE_FEATURE      "Activate Application Check Resources Hardwar"   true )
 option(APP_CONSOLE_FEATURE                     "Activate Application Console"                   true )
 option(APP_INTERNETSERVICES_FEATURE            "Activate Application Internet Services"         true )
 option(APP_LOG_FEATURE                         "Activate Application Log"                       true )

 option(APP_CFG_GENERAL_FEATURE                 "Activate Application CFG General"               true )  
 option(APP_CFG_LOG_FEATURE                     "Activate Application CFG LOG"                   true )
 option(APP_CFG_INTERNETSERVICES_FEATURE        "Activate Application CFG Internet services"     true )      
 option(APP_CFG_CHECKRESOURCESHARDWARE_FEATURE  "Activate Application CFG Check Resorces HW"     true )  
 option(APP_CFG_DNSRESOLVED_FEATURE             "Activate Application CFG DNS Resolved"          true )   
 option(APP_CFG_LOCATION_FEATURE                "Activate Application CFG Location"              true )  


# --------------------------------------------------------------------
# Config Application Macro

 set(APP_CFG_BINCONNPRO "-DAPP_CFG=BINCONNPRO_CFG::GetInstance()")
 add_definitions(${APP_CFG_BINCONNPRO})


# --------------------------------------------------------------------
# Source code of the GEN in this Application

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists.txt") 
                   
                   
# --------------------------------------------------------------------
# Directorys of the Application

 set(APP_DIRECTORY_APPLICATION   "../Application")
 list(APPEND INCLUDES_DIR ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application

 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/BinConnPro.cpp")
 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/BinConnPro_CFG.cpp")
 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/BinConnPro_ApplicationData.cpp")
 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/BinConnPro_ConnectionsManager.cpp")
 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/BinConnPro_Protocol.cpp")
 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/BinConnPro_Protocol_Device.cpp")


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