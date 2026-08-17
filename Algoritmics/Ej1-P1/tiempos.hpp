#ifndef TIEMPOS_HPP
#define TIEMPOS_HPP

#include <iostream> //cin, cout
#include <vector>
#include <cmath> //log, pow
#include "auxiliares.hpp"
#include "algoritmos.hpp"
#include "ClaseTiempo.hpp"

using namespace std;

void tiemposOrdenacionSeleccion(int nMin, int nMax, int incremento, int repeticiones, vector <double> &tiemposReales, vector <double> &numeroElementos);
void calcularTiemposEstimadosPolinomico(const vector <double> &numeroElementos, const vector <double> &a, vector <double> &tiemposEstimados);
double calcularTiempoEstimadoPolinomico(const double &n, vector <double> &a);
void calcularTiemposEstimadosNlogN(const vector <double> &numeroElementos, const vector <double> &a, vector <double> &tiemposEstimados);
void tiemposOrdenacionQuicksort(int nMin, int nMax, int incremento, int repeticiones, std::vector<double>& tiemposReales, std::vector<double>& numeroElementos);
double calcularTiempoEstimadoNlogN(const double &n, const vector<double> &a);
void tiemposDeterminante(int nMin, int nMax, int incremento, vector<double>& tiemposReales, vector<double>& numeroElementos);
//new
void calcularTiemposEstimadosExponencial(const vector <double> &numeroElementos, const vector <double> &a, vector <double> &tiemposEstimados);
void calcularTiemposEstimadosFactorial(const vector <double> &numeroElementos, const vector <double> &a, vector <double> &tiemposEstimados);
//
double calcularTiempoEstimadoExponencial(const double &n, const std::vector<double> &a);
double calcularTiempoEstimadoFactorial(const double &n, const std::vector<double> &a);

#endif