/**
 * @file avltree_imp.hpp
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
#include <numeric>
#include <functional>
#include <limits>
#include <vector>
#include <algorithm>
#include <avltree.hpp>

template <class T>
AVLTree<T>::AVLTree()
{
    // TODO
    root_ = nullptr;
    current_ = nullptr;
    parent_ = nullptr;
    //
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());
    assert(is_empty());
    assert(!current_exists());
#ifndef __ONLY_BSTREE__
    assert(height() == -1);
#endif
}

template <class T>
AVLTree<T>::AVLTree(T const &item)
{
    // TODO
    root_ = AVLTNode<T>::create(item);
    current_ = root_;
    parent_ = nullptr;
    //
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());
    assert(!is_empty());
    assert(item() == item);
    assert(current_exists());
    assert(current() == item);
#ifndef __ONLY_BSTREE__
    assert(current_level() == 0);
    assert(height() == 0);
#endif
}

template <class T>
AVLTree<T>::AVLTree(std::istream &in) noexcept(false)
{
    // TODO
    std::string token;
    in >> token;
    if (token == "[]"){
        root_ = nullptr;
        current_ = nullptr;
        parent_ = nullptr;
    }
    else if (token == "["){
        T item;
        in >> item; //se podría añadir una comprobación de error
        create_root(item); //1º se crear raiz

        AVLTree<T> left_subtree(in); //2º se crea subárbol izquierdo

        AVLTree<T> right_subtree(in);

        set_left(left_subtree); //se asigna ese subárbol como izq del nodo raíz
        set_right(right_subtree);

        in >> token;
        //se podría añadir comprobación de error de != ]
    }
    else{
        throw std::runtime_error("Wrong input format.");
    }
    //

    if (!is_a_binary_search_tree())
        throw std::runtime_error("It is not a binary search tree");
    if (!is_a_balanced_tree())
        throw std::runtime_error("It is not an avl tree");
}

template <class T>
AVLTree<T>::~AVLTree()
{
    // TODO
    // Think if it is necessary to do something here regarding your representation.

    //
}

#ifdef __ONLY_BSTREE__
/**
 * @brief Create an perfectly balanced BSTree by inserting the median of
 *        an ordered sub sequence data[begin, end).
 * @param data is the ordered sequence of values.
 * @param begin,
 * @param end specify a [begin, end) indexing interval of array data to use.
 * @pre 0 <= begin <= end <=data.size()
 * @pre begin==end || data[begin]<data[end];
 */
template <class T>
void create_inserting_median(std::vector<T> const &data,
                             size_t begin,
                             size_t end,
                             AVLTree<T> &tree)
{
    assert(begin <= end);
    assert(end <= data.size());
    assert(begin == end || data[begin] <= data[end - 1]);

    // TODO
    // Hint: if (end==begin) none thing must be done (it is an empty sub array)
    //  else, insert the median in the tree and (recursively) process
    //  the two sub sequences [begin, median_idx) and [median_idx+1, end)
    /*
    if (begin == end)
        return;
    else{
        //
    }
    */
    if(end - begin >= 1){
        // Calcular el índice de la mediana.
        size_t median = begin + ((end - begin) / 2);
        //size_t median = (begin + end) / 2; //begin + end = data.size()
        //size_t median = data.size()+1 / 2;
        //size_t median = data.size() / 2;

        // Insertar la mediana en el árbol.
        tree.insert(data[median]);

        // Procesar recursivamente las dos subsecuencias ó subárboles
        create_inserting_median(data, begin, median, tree); // Subárbol izquierdo.
        create_inserting_median(data, median + 1, end, tree); // Subárbol derecho.
    }
    /*
    std::vector<T> const &data,
                             size_t begin,
                             size_t end,
                             AVLTree<T> &tree)
    */
    //
}

template <class T>
AVLTree<T>
create_perfectly_balanced_bstree(std::vector<T> &data)
{
    AVLTree<T> tree;
    // TODO
    // Remember: the empty tree is perfectly balanced.
    // Remember: first, an ordered sequence (using < order) of values is needed.
    // Then you should use the above create_inserting_median function
    // on a empty tree to recursively create the perfectly balanced bstree.
    // Ordenar los datos en orden ascendente.
    std::sort(data.begin(), data.end());

    // Usar la función create_inserting_median para construir el árbol balanceado.
    create_inserting_median(data, 0, data.size(), tree);
    /*
    std::vector<T> const &data,
                             size_t begin,
                             size_t end,
                             AVLTree<T> &tree)
    */
    //
    return tree;
}
#endif //__ONLY_BSTREE__

