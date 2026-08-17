#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "common_code.hpp"

void fsiv_compute_derivate(cv::Mat const &img, cv::Mat &dx, cv::Mat &dy, int g_r,
                           int s_ap)
{
    CV_Assert(img.type() == CV_8UC1);
    // TODO
    // Remember: if g_r > 0 apply a previous Gaussian Blur operation with kernel size 2*g_r+1.
    // Hint: use Sobel operator to compute derivate.
    cv::Mat img_filtered;
    
    // Aplicar filtro gaussiano si g_r > 0 para reducir ruido
    if(g_r > 0){
        int kernel_size = 2 * g_r + 1;
        cv::GaussianBlur(img, img_filtered, cv::Size(kernel_size, kernel_size), 0);
        /*
        InputArray 	src,
        OutputArray 	dst,
        Size 	ksize,
        double 	sigmaX,
        double 	sigmaY,
        int 	borderType
        */
    }
    else{
        img_filtered = img;
    }
    
    // Calcular las derivadas parciales usando el operador Sobel
    // s_ap es la apertura del operador Sobel (tamaño del kernel)
    // CV_32F para obtener valores en punto flotante
    cv::Sobel(img_filtered, dx, CV_32F, 1, 0, s_ap);  // Derivada en X
    cv::Sobel(img_filtered, dy, CV_32F, 0, 1, s_ap);  // Derivada en Y
    /*
	InputArray 	src,
    OutputArray 	dst,
    int 	ddepth,
    int 	dx,
    int 	dy,
    int 	ksize,
    double 	scale,
    double 	delta,
    int 	borderType
    */
    //
    CV_Assert(dx.size() == img.size());
    CV_Assert(dy.size() == dx.size());
    CV_Assert(dx.type() == CV_32FC1);
    CV_Assert(dy.type() == CV_32FC1);
}

void fsiv_compute_gradient_magnitude(cv::Mat const &dx, cv::Mat const &dy,
                                     cv::Mat &gradient)
{
    CV_Assert(dx.size() == dy.size());
    CV_Assert(dx.type() == CV_32FC1);
    CV_Assert(dy.type() == CV_32FC1);

    // TODO
    // Hint: use cv::magnitude.
    cv::magnitude(dx, dy, gradient);
    /*
    InputArray x: floating-point array of x-coordinates of the vectors.
    InputArray y: 	floating-point array of y-coordinates of the vectors; it must have the same size as x.
    OutputArray magnitude: output array of the same size and type as x.
    dst(I) = sqrt( x(I)^2 + y(I)^2 )
    */
    //

    CV_Assert(gradient.size() == dx.size());
    CV_Assert(gradient.type() == CV_32FC1);
}

void fsiv_compute_gradient_histogram(cv::Mat const &gradient, int n_bins, cv::Mat &hist, float &max_gradient)
{
    // TODO
    // Hint: use cv::minMaxLoc to get the gradient range {0, max_gradient}
    // Obtener el rango del gradiente [0, max_gradient]
    double min_val, max_val;
    cv::minMaxLoc(gradient, &min_val, &max_val);
    /*
    InputArray src,
    double * minVal,
    double * maxVal,
    Point * minLoc = 0,
    Point * maxLoc = 0,
    InputArray mask = noArray() 
    */
    max_gradient = static_cast<float>(max_val);
    
    // Configurar los parámetros para calcular el histograma
    int histSize[] = {n_bins};
    float range[] = {0.0f, max_gradient};
    const float* histRange[] = {range};
    int channels[] = {0};
    
    // Calcular el histograma
    cv::calcHist(&gradient, 1, channels, cv::Mat(), hist, 1, histSize, histRange);
    /*
    const Mat * 	images,
    int 	nimages,
    const int * 	channels,
    InputArray 	mask,
    OutputArray 	hist,
    int 	dims,
    const int * 	histSize,
    const float ** 	ranges,
    bool 	unifor,
    bool 	accumulate 
    */
    //
    CV_Assert(max_gradient > 0.0);
    CV_Assert(hist.rows == n_bins);
}

