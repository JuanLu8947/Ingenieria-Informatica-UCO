/**
 * @file test_ip_utils.cpp
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
#include <string>
#include <vector>
#include <exception>

#include "ip_utils.hpp"

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
            std::cerr << "Error: could not open input filename '" << argv[1] << "'." << std::endl;
            std::cerr << "Usage: " << argv[0] << " filename" << std::endl;
            return EXIT_FAILURE;
        }

        IP ip;

        std::string buffer;
        std::istringstream input;
        while (std::getline(input_file, buffer))
        {
            input.str(buffer);
            input.clear();
            std::string command;
            input >> command;
            if (!input || command == "" || command[0] == '#')
                continue;

            if (command == "load")
            {
                std::cout << "Loading ip ... ";
                try
                {
                    input >> ip;
                    std::cout << "ok." << std::endl;
                }
                catch (std::runtime_error &e)
                {
                    std::cout << "Error: detected wrong input ip format."
                              << std::endl;
                }
            }
            else if (command == "show")
            {
                std::cout << "The loaded ip is: " << ip << std::endl;
            }
            else if (command == "to_int")
            {
                std::cout << "The corresponding uint is: " << ip_to_int(ip)
                          << std::endl;
            }
            else
            {
                std::cerr << "Error: unkown command '" << command << "'." << std::endl;
                return EXIT_FAILURE;
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
        std::cerr << "Cough unknown exception!." << std::endl;
        exit_code = EXIT_FAILURE;
    }
    return exit_code;
}
