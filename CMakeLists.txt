cmake_minimum_required(VERSION 3.0)
project(turbotrack)

add_library(turbotrack "${CMAKE_CURRENT_LIST_DIR}/src/turbotrack.cpp")
target_include_directories(turbotrack PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")

set(TURBOTRACK_LINALG_LIBRARY "EIGEN" CACHE STRING
	"The linear algebra library to use for the vector/quaternion types. Supported: EIGEN, GLM."
)

if(TURBOTRACK_LINALG_LIBRARY STREQUAL "EIGEN")
	find_package(Eigen3 3.3 REQUIRED NO_MODULE)
	target_link_libraries(turbotrack PUBLIC Eigen3::Eigen)

	target_compile_definitions(turbotrack PUBLIC TURBOTRACK_USE_EIGEN)

	target_sources(turbotrack PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src/turbotrack_eigen.cpp")

elseif(TURBOTRACK_LINALG_LIBRARY STREQUAL "GLM")
	find_package(glm REQUIRED NO_MODULE)
	target_link_libraries(turbotrack PUBLIC glm)

	target_compile_definitions(turbotrack PUBLIC TURBOTRACK_USE_GLM)

	target_sources(turbotrack PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src/turbotrack_glm.cpp")

else()
	message(FATAL_ERROR "TURBOTRACK_LINALG_LIBRARY must be set to either EIGEN or GLM!")
endif()
