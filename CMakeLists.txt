cmake_minimum_required(VERSION 3.0)
project(turbotrack)

add_library(turbotrack "${CMAKE_CURRENT_LIST_DIR}/src/turbotrack.cpp")

target_include_directories(turbotrack PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")

find_package(Eigen3 3.3 REQUIRED NO_MODULE)
target_link_libraries(turbotrack PUBLIC Eigen3::Eigen)
