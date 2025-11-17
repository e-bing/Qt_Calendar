# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Calendar_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Calendar_autogen.dir\\ParseCache.txt"
  "Calendar_autogen"
  )
endif()
