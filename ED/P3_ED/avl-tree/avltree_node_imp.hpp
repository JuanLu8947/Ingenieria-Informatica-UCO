/**
 * @file avltree_node_imp.hpp
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
#include <avltree_node.hpp>

template <class T>
typename AVLTNode<T>::Ref AVLTNode<T>::This() const
{
    return This_;
}

template <class T>
AVLTNode<T>::AVLTNode(T const &it)
{
    // TODO
    item_ = it;
    height_ = 0;
    //Ponemos las REF a null
    parent_ = nullptr;
    left_ = nullptr;
    right_ = nullptr;
    //
    assert(item() == it);
    assert(left() == nullptr);
    assert(right() == nullptr);
#ifndef __ONLY_BSTREE__
    assert(parent() == nullptr);
    assert(height() == 0);
    assert(check_height_invariant());
#endif
}

template <class T>
typename AVLTNode<T>::Ref AVLTNode<T>::create(T const &it)
{
    auto This = typename AVLTNode<T>::Ref(new AVLTNode(it));
    This->This_ = This;
    return This;
}

template <class T>
const T &AVLTNode<T>::item() const
{
    // TODO: recode using your representation.
    /*T fixme;
    return fixme;*/
    return item_; //Get
    //
}

template <class T>
typename AVLTNode<T>::Ref const &AVLTNode<T>::left() const
{
    // TODO: fixme
    /*typename AVLTNode<T>::Ref fixme;
    return fixme;*/
    return left_;
    //
}

template <class T>
typename AVLTNode<T>::Ref &AVLTNode<T>::left()
{
    // TODO: fixme
    /*typename AVLTNode<T>::Ref fixme;
    return fixme;*/
    return left_;
    //
}

template <class T>
typename AVLTNode<T>::Ref const &AVLTNode<T>::right() const
{
    // TODO
    /*typename AVLTNode<T>::Ref fixme;
    return fixme;*/
    return right_;
    //
}

template <class T>
typename AVLTNode<T>::Ref &AVLTNode<T>::right()
{
    // TODO
    /*typename AVLTNode<T>::Ref fixme;
    return fixme;*/
    return right_;
    //
}

template <class T>
typename AVLTNode<T>::Ref const &AVLTNode<T>::child(int dir) const
{
    assert(dir == 0 || dir == 1);
    // TODO fixme
    // Remember: this operation is only necessary for the AVLTree.
    /*AVLTNode<T>::Ref fixme;
    return fixme;*/
    if(dir == 0)
        return left();
    else{
        return right();
    }
    //
}

template <class T>
typename AVLTNode<T>::Ref &AVLTNode<T>::child(int dir)
{
    assert(dir == 0 || dir == 1);
    // TODO fixme
    // Remember: this operation is only necessary for the AVLTree.
    /*AVLTNode<T>::Ref fixme;
    return fixme;*/
    if(dir == 0)
        return left();
    else{
        return right();
    }
    //
}

template <class T>
typename AVLTNode<T>::Ref const &AVLTNode<T>::parent() const
{
    // TODO: fixme
    // Remember: this operation is only necessary for the AVLTree.
    //
    /*AVLTNode<T>::Ref fixme;
    return fixme;*/
    return parent_; //Get
    //
}

template <class T>
typename AVLTNode<T>::Ref &AVLTNode<T>::parent()
{
    // TODO: fixme
    // Remember: this operation is only necessary for the AVLTree.
    //
    /*AVLTNode<T>::Ref fixme;
    return fixme;*/
    return parent_; //Get
    //
}

template <class T>
int AVLTNode<T>::height() const
{
    // TODO
    // Remember: this operation is only necessary for the AVLTree.
    // Remember: we want O(1) here.
    /*int fixme = 0;
    return fixme;*/
    return height_; //Get
    //
}

template <class T>
int AVLTNode<T>::balance_factor() const
{
    int bf = 0;
    // TODO
    // Remember: this operation is only necessary for the AVLTree.
    int height_izq = -1, height_drcha = -1;
    if(left()!=nullptr)
        height_izq = left()->height();
    if(right()!=nullptr)
        height_drcha = right()->height();
    bf = height_drcha - height_izq;
    //
    return bf;
}

