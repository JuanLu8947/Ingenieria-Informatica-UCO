/**
 * @file common_code.hpp
 * @author Francisco José Madrid Cuevas (fjmadrid@uco.es)
 * @brief Utility functions for the image equalization process.
 * @date 2024-09-12
 *
 * @copyright Copyright (c) 2024-
 *
 */
#pragma once

#include <opencv2/core/core.hpp>

/**
 * @brief Compute the histogram of an image.
 *
 * @param img the input image.
 * @return the histogram.
 * @pre in.type()==CV_8UC1
 *
 */
cv::Mat fsiv_compute_image_histogram(const cv::Mat &in);

/**
 * @brief Normalize the histogram con L1=1.0
 * @param hist the histogram to be normalized.
 * @pre hist.type()==CV_32FC1
 * @pre hist.rows==256 && hist.cols==1
 * @post hist.type()==CV_32FC1
 * @post hist.rows==256 && hist.cols==1
 * @post abs(sum(hist)[0]-1.0)<=1.0e-6
 */
void fsiv_normalize_histogram(cv::Mat &hist);

/**
 * @brief Compute the accumulated histogram.
 * @param hist the histogram to be accumulated.
 * @pre hist.type()==CV_32FC1
 * @pre hist.rows==256 && hist.cols==1
 * @post hist.type()==CV_32FC1
 * @post hist.rows==256 && hist.cols==1
 */
void fsiv_accumulate_histogram(cv::Mat &hist);

/**
 * @brief Clip an histograma to a clipping level.
 *
 * The residual histogram area will be equally redistribute in all
 * the histogram's bins.
 *
 * @param h is the histogram to be clipped.
 * @param cl is the clipping level.
 */
void fsiv_compute_clipped_histogram(cv::Mat &h, float cl);

/**
 * @brief Find actual the clipping value for an histogram.
 * The actual clipping value P is a value such that
 * \math{P + S/h_bins = CL} where CL is the
 * desired clipping value and S is the residual area of the clipped histogram
 * to be redistributed.
 *
 * The desired CL value is computed as
 * \math{s * histogram's area / histogram's bins}
 *
 * @param h the histogram.
 * @param s the slope factor that controls the contrast limitation.
 * @return the actual clipping value.
 * @warning Its assumed that the histogram is not normalized.
 */
float fsiv_compute_actual_clipping_histogram_value(const cv::Mat &h, float s);

/**
 * @brief Create a transform function to do a contrast limited equalization.
 * @param hist is the image histogram.
 * @param s is the slope factor to control the contrast limitation. A value < 1.0 means do not do contrast limitation.
 * @return the transform function.
 * @pre hist.type()==CV_32FC1
 * @pre hist.rows==256 && hist.cols==1
 * @post retval.type()==CV_8UC1
 * @post retval.rows==256 && retval.cols==1
 */
cv::Mat fsiv_create_equalization_lookup_table(const cv::Mat &hist,
                                              float s);

/**
 * @brief Aplica una "lookup table"
 * @param in la imagen de entrada.
 * @param lkt la tabla.
 * @param out la imgen de salida.
 * @return la imagen de salida.
 * @pre in.type()==CV_8UC1
 * @pre lkt.type()==CV_8UC1
 * @pre lkt.rows==256 && lkt.cols==1
 * @pre out.empty() || (out.type()==CV_8UC1 && out.rows==in.rows && out.cols==in.cols)
 * @post out.rows ==in.rows && out.cols==in.cols && out.type()==in.type()
 */
cv::Mat fsiv_apply_lookup_table(const cv::Mat &in, const cv::Mat &lkt,
                                cv::Mat &out);
