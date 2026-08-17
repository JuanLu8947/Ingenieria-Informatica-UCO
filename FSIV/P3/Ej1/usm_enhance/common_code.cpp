/**
 * @file common_code.cpp
 * @author Francisco José Madrid Cuevas (fjmadrid@uco.es)
 * @brief Utility module to do an Unsharp Mask image enhance.
 * @version 0.1
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024-
 *
 */
#include "common_code.hpp"
#include <opencv2/imgproc.hpp>

cv::Mat
fsiv_create_box_filter(const int r)
{
    CV_Assert(r > 0);
    cv::Mat ret_v;
    // TODO
    // Hint: use the constructor of cv::Mat to set the proper initial value.
    ret_v = cv::Mat::ones(2 * r + 1, 2 * r + 1, CV_32FC1);
    cv::normalize(ret_v, ret_v, 1.0, 0.0, cv::NORM_L1);
    /*
    InputArray 	src,
    InputOutputArray 	dst,
    double alpha = 1,
    double beta = 0,
    int norm_type
    */
    //
    CV_Assert(ret_v.type() == CV_32FC1);
    CV_Assert(ret_v.rows == (2 * r + 1) && ret_v.rows == ret_v.cols);
    CV_Assert(std::abs(1.0 - cv::sum(ret_v)[0]) < 1.0e-6);
    return ret_v;
}

cv::Mat
fsiv_create_gaussian_filter(const int r)
{
    CV_Assert(r > 0);
    cv::Mat ret_v;
    // TODO
    // Hint: use cv::getGaussianKernel()
    ret_v = cv::getGaussianKernel(2 * r + 1, -1, CV_32FC1); //-1 hace que el program calcula la sigma
    /*
    int 	ksize,
    double 	sigma,
    int 	ktype
    */
    ret_v = ret_v * ret_v.t(); //.t ver. transpuesta
    cv::normalize(ret_v, ret_v, 1.0, 0.0, cv::NORM_L1);
    //
    CV_Assert(ret_v.type() == CV_32FC1);
    CV_Assert(ret_v.rows == (2 * r + 1) && ret_v.rows == ret_v.cols);
    CV_Assert(std::abs(1.0 - cv::sum(ret_v)[0]) < 1.0e-6);
    return ret_v;
}

cv::Mat
fsiv_fill_expansion(cv::Mat const &in, const int r)
{
    CV_Assert(!in.empty());
    CV_Assert(r > 0);
    cv::Mat ret_v;
    //! TODO:
    // Hint: use cv::copyMakeBorder() using the constant value 0 to fill the
    //       expanded area.
    cv::copyMakeBorder(in, ret_v, r, r, r, r, cv::BORDER_CONSTANT, cv::Scalar::all(0));
    /*
    InputArray src,
    OutputArray dst,
    int top,
    int bottom,
    int left,
    int right,
    int borderType,
    const Scalar & value = Scalar()

    BORDER_CONSTANT 	
    iiiiii|abcdefgh|iiiiiii with some specified i

    BORDER_REPLICATE 	
    aaaaaa|abcdefgh|hhhhhhh

    BORDER_REFLECT 	
    fedcba|abcdefgh|hgfedcb

    BORDER_WRAP 	
    cdefgh|abcdefgh|abcdefg

    BORDER_REFLECT_101 	
    gfedcb|abcdefgh|gfedcba

    BORDER_TRANSPARENT 	
    uvwxyz|abcdefgh|ijklmn

    BORDER_REFLECT101 	
    same as BORDER_REFLECT_101

    BORDER_DEFAULT 	
    same as BORDER_REFLECT_101

    BORDER_ISOLATED 	
    do not look outside of ROI
    */
    //
    CV_Assert(ret_v.type() == in.type());
    CV_Assert(ret_v.rows == in.rows + 2 * r);
    CV_Assert(ret_v.cols == in.cols + 2 * r);
    return ret_v;
}

