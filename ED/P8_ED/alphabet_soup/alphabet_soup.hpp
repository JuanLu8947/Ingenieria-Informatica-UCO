/**
 * @file alphabet_soup.hpp
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
#include <vector>
#include <cassert>

/** @brief Models an alfabet soup. */
class AlphabetSoup
{
public:
    /** @name Life cycle.*/
    /** @{*/

    /** @brief Default constructor. */
    AlphabetSoup();

    /**
     * @brief Construct a new Alphabet Soup object
     *
     * @param rows number of rows.
     * @param cols number of columns
     */
    AlphabetSoup(int rows, int cols);

    /** @}*/

    /** @name Observers.*/
    /** @{*/

    /** @brief how many rows there are?*/
    int rows() const;

    /** @brief how many columns there are?*/
    int cols() const;

    /** @brief Get the contents of a cell.
     * @pre 0<=row<rows()
     * @pre 0<=col<cols()
     */
    const std::string &cell(int r, int c) const;

    /**
     * @brief Get read only reference to a row of the soup.
     * @return a ro reference to the row.
     * @pre 0<=row<rows()
     */
    const std::vector<std::string> &row(int row) const;

    /** @} */

    /** @name Modifiers.*/
    /** @{*/

    /**
     * @brief set a row.
     * @pre 0<=row<rows()
     * @pre row_v.size()==cols()
     */
    void set_row(int row, const std::string &row_v) noexcept(false);

    /**
     * @brief set the content of a cell.
     * @pre 0<=row<rows()
     * @pre 0<=col<cols()
     * @pre v.size()==1
     */
    void set_cell(int row, int col, const std::string &v);

    /**
     * @brief resize the soup.
     * @post rows()==rows.
     * @post cols()==cols.
     * @post cell()==" " for all cells.
     */
    void resize(int rows, int cols);

    /** @} */

protected:
    std::vector<std::vector<std::string>> alphabet_soup_;
    int cols_;
};

/** @brief load a soup from an input stream.*/
std::istream &operator>>(std::istream &in, AlphabetSoup &soup) noexcept(false);

/** @brief output a soup to an output stream.*/
std::ostream &operator<<(std::ostream &in, AlphabetSoup const &soup);
