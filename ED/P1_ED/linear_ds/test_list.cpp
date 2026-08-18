/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "list.hpp"

int main(int argc, const char *argv[])
{
    int exit_code = EXIT_SUCCESS;
    try
    {
        std::cout.setf(std::ios::unitbuf); // unbuffering output.

        if (argc != 2)
        {
            std::cerr << "Usage: test_list test_case" << std::endl;
            return EXIT_FAILURE;
        }
        std::string filename = argv[1];

        std::ifstream input(argv[1]);
        if (!input)
        {
            std::cerr << "Error: could not open input filename '" << argv[1]
                      << "'." << std::endl;
            return EXIT_FAILURE;
        }
        std::vector<DNode<int>::Ref> nodes(5);
        auto l = std::make_shared<List<int>>();
        auto iterator = l->begin();

        while (input)
        {
            std::string operation;
            input >> operation;
            if (input)
            {
                // TESTS FOR DNODE ******************************************
                if (operation == "CREATE_NODE")
                {
                    int idx;
                    input >> idx;
                    std::cout << "Creating node " << idx << " ... ";
                    nodes[idx] = DNode<int>::create(idx);
                    std::cout << "ok." << std::endl;
                }
                else if (operation == "LINK_NODE_NEXT")
                {
                    int idx1, idx2;
                    input >> idx1 >> idx2;
                    std::cout << "Linking node " << idx2 << " as next of node "
                              << idx1 << " ... ";
                    nodes[idx1]->set_next(nodes[idx2]);
                    std::cout << "ok." << std::endl;
                }
                else if (operation == "LINK_NODE_PREV")
                {
                    int idx1, idx2;
                    input >> idx1 >> idx2;
                    std::cout << "Linking node " << idx2 << " as prev of node "
                              << idx1 << " ... ";
                    nodes[idx1]->set_prev(nodes[idx2]);
                    std::cout << "ok." << std::endl;
                }
                else if (operation == "GET_NODE_NEXT")
                {
                    int idx;
                    input >> idx;
                    std::cout << "Next item of ";
                    std::cout << nodes[idx]->item() << " is ";
                    std::cout << nodes[idx]->next()->item() << std::endl;
                }
                else if (operation == "GET_NODE_PREV")
                {
                    int idx;
                    input >> idx;
                    std::cout << "Prev item of ";
                    std::cout << nodes[idx]->item() << " is ";
                    std::cout << nodes[idx]->prev()->item() << std::endl;
                }
                else if (operation == "NODE_ITEM")
                {
                    int idx;
                    input >> idx;
                    std::cout << "Getting Node " << idx << " item: ";
                    std::cout << nodes[idx]->item() << std::endl;
                }
                else if (operation == "SET_NODE_ITEM")
                {
                    int idx, value;
                    input >> idx >> value;
                    nodes[idx]->set_item(value);
                    std::cout << "Setting node " << idx << " item to: "
                              << value << std::endl;
                }
                // TEST FOR SIMPLE LIST ******************************
                else if (operation == "CREATE_LIST")
                {
                    std::cout << "Creating a new list ... ";
                    l = std::make_shared<List<int>>();
                    iterator = l->begin();
                    std::cout << "ok." << std::endl;
                }
                else if (operation == "IS_EMPTY")
                {
                    std::cout << "Is it empty? " << (l->is_empty() ? "Y" : "N")
                              << std::endl;
                }
                else if (operation == "FRONT")
                {
                    std::cout << "From item: " << l->front() << std::endl;
                }
                else if (operation == "SIZE")
                {
                    std::cout << "List's size: " << l->size() << std::endl;
                }
                else if (operation == "PUSH_FRONT")
                {
                    int v;
                    input >> v;
                    std::cout << "Inserting " << v << " at from ... ";
                    l->push_front(v);
                    std::cout << "ok." << std::endl;
                }
                else if (operation == "POP_FRONT")
                {
                    std::cout << "Removing front ... ";
                    l->pop_front();
                    std::cout << "ok." << std::endl;
                }
                // TEST LIST ITERATOR **************************************
                else if (operation == "BEGIN")
                {
                    std::cout << "Getting iterator at begin ... ";
                    iterator = l->begin();
                    std::cout << "ok." << std::endl;
                }
                else if (operation == "END")
                {
                    std::cout << "Getting iterator at end ... ";
                    iterator = l->end();
                    std::cout << "ok." << std::endl;
                }
                else if (operation == "ITEM")
                {
                    std::cout << "Getting iterator's item: " << iterator.item()
                              << std::endl;
                }
                else if (operation == "SET_ITEM")
                {
                    int v;
                    input >> v;
                    std::cout << "Setting iterator's item to " << v << " ... ";
                    iterator.set_item(v);
                    std::cout << "ok." << std::endl;
                }
                else if (operation == "GOTO_NEXT")
                {
                    std::string line;
                    std::getline(input, line);
                    std::istringstream buffer(line);
                    size_t dist = 1;
                    buffer >> dist;
                    std::cout << "Move iterator to next " << dist << " positions ... ";
                    iterator.goto_next(dist);
                    std::cout << "ok." << std::endl;
                }
                else if (operation == "GOTO_PREV")
                {
                    std::string line;
                    std::getline(input, line);
                    std::istringstream buffer(line);
                    size_t dist = 1;
                    buffer >> dist;
                    std::cout << "Move iterator to prev " << dist << " positions ... ";
                    iterator.goto_prev(dist);
                    std::cout << "ok." << std::endl;
                }
                else if (operation == "AT_END")
                {
                    std::cout << "Is iterator at end position?: ";
                    std::cout << ((iterator == l->end()) ? "Y" : "N")
                              << std::endl;
                }
                else if (operation == "DISTANCE_TO_END")
                {
                    std::cout << "Distance to END ... ";
                    std::cout << iterator.distance(l->end()) << std::endl;
                }
                else if (operation == "DISTANCE_TO_BEGIN")
                {
                    std::cout << "Distance to BEGIN ... ";
                    std::cout << l->begin().distance(iterator) << std::endl;
                }
                //  TEST INSERT/REMOVE  *************************************
                else if (operation == "INSERT")
                {
                    int v;
                    input >> v;
                    std::cout << "Inserting " << v << " ... ";
                    l->insert(iterator, v);
                    std::cout << "ok." << std::endl;
                }
                else if (operation == "REMOVE")
                {
                    std::cout << "Removing " << iterator.item()
                              << " from list ... " << std::endl;
                    l->remove(iterator);
                    std::cout << "ok." << std::endl;
                }
                else if (operation == "PUSH_BACK")
                {
                    int v;
                    input >> v;
                    std::cout << "Inserting " << v << " at the end ... ";
                    l->push_back(v);
                    std::cout << "ok." << std::endl;
                }
                else if (operation == "POP_BACK")
                {
                    std::cout << "Removing " << l->back()
                              << " from the end ... ";
                    l->pop_back();
                    std::cout << "ok." << std::endl;
                }
                // TEST FOLD/UNFOLD **************************************
                else if (operation == "UNFOLD")
                {
                    std::string line;
                    std::getline(input, line);
                    std::istringstream buffer(line);
                    try
                    {
                        std::cout << "Unfolding list ... ";
                        l = std::make_shared<List<int>>(buffer);
                        std::cout << "ok." << std::endl;
                    }
                    catch (std::runtime_error const &e)
                    {
                        std::cout << "Wrong input format." << std::endl;
                    }
                }
                else if (operation == "FOLD")
                {
                    std::cout << "Folding list: ";
                    l->fold(std::cout);
                    std::cout << std::endl;
                }
                else if (operation == "FIND")
                {
                    int v;
                    input >> v;
                    std::cout << "Finding value " << v << " from position: "
                              << iterator.item() << " ... ";
                    iterator = l->find(v, iterator);
                    std::cout << (iterator == l->end() ? "NOT FOUND." : "FOUND.")
                              << std::endl;
                }
                else if (operation == "MERGE")
                {
                    std::string line;
                    std::getline(input, line);
                    std::istringstream buffer(line);
                    auto l2 = std::make_shared<List<int>>(buffer);
                    std::cout << "Merging with " << line << " ... ";
                    l->merge<std::less<int>>(*l2, std::less<int>());
                    std::cout << "ok." << std::endl;
                }
                else if (operation == "SPLICE_RANGE")
                {
                    std::string line;
                    std::getline(input, line);
                    std::istringstream buffer(line);
                    int idx1, idx2;
                    buffer >> idx1 >> idx2;
                    auto l2 = std::make_shared<List<int>>(buffer);
                    auto first = l2->begin();
                    first.goto_next(idx1);
                    auto last = l2->begin();
                    last.goto_next(idx2);
                    std::cout << "Splice the list ";
                    l2->fold(std::cout);
                    std::cout << " range ["
                              << first.item() << ',' << last.item()
                              << ") at current list position ";
                    if (iterator == l->end())
                        std::cout << "end ... ";
                    else
                        std::cout << iterator.item() << " ... ";
                    l->splice(iterator, *l2, first, last);
                    std::cout << "ok." << std::endl;
                    std::cout << "Remainder list: ";
                    l2->fold(std::cout);
                    std::cout << std::endl;
                }
                else if (operation == "SPLICE_ALL")
                {
                    std::string line;
                    std::getline(input, line);
                    std::istringstream buffer(line);
                    auto l2 = std::make_shared<List<int>>(buffer);
                    std::cout << "Splice the list " << line << " at position ";
                    if (iterator == l->end())
                        std::cout << "end ... ";
                    else
                        std::cout << iterator.item() << " ... ";
                    l->splice(iterator, *l2);
                    std::cout << "ok." << std::endl;
                }
                else if (operation == "SPLICE_POS")
                {
                    std::string line;
                    std::getline(input, line);
                    std::istringstream buffer(line);
                    int pos;
                    buffer >> pos;
                    auto l2 = std::make_shared<List<int>>(buffer);
                    auto i = l2->begin();
                    i.goto_next(pos);
                    std::cout << "Splice the list " << line << " position "
                              << i.item() << " at current list position ";
                    if (iterator == l->end())
                        std::cout << "end ... ";
                    else
                        std::cout << iterator.item() << " ... ";
                    l->splice(iterator, *l2, i);
                    std::cout << "ok." << std::endl;
                }
                else if (operation == "SORT_LE")
                {
                    std::cout << "Sorting (<=)  ... ";
                    l->sort(std::less_equal<int>());
                    std::cout << "ok." << std::endl;
                }
                else if (operation == "SORT_GE")
                {
                    std::cout << "Sorting (>=)  ... ";
                    l->sort(std::greater_equal<int>());
                    std::cout << "ok." << std::endl;
                }
                else
                {
                    std::cerr << "Error: operation not found '"
                              << operation << "'." << std::endl;
                    return EXIT_FAILURE;
                }
            }
        }
    }
    catch (std::runtime_error &e)
    {
        std::cerr << "Run time exception: " << e.what() << std::endl;
        exit_code = EXIT_FAILURE;
    }
    catch (...)
    {
        std::cerr << "Catched unknown exception!." << std::endl;
        exit_code = EXIT_FAILURE;
    }
    return exit_code;
}
