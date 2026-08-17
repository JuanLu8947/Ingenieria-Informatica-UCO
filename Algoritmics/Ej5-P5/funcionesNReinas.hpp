#ifndef FUNCIONESNREINAS_H
#define FUNCIONESNREINAS_H

    #include <vector>
    using namespace std;

    void nReinasBacktracking(int n, vector< vector<int>> &soluciones);
    bool nReinasLasVegas(int n, vector<int> &solucion);
    void nReinasLasVegasTodas(const int n, vector< vector<int>> &soluciones);
    bool lugar(vector<int> &x, const int fila);
    void escribirSoluciones(vector< vector <int> >&soluciones);
    void escribirSolucion(vector<int> &solucion);
   
#endif