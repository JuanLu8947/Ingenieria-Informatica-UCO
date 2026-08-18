/**
 * @file test_floyd.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <exception>
#include <vector>
#include <valarray>

#include <item.hpp>
#include <city.hpp>
#include <graph.hpp>
#include <floyd_algorithm.hpp>

int Verbose_level = 0;

template <class T>
int do_the_work(std::istream &input_file)
{
    Graph<T, float> g(input_file);
    typename T::key_t src_key;
    typename T::key_t dst_key;
    if (!(input_file >> src_key >> dst_key))
    {
        std::cerr << "Error: could not read start/end vertices." << std::endl;
        return EXIT_FAILURE;
    }
    auto dst_vertex = g.find_vertex(dst_key);
    if (!dst_vertex)
    {
        std::cerr << "Error: could not find dst node '"
                  << dst_key << "'." << std::endl;
        return EXIT_FAILURE;
    }
    auto src_vertex = g.find_vertex(src_key);
    if (!src_vertex)
    {
        std::cerr << "Error: could not find src node '"
                  << src_key << "'." << std::endl;
        return EXIT_FAILURE;
    }
    FMatrix D;
    IMatrix I;
    floyd_algorithm<T>(g, D, I);
    std::cout << "D matrix: " << std::endl;
    print_floyd_D(std::cout, D);
    std::cout << "I matrix:" << std::endl;
    print_floyd_I(std::cout, I);
    std::list<size_t> path;
    if (D[src_vertex->label()][dst_vertex->label()] < std::numeric_limits<float>::infinity())
        path = floyd_path(src_vertex->label(), dst_vertex->label(), I);

    std::cout << "Path from: '" << src_key << "' to '" << dst_key << "': ";
    for (auto v : path)
    {
        std::cout << ' ' << g.vertex(v)->item().key();
    }
    std::cout << " distance: " << D[src_vertex->label()][dst_vertex->label()] << std::endl;

    return EXIT_SUCCESS;
}

int main(int argc, const char *argv[])
{
    int exit_code = EXIT_SUCCESS;
    try
    {
        std::cout << std::unitbuf;

        if (argc < 2 || argc > 3)
        {
            std::cerr << "Usage: " << argv[0] << " [-v] filename" << std::endl;
            return EXIT_FAILURE;
        }
        std::ifstream input_file;
        if (std::string(argv[1]) == std::string("-v"))
        {
            Verbose_level = 1;
            input_file.open(argv[2]);
        }
        else
            input_file.open(argv[1]);
        if (!input_file)
        {
            std::cerr << "Error: could not open input filename '" << argv[1] << "'." << std::endl;
            return EXIT_FAILURE;
        }
        std::string type;
        input_file >> type;
        input_file.ignore();
        if (type == "INT")
            exit_code = do_the_work<Int>(input_file);
        else if (type == "STRING")
            exit_code = do_the_work<String>(input_file);
        else if (type == "CITY")
            exit_code = do_the_work<City>(input_file);
        else
        {
            std::cerr << "Error: unknown graph type." << std::endl;
            return EXIT_FAILURE;
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
