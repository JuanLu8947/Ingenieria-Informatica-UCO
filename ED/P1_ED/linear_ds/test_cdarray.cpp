/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "cdarray.hpp"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <windows.h>
#include <werapi.h>
void avoid_abort_dialog()
{
    SetErrorMode(GetErrorMode() | SEM_NOGPFAULTERRORBOX);
    WerSetFlags(WER_FAULT_REPORTING_NO_UI);
}
#else
void avoid_abort_dialog()
{
    // In Linux this is not necessary.
}
#endif

int main(int argc, const char *argv[])
{
    int exit_code = EXIT_SUCCESS;
    avoid_abort_dialog();
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: test_cdarray test_case" << std::endl;
            return EXIT_FAILURE;
        }
        std::string filename = argv[1];

        std::ifstream input(argv[1]);
        if (!input)
        {
            std::cerr << "Error: could not open input filename '" << argv[1] << "'." << std::endl;
            return EXIT_FAILURE;
        }

        auto array = std::make_shared<CDArray<int>>();

        while (input)
        {
            std::string operation;
            input >> operation;
            if (input)
            {
                if (operation == "CREATE")
                {
                    size_t value;
                    input >> value;
                    std::cout << "Creating cdarray with capacity " << value
                              << " ... ";
                    array = std::make_shared<CDArray<int>>();
                    std::cout << "ok." << std::endl;
                }
                else if (operation == "PUSH_FRONT")
                {
                    int value;
                    input >> value;
                    std::cout << "Push front " << value << " ... ";
                    array->push_front(value);
                    std::cout << "ok." << std::endl;
                }
                else if (operation == "PUSH_BACK")
                {
                    int value;
                    input >> value;
                    std::cout << "Push back " << value << " ... ";
                    array->push_back(value);
                    std::cout << "ok." << std::endl;
                }
                else if (operation == "POP_FRONT")
                {
                    std::cout << "Pop front (" << array->get(0) << ") ... ";
                    array->pop_front();
                    std::cout << "ok." << std::endl;
                }
                else if (operation == "POP_BACK")
                {
                    std::cout << "Pop back (" << array->get(array->size() - 1) << ") ... ";
                    array->pop_back();
                    std::cout << "ok." << std::endl;
                }
                else if (operation == "INSERT")
                {
                    size_t pos;
                    int value;
                    input >> pos >> value;
                    std::cout << "Inserting at pos " << pos << " the value "
                              << value << " ... ";
                    array->insert(pos, value);
                    std::cout << "ok." << std::endl;
                }
                else if (operation == "REMOVE")
                {
                    size_t pos;
                    input >> pos;
                    std::cout << "Removing from pos " << pos << " the value "
                              << array->get(pos) << " ... ";
                    array->remove(pos);
                    std::cout << "ok." << std::endl;
                }
                else if (operation == "SIZE")
                {
                    std::cout << "Array size = " << array->size()
                              << std::endl;
                }
                else if (operation == "CAPACITY")
                {
                    std::cout << "Array capacity = " << array->capacity()
                              << std::endl;
                }
                else if (operation == "IS_EMPTY")
                {
                    std::cout << "Is array empty()? "
                              << (array->is_empty() ? "Y" : "N")
                              << std::endl;
                }
                else if (operation == "IS_FULL")
                {
                    std::cout << "Is array full()? "
                              << (array->is_full() ? "Y" : "N")
                              << std::endl;
                }
                else if (operation == "FRONT")
                {
                    std::cout << "Front value is "
                              << array->get(0) << std::endl;
                }
                else if (operation == "BACK")
                {
                    std::cout << "Back value is "
                              << array->get(array->size() - 1) << std::endl;
                }
                else if (operation == "SET")
                {
                    size_t pos;
                    int value;
                    input >> pos >> value;
                    std::cout << "Setting at pos " << pos << " the value "
                              << value << " ... ";
                    array->set(pos, value);
                    std::cout << "ok." << std::endl;
                }
                else if (operation == "GET")
                {
                    size_t pos;
                    input >> pos;
                    std::cout << "Value at pos " << pos << " is ";
                    std::cout << array->get(pos) << std::endl;
                }
                else if (operation == "FOLD")
                {
                    std::cout << "Folding array: ";
                    array->fold(std::cout);
                    std::cout << std::endl;
                }
                else if (operation == "UNFOLD")
                {
                    std::string line;
                    std::getline(input, line);
                    std::istringstream buffer(line);
                    try
                    {
                        std::cout << "Unfolding the string '"
                                  << line << "' ... ";
                        array = std::make_shared<CDArray<int>>(buffer);
                        std::cout << "ok." << std::endl;
                    }
                    catch (std::runtime_error const &e)
                    {
                        std::cout << "Wrong input format." << std::endl;
                    }
                }
                else
                {
                    std::cerr << "Error: operation not found? '"
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
