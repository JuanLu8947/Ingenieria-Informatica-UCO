/**
 * @file trie.cpp
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
#include "utf8_utils.hpp"
#include "trie.hpp"

Trie::Trie()
{
    // TODO //constructor por defecto
    _root=nullptr;
    _prefix="";
    //
    assert(is_empty());
}

Trie::Trie(TrieNode::Ref root_node, std::string const &pref)
{
    // TODO //constructor de copia
    _root = root_node; //Inicializa el Trie con un nodo raíz y un prefijo dados.
    _prefix = pref;
    //
    assert(prefix() == pref);
}

Trie::Trie(std::istream &in) noexcept(false)
{
    // TODO //prueba
    // Remember: use get_utf8_char() to load the prefix character by character.
    in >> std::ws;
    char ch;
    if (!(in >> ch) || ch != '[')
        throw std::runtime_error("Wrong input format: expected '['");
    in >> std::ws;
    if (!(in >> ch) || ch != '"')
        throw std::runtime_error("Wrong input format: expected '\"'");
    _prefix.clear();
    while (in.peek() != EOF)
    {
        ch = in.peek();
        if (ch == '"') {
            in.get();
            break;
        }
        std::string symbol = get_utf8_char(in);
        _prefix += symbol;
    }
    in >> std::ws;
    _root = TrieNode::create(in);
    in >> std::ws;
    if (!(in >> ch) || ch != ']')
        throw std::runtime_error("Wrong input format: expected ']'");
    /*
    ·Lee y verifica la comilla ".
    ·Lee el prefijo carácter a carácter (usando UTF-8).
    ·Lee y construye el subtrie (los hijos) usando TrieNode::create(in).
    */
    //
}

bool Trie::is_empty() const
{
    bool ret_v = true;
    // TODO
    if(_root!=nullptr) //método empty
        ret_v=false;
    //
    return ret_v;
}

const std::string &
Trie::prefix() const
{
    // TODO: fixme
    /*std::string fixme;
    return fixme;*/
    return _prefix; //Get
    //
}

void Trie::set_prefix(const std::string &new_p)
{
    // TODO
    _prefix = new_p;
    //
    assert(prefix() == new_p);
}

bool Trie::is_key() const
{
    assert(!is_empty());
    bool ret_val = true;
    // TODO
    if(_root->is_key()==false) //Devuelve true si el nodo raíz representa una clave.
        ret_val=false;
    //
    return ret_val;
}

const TrieNode::Ref &
Trie::root() const
{
    // TODO: fixme
    /*TrieNode::Ref fixme;
    return fixme;*/
    return _root; //Get - referencia al nodo raíz.
    //
}

void Trie::set_root(TrieNode::Ref const &new_r)
{
    // TODO
    _root = new_r;
    //
    assert(root() == new_r);
}

bool Trie::has(std::string const &k) const
{
    assert(!is_empty());
    bool found = false;
    // TODO
    // Hint: use find_node() to do this.
    // Remember: The Trie can have a prefix==k but does not store the key k.
    TrieNode::Ref node = find_node(k); //Devuelve true si el Trie contiene la clave k (usando find_node).
    found = (node != nullptr && node->is_key());
    //
    return found;
}

/**
 * @brief Helper function to retrieve the keys.
 *
 * This function does a recursive preorder traversal of the trie's nodes
 * keeping the current prefix and the retrieved keys as functions parameters.
 *
 * @param[in] node is the current node.
 * @param[in] prefix is the current prefix.
 * @param[in,out] keys are the retrieved keys.
 */
static void
preorder_traversal(TrieNode::Ref node, std::string prefix,
                   std::vector<std::string> &keys)
{
    // TODO
    // Remember: node->is_key() means the prefix is a key too.
    if(node->is_key())
        keys.push_back(prefix);
    node->goto_first_child();
    while(node->current_exists()){
        preorder_traversal(node->current_node(), prefix+node->current_symbol(), keys);
        node->goto_next_child();
    }
    /*
    Hace lo siguiente: 
     Recorre el Trie en preorden (primero el nodo actual, luego sus hijos) para recopilar todas las palabras almacenadas.

    Funcionamiento:
    ·Si el nodo actual representa una clave (is_key()), añade el prefijo actual al vector de claves.
    ·Luego recorre todos los hijos del nodo:
     ·Para cada hijo, llama recursivamente a preorder_traversal con el prefijo extendido con el símbolo del hijo.
     ·Usa goto_first_child() y goto_next_child() para iterar sobre los hijos.
    
    Uso:
     Para obtener todas las palabras almacenadas en el Trie, por ejemplo, para listarlas o exportarlas.
    */
    //
}

void Trie::retrieve(std::vector<std::string> &keys) const
{
    assert(!is_empty());
    // TODO
    // Remember add the subtrie's prefix to the retrieve keys.
    preorder_traversal(_root, prefix(), keys); //Recupera todas las claves del Trie y las añade a keys.
    //
}

Trie Trie::child(std::string const &postfix) const
{
    assert(!is_empty());
    Trie ret_v;
    // TODO
    // Hint: use find_node() to follow the chain of nodes whose represent postfix.
    auto node = find_node(postfix);

    if(node == nullptr)
        ret_v = Trie();
    else{
        ret_v = Trie(node,prefix()+postfix);
    }
    /*
    Hace lo siguiente:
     Devuelve el subtrie que corresponde a un sufijo/postfijo dado.

    Funcionamiento:
    ·Busca el nodo correspondiente al sufijo usando find_node.
    ·Si no existe, devuelve un Trie vacío.
    ·Si existe, crea un nuevo Trie con ese nodo como raíz y el prefijo extendido.
    
    Uso:
     Permite obtener un subtrie que representa todas las palabras que empiezan por el prefijo actual más el postfix dado.
    */
    //
    assert(ret_v.is_empty() || ret_v.prefix() == (prefix() + postfix));
    return ret_v;
}

