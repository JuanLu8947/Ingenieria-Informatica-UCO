/**
 * @file test_graph.cpp
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

#include "graph.hpp"
#include "item.hpp"
#include "city.hpp"

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
            return EXIT_FAILURE;
        }

        std::shared_ptr<Graph<Char, float>> graph = nullptr;
        std::vector<Vertex<Char>::Ref> vertices(10);
        std::vector<Edge<Char, float>::Ref> edges(10);
        VertexIterator<Char, float> current_vertex;
        EdgeIterator<Char, float> current_edge;
        size_t e_label = 0;

        std::cout << std::unitbuf;

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

            if (command == "GRAPH_CREATE")
            {
                bool directed;
                if (!(input >> directed))
                    throw std::runtime_error("Wrong command");
                std::cout << "Creating "
                          << (directed ? "a directed" : "an undirected")
                          << " graph ... ";
                graph = std::make_shared<Graph<Char, float>>(directed);
                std::cout << " ok." << std::endl;
            }
            else if (command == "IS_DIRECTED")
            {
                std::cout << "Is a directed graph? "
                          << (graph->is_directed() ? "Y" : "N") << std::endl;
            }
            else if (command == "IS_EMPTY")
            {
                std::cout << "Is the graph empty? "
                          << (graph->is_empty() ? "Y" : "N") << std::endl;
            }
            else if (command == "HAS_VERTEX")
            {
                int idx;
                if (!(input >> idx))
                    throw std::runtime_error("Wrong command");
                std::cout << "Has the graph the vertex with label = " << idx << "? "
                          << (graph->has(vertices[idx]) ? "Y" : "N") << std::endl;
            }
            else if (command == "HAS_EDGE")
            {
                int idx;
                if (!(input >> idx))
                    throw std::runtime_error("Wrong command");
                std::cout << "Has the graph an edge  linking the vertex with label "
                          << edges[idx]->first()->label() << " with  vertex with label "
                          << edges[idx]->second()->label() << "? "
                          << (graph->has(edges[idx]) ? "Y" : "N") << std::endl;
            }
            else if (command == "NUM_VERTICES")
            {
                std::cout << "Number of vertices: "
                          << graph->num_vertices() << std::endl;
            }
            else if (command == "NUM_EDGES")
            {
                std::cout << "Number of edges: "
                          << graph->num_edges() << std::endl;
            }
            else if (command == "ADD_VERTEX")
            {
                Char data;
                if (!(input >> data))
                    throw std::runtime_error("Wrong command");
                std::cout << "Adding vertex with data item: '" << data
                          << "' ... ";
                auto vertex = graph->add_vertex(data);
                vertices[vertex->label()] = vertex;
                current_vertex = graph->get_iterator(vertex);
                std::cout << "ok." << std::endl;
            }
            else if (command == "PRINT_CURRENT_VERTEX")
            {
                if (current_vertex != graph->vertices_end())
                {
                    std::cout << "Current vertex with label "
                              << (*current_vertex)->label()
                              << " visited flag: " << ((*current_vertex)->is_visited() ? "T" : "F")
                              << " data: '" << (*current_vertex)->item()
                              << "' data key: '" << (*current_vertex)->item().key() << "'."
                              << std::endl;
                }
                else
                    std::cout << "Current vertex doesn't exist." << std::endl;
            }
            else if (command == "ADD_EDGE")
            {
                size_t u_label, v_label;
                if (!(input >> u_label >> v_label))
                    throw std::runtime_error("Wrong command");
                float data;
                if (!(input >> data))
                    throw std::runtime_error("Wrong command");
                std::cout << "Adding edge " << e_label << " for vertices ('"
                          << vertices[u_label]->item() << "','"
                          << vertices[v_label]->item() << "') with data item: '" << data
                          << "' ... ";
                auto edge = graph->add_edge(vertices[u_label], vertices[v_label], data);
                edges[e_label++] = edge;
                current_vertex = graph->find_first(vertices[u_label]->item().key());
                current_edge = graph->find_first(current_vertex, vertices[v_label]->item().key());
                std::cout << "ok." << std::endl;
            }
            else if (command == "PRINT_CURRENT_EDGE")
            {
                if (current_edge != graph->edges_end(current_vertex))
                {
                    std::cout << "Current edge ('"
                              << (*current_edge)->first()->item() << "','"
                              << (*current_edge)->second()->item()
                              << "'), visited flag: " << ((*current_edge)->is_visited() ? "T" : "F")
                              << ", data: " << (*current_edge)->item()
                              << std::endl;
                }
                else
                    std::cout << "Current edge doesn't exist." << std::endl;
            }
            else if (command == "GOTO_VERTEX")
            {
                Char::key_t u_key;
                if (!(input >> u_key))
                    throw std::runtime_error("Wrong command 'GOTO_VERTEX'");
                std::cout << "Moving vertex iterator to vertex with key '" << u_key
                          << "' ...";
                current_vertex = graph->find_first(u_key);
                current_edge = graph->edges_begin(current_vertex);
                std::cout << " ok." << std::endl;
            }
            else if (command == "GOTO_EDGE")
            {
                Char::key_t u_key, v_key;
                if (!(input >> u_key >> v_key))
                    throw std::runtime_error("Wrong command");
                std::cout << "Moving edge iterator to edge ('"
                          << u_key << "','" << v_key << "') ...";
                current_vertex = graph->find_first(u_key);
                current_edge = graph->find_first(current_vertex, v_key);
                std::cout << " ok." << std::endl;
            }
            else if (command == "PRINT_VERTICES")
            {
                std::cout << "Vertices: ";
                for (auto iter = graph->vertices_begin(); iter != graph->vertices_end(); ++iter)
                {
                    std::cout << " '" << (*iter)->item()
                              << "'";
                }
                std::cout << std::endl;
            }
            else if (command == "PRINT_INCIDENT_EDGES")
            {
                std::cout << "Edges incident in current vertex: ";
                for (auto iter = graph->edges_begin(current_vertex); iter != graph->edges_end(current_vertex); ++iter)
                {
                    std::cout << " ('"
                              << (*iter)->first()->item()
                              << "','"
                              << (*iter)->second()->item()
                              << "')";
                }
                std::cout << std::endl;
            }
            else if (command == "IS_ADJACENT")
            {
                size_t u_label, v_label;
                if (!(input >> u_label >> v_label))
                    throw std::runtime_error("Wrong command");
                std::cout << "Is adjacent the vertex '"
                          << vertices[u_label]->item()
                          << "' to vertex '"
                          << vertices[v_label]->item()
                          << "' ?: "
                          << (graph->is_adjacent(vertices[u_label], vertices[v_label]) ? "Y" : "N")
                          << std::endl;
            }
            else if (command == "GOTO_FIRST_VERTEX")
            {
                std::cout << "Moving iterator to first vertex ...";
                current_vertex = graph->vertices_begin();
                std::cout << " ok." << std::endl;
            }
            else if (command == "GOTO_NEXT_VERTEX")
            {
                std::cout << "Moving cursor to next vertex ...";
                current_vertex++;
                std::cout << " ok." << std::endl;
            }
            else if (command == "FIND_VERTEX")
            {
                char key;
                if (!(input >> key))
                    throw std::runtime_error("Wrong command");
                std::cout << "Finding vertex with key '" << key << "' ... ";
                current_vertex = graph->find_first(key);
                std::cout << (current_vertex != graph->vertices_end() ? " found." : " didn't found.") << std::endl;
            }
            else if (command == "FIND_NEXT_VERTEX")
            {
                char key;
                if (!(input >> key))
                    throw std::runtime_error("Wrong command");
                std::cout << "Finding next vertex with key '" << key << "' ... ";
                current_vertex++;
                while (current_vertex != graph->vertices_end() && (*current_vertex)->item().key() != key)
                    ++current_vertex;
                std::cout << (current_vertex != graph->vertices_end() ? " found." : " didn't found.") << std::endl;
            }
            else if (command == "RESET")
            {
                bool state;
                if (!(input >> state))
                    throw std::runtime_error("Wrong command");
                std::cout << "Reseting visited flags to " << (state ? "T" : "F")
                          << " ... ";
                graph->reset(state);
                std::cout << " ok." << std::endl;
            }
            else if (command == "CHECK_VISITED")
            {
                std::cout << "Checking visited flags:" << std::endl;
                for (auto v_iter = graph->vertices_begin(); v_iter != graph->vertices_end(); ++v_iter)
                {
                    std::cout << "\tVertex '" << (*v_iter)->item().key() << "':"
                              << ((*v_iter)->is_visited() ? "T" : "F")
                              << " incident edges:";
                    for (auto e_iter = graph->edges_begin(v_iter); e_iter != graph->edges_end(v_iter); ++e_iter)
                    {
                        std::cout << " (" << (*e_iter)->first()->item().key() << ','
                                  << (*e_iter)->second()->item().key() << "):"
                                  << ((*e_iter)->is_visited() ? "T" : "F");
                    }
                    std::cout << std::endl;
                }
            }
            else if (command == "FOLD")
            {
                std::cout << "Folding graph ... " << std::endl;
                graph->fold(std::cout);
                std::cout << std::endl;
            }
            else if (command == "UNFOLD")
            {
                std::cout << "unfolding graph ... ";
                try
                {
                    graph = std::make_shared<Graph<Char, float>>(input_file);
                    std::cout << " ok." << std::endl;
                }
                catch (std::runtime_error &e)
                {
                    std::cout << "runtime error: '" << e.what() << "'." << std::endl;
                }
            }
            else if (command == "STRING")
            {
                std::cout << "unfolding a graph<String, float> ... ";
                try
                {
                    Graph<String, float> g(input_file);
                    std::cout << " ok." << std::endl;
                    g.fold(std::cout);
                    std::cout << std::endl;
                }
                catch (std::runtime_error &e)
                {
                    std::cout << "runtime error: '" << e.what() << "'." << std::endl;
                }
            }
            else if (command == "INTEGER")
            {
                std::cout << "unfolding a graph<Int, float> ... ";
                try
                {
                    Graph<Int, float> g(input_file);
                    std::cout << " ok." << std::endl;
                    g.fold(std::cout);
                    std::cout << std::endl;
                }
                catch (std::runtime_error &e)
                {
                    std::cout << "runtime error: '" << e.what() << "'." << std::endl;
                }
            }
            else if (command == "CITY")
            {
                std::cout << "unfolding a graph<City, float> ... ";
                try
                {
                    Graph<City, float> g(input_file);
                    std::cout << " ok." << std::endl;
                    g.fold(std::cout);
                    std::cout << std::endl;
                }
                catch (std::runtime_error &e)
                {
                    std::cout << "runtime error: '" << e.what() << "'." << std::endl;
                }
            }
            else if (command == "VERTICES_VECTOR")
            {
                auto vertices_array = get_vertices(*graph);
                std::cout << "Vertices:";
                for (auto &v : vertices_array)
                    std::cout << ' ' << v->item().key();
                std::cout << std::endl;
            }
            else if (command == "EDGES_VECTOR")
            {
                auto edges_array = get_edges(*graph);
                std::cout << "Edges:";
                for (auto &e : edges_array)
                    std::cout << ' ' << e->first()->item().key() << ':' << e->second()->item().key();
                std::cout << std::endl;
            }
            else if (command == "REMOVE_CURRENT_VERTEX")
            {
                std::cout << "Removing current vertex '" << (*current_vertex)->item().key()
                          << "' ...";
                graph->remove_vertex(*current_vertex);
                std::cout << " ok." << std::endl;
            }
            else if (command == "REMOVE_CURRENT_EDGE")
            {
                std::cout << "Removing current edge '"
                          << (*current_edge)->first()->item().key() << "':'"
                          << (*current_edge)->second()->item().key()
                          << "' ...";
                graph->remove_edge((*current_edge)->first(), (*current_edge)->second());
                std::cout << " ok." << std::endl;
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
