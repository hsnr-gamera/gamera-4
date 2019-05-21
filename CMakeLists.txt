cmake_minimum_required(VERSION 3.1.4)

find_package(PythonInterp 2.7 REQUIRED)

# This goes after, since it uses PythonInterp as hint
find_package(PythonLibs 2.7 REQUIRED)
set(GAMERA_SOURCE ${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src/geostructs)