/**
 * @file common_code.hpp
 * @author Francisco José Madrid Cuevas (fjmadrid@uco.es)
 * @brief Utility module to do an Unsharp Mask image enhance.
 * @version 0.1
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024-
 *
 */
#pragma once
#include <opencv2/core.hpp>

/**
 * @brief Return a box filter.
 * @arg[in] r is the filter's radius.
 * @return the filter.
 * @pre r>0;
 * @post ret_v.type()==CV_32FC1
 * @post retV.rows==retV.cols==2*r+1
 * @post (abs(cv::sum(retV)-1.0)<1.0e-6
 */
cv::Mat fsiv_create_box_filter(const int r);

/**
 * @brief Return a Gaussian filter.
 * @arg[in] r is the filter's radius.
 * @return the filter.
 * @pre r>0;
 * @post ret_v.type()==CV_32FC1
 * @post retV.rows==retV.cols==2*r+1
 * @post (abs(cv::sum(retV)-1.0)<1.0e-6
 */
cv::Mat fsiv_create_gaussian_filter(const int r);

/**
 * @brief Expand an image with zero padding.
 * @arg[in] in is the input image.
 * @arg[in] r is the window's radius to expand.
 * @return the expanded image.
 * @pre !in.empty()
 * @pre r>0
 * @post retV.type()==in.type()
 * @post retV.rows==in.rows+2*r
 * @post retV.cols==in.cols+2*r
 */
cv::Mat fsiv_fill_expansion(cv::Mat const &in, const int r);

/**
 * @brief Circular expansion of an image.
 * @arg[in] in is the input image.
 * @arg[in] r is the window's radius to expand.
 * @return the expanded image.
 * @pre !in.empty()
 * @pre r>0
 * @post retV.type()==in.type()
 * @post retV.rows==in.rows+2*r
 * @post retV.cols==in.cols+2*r
 */
cv::Mat fsiv_circular_expansion(cv::Mat const &in, const int r);

/**
 * @brief Compute the digital correlation between two images.
 * @warning Code from scracth. Use cv::filter2D() is not allowed.
 * @arg[in] in is the input image.
 * @arg[in] filter is the filter to be applied.
 * @pre !in.empty() && !filter.empty()
 * @pre in.type()==CV_32FC1 && filter.type()==CV_32FC1.
 * @post ret.type()==CV_32FC1
 * @post ret.rows == in.rows-2*(filters.rows/2)
 * @post ret.cols == in.cols-2*(filters.cols/2)
 */
cv::Mat fsiv_filter2D(cv::Mat const &in, cv::Mat const &filter);

/**
 * @brief Combine two images using weights.
 * @param src1 first image.
 * @param src2 second image.
 * @param a weight for first image.
 * @param b weight for the second image.
 * @return a * src1 + b * src2
 * @pre src1.type()==src2.type()
 * @pre src1.rows==src2.rows
 * @pre src1.cols==src2.cols
 * @post retv.type()==src2.type()
 * @post retv.rows==src2.rows
 * @post retv.cols==src2.cols
 */
cv::Mat fsiv_soft_combine_images(const cv::Mat src1, const cv::Mat src2,
                                 double a, double b);
/**
 * @brief Apply an unsharp mask enhance to the input image.
 * @arg[in] in is the input image.
 * @arg[in] g is the enhance's gain.
 * @arg[in] r is the window's radius.
 * @arg[in] filter_type specifies which filter to use. 0->Box, 1->Gaussian.
 * @arg[in] circular specifies if it is true, it be used circular expansion to do the convolution, else it is used zero padding.
 * @arg[out] unsharp_mask if it is not nullptr, save the unsharp mask used.
 * @pre !in.empty()
 * @pre in.type()==CV_32FC1
 * @pre g>=0.0
 * @pre r>0
 * @pre filter_type is {0, 1}
 * @post ret_v.rows==in.rows && ret_v.cols==in.cols
 * @post ret_v.type()==CV_32FC1
 */
cv::Mat fsiv_usm_enhance(cv::Mat const &in, double g = 1.0, int r = 1,
                         int filter_type = 0, bool circular = false,
                         cv::Mat *unsharp_mask = nullptr);
