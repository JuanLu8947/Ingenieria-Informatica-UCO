/**
 * @file utf8_utils.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include <iostream>
#include <string>

#include "utf8_utils.hpp"

int utf8_char_length(unsigned char first_byte)
{
    int length = 0;
    if (first_byte <= 0x7F)
        length = 1; // Char ASCII de 1 byte
    else if (first_byte >= 0xC0 && first_byte <= 0xDF)
        length = 2; // Char of 2 bytes
    else if (first_byte >= 0xE0 && first_byte <= 0xEF)
        length = 3; // Char of 3 bytes
    else if (first_byte >= 0xF0 && first_byte <= 0xF4)
        length = 4; // Char of 4 bytes
    else
        length = -1; // Invalid UTF-8 sequence.
    return length;
}

std::string
get_utf8_char(const std::string &str, size_t idx)
{
    std::string utf8_char = "";
    int length = utf8_char_length(static_cast<unsigned char>(str[idx]));

    if (length > 0 && (idx + static_cast<size_t>(length)) <= str.length())
        utf8_char = str.substr(idx, length);

    return utf8_char;
}

/**
 * @brief Get a utf8 char object from an input stream.
 *
 * @param in is the input stream to read the character.
 * @return utf8 string with the character extracted.
 */
std::string
get_utf8_char(std::istream &in)
{
    std::string utf8_char = "";
    char byte;
    if (in.get(byte))
    {
        int length = utf8_char_length(static_cast<unsigned char>(byte));
        if (length > 0)
        {
            utf8_char = byte;
            for (int i = 1; i < length && in; i++)
            {
                in.get(byte);
                utf8_char += byte;
            }
        }
    }
    return utf8_char;
}