int fsiv_compute_histogram_percentile(cv::Mat const &hist, float percentile)
{
    CV_Assert(percentile >= 0.0 && percentile <= 1.0);
    CV_Assert(hist.type() == CV_32FC1);
    CV_Assert(hist.cols == 1);
    int idx = -1;
    // TODO
    // Hint: use cv::sum to compute the histogram area.
    // Remember: The percentile p is the first i that sum{h[0], h[1], ..., h[i]} >= p
    // Calcular el área total del histograma
    double total_area = cv::sum(hist)[0];
    
    // Calcular el valor umbral para el percentil
    double threshold = percentile * total_area;
    
    // Acumular los valores del histograma hasta alcanzar el percentil
    double accumulated_sum = 0.0;
    
    for(int i = 0; i < hist.rows; i++){
        accumulated_sum += hist.at<float>(i, 0);
        if(accumulated_sum >= threshold){
            idx = i;
            break;
        }
    }
    //
    CV_Assert(idx >= 0 && idx < hist.rows);
    CV_Assert(idx == 0 || cv::sum(hist(cv::Range(0, idx), cv::Range::all()))[0] / cv::sum(hist)[0] < percentile);
    CV_Assert(cv::sum(hist(cv::Range(0, idx + 1), cv::Range::all()))[0] / cv::sum(hist)[0] >= percentile);
    return idx;
}

float fsiv_histogram_idx_to_value(int idx, int n_bins, float max_value,
                                  float min_value)
{
    CV_Assert(idx >= 0);
    CV_Assert(idx < n_bins);
    float value = 0.0;
    // TODO
    // Remember: Map integer range [0, n_bins) into float
    // range [min_value, max_value)
    value = min_value + (max_value - min_value) * idx / n_bins;
    //
    CV_Assert(value >= min_value);
    CV_Assert(value < max_value);
    return value;
}

cv::Mat fsiv_thinning_edge_map(cv::Mat const &edge_map)
{
    CV_Assert(edge_map.type() == CV_8UC1);
    cv::Mat thinned_edge_map;
    // TODO
    // We could use cv::ximgproc::thinning but you need to compile the separated OpenCV
    // extra module "ximgproc". We are going to implement a less effective but simpler
    // thinning algorithm based on distance transform and morphological dilation.
    //
    // Hint: Use distance L2 and kernel with size 5 in cv::distanceTransform()
    // to get the distance of a white pixel (edge) to the closest black pixel (non-edge).
    //
    // Hint: We want 8-connected thinning so use a 3x3 square structuring element in cv::dilate().
     // Calcular la transformada de distancia
    cv::Mat dist_transform;
    cv::distanceTransform(edge_map, dist_transform, cv::DIST_L2, 5);
    /*
    InputArray src,
    OutputArray dst,
    int distanceType,
    int maskSize,
    int dstType = CV_32F 
    */
    
    // Crear elemento estructurante cuadrado 3x3 para dilatación
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    /*
    int shape,
    Size ksize,
    Point anchor = Point(-1,-1) 
    */
    
    // Dilatar la transformada de distancia
    cv::Mat dist_dilated;
    cv::dilate(dist_transform, dist_dilated, kernel);
    /*
    InputArray src,
    OutputArray dst,
    InputArray kernel,
    Point anchor = Point(-1,-1),
    int iterations = 1,
    int borderType = BORDER_CONSTANT,
    const Scalar & borderValue = morphologyDefaultBorderValue()
    */
    
    // Crear máscara donde la distancia es máximo local (dist == dist_dilated)
    cv::Mat local_maxima;
    cv::compare(dist_transform, dist_dilated, local_maxima, cv::CMP_EQ);
    /*
    InputArray 	src1,
    InputArray 	src2,
    OutputArray 	dst,
    int 	cmpop 
    */

    // El mapa adelgazado es la intersección del mapa original y los máximos locales
    cv::bitwise_and(edge_map, local_maxima, thinned_edge_map);
    /*
    InputArray src1,
    InputArray src2,
    OutputArray dst,
    InputArray mask = noArray() 
    */
    //
    CV_Assert(thinned_edge_map.type() == CV_8UC1);
    CV_Assert(thinned_edge_map.size() == edge_map.size());
    return thinned_edge_map;
}

