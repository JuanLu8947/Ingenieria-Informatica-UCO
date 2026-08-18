/**
 * @file matrix.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#include <string>
#include "matrix.hpp"

template <>
Matrix<float>::Matrix(std::istream &input) noexcept(false)
{
    std::string token;

    if (!(input >> token))
        throw std::runtime_error("Wrong matrix format");
    if (token == "[")
    {
        size_t rs, cs;
        if (!(input >> rs >> cs))
            throw std::runtime_error("Wrong matrix format");
        if (!(rs > 0 && cs > 0))
            throw std::runtime_error("Wrong matrix format");
        resize(rs, cs, 0.0f);
        for (size_t r = 0; r < rows(); ++r)
            for (size_t c = 0; c < cols(); ++c)
            {
                if (!(input >> token))
                    throw std::runtime_error("Wrong matrix format");
                float v;
                size_t last_c;
                v = std::stof(token, &last_c); // handle [+|-]inf and [+|-]nan
                if (last_c != token.size())
                    throw std::runtime_error("Wrong matrix format");
                set(r, c, v);
            }
        if (!(input >> token) || (token != "]"))
            throw std::runtime_error("Wrong matrix format");
    }
    else if (token == "[]")
        resize(0, 0, 0.0f);
    else
        throw std::runtime_error("Wrong matrix format");
}
