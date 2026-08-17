#ifndef FUNCIONES_GRAFOS
#define FUNCIONES_GRAFOS

#include <string>
#include <vector>

using namespace std;

void cargarCiudades(const string nombreFichero, vector<string> &nombres);
void mostrarCiudades(const vector<string> &ciudad);
void cargarMatrizConexion(const string fichero, vector <vector<double> > &matrizConexion);
void mostrarMatrizConexion(const vector< vector<double>> &matriz);
void mostrarCamino(vector<int> &camino);
void mostrarSolucionOptima(const vector<string> &nombresCiudades, const vector< vector<double> > &matrizConexion, vector <int> &camino, 
                            double distanciaMinima);
void mostrarCiclosHamiltonianos(const vector<string> &nombresCiudades, const vector< vector<int> > &ciclosHamiltonianos);
void obtenerCamino(const vector< vector<double> > &solucion, vector<int> &camino);
double sumarDistancias(const vector< vector<double> > &matrizConexion, vector <int> &camino);
int siguienteNodo(const vector< vector<double> > &m, vector <int> caminoActual, vector <int> &caminoAnterior, vector<bool> visitado);
void obtenerCiclosHamiltonianos(const vector< vector<double> > &m, vector< vector<int> > &ciclos,  vector <int> caminoActual, 
                                vector <int> &caminoAnterior, vector<bool> visitado, int ciudadOrigen);
void obtenerSolucionOptimaSinPoda(const vector< vector<double> > &m, vector <int> caminoActual, vector <int> &caminoAnterior, vector <int> &caminoOptimo, 
                                    double distanciaActual, double &distanciaOptima, vector<bool> visitado, int ciudadOrigen);
void obtenerSolucionOptimaConPoda(const vector< vector<double> > &m, vector <int> caminoActual, vector <int> &caminoAnterior, vector <int> &caminoOptimo, 
                                    double distanciaActual, double &distanciaOptima, vector<bool> visitado, int ciudadOrigen);

#endif
