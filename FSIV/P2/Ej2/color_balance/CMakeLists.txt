CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(color_balance VERSION 2.8 LANGUAGES CXX)
ENABLE_LANGUAGE(CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -O0 -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-g -O3 -Wall")
enable_testing()

FIND_PACKAGE(OpenCV REQUIRED )
LINK_LIBRARIES(${OpenCV_LIBS})
include_directories ("${OpenCV_INCLUDE_DIRS}")

add_executable(color_balance color_balance.cpp common_code.cpp common_code.hpp)
add_executable(color_balance_test_common_code test_common_code.cpp common_code.cpp
    common_code.hpp)
set_target_properties(color_balance_test_common_code PROPERTIES OUTPUT_NAME "test_common_code")

add_test(NAME TestFSIVColorRescaling COMMAND test_common_code fsiv_color_rescaling)
add_test(NAME TestFSIVConvertBgrToGray COMMAND test_common_code fsiv_convert_bgr_to_gray)
add_test(NAME TestFSIVGrayWorldColorBalance COMMAND test_common_code fsiv_gray_world_color_balance)
add_test(NAME TestFSIVComputeImageHistogram COMMAND test_common_code fsiv_compute_image_histogram)
add_test(NAME TestFSIVComputeHistogramPercentile COMMAND test_common_code fsiv_compute_histogram_percentile)
add_test(NAME TestFSIVWhitePatchColorBalance COMMAND test_common_code fsiv_white_patch_color_balance)


 
