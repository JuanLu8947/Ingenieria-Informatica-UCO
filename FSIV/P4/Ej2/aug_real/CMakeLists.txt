CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(aug_real VERSION 1.7 LANGUAGES CXX)
ENABLE_LANGUAGE(CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -O0 -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-g -O3 -Wall")
enable_testing()

FIND_PACKAGE(OpenCV REQUIRED )
LINK_LIBRARIES(${OpenCV_LIBS})
include_directories ("${OpenCV_INCLUDE_DIRS}")

add_executable(aug_real aug_real.cpp common_code.cpp common_code.hpp)
add_executable(aug_real_test_common_code test_common_code.cpp test_data.cpp test_data.hpp common_code.cpp common_code.hpp)
set_target_properties(aug_real_test_common_code PROPERTIES OUTPUT_NAME "test_common_code")

 
add_test(NAME TestFSIVGenerate3DCalibrationPoints COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_common_code fsiv_generate_3d_calibration_points WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data)
add_test(NAME TestFSIVFastFindChessboardCorners COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_common_code fsiv_fast_find_chessboard_corners WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data)
add_test(NAME TestFSIVDrawAxes COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_common_code fsiv_draw_axes WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data)
add_test(NAME TestFSIVLoadCalibrationParameters COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_common_code fsiv_load_calibration_parameters WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data)
add_test(NAME TestFSIVComputeCameraPose COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_common_code fsiv_compute_camera_pose WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data)
add_test(NAME TestFSIVProjectImage COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_common_code fsiv_project_image WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data)
