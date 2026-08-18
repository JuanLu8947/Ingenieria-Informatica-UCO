/**
 * @file matrix.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <cassert>
#include <exception>
#include <iostream>
#include <memory>
#include <valarray>

/**
 * @brief A matrix of scalar values.
 */
template <class T>
class Matrix
{
public:
    /** @name Makers*/
    /** @{*/

    /** @brief a reference to a matrix. **/
    typedef std::shared_ptr<Matrix<T>> Ref;

    /**
     * @brief Create an empty Matrix.
     */
    Matrix()
    {
        assert(is_empty());
    }

    /**
     * @brief Unfold a matrix from a input stream.
     * FORMAT
     * "[]"  if empty.
     * '[' <rows> <cols> <rows x cols values of type T> ']'
     * @param input the input stream.
     * @throw std::runtime_error("Wrong matrix format");
     */
    Matrix(std::istream &input) noexcept(false)
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
            resize(rs, cs, T());
            std::string buffer;
            for (size_t r = 0; r < rows(); ++r)
                for (size_t c = 0; c < cols(); ++c)
                {
                    T v;
                    set(r, c, v);
                }
            if (!(input >> token) || (token != "]"))
                throw std::runtime_error("Wrong matrix format");
        }
        else if (token == "[]")
            resize(0, 0, T());
        else
            throw std::runtime_error("Wrong matrix format");
    }

    /**
     * @brief Create a matrix.
     * @param rows the number of rows.
     * @param cols the number of cols.
     * @param fill_v the value used to initialize the elements.
     * @pre rows==0 || cols>0
     */
    Matrix(size_t rows, size_t cols, const T fill_v)
    {
        assert(rows == 0 || cols > 0);
        resize(rows, cols, fill_v);
    }

    /** @}*/

    /** @name Observers*/
    /**@{*/

    /**
     * @brief Is the matrix empty.
     * @return true if the matrix is empty.
     */
    bool is_empty() const
    {
        return rows() == 0;
    }

    /**
     * @brief Get the number of rows.
     * @return the number of rows.
     */
    size_t rows() const
    {
        return data_.size();
    }

    /**
     * @brief Get the number of columns.
     * @return the number of columns.
     */
    size_t cols() const
    {
        return (is_empty() ? 0 : data_[0].size());
    }

    /**
     * @brief Gets a row vector.
     * @param row is the row index.
     * @return a const reference to row vector.
     * @pre row < rows()
     */
    std::valarray<T> const &operator[](size_t row) const
    {
        assert(row < rows());
        return data_[row];
    }

    /**
     * @brief Get a matrix element.
     * @param r the row
     * @param c the col
     * @return the value of element.
     */
    const T &get(size_t r, size_t c) const
    {
        return data_[r][c];
    }

    /**
     * @brief Output the matrix to output stream.
     * OUTPUT FORMAT
     * "[]"  if empty.
     * '[' <rows> <cols> <rows x cols values of type T> ']'
     * @param out the output stream.
     * @return the modified stream.
     */
    std::ostream &fold(std::ostream &out) const
    {
        if (is_empty())
            out << "[]";
        else
        {
            out << "[ " << rows() << " " << cols();
            for (size_t r = 0; r < rows(); ++r)
                for (size_t c = 0; c < cols(); ++c)
                    out << ' ' << data_[r][c];
            out << " ]";
        }
        return out;
    }

    /** @}*/

    /** @name Modifiers*/
    /**@{*/

    /**
     * @brief Set a matrix element.
     * @param r the row
     * @param c the col
     * @param v the value to set.
     */
    void set(size_t r, size_t c, const T &v)
    {
        data_[r][c] = v;
    }

    /**
     * @brief Gets a row vector.
     * @param row is the row index.
     * @return a reference to the row vector.
     * @pre row < rows()
     */
    std::valarray<T> &operator[](size_t row)
    {
        assert(row < rows());
        return data_[row];
    }

    /**
     * @brief resize the matrix to a new size
     * @param rows the number of rows.
     * @param cols the number of columns.
     * @param fill_v the value used to initialize the elements.
     * @pre rows==0 || cols>0
     */
    void resize(size_t rows, size_t cols, const T fill_v)
    {
        assert(rows == 0 || cols > 0);
        data_.resize(rows, std::valarray<T>(fill_v, cols));
    }

    /** @} */

protected:
    std::valarray<std::valarray<T>> data_;
};

/**
 * @brief A matrix of integers;
 */
typedef Matrix<int> IMatrix;

/**
 * @brief A matrix of floats;
 */
typedef Matrix<float> FMatrix;

/**
 * @brief Template specialization to load FMatrix from input stream.
 * Allow matrix values [+|-]inf and [+|-]nan
 * @param input is the input stream.
 */
template <>
Matrix<float>::Matrix(std::istream &input) noexcept(false);
