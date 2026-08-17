#include "auxiliares.hpp"
#include <iostream>
#include <fstream>
#include <cstring>

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

// Función auxiliar para mostrar resultados finales
void mostrarResultados(const SerieTemporal &serie, const string &nombreMetodo) {
    long double errorMax, iseTotal, eMaxTotal;
    int posicionMax;

    if(nombreMetodo == "MÉTODO 1"){
        serie.erroresSegmentacion(iseTotal, errorMax, posicionMax);
    }
    else if(nombreMetodo == "MÉTODO 2"){
        serie.erroresSegmentacion(eMaxTotal, errorMax, posicionMax);
    }
    
    cout << "\n--- RESULTADOS " << nombreMetodo << " ---" << endl
         << "Número de puntos dominantes: " << serie.contarPuntosDominantes() << endl;
    if(nombreMetodo == "MÉTODO 1"){
        cout << "ISE = " << iseTotal << endl;
    }
    else if(nombreMetodo == "MÉTODO 2"){
        cout << "eMax = " << eMaxTotal << endl;
    }
    cout << "Error Máximo = " << errorMax << endl
         << "Punto del Error Máximo = " << posicionMax << endl;
    //
}

void guardarSegmentacion(const SerieTemporal &Serie, const string &nameF, const string &nombreMetodo) {
    string nombreSalida;
    if(nombreMetodo == "MÉTODO 1"){
        nombreSalida = nameF.substr(0, nameF.find(".txt")) + "_metodo1_segmentado.txt";
    }
    else if(nombreMetodo == "MÉTODO 2"){
        nombreSalida = nameF.substr(0, nameF.find(".txt")) + "_metodo2_segmentado.txt";
    }
    Serie.guardarSegmentacion((char*)nombreSalida.c_str());
    cout << "Segmentación guardada en: " << nombreSalida << endl;
    /*
    1:
     nameF.find(".txt") - Busca la posición donde aparece ".txt" en el nombre del archivo
     nameF.substr(0, nameF.find(".txt")) - Extrae la parte del nombre desde el inicio hasta antes de ".txt"
    2:
     nombreSalida.c_str() - Convierte el std::string a const char*, con casting
    */
}

/*
Grafica:
-fichero normal
-segmentacion-metodo1
-segmentacion-metodo2 
*/