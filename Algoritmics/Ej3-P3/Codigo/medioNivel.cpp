#include "medioNivel.hpp"
#include "algoritmos.hpp"
#include "auxiliares.hpp"
#include <iostream>
#include <string>

using namespace std;

void metodo1() {
    cout << "\n=== MÉTODO 1: SEGMENTACIÓN MINIMIZANDO ISE ===\n";
    
    // Cargar datos de entrada
    string nameF;
    int nPuntosSegmentados;
    if (!cargarDatos(nameF, nPuntosSegmentados)) {
        return;
    }
    
    // Crear la serie temporal
    SerieTemporal Serie(nameF.data());
    
    // Llamar al algoritmo de bajo nivel
    //segmentacionMinimizandoISE(Serie, nPuntosSegmentados);
    segmentacion(Serie, nPuntosSegmentados, "metodo1");

    // Mostrar resultados
    mostrarResultados(Serie, "MÉTODO 1");
    
    // Guardar segmentación
    guardarSegmentacion(Serie, nameF, "MÉTODO 1");
}

void metodo2() {
    cout << "\n=== MÉTODO 2: SEGMENTACIÓN MINIMIZANDO eMax ===\n";
    
    // Cargar datos de entrada
    string nameF;
    int nPuntosSegmentados;
    if (!cargarDatos(nameF, nPuntosSegmentados)) {
        return;
    }
    
    // Crear la serie temporal
    SerieTemporal Serie(nameF.data());
    
    // Llamar al algoritmo de bajo nivel
    //segmentacionMinimizandoEmax(Serie, nPuntosSegmentados);
    segmentacion(Serie, nPuntosSegmentados, "metodo2");

    // Mostrar resultados
    mostrarResultados(Serie, "MÉTODO 2");
    
    // Guardar segmentación
    guardarSegmentacion(Serie, nameF, "MÉTODO 2");
}
