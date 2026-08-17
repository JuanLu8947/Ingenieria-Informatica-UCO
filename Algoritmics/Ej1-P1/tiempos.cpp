#include "tiempos.hpp"

void tiemposOrdenacionSeleccion(int nMin, int nMax, int incremento, int repeticiones, vector<double> &tiemposReales, vector<double> &numeroElementos){
    tiemposReales.clear();
    numeroElementos.clear();
    double tiempoPromedio = 0.0;
    
    cout << "Calculando tiempos para ordenación por selección...\n";
    for(int n = nMin; n <= nMax; n += incremento) {
        double tTot = 0.0;
        
        cout << "Probando con n = " << n << " (repeticiones: " << repeticiones << ")...\n";
        for(int r = 0; r < repeticiones; r++){
            vector<int> v(n);
            rellenarVector(v);

            //Clock time;
            //completar nw ===
            //1º i0 reloj
            clock_t t_ini = clock();
            //2º f(x) de bajo nvl
            ordenacionSeleccion(v);
            //3º fin reloj
            clock_t t_fin = clock();

            tTot += static_cast<double>(t_fin - t_ini) / CLOCKS_PER_SEC; // Convertir de clock ticks a segundos
            //====
        }
        //completar nw ===
        double tiempoPromedio = tTot / repeticiones;
        tiemposReales.push_back(tiempoPromedio);
        numeroElementos.push_back(static_cast<double>(n));
        //===
        cout << "  Tiempo promedio: " << tiempoPromedio << " segundos\n";
    }
}

void calcularTiemposEstimadosPolinomico(const vector <double> &numeroElementos, const vector <double> &a, vector <double> &tiemposEstimados){
    //completar nw
    //1º limpiar vect de t
    tiemposEstimados.clear();
    //2ºbucle
    for(int i=0; i<numeroElementos.size(); i++){
        double t = calcularTiempoEstimadoPolinomico(numeroElementos[i], const_cast<vector <double>&>(a));
        tiemposEstimados.push_back(t);
    }
}

double calcularTiempoEstimadoPolinomico(const double &n, vector <double> &a){
    //completar nw
    //1º var aux t
    double t = 0.0;
    //2º bucle
    for(int i=0; i<a.size(); i++){
        t += a[i]*pow(n,i); //t(n) = a[i]*n^i
    }
    //devolver t
    return t;
}

void calcularTiemposEstimadosNlogN(const vector <double> &numeroElementos, const vector <double> &a, vector <double> &tiemposEstimados){
    //completar nw
    //1º limpiar vect de t
    tiemposEstimados.clear();
    //2º bucle
    for(int i=0; i<numeroElementos.size(); i++){
        tiemposEstimados.push_back(calcularTiempoEstimadoNlogN(numeroElementos[i], a));
    }
}

double calcularTiempoEstimadoNlogN(const double &n, const vector<double> &a) {
    //completar nw
    //devolver a0 + a1 * n log(n)
    return a[0] + a[1] * n * log(n);
}

void tiemposOrdenacionQuicksort(int nMin, int nMax, int incremento, int repeticiones, std::vector<double>& tiemposReales, std::vector<double>& numeroElementos) {
    //1º limpiar los vect
    tiemposReales.clear();
    numeroElementos.clear();
    double tiempoPromedio = 0.0;
    //2º bucle de nMin a nMax según incremento
    for(int n=nMin; n<=nMax; n+=incremento){
        //2.1 declare var aux t
        double tTot = 0.0;

        //2.2 bucle según rep
        for(int rep=0; rep<repeticiones; rep++){
            //declare v aux y rellenarlo
            vector<int> v(n);
            rellenarVector(v);

            Clock time;
            //completar nw ===
            //1º i0 reloj
            time.start();
            //2º f(x) de bajo nvl
            ordenacionQuicksort(v, 0, n-1);
            //3º fin reloj
            time.stop();

            tTot += time.elapsed() / 1000000.0; // Convertir de microseg a segundos
            //====
        }
        //completar nw ===
        tiempoPromedio = tTot / repeticiones;
        tiemposReales.push_back(tiempoPromedio);
        numeroElementos.push_back(static_cast<double>(n));
        //===
        cout << "Tiempo promedio: " << tiempoPromedio << " segundos\n";
    }
} 

void tiemposDeterminante(int nMin, int nMax, int incremento, vector<double>& tiemposReales, vector<double>& numeroElementos) {
    //1º limpiar los vect
    tiemposReales.clear();
    numeroElementos.clear();
    double t = 0.0;
    double det;
    //2º bucle desde nMin hasta nMax según incremento
    for(int n=nMin; n<=nMax; n+=incremento){
        //2.1 declare M aux y rellenarla
        vector<vector<double>> matriz(n, vector<double>(n));
        rellenarMatriz(matriz);

        Clock time;
        //completar  nw==
        //reloj + bajo nvl
        time.start();
        calcularDeterminante(matriz, det);
        time.stop();

        //nº elem y tiempos
        t = time.elapsed() / 1000000.0; //us -> seg
        tiemposReales.push_back(t);
        numeroElementos.push_back(static_cast<double>(n));
        // ===
        cout << "  Tiempo: " << t << " segundos\n";
    }
}

//new

void calcularTiemposEstimadosExponencial(const vector <double> &numeroElementos, const vector <double> &a, vector <double> &tiemposEstimados){
    //completar examen
    //1º limpiar vect de t
    tiemposEstimados.clear();
    //2º bucle calc n tEstimados
    for(size_t i=0; i<numeroElementos.size(); i++){
        double tEstimado = calcularTiempoEstimadoExponencial(numeroElementos[i], a);
        tiemposEstimados.push_back(tEstimado);
    }
}

double calcularTiempoEstimadoExponencial(const double &n, const std::vector<double> &a){
    //completar examen
    return a[0] + a[1]*pow(2,n);
}


void calcularTiemposEstimadosFactorial(const vector <double> &numeroElementos, const vector <double> &a, vector <double> &tiemposEstimados){
    //completar examen
    //1º limpiar vect de t
    tiemposEstimados.clear();
    //2º bucle calc n tEstimados
    for(size_t i=0; i<numeroElementos.size(); i++){
        double tEstimado = calcularTiempoEstimadoFactorial(numeroElementos[i], a);
        tiemposEstimados.push_back(tEstimado);
    }
}

double calcularTiempoEstimadoFactorial(const double &n, const std::vector<double> &a){
    //completar examen
    return a[0] + a[1]*factorial(n);
}
