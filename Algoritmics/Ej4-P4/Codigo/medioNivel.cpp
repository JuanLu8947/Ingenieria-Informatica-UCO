#include "medioNivel.hpp"
#include "algoritmos.hpp"
#include "serietemporal.hpp"
#include "auxiliares.hpp"
#include <iostream>
#include <chrono>
#include "tiempos.hpp"

using namespace std;

void segmentacionDinamica() {
    //1.Cargar serie y pedir N ptos segmentados //F(X) cargado&creado
    string nameF;
    int nPuntosSegmentados;
    if (!cargarDatos(nameF, nPuntosSegmentados)) {
        return;
    }
    // Crear la serie temporal
    SerieTemporal Serie(nameF.data());
    int nPuntosTotales = Serie.numeroPuntosSerieTemporal();
    
    cout << "Serie temporal cargada con " << nPuntosTotales << " puntos." << endl;
    /*//F(X) tiempos
    clock_t start = clock();
    SegmentacionDinamica(Serie, nPuntosSegmentados);
    clock_t end = clock();
    double tiempoTranscurrido = double(end - start) / CLOCKS_PER_SEC;
    //*/
    double tiempoTranscurrido = medirTiempo(Serie, nPuntosSegmentados);
    
    //Calcular errores
    long double ISE, errorMax;
    int puntoErrorMax;
    Serie.erroresSegmentacion(ISE, errorMax, puntoErrorMax);
    
    //Mostrar resultados
    mostrarResultados(Serie, ISE, errorMax, puntoErrorMax, tiempoTranscurrido);
    
    //Guardar segmentacion
    /*cout << "Guardando serie original y segmentada en archivos..." << endl;
    Serie.guardarSerieTemporal((char*)"Series/BBVA_original.txt"); // o el nombre que corresponda
    Serie.guardarSegmentacion((char*)"Series/BBVA_segmentada.txt"); // solo puntos dominantes*/
    guardarSegmentacion(Serie, nameF);
}
