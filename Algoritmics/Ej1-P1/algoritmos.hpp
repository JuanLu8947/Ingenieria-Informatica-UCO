#ifndef ALGORITMOS_HPP
#define ALGORITMOS_HPP

#include <iostream> // cin, cout
#include <vector>
#include <algorithm> // swap, sort
#include "sistemaEcuaciones.hpp"
#include "ClaseTiempo.hpp"

using namespace std;

void ordenacionSeleccion(vector<int> &v);
void ordenacionQuicksort(vector<int> &v, int inicio, int fin);
int particion(vector<int> &v, int inicio, int fin);
double calcularDeterminanteIterativo(vector<vector<double>> &matriz, int n);

#endif