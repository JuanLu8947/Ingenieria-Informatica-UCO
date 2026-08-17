#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video.hpp>

#include "common_code.hpp"

void fsiv_compute_dense_optical_flow(cv::Mat const &prev,
                                     cv::Mat const &next,
                                     cv::Mat &flow)
{
    CV_Assert(next.type() == CV_8UC1);
    CV_Assert(prev.type() == CV_8UC1);
    CV_Assert(flow.empty() || flow.type() == CV_32FC2);

    static cv::Ptr<cv::FarnebackOpticalFlow> alg;

    // TODO
    // Hint: if alg is nullptr, first you must create a new algorithm instance
    //    using cv::FarnebackOpticalFlow::create().
    // Remember: if flow is not empty, you must use it as initial estimate
    //    setting the corresponding flag in the algorithm. If it is empty, unset
    //    this flag.
     // Create algorithm instance if it doesn't exist
    if (alg.empty()) {
        alg = cv::FarnebackOpticalFlow::create();
    }
    
    // Set flag for using initial flow estimate
    if (!flow.empty()) {
        alg->setFlags(alg->getFlags() | cv::OPTFLOW_USE_INITIAL_FLOW);
    } else {
        alg->setFlags(alg->getFlags() & ~cv::OPTFLOW_USE_INITIAL_FLOW);
    }
    
    // Calculate optical flow
    alg->calc(prev, next, flow);
    //
    CV_Assert(flow.type() == CV_32FC2);
}

void fsiv_compute_optical_flow_magnitude(cv::Mat &flow, cv::Mat &mag)
{
    CV_Assert(flow.type() == CV_32FC2);

    // TODO
    // Hint: use cv::magnitude.
    cv::Mat flow_xy[2];
    cv::split(flow, flow_xy);
    /*[1/2]
    const Mat & 	src,
    Mat * 	mvbegin
    */
    cv::magnitude(flow_xy[0], flow_xy[1], mag);
    /*
    InputArray 	x,
    InputArray 	y,
    OutputArray 	magnitude 
    */
    //
    CV_Assert(mag.type() == CV_32FC1);
}

cv::Mat
fsiv_create_structuring_element(int ste_r, int type)
{
    cv::Mat ste;
    // TODO
    // Hint: use cv::getStructuringElement.
    int shape;
    switch (type){
        case 0:
            shape = cv::MORPH_RECT;
            break;
        case 1:
            shape = cv::MORPH_CROSS;
            break;
        case 2:
            shape = cv::MORPH_ELLIPSE;
            break;
        default:
            CV_Error(cv::Error::StsBadArg, "Invalid structuring element type");
    }
    ste = cv::getStructuringElement(shape, cv::Size(2 * ste_r + 1, 2 * ste_r + 1),
                                   cv::Point(ste_r, ste_r));
    /*
    int 	shape,
    Size 	ksize,
    Point 	anchor
    */
    //
    return ste;
}

void fsiv_compute_of_foreground_mask(cv::Mat const &prev, cv::Mat const &curr,
                                     cv::Mat &flow,
                                     cv::Mat &mask,
                                     const double t,
                                     const int ste_r,
                                     const int ste_type,
                                     const float alpha,
                                     cv::Mat *flow_mag_out)
{
    CV_Assert(!prev.empty() && prev.size() == curr.size());
    CV_Assert(prev.type() == CV_8UC1 && prev.type() == curr.type());
    CV_Assert(mask.empty() || mask.size() == prev.size());
    CV_Assert(alpha >= 0.0 && alpha <= 1.0);
    CV_Assert(ste_type >= 0 && ste_type <= 2);
    CV_Assert(ste_r >= 0);

    // TODO
    // The steps are:
    // 1. Compute the optical flow.
    fsiv_compute_dense_optical_flow(prev, curr, flow);
    // 2. Compute the magnitude of the optical flow.
    cv::Mat mag;
    fsiv_compute_optical_flow_magnitude(flow, mag);
    //    Remember to store it in flow_mag_out if it is not nullptr.
    if (flow_mag_out != nullptr) {
        *flow_mag_out = mag;
    }
    // 3. Threshold the magnitude (>= th) to get the current mask.
    cv::Mat curr_mask;
    cv::threshold(mag, curr_mask, t, 255, cv::THRESH_BINARY);
    /*
    InputArray 	src,
    OutputArray 	dst,
    double 	thresh,
    double 	maxval,
    int 	type
    */
    curr_mask.convertTo(curr_mask, CV_8UC1);
    // 4. If ste_r>0, dilate the current mask. Hint: use cv::dilate()
    if (ste_r > 0) {
        cv::Mat ste = fsiv_create_structuring_element(ste_r, ste_type);
        cv::dilate(curr_mask, curr_mask, ste);
        /*
        InputArray src,
        OutputArray dst,
        InputArray kernel,
        Point anchor = Point(-1,-1),
        int iterations = 1,
        int borderType = BORDER_CONSTANT,
        const Scalar & borderValue = morphologyDefaultBorderValue()
        */
    }
    // 5. If alpha>0.0 (and input mask is not empty), update mask using a
    //    running average (new_mask = alpha*old_mask + (1-alpha)*current_mask).
    //    When alpha=0.0, new_mask = current_mask. Hint: use cv::addWeighted() for this.
    if (alpha > 0.0 && !mask.empty()) {
        cv::addWeighted(mask, alpha, curr_mask, 1.0 - alpha, 0.0, mask);
        /*
        InputArray 	src1,
        double 	alpha,
        InputArray 	src2,
        double 	beta,
        double 	gamma,
        OutputArray 	dst,
        int 	dtype
        */
    } 
    else {
        mask = curr_mask;
    }
        //
    CV_Assert(mask.size() == prev.size());
    CV_Assert(mask.type() == CV_8UC1);
}

void fsiv_blur_background(cv::Mat const &input,
                          cv::Mat const &fg_mask,
                          cv::Mat &output,
                          const int blur_r,
                          const int blur_type)
{
    CV_Assert(input.size() == fg_mask.size());
    CV_Assert(fg_mask.type() == CV_8UC1);

    // TODO
    // Hint: use cv::blur or cv::GaussianBlur to blur an image.
    // Hint: use cv::Mat::copyTo with mask to fuse foreground and background.
    cv::Mat blurred;
    int ksize = 2 * blur_r + 1;
    switch (blur_type) {
        case 0: // Normal blur
            cv::blur(input, blurred, cv::Size(ksize, ksize));
            /*
            InputArray src,
            OutputArray dst,
            Size ksize,
            Point anchor = Point(-1,-1),
            int borderType = BORDER_DEFAULT
            */
            break;
        case 1: // Gaussian blur
            cv::GaussianBlur(input, blurred, cv::Size(ksize, ksize), 0);
            /*
            InputArray 	src,
            OutputArray 	dst,
            Size 	ksize,
            double 	sigmaX,
            double 	sigmaY,
            int 	borderType
            */
            break;
        default:
            CV_Error(cv::Error::StsBadArg, "Invalid blur type");
    }
    output = input.clone();
    blurred.copyTo(output, 255 - fg_mask);
    //

    CV_Assert(output.type() == input.type());
    CV_Assert(output.size() == input.size());
}
