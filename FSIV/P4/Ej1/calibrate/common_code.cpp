/**
 * @file common_code.cpp
 * @author Francisco José Madrid Cuevas (fjmadrid@uco.es)
 * @brief Utility functions to calibrate/undistort a camera.
 * @version 0.1
 * @date 2024-09-24
 *
 * @copyright Copyright (c) 2024-
 *
 */
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include "common_code.hpp"

std::vector<cv::Point3f>
fsiv_generate_3d_calibration_points(const cv::Size &board_size,
                                    float square_size)
{
    std::vector<cv::Point3f> ret_v;
    // TODO
    // Remember: the first inner point has (1,1) in board coordinates.
    //+Nota usando webcam
    //interpretacin datos
    //variacion de parametros da mas igual
    for (int i = 0; i < board_size.height; ++i) {
        for (int j = 0; j < board_size.width; ++j) {
            ret_v.push_back(cv::Point3f((j+1)*square_size, (i+1)*square_size, 0));
        }
    }
    /*
    cv::Point3f(x,y,z): crea un punto 3D con coordenadas de tipo float (x, y, z).
    (j+1)*square_size: calcula la coordenada X del punto. j es el índice de columna (0..width-1); se suma 1 porque en este ejercicio se decidió que el primer punto interior del tablero tiene coordenadas (1,1) en “coordenadas del tablero”.
    (i+1)*square_size: calcula la coordenada Y del punto. i es el índice de fila (0..height-1); lo mismo que para X.
    0: coordenada Z = 0, porque todos los puntos del tablero se consideran sobre el mismo plano Z=0.
    ret_v.push_back(...): añade ese punto 3D al vector de puntos 3D que representa las esquinas internas del tablero.
    
    Por qué se usa (j+1) y (i+1) en vez de j e i:
     el enunciado indica que “el primer inner point tiene (1,1) en coordenadas del tablero”. Usando (j+1, i+1) el primer punto (i=0,j=0) tendrá coordenadas (1square_size, 1square_size).
     Alternativa habitual: usar (jsquare_size, isquare_size) y entonces el origen sería (0,0). Ambas son válidas; lo importante es ser consistente entre todas las vistas y con los puntos 2D detectados. Cambiar el desplazamiento solo traslada el sistema de referencia del objeto (afecta rvec/tvec), pero no rompe la calibración siempre que sea consistente.

    Significado de square_size:
     Es la longitud real de un lado del cuadrado (en metros, centímetros, o la unidad que elijas). Afecta la escala de los vectores de traslación (tvec). Si usas metros, tvec estará en metros; con centímetros, en cm. Los parámetros intrínsecos (fx,fy,cx,cy) dependen de la relación píxeles/unidad física, pero calibrar con distintas unidades solo cambia la escala de tvec, no la validez si todo es consistente.
    
    Orden y correspondencia:
     El bucle for rellena los puntos en orden fila por fila (i = filas, j = columnas). Este orden debe coincidir con el orden en que OpenCV devuelve las esquinas en findChessboardCorners (por defecto, la misma convención fila->columna), para que cada objectPoint 3D corresponda con el imagePoint 2D correcto al llamar a calibrateCamera.
    
    Consideraciones sobre tipos:
     Point3f usa float. calibrateCamera trabaja con entradas convertibles (internamente puede usar double). No suele ser problema, pero si quieres precisión extrema podrías usar Point3d (double) y ajustar tipos.
    
    Resumen práctico:
     Crea el patrón 3D en el plano Z=0.
     Usa la unidad real en square_size.
     Mantén el mismo orden y offset entre objectPoints 3D e imagePoints 2D.
     Puedes cambiar (j+1) a (j) si prefieres origen en (0,0); sólo sé consistente.
    */
    //
    CV_Assert(ret_v.size() == static_cast<size_t>(board_size.width * board_size.height));
    return ret_v;
}

bool fsiv_find_chessboard_corners(const cv::Mat &img, const cv::Size &board_size,
                                  std::vector<cv::Point2f> &corner_points,
                                  int win_r,
                                  int zz_r,
                                  const cv::TermCriteria &tcr)
{
    CV_Assert(img.type() == CV_8UC3);
    bool was_found = false;
    // TODO
    // Hint: use cv::findChessboardCorners and cv::cornerSubPix.
    // Remember: cornerSubPix requires a grayscale image.
    // Convertir la imagen a escala de grises
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    
    // Buscar las esquinas del tablero de ajedrez
    was_found = cv::findChessboardCorners(gray, board_size, corner_points);
    
    // Si se encontraron las esquinas, refinarlas con cornerSubPix
    if(was_found) {
        cv::cornerSubPix(gray, corner_points, 
                        cv::Size(win_r, win_r),    // Tamaño de la ventana de búsqueda
                        cv::Size(zz_r, zz_r),      // Zona cero (área no considerada)
                        tcr);                       // Criterios de terminación
    }
    /*
    InputArray 	image,
    InputOutputArray 	corners,
    Size 	winSize,
    Size 	zeroZone,
    TermCriteria 	criteria 	
    */
    //
    CV_Assert(!was_found || corner_points.size() == (board_size.width * board_size.height));
    return was_found;
}

