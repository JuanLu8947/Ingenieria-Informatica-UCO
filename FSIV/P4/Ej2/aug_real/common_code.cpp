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
    CV_Assert(ret_v.size() ==
              static_cast<size_t>(board_size.width * board_size.height));
    return ret_v;
}

bool fsiv_fast_find_chessboard_corners(const cv::Mat &img, const cv::Size &board_size,
                                       std::vector<cv::Point2f> &corner_points)
{
    CV_Assert(img.type() == CV_8UC3);
    bool was_found = false;
    // TODO
    // Hint: use cv::findChessboardCorners only with the fast check flag.
    // Remember: do not refine the corner points to get a better computational performance.
    was_found = cv::findChessboardCorners(img, board_size, corner_points, cv::CALIB_CB_FAST_CHECK);
    /*
    InputArray 	image,
    Size 	patternSize,
    OutputArray 	corners,
    int 	flags = 	
    */
    //
    return was_found;
}

void fsiv_compute_camera_pose(const std::vector<cv::Point3f> &_3dpoints,
                              const std::vector<cv::Point2f> &_2dpoints,
                              const cv::Mat &camera_matrix,
                              const cv::Mat &dist_coeffs,
                              cv::Mat &rvec,
                              cv::Mat &tvec)
{
    CV_Assert(_3dpoints.size() >= 4 && _3dpoints.size() == _2dpoints.size());
    // TODO
    // Hint: use cv::solvePnP to the pose of a calibrated camera.
    cv::solvePnP(_3dpoints, _2dpoints, camera_matrix, dist_coeffs, rvec, tvec);
    /*
    (	
        InputArray 	objectPoints,
        InputArray 	imagePoints,
        InputArray 	cameraMatrix,
        InputArray 	distCoeffs,
        OutputArray 	rvec,
        OutputArray 	tvec,
        bool 	useExtrinsicGuess = false,
        int 	flags = SOLVEPNP_ITERATIVE 
    )	
    */
    //
    CV_Assert(rvec.rows == 3 && rvec.cols == 1 && rvec.type() == CV_64FC1);
    CV_Assert(tvec.rows == 3 && tvec.cols == 1 && tvec.type() == CV_64FC1);
}

