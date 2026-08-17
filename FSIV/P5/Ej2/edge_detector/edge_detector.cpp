#include <iostream>
#include <exception>

// Includes para OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#include "common_code.hpp"

const char *keys =
    "{help h usage ? |      | print this message   }"
    "{i              |      | Activate interactive mode.}"
    "{s_ap           | 1    | Sobel kernel aperture radio: 0, 1, 2, 3}"
    "{n_bins         | 100  | Gradient histogram size}"
    "{g_r            | 1    | radius of gaussian filter (2r+1). Value 0 means don't filter.}"
    "{th             | 0.8  | Gradient percentile used as threshold for the gradient percentile detector (th2 for canny).}"
    "{th1            | 0.2  | Gradient percentile used as th1 threshold for the Canny detector (th1 < th).}"
    "{thinning      |      | If set, the output edges are thinned (only for percentile and otsu detectors).}"
    "{m method       | 0    | Detector used: 0:percentile detector, 1:Otsu detector, 2:canny detector}"
    "{c consensus    | 50   | If a ground truth was given, use greater to c% consensus to generate ground truth.}"
    "{@input         |<none>| input image.}"
    "{@output        |<none>| output image.}"
    "{@ground_truth  |      | optional ground truth image to compute the detector metrics.}";

struct Parameters
{
  cv::Mat input;
  cv::Mat gt_img;
  cv::Mat edges;
  cv::Mat dx;
  cv::Mat dy;
  cv::Mat gradient;
  int n_bins;
  int g_r;
  int th2;
  int th1;
  int s_ap;
  int method;
  bool interactive;
  float consensus;
  bool thinning;
};

const char *detectors_names[] = {
    "PERCENTILE",
    "OTSU",
    "CANNY"};

cv::Mat draw_histogram(const cv::Mat &hist, int width, int height,
                       const cv::Scalar &color = cv::Scalar::all(0))
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
    cv::Scalar color_ = color;
    if (color == cv::Scalar::all(0))
      color_ = cv::Scalar(cv::theRNG().uniform(100, 256),
                          cv::theRNG().uniform(100, 256),
                          cv::theRNG().uniform(100, 256));

    // Dibujar la barra
    cv::rectangle(hist_image, pt1, pt2, color_, -1);
  }

  return hist_image;
}

void do_the_process(Parameters *params)
{
  fsiv_compute_derivate(params->input, params->dx, params->dy, params->g_r,
                        2 * params->s_ap + 1);
  fsiv_compute_gradient_magnitude(params->dx, params->dy, params->gradient);
  switch (params->method)
  {
  case 0:
    fsiv_percentile_edge_detector(params->gradient, params->edges,
                                  params->th2 / 100.0, params->n_bins);
    break;
  case 1:
    fsiv_otsu_edge_detector(params->gradient, params->edges);
    break;
  case 2:
    fsiv_canny_edge_detector(params->dx, params->dy, params->edges,
                             params->th1 / 100.0, params->th2 / 100.0, params->n_bins);
    break;
  default:
    throw std::runtime_error("Method not implemented.");
    break;
  }

  if (params->thinning && (params->method == 0 || params->method == 1))
  {
    params->edges = fsiv_thinning_edge_map(params->edges);
  }

  if (!params->gt_img.empty())
  {
    cv::Mat cm;
    cv::Mat gt_img;
    fsiv_compute_ground_truth_image(params->gt_img, params->consensus, gt_img);
    cv::imshow("GROUND TRUTH", gt_img);
    fsiv_compute_edge_detector_confusion_matrix(gt_img, params->edges, cm);
    std::cout << "Method      : " << detectors_names[params->method] << std::endl;
    std::cout << "GT consensus: " << params->consensus << "%" << std::endl;
    std::cout << "sensitivity : " << fsiv_compute_sensitivity(cm) << std::endl;
    std::cout << "precision   : " << fsiv_compute_precision(cm) << std::endl;
    std::cout << "F1          : " << fsiv_compute_F1_score(cm) << std::endl;
    std::cout << std::endl;
  }

  if (params->interactive)
  {
    cv::Mat grad_hist;
    float max_grad;
    fsiv_compute_gradient_histogram(params->gradient, 100, grad_hist, max_grad);
    cv::imshow("GRADIENT HIST", draw_histogram(grad_hist, 200, 100));
    cv::imshow("GRADIENT", params->gradient / max_grad);
    cv::imshow(detectors_names[params->method], params->edges);
  }
}

void onChange_s_ap(int count, void *data)
{
  Parameters *params = reinterpret_cast<Parameters *>(data);
  params->s_ap = count;
  do_the_process(params);
}

void onChange_g_r(int count, void *data)
{
  Parameters *params = reinterpret_cast<Parameters *>(data);
  params->g_r = count;
  do_the_process(params);
}

void onChange_th1(int count, void *data)
{
  Parameters *params = reinterpret_cast<Parameters *>(data);
  params->th1 = count;
  if (params->th1 >= params->th2)
  {
    params->th1 = params->th2 - 1;
    cv::setTrackbarPos("TH1", "PARAMETERS", params->th1);
  }
  do_the_process(params);
}

void onChange_th2(int count, void *data)
{
  Parameters *params = reinterpret_cast<Parameters *>(data);
  params->th2 = count;
  if (params->th1 >= params->th2)
  {
    params->th2 = params->th1 + 1;
    cv::setTrackbarPos("TH2", "PARAMETERS", params->th2);
  }
  do_the_process(params);
}

