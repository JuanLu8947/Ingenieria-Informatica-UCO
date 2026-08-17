#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include <iostream>
#include <vector> //para manejar la clase vector de la STL>
#include <cmath>
#include <cstdlib>
#include "ClaseTiempo.hpp"

using namespace std;


void resolverSistemaEcuaciones(vector < vector < double > > A, vector < vector < double > > B, int n, vector < vector < double > > &X);

//A es la matriz de coeficientes de NXN
//B es la matriz de terminos independientes de NX1
//n es el orden de las matrices
//X es el valor de las variables que se obtienen resolviendo el sistema
//Declaracion y reserva de matrices usando el tipo vector de la STL
// vector < vector < double > > matrizDatos;
// matrizDatos = vector< vector< double > >(filas, vector< double >(columnas)); //Matriz de N x N

void trianguloInferior(std::vector<std::vector<double>> &A, std::vector<std::vector<double>> &inversa);
double productoDiagonal(const std::vector<std::vector<double>> &matriz);

#endif
