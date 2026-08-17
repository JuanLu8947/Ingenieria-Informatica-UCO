#pragma once
#include <opencv2/core.hpp>

/**
 * @brief Return a Gaussian filter.
 * @param[in] r is the filter's radius.
 * @return the filter.
 * @pre r>0;
 * @post ret_v.type()==CV_32FC1
 * @post retV.rows==retV.cols==2*r+1
 * @post (abs(cv::sum(retV)-1.0)<1.0e-6
 */
cv::Mat fsiv_create_gaussian_filter(const int r);

/**
 * @brief Expand an image with zero padding.
 * @param[in] in is the input image.
 * @param[in] r is the window's radius to expand.
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
 * @param[in] in is the input image.
 * @param[in] r is the window's radius to expand.
 * @return the expanded image.
 * @pre !in.empty()
 * @pre r>0
 * @post retV.type()==in.type()
 * @post retV.rows==in.rows+2*r
 * @post retV.cols==in.cols+2*r
 */
cv::Mat fsiv_circular_expansion(cv::Mat const &in, const int r);

/**
 * @brief Create a four points Laplacian filter.
 * @return the filter.
 * @post retval.type()==CV_32FC1
 */
cv::Mat fsiv_create_lap4_filter();

/**
 * @brief Create a eight points Laplacian filter.
 * @return the filter.
 * @post retval.type()==CV_32FC1
 */
cv::Mat fsiv_create_lap8_filter();

/**
 * @brief Create a Difference Of Gaussian filter.
 * @param r1,
 * @param r2 are the radius of the two gaussian filters.
 * @return the filter.
 * @pre r1>0 && r1<r2
 * @post retval.type()==CV_32FC1
 */
cv::Mat fsiv_create_dog_filter(int r1, int r2);

/**
 * @brief Create a sharpening filter.
 * @param filter_type specify what type of Laplacian filter to use: 0->LAP_4, 1->LAP_8, 2->DoG.
 * @param r1 if filter type is 2 (DoG), r1 is the radius for the first Gaussian filter.
 * @param r2 if filter type is 2 (DoG), r2 is the radius for the second Gaussian filter.
 * @return the filter.
 * @pre filter_type in {0,1,2}
 * @pre filter_type!=2 || r1<r2
 * @post retval.type()==CV_32FC1
 */
cv::Mat fsiv_create_sharpening_filter(int filter_type, int r1, int r2);

/**
 * @brief Do a sharpening enhance to an image.
 * @param img is the input image.
 * @param filter_type is the sharpening filter to use: 0->LAP_4, 1->LAP_8, 2->DOG.
 * @param r1 if filter type is DOG, is the radius of first Gaussian filter.
 * @param r2 if filter type is DOG, is the radius of second Gaussian filter.
 * @param circular if it is true, use circular convolution.
 * @return the enhanced image.
 * @pre filter_type in {0,1,2}.
 * @pre 0<r1<r2
 */
cv::Mat fsiv_image_sharpening(const cv::Mat &in, int filter_type,
                              int r1, int r2, bool circular);
