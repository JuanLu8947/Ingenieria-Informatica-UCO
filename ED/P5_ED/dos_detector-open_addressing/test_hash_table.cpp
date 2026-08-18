/**
 * @file test_hash_table.cpp
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
#include <vector>
#include <exception>

#include <hash_table.hpp>

std::istream &
operator>>(std::istream &in, std::vector<int> &v)
{
    size_t size;
    in >> size;
    if (in)
    {
        v.resize(size);
        for (size_t i = 0; i < size && in; ++i)
            in >> v[i];
    }
    return in;
}

uint64_t int_to_uint64_t(const int &k)
{
    return static_cast<uint64_t>(k);
}

int main(int argc, const char *argv[])
{
    std::srand(0); // Use always the same random seed.
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
        std::shared_ptr<HashTable<int, int>> hash_table;
        HashTableIterator<int, int> current_iter;
        std::string buffer;
        std::istringstream input;
        while (std::getline(input_file, buffer))
        {
            if (!input_file || buffer == "" || buffer[0] == '#')
                continue;

            input.str(buffer);
            input.clear();
            std::string command;
            input >> command;
            if (!input)
                continue;

            if (command == "create")
            {
                std::uint64_t m, p, a, b;
                input >> m >> p >> a >> b;
                if (!input)
                    throw std::runtime_error("Wrong command format.");
                hash_table = std::make_shared<HashTable<int, int>>(m, int_to_uint64_t, LPHash::create(UHash(m, p, a, b)));
                std::cout << "Created table with size: " << m << std::endl;
            }
            else if (command == "load_factor")
            {
                std::cout << "load factor: " << hash_table->load_factor()
                          << std::endl;
            }
            else if (command == "has")
            {
                int key;
                input >> key;
                if (!input)
                    throw std::runtime_error("Wrong command format.");
                std::cout << "Has key '" << key << "'?: "
                          << (hash_table->find(key) == hash_table->end() ? "no" : "yes") << std::endl;
            }
            else if (command == "size")
            {
                std::cout << "Table size: " << hash_table->size() << std::endl;
            }
            else if (command == "insert")
            {
                int key;
                int v;
                input >> key >> v;
                if (!input)
                    throw std::runtime_error("Wrong command format.");
                current_iter = hash_table->insert(key, v);

                std::cout << "Inserted pair <" << key << ":" << v << "> at table position: "
                          << current_iter.index() << std::endl;
            }
            else if (command == "find")
            {
                int key;
                input >> key;
                if (!input)
                    throw std::runtime_error("Wrong command format.");
                current_iter = hash_table->find(key);
                if (current_iter.is_valid())
                    std::cout << "Key '" << key << "' found." << std::endl;
                else
                    std::cout << "Key '" << key << "' not found." << std::endl;
            }
            else if (command == "remove")
            {
                std::cout << "Removing key: " << current_iter.key()
                          << " ... ";
                hash_table->remove(current_iter);
                std::cout << " ok." << std::endl;
            }
            else if (command == "set_value")
            {
                int v;
                input >> v;
                if (!input)
                    throw std::runtime_error("Wrong command format.");
                std::cout << "Setting current value to " << v << " ... ";
                current_iter.set_value(v);
                std::cout << " ok." << std::endl;
            }
            else if (command == "show")
            {
                HashTable<int, int> const *const_ht = static_cast<HashTable<int, int> const *>(hash_table.get());
                std::cout << "Table: [";
                for (size_t idx = 0; idx < hash_table->size(); ++idx)
                {
                    std::cout << idx << ":";
                    if (const_ht->entry(idx).is_valid())
                        std::cout << "<" << const_ht->entry(idx).key() << ',' << const_ht->entry(idx).value() << "> ";
                    else if (const_ht->entry(idx).is_deleted())
                        std::cout << "x ";
                    else
                        std::cout << "- ";
                }
                std::cout << "]" << std::endl;
            }
            else if (command == "is_valid")
            {
                std::cout << "Is valid?: " << (current_iter.is_valid() ? "True" : "False") << std::endl;
            }
            else if (command == "get_key")
            {
                if (current_iter.is_valid())
                    std::cout << "Current key: '" << current_iter.key() << "'." << std::endl;
                else
                    std::cout << "Current key: not a valid position." << std::endl;
            }
            else if (command == "get_value")
            {
                if (current_iter.is_valid())
                    std::cout << "Current value: '" << current_iter.value() << "'." << std::endl;
                else
                    std::cout << "Current value: not a valid position." << std::endl;
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
        std::cerr << "Caught unknown exception!." << std::endl;
        exit_code = EXIT_FAILURE;
    }
    return exit_code;
}
