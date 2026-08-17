#include "common_code.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

cv::Mat fsiv_color_rescaling(const cv::Mat &in, const cv::Scalar &from, const cv::Scalar &to)
{
    cv::Mat out;
    // TODO
    // HINT: use cv:divide to compute the scaling factor.
    // HINT: use method cv::Mat::mul() to scale the input matrix.
    cv::Scalar f;
    cv::divide(to, from, f);
    /*
    InputArray 	src1,
    InputArray 	src2,
    OutputArray 	dst,
    double 	scale = 1,
    int 	dtype = -1 
    */
    out = in.mul(f);
    //
    CV_Assert(out.type() == in.type());
    CV_Assert(out.size() == in.size());
    return out;
}

cv::Mat fsiv_gray_world_color_balance(cv::Mat const &in)
{
    CV_Assert(in.type() == CV_8UC3);
    cv::Mat out;
    // TODO
    //  HINT: use cv::mean to compute the mean pixel value.
    cv::Scalar mean_ = cv::mean(in);
    out = fsiv_color_rescaling(in, mean_, cv::Scalar(128, 128, 128));
    //
    CV_Assert(out.type() == in.type());
    CV_Assert(out.rows == in.rows && out.cols == in.cols);
    return out;
}

cv::Mat fsiv_convert_bgr_to_gray(const cv::Mat &img, cv::Mat &out)
{
    CV_Assert(img.channels() == 3);
    // TODO
    // HINT: use cv::cvtColor()
    cv::cvtColor(img, out, cv::COLOR_BGR2GRAY);
    //
    CV_Assert(out.channels() == 1);
    return out;
}

cv::Mat fsiv_compute_image_histogram(cv::Mat const &img)
{
    CV_Assert(img.type() == CV_8UC1);
    cv::Mat hist;
    // TODO
    // Hint: use cv::calcHist().
    std::vector<int> channels = {0};
    std::vector<int> histSizes = {256};
    std::vector<float> ranges = {0, 256};
    cv::calcHist(std::vector<cv::Mat>{img}, channels, cv::Mat(), hist, histSizes, ranges);
    //
    CV_Assert(hist.type() == CV_32FC1);
    CV_Assert(hist.rows == 256 && hist.cols == 1);
    return hist;
}

int fsiv_compute_histogram_percentile(cv::Mat const &hist, float p_value)
{
    CV_Assert(hist.type() == CV_32FC1);
    CV_Assert(hist.cols == 1);
    CV_Assert(0.0 <= p_value && p_value <= 1.0);

    int p = 0;

    // TODO
    // Remember: find the smaller index 'p' such that
    //           sum(h[0], h[1], ... , h[p]) >= p_value*area(hist)
    // Hint: use cv::sum() to compute the histogram area.
    
    // Caso especial: si p_value == 1.0, devolver el último índice
    if (p_value == 1.0f) {
        return hist.rows - 1;
    }
    
    // Calcular el área total del histograma
    double total_area = cv::sum(hist)[0]; //[0] extrae el primer elemento del cv::Scalar resultado
    float umbral = p_value * total_area;
    
    // Acumular valores hasta encontrar el percentil
    float accumulated_sum = 0.0f;
    for (int i = 0; i < hist.rows; i++) {
        accumulated_sum += hist.at<float>(i);
        if (accumulated_sum >= umbral) {
            p = i;
            break;
        }
    }
    
    // Asegurar que siempre tenemos un valor válido
    if (p >= hist.rows) {
        p = hist.rows - 1;
    }
    //

    CV_Assert(0 <= p && p < hist.rows);
    return p;
}

cv::Mat fsiv_white_patch_color_balance(cv::Mat const &in, float p)
{
    CV_Assert(in.type() == CV_8UC3);
    CV_Assert(0.0f <= p && p < 1.0f);
    cv::Mat out;
    if (p == 0.0)
    {
        // TODO
        // HINT: convert to GRAY color space to get the illuminance.
        // HINT: use cv::minMaxLoc to locate the brightest pixel.
        // HINT: use fsiv_color_rescaling when the "from" scalar was computed.
        cv::Mat luma;
        fsiv_convert_bgr_to_gray(in, luma);
        cv::Point maxLoc;
        cv::minMaxLoc(luma, nullptr, nullptr, nullptr, &maxLoc);
        /*
        InputArray 	src,
        double * 	minVal,
        double * 	maxVal = 0,
        Point * 	minLoc = 0,
        Point * 	maxLoc = 0,
        InputArray 	mask = noArray() 
        */
        cv::Vec3b pixel_rgb = in.at<cv::Vec3b>(maxLoc);
        cv::Scalar max_rgb(pixel_rgb[0], pixel_rgb[1], pixel_rgb[2]);
        out = fsiv_color_rescaling(in, max_rgb, cv::Scalar(255, 255, 255));
        //
    }
    else
    {
        // TODO
        // HINT: convert to GRAY color space to get the illuminance.
        // HINT: Compute the illuminance histogram and find the 1-p percentile.
        // HINT: use operator >= to compute a mask with p% brighter pixels and use it
        //        to compute the mean value with cv::mean.
        // HINT: use fsiv_color_rescaling when the "from" scalar was computed.
        cv::Mat luma;
        fsiv_convert_bgr_to_gray(in, luma);
        cv::Mat hist = fsiv_compute_image_histogram(luma);
        int p_index = fsiv_compute_histogram_percentile(hist, 1.0 - p);
        cv::Mat mask = (luma >= p_index);
        cv::Scalar max_rgb = cv::mean(in, mask);
        out = fsiv_color_rescaling(in, max_rgb, cv::Scalar(255, 255, 255));
        //
    }

    CV_Assert(out.type() == in.type());
    CV_Assert(out.rows == in.rows && out.cols == in.cols);
    return out;
}
