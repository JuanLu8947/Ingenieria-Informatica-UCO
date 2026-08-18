/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <sstream>
#include <stdexcept>
#include <cassert>

#include <list.hpp>

template <class T>
List<T>::List()
{
    // TODO
    // Remember: in an empty list, the dummy node is linked with itself.
    //diseño nodos enlazados
    dummy_ = DNode<T>::create(); //creación del nodo dummy
    //enlazado del nodo dummy consigo mismo
    dummy_->set_next(dummy_);
    dummy_->set_prev(dummy_);
    size_ = 0;
    //
    assert(is_empty());
}

template <class T>
List<T>::List(std::istream &in) noexcept(false) : List()
{

    // TODO
    // Hint: use std::istringstream to convert from a "string" token value to a template
    // T type value.
    // Remember: throw std::runtime_error("Wrong input format.") exception when an input
    //  format error was found.
    std::string token; 
    in >> token; //volcado de in a token
    if(token == "["){
        in >> token;
        while(not in.eof() && token != "]"){ 
            std::istringstream iss(token); //creación de un flujo de entrada a partir de token
            T value;
            if(!(iss >> value)) //volcado de iss a value y comprobación de que se ha hecho la extraacción correctamente
                throw std::runtime_error("Wrong input format.");
            push_back(value);
            in >> token;
        }
        if(token != "]")
            throw std::runtime_error("Wrong input format.");
    }
    else{
        throw std::runtime_error("Wrong input format.");
    }
    //
}

template <class T>
List<T>::~List()
{
    // Think. We are using smart pointers (shared_ptr) so the nodes will
    // released automatically when the references going off.
}

template <class T>
typename DNode<T>::Ref List<T>::dummy() const
{
    // TODO: recode with respect to your representation.
    return dummy_; //GetDummy
    //
}

template <class T>
bool List<T>::is_empty() const
{
    // TODO: recode with respect to your representation.
    return size() == 0;
    //
}

template <class T>
size_t List<T>::size() const
{
    // TODO: recode with respect to your representation.
    return size_; //GetSize
    //
}

template <class T>
void List<T>::set_size(size_t new_size)
{
    // TODO
    size_ = new_size;
    //
    assert(size() == new_size);
}

template <class T>
typename List<T>::iterator List<T>::begin() const
{

    // TODO: recode with respect to your representation.
    //return ListIterator<T>();
    return iterator(dummy_->next()); 
    /*
     Crea y devuelve un iterador que apunta al nodo siguiente del nodo dummy_. En una lista no vacía, este nodo es el primer elemento de la lista.
    */
    //
}

template <class T>
typename List<T>::iterator List<T>::end() const
{
    // TODO: recode with respect to your representation.
    return iterator(dummy_); //básciamnete el dummy apunta al final de la lista
    //REF: typedef ListIterator<T> iterator;
    //
}

template <class T>
T const &List<T>::front() const
{
    assert(!is_empty());

    // TODO: recode with respect to your representation.
    // Hint: use iterators.
    /*T fixme{};
    return fixme;
    //F(X): return the first Item of the list.*/
    return begin().item();
    /*
    Utiliza el método begin() para obtener un iterador que apunta al primer elemento de la lista y luego llama al método item() del iterador para obtener el valor del primer elemento.
    */
    //
}

template <class T>
T const &List<T>::back() const
{
    assert(!is_empty());

    // TODO: recode with respect to your representation.
    // Hint: use iterators.
    /*T fixme{};
    return fixme;*/
    return end().prev().item(); //back corresponde al último elemento de la lista
    /*
    Utiliza el método end() para obtener un iterador que apunta al final de la lista (el nodo dummy). Luego, llama al método prev() del iterador para obtener un iterador que apunta al último elemento de la lista. Finalmente, llama al método item() del iterador para obtener el valor del último elemento.
    */
    //
}