cv::Mat
fsiv_circular_expansion(cv::Mat const &in, const int r)
{
    CV_Assert(!in.empty());
    CV_Assert(r > 0);
    cv::Mat ret_v;
    //! TODO
    //  Hint: use cv::copyMakeBorder() filling with a wrapper image.
    cv::copyMakeBorder(in, ret_v, r, r, r, r, cv::BORDER_WRAP, cv::Scalar::all(0));
    //
    CV_Assert(ret_v.type() == in.type());
    CV_Assert(ret_v.rows == in.rows + 2 * r);
    CV_Assert(ret_v.cols == in.cols + 2 * r);
    CV_Assert(!(in.type() == CV_8UC1) || ret_v.at<uchar>(0, 0) == in.at<uchar>(in.rows - r, in.cols - r));
    CV_Assert(!(in.type() == CV_8UC1) || ret_v.at<uchar>(0, ret_v.cols / 2) == in.at<uchar>(in.rows - r, in.cols / 2));
    CV_Assert(!(in.type() == CV_8UC1) || ret_v.at<uchar>(0, ret_v.cols - 1) == in.at<uchar>(in.rows - r, r - 1));
    CV_Assert(!(in.type() == CV_8UC1) || ret_v.at<uchar>(ret_v.rows / 2, 0) == in.at<uchar>(in.rows / 2, in.cols - r));
    CV_Assert(!(in.type() == CV_8UC1) || ret_v.at<uchar>(ret_v.rows / 2, ret_v.cols / 2) == in.at<uchar>(in.rows / 2, in.cols / 2));
    CV_Assert(!(in.type() == CV_8UC1) || ret_v.at<uchar>(ret_v.rows - 1, 0) == in.at<uchar>(r - 1, in.cols - r));
    CV_Assert(!(in.type() == CV_8UC1) || ret_v.at<uchar>(ret_v.rows - 1, ret_v.cols / 2) == in.at<uchar>(r - 1, in.cols / 2));
    CV_Assert(!(in.type() == CV_8UC1) || ret_v.at<uchar>(ret_v.rows - 1, ret_v.cols - 1) == in.at<uchar>(r - 1, r - 1));
    return ret_v;
}

cv::Mat
fsiv_filter2D(cv::Mat const &in, cv::Mat const &filter)
{
    CV_Assert(!in.empty() && !filter.empty());
    CV_Assert(in.type() == CV_32FC1 && filter.type() == CV_32FC1);
    cv::Mat ret_v;

    // TODO
    // Remember: Using cv::filter2D/cv::sepFilter2D is not allowed here because
    //           we want you to code the convolution operation for ease of
    //           understanding. In real applications, you should use one of
    //           those functions.
    ret_v = cv::Mat::zeros(in.rows - filter.rows + 1, in.cols - filter.cols + 1, CV_32FC1); //in.depth()
    for(int row = 0; row <= (in.rows - filter.rows); row++){ //+1
        for(int col = 0; col <= (in.cols - filter.cols); col++){
            cv::Mat window = in(cv::Rect(col, row, filter.cols, filter.rows));
            ret_v.at<float>(row, col) = cv::sum(window.mul(filter))[0];
        }
    }
    //
    CV_Assert(ret_v.type() == CV_32FC1);
    CV_Assert(ret_v.rows == in.rows - 2 * (filter.rows / 2));
    CV_Assert(ret_v.cols == in.cols - 2 * (filter.cols / 2));
    return ret_v;
}

cv::Mat
fsiv_soft_combine_images(const cv::Mat src1, const cv::Mat src2,
                         double a, double b)
{
    CV_Assert(src1.type() == src2.type());
    CV_Assert(src1.rows == src2.rows);
    CV_Assert(src1.cols == src2.cols);
    cv::Mat ret_v;

    // TODO
    // Hint: use cv::addWeighted()
    cv::addWeighted(src1, a, src2, b, 0.0, ret_v);
    /*dst(I)=saturate(src1(I)∗alpha+src2(I)∗beta+gamma)
    InputArray src1,
    double alpha,
    InputArray src2,
    double beta,
    double gamma,
    OutputArray dst,
    */
    //
    CV_Assert(ret_v.type() == src2.type());
    CV_Assert(ret_v.rows == src2.rows);
    CV_Assert(ret_v.cols == src2.cols);
    return ret_v;
}

cv::Mat
fsiv_usm_enhance(cv::Mat const &in, double g, int r,
                 int filter_type, bool circular, cv::Mat *unsharp_mask)
{
    CV_Assert(!in.empty());
    CV_Assert(in.type() == CV_32FC1);
    CV_Assert(r > 0);
    CV_Assert(filter_type >= 0 && filter_type <= 1);
    CV_Assert(g >= 0.0);
    cv::Mat ret_v;
    // TODO
    // Remember: use your own functions fsiv_xxxx
    // Remember: when unsharp_mask pointer is nullptr, means don't save the
    //           unsharp mask on int.
    //1º ver. baja frecuencia
    cv::Mat filter;
    if(filter_type == 0)
        filter = fsiv_create_box_filter(r);
    else
        filter = fsiv_create_gaussian_filter(r);
    
    cv::Mat img_expanded;
    if(!circular)
        img_expanded = fsiv_fill_expansion(in, r);
    else
        img_expanded = fsiv_circular_expansion(in, r);
    
    cv::Mat low_freq = fsiv_filter2D(img_expanded, filter);
    //1.2 convolucion, img simetrica => no hace falta invert

    if(unsharp_mask != nullptr)
        *unsharp_mask = low_freq;

    //2º aplicar combinacion
    ret_v = fsiv_soft_combine_images(in, low_freq, 1.0 + g, -g);
   
    //
    CV_Assert(ret_v.rows == in.rows);
    CV_Assert(ret_v.cols == in.cols);
    CV_Assert(ret_v.type() == CV_32FC1);
    return ret_v;
}
