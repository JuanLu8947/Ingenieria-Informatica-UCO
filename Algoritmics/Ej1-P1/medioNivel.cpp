#include "medioNivel.hpp"
#include "tiempos.hpp"
#include "estadisticas.hpp"
#include "auxiliares.hpp"
#include "algoritmos.hpp"
#include "funcHanoi.hpp"
#include <cmath>

void ordenacionSeleccion() {
    // Implementación de la ordenación por selección
    cout << "\n=== ORDENACION POR SELECCION ===\n";
    int nMin, nMax, incremento, repeticiones;
    vector <double> tiemposReales, numeroElementos, a, tiemposEstimados;

    cout << "Introduzca los parámetros para las pruebas:\n";
    cout << "Tamaño mínimo: ";
    cin >> nMin;
    cout << "Tamaño máximo: ";
    cin >> nMax;
    while(nMax < nMin){
        std::cout << "El máximo no puede ser menor que el mínimo\nIntroduce un valor adecuado para el máximo: ";
        std::cin >> nMax;
    }
    cout << "Incremento: ";
    cin >> incremento;
    cout << "Repeticiones: ";
    cin >> repeticiones;

    /*vector<int> v;
    rellenarVector(v);*/

    cout << "\n1. Calculando tiempos reales...\n";
    tiemposOrdenacionSeleccion(nMin, nMax, incremento, repeticiones, tiemposReales, numeroElementos);

    cout << "\n2. Calculando ajuste polinómico de grado 2...\n";
    ajustePolinomico(numeroElementos, tiemposReales, a);

    cout << "\n3. Calculando tiempos estimados...\n";
    calcularTiemposEstimadosPolinomico(numeroElementos, a, tiemposEstimados);

    double coefDeterminacion = calcularCoeficienteDeterminacion(tiemposReales, tiemposEstimados);
    
    guardarDatos(numeroElementos, tiemposReales, tiemposEstimados);
    //guardarDatosAlgoritmo(numeroElementos, tiemposReales, tiemposEstimados, "datosSeleccion.txt");

    cout << "\n=== RESULTADOS ===\n"; //a0 + a1*n + a2*n^2
    cout << "Ecuación de la curva ajustada: t(n) = " << a[0] << " + " << a[1] << "*n + " << a[2] << "*n^2" << endl;
    cout << "Coeficiente de determinación: " << coefDeterminacion << " (" << (coefDeterminacion * 100) << "%)\n";

    // Estimaciones para tamaños específicos
    double n;
    cout << "\n=== ESTIMACIONES ===\n";
    cout << "Introduzca tamaños de ejemplar para estimar tiempos (0 para salir): ";
    do{
        cout << "\nTamaño del ejemplar: ";
        cin >> n;
        if(n == 0) break;
        double tiempoEstimado = calcularTiempoEstimadoPolinomico(n, a);
        cout << "Tiempo estimado: " << tiempoEstimado << " segundos\n";
        mostrarTiempoFormateado(tiempoEstimado);
        cout << endl;
    }while(n != 0);
}

