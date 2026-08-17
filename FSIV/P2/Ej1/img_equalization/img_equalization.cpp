#include <iostream>
#include <exception>

#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "common_code.hpp"
#include "clahe.hpp"

const cv::String keys =
    "{help h usage ? |      | Print this message.}"
    "{i interactive  |      | Activate interactive mode.}"
    "{r radius       |0     | Set the roi size to (2*2^r+1). A value r=0 means global processing.}"
    "{s slope_factor |0     | Set the slope factor to control the contrast limitation. A value <1.0 do not do such control.}"
    "{@input         |<none>| Input image.}"
    "{@output        |<none>| Output image.}";

typedef struct
{
  cv::Mat in;
  cv::Mat out;
  cv::Mat hist_in;
  cv::Mat hist_img_in;
  bool interactive;
  int r;
  float s;
} UserData;

cv::Mat draw_histogram(const cv::Mat &hist, int width, int height,
                       const cv::Scalar &color = cv::Scalar(255, 255, 255))
{
  // Crear imagen en negro para dibujar el histograma
  cv::Mat hist_image = cv::Mat::zeros(height, width, CV_8UC3);

  // Verificar que el histograma sea válido
  if (hist.empty() || hist.rows <= 0)
    return hist_image;

  int hist_size = hist.rows;

  // Normalizar el histograma para que se ajuste a la altura de la imagen
  cv::Mat normalized_hist;
  cv::normalize(hist, normalized_hist, 0, height * 0.9, cv::NORM_MINMAX, -1, cv::Mat());

  // Calcular el ancho de cada barra del histograma
  int bin_width = width / hist_size;

  // Dibujar cada barra del histograma
  for (int i = 0; i < hist_size; i++)
  {
    int bin_height = static_cast<int>(normalized_hist.at<float>(i));

    // Coordenadas del rectángulo
    cv::Point pt1(i * bin_width, height);
    cv::Point pt2((i + 1) * bin_width, height - bin_height);

    // Dibujar la barra
    cv::rectangle(hist_image, pt1, pt2, color, -1);
  }

  return hist_image;
}

void do_the_work(UserData *data)
{
  cv::Mat in = data->in;
  std::vector<cv::Mat> channels;
  if (data->in.channels() == 3)
  {
    cv::Mat hsv;
    cv::cvtColor(data->in, hsv, cv::COLOR_BGR2HSV);
    cv::split(hsv, channels);
    in = channels[2];
  }

  cv::Mat out = fsiv_clahe(in, data->s, data->r);

  if (data->in.channels() == 3)
  {
    cv::Mat hsv;
    channels[2] = out;
    cv::merge(channels, hsv);
    cv::cvtColor(hsv, data->out, cv::COLOR_HSV2BGR);
  }
  else
    data->out = out;

  if (data->interactive)
  {
    cv::imshow("OUTPUT", data->out);
    if (data->hist_in.empty())
    {
      data->hist_in = fsiv_compute_image_histogram(in);
      data->hist_img_in = draw_histogram(data->hist_in, 512, 400, cv::Scalar(255, 0, 0));
    }
    cv::Mat hist_out = fsiv_compute_image_histogram(out);
    cv::Mat hist_img_out = draw_histogram(hist_out, 512, 400, cv::Scalar(0, 255, 0));

    cv::imshow("INPUT HISTOGRAM", data->hist_img_in);
    cv::imshow("OUTPUT HISTOGRAM", hist_img_out);
  }
}

void on_change_s(int v, void *data_)
{
  UserData *data = static_cast<UserData *>(data_);
  data->s = v / 10.0;
  std::cerr << "Setting s to " << data->s << std::endl;
  do_the_work(data);
}

void on_change_r(int v, void *data_)
{
  UserData *data = static_cast<UserData *>(data_);
  data->r = v > 0 ? 1 << v : 0;
  std::cerr << "Setting r to " << data->r << std::endl;
  do_the_work(data);
}

int main(int argc, char *const *argv)
{
  int retCode = EXIT_SUCCESS;

  try
  {

    cv::CommandLineParser parser(argc, argv, keys);
    parser.about("Apply an contrast limited image equalization to the image. (ver 2.0.0)");
    if (parser.has("help"))
    {
      parser.printMessage();
      return 0;
    }

    cv::String input_name = parser.get<cv::String>(0);
    cv::String output_name = parser.get<cv::String>(1);
    int radius = parser.get<int>("r");
    float slope_factor = parser.get<float>("s");
    bool interactive = parser.has("i");

    if (!parser.check())
    {
      parser.printErrors();
      return 0;
    }

    UserData data;
    data.in = cv::imread(input_name, cv::IMREAD_ANYCOLOR);
    if (data.in.empty())
    {
      std::cerr << "Error: could not open the input image." << std::endl;
      exit(-1);
    }

    data.out = data.in.clone();
    data.interactive = interactive;
    data.s = std::max(0.0f, std::min(10.0f, slope_factor));
    radius = std::max(0, std::min(radius, int(std::log(std::min(data.in.rows, data.in.cols)))));
    data.r = radius == 0 ? 0 : 1 << radius;

    int key = 0;

    if (data.interactive)
    {
      cv::namedWindow("INPUT", cv::WINDOW_GUI_EXPANDED + cv::WINDOW_NORMAL);
      cv::resizeWindow("INPUT", 600, 600.0 * data.in.rows / data.in.cols);
      cv::imshow("INPUT", data.in);

      cv::namedWindow("OUTPUT", cv::WINDOW_GUI_EXPANDED + cv::WINDOW_NORMAL);
      cv::resizeWindow("OUTPUT", 600, 600.0 * data.in.rows / data.in.cols);

      cv::namedWindow("INPUT HISTOGRAM", cv::WINDOW_GUI_EXPANDED + cv::WINDOW_NORMAL);
      cv::resizeWindow("INPUT HISTOGRAM", 512, 400);
      cv::namedWindow("OUTPUT HISTOGRAM", cv::WINDOW_GUI_EXPANDED + cv::WINDOW_NORMAL);
      cv::resizeWindow("OUTPUT HISTOGRAM", 512, 400);

      cv::namedWindow("PARAMETERS", cv::WINDOW_NORMAL);
      cv::createTrackbar("S", "PARAMETERS", 0, 100, on_change_s, &data);
      cv::setTrackbarPos("S", "PARAMETERS", std::min(data.s, 10.0f) * 10.0);
      cv::createTrackbar("R", "PARAMETERS", 0, int(std::log(std::min(data.in.rows, data.in.cols))), on_change_r, &data);
      cv::setTrackbarPos("R", "PARAMETERS", radius);
      std::cout << "Interactive mode. Press <ESC> to abort or <ENTER> to finish saving the output." << std::endl;
      do_the_work(&data);
      do
      {
        key = cv::waitKey(0) & 0xff;
      } while ((key != 27) && (key != 13));
    }
    else
      do_the_work(&data);

    if (key != 27)
    {
      if (!cv::imwrite(output_name, data.out))
      {
        std::cerr << "Error: could not save the result in file '"
                  << output_name << "'." << std::endl;
        return EXIT_FAILURE;
      }
    }
  }
  catch (std::exception &e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  catch (...)
  {
    std::cerr << "Error: unknown exception caught!" << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}