void fsiv_percentile_edge_detector(cv::Mat const &gradient, cv::Mat &edges,
                                   float th, int n_bins)
{
    CV_Assert(gradient.type() == CV_32FC1);

    // TODO
    // Remember: user other fsiv_xxx to compute histogram and percentiles.
    // Remember: map histogram range {0, ..., n_bins} to the gradient range
    // {0.0, ..., max_grad}
    // Hint: use "operator >=" to threshold the gradient magnitude image.
    // Calcular el histograma del gradiente
    cv::Mat hist;
    float max_gradient;
    fsiv_compute_gradient_histogram(gradient, n_bins, hist, max_gradient);
    
    // Calcular el índice del bin correspondiente al percentil th
    int percentile_idx = fsiv_compute_histogram_percentile(hist, th);
    
    // Mapear el índice del histograma al valor real de magnitud del gradiente
    float threshold_value = fsiv_histogram_idx_to_value(percentile_idx, n_bins, max_gradient, 0.0f);
    
    // Umbralizar el gradiente: píxeles con gradiente >= threshold_value son bordes
    edges = gradient >= threshold_value;
    //
    CV_Assert(edges.type() == CV_8UC1);
    CV_Assert(edges.size() == gradient.size());
}

void fsiv_otsu_edge_detector(cv::Mat const &gradient, cv::Mat &edges)
{
    CV_Assert(gradient.type() == CV_32FC1);

    // TODO
    // Hint: normalize input gradient into rango [0, 255] to use
    // cv::threshold properly.
    //
    // Normalizar el gradiente al rango [0, 255]
    cv::Mat gradient_normalized;
    cv::normalize(gradient, gradient_normalized, 0, 255, cv::NORM_MINMAX, CV_8UC1);
    /*
    InputArray 	src,
    InputOutputArray 	dst,
    double 	alpha = 1,
    double beta = 0,
    int norm_type = NORM_L2,
    int dtype = -1,
    InputArray mask = noArray() 
    */

    // Aplicar umbralización usando el método de Otsu
    // THRESH_BINARY: píxeles > umbral -> 255, resto -> 0
    // THRESH_OTSU: calcula automáticamente el umbral óptimo
    cv::threshold(gradient_normalized, edges, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    /*
	InputArray 	src,
    OutputArray 	dst,
    double 	thresh,
    double 	maxval,
    int 	type 
    */
    //
    CV_Assert(edges.type() == CV_8UC1);
    CV_Assert(edges.size() == gradient.size());
}

void fsiv_canny_edge_detector(cv::Mat const &dx, cv::Mat const &dy, cv::Mat &edges,
                              float th1, float th2, int n_bins)
{
    CV_Assert(dx.size() == dy.size());
    CV_Assert(th1 < th2);

    // TODO
    // Hint: convert the intput derivatives to CV_16C1 to be used with canny.
    // Remember: th1 and th2 are given as percentiles so you must transform to
    //           gradient range to be used in canny method.
    // Remember: we compute gradients with L2_NORM so we must indicate this in
    //           the canny method too.
    // Convertir las derivadas a CV_16SC1 para usar con Canny
    cv::Mat dx_16s, dy_16s;
    dx.convertTo(dx_16s, CV_16SC1);
    dy.convertTo(dy_16s, CV_16SC1);
    
    // Calcular la magnitud del gradiente
    cv::Mat gradient;
    fsiv_compute_gradient_magnitude(dx, dy, gradient);
    
    // Calcular el histograma del gradiente
    cv::Mat hist;
    float max_gradient;
    fsiv_compute_gradient_histogram(gradient, n_bins, hist, max_gradient);
    
    // Calcular los índices de percentiles para th1 y th2
    int percentile_idx1 = fsiv_compute_histogram_percentile(hist, th1);
    int percentile_idx2 = fsiv_compute_histogram_percentile(hist, th2);
    
    // Mapear los índices a valores reales de magnitud del gradiente
    float threshold1 = fsiv_histogram_idx_to_value(percentile_idx1, n_bins, max_gradient, 0.0f);
    float threshold2 = fsiv_histogram_idx_to_value(percentile_idx2, n_bins, max_gradient, 0.0f);
    
    // Aplicar el detector de Canny con L2 gradient
    // L2gradient=true indica que usamos norma L2 (sqrt(dx² + dy²))
    cv::Canny(dx_16s, dy_16s, edges, threshold1, threshold2, true);
    /*[2/2]
    InputArray 	dx,
    InputArray 	dy,
    OutputArray 	edges,
    double 	threshold1,
    double 	threshold2,
    bool 	L2gradient 
    */
    //
    CV_Assert(edges.type() == CV_8UC1);
    CV_Assert(edges.size() == dx.size());
}

void fsiv_compute_ground_truth_image(cv::Mat const &consensus_img,
                                     float min_consensus, cv::Mat &gt)
{
    //! TODO
    // Hint: use cv::normalize to normalize consensus_img into range (0, 100)
    // Hint: use "operator >=" to threshold the consensus image.
    // Normalizar la imagen de consenso al rango [0, 100]
    cv::Mat consensus_normalized;
    cv::normalize(consensus_img, consensus_normalized, 0, 100, cv::NORM_MINMAX, CV_32FC1);
    
    // Umbralizar usando el consenso mínimo
    // Píxeles con consenso >= min_consensus son bordes (255)
    gt = consensus_normalized >= min_consensus;
    //
    CV_Assert(consensus_img.size() == gt.size());
    CV_Assert(gt.type() == CV_8UC1);
}

void fsiv_compute_edge_detector_confusion_matrix(cv::Mat const &gt, cv::Mat const &pred, cv::Mat &cm)
{
    CV_Assert(gt.type() == CV_8UC1);
    CV_Assert(pred.type() == CV_8UC1);
    CV_Assert(gt.size() == pred.size());

    // TODO
    // Remember: a edge detector confusion matrix is a 2x2 matrix where the
    // rows are ground truth {Positive: "is edge", Negative: "is not edge"} and
    // the columns are the predictions labels {"is edge", "is not edge"}
    // A pixel value means edge if it is <> 0, else is a "not edge" pixel.
    // Inicializar la matriz de confusión 2x2 con ceros
    cm = cv::Mat::zeros(2, 2, CV_32FC1);

    // Recorrer todos los píxeles
    for(int i = 0; i < gt.rows; i++){
        for(int j = 0; j < gt.cols; j++){
            // Determinar si el píxel es borde en GT y en predicción
            bool is_edge_gt = (gt.at<uchar>(i, j) != 0);
            /*bool is_edge_gt = false;
            if(gt.at<uchar>(i, j) != 0){
                // El píxel en la imagen GT es un borde
                is_edge_gt = true;
            }*/
            /*
            ·gt es una imagen (matriz) de tipo cv::Mat que representa el ground truth (la verdad de si un píxel es borde o no).
            ·gt.at<uchar>(i, j) accede al valor del píxel en la fila i y columna j, interpretándolo como un uchar (entero sin signo de 8 bits, valores de 0 a 255).
            ·Si ese valor es distinto de 0, entonces el píxel se considera un borde (edge).4
            ·Si es igual a 0, se considera que no es borde.
            */
            bool is_edge_pred = (pred.at<uchar>(i, j) != 0);
            
            // Construir la matriz de confusión
            // Filas: GT (0=Positivo/es borde, 1=Negativo/no es borde)
            // Columnas: Predicción (0=es borde, 1=no es borde)
            
            /*    
            La matriz tiene esta estructura:
                             Predicción
                           edge  | not edge
                         --------|----------
            GT   edge    |  TP   |   FN
                not edge |  FP   |   TN
            */
    
            /*El método at permite acceder a los píxeles de una imagen (matriz) de OpenCV especificando el tipo de dato y las coordenadas.
            mat.at<tipo>(fila, columna)
            */

            if(is_edge_gt && is_edge_pred){
                // Verdadero Positivo (TP): GT dice "borde" y predicción dice "borde"
                cm.at<float>(0, 0)++; //incrementa en uno el valor que está en la posición (0,0)
            }
            else if(is_edge_gt && !is_edge_pred){
                // Falso Negativo (FN): GT dice "borde" pero predicción dice "no borde"
                cm.at<float>(0, 1)++;
            }
            else if(!is_edge_gt && is_edge_pred){
                // Falso Positivo (FP): GT dice "no borde" pero predicción dice "borde"
                cm.at<float>(1, 0)++;
            }
            else{
                // Verdadero Negativo (TN): GT dice "no borde" y predicción dice "no borde"
                cm.at<float>(1, 1)++;
            }
        }
    }
    //
    CV_Assert(cm.type() == CV_32FC1);
    CV_Assert(cv::abs(cv::sum(cm)[0] - (gt.rows * gt.cols)) < 1.0e-6);
}

float fsiv_compute_sensitivity(cv::Mat const &cm)
{
    CV_Assert(cm.type() == CV_32FC1);
    CV_Assert(cm.size() == cv::Size(2, 2));
    float sensitivity = 0.0;
    // TODO
    // Hint: see https://en.wikipedia.org/wiki/Confusion_matrix
    // Sensitivity (Recall) = TP / (TP + FN)
    // Es decir, de todos los píxeles que realmente son borde (TP + FN),
    // cuántos fueron correctamente detectados (TP)
    float TP = cm.at<float>(0, 0);  // Verdaderos Positivos
    float FN = cm.at<float>(0, 1);  // Falsos Negativos
    /*
    La matriz de confusión cm es de 2x2 y se usa para evaluar
     el rendimiento de un detector de bordes comparando la
      imagen de bordes predicha con la imagen de bordes real
       (ground truth). Cada posición de la matriz representa
        una combinación de predicción y realidad
         (borde/no borde).

    En resumen: estas líneas extraen los valores necesarios
     para calcular métricas como sensibilidad (recall) y
      precisión del detector de bordes.

    El método .at<float>(0, 0) accede al elemento que está
     en la fila 0 y columna 0 de la matriz cm,
    */

    float total_positives = TP + FN;
    
    if(total_positives > 0.0){
        sensitivity = TP / total_positives;
    }
    else{
        sensitivity = 0.0;
    }
    //
    return sensitivity;
}

float fsiv_compute_precision(cv::Mat const &cm)
{
    CV_Assert(cm.type() == CV_32FC1);
    CV_Assert(cm.size() == cv::Size(2, 2));
    float precision = 0.0;
    // TODO
    // Hint: see https://en.wikipedia.org/wiki/Confusion_matrix
    // Precision = TP / (TP + FP)
    // Es decir, de todos los píxeles que el detector clasificó como borde (TP + FP),
    // cuántos realmente son borde (TP)
    float TP = cm.at<float>(0, 0);  // Verdaderos Positivos
    float FP = cm.at<float>(1, 0);  // Falsos Positivos
    
    float total_predicted_positives = TP + FP;
    
    if(total_predicted_positives > 0.0){
        precision = TP / total_predicted_positives;
    }
    else{
        precision = 0.0;
    }
    //
    return precision;
}

float fsiv_compute_F1_score(cv::Mat const &cm)
{
    CV_Assert(cm.type() == CV_32FC1);
    CV_Assert(cm.size() == cv::Size(2, 2));
    float F1 = 0.0;
    // TODO
    // Hint: see https://en.wikipedia.org/wiki/Confusion_matrix
    // F1 Score = 2 * (Precision * Sensitivity) / (Precision + Sensitivity)
    // Es la media armónica entre precisión y sensibilidad
    
    float precision = fsiv_compute_precision(cm);
    float sensitivity = fsiv_compute_sensitivity(cm);
    
    float sum = precision + sensitivity;
    
    if(sum > 0.0){
        F1 = 2.0 * (precision * sensitivity) / sum;
    }
    else{
        F1 = 0.0;
    }
    //
    return F1;
}
