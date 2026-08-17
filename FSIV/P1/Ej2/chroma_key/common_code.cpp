#include <iostream>
#include "common_code.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

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
fsiv_combine_images(const cv::Mat &img1, const cv::Mat &img2,
                    const cv::Mat &mask)
{
    CV_Assert(img2.size() == img1.size());
    CV_Assert(img2.type() == img1.type());
    CV_Assert(mask.size() == img1.size());
    cv::Mat output;
    //! TODO
    //  HINT: you can use cv::Mat::copyTo().
    // Reemplazar el TODO con:
    //output = img1.clone();
    /*
    Crea una copia completa de img1 y la asigna a output
     clone() hace una copia profunda (no solo una referencia)
    */
    //img2.copyTo(output, ~mask);
    /*
    ~mask es la inversión bit a bit de la máscara
    Si mask tiene valor 255 → ~mask tiene valor 0
    y viceversa.
    copyTo(output, ~mask):
    ·Copia píxeles de img2 a output solo donde ~mask ≠ 0
    ·Es decir, copia img2 donde la máscara original era 0 (negro)

    Esta función combina dos imágenes usando una máscara binaria.
    ·Donde la máscara sea 255 (blanco) → usar píxeles de img1
    ·Donde la máscara sea 0 (negro) → usar píxeles de img2
    */ //otra opcion
    img2.copyTo(output); //1
    img1.copyTo(output, mask); //2
    /*
    1:
    Copia completamente img2 a output (sin máscara)
    Ahora output contiene exactamente los mismos píxeles
     que img2
    Es la "base" sobre la que vamos a trabajar

    2:
    Copia píxeles de img1 a output solo donde mask ≠ 0
    Es decir, copia img1 donde mask = 255 (blanco)
    Sobrescribe la base (img2) en esas posiciones

    Resultado final:
     Donde mask = 255 (blanco) → píxeles de img1 ✓
     Donde mask = 0 (negro) → píxeles de img2 ✓
    */
    //
    CV_Assert(output.size() == img1.size());
    CV_Assert(output.type() == img1.type());
    return output;
}

cv::Mat
fsiv_compute_chroma_key_mask(const cv::Mat &bgr_img,
                             int chroma_key,
                             int sensitivity)
{
    CV_Assert(bgr_img.type() == CV_8UC3);
    cv::Mat mask;
    // TODO
    // Hint: use fsiv_xxx defined functions.
    // Hint: use cv::inRange to get the mask.
    // Remember: the use full range for S and V channels ([0,255]).
    /*cv::Mat hsv_img = fsiv_convert_bgr_to_hsv(bgr_img);
    /*chroma key range =  [h +- s, 0-255, 0-255]
    donde ‘h’ es el valor de chroma key 
    y ‘s’ es la sensibilidad medida como número de tonos.
    Se asume h-s>=0 y que h+s<max{H}.*/
    /*int lower_h = chroma_key - sensitivity;
    int upper_h = chroma_key + sensitivity;
    cv::Scalar lower_b, upper_b; // HSV range.
    */
    /*
    if (lower_h < 0) {
        // Rango 1: [0, upper_h]
        lower_b = cv::Scalar(0, 0, 0); //si se sale por abajo se le asigna 0
        upper_b = cv::Scalar(upper_h, 255, 255); 
                //cv::Scalar(   H,     S,   V)
        cv::Mat mask1, mask2;
        cv::inRange(hsv_img, lower_b, upper_b, mask1);

        // Rango 2: [180 + lower_h, 180]
        lower_b = cv::Scalar(180 + lower_h, 0, 0);
        upper_b = cv::Scalar(180, 255, 255);
        cv::inRange(hsv_img, lower_b, upper_b, mask2);

        mask = mask1 | mask2;
    } 
    else if (upper_h > 180) {
        // Rango 1: [lower_h, 180]
        lower_b = cv::Scalar(lower_h, 0, 0);
        upper_b = cv::Scalar(180, 255, 255); //si se sale por arriba se le asigna 180 y 255 respectivamente
        cv::Mat mask1, mask2;
        cv::inRange(hsv_img, lower_b, upper_b, mask1);

        // Rango 2: [0, upper_h - 180]
        lower_b = cv::Scalar(0, 0, 0);
        upper_b = cv::Scalar(upper_h - 180, 255, 255);
        cv::inRange(hsv_img, lower_b, upper_b, mask2);

        mask = mask1 | mask2;
    } 
    else { // Rango normal (sin problemas circulares)
        lower_b = cv::Scalar(lower_h, 0, 0);
        upper_b = cv::Scalar(upper_h, 255, 255);
        cv::inRange(hsv_img, lower_b, upper_b, mask);
    }
    /*
    Crear una máscara que detecte píxeles de un color específico (chroma key) en el espacio HSV:
    ·H (Hue/Tono): (0-179) [chroma_key - sensitivity, chroma_key + sensitivity]
    ·S (Saturación): [0, 255] (rango completo)
    ·V (Valor/Brillo): [0, 255] (rango completo)

    ·std::max(0, ...) y std::min(179, ...) evitan valores fuera del rango válido de H (0-179)
    ·cv::inRange() devuelve 255 donde el píxel está dentro del rango, 0 donde no
    
    Operación OR (|)
     Combina las dos máscaras
     Si cualquiera de las dos tiene 255 → resultado = 255
      si ambas tienen 0 → resultado = 0
    */
    //Versión + corta
    cv::Scalar lower = cv::Scalar(chroma_key - sensitivity, 0, 0); //1
    cv::Scalar upper = cv::Scalar(chroma_key + sensitivity, 255, 255); //2
    cv::Mat hsv_img = fsiv_convert_bgr_to_hsv(bgr_img);
    cv::inRange(hsv_img, lower, upper, mask); //3
    /*
    1:
    Crea el límite inferior del rango HSV
    H: chroma_key - sensitivity (ej: si chroma_key=60, sensitivity=10 → H=50)
    S: 0 (saturación mínima - acepta cualquier saturación)
    V: 0 (brillo mínimo - acepta cualquier brillo)
    2:
    Crea el límite superior del rango HSV
    H: chroma_key + sensitivity (ej: si chroma_key=60, sensibilidad=10 → H=70)
    S: 255 (saturación máxima - acepta cualquier saturación)
    V: 255 (brillo máximo - acepta cualquier brillo)
    3: Crear máscara
    cv::inRange() compara cada píxel de hsv_img con el rango [lower, upper]
    Si el píxel está DENTRO del rango → mask = 255 (blanco)
    Si el píxel está FUERA del rango → mask = 0 (negro)
    */
    //
    return mask;
}

