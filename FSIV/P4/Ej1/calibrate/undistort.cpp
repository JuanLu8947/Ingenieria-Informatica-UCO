/*!
  Esto es un esqueleto de programa para usar en las prácticas
  de Visión Artificial.

  Se supone que se utilizará OpenCV.

  Para compilar, puedes ejecutar:
    g++ -Wall -o esqueleto esqueleto.cc `pkg-config opencv --cflags --libs`

*/

#include <iostream>
#include <exception>

// Includes para OpenCV, Descomentar según los módulo utilizados.
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
// #include <opencv2/calib3d/calib3d.hpp>

#include "common_code.hpp"

const cv::String keys =
    "{help h usage ? |      | print this message.}"
    "{v video        |      | the input is a video file.}"
    "{fourcc         |      | output video codec used, for example \"MJPG\". Default same as input.}"
    "{@intrinsics    |<none>| intrinsics parameters file.}"
    "{@input         |<none>| input image|video.}"
    "{@output        |<none>| output image|video.}";

int main(int argc, char *const *argv)
{
    int retCode = EXIT_SUCCESS;
    cv::CommandLineParser parser(argc, argv, keys);
    parser.about("Remove distortion from an image/video.");
    if (parser.has("help"))
    {
        parser.printMessage();
        return EXIT_SUCCESS;
    }
    auto is_video = parser.has("v");
    auto calib_fname = parser.get<std::string>("@intrinsics");
    auto input_fname = parser.get<std::string>("@input");
    auto output_fname = parser.get<std::string>("@output");
    if (!parser.check())
    {
        parser.printErrors();
        return EXIT_FAILURE;
    }

    try
    {
        float error;
        cv::Size camera_size;
        cv::Mat K, dist_coeffs, rvec, tvec;

        cv::namedWindow("INPUT", cv::WINDOW_GUI_EXPANDED + cv::WINDOW_NORMAL);
        cv::resizeWindow("INPUT", cv::Size(800, 600));
        cv::namedWindow("OUTPUT", cv::WINDOW_GUI_EXPANDED + cv::WINDOW_NORMAL);
        cv::resizeWindow("OUTPUT", cv::Size(800, 600));

        cv::FileStorage fs;
        fs.open(calib_fname, cv::FileStorage::READ);
        if (!fs.isOpened())
        {
            std::cerr << "Error: could not open [" << calib_fname << "] to read."
                      << std::endl;
            return EXIT_FAILURE;
        }
        fsiv_load_calibration_parameters(fs, camera_size, error, K,
                                         dist_coeffs, rvec, tvec);

        if (is_video)
        {
            auto input_stream = cv::VideoCapture();
            input_stream.open(input_fname);
            if (!input_stream.isOpened())
            {
                std::cerr << "Error: could not open [" << input_fname
                          << "] to read." << std::endl;
                return EXIT_FAILURE;
            }

            cv::Mat first_frame;
            input_stream >> first_frame;
            if (first_frame.empty())
            {
                std::cerr << "Error: could not capture from input stream [" << input_fname << "]." << std::endl;
                return EXIT_FAILURE;
            }
            cv::Size frame_size = first_frame.size();
            auto output_stream = cv::VideoWriter();
            int output_fourcc = input_stream.get(cv::CAP_PROP_FOURCC);
            if (parser.has("fourcc"))
            {
                std::string fourcc = parser.get<std::string>("fourcc");
                if (fourcc.size() != 4)
                {
                    std::cerr << "Error: FOURCC codes must have 4 characters."
                              << std::endl;
                    return EXIT_FAILURE;
                }
                output_fourcc = cv::VideoWriter::fourcc(fourcc[0],
                                                        fourcc[1], fourcc[2], fourcc[3]);
            }
            double output_fps = 25.0;
            output_stream.open(output_fname, output_fourcc, output_fps,
                               frame_size, true);
            if (!output_stream.isOpened())
            {
                std::cerr << "Error: could not write into [" << output_fname
                          << "]." << std::endl;
                return EXIT_FAILURE;
            }
            cv::Mat output_first_frame;
            fsiv_undistort_image(first_frame, output_first_frame, K, dist_coeffs);
            output_stream << output_first_frame;
            fsiv_undistort_video_stream(input_stream, output_stream, K,
                                        dist_coeffs, cv::INTER_LINEAR,
                                        "INPUT", "OUTPUT",
                                        output_fps);
        }
        else
        {
            cv::Mat input_img = cv::imread(input_fname, cv::IMREAD_ANYCOLOR);
            if (input_img.empty())
            {
                std::cerr << "Error: could not open [" << input_fname
                          << "] to read." << std::endl;
                return EXIT_FAILURE;
            }
            cv::Mat output_img;
            fsiv_undistort_image(input_img, output_img, K, dist_coeffs);
            cv::imshow("INPUT", input_img);
            cv::imshow("OUTPUT", output_img);
            int key = cv::waitKey(0) & 0xff;
            if (key != 27)
            {
                if (!cv::imwrite(output_fname, output_img))
                {
                    std::cerr << "Error: could not open [" << output_fname
                              << "] to write." << std::endl;
                    return EXIT_FAILURE;
                }
            }
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        retCode = EXIT_FAILURE;
    }
    return retCode;
}
