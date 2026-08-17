/**
 * @file clahe.hpp
 * @author Francisco José Madrid Cuevas (fjmadrid@uco.es)
 * @brief Implementation of the method Limited Contrast Adaptive Histogram Equalization.
 * @version 1.0
 * @date 2024-09-13
 *
 * @copyright Copyright (c) 2024-
 *
 */
#pragma once
#include <opencv2/core.hpp>

/**
 * @brief Do a contrast limited adaptive histogram equalization of an image.
 * @param in is the input image.
 * @param s is a factor that controls the contrast limitation. If \arg s < 1, do not apply such control.
 * @param r set the windows radius to do a local image equalization. If \arg r=0, a global equalization will be done.
 * @return The output image.
 */
cv::Mat fsiv_clahe(const cv::Mat &in, float s, int radius);