#include "tiempos.hpp"

double medirTiempo(Matriz& A, unsigned int exp, funcion_t funcion) {
    Clock cronometro;
    cronometro.start();
    if(funcion == POTENCIA)
        Matriz resultado = A.potencia(exp);
    else if(funcion == POTENCIA_DYV1)
        Matriz resultado = A.potenciaDyV1(exp);
    else if(funcion == POTENCIA_DYV2)
        Matriz resultado = A.potenciaDyV2(exp);
    /*else if(funcion == POTENCIA_OPCIONAL)
        Matriz resultado = A.potenciaLU(exp);*/
    cronometro.stop();
    return cronometro.elapsed() / 1000000.0;
}