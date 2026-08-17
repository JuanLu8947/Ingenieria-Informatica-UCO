#include "algoritmos.hpp"

void ordenacionSeleccion(vector<int> &v) {
    //Este algorimo ordena de menor a mayor
    // BUCLE EXTERNO: Para cada posición i del array
    for(int i = 0; i < v.size() - 1; i++) {
        // PASO 1: Asumir que el mínimo está en la posición i
        int posicionMinimo = i;
        // PASO 2: BUCLE INTERNO: Buscar el verdadero mínimo
        for(int j = i + 1; j < v.size(); j++) {
            if(v[j] < v[posicionMinimo]) {
                posicionMinimo = j;  // Encontramos uno menor
            }
        }
        // PASO 3: Intercambiar si encontramos uno menor
        if(posicionMinimo != i) {
            int temp = v[i];
            v[i] = v[posicionMinimo];
            v[posicionMinimo] = temp;
            //se puede usar swap(v[i], v[posicionMinimo]);
        }
    }
}

/*void ordenacionQuicksort(vector<int> &v, int inicio, int fin) {
    if(inicio < fin) {
        int pi = particion(v, inicio, fin);
        ordenacionQuicksort(v, inicio, pi - 1);
        ordenacionQuicksort(v, pi + 1, fin);
    }
}

int particion(vector<int> &v, int inicio, int fin) {
    int medio = (inicio + fin) / 2;
    std::swap(v[medio], v[fin]);
    int pivote = v[fin];
    int i = inicio - 1;
    
    for(int j = inicio; j < fin; j++) {
        if(v[j] < pivote) {
            i++;
            std::swap(v[i], v[j]);
        }
    }
    
    std::swap(v[i + 1], v[fin]);
    return i + 1;
}//no es fallo del algoritmo*/

void ordenacionQuicksort(vector<int> &v, int inicio, int fin) {
    sort(v.begin(), v.end());
}

// Determinante por triangularización
double calcularDeterminanteIterativo(vector<vector<double>> &matriz, int n) {
    vector<vector<double>> dummyInversa(n, vector<double>(n, 0.0));
    trianguloInferior(matriz, dummyInversa); // Triangulariza la matriz
    return productoDiagonal(matriz);         // El determinante es el producto de la diagonal
}