# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\ScheduleManagerApp_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ScheduleManagerApp_autogen.dir\\ParseCache.txt"
  "ScheduleManagerApp_autogen"
  )
endif()