void ordenacionQuicksort() {
    // Implementación de la ordenación por Quicksort
    cout << "\n=== ORDENACION POR QUICKSORT ===\n";
    int nMin, nMax, incremento, repeticiones;
    vector<double> tiemposReales, numeroElementos, a, tiemposEstimados;

    cout << "Introduzca los parámetros para las pruebas:\n";
    cout << "Tamaño mínimo: ";
    cin >> nMin;
    cout << "Tamaño máximo: ";
    cin >> nMax;
    while(nMax < nMin){
        cout << "El máximo no puede ser menor que el mínimo\nIntroduce un valor adecuado para el máximo: ";
        cin >> nMax;
    }
    cout << "Incremento: ";
    cin >> incremento;
    cout << "Repeticiones: ";
    cin >> repeticiones;

    cout << "\n1. Calculando tiempos reales...\n";
    tiemposOrdenacionQuicksort(nMin, nMax, incremento, repeticiones, tiemposReales, numeroElementos);
    
    cout << "\n2. Calculando ajuste n*log(n)...\n";
    ajusteNlogN(numeroElementos, tiemposReales, a);

    cout << "\n3. Calculando tiempos estimados...\n";
    calcularTiemposEstimadosNlogN(numeroElementos, a, tiemposEstimados);

    double coefDeterminacion = calcularCoeficienteDeterminacion(tiemposReales, tiemposEstimados);

    guardarDatos(numeroElementos, tiemposReales, tiemposEstimados);
    //guardarDatosAlgoritmo(numeroElementos, tiemposReales, tiemposEstimados, "datosQuicksort.txt");

    cout << "\n=== RESULTADOS ===\n";
    cout << "Ecuación de la curva ajustada: t(n) = " << a[0] << " + " << a[1] << "*n*log(n)" << endl;
    cout << "Coeficiente de determinación: " << coefDeterminacion << "\n";

    // Estimaciones para tamaños específicos
    double n;
    cout << "\n=== ESTIMACIONES ===\n";
    cout << "Introduzca tamaños de ejemplar para estimar tiempos (0 para salir): ";
    do{
        cout << "\nTamaño del ejemplar: ";
        cin >> n;
        if (n == 0) break;
        double tiempoEstimado = calcularTiempoEstimadoNlogN(n, a);
        cout << "Tiempo estimado: " << tiempoEstimado << " segundos\n";
        mostrarTiempoFormateado(tiempoEstimado);
        cout << endl;
    }while(n != 0);
}

void determinanteIterativo() {
    cout << "\n=== DETERMINANTE ITERATIVO ===\n";
    int nMin, nMax, incremento;
    vector<double> tiemposReales, numeroElementos, a, tiemposEstimados;

    cout << "Introduzca los parámetros para las pruebas:\n";
    cout << "Tamaño mínimo: ";
    cin >> nMin;
    cout << "Tamaño máximo: ";
    cin >> nMax;
    while(nMax < nMin){
        cout << "El máximo no puede ser menor que el mínimo\nIntroduce un valor adecuado para el máximo: ";
        cin >> nMax;
    }
    cout << "Incremento: ";
    cin >> incremento;

    cout << "\n1. Calculando tiempos reales...\n";
    tiemposDeterminante(nMin, nMax, incremento, tiemposReales, numeroElementos);

    cout << "\n2. Calculando ajuste polinómico de grado 3...\n";
    ajustePolinomicoGrado3(numeroElementos, tiemposReales, a); // Debes tener esta función, igual que ajustePolinomico pero para grado 3

    cout << "\n3. Calculando tiempos estimados...\n";
    calcularTiemposEstimadosPolinomico(numeroElementos, a, tiemposEstimados);

    double coefDeterminacion = calcularCoeficienteDeterminacion(tiemposReales, tiemposEstimados);

    guardarDatos(numeroElementos, tiemposReales, tiemposEstimados);
    //guardarDatosAlgoritmo(numeroElementos, tiemposReales, tiemposEstimados, "datosDeterminante.txt");

    cout << "\n=== RESULTADOS ===\n";
    cout << "Ecuación de la curva ajustada: t(n) = " << a[0] << " + " << a[1] << "*n + " << a[2] << "*n^2 + " << a[3] << "*n^3" << endl;
    cout << "Coeficiente de determinación: " << coefDeterminacion << " (" << (coefDeterminacion * 100) << "%)\n";

    // Estimaciones para tamaños específicos
    double n;
    cout << "\n=== ESTIMACIONES ===\n";
    cout << "Introduzca tamaños de ejemplar para estimar tiempos (0 para salir): ";
    do{
        cout << "\nTamaño del ejemplar: ";
        cin >> n;
        if(n == 0) break;
        double tiempoEstimado = a[0] + a[1]*n + a[2]*n*n + a[3]*n*n*n;
        cout << "Tiempo estimado: " << tiempoEstimado << " segundos\n";
        mostrarTiempoFormateado(tiempoEstimado);
        cout << endl;
    }while(n != 0);
}