template <class T>
void List<T>::fold(std::ostream &out) const
{
    // TODO
    //f(x) de plegado, pasa de lista a fichero
    out << "[ ";
    for(auto it = begin(); it != end(); it.goto_next()){ //it.goto_next() avanza al siguiente nodo de la lista
        out << it.item() << " ";
    }
    out << "]";
    //
}

template <class T>
void List<T>::hook(typename DNode<T>::Ref n, typename DNode<T>::Ref pos)
{
#ifndef NDEBUG
    auto old_size = size();
#endif
    // TODO
    // Remember updating the size.
    n->set_prev(pos->prev()); 
    n->set_next(pos);
    pos->prev()->set_next(n);
    pos->set_prev(n);
    size_++;
    //
    assert(size() == old_size + 1);
}

template <class T>
void List<T>::unhook(typename DNode<T>::Ref pos)
{
#ifndef NDEBUG
    auto old_size = size();
#endif
    // TODO
    // Remember updating the size.
    pos->prev()->set_next(pos->next());
    pos->next()->set_prev(pos->prev());
    size_--;
    //
    assert(size() == old_size - 1);
}

template <class T>
typename List<T>::iterator List<T>::insert(typename List<T>::iterator const &pos,
                                           T const &it)
{
#ifndef NDEBUG
    auto old_is_empty = is_empty();
    auto old_size = size();
    auto old_pos_prev = pos.prev();
#endif
    iterator ret_v;
    // TODO
    // Hint: delegate in hook.
    auto new_node = DNode<T>::create(it);
    hook(new_node, pos.node());
    //ret_v = new_node;
    //ret_v = set_node(new_node);
    ret_v.set_node(new_node);
    //
    assert(!old_is_empty || (front() == it && back() == it));
    assert(old_is_empty || ret_v.next() == pos);
    assert(old_is_empty || old_pos_prev == ret_v.prev());
    assert(size() == (old_size + 1));
    return ret_v;
}

template <class T>
typename List<T>::iterator List<T>::remove(List<T>::iterator const &pos)
{
    assert(!is_empty());
#ifndef NDEBUG
    auto old_size = size();
    auto old_pos_next = pos.next();
    auto old_pos_prev = pos.prev();
#endif
    iterator ret_v;
    // TODO
    // Hint: delegate in unkook
    auto i = pos.node();
    unhook(pos.node());
    //ret_v.set(i);
    //ret_v = i;
    ret_v = iterator(old_pos_next); // Establece ret_v al siguiente nodo después de pos
    //
    assert(ret_v == old_pos_next);
    assert(ret_v.prev() == old_pos_prev);
    assert(size() == (old_size - 1));
    return ret_v;
}

template <class T>
void List<T>::push_front(T const &new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
#endif
    // TODO
    //  Hint: delegate in insert();
    insert(begin(), new_it); //en ap -> new_it, begin()
    //
    assert(front() == new_it);
    assert(size() == (old_size + 1));
}

template <class T>
void List<T>::push_back(T const &new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
#endif
    // TODO
    //  Hint: delegate in insert();
    insert(end(), new_it);
    //
    assert(back() == new_it);
    assert(size() == (old_size + 1));
}

template <class T>
void List<T>::pop_front()
{
    assert(!is_empty());
#ifndef NDEBUG
    size_t old_size = size();
#endif
    // TODO
    // Hint: delegate in remove.
    remove(begin()); //lit elimina el primer elemento de la lista
    //
    assert(size() == (old_size - 1));
}

template <class T>
void List<T>::pop_back()
{
    assert(!is_empty());
#ifndef NDEBUG
    size_t old_size = size();
    auto old_end_prev_prev = end().prev().prev();
#endif
    // TODO
    // Hint: delegate in remove.
    remove(end().prev()); //elimna el anterior al último ya que el último es el dummy
    //
    assert(is_empty() || end().prev() == old_end_prev_prev);
    assert(size() == (old_size - 1));
}

