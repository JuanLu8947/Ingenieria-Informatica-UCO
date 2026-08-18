#include <cstdlib>
#include <ctime>
#include <exception>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

#include "pattern.hpp"

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

            if (command == "CREATE_PATTERN")
            {
                int cl;
                std::vector<float> values;
                input_line >> cl;
                while (input_line)
                {
                    float v;
                    input_line >> v;
                    if (input_line)
                        values.push_back(v);
                }
                dts.push_back(Pattern(&values[0], values.size(), cl));
                std::cout << "Created new pattern with idx=" << dts.size() - 1
                          << " with class label: "
                          << dts.back().class_label() << std::endl;
            }
            else if (command == "UNFOLD_PATTERN")
            {
                Pattern p;
                std::cout << "Unfolding pattern idx: " << dts.size()
                          << " from text '" << input_line.str().substr(input_line.tellg()) << "' ... ";
                try
                {
                    input_line >> p;
                    dts.push_back(p);
                    std::cout << " ok" << std::endl;
                }
                catch (std::runtime_error &e)
                {
                    std::cout << "exception: " << e.what() << std::endl;
                }
            }
            else if (command == "PATTERN_CLASS_LABEL")
            {
                int idx;
                input_line >> idx;
                std::cout << "dts[" << idx << "] class label: "
                          << dts[idx].class_label() << std::endl;
            }
            else if (command == "SET_PATTERN_CLASS_LABEL")
            {
                int idx, class_label;
                input_line >> idx >> class_label;
                std::cout << "setting class label of patter dts[" << idx << "] to "
                          << class_label << std::endl;
                dts[idx].set_class_label(class_label);
            }
            else if (command == "PATTERN_VALUE")
            {
                int p_idx, v_idx;
                input_line >> p_idx >> v_idx;
                std::cout << "pattern dts[" << p_idx << "] value idx:" << v_idx << " value = "
                          << dts[p_idx].values()[v_idx] << std::endl;
            }
            else if (command == "SET_PATTERN_VALUE")
            {
                int p_idx, v_idx;
                float v;
                input_line >> p_idx >> v_idx >> v;
                std::cout << "setting pattern dts[" << p_idx << "] value idx:" << v_idx << " to  value "
                          << v << std::endl;
                dts[p_idx].values()[v_idx] = v;
            }
            else if (command == "PATTERN_DIM")
            {
                int idx;
                input_line >> idx;
                std::cout << "dts[" << idx << "] dim: "
                          << dts[idx].dim() << std::endl;
            }
            else if (command == "FOLD_PATTERN")
            {
                int idx;
                input_line >> idx;
                std::cout << "Fold dts[" << idx << "]: '" << dts[idx] << "'" << std::endl;
            }
            else if (command == "DIST_L1")
            {
                int idx1, idx2;
                input_line >> idx1 >> idx2;
                std::cout << "L1(dts[" << idx1 << "], dts[" << idx2 << "]) = "
                          << distance_L1(dts[idx1], dts[idx2]) << std::endl;
            }
            else if (command == "DIST_L2")
            {
                int idx1, idx2;
                input_line >> idx1 >> idx2;
                std::cout << "L2(dts[" << idx1 << "], dts[" << idx2 << "]) = "
                          << int(distance_L2(dts[idx1], dts[idx2]) * 100.0) / 100.0 << std::endl;
            }
            else if (command == "LOAD_DATASET")
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
            else if (command == "PRINT_PATTERN")
            {
                int idx;
                input_line >> idx;
                std::cout << "Pattern idx: " << idx
                          << " class label:" << dts[idx].class_label()
                          << " values: ";
                for (auto &v : dts[idx].values())
                    std::cout << ' ' << v << ',';
                std::cout << std::endl;
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
        std::cerr << "Catched unknown exception!." << std::endl;
        exit_code = EXIT_FAILURE;
    }
    return exit_code;
}
