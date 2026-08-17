/**
 * @file calibrate.cpp
 * @author Francisco José Madrid Cuevas (fjmadrid@uco.es)
 * @brief Calibrate the intrinsic parameters of a camera.
 * @version 1.5
 * @date 2024-09-24
 *
 * @copyright (C) Copyright 2024- This work is openly licensed via CC-BY-NC-SA 4.0. See more details here: https://creativecommons.org/licenses/by-nc-sa/4.0/
 *
 */
#include <iostream>
#include <iomanip>
#include <exception>

#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>

#include "common_code.hpp"

const cv::String keys =
    "{help h usage ? |      | print this message.}"
    "{verbose        |      | activate verbose mode.}"
    "{w_r            |5     | Window's radius used to optimize corner points.}"
    "{zz_r           |-1    | Zero zone window's radius used to optimize corner points.}"
    "{eps            |0.0001| Stop corner points optimization if change is lower than eps.}"
    "{max_iter       |100   | Max number of iterations to optimize a corner point.}"
    "{camera         |      | The input is a camera with the specified int as the camera index.}"
    "{c_width        |640   | The camera width.}"
    "{c_height       |480   | The camera height.}"
    "{video          |      | The input is a video with the specified path as the video file pathname.}"
    "{save_frames    |      | If the input is a camera or a video, save the valid captures to files with pathnames <value>_xxx.png where <value> is the value of this option.}"
    "{size           |<none>| square size.}"
    "{rows           |<none>| number of board's rows.}"
    "{cols           |<none>| number of board's cols.}"
    "{@output        |<none>| filename to save the calculated intrinsics parameters.}"
    "{@input_1       |<none>| first image file, video file or camera index.}"
    "{@input_2       |      | second image file.}"
    "{@input_n       |      | ... n-idx image file.}";

const int ESC_KEY = 27;
const int CAPTURE_KEY = 13;
const int CONTINUE_KEY = 32;

struct Params
{
    bool verbose;
    cv::Mat input;
    cv::Size board_size;
    int w_r;
    int zz_r;
    bool was_ok;
    cv::TermCriteria tcr;
    std::vector<cv::Point2f> corner_points;
};

void do_the_work(Params &p)
{
    if (!p.input.empty())
    {
        p.was_ok = fsiv_find_chessboard_corners(p.input, p.board_size,
                                                p.corner_points, p.w_r, p.zz_r, p.tcr);
        if (p.verbose)
        {
            cv::Mat img_aux = p.input.clone();
            cv::drawChessboardCorners(img_aux, p.board_size, p.corner_points, p.was_ok);
            cv::imshow("CHESSBOARD", img_aux);
        }
    }
}

void on_change_rows(int pos, void *usr)
{
    Params *p = reinterpret_cast<Params *>(usr);
    p->board_size.height = pos;
    std::cout << "Board size: " << p->board_size << std::endl;
    do_the_work(*p);
}
void on_change_cols(int pos, void *usr)
{
    Params *p = reinterpret_cast<Params *>(usr);
    p->board_size.width = pos;
    std::cout << "Board size: " << p->board_size << std::endl;
    do_the_work(*p);
}
void on_change_w_r(int pos, void *usr)
{
    Params *p = reinterpret_cast<Params *>(usr);
    p->w_r = pos + 1;
    std::cout << "w_r: " << p->w_r << std::endl;
    do_the_work(*p);
}
void on_change_zz_r(int pos, void *usr)
{
    Params *p = reinterpret_cast<Params *>(usr);
    p->zz_r = pos - 1;
    std::cout << "zz_r: " << p->zz_r << std::endl;
    do_the_work(*p);
}

void on_change_eps(int pos, void *usr)
{
    Params *p = reinterpret_cast<Params *>(usr);
    p->tcr.epsilon = std::pow(10.0, -1.0 * pos);
    std::cout << "eps: " << p->tcr.epsilon << std::endl;
    do_the_work(*p);
}
void on_change_max_iters(int pos, void *usr)
{
    Params *p = reinterpret_cast<Params *>(usr);
    p->tcr.maxCount = pos == 0 ? 1 : pos;
    std::cout << "max_iter: " << p->tcr.maxCount << std::endl;
    do_the_work(*p);
}

