cmake_minimum_required(VERSION 3.10)
project(marketplace)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enables testing with add_test() for this project
enable_testing()

# Adding subdirs
add_subdirectory(src)
add_subdirectory(tests)