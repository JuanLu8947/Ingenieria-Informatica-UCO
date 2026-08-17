#include "auxiliares.hpp"
#include <iostream>
#include <fstream>
#include <cstring> //strlen

// Función auxiliar para cargar archivo y obtener número de puntos segmentados
bool cargarDatos(string &nameF, int &nPuntosSegmentados) {
    cout << "Introduzca el nombre del archivo de datos: ";
    cin >> nameF;

    // Añadir prefijo "Series/" si no existe
    if (nameF.find("Series/") != 0) {
        nameF = "Series/" + nameF;
    }
    // Añadir el sufijo ".txt" si no existe
    if (nameF.find(".txt") != nameF.length() - strlen(".txt")) {
        nameF += ".txt";
    }

    ifstream file(nameF);
    if (!file.is_open()) {
        cout << "Error al abrir el archivo: " << nameF << endl;
        return false;
    }
    file.close();
    cout << "El archivo " << nameF << " se abrió correctamente." << endl;

    cout << "Introduzca el número de puntos segmentados: ";
    cin >> nPuntosSegmentados;
    
    return true;
}

void mostrarResultados(SerieTemporal &Serie, long double ISE, long double errorMax, int puntoErrorMax, double tiempo) {
    cout << "\nResultados de la segmentación:" << endl
         << "ISE = " << ISE << endl
         << "Error máximo = " << errorMax << endl
         << "Punto de error máximo = " << puntoErrorMax << endl
         << "Tiempo de segmentación: " << tiempo << " segundos" << endl
         << "Puntos óptimos de segmentación: ";
    //
    for(int i = 0; i < Serie.numeroPuntosSerieTemporal(); i++)
        if(Serie.dominantePunto(i) == 1)
            cout << i << " ";
    cout << endl;
}

void guardarSegmentacion(const SerieTemporal &Serie, const string &nameF) {
    string salidaSegment = nameF.substr(0, nameF.find(".txt")) + "_segmentado.txt";
    string salidaOriginal = nameF.substr(0, nameF.find(".txt")) + "_original.txt";
    cout << "Guardando serie original en: " << salidaOriginal << endl;

    Serie.guardarSerieTemporal((char*)salidaOriginal.c_str());
    Serie.guardarSegmentacion((char*)salidaSegment.c_str());
    cout << "Segmentación guardada en: " << salidaSegment << endl;
}
