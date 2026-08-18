cmake_minimum_required(VERSION 3.10)
project(dos_detect-open_addressing VERSION 2.4 LANGUAGES CXX)

# Set a default build type if none was specified
set(default_build_type "Debug")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
        STRING "Choose the type of build." FORCE)

    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
        "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

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

include(CheckIncludeFileCXX)
check_include_file_cxx("cstdint" HAVE_CSTDINT)

if(HAVE_CSTDINT)
    include(CheckTypeSize)
    check_type_size("uint64_t" SIZEOF_UINT64_T LANGUAGE CXX)
endif()

message(STATUS "uint64_t size: '${SIZEOF_UINT64_T}'")

if(NOT SIZEOF_UINT64_T EQUAL 8)
    message(WARNING "Can't find suitable uint64_t")
endif()

add_executable(test_hash_f test_hash_function.cpp hash.hpp hash.cpp)
add_executable(test_ip_utils test_ip_utils.cpp ip_utils.cpp ip_utils.hpp)
add_executable(test_hash_table test_hash_table.cpp hash_table.hpp
    hash_table_imp.hpp ip_utils.hpp ip_utils.cpp hash_table_entry.hpp
    hash_table_entry_imp.hpp hash.cpp hash.hpp
    hash_table_iterator.hpp hash_table_iterator_imp.hpp)
add_executable(test_dos_detector
    ip_utils.hpp ip_utils.cpp
    hash.hpp hash.cpp
    hash_table.hpp hash_table_imp.hpp
    hash_table_iterator.hpp hash_table_iterator_imp.hpp
    system.hpp system.cpp
    dos_detector.hpp dos_detector.cpp
    test_dos_detector.cpp)
add_test(NAME TestHashFunction COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_hash_f 01_tests_hash_function WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME TestHashFunctionLP COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_hash_f 02_tests_hash_function_lp WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME TestHashFunctionRP COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_hash_f 03_tests_hash_function_rp WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME TestHashFunctionQP COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_hash_f 04_tests_hash_function_qp WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME TestHashFunctionRH COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_hash_f 05_tests_hash_function_rh WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME TestHashTable COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_hash_table 06_tests_hash_table WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME TestIpUtils COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_ip_utils 07_tests_ip_utils WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME TestDosDetector COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_dos_detector 08_tests_dos_detector WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
