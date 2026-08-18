/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <iostream>
#include <exception>
#include <valarray>
#include <vector>
#include <memory>

/**
 * @brief ADT Pattern.
 * Models a pattern for Machine Learning.
 */
class Pattern
{
public:
    /** @name Life cycle.*/

    /** @{*/

    /**
     * @brief Default constructor.
     *
     * The pattern dimension is zero with class label -1. You can update it later
     * by using the @see reset() method.
     *
     * @post dim()==0
     * @post class_label()==-1
     */
    Pattern();

    /**
     * @brief Create a pattern.
     * @pre size>0
     * @post dim()==size
     * @post class_label()==cl
     */
    Pattern(float *values, const size_t size, const int cl);

    /** @brief Destroy a pattern.**/
    ~Pattern();

    /** @}*/

    /** @name Observers*/

    /**@{*/

    /**
     * @brief get the pattern's dimension.
     */
    size_t dim() const;

    /**
     * @brief get the class label
     */
    int class_label() const;

    /**
     * @brief Get pattern's values.
     *
     * @return const std::valarray<float>&
     */
    const std::valarray<float> &values() const;

    /**@}*/

    /** @name Modifiers*/

    /** @{*/

    /**
     * @brief Reset pattern's values and class label.
     * @post dim()==size.
     * @post class_label()==cl
     */
    void reset(float *values, const size_t size, const int cl);

    /**
     * @brief set the class label.
     * @post class_label() == new_label
     */
    void set_class_label(const int new_label);

    /**
     * @brief Get pattern's values.
     *
     * @return const std::valarray<float>&
     */
    std::valarray<float> &values();

    /** @} */

protected:
    int _class_label;
    std::shared_ptr<std::valarray<float>> _values;
};

/**
 * @brief Euclidean distance between patterns.
 *
 * distance_L2(a,b) = sqrt( sum_i (a[i]-b[i])^2 )
 *
 * @param a one pattern
 * @param b other pattern
 * @pre a.dim()==b.dim()
 * @return euclidean distance for a and b.
 * @post ret_val>=0.0
 */
float distance_L2(const Pattern &a, const Pattern &b);

/**
 * @brief Manhattan distance between patterns.
 *
 * distance_L1(a,b) = sum_i |a[i]-b[i]|
 *
 * @param a one pattern
 * @param b other pattern
 * @return manhattan distance for a and b.
 * @pre a.dim()==b.dim()
 * @post ret_val>=0.0
 */
float distance_L1(const Pattern &a, const Pattern &b);

/**
 * @brief Load a pattern from an input stream.
 * @pre the input format will be "class_label d0 ... dn-1"
 */
std::istream &operator>>(std::istream &input, Pattern &p) noexcept(false);

/**
 * @brief Output a pattern to an output stream.
 * @post the output format will be "[ class_label [ v0 v1 ... v_n-1 ] ]"
 */
std::ostream &operator<<(std::ostream &output, const Pattern &p);

/**
 * @brief Load a file with patterns.
 * @pre the format is a first line <size_t num patterns> <size_t dimension> and then
 * a pattern per line.
 * @warning throw runtime_error("wrong format") when wrong input format was detected.
 */
std::istream &load_dataset(std::istream &input,
                           std::vector<Pattern> &dts) noexcept(false);