template <class T>
bool AVLTree<T>::is_empty() const
{
    // TODO
    //return false; // fixme
    return root_node() == nullptr;//root_node returns root_
    //
}

template <class T>
T const &AVLTree<T>::item() const
{
    assert(!is_empty());
    // TODO: fixme
    /*T fixme{};
    return fixme;*/
    return root_node()->item();
    //
}

template <class T>
std::ostream &AVLTree<T>::fold(std::ostream &out) const
{
    // TODO
    if (is_empty())
        out << "[]";
    else{
        out << "[ ";
        out << item();
        out << " ";
        left().fold(out);
        out << " ";
        right().fold(out);
        out << " ]";
    }
    //[ item left right ] //predecesor
    //
    return out;
}

template <class T>
bool AVLTree<T>::current_exists() const
{
    // TODO
    return current_node() != nullptr; //current_node() returns current_
    //
}

template <class T>
T const &AVLTree<T>::current() const
{
    assert(current_exists());
    // TODO: fixme
    /*T fixme{};
    return fixme;*/
    return current_node()->item(); //Get the current item € node
    //
}

template <class T>
int AVLTree<T>::current_level() const
{
    assert(current_exists());
    int level = 0;
    // TODO
    auto node = parent_node();
    while (node != nullptr){ //mientras que un nodo exista
        level++;                //incrementamos el nivel
        node = node->parent(); //subimos current al padre
    }
    //esta funcion dice en que nivel esta current
    //
    return level;
}

template <class T>
AVLTree<T> AVLTree<T>::left() const
{
    assert(!is_empty());
    AVLTree<T> subtree;
    // TODO
    // Hint: use the private AVLTree constructor given a node as root.
    subtree = AVLTree<T>(root_node()->left());
    //
    return subtree;
}

template <class T>
AVLTree<T> AVLTree<T>::right() const
{
    assert(!is_empty());
    AVLTree<T> subtree;
    // TODO
    // Hint: use the private AVLTree constructor given a node as root.
    subtree = AVLTree<T>(root_node()->right());
    //
    return subtree;
}

template <class T>
size_t AVLTree<T>::size() const
{
    size_t s = 0;
    // TODO
    if (!is_empty())
        s = 1 + left().size() + right().size();
        /*
        ·1: Representa el nodo raíz actual.
        ·left().size(): Calcula el tamaño del subárbol izquierdo recursivamente.
        ·right().size(): Calcula el tamaño del subárbol derecho recursivamente.
        */
    //
    return s;
}

template <class T>
int AVLTree<T>::height() const
{
    int h = 0;
    // TODO
    // Remember: this operation is only necessary for the AVLTree.
    // Remember: we want O(1) here.
    if(is_empty())
        h = -1;
    else{
        h = root_node()->height();
    }
    //
    return h;
}

template <class T>
int AVLTree<T>::balance_factor() const
{
    int bf = 0;
    // TODO
    // Remember: this operation is only necessary for the AVLTree.
    /*if (!is_empty()){
        int left_height = -1, right_height = -1;

        if (root_->left() != nullptr)
            left_height = root_->left()->height();

        if (root_->right() != nullptr)
            right_height = root_->right()->height();

        bf = right_height - left_height;
    }*/
    bf = root_node()->balance_factor(); //usa la funcion balance_factor de AVLTNode
    //
    return bf;
}

template <class T>
bool AVLTree<T>::has(const T &k) const
{
#ifndef NDEBUG
    bool old_current_exists = current_exists();
    T old_current;
    if (old_current_exists)
        old_current = current();
#endif

    bool found = true;

    // TODO
    // Hint: you can reuse the search method for this but in this case you will
    //       need to use "const_cast" to remove constness of "this" and
    //       save/restore the old state of current before returning.
    auto old = current_node();
    AVLTree<T> *nonConstThis = const_cast<AVLTree<T> *>(this);
    /*
    se usa para eliminar const, con lo cuál permite modificar el objeto
    se usa ya que 'has' llama a seach el cuál no es const
    entonces, const_cast puede obtener un puntero no constante al objeto actual y así poder llamar a métodos no constantes.
    */
    found = nonConstThis->search(k);
    nonConstThis->set_current_node(old);
    //

#ifndef NDEBUG
    assert(!old_current_exists || old_current == current());
#endif
    return found;
}

