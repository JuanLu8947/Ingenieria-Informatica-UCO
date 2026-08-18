/**
 * @file test_astar.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <exception>
#include <vector>

#include <city.hpp>
#include <a_star_algorithm.hpp>
#include <dijkstra_algorithm.hpp>

int Verbose_level = 0;

template <class T>
std::ostream &
operator<<(std::ostream &out, const std::vector<T> &v)
{
    out << '[';
    for (size_t i = 0; i < v.size(); ++i)
        out << ' ' << v[i];
    out << " ]";
    return out;
}

/**
 * @brief Functional to compute earth distances between cities.
 */
struct Distance
{
    float operator()(Graph<City, float>::VertexRef const &a,
                     Graph<City, float>::VertexRef const &b) const
    {
        assert(a != nullptr);
        assert(b != nullptr);
        return static_cast<float>(distance(a->item(), b->item()));
    }
};

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
        Graph<City, float> map(input_file);
        std::string src_key;
        std::string dst_key;
        input_file >> src_key >> dst_key;
        if (!input_file)
        {
            std::cerr << "Error: wrong input format. None cities for connect." << std::endl;
            return EXIT_FAILURE;
        }
        auto src = map.find_vertex(src_key);
        if (!src)
        {
            std::cerr << "Error: do not found city '" << src_key << "'." << std::endl;
            return EXIT_FAILURE;
        }
        auto dst = map.find_vertex(dst_key);
        if (!dst)
        {
            std::cerr << "Error: do not found city '" << dst_key << "'." << std::endl;
            return EXIT_FAILURE;
        }

        std::vector<size_t> predecessors;
        std::vector<float> distances;
        Distance dist_proc;
        size_t iterations = a_star_algorithm<City, Distance>(map, src, dst,
                                                             dist_proc,
                                                             predecessors, distances);
        std::cout << "Predecessors: " << predecessors << std::endl;
        std::cout << "Distances   : " << distances << std::endl;
        auto path = dijkstra_path(src->label(), dst->label(), predecessors);
        std::cout << "Path from: '" << src_key << "' to '" << dst_key << "': ";
        for (auto v : path)
        {
            std::cout << ' ' << map.vertex(v)->item().key();
        }
        std::cout << " distance: " << distances[dst->label()] << std::endl;
        std::cout << "Straight line distance: "
                  << distance(src->item(), dst->item()) << " km." << std::endl;
        std::cout << "Number of iterations: " << iterations << std::endl;
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
