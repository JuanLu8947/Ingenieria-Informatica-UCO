/**
 * @file test_trie_node.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include <ios>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <exception>
#include <string>
#include <algorithm>

#include "trie_node.hpp"

#if defined WIN32 || defined _WIN32 || defined __WIN32__ || defined WIN64 || defined _WIN64 || defined __WIN64 || defined _WINDOWS
#include <windows.h>
#endif

int main(int argc, const char *argv[])
{
    int exit_code = EXIT_SUCCESS;
#if defined WIN32 || defined _WIN32 || defined __WIN32__ || defined WIN64 || defined _WIN64 || defined __WIN64 || defined _WINDOWS
    SetConsoleOutputCP(CP_UTF8);
#endif
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
            std::cerr << "Error: could not open input filename '" << argv[1] << "'." << std::endl;
            std::cerr << "Usage: " << argv[0] << " filename" << std::endl;
            return EXIT_FAILURE;
        }
        TrieNode::Ref node = TrieNode::create();
        std::string command;
        std::istringstream input_line;
        std::cout << std::unitbuf;
        std::string buffer;
        while (std::getline(input_file, buffer))
        {

            input_line.clear();
            input_line.str(buffer);
            input_line >> command;
            if (!input_line || command.empty() || command[0] == '#')
                continue;

            if (command == "IS_KEY")
            {
                std::cout << "Is it key?: " << (node->is_key() ? "Yes." : "No.")
                          << std::endl;
            }
            else if (command == "SET_IS_KEY")
            {
                int state;
                input_line >> state;
                std::cout << "seting is key state to: " << (state ? "True" : "False")
                          << std::endl;
                node->set_is_key_state(state);
            }
            else if (command == "SET_CHILD")
            {
                std::string symbol;
                input_line.ignore();
                input_line >> symbol;
                node->set_child(symbol, TrieNode::create());
                std::cout << "Set child for symbol '" << symbol << "'."
                          << std::endl;
            }
            else if (command == "HAS")
            {
                std::string symbol;
                input_line.ignore();
                input_line >> symbol;
                std::cout << "Has '" << symbol << "'?: "
                          << (node->has(symbol) ? "yes." : "no.") << std::endl;
            }
            else if (command == "FIND")
            {
                std::string symbol;
                input_line.ignore();
                input_line >> symbol;
                std::cout << "Found '" << symbol << "': "
                          << (node->find_child(symbol) ? "yes." : "no.") << std::endl;
            }
            else if (command == "CURRENT_EXISTS")
            {
                std::cout << "Does current exist? "
                          << (node->current_exists() ? "yes." : "no.") << std::endl;
            }
            else if (command == "CURRENT_SYMBOL")
            {
                std::cout << "Current symbol '"
                          << node->current_symbol() << "'." << std::endl;
            }
            else if (command == "PRINT")
            {
                std::vector<std::string> symbols;
                node->goto_first_child();
                while (node->current_exists())
                {
                    symbols.push_back(node->current_symbol());
                    node->goto_next_child();
                }
                std::sort(symbols.begin(), symbols.end());
                std::cout << "Sorted symbols:";
                for (auto s : symbols)
                    std::cout << ' ' << s;
                std::cout << std::endl;
            }
            else if (command == "FOLD")
            {
                std::cout << "Fold: ";
                node->fold(std::cout) << std::endl;
            }
            else if (command == "UNFOLD")
            {
                std::cout << "Unfolding ... ";
                try
                {
                    node = TrieNode::create(input_line);
                    std::cout << " ok." << std::endl;
                }
                catch (std::runtime_error &e)
                {
                    std::cout << "Runtime exception: '" << e.what() << "'." << std::endl;
                }
            }
            else
            {
                std::cerr << "Error: command unknown '" << command << "'." << std::endl;
                return EXIT_FAILURE;
            }
        }
    }
    catch (std::runtime_error &e)
    {
        std::cerr << "Runtime exception: " << e.what() << std::endl;
        exit_code = EXIT_FAILURE;
    }
    catch (...)
    {
        std::cerr << "Catched unknown exception!." << std::endl;
        exit_code = EXIT_FAILURE;
    }
    return exit_code;
}
