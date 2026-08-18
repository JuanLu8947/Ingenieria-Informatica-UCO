cmake_minimum_required(VERSION 3.10)
project(pattern VERSION 1.0 LANGUAGES CXX)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "/W4")
    set(CMAKE_CXX_FLAGS_DEBUG "/Od /Zi /EHsc /DEBUG")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGST "-Wall")
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb3")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
enable_testing()
find_package(Python 3 COMPONENTS Interpreter)

add_library(pattern STATIC pattern.cpp pattern.hpp)
add_executable(test_pattern test_pattern.cpp pattern)

add_test(NAME TestPattern COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_pattern 01_tests_pattern WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME TestDataset COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_pattern 02_tests_pattern_dataset WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME TestPatternDistances COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_pattern 03_tests_pattern_distances WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