int main(int argc, char *const *argv)
{
    int retCode = EXIT_SUCCESS;

    try
    {
        cv::CommandLineParser parser(argc, argv, keys);
        parser.about("Calibrate the intrinsic parameters of a camera.");
        if (parser.has("help"))
        {
            parser.printMessage();
            return EXIT_SUCCESS;
        }
        float square_size = parser.get<float>("size");
        int rows = parser.get<int>("rows");
        int cols = parser.get<int>("cols");
        bool is_camera = parser.has("camera");
        bool is_video = parser.has("video");
        bool verbose = parser.has("verbose");
        std::string output_fname = parser.get<cv::String>("@output");
        if (!parser.check())
        {
            parser.printErrors();
            return EXIT_FAILURE;
        }

        // Get the inputs.
        // find the second argument without '-' at begin.
        int input = 1;
        bool found = false;
        while (input < argc && !found)
            found = argv[input++][0] != '-';
        CV_Assert(input <= argc);
        cv::VideoCapture video;
        std::vector<std::string> input_fnames;
        std::string save_frames = parser.get<cv::String>("save_frames");
        int wait_time = 0;
        if (is_camera)
        {
            int camera_idx = parser.get<int>("camera");
            video.open(camera_idx);
            if (!video.isOpened())
            {
                std::cerr << "Error: could not open camera with index ["
                          << camera_idx << "]." << std::endl;
                return EXIT_FAILURE;
            }
            video.set(cv::CAP_PROP_FRAME_WIDTH, parser.get<int>("c_width"));
            video.set(cv::CAP_PROP_FRAME_HEIGHT, parser.get<int>("c_height"));
            wait_time = 20;
        }
        else if (is_video)
        {
            video.open(parser.get<cv::String>("video"));
            if (!video.isOpened())
            {
                std::cerr << "Error: could not open video file ["
                          << parser.get<cv::String>("video") << "]." << std::endl;
                return EXIT_FAILURE;
            }
            wait_time = 0;
        }
        else
        {
            for (; input < argc; ++input)
                input_fnames.push_back(std::string(argv[input]));
            wait_time = 0;
        }
        Params params;
        params.verbose = verbose;
        params.board_size = cv::Size(cols - 1, rows - 1);
        params.w_r = parser.get<int>("w_r");
        params.zz_r = parser.get<int>("zz_r");
        params.tcr = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS,
                                      parser.get<int>("max_iter"),
                                      parser.get<double>("eps"));
        std::vector<cv::Mat> valid_board_views;
        std::vector<cv::Point3f> _3d_board_points =
            fsiv_generate_3d_calibration_points(params.board_size, square_size);
        std::vector<std::vector<cv::Point2f>> _2d_points;
        std::vector<std::vector<cv::Point3f>> _3d_points;
        cv::Size camera_size = cv::Size(0, 0);

        if (verbose || is_camera || is_video)
        {
            std::cout << std::endl
                      << "Press the <ENTER> key to capture a valid board view." << std::endl
                      << "Press the <SPACE> key to continue without capturing the current view." << std::endl
                      << "Press the <ESC> key to finish the capturing process." << std::endl
                      << std::endl;
            cv::namedWindow("CHESSBOARD", cv::WINDOW_GUI_EXPANDED + cv::WINDOW_NORMAL);
            cv::resizeWindow("CHESSBOARD", cv::Size(800, 600));
            cv::namedWindow("PARAMS", cv::WINDOW_GUI_EXPANDED + cv::WINDOW_NORMAL);
            cv::createTrackbar("ROWS", "PARAMS", 0, 20, on_change_rows, &params);
            cv::setTrackbarPos("ROWS", "PARAMS", params.board_size.height);
            cv::createTrackbar("COLS", "PARAMS", 0, 20, on_change_cols, &params);
            cv::setTrackbarPos("COLS", "PARAMS", params.board_size.width);
            cv::createTrackbar("W_R", "PARAMS", 0, 20, on_change_w_r, &params);
            cv::setTrackbarPos("W_R", "PARAMS", params.w_r - 1);
            cv::createTrackbar("ZZ_R", "PARAMS", 0, 20, on_change_zz_r, &params);
            cv::setTrackbarPos("ZZ_R", "PARAMS", params.zz_r + 1);
            cv::createTrackbar("EPS", "PARAMS", 0, 6, on_change_eps, &params);
            cv::setTrackbarPos("EPS", "PARAMS", static_cast<int>(-1.0 * std::log10(params.tcr.epsilon)));
            cv::createTrackbar("Max Iters", "PARAMS", 0, 1000, on_change_max_iters, &params);
            cv::setTrackbarPos("Max Iters", "PARAMS", params.tcr.maxCount);
        }
        int key = 0;
        int img_idx = 0;
        do
        {
            if (is_camera || is_video)
                video >> params.input;
            else
                params.input = static_cast<size_t>(img_idx) < input_fnames.size() ? cv::imread(input_fnames[img_idx++], cv::IMREAD_COLOR) : cv::Mat();
            if (params.input.empty())
                break;
            do_the_work(params);
            if (verbose || is_camera || is_video)
                key = cv::waitKey(wait_time) & 0xFF;
            else
                key = 13;  // force enter key if not verbose
            if (key == 13) // Enter
            {
                if (params.was_ok)
                {
                    valid_board_views.push_back(params.input.clone());
                    _3d_points.push_back(_3d_board_points);
                    _2d_points.push_back(params.corner_points);
                    if (verbose || is_camera || is_video)
                    {
                        std::cout << "Taken the valid view " << std::setfill('0')
                                  << std::setw(3) << valid_board_views.size()
                                  << std::endl;
                    }
                }
            }
            else if (key == 27) // ESC
            {
                break;
            }
        } while (1);

        if (verbose | is_camera | is_video)
        {
            cv::destroyWindow("CHESSBOARD");
            cv::destroyWindow("PARAMS");
        }

        if (valid_board_views.size() >= 2)
        {
            camera_size = valid_board_views[0].size();
            cv::Mat camera_matrix;
            cv::Mat dist_coeffs;
            std::vector<cv::Mat> rvects;
            std::vector<cv::Mat> tvects;
            float error = fsiv_calibrate_camera(_2d_points, _3d_points,
                                                camera_size,
                                                camera_matrix, dist_coeffs,
                                                &rvects, &tvects);
            if (verbose)
            {
                std::cout << std::endl
                          << "Calibration error: " << error << std::endl
                          << "Camera size: " << camera_size << std::endl
                          << "Camera matrix: " << std::endl
                          << camera_matrix << std::endl
                          << "Distortion coefficients: " << std::endl
                          << dist_coeffs << std::endl;
            }

            cv::FileStorage fs;
            fs.open(output_fname, cv::FileStorage::WRITE);
            if (!fs.isOpened())
            {
                std::cerr << "Error: could not open [" << output_fname
                          << "] to write." << std::endl;
                return EXIT_FAILURE;
            }
            else
            {
                fsiv_save_calibration_parameters(fs, camera_size, error,
                                                 camera_matrix, dist_coeffs);
                fs.release();
            }

            if (save_frames != "")
            {
                std::ostringstream out;
                const int n_digits = valid_board_views.size() / 10 + 1;
                for (size_t v = 0; v < valid_board_views.size(); ++v)
                {
                    out.str("");
                    out << save_frames << "_" << std::setfill('0') << std::setw(n_digits) << v << ".png";
                    if (!cv::imwrite(out.str(), valid_board_views[v]))
                    {
                        std::cerr << "Error: could not save the view to the filename ["
                                  << out.str() << "]." << std::endl;
                    }
                }
            }

            if (verbose)
            {
                std::ostringstream out;
                const int n_digits = valid_board_views.size() / 10 + 1;
                key = 0;
                for (size_t v = 0; key != ESC_KEY && v < valid_board_views.size(); ++v)
                {
                    out.str("");
                    out << "View " << std::setfill('0') << std::setw(n_digits) << v;
                    cv::drawFrameAxes(valid_board_views[v], camera_matrix, dist_coeffs,
                                      rvects[v], tvects[v], square_size);
                    cv::namedWindow(out.str(), cv::WINDOW_GUI_EXPANDED + cv::WINDOW_NORMAL);
                    cv::resizeWindow(out.str(), cv::Size(800, 600));
                    cv::imshow(out.str(), valid_board_views[v]);
                    key = cv::waitKey(0) & 0xFF;
                    cv::destroyWindow(out.str());
                }
            }
        }
        else
        {
            std::cerr << "Error: could not find at least two valid views!."
                      << std::endl;
            return EXIT_FAILURE;
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Capturada excepcion: " << e.what() << std::endl;
        retCode = EXIT_FAILURE;
    }
    return retCode;
}
