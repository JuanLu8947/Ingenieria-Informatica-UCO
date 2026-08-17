/**
 * @file common_code.hpp
 * @author Francisco José Madrid Cuevas (fjmadrid@uco.es)
 * @brief Utility functions to calibrate/undistort a camera.
 * @version 0.1
 * @date 2024-09-24
 *
 * @copyright Copyright (c) 2024-
 *
 */
#pragma once

#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

/**
 * @brief Generate a 3d point vector with the inner corners of a calibration board.
 * @param board_size is the inner points board geometry (cols x rows).
 * @param square_size is the size of the squares.
 * @return a vector of 3d points with the corners.
 * @post ret_v.size()==(cols*rows)
 */
std::vector<cv::Point3f> fsiv_generate_3d_calibration_points(const cv::Size &board_size,
                                                             float square_size);

/**
 * @brief Find a calibration chessboard and compute the refined coordinates of the inner corners.
 * @param img is the image where finding out.
 * @param board_size is the inners board points geometry.
 * @param[out] corner_points save the refined corner coordinates if the board was found.
 * @param[in] win_r is the window's radius used to optimize corner points.
 * @param[in] zz_r is the zero zone window's radius used to optimize corner points.
 * @param[in] tcr is the criteria used to stop the optimization.
 * @return true if the board was found.
 * @pre img.type()==CV_8UC3
 * @post !retval || corner_points.size()==(board_size.width*board_size.height)
 */
bool fsiv_find_chessboard_corners(const cv::Mat &img, const cv::Size &board_size,
                                  std::vector<cv::Point2f> &corner_points,
                                  int win_r = 5, int zz_r = -1, cv::TermCriteria const &tcr = cv::TermCriteria());
/**
 * @brief Calibrate a camara given the a sequence of 3D points and its correspondences in the plane image.
 * @param[in] _2d_points are the sequence of 2d corners detected per view.
 * @param[in] _3d_points are the corresponding 3d points per view.
 * @param[in] camera_size is the camera geometry in pixels.
 * @param[out] camera_matrix is the calibrated camera matrix.
 * @param[out] dist_coeffs is the calibrated distortion coefficients.
 * @param[out] rvects is not null, it will save the rotation matrix of each view.
 * @param[out] tvects is not null, it will save the translation vector of each view.
 * @return the reprojection error of the calibration.
 */
float fsiv_calibrate_camera(
    const std::vector<std::vector<cv::Point2f>> &_2d_points,
    const std::vector<std::vector<cv::Point3f>> &_3d_points,
    const cv::Size &camera_size,
    cv::Mat &camera_matrix,
    cv::Mat &dist_coeffs,
    std::vector<cv::Mat> *rvecs = nullptr,
    std::vector<cv::Mat> *tvecs = nullptr);

/**
 * @brief Project the 3D Camera Coordinate system on the image.
 * The X axis will be draw in red, the Y axis in green and the Z axis in blue.
 * @param[in,out] img the image where projecting the axes.
 * @param[in] camera_matrix is the camera matrix.
 * @param[in] dist_coeffs are the distortion coefficients.
 * @param[in] rvec is the rotation vector.
 * @param[in] tvec is the translation vector.
 * @param[in] size is the length in word coordinates of each axis.
 * @param[in] line_width used to draw the axis.
 */
void fsiv_draw_axes(cv::Mat &img,
                    const cv::Mat &camera_matrix, const cv::Mat &dist_coeffs,
                    const cv::Mat &rvec, const cv::Mat &tvec,
                    const float size, const int line_width = 1);

/**
 * @brief Save the calibration parameters in a file.
 * The labels to save are:
 *
 * image-width (int)
 * image-height (int)
 * error (float/double)
 * camera-matrix (Matrix 3x3 CV_64F)
 * distortion-coefficients (Matrix 1x5 CV_64F)
 * rvec (Matrix 3x1 CV_64F)
 * tvec (Matrix 3x1 CV_64F)
 *
 * @param[in|out] fs is a file storage object to write the data.
 * @param[in] camera_size is the camera geometry in pixels.
 * @param[in] error is the calibration error.
 * @param[in] camera_matrix is the camera matrix.
 * @param[in] dist_coeffs are the distortion coefficients.
 * @param[in] rvec is the rotation vector.
 * @param[in] tvec is the translation vector.
 * @pre fs.isOpened()
 * @post fs.isOpened()
 */
