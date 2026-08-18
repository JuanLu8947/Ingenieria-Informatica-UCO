/**
 * @file test_edge.cpp
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

#include <edge.hpp>
#include <item.hpp>

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

        std::vector<Vertex<Char>::Ref> vertices(10);
        std::vector<Edge<Char, float>::Ref> edges(10);
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

            if (command == "VERTEX_CREATE")
            {
                size_t label;
                Char data;
                if (!(input >> label))
                    throw std::runtime_error("Wrong command");
                if (!(input >> data))
                    throw std::runtime_error("Wrong command");
                std::cout << "Creating a vertex with label " << label << " ... ";
                vertices[label] = Vertex<Char>::create(label, data);
                std::cout << "ok." << std::endl;
            }
            else if (command == "VERTEX_PRINT")
            {
                size_t label;
                if (!(input >> label))
                    throw std::runtime_error("Wrong command");
                std::cout << "Vertex with label "
                          << vertices[label]->label()
                          << " visited flag: " << (vertices[label]->is_visited() ? "T" : "F")
                          << " data: '" << vertices[label]->item()
                          << "' data key: '" << vertices[label]->item().key() << "'."
                          << std::endl;
            }
            else if (command == "VERTEX_SET_VISITED")
            {
                size_t label;
                if (!(input >> label))
                    throw std::runtime_error("Wrong command");
                bool is_visited;
                if (!(input >> is_visited))
                    throw std::runtime_error("Wrong command");
                std::cout << "Setting visited flag of vertex with label "
                          << label << " to " << (is_visited ? "T" : "F")
                          << " ...";
                vertices[label]->set_visited(is_visited);
                std::cout << "ok." << std::endl;
            }
            else if (command == "VERTEX_SET_ITEM")
            {
                size_t label;
                if (!(input >> label))
                    throw std::runtime_error("Wrong command");
                Char data;
                if (!(input >> data))
                    throw std::runtime_error("Wrong command");
                std::cout << "Setting item of vertex with label "
                          << label << " to '" << data
                          << "' ...";
                vertices[label]->set_item(data);
                std::cout << "ok." << std::endl;
            }
            else if (command == "EDGE_CREATE")
            {
                size_t e_label, u_label, v_label;
                if (!(input >> e_label >> u_label >> v_label))
                    throw std::runtime_error("Wrong command");
                float data;
                if (!(input >> data))
                    throw std::runtime_error("Wrong command");
                std::cout << "Creating edge " << e_label << " connecting "
                          << " vertices (" << u_label << "," << v_label
                          << ") with data " << data << " ...";
                edges[e_label] = Edge<Char, float>::create(vertices[u_label], vertices[v_label], data);
                std::cout << "ok." << std::endl;
            }
            else if (command == "EDGE_PRINT")
            {
                size_t e_label;
                if (!(input >> e_label))
                    throw std::runtime_error("Wrong command");
                std::cout << "Edge " << e_label << " connecting vertices ("
                          << edges[e_label]->first()->label() << ","
                          << edges[e_label]->second()->label() << ")"
                          << ", visited flag: " << (edges[e_label]->is_visited() ? "T" : "F")
                          << ", data: " << edges[e_label]->item() << std::endl;
            }
            else if (command == "EDGE_SET_VISITED")
            {
                size_t label;
                if (!(input >> label))
                    throw std::runtime_error("Wrong command");
                bool is_visited;
                if (!(input >> is_visited))
                    throw std::runtime_error("Wrong command");
                std::cout << "Setting visited flag of edge with label "
                          << label << " to " << (is_visited ? "T" : "F")
                          << " ...";
                edges[label]->set_visited(is_visited);
                std::cout << "ok." << std::endl;
            }
            else if (command == "EDGE_SET_ITEM")
            {
                size_t label;
                if (!(input >> label))
                    throw std::runtime_error("Wrong command");
                float data;
                if (!(input >> data))
                    throw std::runtime_error("Wrong command");
                std::cout << "Setting item of edge with label "
                          << label << " to '" << data << "' ...";
                edges[label]->set_item(data);
                std::cout << "ok." << std::endl;
            }
            else if (command == "EDGE_OTHER")
            {
                size_t e_label;
                if (!(input >> e_label))
                    throw std::runtime_error("Wrong command");

                auto first = edges[e_label]->first();
                auto second = edges[e_label]->second();

                std::cout << "Edge (" << first->label() << "," << second->label()
                          << ")->other(" << first->label() << ") is ";
                auto v = edges[e_label]->other(first);
                std::cout << v->label() << "." << std::endl;

                std::cout << "Edge (" << first->label() << "," << second->label()
                          << ")->other(" << second->label() << ") is ";
                auto u = edges[e_label]->other(second);
                std::cout << u->label() << "." << std::endl;
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