void torresDeHanoi() {
    cout << "\n=== TORRES DE HANOI ===\n";
    int nMin, nMax, incremento;
    vector<double> tiemposReales, numeroElementos;

    cout << "Introduzca los parámetros para las pruebas:\n";
    cout << "Número mínimo de discos: ";
    cin >> nMin;
    cout << "Número máximo de discos: ";
    cin >> nMax;
    while(nMax < nMin){
        cout << "El máximo no puede ser menor que el mínimo\nIntroduce un valor adecuado para el máximo: ";
        cin >> nMax;
    }
    cout << "Incremento: ";
    cin >> incremento;

    cout << "\n1. Calculando tiempos reales...\n";
    tiemposHanoi(nMin, nMax, incremento, numeroElementos, tiemposReales);
    guardarDatos(numeroElementos, tiemposReales, tiemposReales);
}

void torresDeHanoiConAjuste() {
    cout << "\n=== TORRES DE HANOI CON AJUSTE EXPONENCIAL ===\n";
    int nMin, nMax, incremento;
    vector<double> tiemposReales, numeroElementos, a, tiemposEstimados;

    cout << "Introduzca los parámetros para las pruebas:\n";
    cout << "Número mínimo de discos: ";
    cin >> nMin;
    cout << "Número máximo de discos: ";
    cin >> nMax;
    while(nMax < nMin){
        cout << "El máximo no puede ser menor que el mínimo\nIntroduce un valor adecuado para el máximo: ";
        cin >> nMax;
    }
    cout << "Incremento: ";
    cin >> incremento;

    cout << "\n1. Calculando tiempos reales...\n";
    tiemposHanoi(nMin, nMax, incremento, numeroElementos, tiemposReales);

    cout << "\n2. Calculando ajuste exponencial...\n";
    ajusteExponencial(numeroElementos, tiemposReales, a);

    cout << "\n3. Calculando tiempos estimados...\n";
    calcularTiemposEstimadosExponencial(numeroElementos, a, tiemposEstimados);

    double coefDeterminacion = calcularCoeficienteDeterminacion(tiemposReales, tiemposEstimados);

    guardarDatos(numeroElementos, tiemposReales, tiemposEstimados);

    cout << "\n=== RESULTADOS ===\n";
    cout << "Ecuación de la curva ajustada: t(n) = " << a[0] << " + " << a[1] << "*2^n" << endl;
    cout << "Coeficiente de determinación: " << coefDeterminacion << " (" << (coefDeterminacion * 100) << "%)\n";

    // Estimaciones para tamaños específicos
    double n;
    cout << "\n=== ESTIMACIONES ===\n";
    cout << "Introduzca tamaños de ejemplar para estimar tiempos (0 para salir): ";
    do{
        cout << "\nNúmero de discos: ";
        cin >> n;
        if(n == 0) break;
        double tiempoEstimado = calcularTiempoEstimadoExponencial(n, a);
        cout << "Tiempo estimado: " << tiempoEstimado << " ms\n";
        mostrarTiempoFormateado(tiempoEstimado / 1000.0);
        cout << endl;
    }while(n != 0);
}

