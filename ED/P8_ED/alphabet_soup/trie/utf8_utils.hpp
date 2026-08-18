/**
 * @file utf8_utils.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#pragma once

#include <iostream>
#include <string>

/**
 * @brief Computes the length of the utf-8 char encoding sequence given the first byte.
 *
 * @param first_byte the first byte of the utf-8 sequence.
 * @return the length of the utf-8 char in bytes or -1 it is not a valid UTF-8 sequence.
 */
int utf8_char_length(unsigned char first_byte);

/**
 * @brief Get the utf-8 char from a utf-8 string.
 *
 * @param str string to analyze asuming UTF-8 encoding.
 * @param idx position of the character into the input string.
 * @return substring with the utf-8 char extracted or "" if it could not be extracted.
 */
std::string get_utf8_char(const std::string &str, size_t idx);

/**
 * @brief Get a utf-8 char from an input stream.
 *
 * @param in input stream to read the character.
 * @return string with the utf-8 char extracted or "" if it could not be extracted.
 */
std::string get_utf8_char(std::istream &in);