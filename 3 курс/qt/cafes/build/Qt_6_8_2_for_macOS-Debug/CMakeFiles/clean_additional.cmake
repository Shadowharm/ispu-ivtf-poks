# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/cafes_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/cafes_autogen.dir/ParseCache.txt"
  "cafes_autogen"
  )
endif()