template <class T>
typename List<T>::iterator List<T>::find(T const &it, List<T>::iterator const &from) const
{
    iterator ret_v;
    // TODO
    auto i = from;
    while(i != end() && i.item() != it){
        //i.goto_next();
        i = i.next();
    }
    ret_v = i;
    //
    assert(ret_v == end() || ret_v.item() == it);
    return ret_v;
}

template <class T>
void List<T>::splice(iterator const &pos, List<T> &list2,
                     iterator const &first, iterator const &last)
{
#ifndef NDEBUG
    size_t old_size = size();
    size_t old_l2_size = list2.size();
    auto old_range_size = first.distance(last);
#endif
    // TODO
    // Hint: if the range [first, last) is empty, nothing must be done.
    int range_size = first.distance(last);
    auto pos_node = pos.node();
    auto prev_pos_node = pos_node->prev();
    auto first_node = first.node(); 
    auto prev_first_node = first_node->prev();
    auto last_node = last.node();
    auto prev_last_node = last_node->prev();

    //Splice l2 range into this
    prev_pos_node->set_next(first_node);
    first_node->set_prev(prev_pos_node);
    pos_node->set_prev(prev_last_node);
    prev_last_node->set_next(pos_node);

    // remove range from list2
    prev_first_node->set_next(last_node);
    last_node->set_prev(prev_first_node);

    //Update lists sizes
    size_ += range_size;
    list2.size_ -= range_size;
    //
    assert(size() == (old_size + old_range_size));
    assert(list2.size() == (old_l2_size - old_range_size));
}

template <class T>
void List<T>::splice(iterator const &pos, List<T> &list2)
{
#ifndef NDEBUG
    size_t old_size = size();
    auto old_list2_size = list2.size();
#endif
    // TODO
    // Hint: Delegate in splice the list2 range [begin, end).
    splice(pos, list2, list2.begin(), list2.end());
    /*
    (iterator const &pos, List<T> &list2,
        iterator const &first, iterator const &last)
    */
    //
    assert(size() == (old_size + old_list2_size));
    assert(list2.size() == 0);
    assert(list2.is_empty());
}

template <class T>
void List<T>::splice(iterator const &pos, List<T> &list2, iterator const &i)
{
#ifndef NDEBUG
    size_t old_size = size();
    auto old_list2_size = list2.size();
#endif
    // TODO
    // Hint: Delegate in splice the list2 range [i, i.next()).
    splice(pos, list2, i, i.next());
    /*
    (iterator const &pos, List<T> &list2,
        iterator const &first, iterator const &last)
    */
    //
    assert(size() == (old_size + 1));
    assert(list2.size() == (old_list2_size - 1));
}

template <class T>
template <class Compare>
void List<T>::merge(List<T> &other, Compare comp)
{
    // TODO
    // Remember: The nodes of the other list are spliced into this list.
    auto iter1 = begin();
    auto iter2 = other.begin(); //l2 = other
    while(iter1 != end() && iter2 != other.end()){
        if(comp(iter1.item(), iter2.item())){
            iter1.goto_next();
        }
        else{
            auto tmp = iter2;
            iter2.goto_next();
            splice(iter1, other, tmp, tmp.next());
        }
    }
    if(iter2 != other.end()){
        splice(iter1, other, other.begin(), other.end());
    }
    //
}

template <class T>
template <class Compare>
void List<T>::sort(Compare comp)
{
    // TODO
    // Remember: we want a complexity in to N Log(N) so mergeSort algorithm is
    // a good candidate to sort the list.
    // Hint: Do a recursive implementation, splitting the list into two halves,
    // sorting recursively each part and merging the sorted lists to obtain
    // the full sorted list.
    if(size() > 1){
        auto tmp = List<T>();
        auto midPoint = begin(); //midpoint ← begin().gotoNext(size() / 2)
        midPoint.goto_next(size() / 2);
        tmp.splice(tmp.begin(), *this, midPoint, end());
        sort(comp);
        tmp.sort(comp);
        merge(tmp, comp);
    }
    // The empty list and a list with only one element are sorted by default.
    
    //
}
