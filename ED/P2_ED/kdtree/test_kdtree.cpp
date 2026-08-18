#include <cstdlib>
#include <ctime>
#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include <pattern.hpp>
#include "kdtree.hpp"

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
            std::cerr << "Error: could not open input filename '"
                      << argv[1] << "'." << std::endl;
            std::cerr << "Usage: " << argv[0] << " filename" << std::endl;
            return EXIT_FAILURE;
        }

        auto kdtree = std::make_shared<KDTree>();
        std::string command;
        std::cout << std::unitbuf;
        std::istringstream input_line;
        std::string line;
        std::vector<Pattern> dts;

        while (std::getline(input_file, line))
        {
            if (line == "" || line[0] == '#')
                continue;

            input_line.clear();
            input_line.str(line);
            input_line >> command;
            if (!input_line)
                continue;

            if (command == "LOAD_DATASET")
            {
                // input_file.ignore(); //skip newline.
                dts.resize(0);
                std::cout << "Loading dataset: ";
                try
                {
                    load_dataset(input_file, dts);
                    std::cout << " size = " << dts.size()
                              << " patterns with dims = " << dts[0].dim() << std::endl;
                }
                catch (std::runtime_error &e)
                {
                    std::cout << "wrong input format" << std::endl;
                    return EXIT_SUCCESS;
                }
            }
            else if (command == "CREATE_KDTREE")
            {
                std::cout << "Creating kdtree from dataset ... ";
                kdtree = std::make_shared<KDTree>(dts);
                std::cout << " ok." << std::endl;
            }
            else if (command == "FOLD_KDTREE")
            {
                kdtree->fold(std::cout);
                std::cout << std::endl;
            }
            else if (command == "UNFOLD_KDTREE")
            {
                try
                {
                    std::cout << "Unfolding kdtree ... ";
                    kdtree = std::make_shared<KDTree>(input_file);
                    std::cout << " ok." << std::endl;
                }
                catch (std::runtime_error &e)
                {
                    std::cout << "Wrong input format." << std::endl;
                }
            }
            else if (command == "FIND_L1_NN")
            {
                Pattern p;
                input_line >> p;
                std::cout << "Find NN for p=" << p << std::endl;
                auto result = kdtree->find_nn(p, distance_L1);
                std::cout << "L1 nn  : " << std::get<1>(result) << std::endl;
                std::cout << "L1 dist: " << std::get<0>(result) << std::endl;
            }
            else if (command == "FIND_L2_NN")
            {
                Pattern p;
                input_line >> p;
                std::cout << "Find NN for p=" << p << std::endl;
                auto result = kdtree->find_nn(p, distance_L2);
                std::cout << "L2 nn  : " << std::get<1>(result) << std::endl;
                std::cout << "L2 dist: " << std::get<0>(result) << std::endl;
            }
            else
            {
                std::cerr << "Error: input command unknown '" << command
                          << "'." << std::endl;
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
