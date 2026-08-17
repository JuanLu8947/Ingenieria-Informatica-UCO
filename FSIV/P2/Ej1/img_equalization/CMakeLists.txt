CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(img_equalization VERSION 1.10 LANGUAGES CXX)
ENABLE_LANGUAGE(CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -O0 -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-g -O3 -Wall")
enable_testing()

FIND_PACKAGE(OpenCV REQUIRED)
LINK_LIBRARIES(${OpenCV_LIBS})
include_directories("${OpenCV_INCLUDE_DIRS}")

add_executable(img_equalization img_equalization.cpp common_code.cpp
    common_code.hpp clahe.cpp clahe.hpp)

add_executable(img_equalization_test_common_code test_common_code.cpp common_code.cpp
    common_code.hpp)
set_target_properties(img_equalization_test_common_code PROPERTIES OUTPUT_NAME "test_common_code")

add_test(NAME TestFSIVComputeHistogram COMMAND test_common_code fsiv_compute_histogram)
add_test(NAME TestFSIVNormalizeHistogram COMMAND test_common_code fsiv_normalize_histogram)
add_test(NAME TestFSIVAccumulateHistogram COMMAND test_common_code fsiv_accumulate_histogram)
add_test(NAME TestFSIVCreateEqualizationLookupTable COMMAND test_common_code fsiv_create_equalization_lookup_table)
add_test(NAME TestFSIVComputeActualClippingHistogramValue COMMAND test_common_code fsiv_compute_actual_clipping_histogram_value)
add_test(NAME TestFSIVComputeClippedHistogram COMMAND test_common_code fsiv_compute_clipped_histogram)
add_test(NAME TestFSIVCreateEqualizationLookupTableWithCLAHE COMMAND test_common_code fsiv_create_equalization_lookup_table_with_clahe)
add_test(NAME TestFSIVApplyLookupTable COMMAND test_common_code fsiv_apply_lookup_table)
