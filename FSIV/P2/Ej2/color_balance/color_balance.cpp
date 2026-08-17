#include <iostream>
#include <exception>

#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "common_code.hpp"

const cv::String keys =
    "{help h usage ? |      | print this message   }"
    "{i interactive  |      | use interactive mode.}"
    "{p              |0     | Percentage of brightest points used. Default 0 means use the classical white patch method. Value 100 means use the gray world method. Values (0, 100) means to use this percentage of brighter pixels to compute white patch value.}"
    "{@input         |<none>| input image.}"
    "{@output        |<none>| output image.}";

/**
 * @brief Application State.
 * Use this structure to maintain the state of the application
 * that will be passed to the callbacks.
 */
struct UserData
{
    cv::Mat in;  // input image.
    cv::Mat out; // output image.
    int p;       // percentage of brighter pixels used to compute the white patch.
};

void do_the_job(UserData &user_data)
{
    if (user_data.p < 100)
        user_data.out = fsiv_white_patch_color_balance(user_data.in, user_data.p / 100.0f);
    else
        user_data.out = fsiv_gray_world_color_balance(user_data.in);
    cv::imshow("INPUT", user_data.in);
    cv::imshow("OUTPUT", user_data.out);
}

/** @brief Standard trackbar callback
 * Use this function an argument for cv::createTrackbar to control
 * the trackbar changes.
 *
 * @arg v give the trackbar position.
 * @arg user_data allow to pass user data to the callback.
 */
void on_change_p(int v, void *user_data_)
{
    UserData *user_data = static_cast<UserData *>(user_data_);
    if (v == 0)
        std::cout << "Setting p to 0% (classical white patch method)" << std::endl;
    else if (v == 100)
        std::cout << "Setting p to 100% (gray world method)" << std::endl;
    else
        std::cout << "Setting p to " << v << "%" << std::endl;
    user_data->p = v;
    do_the_job(*user_data);
}

int main(int argc, char *const *argv)
{
    int retCode = EXIT_SUCCESS;

    try
    {

        cv::CommandLineParser parser(argc, argv, keys);
        parser.about("Apply a color balance to an image.");
        if (parser.has("help"))
        {
            parser.printMessage();
            return EXIT_SUCCESS;
        }
        bool interactive_mode = parser.has("i");
        int p = parser.get<int>("p");
        if (p < 0 || p > 100)
        {
            std::cerr << "Error: p is out of range [0, 100]." << std::endl;
            return EXIT_FAILURE;
        }
        cv::String input_n = parser.get<cv::String>("@input");
        cv::String output_n = parser.get<cv::String>("@output");
        if (!parser.check())
        {
            parser.printErrors();
            return EXIT_FAILURE;
        }
        UserData user_data;
        user_data.p = p;
        user_data.in = cv::imread(input_n, cv::IMREAD_COLOR);
        if (user_data.in.empty())
        {
            std::cerr << "Error: could not open input image." << std::endl;
            return EXIT_FAILURE;
        }

        cv::namedWindow("INPUT", cv::WINDOW_GUI_EXPANDED + cv::WINDOW_NORMAL);
        cv::resizeWindow("INPUT", cv::Size(800, 600));
        cv::namedWindow("OUTPUT", cv::WINDOW_GUI_EXPANDED + cv::WINDOW_NORMAL);
        cv::resizeWindow("OUTPUT", cv::Size(800, 600));
        if (interactive_mode)
        {
            cv::createTrackbar("P", "OUTPUT", 0, 100, on_change_p,
                               &user_data);
            cv::setTrackbarPos("P", "OUTPUT", user_data.p);
            std::cout << "Use the trackbar to change p." << std::endl;
            std::cout << "p=0 means use the classical white patch method." << std::endl;
            std::cout << "p=100 means use the gray world method." << std::endl;
            std::cout << "p in (0, 100) means to use this percentage of brighter pixels to compute white patch value." << std::endl;
            std::cout << "Press <ESC> key to finish or <ENTER> key to save the output image." << std::endl;
        }
        do_the_job(user_data);
        int k = 0;
        do
        {
            k = cv::waitKey(0) & 0xff;
        } while (interactive_mode && k != 27 && k != 13);

        if (k == 13)
            cv::imwrite(output_n, user_data.out);
    }
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        retCode = EXIT_FAILURE;
    }
    return retCode;
}
