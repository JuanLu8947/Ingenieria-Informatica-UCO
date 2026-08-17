#include "algoritmos.hpp"
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

//F(X): general
void segmentacion(SerieTemporal &Serie, int nPuntosSegmentados, const string &metodo){
    
    cout << "Serie temporal cargada con " << Serie.numeroPuntosSerieTemporal() << " puntos." << endl;

    // Inicializar todos los puntos como dominantes
    vector<int> dom;
    vector<long double> error;
    
    // Inicialmente todos los puntos son dominantes
    for(int i = 0; i < Serie.numeroPuntosSerieTemporal(); i++){
        Serie.dominantePunto(i, true);
        dom.push_back(i);
    }

    //Calcular errores iniciales para cada punto
    //El primer y último punto tienen error infinito (no se pueden eliminar)
    //1ºpto
    error.push_back(numeric_limits<long double>::infinity());
    //ptos intermedios
    for (int i = 1; i < Serie.numeroPuntosSerieTemporal() - 1; i++) {
        int posicion;
        long double err;
        // Error máximo que se generaría si eliminamos el punto i
        if(metodo == "metodo1"){
            err = Serie.calcularIseEntreDosPuntos(dom[i-1], dom[i+1]);
        }
        else if(metodo == "metodo2"){
            err = Serie.calcularEmaxEntreDosPuntos(dom[i-1], dom[i+1], posicion);
        }
        error.push_back(err);
    }
    //último pto
    error.push_back(numeric_limits<long double>::infinity());

    //mientras que haya más puntos que los deseados:
    while(dom.size() > nPuntosSegmentados){
        int idxMenorErr = -1;
        //Completar examen --hasta aqui dan--
        long double mejorErr = numeric_limits<long double>::infinity(); //se supone que el mejor err es infinito
        //Bucle encontrar menor ISE, excluye 1º y ult pto
        for(int i=1; i<error.size()-1; i++){
            //si se encuentra un err mejor q mejorErr -> actu
            if(error[i] < mejorErr){
                mejorErr = error[i];
                idxMenorErr = i;
            }
        }

        //elim pto de la serie
        Serie.dominantePunto(dom[idxMenorErr], false);

        //elim pto de los vect
        dom.erase(dom.begin()+idxMenorErr);
        error.erase(error.begin()+idxMenorErr);

        //recalc err ptos ady --a partir de aqui dan--
        if(idxMenorErr > 1){ //Pto anterior (no es el primero)
            int i = idxMenorErr - 1; 
            if(metodo == "metodo1"){
                error[i] = Serie.calcularIseEntreDosPuntos(dom[i-1], dom[i+1]);
            }
            else if(metodo == "metodo2"){
                int posicion;
                error[i] = Serie.calcularEmaxEntreDosPuntos(dom[i-1], dom[i+1], posicion);
            }
        }

        if(idxMenorErr < error.size()-1){ //Pto sig (no es el últ)
            int i = idxMenorErr;
            if(metodo == "metodo1"){
                error[i] = Serie.calcularIseEntreDosPuntos(dom[i-1], dom[i+1]);
            }
            else if(metodo == "metodo2"){
                int posicion;
                error[i] = Serie.calcularEmaxEntreDosPuntos(dom[i-1], dom[i+1], posicion);
            }
        }
    }
}