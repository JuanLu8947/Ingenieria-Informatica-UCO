/**
 * @file trie_node.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include <cassert>
#include <sstream>
#include <cstdint>
#include "utf8_utils.hpp"
#include "trie_node.hpp"

TrieNode::TrieNode(bool is_key_state)
{
    // TODO //constructor de copia por defecto
    _is_key = is_key_state; //indica si este nodo representa una clave completa.
    _current = _childs.end(); //icializa el iterador de hijos como "no válido" (no apunta a ningún hijo).
    //
    assert(is_key() == is_key_state);
    assert(!current_exists());
};

TrieNode::Ref TrieNode::create(bool is_key_state)
{
    return Ref(new TrieNode(is_key_state));
}

TrieNode::~TrieNode()
{
}

bool TrieNode::is_key() const
{
    bool ret_val = true;
    // TODO
    ret_val = _is_key; //Set
    //
    return ret_val;
}

bool TrieNode::has(const std::string &k) const
{
    bool ret_v = false;
    // TODO
    // Hint: use std::map::find() to check if the key exists.
    ret_v = (_childs.find(k) != _childs.end());
    //
    return ret_v;
}

const TrieNode::Ref &
TrieNode::child(const std::string &k) const
{
    assert(has(k));
    // TODO
    // Hint: use std::map::at() to get the child node.
    /*TrieNode::Ref fixme;
    return fixme;*/
    return _childs.at(k); //Devuelve el hijo asociado al símbolo k usando el método at() de std::map.
    //
}

bool TrieNode::current_exists() const
{
    bool ret_val = true;
    // TODO
    // Hint: use std::map::end() to check if the current is valid.
    ret_val = (_current != _childs.end()); //Comprueba si el iterador _current apunta a un hijo válido.
    //
    return ret_val;
}

const TrieNode::Ref &
TrieNode::current_node() const
{
    assert(current_exists());
    // TODO
    /*TrieNode::Ref fixme;
    return fixme;*/
    return _current->second; //Devuelve el nodo hijo al que apunta _current.
    //
}

const std::string &TrieNode::current_symbol() const
{
    assert(current_exists());
    // TODO
    /*std::string fixme;
    return fixme;*/
    static std::string symbol;
    symbol = _current->first;
    return symbol; //Devuelve el símbolo (clave) del hijo actual.
    //
}

void TrieNode::set_is_key_state(bool new_state)
{
    // TODO
    _is_key = new_state;
    //
    assert(is_key() == new_state);
}

bool TrieNode::find_child(const std::string &s)
{
    bool found = false;
    // TODO
    _current = _childs.find(s); //Busca un hijo con símbolo s y actualiza _current al resultado.
    found = current_exists();
    //
    assert(found || !current_exists());
    assert(!found || current_symbol() == s);
    return found;
}

void TrieNode::goto_first_child()
{
    // TODO
    _current = _childs.begin(); //Sitúa _current en el primer hijo (si existe).
    //
}

void TrieNode::goto_next_child()
{
    assert(current_exists());
    // TODO
    ++_current; //avanza _current al siguiente hijo.
    //
}

void TrieNode::set_child(const std::string &k, const Ref &node)
{
    assert(node != nullptr);
    // TODO
    _childs[k] = node; //Añade o reemplaza un hijo con símbolo k y lo selecciona como actual.
    _current = _childs.find(k);
    //
    assert(current_symbol() == k);
    assert(current_node() == node);
}

std::ostream &
TrieNode::fold(std::ostream &out) const
{
    // TODO
    out << "[ ";
    if(is_key()) 
        out << "T";
    else {
        out << "F";
    }

    for (auto it = _childs.begin(); it != _childs.end(); ++it) {
        std::string symbol = it->first;
        out << " " << symbol << " ";
        it->second->fold(out);
    }
    out << " ]";
    /*
    ·Escribe T si es clave, F si no.
    ·Para cada hijo, escribe el símbolo y recursivamente el hijo.
    */
    //
    return out;
}

TrieNode::Ref TrieNode::create(std::istream &in) noexcept(false)
{
    TrieNode::Ref node = nullptr;
    // TODO
    // Remember: use get_utf8_char() to extract the "symbols" that define a node
    // from the input stream due to the symbols are utf-8 encoded.
    // Remember: use in.ignore(1) to skip the space before a folded node.
    // Remember: throw std::runtime_error("Wrong input format") when the input
    // format is not as expected.
    std::string token;
    in >> token;    
    if (token != "[")
        throw std::runtime_error("Wrong input format");
    in >> token;
    if(token=="T")
        node = TrieNode::create(true);
    else if(token=="F")
        node = TrieNode::create(false);
    else
        throw std::runtime_error("Wrong input format");
    while (true){
        while (in.peek() == ' ')
            in.ignore(1);
            
        if (in.peek() == ']'){
            in.ignore(1);
            break;
        }
        std::string symbol = get_utf8_char(in);
        if (symbol.empty())
            throw std::runtime_error("Wrong input format");
        if (in.peek() == ' ')
            in.ignore(1);
        node->set_child(symbol, TrieNode::create(in));
    }
    //
    return node;
}
