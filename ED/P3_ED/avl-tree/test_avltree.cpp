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
#include "avltree.hpp"

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

        auto tree = std::make_shared<AVLTree<int>>();
        AVLTreeIterator<int> iter;
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

            if (command == "IS_EMPTY")
            {
                std::cout << "Is it empty? "
                          << (tree->is_empty() ? "Y." : "N.")
                          << std::endl;
            }
            else if (command == "HEIGHT")
            {
                std::cout << "Height = " << tree->height() << std::endl;
            }
            else if (command == "SIZE")
            {
                std::cout << "Size = " << tree->size() << std::endl;
            }
            else if (command == "BALANCE_FACTOR")
            {
                std::cout << "Balance factor = " << tree->balance_factor()
                          << std::endl;
            }
            else if (command == "UNFOLD")
            {
                try
                {
                    std::cout << "Unfold tree ... ";
                    tree = std::make_shared<AVLTree<int>>(input_line);
                    std::cout << " ok." << std::endl;
                }
                catch (std::runtime_error &e)
                {
                    std::cout << "Input error: " << e.what() << std::endl;
                }
            }
#ifdef __ONLY_BSTREE__
            else if (command == "CREATE_PERFECTLY_BALANCED")
            {
                std::vector<int> data;
                int v;
                while (input_line >> v)
                    data.push_back(v);
                std::cout << "Creating a perfectly balanced bstree ... ";
                *tree = create_perfectly_balanced_bstree<int>(data);
                std::cout << " ok. " << std::endl;
            }
#endif // __ONLY_BSTREE__
            else if (command == "HAS")
            {
                int key;
                input_line >> key;
                if (!input_line)
                {
                    std::cerr << "Error: wrong format of test file."
                              << std::endl;
                    return EXIT_FAILURE;
                }
                std::cout << "Has key value " << key << " ?: "
                          << (tree->has(key) ? "Y." : "N.") << std::endl;
            }
            else if (command == "SEARCH")
            {
                int key;
                input_line >> key;
                if (!input_line)
                {
                    std::cerr << "Error: wrong format of test file."
                              << std::endl;
                    return EXIT_FAILURE;
                }
                std::cout << "Search for key value " << key << " ... "
                          << (tree->search(key) ? " found." : "not found.")
                          << std::endl;
            }
            else if (command == "CURRENT_EXISTS")
            {
                std::cout << "Has a current item? "
                          << (tree->current_exists() ? "Y." : "N.")
                          << std::endl;
            }
            else if (command == "CURRENT")
            {
                std::cout << "Current item: "
                          << tree->current() << std::endl;
            }
            else if (command == "CURRENT_LEVEL")
            {
                std::cout << "Current's level is " << tree->current_level()
                          << std::endl;
            }
            else if (command == "INSERT")
            {
                std::string buffer;
                std::getline(input_line, buffer);
                std::istringstream numbers(buffer);
                int key;
                numbers >> key;
                std::cout << "Inserting ";
                while (numbers)
                {
                    std::cout << key << ' ';
                    tree->insert(key);
                    numbers >> key;
                }
                std::cout << std::endl;
            }
            else if (command == "REMOVE")
            {
                std::cout << "Removing key " << tree->current();
                tree->remove();
                std::cout << " ok." << std::endl;
            }
            else if (command == "FOLD")
            {
                tree->fold(std::cout);
                std::cout << std::endl;
            }
            else if (command == "COMPUTE_MIN_MAX_BRANCH_LENGTH")
            {
                std::cout << "Computing min and max branch length ... ";
                int min, max;
                std::tie(min, max) = compute_min_max_branch_length(*tree);
                std::cout << " min length = " << min
                          << " max length = " << max << std::endl;
            }
            else if (command == "ITER_BEGIN")
            {
                std::cout << "Move iterator at the beginning ... ";
                iter = tree->begin();
                std::cout << "ok." << std::endl;
            }
            else if (command == "ITER_NEXT")
            {
                std::cout << "Move iterator to next position ... ";
                ++iter;
                std::cout << "ok." << std::endl;
            }
            else if (command == "ITER_PREV")
            {
                std::cout << "Move iterator to the prev position ... ";
                --iter;
                std::cout << "ok." << std::endl;
            }
            else if (command == "ITER_IS_END")
            {
                std::cout << "Is iterator at the end ? ";
                std::cout << (iter == tree->end() ? "Y" : "N") << std::endl;
            }
            else if (command == "ITER_IS_END")
            {
                std::cout << "Is iterator at the end ? ";
                std::cout << (iter == tree->end() ? "Y" : "N") << std::endl;
            }
            else if (command == "ITER_IS_END")
            {
                std::cout << "Is iterator at the end ? ";
                std::cout << (iter == tree->end() ? "Y" : "N") << std::endl;
            }
            else if (command == "ITER_ITEM")
            {
                std::cout << "*iter = ";
                std::cout << *iter << std::endl;
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
