//! \file chroma_key.cpp
//! Replace background based on color
//! University of Cordoba
//! (c) MJMJ/2020 FJMC/2022-

#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "common_code.hpp"

const char *keys =
    "{h help usage ? |      | print this message   }"
    "{k key          |  60  | Chroma key (hue). Def. 60}"
    "{s sensitivity  |  20 | sensitivity. Def. 20}"
    "{v video        |     | the input is a videofile.}"
    "{c camera       |     | the input is a capture device index.}"
    "{@input         |<none>| input source (pathname or camera idx).}"
    "{@background    |<none>| pathname of background image.}"
    "{@output        | | pathname for the output image (it used only when the input is a image too).}";

/**
 * @brief Estado actual de la aplicación.
 *
 * Estos datos serán pasados a las callbacks que gestionan
 * los deslizadores y el ratón para poder
 * actualizar el estado de la aplicación de forma interactiva con la
 * interfaz gráfica.
 */
struct AppState
{
    cv::Mat foreg;   /*< La imagen de primer plano*/
    cv::Mat backg;   /*< La imagen de fondo*/
    cv::Mat output;  /*< el resultado de la combinación*/
    cv::Mat mask;    /*< la máscara calculada (si se quiere guardar)*/
    int hue;         /*< el valor actual del deslizador Hue*/
    int sensitivity; /*< el valor actual del deslizador sensibilidad.*/
};

/**
 * @brief Do the processing.
 *
 * @param app_state the application state.
 */
void do_the_work(AppState *app_state)
{
    app_state->output = fsiv_apply_chroma_key(app_state->foreg, app_state->backg,
                                              app_state->hue,
                                              app_state->sensitivity,
                                              &app_state->mask);
    cv::imshow("OUT", app_state->output);
    cv::imshow("CHROMA KEY MASK", app_state->mask);
}

/**
 * @brief Callback para gestionar el deslizador Hue.
 * @param v Posición actual del deslizador.
 * @param app_state_ Estado de la aplicación.
 */
void on_change_hue(int v, void *app_state_)
{
    AppState *app_state = static_cast<AppState *>(app_state_);
    app_state->hue = v;
    do_the_work(app_state);
}

/**
 * @brief Callback para gestionar el deslizador Sensibilidad.
 * @param v Posición actual del deslizador.
 * @param app_state_ Estado de la aplicación.
 */
void on_change_sensitivity(int v, void *app_state_)
{
    AppState *app_state = static_cast<AppState *>(app_state_);
    app_state->sensitivity = v;
    do_the_work(app_state);
}

/**
 * @brief Callback para gestionar el ratón en la ventana de primer plano.
 *
 * Si el usuario pulsa con el botón izquierdo se selecciona el tono (Hue) en
 * punto de la imagen donde está el ratón.
 *
 * @param event codifica el evento que provocó la llamada @see cv::EVENT_xxx
 * @param x coordenada x del puntero.
 * @param y coordenada y del puntero.
 * @param flags estado del teclado cuando se generó el evento.
 * @param app_state_ información de estado de la aplicación (opcional).
 */
