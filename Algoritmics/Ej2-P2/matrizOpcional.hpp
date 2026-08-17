#ifndef MATRIZ_HPP
#define MATRIZ_HPP

#include <vector>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

class Matriz 
{
private:
    vector < vector < double > > _m;
    unsigned int _f, _c;

public:
    // Constructores y destructor
    Matriz(unsigned int f, unsigned int c);
    Matriz();
    ~Matriz();
    
    // Métodos de acceso
    unsigned int getFilas() const;
    unsigned int getColumnas() const;
    void setElemento(unsigned int i, unsigned int j, double x);
    double getElemento(unsigned int i, unsigned int j) const;
    
    // Métodos de inicialización
    void rellenarMatrizAleatoria();
    void rellenarMatrizUnidad();
    void rellenarMatrizSimetricaAleatoria();
    
    // Métodos de matrices especiales
    Matriz invertirMatriz();
    void lu_decomposicion(const Matriz &A, Matriz &L, Matriz &U) const;
    void forward_substitution(const Matriz &L, const std::vector<double>& b, std::vector<double>& y) const;
    void backward_substitution(const Matriz &U, const std::vector<double>& y, std::vector<double>& x) const;
    Matriz autoVectoresMatriz(Matriz &diagonal) const;
    
    // Operadores sobrecargados
    friend ostream& operator << (ostream &salida, Matriz &z);
    friend bool operator == (const Matriz &x, const Matriz &y);
    friend Matriz operator + (const Matriz &x, const Matriz &y);
    friend Matriz operator * (const Matriz &x, const Matriz &y);
    
    // Métodos de potenciación
    Matriz potencia(const unsigned int &n) const;
    //Matriz potenciaDiagonal(const unsigned int &n) const;
    Matriz potenciaDyV1(const unsigned int &n) const;
    Matriz potenciaDyV2(const unsigned int &n) const;
    //Matriz potenciaLU(unsigned int n) const;
};

#endif