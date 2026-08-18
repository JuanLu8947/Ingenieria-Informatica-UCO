/**
 * @file ip_utils.hpp
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
#include <cstdint>
#include <array>
#include <memory>

/**
 * @brief Represent a IPv4 address.
 */
struct IP
{
    /**
     * @brief Default constructor.
     */
    IP();

    /**
     * @brief Constructor.
     */
    IP(std::uint8_t a, std::uint8_t b, std::uint8_t c, std::uint8_t d);

    /**
     * @brief Is b ip address b equal to this?.
     */
    bool operator==(IP const &b) const;

    /**
     * @brief Is b ip address b less than this?
     * A lexicographical order is check.
     */
    bool operator<(IP const &b) const;

    /**
     * The ip bytes.
     * example if the ip is "150.214.110.3":
     * bytes[0]=150, bytes[1]=214, bytes[2]=110, bytes[3]=3
     */
    std::array<std::uint8_t, 4> bytes;
};

/**
 * @brief output a ip in text format.
 */
std::ostream &operator<<(std::ostream &out, const IP &ip);

/**
 * @brief load an IPv4 address from a text input stream.
 * @throw std::runtime_error("Ip: wrong input format.") in case of input error.
 */
std::istream &operator>>(std::istream &in, IP &ip) noexcept(false);

/**
 * @brief Convert an IP to its integer representation.
 *
 * @param ip is the ip to be converted.
 * @return the integer representation.
 */
std::uint64_t ip_to_int(const IP &ip);