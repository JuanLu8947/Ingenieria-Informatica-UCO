#include <iostream>
#include "common_code.hpp"
#include <opencv2/imgproc.hpp>

cv::Mat
fsiv_create_gaussian_filter(const int r)
{
    CV_Assert(r > 0);
    cv::Mat ret_v;
    //! TODO
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

cv::Mat fsiv_create_lap4_filter()
{
    cv::Mat ret_v;
    //! TODO
    // Hint: you can use a comma-separated initializer.
    //       See: https://docs.opencv.org/4.5.5/d6/d9e/classcv_1_1MatCommaInitializer__.html
    ret_v = (cv::Mat_<float>(3,3) << 0, 1, 0,
                                       1,-4, 1,
                                       0, 1, 0);
    /*
    crea un filtro Laplaciano de 4 vecinos:
     para ello usa una matriz 3x3:
      El valor central es -4, y los valores de sus vecinos (arriba, abajo, izquierda, derecha) son 1.
      Los valores en las esquinas son 0.
    Este filtro se usa para detectar bordes en imágenes, resaltando los cambios bruscos de intensidad. La suma total de la máscara es 0, lo que significa que no cambia el brillo global de la imagen, solo resalta los bordes.
    */
    //
    CV_Assert(!ret_v.empty());
    CV_Assert(ret_v.rows == 3 && ret_v.cols == 3);
    CV_Assert(ret_v.type() == CV_32FC1);
    return ret_v;
}

cv::Mat fsiv_create_lap8_filter()
{
    cv::Mat ret_v;
    //! TODO
    // Hint: you can use a comma-separated initializer.
    //       See: https://docs.opencv.org/4.5.5/d6/d9e/classcv_1_1MatCommaInitializer__.html
    ret_v = (cv::Mat_<float>(3,3) <<
              1.0f,  1.0f,  1.0f,
              1.0f, -8.0f,  1.0f,
              1.0f,  1.0f,  1.0f);
    /*
    Crea un filtro Laplaciano de 8 vecinos (float):
     para ello usa una matriz 3x3:
      El valor central es -8, y los valores de sus ocho vecinos (arriba, abajo, izquierda, derecha y las cuatro diagonales) son 1
    */
    //ret_v.convertTo(ret_v, CV_32FC1);
    //
    CV_Assert(!ret_v.empty());
    CV_Assert(ret_v.rows == 3 && ret_v.cols == 3);
    CV_Assert(ret_v.type() == CV_32FC1);
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
    //  Hint: use cv::copyMakeBorder() filling with border wrap extrapolation.
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

cv::Mat fsiv_create_dog_filter(int r1, int r2)
{
    CV_Assert(r1 > 0 && r1 < r2);
    cv::Mat ret_v;

    //! TODO
    // Hint: use fsiv_create_gaussian_filter() and fsiv_fill_expansion() to
    //       expand the smaller filter to be the same size as the larger one,
    //       so you can get the difference of both.
    ret_v = fsiv_create_gaussian_filter(r2);
    /*
    fsiv_create_gaussian_filter(r2) genera un filtro gaussiano grande
     de radio r2. 
    El resultado es una matriz cuadrada de tamaño
     (2*r2+1) x (2*r2+1).
    */
    ret_v -= fsiv_fill_expansion(fsiv_create_gaussian_filter(r1), r2 - r1);
    /*
    DoG (Difference of Gaussians):
     fsiv_fill_expansion(..., r2 - r1) toma el filtro pequeño 
      y lo expande (rellenando con ceros alrededor)
       hasta que tenga el mismo tamaño que el filtro grande.
      Así, ambos filtros tienen el mismo tamaño y 
       se pueden restar.
    */
    //

    CV_Assert(!ret_v.empty());
    CV_Assert(ret_v.rows == (2 * r2 + 1) && ret_v.cols == (2 * r2 + 1));
    CV_Assert(ret_v.type() == CV_32FC1);
    return ret_v;
}

cv::Mat
fsiv_create_sharpening_filter(const int filter_type, int r1, int r2)
{
    CV_Assert(0 <= filter_type && filter_type <= 2);
    CV_Assert(filter_type != 2 || (0 < r1 && r1 < r2));
    cv::Mat filter;
    //! TODO
    //  Remember: sharpening filter = -Laplacian + [1]
    cv::Mat L;
    if (filter_type == 0) {
        L = fsiv_create_lap4_filter();
    }
    else if (filter_type == 1) {
        L = fsiv_create_lap8_filter();
    }
    else { // filter_type == 2 (DoG)
        L = fsiv_create_dog_filter(r1, r2);
    }

    filter = -L; // -Laplacian (or -DoG) //Esto invierte el efecto del filtro, pasando de detectar bordes a realzar detalles.
    int cy = filter.rows / 2; //calculan la posición del centro de la matriz del filtro (kernel).
    int cx = filter.cols / 2;
    filter.at<float>(cy, cx) += 1.0f; // add 1 at the center (impulse)
    /*
    Hace que el filtro no solo realce bordes, sino que
     también conserve la información original de la imagen
      (efecto “high-boost” o realce).
    */
    //
    CV_Assert(!filter.empty() && filter.type() == CV_32FC1);
    CV_Assert((filter_type == 2) || (filter.rows == 3 && filter.cols == 3));
    CV_Assert((filter_type != 2) || (filter.rows == (2 * r2 + 1) &&
                                     filter.cols == (2 * r2 + 1)));
    return filter;
}

cv::Mat
fsiv_image_sharpening(const cv::Mat &in, int filter_type,
                      int r1, int r2, bool circular)
{
    CV_Assert(in.type() == CV_32FC1);
    CV_Assert(0 < r1 && r1 < r2);
    CV_Assert(0 <= filter_type && filter_type <= 2);
    cv::Mat out;

    //! TODO
    // Remember: The effect consists of performing a convolution of the input
    //           image with the appropriate sharpening filter.
    // Hint: use cv::filter2D to convolve. In this case, because the input
    //       image is already extended, you should use 'cv::BORDER_ISOLATED'
    //       to do nothing to the extended area.
    // Remember: the convolved output image has the extended size but we need
    //           to return one with size equal to the input size. You can use
    //           cv::Mat::copyTo on a centered window to extract the result.

    // Build sharpening filter
    cv::Mat sharp_filt = fsiv_create_sharpening_filter(filter_type, r1, r2);
    int radius = sharp_filt.rows / 2;

    // Expand input image according to chosen border mode
    cv::Mat in_expanded;
    if (circular)
        in_expanded = fsiv_circular_expansion(in, radius);
    else
        in_expanded = fsiv_fill_expansion(in, radius);

    // Convolucion con BORDER_ISOLATED
    cv::Mat conv;
    cv::filter2D(in_expanded, conv, -1, sharp_filt, cv::Point(-1, -1), 0.0, cv::BORDER_ISOLATED);
    /*
    cv::filter2D aplica el filtro de realce a la imagen
     expandida.
    Se usa cv::BORDER_ISOLATED para que la convolución no
     mezcle los bordes añadidos con la imagen original.
    (InputArray src,
    OutputArray dst,
    int depth, -1 significa que se usará la misma profundidad que la imagen de entrada.
    InputArray kernel, Kernel o filtro de realce
    Point anchor = Point(-1,-1), significa que el centro del kernel se usa como anclaje.
    double delta = 0.0: Valor añadido a cada píxel después de la convolución
    int borderType)
    */

    // Crop back to original size
    cv::Rect roi(radius, radius, in.cols, in.rows);
    /*
    Crea un rectángulo (roi, Region Of Interest) 
     que define la zona central de la imagen convolucionada
    radius, radius:
     Esquina superior izquierda del rectángulo.
      El valor radius corresponde al número de
       filas/columnas añadidas a cada lado durante la
        expansión de la imagen (por el tamaño del filtro)
    in.cols, in.rows:
     Ancho y alto del rectángulo, que coinciden con
      el tamaño original de la imagen de entrada.
    */
    //out = conv(roi).clone();
    conv(roi).copyTo(out);
    /*
    conv(roi) selecciona la submatriz de conv definida por
     el rectángulo roi (la zona central, del tamaño original).
    .copyTo(out) copia esa submatriz en la variable out.
    El resultado es que out contiene la imagen filtrada,
     pero recortada al tamaño original de la imagen de
      entrada, eliminando los bordes extra que se añadieron
       para la convolución.
    
    EN RESUMEN
    Recorta la imagen al tamaño original:
     Después de la convolución, la imagen resultante es
      más grande (por la expansión).
     Se recorta el centro para recuperar el tamaño original
      de la imagen de entrada.
    */
    //
    CV_Assert(out.type() == in.type());
    CV_Assert(out.size() == in.size());
    return out;
}
