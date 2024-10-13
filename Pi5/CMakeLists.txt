cmake_minimum_required(VERSION 3.10)
project(OpenCV)

find_package(OpenCV REQUIRED)
include_directories(($/usr/include/opencv4))

add_executable(opencv_example src/main.cpp)
target_link_libraries(opencv_example $/usr/include/opencv4)