#pragma once
#include <opencv2/core.hpp>

/**
 * @brief Convierte una imagen en color BGR a HSV.
 * @param img imagen de entrada.
 * @return la imagen de salida.
 */
cv::Mat fsiv_convert_bgr_to_hsv(const cv::Mat &img);

/**
 * @brief Realiza una combinación "hard" entre dos imágenes usando una máscara.
 * La imagen de salida tendrá los contenidos de la imagen primera donde la máscara
 * sea 255 y los de la segunda donde sea 0.
 * @param img1 la primera imagen.
 * @param img2 la segunda imagen.
 * @param mask la máscara 0 (img2) / 255 (img1).
 * @return la imagen resultante de la combinación.
 */
cv::Mat fsiv_combine_images(const cv::Mat &foreground, const cv::Mat &background,
                            const cv::Mat &mask);

/**
 * @brief Crea una máscara activando los píxeles que están dentro de un rango de tonos.
 * El rango de tonos se define en el espacio HSV con H en el
 * rango [chroma_key+-sensitivity] y S/V en [0,255].
 * @param bgr_img es la imagen de entrada (BGR 8bits.).
 * @param chroma_key es el valor del tono (hue) a utilizar como color clave.
 * @param sensitivity es el valor que permite ampliar el rango de tonos (hue +- sensitivity).
 * @return la máscara (0/255).
 */
cv::Mat fsiv_compute_chroma_key_mask(const cv::Mat &bgr_img,
                                     int chroma_key,
                                     int sensitivity);

/**
 * @brief Sustituye en fondo de una imagen por otra usando un color clave.
 * @param foreg imagen que representa el primer plano.
 * @param backg imagen que representa el fondo con el que rellenar.
 * @param hue tono del color usado como color clave.
 * @param sensitivity permite ampliar el rango de tono con hue +- sensitivity.
 * @param mask_out si no es nulo, se asigna la máscara calculada a *mask_out.
 * @return la imagen con la la composición.
 */
cv::Mat fsiv_apply_chroma_key(const cv::Mat &foreg, const cv::Mat &backg, int hue,
                              int sensitivity, cv::Mat *mask_out = nullptr);
