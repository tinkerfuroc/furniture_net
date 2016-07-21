cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(pcd2depth)

find_package(PCL 1.2 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (pcd2depth ./src/pcd2depth.cpp)

target_link_libraries (pcd2depth ${PCL_LIBRARIES})
