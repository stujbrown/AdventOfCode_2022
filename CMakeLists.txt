# CMakeList.txt : CMake project for AdventOfCode_2022, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("AdventOfCode_2022")

# Add source to this project's executable.
add_executable (AdventOfCode_2022 "main.cpp"  "days/day1.cpp" "days/aoc_days.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET AdventOfCode_2022 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
