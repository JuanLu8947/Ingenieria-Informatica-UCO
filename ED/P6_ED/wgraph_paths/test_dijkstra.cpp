/**
 * @file test_dijkstra.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <exception>
#include <vector>
#include <unordered_map>

#include "item.hpp"
#include "city.hpp"
#include "graph.hpp"
#include "dijkstra_algorithm.hpp"

int Verbose_level = 0;

template <class T>
std::ostream &
print_predecessors(std::ostream &out,
                   const Graph<T, float> &g,
                   std::vector<size_t> const &predecessors)
{
    out << '[';
    for (size_t n = 0; n < predecessors.size(); ++n)
        out << " ['" << g.vertex(n)->item().key() << "']:'" << g.vertex(predecessors[n])->item().key() << '\'';
    out << " ]";
    return out;
}

template <class T>
std::ostream &
print_distances(std::ostream &out,
                const Graph<T, float> &g,
                std::vector<float> const &distances)
{
    out << '[';
    for (size_t n = 0; n < distances.size(); ++n)
        out << " ['" << g.vertex(n)->item().key() << "']=" << distances[n];
    out << " ]";
    return out;
}

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

    std::vector<size_t> predecessors;
    std::vector<float> distances;
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
    dijkstra_algorithm<T>(g, src_vertex, predecessors, distances);
    std::cout << "Predecessors: ";
    print_predecessors<T>(std::cout, g, predecessors);
    std::cout << std::endl;
    std::cout << "Distances   : ";
    print_distances<T>(std::cout, g, distances);
    std::cout << std::endl;
    auto path = dijkstra_path(src_vertex->label(), dst_vertex->label(), predecessors);
    std::cout << "Path from: '" << src_key << "' to '" << dst_key << "': ";
    for (auto label : path)
    {
        std::cout << ' ' << g.vertex(label)->item().key();
    }
    if (distances[dst_vertex->label()] == std::numeric_limits<float>::infinity())
        std::cout << " distance: inf" << std::endl;
    else
        std::cout << " distance: " << distances[dst_vertex->label()] << std::endl;
    return EXIT_SUCCESS;
}

int main(int argc, const char *argv[])
{
    int exit_code = EXIT_SUCCESS;
    try
    {
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
