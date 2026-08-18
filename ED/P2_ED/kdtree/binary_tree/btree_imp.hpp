/**
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
#include <memory>
#include <iostream>
#include <sstream>

#include "btree.hpp"

template <class T>
bool BTree<T>::is_empty() const
{
    bool ret_v = false;
    // TODO
    //en árboles si la raiz o root es null -> es empty
    ret_v = (root() == nullptr);
    //
    return ret_v;
}

template <class T>
BTree<T>::BTree()
{
    // TODO
    //constructor base -> root es null
    _root = nullptr;
    //
    assert(is_empty());
}

template <class T>
BTree<T>::BTree(const T &it)
{
    // TODO
    //constructor con inicialización de la raiz
    //_root = std::make_shared<BTNode<T>>(it);
    _root = BTNode<T>::create(it);
    //
    assert(!is_empty());
    assert(item() == it);
    assert(left().is_empty());
    assert(right().is_empty());
}

template <class T>
BTree<T>::BTree(std::istream &in) noexcept(false)
    : BTree<T>()
{
    // TODO
    // Remember: throw std:runtime_error exception with text
    //"Wrong input format." when an input format error is found.
    //unfold usado como constructor 
    std::string token;
    T it; //creacion de un it tipo T
    in >> token; //volcado de in a token
    if(token == "["){
        in >> it;
        if(in.fail())
            throw std::runtime_error("Wrong input format.");
        //
        set_root(BTNode<T>::create(it)); //creación de la raíz //ya que es un constructor 
        //al igual que creamos la raiz ahora creamos el subárbol 1º izquierdo y 2º derecho
        set_left(BTree<T>(in)); //creación del subárbol izquierdo
        set_right(BTree<T>(in)); //creación del subárbol derecho
        in >> token;
        //
        if(token != "]")
            throw std::runtime_error("Wrong input format.");
    }
    else if(token != "[]")
        throw std::runtime_error("Wrong input format.");
    //
}

template <class T>
T BTree<T>::item() const
{
    assert(!is_empty());
    T ret_v;
    // TODO
    ret_v = root()->item(); //devuelve el item de la raiz
    //
    return ret_v;
}

template <class T>
BTree<T> BTree<T>::left() const
{
    assert(!is_empty());
    BTree<T> subtree;
    // TODO
    // Hint: use the private constructor given a root node.
    subtree = BTree<T>(root()->left()); //subárbol izquierdo
    //se apunta la raíz al subárbol izquierdo
    //
    return subtree;
}

template <class T>
BTree<T> BTree<T>::right() const
{
    assert(!is_empty());
    BTree<T> subtree;
    // TODO
    // TODO
    // Hint: use the private constructor given a root node.
    subtree = BTree<T>(root()->right()); //subárbol derecho
    //se apunta la raíz al subárbol derecho
    //
    return subtree;
}

template <class T>
std::ostream &BTree<T>::fold(std::ostream &out) const
{
    // TODO
    //el fold pliega el árbol en el fichero out
    if(is_empty())
    out << "[]";
    else{
        out << "[ ";
        out << item();
        out << " ";
        left().fold(out); //fold del subárbol izquierdo
        out << " ";
        right().fold(out); //fold del subárbol derecho
        out << " ]";
    }
    //
    return out;
}

template <class T>
void BTree<T>::create_root(const T &it)
{
    assert(is_empty());
    // TODO
    //_root = std::make_shared<BTNode<T>>(it); //creación de la raíz con it
    //reserva de memoria y uso de punteros inteligentes
    _root = BTNode<T>::create(it);
    //
    assert(!is_empty());
    assert(item() == it);
    assert(left().is_empty());
    assert(right().is_empty());
}

template <class T>
void BTree<T>::set_item(const T &new_it)
{
    assert(!is_empty());
    // TODO
    root()->set_item(new_it); //cambio de item de la raíz
    //
    assert(item() == new_it);
}

template <class T>
void BTree<T>::set_left(const BTree<T> &new_left)
{
    assert(!is_empty());
    // TODO
    root()->set_left(new_left.root()); //cambio de subárbol izquierdo
    //como se observa a través de root se hace el cambio
    //
    assert(left().root() == new_left.root());
}

template <class T>
void BTree<T>::set_right(const BTree<T> &new_right)
{
    assert(!is_empty());
    // TODO
    root()->set_right(new_right.root()); //cambio de subárbol derecho
    //
    assert(right().root() == new_right.root());
}

template <class T>
BTree<T>::BTree(const typename BTNode<T>::Ref &n)
{
    // TODO
    _root = n; //se hace para luego el assert
    //
    assert(root() == n);
}

template <class T>
typename BTNode<T>::Ref BTree<T>::root() const
{
    typename BTNode<T>::Ref node;
    // TODO
    node = _root; //asignamos root a node, devolvemos node
    //
    return node;
}

template <class T>
void BTree<T>::set_root(const typename BTNode<T>::Ref &new_root)
{
    // TODO
    _root = new_root; //cambio de raíz //SET
    //
    assert(root() == new_root);
}

template <class T>
BTree<T>::BTree(const BTree<T> &other)
{
    set_root(other.root());
}

template <class T>
BTree<T>::BTree(BTree<T> &&other)
{
    set_root(other.root());
}

template <class T>
BTree<T> &BTree<T>::operator=(const BTree<T> &other)
{
    set_root(other.root());
    return *this;
}

template <class T>
BTree<T> &BTree<T>::operator=(BTree<T> &&other)
{
    set_root(other.root());
    return *this;
}
