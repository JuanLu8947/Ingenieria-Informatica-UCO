cmake_minimum_required(VERSION 3.10)
project(avl_tree VERSION 1.9 LANGUAGES CXX)

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

add_executable(test_bstnode test_avltnode.cpp avltree_node.hpp avltree_node_imp.hpp)
target_compile_definitions(test_bstnode PRIVATE -D__ONLY_BSTREE__=1)

add_executable(test_avltnode test_avltnode.cpp avltree_node.hpp avltree_node_imp.hpp)

add_executable(test_bstree test_avltree.cpp avltree_node.hpp avltree_node_imp.hpp avltree_iterator.hpp avltree_iterator_imp.hpp avltree.hpp avltree_imp.hpp)
target_compile_definitions(test_bstree PRIVATE -D__ONLY_BSTREE__=1)

add_executable(test_avltree test_avltree.cpp avltree_node.hpp avltree_node_imp.hpp avltree_iterator.hpp avltree_iterator_imp.hpp avltree.hpp avltree_imp.hpp)


add_test(NAME TestBSTreeNode COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_bstnode 01_tests_bstnode WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME TestBSTree COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_bstree 02_tests_bstree WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME TestBSTreePB COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_bstree 03_tests_bstree_perfectly_balanced WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME TestAVLTreeNode COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_avltnode 04_tests_avltnode WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME TestAVLTree COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_avltree 05_tests_avltree WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME TestAVLTreeIterator COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_avltree 07_tests_avltree_iterator WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME TestAVLTreeMinMax COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_avltree 06_tests_compute_min_max_branch_length WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})