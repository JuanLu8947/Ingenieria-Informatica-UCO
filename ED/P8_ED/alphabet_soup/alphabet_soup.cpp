/**
 * @file alphabet_soup.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include <sstream>
#include "alphabet_soup.hpp"
#include <utf8_utils.hpp>

AlphabetSoup::AlphabetSoup()
{
    cols_ = 0;
}

AlphabetSoup::AlphabetSoup(int rows, int cols)
{
    resize(rows, cols);
}

int AlphabetSoup::rows() const
{
    return static_cast<int>(alphabet_soup_.size());
}

int AlphabetSoup::cols() const
{
    return cols_;
}

const std::string &
AlphabetSoup::cell(int r, int c) const
{
    assert(0 <= r && r < rows());
    assert(0 <= c && c < cols());
    return row(r)[static_cast<size_t>(c)];
}

std::vector<std::string> const &
AlphabetSoup::row(int row) const
{
    assert(0 <= row && row < rows());
    return alphabet_soup_[static_cast<size_t>(row)];
}

void AlphabetSoup::set_row(int row, const std::string &row_v) noexcept(false)
{
    assert(0 <= row && row < rows());

    for (int col = 0, idx = 0; col < cols() &&
                               static_cast<size_t>(idx) < row_v.size();
         ++col)
    {
        std::string v = get_utf8_char(row_v, idx);
        if (v != "")
        {
            set_cell(row, idx, get_utf8_char(row_v, idx));
            idx += utf8_char_length(row_v[idx]);
        }
        else
            throw(std::runtime_error("wrong input format: invalid UTF-8 character"));
    }
}

void AlphabetSoup::set_cell(int row, int col, const std::string &v)
{
    assert(0 <= row && row < rows());
    assert(0 <= col && col < cols());
    alphabet_soup_[static_cast<size_t>(row)][static_cast<size_t>(col)] = v;
}

void AlphabetSoup::resize(int rows, int cols)
{
    assert(rows >= 0);
    assert(cols >= 0);
    cols_ = cols;
    alphabet_soup_.resize(static_cast<size_t>(rows),
                          std::vector<std::string>(static_cast<size_t>(cols), " "));
}

std::istream &
operator>>(std::istream &in, AlphabetSoup &soup) noexcept(false)
{
    std::string line;
    int rows, cols;
    if (std::getline(in, line))
    {
        std::istringstream iss(line);
        iss >> rows >> cols;
        if (!iss)
            throw std::runtime_error("wrong input format: expected two integers");
        soup.resize(rows, cols);
        for (int i = 0; i < rows && in; ++i)
        {
            std::getline(in, line);
            if (in)
                soup.set_row(i, line);
        }
    }
    if (!in)
        throw std::runtime_error("wrong input format: expected more rows");
    return in;
}

std::ostream &
operator<<(std::ostream &out, AlphabetSoup const &soup)
{
    out << soup.rows() << ' ' << soup.cols() << std::endl;
    for (int r = 0; r < soup.rows(); ++r)
    {
        std::string line = "";
        for (const auto &cell : soup.row(r))
            line += cell;
        out << line << std::endl;
    }
    return out;
}
