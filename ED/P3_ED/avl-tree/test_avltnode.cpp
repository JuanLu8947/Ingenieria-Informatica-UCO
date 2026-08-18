/**
 * @file test_avltree.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <vector>
#include <valarray>
#include "avltree_node.hpp"

int main(int argc, const char *argv[])
{
    int exit_code = EXIT_SUCCESS;
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: " << argv[0] << " filename" << std::endl;
            return EXIT_FAILURE;
        }
        std::ifstream input_file(argv[1]);
        if (!input_file)
        {
            std::cerr << "Error: could not open input filename '"
                      << argv[1] << "'." << std::endl;
            std::cerr << "Usage: " << argv[0] << " filename" << std::endl;
            return EXIT_FAILURE;
        }
        AVLTNode<int>::Ref node[10];
        std::string command;
        std::cout << std::unitbuf;
        std::istringstream input_line;
        std::string line;
        while (std::getline(input_file, line))
        {
            if (line.size() == 0 || line[0] == '#')
                continue;
            input_line.clear();
            input_line.str(line);
            if (!(input_line >> command))
            {
                std::cerr << "Error: wrong format of test file."
                          << std::endl;
                return EXIT_FAILURE;
            }

            if (command == "NODE_CREATE")
            {
                int idx;
                int item;
                input_line >> idx;
                input_line >> item;
                std::cout << "Creating node idx " << idx << " with item "
                          << item << std::endl;
                node[idx] = AVLTNode<int>::create(item);
            }
            else if (command == "NODE_ITEM")
            {
                int idx;
                input_line >> idx;
                std::cout << "Node idx " << idx << " item: "
                          << node[idx]->item() << std::endl;
            }
            else if (command == "NODE_HEIGHT")
            {
                int idx;
                input_line >> idx;
                std::cout << "Node idx " << idx << " height: "
                          << node[idx]->height() << std::endl;
            }
            else if (command == "NODE_PARENT")
            {
                int idx;
                input_line >> idx;
                std::cout << "Node idx " << idx << " parent's item = "
                          << node[idx]->parent()->item() << std::endl;
            }
            else if (command == "NODE_LEFT_CHILD")
            {
                int idx;
                input_line >> idx;
                std::cout << "Node idx " << idx << " left child's item = "
                          << node[idx]->left()->item() << std::endl;
            }
            else if (command == "NODE_RIGHT_CHILD")
            {
                int idx;
                input_line >> idx;
                std::cout << "Node idx " << idx << " right child's item = "
                          << node[idx]->right()->item() << std::endl;
            }
            else if (command == "NODE_ATTACH_LEFT")
            {
                int c_idx, p_idx;
                input_line >> c_idx >> p_idx;
                std::cout << "Attaching node idx " << c_idx
                          << " as left child of node idx " << p_idx
                          << std::endl;
                node[p_idx]->set_left(node[c_idx]);
            }
            else if (command == "NODE_ATTACH_RIGHT")
            {
                int c_idx, p_idx;
                input_line >> c_idx >> p_idx;
                std::cout << "Attaching node idx " << c_idx
                          << " as right child of node idx " << p_idx
                          << std::endl;
                node[p_idx]->set_right(node[c_idx]);
            }
            else if (command == "NODE_DETTACH_LEFT")
            {
                int idx;
                input_line >> idx;
                std::cout << "Dettaching left child of node idx " << idx
                          << std::endl;
                node[idx]->set_left(nullptr);
            }
            else if (command == "NODE_DETTACH_RIGHT")
            {
                int idx;
                input_line >> idx;
                std::cout << "Dettaching right child of node idx " << idx
                          << std::endl;
                node[idx]->set_right(nullptr);
            }
            else if (command == "NODE_BALANCE_FACTOR")
            {
                int idx;
                input_line >> idx;
                std::cout << "Balance factor for node idx " << idx << " = ";
                std::cout << node[idx]->balance_factor() << std::endl;
            }
            else
            {
                std::cerr << "Error: input command unknown '" << command
                          << "'." << std::endl;
                return EXIT_FAILURE;
            }
        }
    }
    catch (...)
    {
        std::cerr << "Caught unknown exception!." << std::endl;
        exit_code = EXIT_FAILURE;
    }
    return exit_code;
}
