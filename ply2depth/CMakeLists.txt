cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(ply2depth)

find_package(OpenCV REQUIRED)
find_package(PCL 1.7 REQUIRED)

include_directories(
  include
  ${OpenCV_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
)
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (ply2depth ./src/ply2depth.cpp)

target_link_libraries (ply2depth ${PCL_LIBRARIES} ${OpenCV_LIBS})
