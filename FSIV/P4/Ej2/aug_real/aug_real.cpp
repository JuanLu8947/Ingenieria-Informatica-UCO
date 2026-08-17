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
#include <opencv2/calib3d/calib3d.hpp>

#include "common_code.hpp"

const cv::String keys =
    "{help h usage ? |      | print this message   }"
    "{draw_model     |      | draw a 3d model else draw XYZ axis.}"
    "{is_camera      |      | The input is a camera idx.}"
    "{render_image   |      | Render an image on the board. -render_image=img.png}"
    "{render_video   |      | Render a video on the board. -render_video=video.avi}"
    "{rows          |<none>| board rows.}"
    "{cols          |<none>| board cols.}"
    "{size          |<none>| board squared side size.}"
    "{@intrinsics    |<none>| intrinsics calibration filename.}"
    "{@input         |<none>| input video stream (filename or camera idx)}";

int main(int argc, char *const *argv)
{
    int retCode = EXIT_SUCCESS;

    try
    {

        cv::CommandLineParser parser(argc, argv, keys);
        parser.about("Do augmented reality on a input stream.");
        if (parser.has("help"))
        {
            parser.printMessage();
            return EXIT_SUCCESS;
        }
        int rows = parser.get<int>("rows");
        int cols = parser.get<int>("cols");
        cv::Size board_size(cols - 1, rows - 1);
        float size = parser.get<float>("size");
        std::string intrinsics_file = parser.get<std::string>("@intrinsics");
        bool is_camera = parser.has("is_camera");
        bool draw_axis = !parser.has("draw_model");
        int camera_idx = -1;
        std::string input_file;
        if (is_camera)
            camera_idx = parser.get<int>("@input");
        else
            input_file = parser.get<std::string>("@input");
        cv::Mat projected_image;
        if (parser.has("render_image"))
        {
            projected_image = cv::imread(parser.get<std::string>("render_image"), cv::IMREAD_COLOR);
            if (projected_image.empty())
            {
                std::cerr << "Error: could not load the image to be projected." << std::endl;
                return EXIT_FAILURE;
            }
        }
        cv::VideoCapture projected_video;
        if (parser.has("render_video"))
        {
            projected_video.open(parser.get<std::string>("render_video"));
            if (!projected_video.isOpened())
            {
                std::cerr << "Error: could not load the video to be projected." << std::endl;
                return EXIT_FAILURE;
            }
        }
        if (!parser.check())
        {
            parser.printErrors();
            return EXIT_FAILURE;
        }

        cv::VideoCapture cap;
        if (is_camera)
            cap.open(camera_idx);
        else
            cap.open(input_file);
        if (!cap.isOpened())
        {
            std::cerr << "Error: could not open the input stream!" << std::endl;
            return EXIT_FAILURE;
        }

        auto fs = cv::FileStorage();
        if (!fs.open(intrinsics_file, cv::FileStorage::READ))
        {
            std::cerr << "Error: could not open [" << intrinsics_file
                      << "] to read calibration parameters." << std::endl;
            return EXIT_FAILURE;
        }
        cv::Mat M;           // camera matrix
        cv::Mat dist_coeffs; // distortion coefficients.
        cv::Mat rvec, tvec;
        cv::Size camera_size;
        float rep_error; // calibration reprojection error.
        fsiv_load_calibration_parameters(fs, camera_size, rep_error, M, dist_coeffs, rvec, tvec);

        cv::Mat input_frame;
        cv::Mat input_frame_gray;
        std::vector<cv::Point3f> obj_points =
            fsiv_generate_3d_calibration_points(board_size, size);
        const cv::TermCriteria criteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 30, 0.001);
        std::vector<cv::Point2f> img_points;
        cv::namedWindow("VIDEO", cv::WINDOW_GUI_EXPANDED);
        int wait_time = (is_camera ? 20 : 1000 / 15.0); // for a video file we use 15fps.
        int key = 0;
        cv::theRNG().state = cv::getTickCount();
        while ((key != 27) && cap.read(input_frame))
        {
            if (fsiv_fast_find_chessboard_corners(input_frame, board_size, img_points))
            {
                fsiv_compute_camera_pose(obj_points, img_points, M, dist_coeffs, rvec, tvec);
                if (projected_video.isOpened())
                    projected_video.read(projected_image);

                if (!projected_image.empty())
                    fsiv_project_image(projected_image, input_frame, board_size, img_points);

                if (draw_axis)
                    fsiv_draw_axes(input_frame, M, dist_coeffs, rvec, tvec,
                                   size, 3);
                else
                    fsiv_draw_3d_model(input_frame, M, dist_coeffs, rvec,
                                       tvec, size);
            }
            cv::imshow("VIDEO", input_frame);
            key = cv::waitKey(wait_time) & 0xff;
        }
        cv::destroyAllWindows();
    }
    catch (std::exception &e)
    {
        std::cerr << "Capturada excepcion: " << e.what() << std::endl;
        retCode = EXIT_FAILURE;
    }
    return retCode;
}
