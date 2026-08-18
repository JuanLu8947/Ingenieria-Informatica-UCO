cmake_minimum_required(VERSION 3.10)
project(wgraph_paths VERSION 1.3 LANGUAGES CXX)

enable_language(CXX)

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

add_subdirectory(priority_queue)
include_directories("./priority_queue")

add_subdirectory(graph)
include_directories("./graph")

add_subdirectory(matrix)
include_directories("./matrix")

add_executable(test_dijkstra test_dijkstra.cpp dijkstra_algorithm.hpp dijkstra_algorithm_imp.hpp)
target_link_libraries(test_dijkstra graph)
target_compile_definitions(test_dijkstra PRIVATE -D__VERBOSE__=1)

add_executable(test_floyd test_floyd.cpp floyd_algorithm.hpp floyd_algorithm_imp.hpp)
target_link_libraries(test_floyd matrix graph)
target_compile_definitions(test_floyd PRIVATE -D__VERBOSE__=1)

add_executable(test_astar test_astar.cpp a_star_algorithm.hpp a_star_algorithm_imp.hpp)
target_link_libraries(test_astar graph)
target_compile_definitions(test_astar PRIVATE -D__VERBOSE__=1)

add_test(NAME TestDijkstra COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_dijkstra 01_tests_dijkstra WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME TestFloyd COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_floyd 02_tests_floyd WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME TestAStar COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_astar 03_tests_astar WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})