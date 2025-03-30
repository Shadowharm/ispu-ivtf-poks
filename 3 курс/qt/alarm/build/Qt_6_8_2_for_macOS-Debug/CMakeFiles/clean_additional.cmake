# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/alarm_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/alarm_autogen.dir/ParseCache.txt"
  "alarm_autogen"
  )
endif()
