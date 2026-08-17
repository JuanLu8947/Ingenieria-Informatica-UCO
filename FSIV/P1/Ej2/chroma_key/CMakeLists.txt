CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(chroma_key VERSION 1.4 LANGUAGES CXX)
ENABLE_LANGUAGE(CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -O0 -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-g -O3 -Wall")
enable_testing()

FIND_PACKAGE(OpenCV REQUIRED )
LINK_LIBRARIES(${OpenCV_LIBS})
include_directories ("${OpenCV_INCLUDE_DIRS}")

add_executable(chroma_key chroma_key.cpp common_code.cpp
    common_code.hpp)

add_executable(chroma_key_test_common_code test_common_code.cpp common_code.cpp
    common_code.hpp)
set_target_properties(chroma_key_test_common_code PROPERTIES OUTPUT_NAME "test_common_code")

add_test(NAME TestFSIVConvertBgrToHsv COMMAND test_common_code fsiv_convert_bgr_to_hsv)
add_test(NAME TestFSIVComputeChromaKeyMask COMMAND test_common_code fsiv_compute_chroma_key_mask)
add_test(NAME TestFSIVCombineImages COMMAND test_common_code fsiv_combine_images)
add_test(NAME TestFSIVApplyChromaKey COMMAND test_common_code fsiv_apply_chroma_key)