void onChange_method(int count, void *data)
{
  Parameters *params = reinterpret_cast<Parameters *>(data);
  params->method = count;
  do_the_process(params);
}

void onChange_consensus(int count, void *data)
{
  Parameters *params = reinterpret_cast<Parameters *>(data);
  params->consensus = count;
  do_the_process(params);
}

void onChange_thinning(int count, void *data)
{
  Parameters *params = reinterpret_cast<Parameters *>(data);
  params->thinning = (count != 0);
  do_the_process(params);
}

int main(int argc, char *const *argv)
{
  int retCode = EXIT_SUCCESS;

  try
  {

    cv::CommandLineParser parser(argc, argv, keys);
    parser.about("Edge detector v0.0");
    if (parser.has("help"))
    {
      parser.printMessage();
      return 0;
    }
    cv::String input_fname = parser.get<cv::String>("@input");
    cv::String output_fname = parser.get<cv::String>("@output");
    cv::String gt_fname = parser.get<cv::String>("@ground_truth");
    int n_bins = parser.get<int>("n_bins");
    int g_r = parser.get<int>("g_r");
    float th2 = parser.get<float>("th");
    float th1 = parser.get<float>("th1");
    int s_ap = parser.get<int>("s_ap");
    int method = parser.get<int>("method");
    float consensus = parser.get<float>("c");
    bool interactive = parser.has("i");
    bool thinning = parser.has("thinning");

    if (!parser.check())
    {
      parser.printErrors();
      return 0;
    }

    cv::Mat img = cv::imread(input_fname, cv::IMREAD_GRAYSCALE);
    if (img.empty())
    {
      std::cerr << "Error: cannot read image: " << input_fname << std::endl;
      return EXIT_FAILURE;
    }
    cv::Mat gt_img;
    if (gt_fname != "")
    {
      gt_img = cv::imread(gt_fname, cv::IMREAD_GRAYSCALE);
      if (gt_img.empty())
      {
        std::cerr << "Error: cannot read ground truth image: " << gt_fname << std::endl;
        return EXIT_FAILURE;
      }
    }
    Parameters params;
    params.input = img;
    params.gt_img = gt_img;
    params.n_bins = n_bins;
    params.g_r = g_r;
    params.s_ap = s_ap;
    params.th1 = th1 * 100;
    params.th2 = th2 * 100;
    params.method = method;
    params.interactive = interactive;
    params.consensus = consensus;
    params.thinning = thinning;

    if (interactive)
    {
      cv::namedWindow("ORIGINAL", cv::WINDOW_AUTOSIZE + cv::WINDOW_GUI_EXPANDED);
      cv::namedWindow("GRADIENT", cv::WINDOW_AUTOSIZE + cv::WINDOW_GUI_EXPANDED);
      cv::namedWindow("GRADIENT HIST", cv::WINDOW_NORMAL + cv::WINDOW_GUI_EXPANDED);
      cv::namedWindow("GROUND TRUTH", cv::WINDOW_AUTOSIZE + cv::WINDOW_GUI_EXPANDED);
      cv::namedWindow("PERCENTILE", cv::WINDOW_AUTOSIZE + cv::WINDOW_GUI_EXPANDED);
      cv::namedWindow("OTSU", cv::WINDOW_AUTOSIZE + cv::WINDOW_GUI_EXPANDED);
      cv::namedWindow("CANNY", cv::WINDOW_AUTOSIZE + cv::WINDOW_GUI_EXPANDED);

      cv::imshow("ORIGINAL", img);
      cv::namedWindow("PARAMETERS", cv::WINDOW_NORMAL);
      cv::createTrackbar("S_AP", "PARAMETERS", nullptr, 3,
                         onChange_s_ap, &params);
      cv::setTrackbarPos("S_AP", "PARAMETERS", params.s_ap);
      cv::createTrackbar("G_R", "PARAMETERS", nullptr, 15,
                         onChange_g_r, &params);
      cv::setTrackbarPos("G_R", "PARAMETERS", params.g_r);
      cv::createTrackbar("TH1", "PARAMETERS", nullptr, 100,
                         onChange_th1, &params);
      cv::setTrackbarPos("TH1", "PARAMETERS", params.th1);
      cv::createTrackbar("TH2", "PARAMETERS", nullptr, 100,
                         onChange_th2, &params);
      cv::setTrackbarPos("TH2", "PARAMETERS", params.th2);
      cv::createTrackbar("method", "PARAMETERS", nullptr, 2,
                         onChange_method, &params);
      cv::setTrackbarPos("method", "PARAMETERS", params.method);
      cv::createTrackbar("Thinning", "PARAMETERS", nullptr, 1,
                         onChange_thinning, &params);
      cv::setTrackbarPos("Thinning", "PARAMETERS", params.thinning ? 1 : 0);
      if (!params.gt_img.empty())
      {
        cv::createTrackbar("consensus", "PARAMETERS", nullptr, 100,
                           onChange_consensus, &params);
        cv::setTrackbarPos("consensus", "PARAMETERS", params.consensus);
      }
      do_the_process(&params);
      int key = 0;
      while (key != 13 && key != 27)
        key = cv::waitKey(0) & 0xff;
      if (key != 27)
        cv::imwrite(output_fname, params.edges);
    }
    else
    {
      do_the_process(&params);
      cv::imwrite(output_fname, params.edges);
    }
  }
  catch (std::exception &e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  catch (...)
  {
    std::cerr << "Capturada excepcion desconocida!" << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}