/**
 * @brief infix process of a node.
 * The Processor must allow to be used as a function with a parameter  (the
 * item to be processed) and returning true if the process must continue or
 * false if not.
 * @param node is the node to be processed.
 * @param p is the Processor.
 * @return true if all the tree was in-fix processed.
 */
template <class T, class Processor>
bool infix_process(typename AVLTNode<T>::Ref node, Processor &p)
{
    bool retVal = true;
    // TODO
    // Remember: if node is nullptr return true.
    /*
    if (node == nullptr)
        return true;
    else{
        // Procesar el subárbol izquierdo.
        retVal = infix_process<T, Processor>(node->left(), p); //internamente tiene f(x) lambda

        // Si el procesamiento del subárbol izquierdo fue exitoso, procesar el nodo actual.
        if(retVal)
            retVal = p(node->item());

        // Si el procesamiento del nodo actual fue exitoso, procesar el subárbol derecho.
        if (retVal)
            retVal = infix_process<T, Processor>(node->right(), p);
    }
    */
    if(node != nullptr){ //igual q en kdtree
        retVal = retVal && infix_process<T>(node->left(), p);
        retVal = retVal && p(node->item());
        retVal = retVal && infix_process<T>(node->right(), p);
    }
    //
    return retVal;
}

template <class T>
bool AVLTree<T>::is_a_binary_search_tree() const
{
    bool is_bst = true;
    // TODO
    // Remember: a empty tree is a binary search tree.
    //
    // Remember: for a non empty binary search tree, the in-fix traversal from
    // the root node must follow an ordered sequence of items.
    //
    // Remember: use a lambda function with signature '(T v) -> bool' to
    //  implement the Processor.
    //
    if(!is_empty()){
        std::vector<T> v;
        auto p = [&v](T const &it)
        {
            v.push_back(it);
            return std::is_sorted(v.begin(), v.end());
        };
        is_bst = infix_process<T>(root_node(), p);
    }
    //
    return is_bst;
}

template <class T>
bool AVLTree<T>::is_a_balanced_tree() const
{
    bool is_balanced = true;
#ifndef __ONLY_BSTREE__
    // TODO
    // Remember: this operation is only necessary for the AVLTree.
    // Remember: a empty tree is balanced.
    //
    // Remember: A non empty tree is balanced if both children are balanced
    // and the absolute value of the balance factor of the tree is less or
    // equal to one.
    if(!is_empty()){ //FE <= 1
        is_balanced = std::abs(balance_factor()) <= 1; //1ª comprobación
        //se comprueba por la izq y por la drcha
        is_balanced = is_balanced && left().is_a_balanced_tree(); 
        is_balanced = is_balanced && right().is_a_balanced_tree();
    }
    //
#endif
    return is_balanced;
}

template <class T>
void AVLTree<T>::create_root(T const &v)
{
    assert(is_empty());
    // TODO
    root_ = AVLTNode<T>::create(v);
    current_ = root_; //al crear el árbol nuestro cursor está en root
    parent_ = nullptr;
    //
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());
    assert(!is_empty());
    assert(item() == v);
    assert(current_exists());
    assert(current() == v);
#ifndef __ONLY_BSTREE__
    assert(current_level() == 0);
    assert(height() == 0);
#endif
}

template <class T>
bool AVLTree<T>::search(T const &k)
{
    bool found = false;
    // TODO
    set_current_node(root_node()); //current_ = root_;
    set_parent_node(nullptr); //parent_ = nullptr;
    while(current_node() != nullptr && !found){
        if(current_node()->item() == k)
            found = true;
        else{
            set_parent_node(current_node()); //parent_ = current_;
            if(current_node()->item() > k)
                set_current_node(current_node()->left()); //current_ = current_->left();
            else{
                set_current_node(current_node()->right()); //current_ = current_->right();
            }
        }
    }
    //
    assert(!found || current() == k);
    assert(found || !current_exists());
    return found;
}

