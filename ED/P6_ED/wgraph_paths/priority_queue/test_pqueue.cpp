#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <exception>
#include <vector>
#include <priority_queue.hpp>

/** @brief Load a vector of items from input stream.
 * input format:
 * [ <item0>' '...<item_n-1> ]
 */
template <class T>
std::istream &operator>>(std::istream &in, std::vector<T> &data)
{
    data.clear();
    std::string token;
    in >> token;
    if (token == "[")
    {
        while (in >> token && token != "]")
        {
            std::istringstream buff(token);
            T v;
            if (buff >> v)
                data.push_back(v);
            else
                throw std::runtime_error("wrong input format.");
        }
        if (token != "]")
            throw std::runtime_error("wrong input format.");
    }
    else
        throw std::runtime_error("wrong input format.");
    return in;
}

/** @brief Load a vector of items from input stream.
 * output format:
 * [ <item0> ... <item_n-1> ]
 */
template <class T>
std::ostream &operator<<(std::ostream &out, std::vector<T> const &data)
{
    out << "[ ";
    for (auto const &v : data)
        std::cout << v << ' ';
    out << "]";
    return out;
}

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
        std::vector<int> data;
        std::string command;
        PriorityQueue<int> pqueue(data, std::less_equal<int>());
        std::string line;

        while (std::getline(input_file, line))
        {
            if (line.empty() || line[0] == '#')
                continue;
            std::istringstream in(line);
            in >> command;
            if (command == "create")
            {
                data.clear();
                std::string order;
                in >> order;
                std::cout << "Creating heap with order: ";
                if (order == "asc")
                {
                    pqueue = PriorityQueue<int>(data, std::less_equal<int>());
                    std::cout << "ascended" << std::endl;
                }
                else if (order == "desc")
                {
                    pqueue = PriorityQueue<int>(data, std::greater_equal<int>());
                    std::cout << "descended" << std::endl;
                }
                else
                {
                    std::cerr << "Unknown order: " << order << std::endl;
                    exit_code = EXIT_FAILURE;
                }
            }
            else if (command == "is_empty")
            {
                std::cout << (pqueue.is_empty() ? "empty" : "not empty") << std::endl;
            }
            else if (command == "size")
            {
                std::cout << "size = " << pqueue.size() << std::endl;
            }
            else if (command == "front")
            {
                std::cout << "front = " << pqueue.front() << std::endl;
            }
            else if (command == "enqueue")
            {
                std::cout << "Enqueue: ";
                int v;
                while (in >> v)
                {
                    pqueue.enqueue(v);
                    std::cout << " " << v;
                }
                std::cout << std::endl;
            }
            else if (command == "dequeue")
            {
                std::cout << "Dequeue: ";
                pqueue.dequeue();
                std::cout << " ok." << std::endl;
            }
            else
            {
                std::cerr << "Unknown command: " << command << std::endl;
                exit_code = EXIT_FAILURE;
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
