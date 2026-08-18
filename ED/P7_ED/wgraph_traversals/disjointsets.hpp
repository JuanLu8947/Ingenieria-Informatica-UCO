/**
 * @file disjointsets.hpp
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
#include <iostream>
#include <vector>

/**
 * @brief ADT DisjointSets.
 * Models a DisjointSets.
 */
class DisjointSets
{
  public:

  /** @name Life cicle.*/
  /** @{*/

    /** @brief Create an DisjoitSets object.
     * Start with capacity elements each one is has its own set.
     * @pre capacity>1
     */
    DisjointSets (size_t capacity):
        _parent(capacity, -1), _rank(capacity)
    {
        assert(capacity>1);
    }

  /** @brief Destroy a Heap.**/
  ~DisjointSets()
  {}

  /** @}*/

  /** @name Observers*/

  /** @{*/

    /** @brief Get the capacity.*/
    int capacity() const
    {
        return static_cast<int>(_parent.size());
    }

    /** @brief Is i a set?
     * @pre 0<=x<capacity()
     */
    bool is_set(int i) const
    {
        assert(i>=0 && i<capacity());
        return _parent[i] != -1;
    }


    /** @brief Find the set for element i
     * @pre 0<=i<capacity()
     * @return the set for the element i or -1 if i does not belongs to any set.
     */
    int find(int i) const
    {
        if (_parent[i] >= 0)
        {   if (i != _parent[i])
                const_cast<DisjointSets*>(this)->_parent[i] = find(_parent[i]);
            i = _parent[i];
        }
        else
            i = -1;
        return i;
    }


  /** @}*/

  /** @name Modifiers*/    

  /** @{*/

    /** @brief make a set for element i
     * @pre 0<=i<capacity()
     * @pre not is_set(i)
     */
    void make_set(int i)
    {
        assert(i>=0 && i<capacity());
        _parent[i] = i;
        _rank[i] = 0;
    }

    /** @brief Joint two sets.
     * @pre 0<= i,j < capacity()
     * @pre is_set(i) && is_set(j)
     * @post find(i)=find(j)
     */
    void joint(int i, int j)
    {
        assert(i>=0 && i<capacity());
        assert(j>=0 && j<capacity());
        assert(is_set(i) && is_set(j));

        //If i>j swap them.
        if (i>j)
            std::swap(i, j);

        //Find the root for i
        int i_id = find(i);

        //Find the root for j
        int j_id = find(j);

        if (i_id != j_id)
        {
            if (_rank[i_id] > _rank[j_id])
            {
                //Link j's tree as subtree in the i's tree.
                _parent[j_id] = i_id;
            }
            else
            {
                //Link i's tree as subtree of j's tree.
                _parent[i_id] = j_id;

                if (_rank[i_id] == _rank[j_id])
                {
                    //The trees had the same rank, so now one has one level more.
                    _rank[j_id]++;
                }
            }
        }
    }

  /** @}*/

protected:

  std::vector<int> _parent;
  std::vector<int> _rank;

};