template <class T>
void AVLTree<T>::insert(T const &k)
{
    // Check invariants.
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());

    if (!search(k))
    {
        // TODO
        /*if(is_empty()){
            create_root(k);
        }
        else{
            typename AVLTNode<T>::Ref new_node = AVLTNode<T>::create(k);
            if(current_->item() > k)
                current_->set_left(new_node);
            else{
                current_->set_right(new_node);
            }
            new_node->set_parent(current_); //Se establece el nodo actual (current_) como el padre del nuevo nodo
            set_current_node(new_node); //Se actualiza el nodo actual del árbol
        }*/
        current_ = AVLTNode<T>::create(k);
        if(parent_node() == nullptr)
            set_root_node(current_node());
        else if(current_node()->item() < parent_node()->item())
            parent_node()->set_left(current_node());
        else{
            parent_node()->set_right(current_node());
        }
        current_node()->set_parent(parent_node());
        //
        assert(check_parent_chains());
        make_balanced();
        assert(check_parent_chains());
    }
    // Check invariants.
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());

    // check postconditions.
    assert(current_exists());
    assert(current() == k);
}

template <class T>
void AVLTree<T>::remove()
{
    // check preconditions.
    assert(current_exists());

#ifndef NDEBUG
    // the invariants only must be checked for the first recursive call.
    // We use a static variable to count the recursion levels.
    // see section "Static variables in a Function" in
    // ref https://www.geeksforgeeks.org/static-keyword-cpp/ for more info.
    static int recursion_count = 0;
    recursion_count++;
    if (recursion_count == 1)
    {
        // Check invariants.
        assert(is_a_binary_search_tree());
        assert(is_a_balanced_tree());
    }
#endif // NDEBUG

    bool replace_with_subtree = true;
    typename AVLTNode<T>::Ref subtree;

    // TODO
    //  Check which of cases 0,1,2,3 we have (see theory class slides).
    
    if(current_node()->left() == nullptr && current_node()->right() == nullptr){
        //case 0
        subtree = nullptr;
    }
    else if(current_node()->right() == nullptr){
        //case 1
        subtree = current_node()->left();
    }
    else if(current_node()->left() == nullptr){
        //case 2
        subtree = current_node()->right();
    }
    else{
        //case 3
        replace_with_subtree = false;
    }
    //

    if (replace_with_subtree)
    {
        // TODO
        // Manage cases 0,1,2
        // Remember: update subtree to parent links too.
        if(parent_node() == nullptr) //root_ = subtree;
            set_root_node(subtree);
        else if(current_node() == parent_node()->left())
            parent_node()->set_left(subtree);
        else if(current_node() == parent_node()->right())
            parent_node()->set_right(subtree);

        set_current_node(nullptr); //current_ = nullptr;
        //
        assert(check_parent_chains());
        make_balanced();
        assert(check_parent_chains());
    }
    else
    {
        // TODO
        // Manage case 3.
        auto sucesor = current_node();
        find_inorder_sucessor();
        sucesor->set_item(current_node()->item());
        remove();
        //
    }

#ifndef NDEBUG
    // We come back so the recursion count must be decreased.
    recursion_count--;
    assert(recursion_count >= 0);
    if (recursion_count == 0)
    {
        // Only check for the last return.
        // Check invariants.
        assert(is_a_binary_search_tree());
        assert(is_a_balanced_tree());

        // Check postconditions.
        assert(!current_exists());
    }
#endif
}

template <class T>
AVLTree<T>::AVLTree(typename AVLTNode<T>::Ref const &root)
{
    // TODO
    //es como un constructor
    /*root_ = root;
    current_ = root_;
    parent_ = nullptr;*/
    set_root_node(root);
    set_current_node(root_node());
    set_parent_node(nullptr);
    //
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());
    assert(root_node() == root);
    assert(current_node() == root);
    assert(parent_node() == nullptr);
}

template <class T>
void AVLTree<T>::set_left(AVLTree<T> &subtree)
{
    assert(!is_empty());
    // TODO
    root_node()->set_left(subtree.root_node()); // Establecer el subárbol izquierdo del nodo raíz.
    if(subtree.root_node()) //
        subtree.root_node()->set_parent(root_node()); // Establecer el padre del subárbol izquierdo al nodo raíz.
    //
    assert(subtree.is_empty() || left().item() == subtree.item());
    assert(!subtree.is_empty() || left().is_empty());
}

