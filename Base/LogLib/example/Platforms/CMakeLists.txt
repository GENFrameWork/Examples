# --------------------------------------------------------------------
# Example  Hello World 
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.21.0)
project(helloworld)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(GEN_DIRECTORY_COMMON              "../../../../../GEN/Common") 
set(GEN_DIRECTORY_XUTILS              "../../../../../GEN/XUtils") 
set(GEN_DIRECTORY_XUTILS_FORMATFILES  "../../../../../GEN/XUtils/FormatFiles") 
set(GEN_DIRECTORY_APPFLOW             "../../../../../GEN/AppFlow") 
set(GEN_DIRECTORY_MAINPROC            "../../../../../GEN/MainProc") 
set(GEN_DIRECTORY_PLATFORMS_LINUX     "../../../../../GEN/Platforms/Linux") 
set(APP_DIRECTORY_APPLICATION         "../")


list(APPEND GEN_INCLUDES_DIR_LIST ${GEN_DIRECTORY_COMMON})
list(APPEND GEN_INCLUDES_DIR_LIST ${GEN_DIRECTORY_XUTILS})
list(APPEND GEN_INCLUDES_DIR_LIST ${GEN_DIRECTORY_XUTILS_FORMATFILES})
list(APPEND GEN_INCLUDES_DIR_LIST ${GEN_DIRECTORY_APPFLOW})
list(APPEND GEN_INCLUDES_DIR_LIST ${GEN_DIRECTORY_MAINPROC})
list(APPEND GEN_INCLUDES_DIR_LIST ${GEN_DIRECTORY_PLATFORMS_LINUX})
list(APPEND GEN_INCLUDES_DIR_LIST ${APP_DIRECTORY_APPLICATION})


include_directories(${GEN_INCLUDES_DIR_LIST})


set(CMAKE_BUILD_TYPE Debug            CACHE STRING "Choose the type of build."  FORCE)
set(CMAKE_CONFIGURATION_TYPES Debug   CACHE STRING "Choose the type of build."  FORCE)


add_executable(${CMAKE_PROJECT_NAME}  ../../../helloworld.cpp)             

set(LIB_ROOT "${CMAKE_CURRENT_LIST_DIR}/../..")


if(WIN32)
  
  add_definitions(-DWINDOWS)  

  set(LOG_LIB_DIR "${LIB_ROOT}/Platforms/Windows/intel32")
  set(LOG_DLL_DIR "${LIB_ROOT}/Platforms/Windows/intel32")

  find_library(LOGLIB
               NAMES loglib
               PATHS "${LOG_LIB_DIR}"
               NO_DEFAULT_PATH
              )

  if(NOT LOGLIB)
    message(FATAL_ERROR "Not Found loglibb in: ${LOGLIB}")
  endif()

  target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE "${LOGLIB}")

  add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_if_different
                     "${LOG_DLL_DIR}/loglib.dll"
                     "$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/loglib.dll"
                     COMMENT "Copy loglib.dll to dir EXE"
                    )

else()

  add_definitions(-DLINUX)  

  set(LOG_LIB_DIR "${LIB_ROOT}/Platforms/Linux/intel64")

  find_library(LOGLIB
               NAMES loglib libloglib
               PATHS "${LOG_LIB_DIR}"
               NO_DEFAULT_PATH
              )

  if(NOT LOGLIB)
    message(FATAL_ERROR "Not Found loglib in: ${LOG_LIB_DIR}")
  endif()

  target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE "${LOGLIB}")

  set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
                        BUILD_RPATH "${LOG_LIB_DIR}"
                        INSTALL_RPATH "${LOG_LIB_DIR}"
                       )
endif()              
              