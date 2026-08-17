CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(blur_background VERSION 2.5 LANGUAGES CXX)
ENABLE_LANGUAGE(CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -O0 -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-g -O3 -Wall")
enable_testing()

FIND_PACKAGE(OpenCV REQUIRED)
LINK_LIBRARIES(${OpenCV_LIBS})
include_directories("${OpenCV_INCLUDE_DIRS}")

add_executable(blur_background blur_background.cpp
    common_code.cpp common_code.hpp)

add_executable(blur_background_test_common_code test_common_code.cpp
    common_code.cpp common_code.hpp)
set_target_properties(blur_background_test_common_code PROPERTIES OUTPUT_NAME "test_common_code")

add_test(NAME TestFSIVComputeDenseOpticalFlow COMMAND test_common_code fsiv_compute_dense_optical_flow)
add_test(NAME TestFSIVComputeOpticalFlowMagnitude COMMAND test_common_code fsiv_compute_optical_flow_magnitude)
add_test(NAME TestFSIVCreateStructuringElement COMMAND test_common_code fsiv_create_structuring_element)
add_test(NAME TestFSIVComputeOfForegroundMask COMMAND test_common_code fsiv_compute_of_foreground_mask)
add_test(NAME TestFSIVBlurBackground COMMAND test_common_code fsiv_blur_background)
