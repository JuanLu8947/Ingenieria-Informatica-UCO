CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(cbg_process VERSION 1.7 LANGUAGES CXX)
ENABLE_LANGUAGE(CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -O0 -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-g -O3 -Wall")
enable_testing()

FIND_PACKAGE(OpenCV REQUIRED )
LINK_LIBRARIES(${OpenCV_LIBS})
include_directories ("${OpenCV_INCLUDE_DIRS}")

add_executable(cbg_process cbg_process.cpp common_code.cpp
    common_code.hpp)

add_executable(cbg_process_test_common_code test_common_code.cpp common_code.cpp
    common_code.hpp)
set_target_properties(cbg_process_test_common_code PROPERTIES OUTPUT_NAME "test_common_code")

add_test(NAME TestFSIVConvertImageByteToFloat COMMAND test_common_code fsiv_convert_image_byte_to_float)
add_test(NAME TestFSIVConvertImageFloatToByte COMMAND test_common_code fsiv_convert_image_float_to_byte)
add_test(NAME TestFSIVConvertBgrToHsv COMMAND test_common_code fsiv_convert_bgr_to_hsv)
add_test(NAME TestFSIVConvertHsvToBgr COMMAND test_common_code fsiv_convert_hsv_to_bgr)
add_test(NAME TestFSIVCBGProcess COMMAND test_common_code fsiv_cbg_process)
add_test(NAME TestFSIVCBGProcessOnlyLuma COMMAND test_common_code fsiv_cbg_process_only_luma)
