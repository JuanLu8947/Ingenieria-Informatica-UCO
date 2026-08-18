/**
 * @file city.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <exception>
#include <iostream>
#include <string>

#include "item.hpp"

/**
 * @brief Define a data associated to a city.
 */
struct City_data
{
    std::string name;
    float latitude;
    float longitude;

    City_data(const std::string &name_ = "", float latitude_ = 0.0f, float longitude_ = 0.0f)
        : name(name_), latitude(latitude_), longitude(longitude_)
    {
    }

    bool operator<(const City_data &o) const
    {
        return name < o.name;
    }

    bool operator==(const City_data &o) const
    {
        return name == o.name;
    }
};

/**
 * @brief Fold the city data.
 * @param out the output stream.
 * @param city the city's data.
 * @return the output stream.
 */
std::ostream &operator<<(std::ostream &out, const City_data &city);

/**
 * @brief Unfold the city's data from an input stream.
 * @param in the input stream.
 * @param city the city's data unfolded.
 * @return the input stream.
 */
std::istream &operator>>(std::istream &in, City_data &city);

/**
 * @brief A City.
 */
using City = Item<City_data, std::string>;

/**
 * @brief Template specialization to get the city's key.
 * @return the key.
 */
template <>
inline std::string City::key() const
{
    return data_.name;
}

/**
 * @brief Compute the the distance between two cities given their locations.
 */
double distance(const City &s, const City &d);
