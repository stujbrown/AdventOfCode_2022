# CMakeList.txt : CMake project for AdventOfCode_2022, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("AdventOfCode_2022")

set(IMGUI
	"imgui")
	
include_directories("${CMAKE_CURRENT_LIST_DIR}")
include_directories("${CMAKE_CURRENT_LIST_DIR}/${IMGUI}")
include_directories("C:/Program Files (x86)/Windows Kits/10/Include/10.0.19041.0/um")

link_directories("${IMGUI}/build/src/Release")

# Add source to this project's executable.
add_executable (AdventOfCode_2022 WIN32
	"${IMGUI}/imgui.cpp"
	"${IMGUI}/imgui_draw.cpp"
	"${IMGUI}/imgui_tables.cpp"
	"${IMGUI}/imgui_widgets.cpp"
	"${IMGUI}/backends/imgui_impl_dx11.cpp" 
	"${IMGUI}/backends/imgui_impl_win32.cpp"
	"main.cpp" 
	"window.cpp"
	"days/day1.cpp"
	"days/day2.cpp"
	"days/day3.cpp"
	"days/day4.cpp"
	"days/day5.cpp"
	"days/day6.cpp"
	"days/day7.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET AdventOfCode_2022 PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(AdventOfCode_2022 
	"d3d11.lib"
	"opengl32.dll")
