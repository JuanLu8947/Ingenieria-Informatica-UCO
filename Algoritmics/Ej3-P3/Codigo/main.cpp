#include "medioNivel.hpp"
#include <iostream>
using namespace std;

int main(){
    int o;
    
    do {
        cout << "=== PRÁCTICA 3: SEGMENTACIÓN DE SERIES TEMPORALES ===\n";
        cout << "1. Método 1: Segmentación minimizando ISE" << endl;
        cout << "2. Método 2: Segmentación minimizando eMax" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> o;
        
        switch(o) {
            case 1:
                metodo1();
                break;
            case 2:
                metodo2();
                break;
            case 0:
                cout << "\nSaliendo del programa..." << endl;
                break;
            default:
                cout << "\nOpción no válida. Intente de nuevo.\n";
                break;
        }
    } while(o != 0);
    
    return 0;
}