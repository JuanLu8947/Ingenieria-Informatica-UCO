#ifndef FUNCFIBONACCI_HPP
#define FUNCFIBONACCI_HPP

    #include <vector>
    
    void tiemposHanoi(int nMin, int nMax, int inc,
std::vector<double> &numeroElementos, std::vector<double> &tiemposReales);
    double calcularTiempoEstimadoExponencial(const double &n, const std::vector<double> &a);
    double calcularTiempoEstimadoFactorial(const double &n, const std::vector<double> &a);
    void torresHanoi(int n, int i, int j);
    
#endif