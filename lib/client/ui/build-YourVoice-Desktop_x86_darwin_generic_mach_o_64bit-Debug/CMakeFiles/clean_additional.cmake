# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/YourVoice_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/YourVoice_autogen.dir/ParseCache.txt"
  "YourVoice_autogen"
  )
endif()
