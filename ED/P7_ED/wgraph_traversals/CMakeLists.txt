cmake_minimum_required(VERSION 3.10)
project(graph_traversals VERSION 1.4 LANGUAGES CXX)

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

add_subdirectory(graph)
include_directories("graph")

add_executable(test_traversals test_traversals.cpp wgraph_traversals.hpp wgraph_traversals_imp.hpp
    prim_algorithm.hpp prim_algorithm_imp.hpp
    kruskal_algorithm.hpp kruskal_algorithm_imp.hpp disjointsets.hpp)
target_link_libraries(test_traversals graph)
target_compile_definitions(test_traversals PRIVATE -D__VERBOSE__=1)

add_test(NAME TestDeepFirst COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_traversals 01_tests_df WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME TestBreathFirst COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_traversals 02_tests_bf WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME TestTopologicalSorting COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_traversals 03_tests_ts WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME TestPrim COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_traversals 04_tests_prim WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME TestKruskal COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_traversals 05_tests_kruskal WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})