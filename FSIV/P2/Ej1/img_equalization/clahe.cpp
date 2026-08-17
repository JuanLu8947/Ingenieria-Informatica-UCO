/**
 * @file clahe.cpp
 * @author Francisco José Madrid Cuevas (fjmadrid@uco.es)
 * @brief Implementation of the method Limited Contrast Adaptive Histogram Equalization.
 * @version 1.0
 * @date 2024-09-13
 *
 * @copyright Copyright (c) 2024-
 *
 */
#include "clahe.hpp"
#include "common_code.hpp"
#include <opencv2/imgproc.hpp>

static uchar interpolate_corner(const cv::Mat &in,
                                const std::vector<cv::Mat> &lkts, const cv::Point &p,
                                const cv::Size &cell_size, const cv::Size &grid_size)
{
    const int x_off = (cell_size.width + 1) >> 1;
    const int y_off = (cell_size.height + 1) >> 1;

    CV_Assert((p.x < x_off && p.y < y_off) ||
              (p.x < x_off && p.y >= (in.rows - y_off - 1)) ||
              (p.x >= (in.cols - x_off - 1) && p.y < x_off) ||
              (p.x >= (in.cols - x_off - 1) && p.y >= (in.rows - y_off - 1)));

    const int cell_y = p.y / cell_size.height;
    const int cell_x = p.x / cell_size.width;
    const int h_idx = cell_y * grid_size.width + cell_x;
    uchar out = lkts[h_idx].at<uchar>(in.at<uchar>(p));
    return out;
}

static uchar linear_interpolate_rows(const cv::Mat &in,
                                     const std::vector<cv::Mat> &lkts, const cv::Point &p,
                                     const cv::Size &cell_size, const cv::Size &grid_size)
{
    const int x_off = cell_size.width >> 1;
    const int y_off = cell_size.height >> 1;
    CV_Assert(p.x >= x_off && p.x < (in.cols - x_off - 1) &&
              ((p.y < y_off) || p.y >= (in.rows - y_off - 1)));

    const int cell_y = (p.y - y_off) / cell_size.height;
    int cell1_x = (p.x - x_off) / cell_size.width;
    const int cell2_x = cell1_x + 1;
    const float center2_x = cell2_x * cell_size.width + x_off;
    const float w1 = (center2_x - p.x) / cell_size.width;
    const float w2 = 1.0 - w1;
    const int idx1 = cell_y * grid_size.width + cell1_x;
    const int idx2 = cell_y * grid_size.width + cell2_x;
    const uchar in_v = in.at<uchar>(p);
    uchar out = w1 * lkts[idx1].at<uchar>(in_v) +
                w2 * lkts[idx2].at<uchar>(in_v);
    return out;
}

static uchar linear_interpolate_cols(const cv::Mat &in,
                                     const std::vector<cv::Mat> &lkts, const cv::Point &p,
                                     const cv::Size &cell_size, const cv::Size &grid_size)
{
    const int x_off = cell_size.width >> 1;
    const int y_off = cell_size.height >> 1;

    CV_Assert(p.y >= y_off && p.y < (in.rows - y_off - 1) &&
              ((p.x < x_off) || p.x >= (in.cols - x_off - 1)));

    const int cell_x = p.x / cell_size.width;
    int cell1_y = (p.y - y_off) / cell_size.height;
    const int cell2_y = cell1_y + 1;
    const float center2_y = cell2_y * cell_size.height + y_off;
    const float w1 = (center2_y - p.y) / cell_size.height;
    const float w2 = 1.0 - w1;
    const int idx1 = cell1_y * grid_size.width + cell_x;
    const int idx2 = cell2_y * grid_size.width + cell_x;
    const uchar in_v = in.at<uchar>(p);
    uchar out = w1 * lkts[idx1].at<uchar>(in_v) +
                w2 * lkts[idx2].at<uchar>(in_v);
    return out;
}

static uchar bilinear_interpolate(const cv::Mat &in,
                                  const std::vector<cv::Mat> &lkts, const cv::Point &p,
                                  const cv::Size &cell_size, const cv::Size &grid_size)
{
    const int x_off = cell_size.width >> 1;
    const int y_off = cell_size.height >> 1;
    CV_Assert(p.y >= y_off && p.y < (in.rows - y_off - 1) &&
              p.x >= x_off && p.x < (in.cols - x_off - 1));

    const int cell1_x = (p.x - x_off) / cell_size.width;
    const int cell1_y = (p.y - y_off) / cell_size.height;
    const int cell2_x = cell1_x + 1;
    const int cell2_y = cell1_y;
    const int cell3_x = cell1_x + 1;
    const int cell3_y = cell1_y + 1;
    const int cell4_x = cell1_x;
    const int cell4_y = cell1_y + 1;
    const float center3_x = cell3_x * cell_size.width + x_off;
    const float center3_y = cell3_y * cell_size.height + y_off;
    const int idx11 = cell1_y * grid_size.width + cell1_x;
    const int idx12 = cell2_y * grid_size.width + cell2_x;
    const int idx22 = cell3_y * grid_size.width + cell3_x;
    const int idx21 = cell4_y * grid_size.width + cell4_x;
    const uchar in_v = in.at<uchar>(p);
    const uchar q11 = lkts[idx11].at<uchar>(in_v);
    const uchar q12 = lkts[idx12].at<uchar>(in_v);
    const uchar q22 = lkts[idx22].at<uchar>(in_v);
    const uchar q21 = lkts[idx21].at<uchar>(in_v);
    const float w_x = (center3_x - p.x) / cell_size.width;
    const float out_x1 = w_x * q11 + (1.0f - w_x) * q12;
    const float out_x2 = w_x * q21 + (1.0f - w_x) * q22;
    const float w_y = (center3_y - p.y) / cell_size.height;
    const uchar out = cv::saturate_cast<uchar>(w_y * out_x1 + (1.0f - w_y) * out_x2);
    return out;
}

