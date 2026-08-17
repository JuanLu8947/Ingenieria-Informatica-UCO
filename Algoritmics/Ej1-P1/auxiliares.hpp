#ifndef AUXILIARES_HPP
#define AUXILIARES_HPP
#include <iostream>
#include <cstdlib> //rand y srand
#include <ctime> //time
#include <vector>
#include <fstream>
#include <iomanip> //setw, setprecision
#include <algorithm> //shuffle
#include <random> //random_device, mt19937
#include "ClaseTiempo.hpp"
using namespace std;

void rellenarVector(vector<int> &v);
void calcularMatrices(const vector<double> &numeroElementos, const vector<double> &tiemposReales, int ordenMatrizSistema, vector< vector<double> > &matrizCoeficientes, vector< vector<double> > &matrizTerminosIndependientes);
void guardarDatos(const vector<double> &numeroElementos, const vector<double> &tiemposReales, const vector<double> &tiemposEstimados);
void guardarDatosAlgoritmo(const vector<double> &numeroElementos, const vector<double> &tiemposReales, const vector<double> &tiemposEstimados, const string &nombreArchivo);
void mostrarTiempoFormateado(double segundos);
void rellenarMatriz(vector<vector<double>> &matriz);
void calcularDeterminante(const std::vector<std::vector<double>>& matriz, double& determinante);
void seleccionAleatoria80_20(const vector<double> &numeroElementos, const vector<double> &tiemposReales, vector<double> &elementos80, vector<double> &tiempos80, vector<double> &elementos20, vector<double> &tiempos20);

// Factorial (devuelve n! como double)
double factorial(int n);

#endif