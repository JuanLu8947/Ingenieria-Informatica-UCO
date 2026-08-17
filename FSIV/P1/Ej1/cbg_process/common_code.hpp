#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

/**
 * @brief Convierte una imagen con tipo byte a flotante [0,1].
 * @param img imagen de entrada.
 * @return la imagen de salida.
 * @warning la imagen de entrada puede ser monocroma o RGB.
 */
cv::Mat fsiv_convert_image_byte_to_float(const cv::Mat &img);

/**
 * @brief Convierte una imagen con tipo float [0,1] a byte [0,255].
 * @param img imagen de entrada.
 * @return la imagen de salida.
 * @warning la imagen de entrada puede ser monocroma o RGB.
 */
cv::Mat fsiv_convert_image_float_to_byte(const cv::Mat &img);

/**
 * @brief Convierte una imagen en color BGR a HSV.
 * @param img imagen de entrada.
 * @return la imagen de salida.
 */
cv::Mat fsiv_convert_bgr_to_hsv(const cv::Mat &img);

/**
 * @brief Convierte una imagen en color HSV a BGR.
 * @param img imagen de entrada.
 * @return la imagen de salida.
 */
cv::Mat fsiv_convert_hsv_to_bgr(const cv::Mat &img);

/**
 * @brief Realiza un control del brillo/contraste/gamma de la imagen.
 *
 * El proceso sería:
 *
 * O = c * I^g + b
 *
 * Si la imagen es RGB y el flag only_luma es true, se utiliza el espacio HSV
 * para procesar sólo el canal V (luma).
 *
 * @param img  imagen de entrada.
 * @param contrast controla el ajuste del contraste.
 * @param brightness controla el ajuste del brillo.
 * @param gamma controla el ajuste de la gamma.
 * @param only_luma si es true sólo se procesa el canal Luma.
 * @return la imagen procesada.
 */
cv::Mat fsiv_cbg_process(const cv::Mat &img,
                         double contrast = 1.0, double brightness = 0.0, double gamma = 1.0,
                         bool only_luma = true);
