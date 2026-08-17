#include "estadisticas.hpp"
#include "auxiliares.hpp"
#include "sistemaEcuaciones.hpp"
#include <cmath>

void ajustePolinomico(const vector <double> &numeroElementos, const vector <double> &tiemposReales, vector <double> &a){
    //declare M aux
    vector<vector<double>> matrizCoeficientes, matrizTerminosIndependientes, X;
    //declare var aux
    int ordenMatrizSistema = 3; // Para polinomio de grado 2
    
    //f(x) bajo nivel, no tiene cambio de variable
    calcularMatrices(numeroElementos, tiemposReales, ordenMatrizSistema, matrizCoeficientes, matrizTerminosIndependientes);
    
    //3º resolver sys ec, param 3 -> nº filas/col de M
    resolverSistemaEcuaciones(matrizCoeficientes, matrizTerminosIndependientes, ordenMatrizSistema, X);
    
    a.clear();
    for(int i = 0; i < ordenMatrizSistema; i++) {
        a.push_back(X[i][0]);
        /*cout << "a[i]: " << a[i] << endl
            << "X[i][0]" << X[i][0] << "\n\n";*/
    }
}

void calcularMatrices(const vector<double> &numeroElementos, const vector<double> &tiemposReales, int ordenMatrizSistema, vector<vector<double>> &matrizCoeficientes, vector<vector<double>> &matrizTerminosIndependientes) {
    // Implementación de la función para calcular las matrices del sistema
    /*vector<double> n = numeroElementos, t = tiemposReales;
    int expN = 0, expT = 0;
    sumatorio(n, t, expN, expT);*/
    //1º Redimensionar las matrices
    matrizCoeficientes = vector<vector<double>>(ordenMatrizSistema, vector<double>(ordenMatrizSistema));
    matrizTerminosIndependientes = vector<vector<double>>(ordenMatrizSistema, vector<double>(1));
    //2º obtener var aux
    vector<double> n = numeroElementos, t = tiemposReales;

    for (int i = 0; i < ordenMatrizSistema; i++) {
        for (int j = 0; j < ordenMatrizSistema; j++) {
            matrizCoeficientes[i][j] = sumatorio(n, t, i + j, 0);
        }
        matrizTerminosIndependientes[i][0] = sumatorio(n, t, i, 1);
    }
    /*
    Construye el sistema de ecuaciones normal para
     el ajuste polinómico por mínimos cuadrados. 
     Es decir, genera la matriz de coeficientes y 
     el vector de términos independientes que 
     necesitas para encontrar los coeficientes del
     polinomio de ajuste.
    
    Redimensiona las matrices:
    ·matrizCoeficientes se hace de tamaño
     ordenMatrizSistema × ordenMatrizSistema
     (por ejemplo, 3x3 para un polinomio de grado 2).
    ·matrizTerminosIndependientes se hace de tamaño
     ordenMatrizSistema × 1 (un vector columna).
    
    Rellena la matriz de coeficientes:
    ·Para cada posición [i][j], calcula el sumatorio
     usando la función sumatorio con exponente
     de numeroElementos igual a i+j y exponente de 
     tiemposReales igual a 0.
    */
}

void ajusteNlogN(const vector<double> &numeroElementos, const vector<double> &tiemposReales, vector<double> &a){
    //declare M aux
    vector<vector<double>> matrizCoeficientes, matrizTerminosIndependientes, X;
    
    //f(x) bajo nivel donde se hace el cambio
    calcularMatricesNlogN(numeroElementos, tiemposReales, matrizCoeficientes, matrizTerminosIndependientes);
    
    //3º resolver sys ec, param 3 -> nº filas/col de M
    resolverSistemaEcuaciones(matrizCoeficientes, matrizTerminosIndependientes, 2, X);
    
    //vect a[]
    a.clear();
    a.push_back(X[0][0]); // a0
    a.push_back(X[1][0]); // a1
}

