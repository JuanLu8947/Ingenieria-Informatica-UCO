#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <exception>

#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "common_code.hpp"

const char *keys =
    "{help h usage ? |      | print this message.}"
    "{i interactive  |      | Activate interactive mode.}"
    "{f filter       |0     | Laplacian filter to be used to build the sharpening filter: 0->LAP_4, 1->LAP_8, 2->DOG}"
    "{r1             |1     | r1 for DoG filter.}"
    "{r2             |2     | r2 for DoG filter. (0<r1<r2)}"
    "{c circular     |      | use circular convolution.}"
    "{@input         |<none>| input image.}"
    "{@output        |<none>| output image.}";

struct UserData
{
    cv::Mat input;
    std::vector<cv::Mat> input_channels;
    std::vector<cv::Mat> output_channels;
    cv::Mat output;
    int filter_type;
    int r1;
    int r2;
    int only_luma;
    int circular;
    bool interactive;
    float contrast;
};

// img_f: CV_32F o CV_64F en [-1, 1]
cv::Mat to_diverging_heatmap_neg_blue_pos_red(const cv::Mat &img_f)
{
    CV_Assert(img_f.type() == CV_32F || img_f.type() == CV_64F);
    cv::Mat f32;
    img_f.convertTo(f32, CV_32F);

    // Magnitud en [0,1]
    cv::Mat mag = cv::abs(f32);
    cv::min(mag, 1.0f, mag);

    // Hue (H): 0=rojo (positivos), 120=azul (negativos) en escala [0..179]
    cv::Mat H(f32.size(), CV_8U), S(f32.size(), CV_8U, cv::Scalar(255)), V(f32.size(), CV_8U);
    cv::Mat posMask = (f32 > 0), negMask = (f32 < 0);

    H.setTo(0);            // rojo por defecto
    H.setTo(120, negMask); // azul para negativos

    // Brillo según magnitud
    cv::Mat Vf;
    mag.convertTo(Vf, CV_32F, 255.0);
    Vf.convertTo(V, CV_8U);

    // Mezclar HSV y convertir a BGR
    std::vector<cv::Mat> hsv = {H, S, V};
    cv::Mat hsvImg, bgr;
    cv::merge(hsv, hsvImg);
    cv::cvtColor(hsvImg, bgr, cv::COLOR_HSV2BGR);
    return bgr;
}

void do_the_work(UserData *user_data)
{
    cv::Mat input = user_data->input;
    if (user_data->input_channels.size() == 3)
        input = user_data->input_channels[2];

    user_data->output = fsiv_image_sharpening(input,
                                              user_data->filter_type,
                                              user_data->r1,
                                              user_data->r2,
                                              user_data->circular);

    if (user_data->input_channels.size() == 3)
    {
        // Revert to BGR.
        cv::Mat hsv;
        user_data->output_channels[2] = user_data->output;
        cv::merge(user_data->output_channels, hsv);
        cv::cvtColor(hsv, user_data->output, cv::COLOR_HSV2BGR);
    }
    if (user_data->interactive)
    {
        cv::imshow("OUTPUT", user_data->output);
        cv::Mat luma;
        if (user_data->input_channels.size() == 3)
            cv::cvtColor(user_data->input, luma, cv::COLOR_BGR2GRAY);
        else
            luma = user_data->input.clone();
        luma.convertTo(luma, CV_32F, 1.0 / 255.0);
        cv::Mat filter;
        switch (user_data->filter_type)
        {
        case 0:
            filter = fsiv_create_lap4_filter();
            break;
        case 1:
            filter = fsiv_create_lap8_filter();
            break;
        case 2:
            filter = fsiv_create_dog_filter(user_data->r1, user_data->r2);
            break;
        default:
            CV_Assert(false);
        }
        if (user_data->circular)
            luma = fsiv_circular_expansion(luma, filter.rows / 2);
        else
            luma = fsiv_fill_expansion(luma, filter.rows / 2);
        cv::Mat lap;
        cv::filter2D(luma, lap, CV_32F, filter,
                     cv::Point(-1, -1),
                     0,
                     cv::BORDER_ISOLATED);
        lap = lap(cv::Rect(filter.cols / 2, filter.cols / 2, user_data->output.cols, user_data->output.rows));
        double min_v, max_v;
        cv::minMaxLoc(lap, &min_v, &max_v);
        cv::Mat lap_neg;
        cv::divide(lap, std::abs(min_v) + 1e-6, lap_neg);
        cv::divide(lap, max_v + 1e-6, lap);
        lap_neg.copyTo(lap, lap < 0);
        cv::Mat heatmap = to_diverging_heatmap_neg_blue_pos_red(lap).mul(user_data->contrast);
        cv::imshow("LAPLACIAN", heatmap);
    }
}

void filter_trackbar(int pos, void *userdata)
{
    UserData *d = static_cast<UserData *>(userdata);
    pos = std::max(0, std::min(pos, 2));
    d->filter_type = pos;
    std::cout << "Set filter type to " << d->filter_type << std::endl;
    do_the_work(d);
}

void r1_trackbar(int pos, void *userdata)
{
    UserData *d = static_cast<UserData *>(userdata);
    if (pos > 0 && pos < d->r2)
    {
        d->r1 = pos;
        std::cout << "Set r1=" << d->r1 << " r2=" << d->r2 << std::endl;
        do_the_work(d);
    }
    else
        cv::setTrackbarPos("R1", "PARAMETERS", d->r1);
}