void fsiv_draw_axes(cv::Mat &img,
                    const cv::Mat &camera_matrix, const cv::Mat &dist_coeffs,
                    const cv::Mat &rvec, const cv::Mat &tvec,
                    const float size, const int line_width)
{
    // TODO
    // Hint: use cv::projectPoints to get the image coordinates of the 3D points
    // (0,0,0), (size, 0, 0), (0, size, 0) and (0, 0, -size) and draw a line for
    // each axis: blue for axis OX, green for axis OY and red for axis OZ.
    // Warning: use of cv::drawFrameAxes() is not allowed.
    
    // Definir los puntos 3D: origen y extremos de cada eje
    std::vector<cv::Point3f> axis_points;
    axis_points.push_back(cv::Point3f(0, 0, 0));        // Origen
    axis_points.push_back(cv::Point3f(size, 0, 0));     // Eje X (rojo)
    axis_points.push_back(cv::Point3f(0, size, 0));     // Eje Y (verde)
    axis_points.push_back(cv::Point3f(0, 0, -size));    // Eje Z (azul)
    
    // Proyectar los puntos 3D a coordenadas 2D de la imagen
    std::vector<cv::Point2f> projected_points;
    cv::projectPoints(axis_points, rvec, tvec, camera_matrix, dist_coeffs, projected_points);
    /*
    InputArray 	objectPoints,
    InputArray 	rvec,
    InputArray 	tvec,
    InputArray 	cameraMatrix,
    InputArray 	distCoeffs,
    OutputArray 	imagePoints,
    OutputArray 	jacobian = noArray(),
    double 	aspectRatio = 0 
    */
    
    // Dibujar líneas desde el origen a cada extremo del eje
    // Eje X - Azul (BGR: 255, 0, 0)
    cv::line(img, projected_points[0], projected_points[1], cv::Scalar(255, 0, 0), line_width);
    
    // Eje Y - Verde (BGR: 0, 255, 0)
    cv::line(img, projected_points[0], projected_points[2], cv::Scalar(0, 255, 0), line_width);
    
    // Eje Z - Rojo (BGR: 0, 0, 255)
    cv::line(img, projected_points[0], projected_points[3], cv::Scalar(0, 0, 255), line_width);
    /*
    InputOutputArray 	img,
    Point 	pt1,
    Point 	pt2,
    const Scalar & 	color,
    int 	thickness = 1,
    int 	lineType = LINE_8,
    int 	shift = 0 
    */
    //
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
    //  Hint: use fs["label"] >> var to load data items from the file.
    //  @see cv::FileStorage operators "[]" and ">>"
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

void fsiv_draw_3d_model(cv::Mat &img, const cv::Mat &M, const cv::Mat &dist_coeffs,
                        const cv::Mat &rvec, const cv::Mat &tvec,
                        const float size)
{
    CV_Assert(img.type() == CV_8UC3);

    // TODO
    // Hint: build a 3D object points vector with pair of segments end points.
    // Use cv::projectPoints to get the 2D image coordinates of 3D object points,
    // build a vector of vectors of Points, one for each segment, and use
    // cv::polylines to draw the wire frame projected model.
    // Hint: use a "reference point" to move the model around the image and update it
    //       at each call to move the 3D model around the scene.
    // Construir un modelo 3D simple: una pirámide con base cuadrada
    // Base de la pirámide en el plano Z=0
    std::vector<cv::Point3f> model_3d_points;
    
    // Punto de referencia estático para mover el modelo (puedes hacerlo dinámico después)
    static cv::Point3f reference_point(0.0f, 0.0f, 0.0f);
    
    // Definir los vértices de la pirámide
    // Base (4 vértices en Z=0)
    cv::Point3f base1 = reference_point + cv::Point3f(0, 0, 0);
    cv::Point3f base2 = reference_point + cv::Point3f(size, 0, 0);
    cv::Point3f base3 = reference_point + cv::Point3f(size, size, 0);
    cv::Point3f base4 = reference_point + cv::Point3f(0, size, 0);
    
    // Vértice superior (en Z=-size para que apunte hacia arriba en el sistema de cámara)
    cv::Point3f apex = reference_point + cv::Point3f(size/2, size/2, -size);
    
    // Construir vector con todos los puntos 3D que necesitamos proyectar
    model_3d_points.push_back(base1);
    model_3d_points.push_back(base2);
    model_3d_points.push_back(base3);
    model_3d_points.push_back(base4);
    model_3d_points.push_back(apex);
    
    // Proyectar los puntos 3D a coordenadas 2D de la imagen
    std::vector<cv::Point2f> projected_points;
    cv::projectPoints(model_3d_points, rvec, tvec, M, dist_coeffs, projected_points);
    
    // Construir las aristas del modelo (wire frame)
    // Cada elemento del vector es un segmento (arista)
    std::vector<std::vector<cv::Point>> segments;
    
    // Base de la pirámide (4 aristas)
    segments.push_back({cv::Point(projected_points[0]), cv::Point(projected_points[1])});
    segments.push_back({cv::Point(projected_points[1]), cv::Point(projected_points[2])});
    segments.push_back({cv::Point(projected_points[2]), cv::Point(projected_points[3])});
    segments.push_back({cv::Point(projected_points[3]), cv::Point(projected_points[0])});
    
    // Aristas desde la base hasta el vértice superior (4 aristas)
    segments.push_back({cv::Point(projected_points[0]), cv::Point(projected_points[4])});
    segments.push_back({cv::Point(projected_points[1]), cv::Point(projected_points[4])});
    segments.push_back({cv::Point(projected_points[2]), cv::Point(projected_points[4])});
    segments.push_back({cv::Point(projected_points[3]), cv::Point(projected_points[4])});
    
    // Dibujar el wire frame usando cv::polylines
    cv::polylines(img, segments, false, cv::Scalar(0, 255, 255), 2, cv::LINE_AA);
    /*polylines [2/2]
    InputOutputArray 	img,
    InputArrayOfArrays 	pts,
    bool 	isClosed,
    const Scalar & 	color,
    int 	thickness = 1,
    int 	lineType = LINE_8,
    int 	shift = 0 
    */
    // Opcional: actualizar reference_point para mover el modelo en futuras llamadas
    reference_point.x += 0.1f; // Ejemplo de movimiento
    //
}

void fsiv_project_image(const cv::Mat &model, cv::Mat &scene,
                        const cv::Size &board_size,
                        const std::vector<cv::Point2f> &chess_board_corners)
{
    CV_Assert(!model.empty() && model.type() == CV_8UC3);
    CV_Assert(!scene.empty() && scene.type() == CV_8UC3);
    CV_Assert(static_cast<size_t>(board_size.area()) ==
              chess_board_corners.size());

    // TODO
    // Hint: get the upper-left, upper-right, bottom-right and bottom-left
    //   chess_board_corners and map to the upper-left, upper-right, bottom-right
    //   and bottom-left model image point coordinates.
    //   Use cv::getPerspectiveTransform compute such mapping.
    // Hint: use cv::wrapPerspective to get a wrap version of the model image
    //   using the computed mapping. Use INTER_LINEAR as interpolation method
    //   and use BORDER_TRANSPARENT as a border extrapolation method
    //   to maintain the underlying image.
    //
    // Obtener las 4 esquinas del tablero de ajedrez detectado
    // Las esquinas están ordenadas: primera fila de izquierda a derecha, luego siguiente fila, etc.
    
    // Esquina superior-izquierda (primer punto detectado)
    cv::Point2f upper_left = chess_board_corners[0];
    
    // Esquina superior-derecha (último punto de la primera fila)
    cv::Point2f upper_right = chess_board_corners[board_size.width - 1];
    
    // Esquina inferior-derecha (último punto detectado)
    cv::Point2f bottom_right = chess_board_corners[board_size.width * board_size.height - 1];
    
    // Esquina inferior-izquierda (primer punto de la última fila)
    cv::Point2f bottom_left = chess_board_corners[(board_size.height - 1) * board_size.width];
    
    // Puntos de origen en la imagen modelo (las 4 esquinas de la imagen)
    std::vector<cv::Point2f> model_points;
    model_points.push_back(cv::Point2f(0, 0));                              // upper-left
    model_points.push_back(cv::Point2f(model.cols - 1, 0));                // upper-right
    model_points.push_back(cv::Point2f(model.cols - 1, model.rows - 1));  // bottom-right
    model_points.push_back(cv::Point2f(0, model.rows - 1));                // bottom-left
    
    // Puntos de destino en la escena (las 4 esquinas del tablero detectado)
    std::vector<cv::Point2f> scene_points;
    scene_points.push_back(upper_left);
    scene_points.push_back(upper_right);
    scene_points.push_back(bottom_right);
    scene_points.push_back(bottom_left);
    
    // Calcular la matriz de transformación en perspectiva (homografía)
    cv::Mat H = cv::getPerspectiveTransform(model_points, scene_points);
    /*getPerspectiveTransform [1/2]
    const Point2f 	src[],
    const Point2f 	dst[] 
    */
    
    // Proyectar la imagen modelo sobre la escena usando la homografía calculada
    // BORDER_TRANSPARENT mantiene el contenido subyacente de la imagen donde no hay píxeles del modelo
    cv::warpPerspective(model, scene, H, scene.size(), cv::INTER_LINEAR, 
                       cv::BORDER_TRANSPARENT);
    /*
    InputArray 	src,
    OutputArray 	dst,
    InputArray 	M,
    Size 	dsize,
    int 	flags = INTER_LINEAR,
    int 	borderMode = BORDER_CONSTANT,
    const Scalar & 	borderValue = Scalar() 
    */
    //
}
