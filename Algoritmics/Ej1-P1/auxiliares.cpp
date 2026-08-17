#include "auxiliares.hpp"
#include "medioNivel.hpp"
#include "estadisticas.hpp"
#include "algoritmos.hpp"
#include <cmath> // std::nan

void rellenarVector(vector<int> &v) {
    for(size_t i = 0; i < v.size(); i++){
        v[i] = rand() % 10000000; // Rellenar con números aleatorios entre 0 y 9999999
    }
    //ordenacionSeleccion(v); // Ordenar el vector tras rellenarlo
}

double factorial(int n) {
    if (n < 0) {
        return std::nan("");
    }
    double resultado = 1.0;
    for (int i = 2; i <= n; ++i) {
        resultado *= static_cast<double>(i);
    }
    return resultado;
}

void guardarDatos(const vector<double> &numeroElementos, const vector<double> &tiemposReales, const vector<double> &tiemposEstimados) {
    // Implementación de la función para guardar los datos en un archivo
    ofstream fichero("datosFinales.txt"); // Abrir archivo en modo escritura
    if(fichero.is_open()) { 
        // Configurar formato del archivo
        fichero << fixed << setprecision(8);
        
        // Encabezados alineados
        fichero << left << setw(12) << "# Tamaño" 
                << setw(15) << "Tiempo_Real" 
                << setw(15) << "Tiempo_Estimado" << "\n";
        
        // Datos alineados
        for(size_t i = 0; i < numeroElementos.size(); i++) {
            fichero << left << setw(12) << static_cast<int>(numeroElementos[i])
                    << setw(15) << tiemposReales[i] 
                    << setw(15) << tiemposEstimados[i] << "\n";
        }
        fichero.close();
        cout << "Datos guardados correctamente\n";
    } 
    else {
        cout << "Error al abrir el archivo para guardar los datos.\n";
    }
}

void guardarDatosAlgoritmo(const vector<double> &numeroElementos, const vector<double> &tiemposReales, const vector<double> &tiemposEstimados, const string &nombreArchivo) {
    // Función flexible para guardar datos de diferentes algoritmos
    ofstream fichero(nombreArchivo);
    if(fichero.is_open()) {
        // Encabezados alineados
        fichero << "# Tamaño " 
                << "Tiempo_Real " 
                << "Tiempo_Estimado" << endl;
        
        // Datos alineados
        for(size_t i = 0; i < numeroElementos.size(); i++) {
            fichero << static_cast<int>(numeroElementos[i]) 
                    << " " <<  tiemposReales[i] 
                    << " " << tiemposEstimados[i] << endl;
        }
        fichero.close();
        cout << "Datos guardados en " << nombreArchivo << "\n";
    } 
    else {
        cout << "Error al abrir el archivo " << nombreArchivo << "\n";
    }
}

void mostrarTiempoFormateado(double segundos) {
    int anos = segundos / (365.25 * 24 * 3600);
    segundos -= anos * 365.25 * 24 * 3600;
    
    int dias = segundos / (24 * 3600);
    segundos -= dias * 24 * 3600;
    
    int horas = segundos / 3600;
    segundos -= horas * 3600;
    
    int minutos = segundos / 60;
    segundos -= minutos * 60;
    
    cout << "Tiempo estimado formateado: ";
    if(anos > 0) cout << anos << " años, ";
    if(dias > 0) cout << dias << " días, ";
    if(horas > 0) cout << horas << " horas, ";
    if(minutos > 0) cout << minutos << " minutos, ";
    cout << segundos << " segundos\n";
}

void rellenarMatriz(vector<vector<double>> &matriz) {
    int n = matriz.size();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            matriz[i][j] = 0.95 + (static_cast<double>(rand()) / RAND_MAX) * 0.1; // Entre 0.95 y 1.05
        }
    }
}

void calcularDeterminante(const vector<vector<double>>& matriz, double& determinante) {
    vector<vector<double>> copia = matriz;
    vector<vector<double>> dummyInversa(matriz.size(), vector<double>(matriz.size(), 0.0));
    trianguloInferior(copia, dummyInversa);
    determinante = productoDiagonal(copia);
}

void seleccionAleatoria80_20(const vector<double> &numeroElementos, const vector<double> &tiemposReales, vector<double> &elementos80, vector<double> &tiempos80, vector<double> &elementos20, vector<double> &tiempos20) {
    for(size_t i = 0; i < numeroElementos.size(); i++) {
        if(i % 5 != 4) { // 4 de cada 5 (80%)
            elementos80.push_back(numeroElementos[i]);
            tiempos80.push_back(tiemposReales[i]);
        } else { // 1 de cada 5 (20%)
            elementos20.push_back(numeroElementos[i]);
            tiempos20.push_back(tiemposReales[i]);
        }
    }
}
