/**
 * @file blur_background.cpp
 * @author Francisco José Madrid Cuevas (fjmadrid@uco.es)
 * @brief Blur the background of the input video stream using optical flow magnitude as clue.
 * @date 2024-10-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <iostream>
#include <exception>

#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video.hpp>

#include "common_code.hpp"

const cv::String keys =
    "{help h usage ? |      | print this message   }"
    "{is_camera      |      | The input video stream is a camera.}"
    "{c_width        |640   | The frame width if the input is from a camera.}"
    "{c_height       |480   | The frame height if the input is from a camera.}"
    "{ste_r          |3     | Structure element radius for morph. Default 0 means not use. Range [0,25].}"
    "{ste_type       |2     | Type of structure element: 0:rect, 1:cross, 2:ellipse.}"
    "{blur_type      |0     | Blur type: 0->Box, 1->Gaussian.}"
    "{blur_r         |5     | Blur radius.}"
    "{th             |2.0   | Threshold the optical flow magnitude to get the mask. Range [0,10].}"
    "{alpha          |0.2   | Background mask model has an old model alpha memory weight. Range [0,1]. Default 0 means don't have memory.}"
    "{@input         |<none>| input stream (filename or camera idx)}";

struct GuiPArams
{
    float th;
    int ste_r;
    int ste_type;
    float alpha;
    int blur_r;
    int blur_type;
};

void onChange_th(int count, void *params)
{
    auto params_ = reinterpret_cast<GuiPArams *>(params);
    params_->th = count / 10.0;
    std::cout << "Setting th to " << params_->th << std::endl;
}

void onChange_alpha(int count, void *params)
{
    reinterpret_cast<GuiPArams *>(params)->alpha = count / 100.0;
    std::cout << "Setting alpha to " << count / 100.0 << std::endl;
}

void onChange_ste_r(int count, void *params)
{
    reinterpret_cast<GuiPArams *>(params)->ste_r = count;
    std::cout << "Setting ste_r to " << count << std::endl;
}

void onChange_ste_type(int count, void *params)
{
    reinterpret_cast<GuiPArams *>(params)->ste_type = count;
    std::cout << "Setting ste_type to " << count << std::endl;
}

void onChange_blur_r(int count, void *params)
{
    reinterpret_cast<GuiPArams *>(params)->blur_r = count + 1;
    std::cout << "Setting blur radius  to " << count + 1 << std::endl;
}

void onChange_gaussian_blur(int count, void *params)
{
    reinterpret_cast<GuiPArams *>(params)->blur_type = count;
    std::cout << "Setting blur type to " << (count ? "Gaussian" : "Box") << std::endl;
}

int main(int argc, char *const *argv)
{
    int retCode = EXIT_SUCCESS;

    try
    {

        cv::CommandLineParser parser(argc, argv, keys);
        parser.about("Blur the background of the input video stream using optical flow magnitude as clue.");
        if (parser.has("help"))
        {
            parser.printMessage();
            return EXIT_SUCCESS;
        }
        bool is_camera = parser.has("is_camera");
        int blur_r = parser.get<int>("blur_r");

        cv::Mat ste;
        int ste_r = parser.get<int>("ste_r");
        int ste_type = parser.get<int>("ste_type");

        int blur_type = std::max(0, std::min(1, parser.get<int>("blur_type")));
        double th = parser.get<double>("th");
        double alpha = parser.get<double>("alpha");

        int camera_idx = -1;
        std::string input_file = parser.get<std::string>("@input");

        if (!parser.check())
        {
            parser.printErrors();
            return EXIT_FAILURE;
        }

        if (is_camera)
            camera_idx = std::stoi(input_file);

        cv::VideoCapture cap;

        if (is_camera)
        {
            cap.open(camera_idx);
            std::cerr << "set width " << parser.get<int>("c_width") << " height " << parser.get<int>("c_height") << std::endl;
            cap.set(cv::CAP_PROP_FRAME_WIDTH, parser.get<int>("c_width"));
            cap.set(cv::CAP_PROP_FRAME_HEIGHT, parser.get<int>("c_height"));
        }
        else
            cap.open(input_file);

        if (!cap.isOpened())
        {
            std::cerr << "Error: could not open the input stream!" << std::endl;
            return EXIT_FAILURE;
        }

        // TODO

        GuiPArams gui_params;

        gui_params.th = th;
        gui_params.alpha = alpha;
        gui_params.ste_r = ste_r;
        gui_params.ste_type = ste_type;
        gui_params.blur_r = blur_r;
        gui_params.blur_type = blur_type;

        cv::Mat prev, prev_gray;
        cap >> prev;
        if (prev.empty())
        {
            std::cerr << "Error: could not read frames from the input stream!" << std::endl;
            return EXIT_FAILURE;
        }

        cv::cvtColor(prev, prev_gray, cv::COLOR_BGR2GRAY);

        cv::Mat curr, curr_gray, flow;
        cv::Mat mask;
        cv::Mat blur_curr;
        cv::Mat flow_mag;
        int key = 0;

        cv::namedWindow("FLOW MAGNITUDE", cv::WINDOW_GUI_EXPANDED + cv::WINDOW_AUTOSIZE);
        cv::resizeWindow("FLOW_MAGNITUDE", 640, 480);
        cv::namedWindow("MASK", cv::WINDOW_GUI_EXPANDED + cv::WINDOW_AUTOSIZE);
        cv::resizeWindow("MASK", 640, 480);
        cv::namedWindow("ORIGINAL", cv::WINDOW_GUI_EXPANDED + cv::WINDOW_AUTOSIZE);
        cv::resizeWindow("ORIGINAL", 640, 480);
        cv::namedWindow("BLURRING", cv::WINDOW_GUI_EXPANDED + cv::WINDOW_AUTOSIZE);
        cv::resizeWindow("BLURRING", 640, 480);
        cv::namedWindow("PARAMETERS", cv::WINDOW_GUI_EXPANDED + cv::WINDOW_NORMAL);

        cv::createTrackbar("TH", "PARAMETERS", nullptr, 100, onChange_th, &gui_params);
        cv::setTrackbarPos("TH", "PARAMETERS", std::min(100, int(gui_params.th * 10.0)));
        cv::createTrackbar("ALPHA", "PARAMETERS", nullptr, 100, onChange_alpha, &gui_params);
        cv::setTrackbarPos("ALPHA", "PARAMETERS", gui_params.alpha * 100);
        cv::createTrackbar("BLUR_R", "PARAMETERS", nullptr, 10, onChange_blur_r, &gui_params);
        cv::setTrackbarPos("BLUR_R", "PARAMETERS", std::min(10, gui_params.blur_r - 1));
        cv::createTrackbar("BLUR_TYPE", "PARAMETERS", nullptr, 1, onChange_gaussian_blur, &gui_params);
        cv::setTrackbarPos("BLUR_TYPE", "PARAMETERS", gui_params.blur_type);
        cv::createTrackbar("STE_R", "PARAMETERS", nullptr, 25, onChange_ste_r, &gui_params);
        cv::setTrackbarPos("STE_R", "PARAMETERS", std::min(25, gui_params.ste_r));
        cv::createTrackbar("STE_T", "PARAMETERS", nullptr, 2, onChange_ste_type, &gui_params);
        cv::setTrackbarPos("STE_T", "PARAMETERS", std::min(2, gui_params.ste_type));
        while ((key != 27))
        {
            if (!cap.read(curr))
            {
                if (!is_camera)
                {
                    cap.set(cv::CAP_PROP_POS_FRAMES, 0); // reset to start again the video.
                    continue;
                }
                else
                    break;
            }
            cv::cvtColor(curr, curr_gray, cv::COLOR_BGR2GRAY);
            fsiv_compute_of_foreground_mask(prev_gray, curr_gray, flow,
                                            mask, gui_params.th, gui_params.ste_r, gui_params.ste_type,
                                            gui_params.alpha, &flow_mag);
            fsiv_blur_background(curr, mask, blur_curr, gui_params.blur_r,
                                 gui_params.blur_type);
            cv::normalize(flow_mag, flow_mag, 0, 1, cv::NORM_MINMAX);
            cv::imshow("FLOW MAGNITUDE", flow_mag);
            cv::imshow("MASK", mask);
            cv::imshow("ORIGINAL", curr);
            cv::imshow("BLURRING", blur_curr);

            curr.copyTo(prev);
            key = cv::waitKey(20) & 0xff;
        }
        cv::destroyAllWindows();
    }
    catch (std::exception &e)
    {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        retCode = EXIT_FAILURE;
    }
    return retCode;
}
