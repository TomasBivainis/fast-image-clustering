cmake_minimum_required(VERSION 3.10)
project(KMeansApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.13.0
)
FetchContent_MakeAvailable(Catch2)

add_library(KMeansLib
    src/Vec3.cpp
    src/Image.cpp
    src/Centroid.cpp
    src/KMeans.cpp
)

target_include_directories(KMeansLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(KMeansLib PUBLIC ${OpenCV_LIBS})

add_executable(KMeansApp ./src/main.cpp)
target_link_libraries(KMeansApp PRIVATE KMeansLib)