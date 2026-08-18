cmake_minimum_required(VERSION 3.10)
project(kdtree VERSION 1.0 LANGUAGES CXX)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "/W4")
    set(CMAKE_CXX_FLAGS_DEBUG "/Od /Zi /EHsc /DEBUG")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "-Wall")
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb3")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
enable_testing()
find_package(Python 3 COMPONENTS Interpreter)

add_subdirectory(pattern)
include_directories("pattern")

add_subdirectory(binary_tree)
include_directories("binary_tree")

add_library(kdtree STATIC kdtree.hpp kdtree.cpp)
target_link_libraries(kdtree pattern)

add_executable(test_kdtree test_kdtree.cpp)
target_link_libraries(test_kdtree kdtree pattern)

add_test(NAME TestCreateKDTree COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_kdtree 01_tests_create_kdtree WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME TestKDTreeNearestL1 COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_kdtree 02_tests_find_nn_L1 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME TestKDTreeNearestL2 COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_kdtree 03_tests_find_nn_L2 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