template <class T>
void AVLTree<T>::set_right(AVLTree<T> &subtree)
{
    assert(!is_empty());
    // TODO
    // Remember to set parent's link of the subtree root to this.
    root_node()->set_right(subtree.root_node()); // Establecer el subárbol derecho del nodo raíz.
    if(subtree.root_node()) //
        subtree.root_node()->set_parent(root_node()); // Establecer el padre del subárbol derecho al nodo raíz.
    //
    assert(subtree.is_empty() || right().item() == subtree.item());
    assert(!subtree.is_empty() || right().is_empty());
}

template <class T>
typename AVLTNode<T>::Ref const &AVLTree<T>::current_node() const
{
    // TODO: fixme
    /*typename AVLTNode<T>::Ref fixme;
    return fixme;*/
    return current_; //Get, current ya apunta a node
    //
}

template <class T>
typename AVLTNode<T>::Ref &AVLTree<T>::current_node()
{
    // TODO: fixme
    /*typename AVLTNode<T>::Ref fixme;
    return fixme;*/
    return current_;
    //
}

template <class T>
void AVLTree<T>::set_current_node(typename AVLTNode<T>::Ref const &new_c)
{
    // TODO
    current_ = new_c;
    //
    assert(current_node() == new_c);
}

template <class T>
typename AVLTNode<T>::Ref const &AVLTree<T>::root_node() const
{
    // TODO: fixme
    /*typename AVLTNode<T>::Ref fixme;
    return fixme;*/
    return root_;
    //
}

template <class T>
typename AVLTNode<T>::Ref &AVLTree<T>::root_node()
{
    // TODO: fixme
    /*typename AVLTNode<T>::Ref fixme;
    return fixme;*/
    return root_;
    //
}

template <class T>
void AVLTree<T>::set_root_node(typename AVLTNode<T>::Ref const &new_root)
{
    // TODO
    root_ = new_root;
    //
    assert(root_node() == new_root);
}

template <class T>
typename AVLTNode<T>::Ref const &AVLTree<T>::parent_node() const
{
    // TODO: fixme
    /*typename AVLTNode<T>::Ref fixme;
    return fixme;*/
    return parent_; //Get, parent ya es el padre del node
    //
}

template <class T>
typename AVLTNode<T>::Ref &AVLTree<T>::parent_node()
{
    // TODO: fixme
    /*typename AVLTNode<T>::Ref fixme;
    return fixme;*/
    return parent_;
    //
}

template <class T>
void AVLTree<T>::set_parent_node(typename AVLTNode<T>::Ref const &new_p)
{
    // TODO
    parent_ = new_p;
    //
    assert(parent_node() == new_p);
}

template <class T>
void AVLTree<T>::find_inorder_sucessor()
{
    assert(current_exists());
    assert(is_a_binary_search_tree());

#ifndef NDEBUG
    T old_curr = current();
#endif
    // TODO
    // El sucesor en orden es el nodo más pequeño del subárbol derecho.
    //1º drcha y 2º full izq
    /*if (current_->right() != nullptr){
        // Moverse al subárbol derecho.
        current_ = current_->right();
        // Encontrar el nodo más pequeño en el subárbol derecho.
        while (current_->left() != nullptr)
            current_ = current_->left();
    }
    else{
        // Si no hay subárbol derecho, se mueve hacia arriba
        // hasta encontrar un nodo que sea el hijo izquierdo de su padre.
        // El padre es el sucesor en orden.
        while (parent_ != nullptr && current_ == parent_->right()){
            current_ = parent_;
            parent_ = parent_->parent();
        }
        current_ = parent_;
    }*/
    //1ºdrcha y 2ºfull izq
    set_parent_node(current_node()); //current actual es el padre
    set_current_node(current_node()->right()); //current_ = current_->right();
    while (current_node()->left() != nullptr){ //va bajando actualizando current
        set_parent_node(current_node());
        set_current_node(current_node()->left());
    }
    //
    assert(current_exists() && current_node()->left() == nullptr);
#ifndef NDEBUG
    assert(current() > old_curr);
#endif
}

