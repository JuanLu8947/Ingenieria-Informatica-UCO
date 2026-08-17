#include <iostream>
#include <vector>
#include <fstream>
#include "medioNivel.hpp"
#include "tiempos.hpp"

funcion_t funcion;

// Nueva función: compara los tres métodos para una matriz de 'orden' elevada a 'exponente'
void compararAlgoritmos(unsigned int orden, unsigned int exponente) {
    using std::cout; using std::endl;

    cout << "\nEjecutando comparación de métodos..." << endl;
    cout << "Orden: " << orden << ", Exponente: " << exponente << endl;

    Matriz A(orden, orden);
    A.rellenarMatrizAleatoria();

    Clock cronometro;

    // Iterativo
    cronometro.start();
    Matriz r_iter = A.potencia(exponente);
    cronometro.stop();
    double t_iter = cronometro.elapsed() / 1000.0;  // microsegundos a milisegundos

    // Divide y Vencerás (básico)
    cronometro.start();
    Matriz r_dyv1 = A.potenciaDyV1(exponente);
    cronometro.stop();
    double t_dyv1 = cronometro.elapsed() / 1000.0;  // microsegundos a milisegundos

    // Divide y Vencerás (optimizado)
    cronometro.start();
    Matriz r_dyv2 = A.potenciaDyV2(exponente);
    cronometro.stop();
    double t_dyv2 = cronometro.elapsed() / 1000.0;  // microsegundos a milisegundos

    bool coinciden = (r_iter == r_dyv1) && (r_iter == r_dyv2);

    cout << "\n¿Coinciden las potencias? " << (coinciden ? "Sí" : "No") << endl;
    cout << "Tiempos:" << endl;
    cout << "- Iterativo: " << t_iter << " ms" << endl;
    cout << "- DyV (básico): " << t_dyv1 << " ms" << endl;
    cout << "- DyV (optimizado): " << t_dyv2 << " ms" << endl;

    cout << "\n=== RESULTADOS ===" << endl;
    cout << "\nMétodo Iterativo:" << endl;
    cout << r_iter << endl;

    cout << "\nMétodo DyV (básico):" << endl;
    cout << r_dyv1 << endl;

    cout << "\nMétodo DyV (optimizado):" << endl;
    cout << r_dyv2 << endl;
}
