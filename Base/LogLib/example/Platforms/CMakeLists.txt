# --------------------------------------------------------------------
# Example  Hello World 
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.21.0)
project(helloworld)

set(GEN_DIRECTORY "../../../../../GEN/XUtils") 

include_directories(${GEN_DIRECTORY})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

 set(CMAKE_BUILD_TYPE Debug            CACHE STRING "Choose the type of build."  FORCE)
 set(CMAKE_CONFIGURATION_TYPES Debug   CACHE STRING "Choose the type of build."  FORCE)

add_executable(${CMAKE_PROJECT_NAME}
               ../../../helloworld.cpp
               ../../../helloworld.h
              )             

set(LIB_ROOT "${CMAKE_CURRENT_LIST_DIR}/../..")


if(WIN32)
  
  set(LOG_LIB_DIR "${LIB_ROOT}/Platforms/Windows/intel32")
  set(LOG_DLL_DIR "${LIB_ROOT}/Platforms/Windows/intel32")

  find_library(LOGLIB_IMPORT_LIB
               NAMES loglib
               PATHS "${LOG_LIB_DIR}"
               NO_DEFAULT_PATH
              )

  if(NOT LOGLIB_IMPORT_LIB)
    message(FATAL_ERROR "Not Found loglib.lib en: ${LOG_LIB_DIR}")
  endif()

  target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE "${LOGLIB_IMPORT_LIB}")

  add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_if_different
                     "${LOG_DLL_DIR}/loglib.dll"
                     "$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/loglib.dll"
                     COMMENT "Copy loglib.dll to dir EXE"
                    )

else()

  set(LOG_LIB_DIR "${LIB_ROOT}/Platforms/Linux/intel64")

  find_library(LOGLIB_SO
               NAMES loglib libloglib
               PATHS "${LOG_LIB_DIR}"
               NO_DEFAULT_PATH
              )

  if(NOT LOGLIB_SO)
    message(FATAL_ERROR "Not Found loglib.lib en: ${LOG_LIB_DIR}")
  endif()

  target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE "${LOGLIB_SO}")

  set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
                        BUILD_RPATH "${LOG_LIB_DIR}"
                        sINSTALL_RPATH "${LOG_LIB_DIR}"
                       )
endif()              
              