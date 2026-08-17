#include "tiempos.hpp"
#include "ClaseTiempo.hpp"
#include "funcionesNReinas.hpp"

double medirTiempo(int reinas, vector<vector<int>> &soluciones) {
    Clock time;
    time.start();
    nReinasLasVegasTodas(reinas, soluciones);
    time.stop();
    return time.elapsed()/1000.0; // Convertir microsegundos a ms
}