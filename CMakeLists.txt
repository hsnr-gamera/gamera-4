cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "-O0 -Wall -Wno-deprecated-declarations") #TODO fix the deprected flag
set(CMAKE_CXX_FLAGS_DEBUG "-g")

find_package(PythonInterp 3 REQUIRED)

# This goes after, since it uses PythonInterp as hint
find_package(PythonLibs 3 REQUIRED)
add_definitions(-D__DEBUG_GAPI__)
set(GAMERA_SOURCE ${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE GAMERA_SOURCES
        "*.h"
        "*.hpp"
        "*.cpp"
        "*.c"
        )

include_directories(${PYTHON_INCLUDE_DIRS})
include_directories(${GAMERA_SOURCE})
include_directories(${PROJECT_SOURCE_DIR}/src/)

add_subdirectory(src/geostructs)
add_subdirectory(src/knncore)
add_subdirectory(src)
add_subdirectory(src/gameracore)
add_subdirectory(src/knnga)
add_subdirectory(src/graph)
add_subdirectory(src/libtiff)