void on_mouse(int event, int x, int y, int flags, void *app_state_)
{
    AppState *app_state = static_cast<AppState *>(app_state_);

    if (event == cv::EVENT_LBUTTONDOWN)
    {
        // Click con el botón izquierdo.
        cv::Mat hsv;
        cv::cvtColor(app_state->foreg, hsv, cv::COLOR_BGR2HSV);
        app_state->hue = hsv.at<cv::Vec3b>(y, x)[0]; // Valor del canal H en (x,y).
        // posicionar el deslizador para en el nuevo valor.
        cv::setTrackbarPos("KEY", "OUT", app_state->hue);
        // do_the_work(app_state);
    }
}

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    try
    {
        /// Init the parser
        cv::CommandLineParser parser(argc, argv, keys);
        parser.about("Replace background based on color.");
        if (parser.has("help"))
        {
            parser.printMessage();
            return 0;
        }

        // Get the values

        // Creamos una instancia para representar el estado de la Aplicación.
        AppState app_state;

        // Inicializar los valores de estado con los parámetros dados
        // en la línea de comandos.
        app_state.hue = parser.get<int>("k");
        app_state.sensitivity = parser.get<int>("s");
        std::string imgname = parser.get<std::string>("@input");
        std::string bckname = parser.get<std::string>("@background");
        std::string outname = parser.get<std::string>("@output");
        bool is_video = parser.has("video");
        bool is_camidx = parser.has("camera");

        if (!parser.check())
        {
            parser.printErrors();
            return EXIT_FAILURE;
        }

        app_state.backg = cv::imread(bckname, cv::IMREAD_COLOR);
        if (app_state.backg.empty())
        {
            std::cerr << "Error reading: " << bckname << std::endl;
            return EXIT_FAILURE;
        }

        // Inicializar la interfaz gráfica.
        cv::namedWindow("FOREG", cv::WINDOW_GUI_EXPANDED + cv::WINDOW_NORMAL);
        cv::namedWindow("BACKG", cv::WINDOW_GUI_EXPANDED + cv::WINDOW_NORMAL);
        cv::namedWindow("OUT", cv::WINDOW_GUI_EXPANDED + cv::WINDOW_NORMAL);
        cv::namedWindow("CHROMA KEY MASK", cv::WINDOW_GUI_EXPANDED + cv::WINDOW_NORMAL);
        // Fijamos un tamaño de la ventana para prevenir que la imagen tenga un
        // tamaño demasiado grande.
        cv::resizeWindow("FOREG", cv::Size(800, 600));
        cv::resizeWindow("BACKG", cv::Size(800, 600));
        cv::resizeWindow("OUT", cv::Size(800, 600));
        cv::resizeWindow("CHROMA KEY MASK", cv::Size(800, 600));

        // Creamos deslizadores y los añadimos a la ventana "OUT".
        // Cada deslizador tiene asociado un callback que es llamado cuando
        //   el usuario lo mueve.
        // El estado de la aplicación se da para que desde
        //   el callback podamos acceder al mismo.
        cv::createTrackbar("KEY", "OUT", nullptr, 180, on_change_hue,
                           &app_state);

        cv::createTrackbar("SENSITIVITY", "OUT", nullptr, 128,
                           on_change_sensitivity, &app_state);
        //

        // Añadimos una función para gestionar el ratón en la ventana
        //   "FOREG" de forma que si el usuario pulsa el botón izquierdo
        //   en un punto seleccionamos el valor Hue correspondiente de la imagen
        //   de primer plano como nuevo valor clave (chroma key).
        // El estado de la aplicación se da para que desde
        //   el callback podamos acceder al mismo.
        cv::setMouseCallback("FOREG", on_mouse, &app_state);
        //

        if (is_video || is_camidx)
        {
            cv::VideoCapture capt;
            if (is_video)
                capt.open(imgname);
            else
                capt.open(std::stoi(imgname));
            if (!capt.isOpened())
            {
                std::cerr << "Error: could not open the video stream."
                          << std::endl;
                return EXIT_FAILURE;
            }

            // capturamos/leemos una primera imagen para comprobar que se puede
            // y de paso saber el tamaño de las imágenes de entrada.
            capt >> app_state.foreg;

            if (app_state.foreg.empty())
            {
                // No se puede capturar o leer de la fuente de video.
                std::cerr << "Error: could not read from the video stream."
                          << std::endl;
                return EXIT_FAILURE;
            }

            if (app_state.foreg.size() != app_state.backg.size())
                // Para combinar las imágenes deben tener el mismo tamaño.
                // si ajustamos el tamaño del background ahora evitaremos que
                // fsiv_apply_chroma_key lo tenga que hacer para cada nuevo
                // frame de entrada.
                cv::resize(app_state.backg, app_state.backg, app_state.foreg.size());

            // Inicializar los deslizadores con los valores dados por la cli.
            // Esto forzará a que se actualice la GUI con la primera imagen.
            cv::setTrackbarPos("KEY", "OUT", app_state.hue);
            cv::setTrackbarPos("SENSITIVITY", "OUT", app_state.sensitivity);
            cv::imshow("BACKG", app_state.backg);

            int key = 0; // La tecla que se pulsa.
            int wait_time = 20;
            if (is_video)
                wait_time = (1000.0 / 24.0); // 24FPS.
            do
            {
                cv::imshow("FOREG", app_state.foreg); // Mostrar la imagen actual de primer plano.
                do_the_work(&app_state);              // Procesar la imagen.
                key = cv::waitKey(wait_time) & 0xff;  // 24FPS.
                capt >> app_state.foreg;              // Captura/lee una nueva imagen (si hay).

            } // Terminamos cuando no hay nada más que leer o se pulsa la tecla ESC.
            while (!(app_state.foreg.empty() || key == 27));
        }
        else
        {
            app_state.foreg = cv::imread(imgname, cv::IMREAD_COLOR);
            if (app_state.foreg.empty())
            {
                std::cerr << "Error reading: " << imgname << std::endl;
                return EXIT_FAILURE;
            }

            cv::imshow("FOREG", app_state.foreg);
            cv::imshow("BACKG", app_state.backg);

            // Inicializar los deslizadores con los valores dados por la cli.
            // Esto forzará a que se actualice la GUI con la imagen OUT.
            cv::setTrackbarPos("KEY", "OUT", app_state.hue);
            cv::setTrackbarPos("SENSITIVITY", "OUT", app_state.sensitivity);
            int key = cv::waitKey(0) & 0xff; // Esperar hasta que se pulse una tecla.
            if (key != 27 && outname != "")
                cv::imwrite(outname, app_state.output);
        }

        cv::destroyAllWindows();
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
        retCode = EXIT_FAILURE;
    }
    catch (...)
    {
        std::cerr << "Unknown exception." << std::endl;
        retCode = EXIT_FAILURE;
    }

    return retCode;
}
