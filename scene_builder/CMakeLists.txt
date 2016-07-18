cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(viewer)

find_package(PCL 1.2 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (ply2pcd ./target/ply2pcd.cpp)
target_link_libraries (ply2pcd ${PCL_LIBRARIES})
