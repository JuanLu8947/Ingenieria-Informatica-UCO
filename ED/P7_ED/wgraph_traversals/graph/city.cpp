/**
 * @file city.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#define _USE_MATH_DEFINES // for C++ math constants
#include <cmath>
#include "city.hpp"

/** @brief convert from degrees to radians. */
inline static
double
to_rad(const double a)
{
    return M_PI/180.0 * a;
}

double
distance(const City& s, const City& d)
{
    const double EARTH_RADIX = 6378.0; //Km.
    const double dif_latitude = to_rad(d.data_.latitude - s.data_.latitude);
    const double dif_longitude = to_rad(d.data_.longitude - s.data_.longitude);

    const double a = std::pow(std::sin(dif_latitude/2.0), 2.0) +
              std::cos(to_rad(s.data_.latitude))*
              std::cos(to_rad(d.data_.latitude))*
              std::pow(std::sin(dif_longitude/2.0),2.0);
    const double c = 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0-a));
    return c*EARTH_RADIX;
}

/**
 * @brief unfold a city's data from an input stream.
 */
std::istream&
operator>>(std::istream& in, City_data & city)
{
    in >> city.name >> city.latitude >> city.longitude;
    return in;
}


/**
 * @brief fold a City to an output stream.
 */
std::ostream&
operator << (std::ostream& out, const City_data& city)
{
    out << city.name << ' ' << city.latitude << ' ' << city.longitude;
    return out;
}



