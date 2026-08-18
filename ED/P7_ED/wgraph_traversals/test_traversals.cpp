/**
 * @file test_traversals.cpp
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
#include <exception>
#include <vector>

#include "item.hpp"
#include "graph.hpp"
#include "wgraph_traversals.hpp"
#include "prim_algorithm.hpp"
#include "kruskal_algorithm.hpp"

int Verbose_level = 0;

template <class T>
int do_df_scan(std::istream &input_file)
{
    typename T::key_t start_key;
    std::vector<std::pair<typename Graph<T, float>::VertexRef,
                          typename Graph<T, float>::VertexRef>>
        vertices;

    auto p = [&vertices](typename Graph<T, float>::VertexRef &v,
                         typename Graph<T, float>::VertexRef &u) -> void
    {
        vertices.push_back(std::make_pair(v, u));
    };

    Graph<T, float> g(input_file);
    if ((input_file >> start_key))
    {
        auto start = g.find_first(start_key);
        if (start == g.vertices_end())
        {
            std::cerr << "Error: could not find the start node." << std::endl;
            return EXIT_FAILURE;
        }
        depth_first_scan(g, start, start, p);
    }
    else
    {
        depth_first_scan(g, p);
    }

    std::cout << "DF scans:";
    for (auto &e : vertices)
    {
        if (e.first == e.second)
            std::cout << std::endl
                      << '\t';
        std::cout << ' ' << e.first->item().key() << ':' << e.second->item().key();
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}

template <class T>
int do_bf_scan(std::istream &input_file)
{
    typename T::key_t start_key;
    std::vector<std::pair<typename Graph<T, float>::VertexRef,
                          typename Graph<T, float>::VertexRef>>
        vertices;

    auto p = [&vertices](typename Graph<T, float>::VertexRef &v,
                         typename Graph<T, float>::VertexRef &u) -> void
    {
        vertices.push_back(std::make_pair(v, u));
    };

    Graph<T, float> g(input_file);
    if ((input_file >> start_key))
    {
        auto start = g.find_first(start_key);
        if (start == g.vertices_end())
        {
            std::cerr << "Error: could not find the start node." << std::endl;
            return EXIT_FAILURE;
        }
        breadth_first_scan(g, start, p);
    }
    else
    {
        breadth_first_scan(g, p);
    }

    std::cout << "BF scans:";
    for (auto &e : vertices)
    {
        if (e.first == e.second)
            std::cout << std::endl
                      << '\t';
        std::cout << ' ' << e.first->item().key() << ':' << e.second->item().key();
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}

template <class T>
int do_prim_scan(std::istream &input_file)
{
    Graph<T, float> g(input_file);
    typename T::key_t start_node_key;
    if (!(input_file >> start_node_key))
    {
        std::cerr << "Error: could not read the start node key."
                  << std::endl;
        return EXIT_FAILURE;
    }
    auto start_node = g.find_first(start_node_key);
    if (start_node == g.vertices_end())
    {
        std::cerr << "Error: could not find the start node." << std::endl;
        return EXIT_FAILURE;
    }
    std::vector<typename Graph<T, float>::EdgeRef> MST;
    float total_weight = 0.0;
    std::cout << "Minimum Spanning tree rooted at '" << start_node_key << "':";

    try
    {
        total_weight = prim_algorithm<T>(g, start_node, MST);
    }
    catch (std::runtime_error &e)
    {
        std::cout << " !!Error: The input graph is unconnected." << std::endl;
        return EXIT_SUCCESS;
    }

    for (size_t i = 0; i < MST.size(); ++i)
    {
        float w = MST[i]->item();
        typename T::key_t u = MST[i]->first()->item().key();
        typename T::key_t v = MST[i]->second()->item().key();
        if (v < u)
            std::swap(u, v);
        std::cout << ' ' << w << ":(" << u << ',' << v << ')';
    }
    std::cout << std::endl;
    std::cout << "Total weight: " << total_weight << std::endl;
    return EXIT_SUCCESS;
}

template <class T>
int do_kruskal_scan(std::istream &input_file)
{
    Graph<T, float> g(input_file);
    std::vector<typename Graph<T, float>::EdgeRef> MST;

    float total_weight = 0.0;
    std::cout << "Minimum Spanning tree :";

    try
    {
        total_weight = kruskal_algorithm<T>(g, MST);
    }
    catch (std::runtime_error &e)
    {
        std::cout << " !!Error: The input graph is unconnected." << std::endl;
        return EXIT_SUCCESS;
    }

    for (auto &e : MST)
    {
        std::cout << ' ' << e->item() << ":("
                  << e->first()->item().key() << ','
                  << e->second()->item().key() << ')';
    }
    std::cout << std::endl;
    std::cout << "Total weight: " << total_weight << std::endl;
    return EXIT_SUCCESS;
}

template <class T>
int do_ts_scan(std::istream &input_file)
{
    std::list<typename Graph<T, String>::VertexRef> sorting;
    Graph<T, String> g(input_file);
    topological_sorting(g, sorting);

    std::cout << "Topological sorting:";
    for (auto &v : sorting)
        std::cout << ' ' << v->item();
    std::cout << std::endl;

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
        std::string scan_type, vertex_type;
        if (!(input_file >> scan_type >> vertex_type))
        {
            std::cerr << "Error: could not read scan and the type signature."
                      << std::endl;
            return EXIT_FAILURE;
        }

        if (scan_type == "DF")
        {
            if (vertex_type == "INT")
                exit_code = do_df_scan<Int>(input_file);
            else if (vertex_type == "STRING")
                exit_code = do_df_scan<String>(input_file);
            else
            {
                std::cerr << "Error: unknown graph type." << std::endl;
                return EXIT_FAILURE;
            }
        }
        else if (scan_type == "BF")
        {
            if (vertex_type == "INT")
                exit_code = do_bf_scan<Int>(input_file);
            else if (vertex_type == "STRING")
                exit_code = do_bf_scan<String>(input_file);
            else
            {
                std::cerr << "Error: unknown graph type." << std::endl;
                return EXIT_FAILURE;
            }
        }
        else if (scan_type == "PRIM")
        {
            if (vertex_type == "INT")
                exit_code = do_prim_scan<Int>(input_file);
            else if (vertex_type == "STRING")
                exit_code = do_prim_scan<String>(input_file);
            else
            {
                std::cerr << "Error: unknown graph type." << std::endl;
                return EXIT_FAILURE;
            }
        }
        else if (scan_type == "KRUSKAL")
        {
            if (vertex_type == "INT")
                exit_code = do_kruskal_scan<Int>(input_file);
            else if (vertex_type == "STRING")
                exit_code = do_kruskal_scan<String>(input_file);
            else
            {
                std::cerr << "Error: unknown graph type." << std::endl;
                return EXIT_FAILURE;
            }
        }
        else if (scan_type == "TS")
        {
            if (vertex_type == "INT")
                exit_code = do_ts_scan<Int>(input_file);
            else if (vertex_type == "STRING")
                exit_code = do_ts_scan<String>(input_file);
            else
            {
                std::cerr << "Error: unknown graph type." << std::endl;
                return EXIT_FAILURE;
            }
        }
        else
        {
            std::cerr << "Error: unknown scan type." << std::endl;
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
        std::cerr << "Caught unknown exception!." << std::endl;
        exit_code = EXIT_FAILURE;
    }
    return exit_code;
}