void calcularMatricesNlogN(const vector<double> &numeroElementos, const vector<double> &tiemposReales, vector<vector<double>> &matrizCoeficientes, vector<vector<double>> &matrizTerminosIndependientes){
    // Para ajuste t(n) = a0 + a1*n*log(n)
    // Cambio de variable: z = n*log(n)
    // Entonces: t = a0 + a1*z
    
    vector<double> z;
    //completar cambio de variable
    for(int i=0; i<numeroElementos.size(); i++){
        z.push_back(numeroElementos[i]*log(numeroElementos[i]));
    }
    /*formato examen (en ajuste) 
    bucle 
        z[i] = numeroElementos[i]*log(numeroElementos[i];
    */
    
    // Inicializar matrices
    matrizCoeficientes = vector<vector<double>>(2, vector<double>(2));
    matrizTerminosIndependientes = vector<vector<double>>(2, vector<double>(1));
    
    vector<double> t = tiemposReales;
    
    // Sistema para ajuste lineal:
    // Σ1*a0 + Σz*a1 = Σt
    // Σz*a0 + Σz²*a1 = Σzt

    // Para matrizCoeficientes 2x2
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (i == 0 && j == 0)
                matrizCoeficientes[i][j] = numeroElementos.size(); // Σ1
            else
                matrizCoeficientes[i][j] = sumatorio(z, t, i + j, 0); // Σz^(i+j)
        }
    }
    
    // Para matrizTerminosIndependientes 2x1
    for (int i = 0; i < 2; ++i) {
        matrizTerminosIndependientes[i][0] = sumatorio(z, t, i, 1); // Σz^i * t
    }
}

double sumatorio(vector <double> &n, vector <double> &t, int expN, int expT){
    // Implementación de la función para calcular sumatorios de matrices
    double suma = 0.0;
    for (int i = 0; i < n.size(); i++) {
        suma += pow(n[i], expN) * pow(t[i], expT);
    }
    return suma;
    //∑(ni^expN * ti^expT)
}

void ajusteExponencial(const vector<double> &numeroElementos, const vector<double> &tiemposReales, vector<double> &a){
    //se hace como el NlogN
    // Ajuste exponencial: t(n) = a0 + a1*2^n
    // Cambio de variable: z = 2^n
    // Sys: t = a0 + a1*z
    
    //1º crear las M aux
    vector<vector<double>> matrizCoeficientes, matrizTerminosIndependientes, X;
    
    //2º f(x) de bajo nvl donde se hará el cambio
    calcularMatricesExponencial(numeroElementos, tiemposReales, matrizCoeficientes, matrizTerminosIndependientes);
    
    //3º resolver sys ec, param 3 -> nº filas/col de M
    resolverSistemaEcuaciones(matrizCoeficientes, matrizTerminosIndependientes, 2, X);
    
    //4º, primero limpiar vect a[]
    a.clear();
    //5º obtener a0 & a0
    a.push_back(X[0][0]); // a0
    a.push_back(X[1][0]); // a1
}

void calcularMatricesExponencial(const vector<double> &numeroElementos, const vector<double> &tiemposReales, vector<vector<double>> &matrizCoeficientes, vector<vector<double>> &matrizTerminosIndependientes) {
    // Para ajuste t(n) = a0 + a1*2^n
    // Cambio de variable: z = 2^n
    // Entonces: t = a0 + a1*z
    vector<double> z;
    //Completar examen: realizar el cambio de var ====
    for(size_t i = 0; i < numeroElementos.size(); i++) {
        z.push_back(pow(2.0, numeroElementos[i]));
    }
    /*formato examen (en ajuste)
    el cambio se hace directamente en el ajuste
    BUcle
        z[i] = pow(2.0, numeroElementos[i]);
    */
   //=======
    
    // Inicializar matrices
    matrizCoeficientes = vector<vector<double>>(2, vector<double>(2));
    matrizTerminosIndependientes = vector<vector<double>>(2, vector<double>(1));
    
    vector<double> t = tiemposReales;
    
    // Sistema para ajuste lineal:
    // Σ1*a0 + Σz*a1 = Σt
    // Σz*a0 + Σz²*a1 = Σzt

    // Para matrizCoeficientes 2x2
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (i == 0 && j == 0)
                matrizCoeficientes[i][j] = numeroElementos.size(); // Σ1
            else
                matrizCoeficientes[i][j] = sumatorio(z, t, i + j, 0); // Σu^(i+j)
        }
    }
    
    // Para matrizTerminosIndependientes 2x1
    for (int i = 0; i < 2; ++i) {
        matrizTerminosIndependientes[i][0] = sumatorio(z, t, i, 1); // Σu^i * t
    }
}

