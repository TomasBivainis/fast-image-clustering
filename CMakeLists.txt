cmake_minimum_required(VERSION 3.10)
project(MyOpenCVProject)

find_package(OpenCV REQUIRED)

add_executable(my_app ./src/main.cpp)

target_link_libraries(my_app ${OpenCV_LIBS})