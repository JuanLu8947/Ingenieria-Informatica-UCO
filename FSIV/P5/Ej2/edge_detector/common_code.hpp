#pragma once

#include <opencv2/core/core.hpp>

/**
 * @brief Compute image derivatives.
 *
 * @param[in] img input image
 * @param[out] dx x axis derivate
 * @param[out] dy y axis derivate
 * @param[in] g_r gaussian radio used to do a gaussian blur.
 * @param[in] s_ap Sobel kernel size.
 *
 */
void fsiv_compute_derivate(cv::Mat const &img, cv::Mat &dx, cv::Mat &dy, int g_r,
                           int s_ap = 1);

/**
 * @brief Compute gradient magnitude.
 *
 * @param[in] dx x axis derivate.
 * @param[in] dy x axis derivate.
 * @param[out] gradient magnitude.
 */
void fsiv_compute_gradient_magnitude(cv::Mat const &dx, cv::Mat const &dy,
                                     cv::Mat &gradient);

/**
 * @brief Compute gradient histogram.
 *
 * @param[in] gradient magnitude.
 * @param[in] n_bins number of histogram's bins.
 * @param[out] hist the gradient histogram.
 * @param[out] max_gradient maximum gradient value.
 */
void fsiv_compute_gradient_histogram(cv::Mat const &gradient, int n_bins,
                                     cv::Mat &hist, float &max_gradient);

/**
 * @brief Compute the histogram idx corresponding with a percentile.
 *
 * @param[in] hist the histogrman.
 * @param[in] percentile the percentile to find.
 * @return the histogram index corresponding with the percentile.
 */
int fsiv_compute_histogram_percentile(cv::Mat const &hist, float percentile);

/**
 * @brief Maps from integer range [0, nbins) to float range [min_value, max_value).
 *
 * @param[in] idx input index.
 * @param[in] n_bins number of bins.
 * @param[in] max_value maximum output range value.
 * @param[in] min_value minimum output range value.
 * @return the mapped value.
 */
float fsiv_histogram_idx_to_value(int idx, int n_bins, float max_value, float min_value = 0.0);

/**
 * @brief Thin the edge map.
 *
 * @param[in] edge_map the input edge map.
 * @return the thinned edge map.
 * @pre edge_map is of type CV_8UC1.
 * @post thinned_edge_map is of type CV_8UC1.
 * @post thinned_edge_map has the same size as edge_map.
 */
cv::Mat fsiv_thinning_edge_map(cv::Mat const &edge_map);

/**
 * @brief Detect borders using the percentile method.
 *
 * @param[in] gradient input magnitude.
 * @param[out] edges the detected borders.
 * @param[in] th is the gradient percentile used as threshold.
 * @param[in] n_bins number of histogram's bins.
 */
void fsiv_percentile_edge_detector(cv::Mat const &gradient, cv::Mat &edges,
                                   float th, int n_bins = 100);

/**
 * @brief Detect borders using the Otsu method.
 *
 * @param[in] gradient input magnitude.
 * @param[out] edges the detected borders.
 */
void fsiv_otsu_edge_detector(cv::Mat const &gradient, cv::Mat &edges);

/**
 * @brief Detect borders using the Canny method.
 *
 * @param[in] gradient input magnitude.
 * @param[out] edges the detected borders.
 * @param[in] th1 is the gradient percentile used as low threshold.
 * @param[in] th2 is the gradient percentile used as high threshold.
 * @param[in] n_bins number of histogram's bins.
 */
void fsiv_canny_edge_detector(cv::Mat const &dx, cv::Mat const &dy,
                              cv::Mat &edges, float th_low = 0.2, float th_high = 0.8, int n_bins = 100);

/**
 * @brief Computes the ground truth image from a consensus image.
 *
 * The value of a pixel in the consensus image means the number of experts who think that pixel is an "edge".
 *
 * @param consensus_img is the consensus image.
 * @param min_consensus is the minimum consensus value to consider a pixel as edge. Is a value in [0, 100].
 * @param gt is the computed ground truth image.
 */
void fsiv_compute_ground_truth_image(cv::Mat const &consensus_img, float min_consensus, cv::Mat &gt);

/**
 * @brief Compute the edge detector confusion matrix.
 *
 * A confusion matrix is a 2x2 matrix where:
 *   - The first row represents the ground truth: [non-edge, edge].
 *   - The second row represents the predicted edges: [non-edge, edge].
 *
 * A pixel is classified as edge if its value is non-zero.
 *
 * @param[in] gt is the ground truth.
 * @param[in] pred are the predicted edges.
 * @param[out] cm the confusion matrix.
 */
void fsiv_compute_edge_detector_confusion_matrix(cv::Mat const &gt, cv::Mat const &pred,
                                                 cv::Mat &cm);

/**
 * @brief Compute the sensitivity score
 *
 * @param cm the confusion matrix.
 * @return the score.
 */
float fsiv_compute_sensitivity(cv::Mat const &cm);

/**
 * @brief Compute the precision score
 *
 * @param cm the confusion matrix.
 * @return the score.
 */
float fsiv_compute_precision(cv::Mat const &cm);

/**
 * @brief Compute the F1 score
 *
 * @param cm the confusion matrix.
 * @return the score.
 */
float fsiv_compute_F1_score(cv::Mat const &cm);