cmake_minimum_required(VERSION 3.0)
project(turbotrack CXX)

add_library(turbotrack INTERFACE)
target_include_directories(turbotrack INTERFACE "${CMAKE_CURRENT_LIST_DIR}/include")
set_target_properties(turbotrack PROPERTIES
	CXX_STANDARD 17
	CXX_EXTENSIONS OFF
)