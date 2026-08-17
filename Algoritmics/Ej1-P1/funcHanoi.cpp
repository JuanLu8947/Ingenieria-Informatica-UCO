#include <vector>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include "funcHanoi.hpp"
//#include "miscelanea.hpp"
#include "ClaseTiempo.hpp"
#include "sistemaEcuaciones.hpp"

void tiemposHanoi(int nMin, int nMax, int inc,
std::vector<double> &numeroElementos, std::vector<double> &tiemposReales)
{
    std::srand(unsigned(std::time(nullptr)));

    for (int i = nMin; i <= nMax; i += inc) 
    {        
        Clock time; //declare clock
        double tiempoReal = 0;

        //COMPLETAR ESTA PARTE
            //Rellenar la parte de la toma de tiempos. 
            //La función que resuelve las torres de Hanoi es la función que tenéis a continuación
        //1º i0 reloj
        time.start();
        //2º f(x) bajo nivel
        torresHanoi(i, 1, 2);
        //3º paramos reloj
        time.stop();
        
        //4º obtener tiempo
        tiempoReal = time.elapsed() / 1000.0; // Convertir de microseg a ms
        //5º añadimos los elem al vect
        numeroElementos.push_back(i);
        //6º añadimos los t
        tiemposReales.push_back(tiempoReal);
        
        //====
        std::cout << "n = " << i << " t Hanoi original = " << tiempoReal  << " ms. " << std::endl;
    }

}

void torresHanoi(int n, int i, int j)
{
    if (n > 1)
    {
        torresHanoi(n - 1, i, 6 - i -j);
        torresHanoi(n - 1, 6 - i - j, j);
    }  

}

