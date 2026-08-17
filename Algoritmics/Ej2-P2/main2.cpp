#include "medioNivel.hpp"
#include <iostream>

using namespace std;

int main() {
    cout << "=== PRÁCTICA 2: EXPONENCIACIÓN DE MATRICES ===" << endl
         << "Comparación de 3 algoritmos de potenciación" << endl << endl;

    unsigned int orden, exponente;
    cout << "Orden de la matriz: ";
    cin >> orden;
    cout << "Exponente: ";
    cin >> exponente;

    compararAlgoritmos(orden, exponente);

    return 0;
}