void ajusteFactorial(const vector<double> &numeroElementos, const vector<double> &tiemposReales, vector<double> &a){
    //se hace como NlogN
    // Ajuste factorial: t(n) = a0 + a1*n!
    // Cambio de variable: v = n!
    // Sistema lineal: t = a0 + a1*v
    
    //1º declare M aux
    vector<vector<double>> matrizCoeficientes, matrizTerminosIndependientes, X;
    
    //2º f(x) de bajo nvl donde se hará el cambio
    calcularMatricesFactorial(numeroElementos, tiemposReales, matrizCoeficientes, matrizTerminosIndependientes);
    
    //3º resolver sys ec, param 3 -> nº filas/col de M
    resolverSistemaEcuaciones(matrizCoeficientes, matrizTerminosIndependientes, 2, X);
    
    //4º, primero limpiar vect a[]
    a.clear();
    //5º obtener a0 & a0
    a.push_back(X[0][0]); // a0
    a.push_back(X[1][0]); // a1
}

void calcularMatricesFactorial(const vector<double> &numeroElementos, const vector<double> &tiemposReales, vector<vector<double>> &matrizCoeficientes, vector<vector<double>> &matrizTerminosIndependientes) {
    // Para ajuste t(n) = a0 + a1*n!
    // Cambio de variable: z = n!
    // Entonces: t = a0 + a1*z
    
    vector<double> z;
    //Completar examen: realizar el cambio de var ====
    for(size_t i = 0; i < numeroElementos.size(); i++) {
        z.push_back(factorial(static_cast<double>(numeroElementos[i])));
    }
    /*formato examen (en ajuste)
    el cambio se hace directamente en el ajuste
    Bucle
        z[i] = fact(n[i]);
    */
    //=======
    
    // Inicializar matrices
    matrizCoeficientes = vector<vector<double>>(2, vector<double>(2));
    matrizTerminosIndependientes = vector<vector<double>>(2, vector<double>(1));
    
    vector<double> t = tiemposReales;
    
    // Sistema para ajuste lineal:
    // Σ1*a0 + Σz*a1 = Σt
    // Σv*a0 + Σz²*a1 = Σvt

    // Para matrizCoeficientes 2x2
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (i == 0 && j == 0)
                matrizCoeficientes[i][j] = numeroElementos.size(); // Σ1
            else
                matrizCoeficientes[i][j] = sumatorio(z, t, i + j, 0); // Σv^(i+j)
        }
    }
    
    // Para matrizTerminosIndependientes 2x1
    for (int i = 0; i < 2; ++i) {
        matrizTerminosIndependientes[i][0] = sumatorio(z, t, i, 1); // Σv^i * t
    }
}

void ajustePolinomicoGrado3(const std::vector<double> &numeroElementos, const std::vector<double> &tiemposReales, std::vector<double> &a){
    // Ajuste polinómico de grado 3: resuelve un sistema 4x4
    int grado = 3;
    int n = grado + 1;
    vector<vector<double>> matrizCoeficientes(n, vector<double>(n, 0.0));
    vector<vector<double>> matrizTerminosIndependientes(n, vector<double>(1, 0.0));

    // Rellenar matriz de coeficientes
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double suma = 0.0;
            for (size_t k = 0; k < numeroElementos.size(); ++k) {
                suma += pow(numeroElementos[k], i + j);
            }
            matrizCoeficientes[i][j] = suma;
        }
    }
    // Rellenar matriz de términos independientes
    for (int i = 0; i < n; ++i) {
        double suma = 0.0;
        for (size_t k = 0; k < numeroElementos.size(); ++k) {
            suma += pow(numeroElementos[k], i) * tiemposReales[k];
        }
        matrizTerminosIndependientes[i][0] = suma;
    }
    // Resolver el sistema
    vector<vector<double>> X;
    resolverSistemaEcuaciones(matrizCoeficientes, matrizTerminosIndependientes, n, X);
    a.clear();
    for (int i = 0; i < n; ++i) {
        a.push_back(X[i][0]);
    }
}

double calcularCoeficienteDeterminacion(const vector <double> &tiemposReales, const vector <double> &tiemposEstimados){
    double varianzaReales = calcularVarianza(tiemposReales);
    double varianzaEstimados = calcularVarianza(tiemposEstimados);
    
    if(varianzaReales == 0) return 0.0;
    return varianzaEstimados / varianzaReales;
}

double calcularVarianza(const vector<double> &datos) {
    if(datos.empty()) return 0.0;
    
    double media = 0.0;
    for(double dato : datos) {
        media += dato;
    }
    media /= datos.size();
    
    double varianza = 0.0;
    for(double dato : datos) {
        varianza += pow((dato - media), 2);
    }
    return varianza / datos.size();
}