template <class T>
typename AVLTNode<T>::Ref AVLTree<T>::rotate(typename AVLTNode<T>::Ref &P, int dir)
{
    assert(P != nullptr);
    assert(dir == 0 || dir == 1);
    assert(P->child(1 - dir) != nullptr);
    auto N = P->child(1 - dir); // the child to promote.
#ifdef __DEBUG__
    if (__DEBUG__ > 1)
        std::clog << "Rotating to " << (dir == 0 ? "left" : "right") << " on key " << P->item() << std::endl;
#endif
    // TODO
    // Remember: this operation is only necessary for the AVLTree.
    // Remember: if P has not a parent (it is the tree's current root),
    // the promoted node N will be the new root of the tree.
    // Hint: you can see wikipedia: https://en.wikipedia.org/wiki/Tree_rotation
    auto G = P->parent(); //guardado del padre del nodo actual en G

    //gpDir <- G.child(0)==P ? 0 : 1 no tiene sentido q se haga si es null

    N = P->child(1 - dir); //declarado arriba, se obtiene el hijo de la dir opuesta

    auto CN = N->child(dir); //CN es el hijo de N en la dir de rotación

    P->set_child(1 - dir, CN); //ahora el hijo de P en la dir opuesta es CN

    N->set_child(dir, P); //el hijo de N en la dir de rotación es P

    if (G != nullptr){
        int gpDir;
        if (G->child(0) == P) // 0 -> izq
            gpDir = 0; // P es el hijo izquierdo de G.
        else{
            gpDir = 1; // P es el hijo derecho de G.
        }
                    //dir, padre
        G->set_child(gpDir, N); 
    }
    else{
        N->set_parent(nullptr); //el padre de la dir opuesta (N) pasa a ser null
        set_root_node(N); //y N(nodo de la dir opuesta) pasa a ser la raíz del árbol
    }
    /*
    Guardar referencias:
    ·G: El padre del nodo actual P.
    ·N: El hijo de P en la dirección opuesta a dir (el nodo que será promovido).
    ·CN: El hijo de N en la dirección de dir (el subárbol que será reasignado).
    
    Actualizar enlaces entre P y CN:
    ·P ahora apunta a CN como su hijo en la dirección opuesta a dir.
    ·Si CN no es nulo, su padre se actualiza para que apunte a P.
    
    Actualizar enlaces entre N y P:
    ·N ahora apunta a P como su hijo en la dirección de dir.
    ·P actualiza su padre para que apunte a N
    */
    //
    return N;
}

template <class T>
void AVLTree<T>::make_balanced()
{
#ifdef __ONLY_BSTREE__
    return; // for a BSTree there is no need to balance.
#else
    auto P = parent_node(); // the subtree root node.

    while (P)
    {
        // TODO
        // Check the subtree balance factor to do rotations if needed

        // First, update subtree root node height because we have just done
        // an insertion/deletion in the subtree.
        P->update_height();
        //

        // Second, compute balance factor.
        int bfP = P->balance_factor();
        //

        // Third, check the balance factor to do rotations if needed.
        // Remember: update subtree_root if any rotation is done.
        if (std::abs(bfP) > 1){
            int dir = 0; //Inicializamos la dir de rotación a 0 (izquierda por defecto)

            if(bfP>0)  //Si el FE es positivo, cambiamos dir a 1 (derecha)
                dir = 1;
            
            auto N = P->child(dir); //Obtenemos el hijo de P en la dir det.
            int bfN = N->balance_factor(); //Realiza una rotación simple hacia la dir opuesta
            
            /*
            bfP: Factor de balance del nodo actual (P).
            bfN: Factor de balance del hijo de P en la dirección de desbalance (N).
            */

            if((bfP * bfN) >= 0) //el desbalance está en la misma dirección en ambos niveles (izq-izq o drcha-drcha), es decir, rotación simple
                P = rotate(P, 1 - dir); //se rota hacia la dir opuesta, (drcha-drcha -> rot izq)
            else{ //rotación doble (drcha-izq o izq-drcha), se divide en 2 simples
                rotate(N, dir); //1º se rota en la dir del desblance
                P = rotate(P, 1 - dir); //2º rot en la dir opuesta
            }
        }
        //

        P = P->parent(); // going up.
    }
    // Update the cursor's parent_ node if needed.
    if (current_exists())
        set_parent_node(current_node()->parent());
    assert(!current_exists() || current_node()->parent() == parent_node());
#endif //__ONLY_BSTREE__
}

