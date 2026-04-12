# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "E:\\Projects\\GEN_FrameWork\\Examples\\Console\\BinConnPro\\Common\\docker\\dockerfile_prod_binconnpro"
  )
endif()