template <class T>
bool AVLTNode<T>::check_height_invariant() const
{
    bool ret_val = false;
#ifdef __ONLY_BSTREE__
    ret_val = true; // In a BSTree we do not need to check the height invariant.
#else
    // TODO
    // Remember: the height of a node is one more than the maximum of the heights of its children.
    //1º que todo, la altura de nodo izq y drcho debe de ser -1
    int left_height = -1, right_height = -1;

    //luego comprobamos que exista ese nodo izq o drecho
    if(left() != nullptr) //si existe, se le asigna la altura
        left_height = left()->height();
    if(right() != nullptr)
        right_height = right()->height();

    //finalmente se comprueba la altura del nivel
    ret_val = (height_ == 1 + std::max(left_height, right_height));
    //
#endif
    return ret_val;
}

template <class T>
void AVLTNode<T>::update_height()
{
    // TODO
    // Remember: this operation is only necessary for the AVLTree.
    // Remember: we want O(1) here.
    // Remember: the height of a node is one more than the maximum of the heights of its children.
    // Remember: the height of a "void" node is -1.
    //para actualizar la altura, se hace lo mismo pero sobre la variable
    //1º que todo, la altura de nodo izq y drcho debe de ser -1
    int left_height = -1, right_height = -1;

    //luego comprobamos que exista ese nodo izq o drecho
    if(left() != nullptr) //si existe, se le asigna la altura
        left_height = left()->height();
    if(right() != nullptr)
        right_height = right()->height();

    //finalmente se devuelve la altura del nivel
    height_ = 1 + std::max(left_height, right_height);
    //
    assert(check_height_invariant());
}

template <class T>
void AVLTNode<T>::set_item(const T &new_it)
{
    // TODO
    item_ = new_it;
    //
    assert(item() == new_it);
}

template <class T>
void AVLTNode<T>::set_parent(AVLTNode<T>::Ref new_parent)
{
    // TODO
    // Remember: this operation is only necessary for the AVLTree.
    parent_ = new_parent;
    //
    assert(parent() == new_parent);
}

template <class T>
void AVLTNode<T>::set_left(Ref new_child)
{
    // TODO
    // Remember: When implementing the AVL Tree, the child's parent link is needed to be
    // updated to point to this node. Use This() method to get a Reference to this.
    // Remember: When implementing the AVL Tree, the node height must be updated at the end.
    /*left_ = new_child;
    if(left_ != nullptr)
        left_->set_parent(This());*/
    left_ = new_child;
    if (new_child)
        new_child->set_parent(This());
    update_height();
    //
    assert(left() == new_child);
#ifndef __ONLY_BSTREE__
    assert(check_height_invariant());
    assert(!new_child || new_child->parent() == This());
#endif
}

template <class T>
void AVLTNode<T>::set_right(AVLTNode<T>::Ref new_child)
{
    // TODO
    // Remember: for the AVLTree the child's parent link is needed to be
    // updated to point to this node. Use This() method to get a Reference to this.
    // Remember: for the AVLTree the height of the node must be updated at the end.
    /*right_ = new_child;
    if(right_ != nullptr)
        right_->set_parent(This());*/
    right_ = new_child;
    if (new_child)
        new_child->set_parent(This());
    update_height();
    //
    assert(right() == new_child);
#ifndef __ONLY_BSTREE__
    assert(check_height_invariant());
    assert(!new_child || new_child->parent() == This());
#endif
}

template <class T>
void AVLTNode<T>::set_child(int dir, Ref new_child)
{
    assert(dir == 0 || dir == 1);
    // TODO
    // Remember: this operation is only necessary for the AVLTree.
    if(dir == 0) //según dir, será hijo izq o drcho
        left_ = new_child;
    else{
        right_ = new_child;
    }
    if (new_child != nullptr)
        new_child->set_parent(This());

    update_height();
    //
    assert(check_height_invariant());
    assert(dir == 0 || right() == new_child);
    assert(dir == 1 || left() == new_child);
    assert(!new_child || new_child->parent() == This());
}
