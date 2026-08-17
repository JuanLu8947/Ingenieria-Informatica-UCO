#include "common_code.hpp"

cv::Mat
fsiv_convert_image_byte_to_float(const cv::Mat &img)
{
    CV_Assert(img.depth() == CV_8U);
    cv::Mat out; //n-dimensional dense array class -> M
    //! TODO
    // Hint: use cv::Mat::convertTo().
    img.convertTo(out, CV_32F, 1.0 / 255.0);
    /*
    OutputArray 	m,
    int 	rtype,
    double 	alpha = 1,
    double 	beta = 0 	
    */
    //
    CV_Assert(out.rows == img.rows && out.cols == img.cols);
    CV_Assert(out.depth() == CV_32F);
    CV_Assert(img.channels() == out.channels());
    return out;
}

cv::Mat
fsiv_convert_image_float_to_byte(const cv::Mat &img)
{
    CV_Assert(img.depth() == CV_32F);
    cv::Mat out;
    //! TODO
    // Hint: use cv::Mat::convertTo()
    img.convertTo(out, CV_8U, 255.0);
    //
    CV_Assert(out.rows == img.rows && out.cols == img.cols);
    CV_Assert(out.depth() == CV_8U);
    CV_Assert(img.channels() == out.channels());
    return out;
}

cv::Mat
fsiv_convert_bgr_to_hsv(const cv::Mat &img)
{
    CV_Assert(img.channels() == 3);
    cv::Mat out;
    //! TODO
    // Hint: use cvtColor.
    // Remember: the input color scheme is assumed to be BGR.
    cv::cvtColor(img, out, cv::COLOR_BGR2HSV);
    //
    CV_Assert(out.channels() == 3);
    return out;
}

cv::Mat
fsiv_convert_hsv_to_bgr(const cv::Mat &img)
{
    CV_Assert(img.channels() == 3);
    cv::Mat out;
    //! TODO
    // Hint: use cvtColor.
    // Remember: the ouput color scheme is assumed to be BGR.
    cv::cvtColor(img, out, cv::COLOR_HSV2BGR);
    //
    CV_Assert(out.channels() == 3);
    return out;
}

cv::Mat
fsiv_cbg_process(const cv::Mat &in,
                 double contrast, double brightness, double gamma,
                 bool only_luma)
{
    CV_Assert(in.depth() == CV_8U);
    cv::Mat out;
    // TODO
    // Hint: convert to float range [0,1] before processing the image.
    // Hint: use cv::pow() to apply the gamma parameter.
    // Hint: if input channels is 3 and only luma is required, convert to HSV
    //       color space and process only de V (luma) channel.
    /*if(only_luma && in.channels() == 3){
        // Convert to HSV
        out = fsiv_convert_bgr_to_hsv(in);
        
        // Split channels
        std::vector<cv::Mat> channels;
        cv::split(out, channels);
        
        // Process only V channel (index 2: H=0, S=1, V=2)
        //cv::Mat v_channel = channels[2];
        cv::Mat v_channel;
        channels[2].copyTo(v_channel);
        
        // Convert V channel to float [0,1]
        v_channel = fsiv_convert_image_byte_to_float(v_channel);
        
        // Apply corrections in the correct order: gamma first, then contrast and brightness
        cv::pow(v_channel, gamma, v_channel);
        v_channel = v_channel * contrast + brightness;
        
        // Convert back to byte
        v_channel = fsiv_convert_image_float_to_byte(v_channel);
        
        // Put the processed V channel back
        channels[2] = v_channel;
        
        // Merge channels
        cv::merge(channels, out);
        
        // Convert back to BGR
        out = fsiv_convert_hsv_to_bgr(out);
    }
    else {
        // Process all channels
        out = fsiv_convert_image_byte_to_float(in);
        cv::pow(out, gamma, out);
        out = out * contrast + cv::Scalar::all(brightness);
        out = fsiv_convert_image_float_to_byte(out);
    }*/
    std::vector<cv::Mat> mv;
    out=fsiv_convert_image_byte_to_float(in);
    if(only_luma && in.channels() == 3){
        out=fsiv_convert_bgr_to_hsv(out);
        cv::split(out,mv); //1
        out=mv[2];
    }

    cv::pow(out,gamma,out); //2
    out*=contrast;
    out+=cv::Scalar::all(brightness);

    if(only_luma && in.channels()==3){
        cv::merge(mv,out);
        out=fsiv_convert_hsv_to_bgr(out);
    }
    out=fsiv_convert_image_float_to_byte(out);
    /*
    1:
    Separa los 3 canales HSV en el vector mv
    mv[0] = canal H, mv[1] = canal S, mv[2] = canal V

    2:
    Si gamma > 1 → imagen más oscura; si gamma < 1 → imagen más clara
    */
    //
    CV_Assert(out.rows == in.rows && out.cols == in.cols);
    CV_Assert(out.depth() == CV_8U);
    CV_Assert(out.channels() == in.channels());
    return out;
}