float fsiv_calibrate_camera(const std::vector<std::vector<cv::Point2f>> &_2d_points,
                            const std::vector<std::vector<cv::Point3f>> &_3d_points,
                            const cv::Size &camera_size,
                            cv::Mat &camera_matrix,
                            cv::Mat &dist_coeffs,
                            std::vector<cv::Mat> *rvecs,
                            std::vector<cv::Mat> *tvecs)
{
    CV_Assert(_3d_points.size() >= 2 && _3d_points.size() == _2d_points.size());
    float error = 0.0;
    // TODO
    // Hint: use cv::calibrateCamera.
    // Remember: if rvecs or tvecs are not nullptr, save the rotation and translation vectors.
    if (rvecs != nullptr && tvecs != nullptr) {
        error = static_cast<float>(cv::calibrateCamera(_3d_points, _2d_points, camera_size, camera_matrix, dist_coeffs, *rvecs, *tvecs)); //casting necesario
    } else {
        std::vector<cv::Mat> temp_rvecs, temp_tvecs;
        error = static_cast<float>(cv::calibrateCamera(_3d_points, _2d_points, camera_size, camera_matrix, dist_coeffs, temp_rvecs, temp_tvecs));
    }
    /*
    double cv::calibrateCamera	[2/2]
    (	InputArrayOfArrays 	objectPoints,
        InputArrayOfArrays 	imagePoints,
        Size 	imageSize,
        InputOutputArray 	cameraMatrix,
        InputOutputArray 	distCoeffs,
        OutputArrayOfArrays 	rvecs,
        OutputArrayOfArrays 	tvecs,
        int 	flags = 0,
        TermCriteria 	criteria = TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, 30, DBL_EPSILON) 
    )	
    double cv::calibrateCamera	[1/2]
    (	InputArrayOfArrays 	objectPoints,
        InputArrayOfArrays 	imagePoints,
        Size 	imageSize,
        InputOutputArray 	cameraMatrix,
        InputOutputArray 	distCoeffs,
        OutputArrayOfArrays 	rvecs,
        OutputArrayOfArrays 	tvecs,
        OutputArray 	stdDeviationsIntrinsics,
        OutputArray 	stdDeviationsExtrinsics,
        OutputArray 	perViewErrors,
        int 	flags = 0,
        TermCriteria 	criteria = TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, 30, DBL_EPSILON) 
    )	
    */
    //
    CV_Assert(camera_matrix.rows == camera_matrix.cols &&
              camera_matrix.rows == 3 &&
              camera_matrix.type() == CV_64FC1);
    CV_Assert((dist_coeffs.rows * dist_coeffs.cols) == 5 &&
              dist_coeffs.type() == CV_64FC1);
    CV_Assert(rvecs == nullptr || rvecs->size() == _2d_points.size());
    CV_Assert(tvecs == nullptr || tvecs->size() == _2d_points.size());
    return error;
}

void fsiv_save_calibration_parameters(cv::FileStorage &fs,
                                      const cv::Size &camera_size,
                                      float error,
                                      const cv::Mat &camera_matrix,
                                      const cv::Mat &dist_coeffs,
                                      const cv::Mat &rvec,
                                      const cv::Mat &tvec)
{
    CV_Assert(fs.isOpened());
    CV_Assert(camera_matrix.type() == CV_64FC1 && camera_matrix.rows == 3 && camera_matrix.cols == 3);
    CV_Assert(dist_coeffs.type() == CV_64FC1 && dist_coeffs.rows == 1 && dist_coeffs.cols == 5);
    CV_Assert(rvec.type() == CV_64FC1 && rvec.rows == 3 && rvec.cols == 1);
    CV_Assert(tvec.type() == CV_64FC1 && tvec.rows == 3 && tvec.cols == 1);
    // TODO
    // Hint: use cv::FileStorage "<<" operator to save the data.
    // Remember: the labels are: image-width, image-height, error, camera-matrix, distortion-coefficients, rvec, tvec.
    fs << "image-width" << camera_size.width
       << "image-height" << camera_size.height
       << "error" << error
       << "camera-matrix" << camera_matrix
       << "distortion-coefficients" << dist_coeffs
       << "rvec" << rvec
       << "tvec" << tvec;
    //
    CV_Assert(fs.isOpened());
    return;
}

