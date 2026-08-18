/**
 * @file ip_utils.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include "ip_utils.hpp"
#include <sstream>
#include <string>
#include <algorithm>

IP::IP() : bytes({0, 0, 0, 0})
{
}
IP::IP(std::uint8_t a, std::uint8_t b, std::uint8_t c, std::uint8_t d)
    : bytes({a, b, c, d})
{
}

bool IP::operator==(IP const &b) const
{
    return bytes == b.bytes;
}

bool IP::operator<(IP const &b) const
{
    return bytes < b.bytes;
}

std::ostream &
operator<<(std::ostream &out, const IP &ip)
{
    // TODO
    // Remember: we want to output the ascii code, not the char.
    out << static_cast<int>(ip.bytes[0]) << "."
    << static_cast<int>(ip.bytes[1]) << "."
    << static_cast<int>(ip.bytes[2]) << "."
    << static_cast<int>(ip.bytes[3]);
    /*
    ·Este operador permite imprimir una dirección IP en formato legible (por ejemplo, 192.168.0.1).
    ·static_cast<int>: Convierte cada byte de la dirección IP (almacenado como std::uint8_t) a un entero para que se imprima como su valor numérico ASCII, no como un carácter.
    ·Los bytes se separan con puntos (.) para seguir el formato estándar de las direcciones IP.
    */
    //
    return out;
}

std::istream &
operator>>(std::istream &in, IP &ip) noexcept(false)
{
    // TODO
    // Hint: you can use a std::istringstream to convert from text to uint8_t.
    // Hint: you can use the std::replace algorithm to replace '.' by ' '.
    // Remember: if a wrong format is detected, throw an runtime_error exception.
    std::string input;
    in >> input;

    std::replace(input.begin(), input.end(), '.', ' ');

    std::istringstream iss(input);
    int a, b, c, d;

    if (!(iss >> a >> b >> c >> d) || a < 0 || a > 255 || b < 0 || b > 255 || c < 0 || c > 255 || d < 0 || d > 255)
    {
        throw std::runtime_error("Ip: wrong input format.");
    }

    ip = IP(static_cast<std::uint8_t>(a),
            static_cast<std::uint8_t>(b),
            static_cast<std::uint8_t>(c),
            static_cast<std::uint8_t>(d));
    /*
    ·Este operador permite leer una dirección IP desde un flujo de entrada (por ejemplo, desde el teclado o un archivo).
    ·Pasos principales:
     ·Leer la entrada como una cadena: Se almacena la dirección IP en formato de texto (por ejemplo, 192.168.0.1).
     ·Reemplazar los puntos (.) por espacios ( ): Esto facilita la conversión de los valores numéricos usando un std::istringstream.
     ·Convertir los valores a enteros: Se extraen los cuatro octetos de la dirección IP y se verifican que estén en el rango [0, 255].
     ·Lanzar una excepción si el formato es incorrecto: Si la conversión falla o los valores están fuera de rango, se lanza una excepción std::runtime_error.
     ·Asignar los valores a la estructura IP: Se convierten los enteros a std::uint8_t y se almacenan en la estructura.
    */
    //
    return in;
}

std::uint64_t
ip_to_int(const IP &ip)
{
    std::uint64_t ret_val = 0l;
    // TODO
    // Remember: casting to 64 bits unsigned integer to do not loss bits.
    // Hint: mult by 2^n means shift to left n bits.
    ret_val = (static_cast<std::uint64_t>(ip.bytes[0]) << 24) +
              (static_cast<std::uint64_t>(ip.bytes[1]) << 16) +
              (static_cast<std::uint64_t>(ip.bytes[2]) << 8) +
              (static_cast<std::uint64_t>(ip.bytes[3]));
    /*
    ·Convierte una dirección IP en su representación numérica de 64 bits.
    ·Pasos principales:
     ·Convertir cada byte a un entero de 64 bits: Se utiliza static_cast<std::uint64_t>std::uint64_t para evitar pérdida de bits.
     ·Desplazar los bytes a sus posiciones correspondientes:
      ·El primer byte se desplaza 24 bits a la izquierda.
      ·El segundo byte se desplaza 16 bits a la izquierda.
      ·El tercer byte se desplaza 8 bits a la izquierda.
      ·El cuarto byte no se desplaza.
     ·Sumar los valores desplazados: Esto combina los bytes en un único número de 64 bits.
    ·Ejemplo:
     ·Para la dirección IP 192.168.0.1:
      ·192 << 24 = 3221225472
      ·168 << 16 = 11010048
      ·0 << 8 = 0
      ·1 = 1
      ·Resultado: 3232235521.
    */
    //
    return ret_val;
}
