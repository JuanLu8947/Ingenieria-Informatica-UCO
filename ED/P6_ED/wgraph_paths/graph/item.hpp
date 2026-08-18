/**
 * @file item.hpp
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
#include <memory>

/**
 * @brief The a data Item[G] ADT.
 */
template <class T, class Key>
struct Item
{
    using key_t = Key;
    using Ref = std::shared_ptr<Item<T, Key>>;

    Item() : data_()
    {
    }

    Item(const T &v) : data_(v)
    {
    }

    static Ref create(const T &v)
    {
        return std::shared_ptr<Item<T, Key>>(new Item<T, Key>(v));
    }

    key_t key() const
    {
        return static_cast<key_t>(data_);
    }
    bool operator==(const Item<T, Key> &other) const
    {
        return key() == other.key();
    }
    bool operator!=(const Item<T, Key> &other) const
    {
        return !(key() == other.key());
    }

    bool operator<(const Item<T, Key> &other) const
    {
        return key() < other.key();
    }

    bool operator<=(const Item<T, Key> &other) const
    {
        return key() < other.key() || key() == other.key();
    }

    T data_;
};

template <class T, class Key>
std::ostream &operator<<(std::ostream &out, const Item<T, Key> &v)
{
    out << v.data_;
    return out;
}

template <class T, class Key>
std::istream &operator>>(std::istream &in, Item<T, Key> &v)
{
    in >> v.data_;
    return in;
}

// Some basic definitions.
typedef Item<char, char> Char;
typedef Item<std::string, std::string> String;
typedef Item<int, int> Int;