cv::Mat
fsiv_apply_chroma_key(const cv::Mat &foreg, const cv::Mat &backg, int hue,
                      int sensitivity, cv::Mat *mask_out)
{
    cv::Mat out;
    cv::Scalar lower_b, upper_b; // HSV range.

    // TODO
    // Hint: use fsiv_xxx defined functions.
    // Hint: use cv::resize if backg img has different size than foreg.
    // Remember: if mask_out is not null, the computed mask must be assigned to *mask_out.
    // 1. Calcular máscara
    /*cv::Mat mask = fsiv_compute_chroma_key_mask(foreg, hue, sensitivity);
    /*
    Llama a la función que ya implementamos para detectar el color clave
     foreg: imagen de primer plano (donde está la persona/objeto)
     hue: el tono del color a eliminar (ej: verde=60, azul=120)
     sensitivity: tolerancia del color (±sensitivity tonos)
    Resultado: máscara donde 255=color clave detectado, 0=resto
    */

    // 2. Redimensionar fondo si es necesario
    /*cv::Mat resized_backg;
    if (backg.size() != foreg.size()) {
        cv::resize(backg, resized_backg, foreg.size());
    } else {
        resized_backg = backg;
    }*/
    /*
    Problema: las imágenes pueden tener tamaños diferentes
    Solución:
    Si son diferentes → redimensionar fondo al tamaño del primer plano
    Si son iguales → usar el fondo tal como está
    cv::resize(origen, destino, nuevo_tamaño) cambia el tamaño de la imagen
    */
    
    // 3. Combinar imágenes
    /*out = fsiv_combine_images(resized_backg, foreg, mask);
    //resized_backg es img1 (donde mask=255)
    //foreg es img2 (donde mask=0)
    //mask es la máscara binaria
    
    // 4. Devolver máscara si se solicita
    if (mask_out != nullptr) {
        *mask_out = mask;
    }*/
    /*
    mask_out es un parámetro opcional (puede ser nullptr)
    Si el usuario quiere obtener la máscara calculada, se la asignamos
    *mask_out = mask desreferencia el puntero y asigna el valor
    */
    //otra versión
    //1. Manejo de diferentes tamaños de imagen
    if(foreg.size() != backg.size()){
        cv::resize(backg, out, foreg.size() /*, cv::INTER_LINEAR (por defecto) = bilineal*/);
    }
    else
        out = backg;
    //2. Calcular máscara de chroma key
    cv::Mat mask = fsiv_compute_chroma_key_mask(foreg, hue, sensitivity);
    //3. Devolver máscara si se solicita
    if (mask_out != nullptr)
        *mask_out = mask;
    //4. Combinar imágenes
    out = fsiv_combine_images(out, foreg, mask); //los param se ponen en ese orden debido a lo realizado anteriormente con la máscara (255→img1, 0→img2)
    /*
    1:
    Si son diferentes tamaños: redimensiona backg al tamaño de foreg y lo guarda en out
    Si son iguales: simplemente asigna backg a out
     Su importancia se debe a que:
      Las imágenes deben tener el mismo tamaño para poder combinarlas
      cv::resize() cambia el tamaño manteniendo las proporciones
    4:
    out (fondo redimensionado) → img1 (donde mask=255)
    foreg (primer plano) → img2 (donde mask=0)
    mask → máscara binaria
    Recordando cómo funciona fsiv_combine_images:
    
    Donde mask=255 → usar img1 (fondo)
    Donde mask=0 → usar img2 (primer plano)
    Lógica del chroma key:
    mask=255: píxeles donde se detectó color clave → usar fondo
    mask=0: píxeles normales del primer plano → usar primer plano
    */
    //
    CV_Assert(out.size() == foreg.size());
    CV_Assert(out.type() == foreg.type());
    return out;
}