void r2_trackbar(int pos, void *userdata)
{
    UserData *d = static_cast<UserData *>(userdata);
    if (pos > d->r1)
    {
        d->r2 = pos;
        std::cout << "Set r1=" << d->r1 << " r2=" << d->r2 << std::endl;
        do_the_work(d);
    }
    else
        cv::setTrackbarPos("R2", "PARAMETERS", d->r2);
}

void circular_trackbar(int pos, void *userdata)
{
    UserData *d = static_cast<UserData *>(userdata);
    d->circular = (pos == 1);
    std::cout << "Set circular convolution mode to state " << d->circular
              << std::endl;
    do_the_work(d);
}

void contrast_trackbar(int pos, void *userdata)
{
    UserData *d = static_cast<UserData *>(userdata);
    d->contrast = 1.0f + pos / 10.0f; // [1.0, 10.0]
    std::cout << "Set contrast to " << d->contrast << std::endl;
    do_the_work(d);
}

int main(int argc, char *const *argv)
{
    int retCode = EXIT_SUCCESS;

    try
    {

        cv::CommandLineParser parser(argc, argv, keys);
        parser.about("Enhance an image using a sharpening filter. (ver 1.11.0)");
        if (parser.has("help"))
        {
            parser.printMessage();
            return 0;
        }
        UserData data;

        data.filter_type = parser.get<float>("f");
        data.r1 = parser.get<int>("r1");
        data.r2 = parser.get<int>("r2");
        data.interactive = parser.has("i");
        data.circular = parser.has("circular");

        cv::String input_name = parser.get<cv::String>(0);
        cv::String output_name = parser.get<cv::String>(1);

        if (!parser.check())
        {
            parser.printErrors();
            return 0;
        }

        data.input = cv::imread(input_name, cv::IMREAD_ANYCOLOR);

        if (data.input.empty())
        {
            std::cerr << "Error: could not open the input image '" << input_name << "'." << std::endl;
            return EXIT_FAILURE;
        }

        data.input.convertTo(data.input, CV_32F, 1.0 / 255.0);

        if (data.input.channels() == 3)
        {
            cv::Mat hsv_img;
            cv::cvtColor(data.input, hsv_img, cv::COLOR_BGR2HSV);
            cv::split(hsv_img, data.input_channels);
            data.output_channels = data.input_channels;
        }

        if (data.filter_type < 0 || data.filter_type > 2)
        {
            std::cerr << "Error: filter type parameter has values in {0, 1, 2}." << std::endl;
            return EXIT_FAILURE;
        }

        if (data.r1 < 0 || data.r1 >= data.r2 || data.r2 >= std::min(data.input.rows, data.input.cols) / 2)
        {
            std::cerr << "Error: Condition 0 <= r1 < r2 < min(rows, cols) / 2 is not meet." << std::endl;
            return EXIT_FAILURE;
        }
        int key = 0;

        if (data.interactive)
        {
            data.contrast = 1.0f;
            cv::namedWindow("INPUT", cv::WINDOW_GUI_EXPANDED + cv::WINDOW_NORMAL);
            cv::resizeWindow("INPUT", cv::Size(800, 600));
            cv::namedWindow("OUTPUT", cv::WINDOW_GUI_EXPANDED + cv::WINDOW_NORMAL);
            cv::resizeWindow("OUTPUT", cv::Size(800, 600));
            cv::namedWindow("LAPLACIAN", cv::WINDOW_GUI_EXPANDED + cv::WINDOW_NORMAL);
            cv::resizeWindow("LAPLACIAN", cv::Size(800, 600));
            cv::namedWindow("PARAMETERS", cv::WINDOW_GUI_EXPANDED + cv::WINDOW_NORMAL);

            cv::createTrackbar("FILTER", "PARAMETERS", 0, 2, filter_trackbar, &data);
            cv::setTrackbarPos("FILTER", "PARAMETERS", data.filter_type);
            cv::createTrackbar("R1", "PARAMETERS", 0, std::min(data.input.rows, data.input.cols) / 2, r1_trackbar, &data);
            cv::setTrackbarPos("R1", "PARAMETERS", data.r1);
            cv::createTrackbar("R2", "PARAMETERS", 0, std::min(data.input.rows, data.input.cols) / 2, r2_trackbar, &data);
            cv::setTrackbarPos("R2", "PARAMETERS", data.r2);
            cv::createTrackbar("CIRC", "PARAMETERS", 0, 1, circular_trackbar, &data);
            cv::setTrackbarPos("CIRC", "PARAMETERS", data.circular ? 1 : 0);
            cv::createTrackbar("CONTRAST", "PARAMETERS", 0, 90, contrast_trackbar, &data);
            cv::setTrackbarPos("CONTRAST", "PARAMETERS", 0);

            cv::imshow("INPUT", data.input);
            std::cout << "Interative mode. Press <ENTER> to finish with saving or <ESC> to abort." << std::endl;
            do_the_work(&data);

            do
            {
                key = cv::waitKey(0) & 0xff;
            } while (key != 27 && key != 13);
        }
        else
            do_the_work(&data);

        if (key != 27)
        {
            data.output.convertTo(data.output, CV_32F, 256.0);
            if (!cv::imwrite(output_name, data.output))
            {
                std::cerr << "Error: could not save the result in file '" << output_name << "'." << std::endl;
                return EXIT_FAILURE;
            }
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        retCode = EXIT_FAILURE;
    }
    return retCode;
}
