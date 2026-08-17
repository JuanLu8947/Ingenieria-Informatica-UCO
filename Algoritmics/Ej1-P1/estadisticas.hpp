#ifndef ESTADISTICAS_HPP
#define ESTADISTICAS_HPP

#include <iostream>
#include <vector>
#include "ClaseTiempo.hpp"
using namespace std;

void ajustePolinomico(const vector <double> &numeroElementos, const vector <double> &tiemposReales, vector <double> &a);
double sumatorio(vector <double> &n, vector <double> &t, int expN, int expT);
double calcularCoeficienteDeterminacion(const vector <double> &tiemposReales, const vector <double> &tiemposEstimados);
void ajusteNlogN(const vector <double> &numeroElementos, const vector <double> &tiemposReales, vector <double> &a);
double calcularVarianza(const vector<double> &datos);
void calcularMatricesNlogN(const vector<double> &numeroElementos, const vector<double> &tiemposReales, vector<vector<double>> &matrizCoeficientes, vector<vector<double>> &matrizTerminosIndependientes);
void ajustePolinomicoGrado3(const std::vector<double> &numeroElementos, const std::vector<double> &tiemposReales, std::vector<double> &a);
//new
void ajusteExponencial(const vector<double> &numeroElementos, const vector<double> &tiemposReales, vector<double> &a);
void calcularMatricesExponencial(const vector<double> &numeroElementos, const vector<double> &tiemposReales, vector<vector<double>> &matrizCoeficientes, vector<vector<double>> &matrizTerminosIndependientes);
void ajusteFactorial(const vector<double> &numeroElementos, const vector<double> &tiemposReales, vector<double> &a);
void calcularMatricesFactorial(const vector<double> &numeroElementos, const vector<double> &tiemposReales, vector<vector<double>> &matrizCoeficientes, vector<vector<double>> &matrizTerminosIndependientes);

#endif