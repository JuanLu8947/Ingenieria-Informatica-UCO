cmake_minimum_required(VERSION 3.10)
project(alphabet_soup VERSION 2.4.1 LANGUAGES CXX)

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

add_subdirectory(trie)
include_directories("trie")

add_executable(test_alphabet_soup_solver test_alphabet_soup_solver.cpp
    alphabet_soup_solver.cpp alphabet_soup_solver.hpp
    alphabet_soup.cpp alphabet_soup.hpp)
target_link_libraries(test_alphabet_soup_solver trie)

add_test(NAME TestAlphabetSoup COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_alphabet_soup_solver 01_tests_alphabet_soup WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