void torresDeHanoiConAjusteFactorial() {
    cout << "\n=== TORRES DE HANOI CON AJUSTE FACTORIAL ===\n";
    int nMin, nMax, incremento;
    vector<double> tiemposReales, numeroElementos, a, tiemposEstimados;

    cout << "Introduzca los parámetros para las pruebas:\n";
    cout << "Número mínimo de discos: ";
    cin >> nMin;
    cout << "Número máximo de discos: ";
    cin >> nMax;
    while(nMax < nMin){
        cout << "El máximo no puede ser menor que el mínimo\nIntroduce un valor adecuado para el máximo: ";
        cin >> nMax;
    }
    cout << "Incremento: ";
    cin >> incremento;

    cout << "\n1. Calculando tiempos reales...\n";
    tiemposHanoi(nMin, nMax, incremento, numeroElementos, tiemposReales);

    cout << "\n2. Calculando ajuste factorial...\n";
    ajusteFactorial(numeroElementos, tiemposReales, a);

    cout << "\n3. Calculando tiempos estimados...\n";
    calcularTiemposEstimadosFactorial(numeroElementos, a, tiemposEstimados);

    double coefDeterminacion = calcularCoeficienteDeterminacion(tiemposReales, tiemposEstimados);

    guardarDatos(numeroElementos, tiemposReales, tiemposEstimados);

    cout << "\n=== RESULTADOS ===\n";
    cout << "Ecuación de la curva ajustada: t(n) = " << a[0] << " + " << a[1] << "*n!" << endl;
    cout << "Coeficiente de determinación: " << coefDeterminacion << " (" << (coefDeterminacion * 100) << "%)\n";

    // Estimaciones para tamaños específicos
    double n;
    cout << "\n=== ESTIMACIONES ===\n";
    cout << "Introduzca tamaños de ejemplar para estimar tiempos (0 para salir): ";
    do{
        cout << "\nNúmero de discos: ";
        cin >> n;
        if(n == 0) break;
        double tiempoEstimado = calcularTiempoEstimadoFactorial(n, a);
        cout << "Tiempo estimado: " << tiempoEstimado << " ms\n";
        mostrarTiempoFormateado(tiempoEstimado / 1000.0);
        cout << endl;
    }while(n != 0);
}

void compararAjustesHanoi() {
    cout << "\n=== COMPARACION DE AJUSTES (EXPONENCIAL vs FACTORIAL) ===\n";
    int nMin, nMax, incremento;
    vector<double> tiemposReales, numeroElementos;
    vector<double> aExp, aFact, tiemposExpEstimados, tiemposFactEstimados;

    cout << "Introduzca los parámetros para las pruebas:\n";
    cout << "Número mínimo de discos: ";
    cin >> nMin;
    cout << "Número máximo de discos: ";
    cin >> nMax;
    while(nMax < nMin){
        cout << "El máximo no puede ser menor que el mínimo\nIntroduce un valor adecuado para el máximo: ";
        cin >> nMax;
    }
    cout << "Incremento: ";
    cin >> incremento;

    cout << "\n1. Calculando tiempos reales...\n";
    tiemposHanoi(nMin, nMax, incremento, numeroElementos, tiemposReales);

    cout << "\n2. Calculando ajuste exponencial...\n";
    ajusteExponencial(numeroElementos, tiemposReales, aExp);
    calcularTiemposEstimadosExponencial(numeroElementos, aExp, tiemposExpEstimados);

    cout << "\n3. Calculando ajuste factorial...\n";
    ajusteFactorial(numeroElementos, tiemposReales, aFact);
    calcularTiemposEstimadosFactorial(numeroElementos, aFact, tiemposFactEstimados);

    double coefExpDeterminacion = calcularCoeficienteDeterminacion(tiemposReales, tiemposExpEstimados);
    double coefFactDeterminacion = calcularCoeficienteDeterminacion(tiemposReales, tiemposFactEstimados);

    guardarDatos(numeroElementos, tiemposReales, tiemposExpEstimados);
    
    cout << "\n=== RESULTADOS ===\n";
    cout << "\nAJUSTE EXPONENCIAL:\n";
    cout << "Ecuación: t(n) = " << aExp[0] << " + " << aExp[1] << "*2^n" << endl;
    cout << "Coeficiente de determinación: " << coefExpDeterminacion << " (" << (coefExpDeterminacion * 100) << "%)\n";
    
    cout << "\nAJUSTE FACTORIAL:\n";
    cout << "Ecuación: t(n) = " << aFact[0] << " + " << aFact[1] << "*n!" << endl;
    cout << "Coeficiente de determinación: " << coefFactDeterminacion << " (" << (coefFactDeterminacion * 100) << "%)\n";

    cout << "\n=== RECOMENDACION ===\n";
    if(coefExpDeterminacion > coefFactDeterminacion) {
        cout << "El ajuste EXPONENCIAL es mejor (R² = " << coefExpDeterminacion << ")\n";
    } else {
        cout << "El ajuste FACTORIAL es mejor (R² = " << coefFactDeterminacion << ")\n";
    }
}