void fsiv_load_calibration_parameters(cv::FileStorage &fs,
                                      cv::Size &camera_size,
                                      float &error,
                                      cv::Mat &camera_matrix,
                                      cv::Mat &dist_coeffs,
                                      cv::Mat &rvec,
                                      cv::Mat &tvec)
{
    CV_Assert(fs.isOpened());
    // TODO
    // Hint: use cv::FileStorage ">>" operator to load the data.
    // Remember: the labels are: image-width, image-height, error, camera-matrix, distortion-coefficients, rvec, tvec.
    fs["image-width"] >> camera_size.width;
    fs["image-height"] >> camera_size.height;
    fs["error"] >> error;
    fs["camera-matrix"] >> camera_matrix;
    fs["distortion-coefficients"] >> dist_coeffs;
    fs["rvec"] >> rvec;
    fs["tvec"] >> tvec;
    //
    CV_Assert(fs.isOpened());
    CV_Assert(camera_matrix.type() == CV_64FC1 && camera_matrix.rows == 3 && camera_matrix.cols == 3);
    CV_Assert(dist_coeffs.type() == CV_64FC1 && dist_coeffs.rows == 1 && dist_coeffs.cols == 5);
    CV_Assert(rvec.type() == CV_64FC1 && rvec.rows == 3 && rvec.cols == 1);
    CV_Assert(tvec.type() == CV_64FC1 && tvec.rows == 3 && tvec.cols == 1);
    return;
}

void fsiv_undistort_image(const cv::Mat &input, cv::Mat &output,
                          const cv::Mat &camera_matrix,
                          const cv::Mat &dist_coeffs)
{
    // TODO
    // Hint: use cv::undistort.
    cv::undistort(input, output, camera_matrix, dist_coeffs);
    /*InputArray 	src,
    OutputArray 	dst,
    InputArray 	cameraMatrix,
    InputArray 	distCoeffs,
    InputArray 	newCameraMatrix  = noArray()
    */
    //
}

void fsiv_undistort_video_stream(cv::VideoCapture &input_stream,
                                 cv::VideoWriter &output_stream,
                                 const cv::Mat &camera_matrix,
                                 const cv::Mat &dist_coeffs,
                                 const int interp,
                                 const char *input_wname,
                                 const char *output_wname,
                                 double fps)
{
    CV_Assert(input_stream.isOpened());
    CV_Assert(output_stream.isOpened());
    // TODO
    // Hint: to speed up, first compute the transformation maps
    //  with the first video frame using cv::initUndistortRectifyMap
    //  and then, for the rest of video frames, only remap (cv::remap)
    //  the input frame using the computed maps.
    // Remember: if input_wname or output_wname are not nullptr, show the frames.
    cv::Mat frame, map1, map2, undistorted;
    input_stream >> frame;
    cv::initUndistortRectifyMap(camera_matrix, dist_coeffs, cv::Mat(), camera_matrix, frame.size(), CV_32FC1, map1, map2);
    /*
    InputArray 	cameraMatrix,
    InputArray 	distCoeffs,
    InputArray 	R,
    InputArray 	newCameraMatrix,
    Size 	size,
    int 	m1type,
    OutputArray 	map1,
    OutputArray 	map2 		
    */
    do {
        input_stream >> frame;
        if (frame.empty()) 
            break;
        cv::remap(frame, undistorted, map1, map2, interp);
        /*
        InputArray 	src,
        OutputArray 	dst,
        InputArray 	map1,
        InputArray 	map2,
        int 	interpolation,
        int 	borderMode = BORDER_CONSTANT,
        const Scalar & 	borderValue = Scalar()
        */
        output_stream.write(undistorted);
        /*
        output_stream es un objeto de tipo cv::VideoWriter de OpenCV, que permite crear y escribir vídeos.
        .write(undistorted) toma una imagen (matriz cv::Mat) llamada undistorted y la añade como un nuevo frame al vídeo que está creando o editando.
        undistorted es el resultado de aplicar la corrección de distorsión a un frame original de vídeo
        
        cada vez que se ejecuta esta línea, se añade un nuevo frame corregido al archivo de vídeo de salida. Así, el vídeo final contendrá todas las imágenes procesadas, una tras otra, formando la secuencia de vídeo corregida.
        */
        if (input_wname) 
            cv::imshow(input_wname, frame);
        /* displays an image in the specified window.
        const String & 	winname,
        InputArray 	mat 
        */
        if (output_wname) 
            cv::imshow(output_wname, undistorted);
        if (input_wname || output_wname) 
            cv::waitKey(1);
        /*int delay	
        waits for a key event infinitely
        */
    } while (!frame.empty());
    //
    CV_Assert(input_stream.isOpened());
    CV_Assert(output_stream.isOpened());
}