static uchar compute_interpolate_value(const cv::Mat &in,
                                       const std::vector<cv::Mat> &lkts, const cv::Point &p,
                                       const cv::Size &cell_size, const cv::Size &grid_size)
{
    uchar out = in.at<uchar>(p);
    const int x_off = cell_size.width >> 1;
    const int y_off = cell_size.height >> 1;

    if (p.y >= y_off && p.y < (in.rows - y_off - 1) &&
        p.x >= x_off && p.x < (in.cols - x_off - 1))
        out = bilinear_interpolate(in, lkts, p, cell_size, grid_size);
    else if (p.y >= y_off && p.y < (in.rows - y_off - 1) &&
             ((p.x < x_off) || p.x >= (in.cols - x_off - 1)))
        out = linear_interpolate_cols(in, lkts, p, cell_size, grid_size);
    else if (p.x >= x_off && p.x < (in.cols - x_off - 1) &&
             ((p.y < y_off) || p.y >= (in.rows - y_off - 1)))
        out = linear_interpolate_rows(in, lkts, p, cell_size, grid_size);
    else
        out = interpolate_corner(in, lkts, p, cell_size, grid_size);
    return out;
}

cv::Mat
fsiv_clahe(const cv::Mat &in_, float s, int radius)
{
    CV_Assert(in_.type() == CV_8UC1);
    cv::Mat out = in_.clone();
    // TODO
    // Hint: use all the fsiv_xxx implemented functions.
    // Remember: if radius>0, do an local histogram equalization using windows
    //  of size (2*r+1, 2*r+1). The not processed image ares will be the same
    //  values as the input image.

    if (radius == 0)
    {
        // TODO: do a global equalization.
        // Hint: use fsiv_apply_lookup_table to apply the transform function
        // computed to all the image positions.
        cv::Mat hist = fsiv_compute_image_histogram(in_);
        cv::Mat lkt =
            fsiv_create_equalization_lookup_table(hist, s);
        fsiv_apply_lookup_table(in_, lkt, out);
        //
    }
    else
    {
        // TODO: Do a local equalization.
        // Remember: the windows size will be [2*r+1, 2*r+1]
        // Remember: Only process the values in the image area
        //           [[r, height-r], [r, width-r]]
        // Hint: use cv::Rect() to define a window to be processed.

        // First extend the input if it is needed to be a multiple of the cell size.
        cv::Size cell_size = cv::Size(2 * radius + 1, 2 * radius + 1);
        // cv::Size cell_size = cv::Size(1 << radius, 1 << radius);
        cv::Mat in = in_;
        if ((in_.rows % cell_size.height) != 0 || (in_.cols % cell_size.width) != 0)
        {
            in = cv::Mat(in_.rows + cell_size.height - (in_.rows % cell_size.height),
                         in_.cols + cell_size.width - (in_.cols % cell_size.width), in.type());
            cv::copyMakeBorder(in_, in, 0, cell_size.height - (in_.rows % cell_size.height),
                               0, cell_size.width - (in_.cols % cell_size.width), cv::BORDER_REFLECT101);
        }
        cv::Size grid_size = cv::Size(in.cols / cell_size.width, in.rows / cell_size.height);
        // Compute a transform function for each image cell.
        std::vector<cv::Mat> lkts(grid_size.area());
        for (int cell_row = 0; cell_row < grid_size.height; ++cell_row)
            for (int cell_col = 0; cell_col < grid_size.width; ++cell_col)
            {
                const int idx = cell_row * grid_size.width + cell_col;
                cv::Mat hist = fsiv_compute_image_histogram(in(cv::Rect(cell_col * cell_size.width,
                                                                        cell_row * cell_size.height, cell_size.width, cell_size.height)));
                lkts[idx] = fsiv_create_equalization_lookup_table(hist, s);
            }
        // Apply the transform interpolating on the grid.
        for (int y = 0; y < in_.rows; ++y)
            for (int x = 0; x < in_.cols; ++x)
            {
                out.at<uchar>(y, x) = compute_interpolate_value(in, lkts, cv::Point(x, y), cell_size, grid_size);
            }
        //
    }
    CV_Assert(out.size() == in_.size());
    CV_Assert(out.type() == in_.type());
    return out;
}
