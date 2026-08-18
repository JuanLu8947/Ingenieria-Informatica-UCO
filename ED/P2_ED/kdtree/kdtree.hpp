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
#include <memory>
#include <vector>
#include <tuple>
#include <functional>

#include "btree.hpp"
#include "pattern.hpp"

/**
 * @brief Models a K-Dimensional Tree.
 *
 * A KDTree organizes a k-dimensional vector space by recursive bipartition of
 * each dimension.
 *
 * This tree allows to find the k nearest neighbour with a better complexity
 * than a exhaustive search (in average case).
 *
 */
class KDTree
{
public:
    /**
     * @brief Type for functions that compute distances between patterns.
     *
     */
    using distance_function_t = std::function<float(const Pattern &a, const Pattern &b)>;

    /** @name Life cycle.*/
    /** @{ */

    /**
     * @brief Create an empty kdtree.
     * @post is_empty()
     */
    KDTree();

    /** @brief Create a KDTree given a dataset.*/
    KDTree(std::vector<Pattern> &dataset);

    /**
     * @brief Create a KDTree unfolding from a stream.
     * Format: <k> <binary_tree<Pattern>>
     * @warning throw std::runtime_error("wrong input format")
     */
    KDTree(std::istream &in) noexcept(false);

    /**
     * @brief Destroy the KDTree object
     *
     */
    ~KDTree();

    /** @}*/

    /** @name Observers.*/
    /** @{*/

    /**
     * @brief Is it empty?
     */
    bool is_empty() const;

    /**
     * @brief get the root item.
     *
     * @return the root item pattern.
     * @pre !is_empty().
     */
    Pattern item() const;

    /**
     * @brief number of dimensions of the kdtree.
     * @pre !is_empty()
     */
    size_t get_k() const;

    /**
     * @brief Fold the kdtree into an output stream.
     * Format : <k> <tree>
     * @param out is the output stream to use.
     */
    std::ostream &fold(std::ostream &out) const;

    /**
     * @brief find the nearest neighbour from a given pattern.
     * @param p is the pattern to match with.
     * @param dist is used to compute the distance between two patterns
     * @return a tuple with the nearest pattern and the its distance.
     * @pre not is_empty()
     * @pre p.dim() == k()
     */
    std::tuple<float, Pattern> find_nn(Pattern const &p,
                                       const distance_function_t &dist) const;

    /**
     * @brief Get the left subtree.
     *
     * @return the left subtree.
     * @pre !is_empty()
     */
    KDTree left() const;

    /**
     * @brief Get the right subtree.
     *
     * @return the right subtree.
     * @pre !is_empty()
     */
    KDTree right() const;

    /** @}*/

    /** @name Modifiers.*/
    /** @{*/

    /**
     * @brief Rebuild the kdtree to fit a new dataset.
     *
     * @param dts is the new dataset to be fitted.
     * @pre is_empty()
     * @pre dts.size()>0
     * @pre All patterns in dts has same dimensions.
     * @post get_k()==dts[0].dim()
     * @post !is_empty()
     */
    void fit(std::vector<Pattern> &dts);

    /** @}*/

protected:
    /**
     * @brief Construct a new KDTree object given a btree.
     *
     * @param tree is the btree used.
     * @param k is the dimensionality of the problem.
     */
    KDTree(const BTree<Pattern> &tree, size_t k);

    /**
     * @brief find the nearest neighbour from a given pattern.
     * @param p is the pattern to match with.
     * @param dist is used to compute the distance between two patterns
     * @param level is the level of the current subtree (this).
     * @return a tuple with the nearest pattern and the its distance.
     * @pre not is_empty()
     * @pre p.dim() == k()
     */
    std::tuple<float, Pattern> find_nn(Pattern const &p,
                                       const distance_function_t &dist,
                                       size_t level) const;

    /**
     * @brief Get the underlying binary tree.
     * @return a const tree's reference.
     */
    BTree<Pattern> btree() const;

    /**
     * @brief Set the underlying binary tree.
     */
    void set_btree(const BTree<Pattern> &btree);

    /**
     * @brief Set the vector space dimension.
     */
    void set_k(size_t k);

    // TODO: find a representation.
    // Hint: you can use a binary tree to represent a kdtree.
    size_t _k;
    BTree<Pattern> _tree;
    //
};

/**
 * @brief Test equality between two patterns.
 *
 * @param a is a pattern.
 * @param b is a pattern.
 * @return true if a.class_label() == b.class_label() and a.dim()==b.dim() and a.values() == b.values()
 */
bool operator==(const Pattern &a, const Pattern &b);