bool Trie::current_exists() const
{
    assert(!is_empty());
    bool ret_val = false;
    // TODO
    if(_root->current_exists()) //Devuelve true si existe un hijo seleccionado en el nodo raíz.
        ret_val=true;
    //
    return ret_val;
}

Trie Trie::current() const
{
    assert(current_exists());
    Trie ret_v;
    // TODO
    ret_v=Trie(_root->current_node(), _prefix+_root->current_symbol()); //Devuelve el subtrie correspondiente al hijo seleccionado actualmente.
    //
    return ret_v;
}

const std::string &Trie::current_symbol() const
{
    assert(current_exists());
    // TODO: fixme
    /*std::string fixme;
    return fixme;*/
    return _root->current_symbol(); //Devuelve el símbolo del hijo seleccionado actualmente.
    //
}

void Trie::insert(std::string const &k)
{
    assert(k != "");
    // TODO
    // Remember: we are using utf-8 encoding for the symbols. In utf-8 a symbol
    // can be represented by one or more bytes. Use the helper functions
    // utf8_char_length() and get_utf8_char() to extract the symbols from the
    // key.
    if(_root == nullptr) 
        _root = TrieNode::create(false);
    TrieNode::Ref node = _root;
    size_t i = 0;
    while (i < k.length()){
        int char_length = utf8_char_length(k[i]);
        std::string symbol = get_utf8_char(k, i);
        
        if(node->has(symbol))
            node = node->child(symbol);
        else {
            TrieNode::Ref new_node = TrieNode::create(false);
            node->set_child(symbol, new_node);
            node = new_node;
        }
        i += char_length;
    }
    node->set_is_key_state(true);
    /*
    Hace lo siguiente:
        Inserta una palabra en el Trie, creando los nodos necesarios.
    Funcionamiento:
    ·Si el Trie está vacío, crea el nodo raíz.
    ·Recorre la palabra símbolo a símbolo (usando UTF-8).
    ·Si el nodo actual ya tiene un hijo con ese símbolo, avanza a ese hijo.
    ·Si no, crea un nuevo nodo hijo y avanza.
    ·Al final, marca el nodo como clave (is_key_state = true).
    Uso:
        Permite añadir nuevas palabras al Trie, asegurando que cada símbolo se maneje correctamente incluso si es multibyte (UTF-8).
    */
    //
    assert(!is_empty());
    assert(has(k));
}

TrieNode::Ref
Trie::find_node(std::string const &pref) const
{
    assert(!is_empty());
    TrieNode::Ref node;
    // TODO
    // Remember: the prefix "" must return the trie's root node.
    // Remember: we are using utf-8 encoding for the symbols. In utf-8 a symbol
    // can be represented by one or more bytes. Use the helper functions
    // utf8_char_length() and get_utf8_char() to extract the symbols from the
    // key.
    if (pref.empty()) 
        return _root;
    node = _root;
    size_t i = 0;
    while (i < pref.length() && node != nullptr){
        int char_length = utf8_char_length(pref[i]);
        std::string symbol = get_utf8_char(pref, i);
        if (node->has(symbol)) {
            node = node->child(symbol);
            i += char_length;
        } 
        else {
            node = nullptr;
        }
    } 
    /*
    Hace lo siguiente:
     Busca un nodo en el Trie que represente un prefijo dado.

    Funcionamiento:
    ·Si el prefijo está vacío, devuelve el nodo raíz.
    ·Si no, recorre símbolo a símbolo (UTF-8) desde la raíz, bajando por los hijos.
    ·Si en algún momento no existe el hijo, devuelve nullptr.

    Uso:
     Permite localizar el nodo que representa un prefijo, útil para búsquedas, autocompletado, o para obtener subtries.
    */
    //
    return node;
}

std::ostream &
Trie::fold(std::ostream &out) const
{
    // TODO //prueba
    out << "[ ";
    out << "\"" << _prefix << "\"";
    if (_root != nullptr) 
    {
        out << " ";
        _root->fold(out);
    }
    out << " ]";
    /*
    ·Escribe el prefijo entre comillas.
    ·Si hay nodo raíz, escribe un espacio y llama a fold del nodo raíz (que recursivamente escribe los hijos).
    */
    //
    return out;
}

bool Trie::find_symbol(const std::string &symbol)
{
    assert(!is_empty());
    bool found = false;
    // TODO
    if(_root->find_child(symbol) == true) //Busca un hijo con el símbolo dado y lo selecciona como actual.
        found = true;
    //
    assert(!found || current_exists());
    assert(found || !current_exists());
    assert(!current_exists() || current_symbol() == symbol);
    return found;
}

void Trie::goto_first_symbol()
{
    assert(!is_empty());
    // TODO
    _root->goto_first_child(); //Selecciona el primer hijo del nodo raíz.
    //
    assert(!current_exists() ||
           current().prefix() == (prefix() + current_symbol()));
}

void Trie::goto_next_symbol()
{
    assert(current_exists());
    // TODO
    _root->goto_next_child(); //Avanza al siguiente hijo del nodo raíz.
    //
}
