# --------------------------------------------------------------------
# Example  Hello World
# --------------------------------------------------------------------


cmake_minimum_required(VERSION 3.21.0)
project(helloworld)

option(LOGLIB_STATIC_FEATURE "Log LIB Static" ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


set(GEN_DIRECTORY_MAINPROC            "../../../../../GEN/MainProc")
set(GEN_DIRECTORY_XUTILS              "../../../../../GEN/XUtils")
set(APP_DIRECTORY_APPLICATION         "../")


list(APPEND GEN_INCLUDES_DIR_LIST ${GEN_DIRECTORY_MAINPROC})
list(APPEND GEN_INCLUDES_DIR_LIST ${GEN_DIRECTORY_XUTILS})
list(APPEND GEN_INCLUDES_DIR_LIST ${APP_DIRECTORY_APPLICATION})


include_directories(${GEN_INCLUDES_DIR_LIST})

set(CMAKE_BUILD_TYPE Debug           CACHE STRING "Choose the type of build." FORCE)
set(CMAKE_CONFIGURATION_TYPES Debug  CACHE STRING "Choose the type of build." FORCE)

add_executable(${CMAKE_PROJECT_NAME} ../../../helloworld.cpp)




# --------------------------------------------------------------------
# loglib 
# --------------------------------------------------------------------

set(LIB_ROOT "${CMAKE_CURRENT_LIST_DIR}/../..")

if(WIN32)

  add_definitions(-DWINDOWS)

  set(LOG_DIR "${LIB_ROOT}/Platforms/Windows/intel32")
    
  find_library(LOGLIB_PATH
    NAMES loglib
    PATHS "${LOG_DIR}"
    NO_DEFAULT_PATH
  )


  if(NOT LOGLIB_PATH)

    message(FATAL_ERROR "Not Found loglib.lib in: ${LOG_DIR}")

  endif()

  
  if(LOGLIB_STATIC_FEATURE)

    add_library(loglib::loglib STATIC IMPORTED GLOBAL)

    set_target_properties( loglib::loglib PROPERTIES
                           IMPORTED_LOCATION "${LOGLIB_PATH}"         # loglib.lib (static)
                          )  
                          
    target_link_libraries(loglib::loglib INTERFACE ws2_32 iphlpapi)

  else()

    set(LOGLIB_DLL "${LOG_DIR}/loglib.dll")

    if(NOT EXISTS "${LOGLIB_DLL}")
      message(FATAL_ERROR "Not Found loglib.dll in: ${LOG_DIR}")
    endif()

    add_library(loglib::loglib SHARED IMPORTED GLOBAL)

    set_target_properties( loglib::loglib PROPERTIES
                           IMPORTED_LOCATION "${LOGLIB_DLL}"          # loglib.dll
                           IMPORTED_IMPLIB   "${LOGLIB_PATH}"         # loglib.lib (import)
                         )

    # Copy Windows DLL next to exe (sin rutas duplicadas)
    add_custom_command( TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${LOGLIB_DLL}" "$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/loglib.dll"
                      )

  endif()
  
  target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE loglib::loglib)

else()

  add_definitions(-DLINUX)

  set(LOG_DIR "${LIB_ROOT}/Platforms/Linux/intel64")

  find_library( LOGLIB_PATH
                NAMES loglib libloglib
                PATHS "${LOG_DIR}"
                NO_DEFAULT_PATH
              )


  if(NOT LOGLIB_PATH)

    message(FATAL_ERROR "Not Found loglib in: ${LOG_DIR}")

  endif()


  add_library(loglib::loglib UNKNOWN IMPORTED GLOBAL)

  set_target_properties( loglib::loglib PROPERTIES
                         IMPORTED_LOCATION "${LOGLIB_PATH}"
                       )

  target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE loglib::loglib)

  set_target_properties( ${CMAKE_PROJECT_NAME} PROPERTIES
                         BUILD_RPATH "${LOG_DIR}"
                         INSTALL_RPATH "${LOG_DIR}"
                       )

endif()