void fsiv_save_calibration_parameters(cv::FileStorage &fs,
                                      const cv::Size &camera_size,
                                      float error,
                                      const cv::Mat &camera_matrix,
                                      const cv::Mat &dist_coeffs,
                                      const cv::Mat &rvec = cv::Mat::zeros(3, 1, CV_64FC1),
                                      const cv::Mat &tvec = cv::Mat::zeros(3, 1, CV_64FC1));

/**
 * @brief Compute the pose of a camara giving a view of the board.
 * @param[in] _3dpoints are the WCS 3D points of the board.
 * @param[in] _2dpoints are the refined corners detected.
 * @param[in] camera_matrix is the camera matrix.
 * @param[in] dist_coeffs are the distortion coefficients.
 * @param[out] rvec is the computed rotation vector.
 * @param[out] tvec is the computed translation vector.
 */
void fsiv_compute_camera_pose(const std::vector<cv::Point3f> &_3dpoints,
                              const std::vector<cv::Point2f> &_2dpoints,
                              const cv::Mat &camera_matrix,
                              const cv::Mat &dist_coeffs,
                              cv::Mat &rvec,
                              cv::Mat &tvec);

/**
 * @brief Load the calibration parameters from a file.
 * The file will have the following labels:
 *
 * image-width (int)
 * image-height (int)
 * error (float/double)
 * camera-matrix (Matrix 3x3 CV_64F)
 * distortion-coefficients (Matrix 1x5 CV_64F)
 * rvec (Matrix 3x1 CV_64F)
 * tvec (Matrix 3x1 CV_64F)
 *
 * @param[in|out] fs is a file storage object to write the data.
 * @param[out] camera_size is the camera geometry in pixels.
 * @param[out] error is the calibration error.
 * @param[out] camera_matrix is the camera matrix.
 * @param[out] dist_coeffs are the distortion coefficients.
 * @param[out] rvec is the rotation vector.
 * @param[out] tvec is the translation vector.
 * @pre fs.isOpened()
 * @post fs.isOpened()
 */
void fsiv_load_calibration_parameters(cv::FileStorage &fs,
                                      cv::Size &camera_size,
                                      float &error,
                                      cv::Mat &camera_matrix,
                                      cv::Mat &dist_coeffs,
                                      cv::Mat &rvec,
                                      cv::Mat &tvec);

/**
 * @brief Correct the len's distorntions of an image.
 * @param[in] input the distorted image.
 * @param[out] output the corrected image.
 * @param[in] camera_matrix is the camera matrix.
 * @param[in] dist_coeffs are the distortion coefficients.
 */
void fsiv_undistort_image(const cv::Mat &input, cv::Mat &output,
                          const cv::Mat &camera_matrix,
                          const cv::Mat &dist_coeffs);
/**
 * @brief Correct the len's distortions from a input video stream.
 * @param[in|out] input is the input distorted video stream.
 * @param[out] output is the corrected output video stream.
 * @param[in] camera_matrix is the camera matrix.
 * @param[in] dist_coeffs are the distortion coefficients.
 * @param[in] interp specifies the interpolation method to use.
 * @param[in] input_wname if it is not nullptr, show input frames.
 * @param[in] output_wname if it is not nullptr, show ouput frames.
 * @param[in] fps is the frame per seconds to wait between frames (when frames are shown). Value 0 means dont wait.
 * @pre input.isOpened()
 * @pre output.isOpened()
 * @post input.isOpened()
 * @post output.isOpened()
 */
void fsiv_undistort_video_stream(cv::VideoCapture &input_stream,
                                 cv::VideoWriter &output_stream,
                                 const cv::Mat &camera_matrix,
                                 const cv::Mat &dist_coeffs,
                                 const int interp = cv::INTER_LINEAR,
                                 const char *input_wname = nullptr,
                                 const char *output_wname = nullptr,
                                 double fps = 0.0);
