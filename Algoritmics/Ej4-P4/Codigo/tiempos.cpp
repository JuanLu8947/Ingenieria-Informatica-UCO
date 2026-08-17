#include "tiempos.hpp"
#include "algoritmos.hpp"
#include <chrono>

double medirTiempo(SerieTemporal &Serie, int nPuntosSegmentados) {
    clock_t start = clock();
    SegmentacionDinamica(Serie, nPuntosSegmentados);
    clock_t end = clock();
    return double(end - start) / CLOCKS_PER_SEC;
}