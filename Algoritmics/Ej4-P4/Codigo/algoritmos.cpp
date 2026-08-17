#include "algoritmos.hpp"
#include "serietemporal.hpp"
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

void SegmentacionDinamica(SerieTemporal &s, int numeroPuntosSegmentacion){
    vector<vector<long double>> errOptimo(s.numeroPuntosSerieTemporal(), vector<long double>(numeroPuntosSegmentacion, numeric_limits<long double>::infinity()));
    vector<vector<int>> padre(s.numeroPuntosSerieTemporal(), vector<int>(numeroPuntosSegmentacion));

    errOptimo[0][0] = 0;
    for (int n = 1; n < s.numeroPuntosSerieTemporal(); ++n) {
        errOptimo[n][0] = numeric_limits<long double>::infinity();
    }

    //Completar examen====
    int N = s.numeroPuntosSerieTemporal(), M = numeroPuntosSegmentacion;
    /*if (M < 2 || M > N) //No se puede aprox N ptos con 1 sgmnt || Nº de sgment debe ser menor al nº de puntos
        return;*/ //sobra

    for(int m = 1 ; m <= M-1; ++m) //M
        for(int n = m ; n <= N-1; ++n) //N, desde m
            for(int j = m-1; j <= n-1; ++j){ //aux hasta n-1 (incluido)
                long double err = errOptimo[j][m-1] + s.calcularIseEntreDosPuntos(j, n); 
                //si se encuentra uno mas optimo que el actual -> actu
                if(err < errOptimo[n][m]){ //n, m
                    errOptimo[n][m] = err; //n, m
                    padre[n][m] = j; //n, m
                }
            }
    //===============

    vector<int> dom(numeroPuntosSegmentacion);
    int i = s.numeroPuntosSerieTemporal()-1;
    for (int m = numeroPuntosSegmentacion-1; m > 0; --m) {
        dom[m] = i;
        i = padre[i][m];
    }

    for (int i = 0; i < s.numeroPuntosSerieTemporal(); ++i) {
        s.dominantePunto(i, false);
    }

    for (int i = 0; i < numeroPuntosSegmentacion; ++i) {
        s.dominantePunto(dom[i], true);
    }
}