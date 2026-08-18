cmake_minimum_required(VERSION 3.10)
project(linear_ds VERSION 1.4 LANGUAGES CXX)

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

add_executable(test_list test_list.cpp list.hpp list_imp.hpp list_node.hpp
    list_node_imp.hpp list_iterator.hpp list_iterator_imp.hpp)
add_executable(test_dnode test_list.cpp list.hpp list_imp.hpp list_node.hpp
    list_node_imp.hpp list_iterator.hpp list_iterator_imp.hpp)
add_executable(test_iterator test_list.cpp list.hpp list_imp.hpp list_node.hpp
    list_node_imp.hpp list_iterator.hpp list_iterator_imp.hpp)
add_executable(test_stack test_stack.cpp stack.hpp stack_imp.hpp list.hpp
    list_imp.hpp)
add_executable(test_cdarray test_cdarray.cpp cdarray_imp.hpp)
add_executable(test_queue test_queue.cpp queue.hpp queue_imp.hpp
    stack.hpp stack_imp.hpp)

add_test(NAME TestCDArray COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_cdarray 01_tests_cdarray WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME TestCDArrayFoldUnfold COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_cdarray 02_tests_cdarray_fold_unfold WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME TestQueue COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_queue 03_tests_queue WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME TestDNode COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_dnode 04_tests_simple_list_node WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME TestSimpleList COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_list 05_tests_simple_list WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME TestListNode COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_list 06_tests_list_node WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME TestListIterator COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_iterator 07_tests_list_iterator WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME TestListEditing COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_list 08_tests_list_editing WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME TestListFoldUnfold COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_list 09_tests_list_fold_unfold WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME TestListAlgorithm COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_list 10_list_algorithms WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME TestStack COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_stack 11_tests_stack WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