template <class T>
bool AVLTree<T>::check_parent_chains() const
{
#ifdef __ONLY_BSTREE__
    return true; // for a BSTree there is no need to check this.
#else
    if (!is_empty())
    {
        std::function<void(typename AVLTNode<T>::Ref, std::vector<typename AVLTNode<T>::Ref>)> go_down;
        go_down = [&go_down](typename AVLTNode<T>::Ref node, std::vector<typename AVLTNode<T>::Ref> branch) -> void
        {
            if (node->left() != nullptr || node->right() != nullptr)
            {
                branch.push_back(node);
                if (node->left())
                    // go down by the left
                    go_down(node->left(), branch);
                if (node->right())
                    // go down by the right
                    go_down(node->right(), branch);
            }
            else
            {
                // The node is a leaf node, so check the branch
                // to the tree root node.
                typename AVLTNode<T>::Ref parent = node->parent();
                int idx = static_cast<int>(branch.size()) - 1;
                while (parent && idx >= 0)
                {
                    assert(parent == branch[idx]);
                    --idx;
                    parent = parent->parent();
                }
                assert(idx == -1 && parent == nullptr);
            }
        };
        std::vector<typename AVLTNode<T>::Ref> branch;
        go_down(root_node(), branch);
    }
    return true;
#endif
}

template <class T>
std::tuple<int, int>
compute_min_max_branch_length(AVLTree<T> const &tree)
{
    int min_path_l = std::numeric_limits<int>::max();
    int max_path_l = 0;

    // TODO
    //  Hint: you can use a lambda function to recursive go down through the tree.
    //  A new recursion increase the level in the tree. When a subtree is empty
    //  you have achieved a the leaf of a branch and the current level is e
    //  the branch length ending in this leaf node so we can update
    //  the min/max length values according before returning.
    //  @see: https://stackoverflow.com/questions/2067988/recursive-lambda-functions-in-c11
    //  or check_parent_chains() function the to study similar cases.

    std::function<void(AVLTree<T>, int &, int &, size_t)> go_down;
    go_down = [&go_down](AVLTree<T> tree, int &min_path_l, int &max_path_l, size_t current_level) -> void
    {
        auto left = tree.left();
        auto right = tree.right();
        if (left.is_empty() && right.is_empty()){
            min_path_l = std::min(min_path_l, static_cast<int>(current_level)); //Convierte current_level de size_t a int
            max_path_l = std::max(max_path_l, static_cast<int>(current_level));
        }
        else{
            if (!left.is_empty())
                go_down(left, min_path_l, max_path_l, current_level + 1);
            if (!right.is_empty())
                go_down(right, min_path_l, max_path_l, current_level + 1);
        }
    };
    if (!tree.is_empty())
        go_down(tree, min_path_l, max_path_l, 0);
    else{ //empty tree
        min_path_l = -1;
        max_path_l = -1;
    }
    /*
    Definición de la función lambda go_down:
    ·La función toma como parámetros:
     ·tree: El árbol actual que se está procesando.
     ·min_path_l: Referencia a la longitud mínima de las ramas.
     ·max_path_l: Referencia a la longitud máxima de las ramas.
     ·current_level: El nivel actual en el árbol (profundidad).
    ·Es recursiva y se llama para los subárboles izquierdo y derecho.
    
    Caso base:
    ·Si el árbol actual no tiene subárboles izquierdo ni derecho (es una hoja), actualiza las longitudes mínima y máxima con el nivel actual.
    
    Caso recursivo:
    ·Si el árbol tiene subárboles, llama recursivamente a go_down para el subárbol izquierdo y derecho, incrementando el nivel actual.
    
    Manejo del árbol vacío:
    ·Si el árbol está vacío, las longitudes mínima y máxima se establecen en -1.
    */
    //

    return std::make_tuple(min_path_l, max_path_l);
}
template <class T>
AVLTreeIterator<T> AVLTree<T>::begin() const
{
    typename AVLTNode<T>::Ref node;
    // TODO
    // Encontrar el nodo más pequeño (más a la izquierda).
    node = root_node();
    while (node != nullptr && node->left() != nullptr)
        node = node->left();
    //
    return AVLTreeIterator<T>(node);
}

template <class T>
AVLTreeIterator<T> AVLTree<T>::end() const
{
    return AVLTreeIterator<T>(nullptr);
}
