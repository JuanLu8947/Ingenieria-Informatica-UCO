#include <vector>    // necesario para el contenedor Vector2D
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <math.h>
#include <cassert>
#include <numeric>
#include "serietemporal.hpp"
#include "punto.hpp"
#include "recta.hpp"

using namespace std;

/* FUNCIONES DE INTERFAZ PARA EL TIPO CONTORNO */


//Constructor. Crea un serieTemporal a partir de un fichero
SerieTemporal::SerieTemporal(char *nombreFichero)	
{
	//Se leen los puntos del fichero y se almacenan en el serieTemporal
	//Tambien se inicializa el vector de dominantes a false
 	long double x, y;
    Punto p;
        

 	ifstream pf(nombreFichero);
 	if (!pf)
    {
	    cout << "\n Fichero inexistente";
	    exit(0);
    }
    
    //Los puntos leídos se almacenan en la serie y todos los puntos se marcan como no dominantes
 	while(pf >> x >> y)
 	{
	    p.x(x);
    	p.y(y);
    	_puntoSerieTemporal.push_back(p);
    	_dominante.push_back(false);
 	}

 	//Asignamos numero de puntos de la serie.
 	numeroPuntosSerieTemporal(_puntoSerieTemporal.size());         
 	pf.close();  

 	//Reservamos los valarrays de los sumatorios.
 	_sumaX.resize(numeroPuntosSerieTemporal());
    _sumaY.resize(numeroPuntosSerieTemporal());
    _sumaXX.resize(numeroPuntosSerieTemporal());
    _sumaYY.resize(numeroPuntosSerieTemporal());
    _sumaXY.resize(numeroPuntosSerieTemporal());
    //Calcula los sumatorios para facilitar y reducir la complejidad del cálculo del ISE.
    calcularSumatorios();
}

//Destructor
SerieTemporal::~SerieTemporal() 
{
	_puntoSerieTemporal.clear();
	_dominante.clear();
}


//Guarda en un fichero los pumntos de la serie temporal
void SerieTemporal::guardarSerieTemporal(char *nombre)const
{
	Punto punto;
 	ofstream pf(nombre);

 	if (!pf) 
  	{
	    cout << "Error en la apertura del fichero \n";
	    exit(0);
  	}
 
 	/* Guardamos las coordenadas cartesianas del serieTemporal */ 
 	for(int i = 0 ;i < numeroPuntosSerieTemporal() ; i++) // Cambio en la indexación
	{
		punto = puntoSerieTemporal(i);
   		pf << punto.x() << " " << punto.y() << "\n";
	}

  	pf.close();
}

//Esta función es igual que la anterior pero solo guarda los puntos dominantes que componen la segmentación

void SerieTemporal::guardarSegmentacion(char *nombre)const
{
	Punto punto;
	ofstream pf(nombre);

	if (!pf) 
	{
		cout << "Error en la apertura del fichero \n";
		exit(0);
	}
 
 	/* Guardamos las coordenadas cartesianas del serieTemporal */ 
 	for(int i = 0 ;i < numeroPuntosSerieTemporal() ; i++) // Cambio en la indexación
	{
	    if (dominantePunto(i))
	    {
			punto = puntoSerieTemporal(i);
	        pf << punto.x() << " " << punto.y() << "\n";
	    }
	}

  	pf.close();
}

int SerieTemporal::contarPuntosDominantes()const
{
 	int numeroPuntosDominantes = 0;
 
 	for (int t = 0; t < numeroPuntosSerieTemporal(); t++) // Cambio en la indexación
 	{
	  	if (dominantePunto(t))
	  	{
	   		numeroPuntosDominantes++;
	  	}
 	}

	return numeroPuntosDominantes;
}

//Esta funcion calcula el ISE, error máximo y su posición, para la segmentacion realizada.
void SerieTemporal::erroresSegmentacion(long double &sumaErrorCuadrado, long double &errorMaximo, int &posicionMaximo)const
{
 	int t = 0; // Cambio en la indexación inicial
 	//int tInicial;
 	int tIzquierda, tDerecha;
 	long double error;
 	int posicion;

 	/* Recorrido del serieTemporal, calculando la distancia de cada punto real del serieTemporal
    al serieTemporal aproximado por los puntosdominantes */
 	sumaErrorCuadrado = 0.0;
 	errorMaximo = 0.0;

 	/*Busqueda del primer punto dominante del serieTemporal*/
 	while(!dominantePunto(t)) 
  		t++;

 	//tInicial = t;

 	/* se asigna el extremo izquierdo del intervalo a tInicial para los primeros puntos */
 	tIzquierda = t; 
 	do
 	{
	  	t++;

	  	while (!dominantePunto(t)) /* Se localiza extremo derecho del intervalo */
	   		t++;

	  	tDerecha = t;

	  	
	  	//Se calcula el ISE entre tIzquierda y tDerecha y se acumula
	  	sumaErrorCuadrado+= calcularIseEntreDosPuntos(tIzquierda, tDerecha);

	  	//Se calcula el emax entre tIzquierda y tDerecha y se guarda el máximo
	  	error = calcularEmaxEntreDosPuntos(tIzquierda, tDerecha, posicion);

		if (error > errorMaximo) //Actualizamos error máximo y su posición
	   	{
	    	errorMaximo = error;
	    	posicionMaximo = posicion;
	   	}


	  	tIzquierda = tDerecha; /*Para el siguiente intervalo tDerecha sera tIzquierda */
 	} while (tDerecha != numeroPuntosSerieTemporal() -1);
}


long double SerieTemporal::calcularIseEntreDosPuntos(int inicial, int final) const
{
	assert(inicial >= 0 and inicial < numeroPuntosSerieTemporal()); 
	assert(final >= 0 and final < numeroPuntosSerieTemporal());

	/*Esta funcion calcula la suma de los errores medidos en vertical de los puntos comprendidos entre inicio y fin*/
	/* Con respecto a la recta que une los puntos inicio y fin */

	long double ise = 0.0;
	long double A, B, C; //Coeficientes de la recta en forma general. Ax + By + C = 0
	long double a, b; //Coeficientes de la recta en forma explícita. y = a + bx

	if (inicial == final)
		return 0.0;
	if (inicial == final - 1)
		return 0.0;

	int numeroPuntos = final - inicial - 1;

	Recta recta(puntoSerieTemporal(inicial), puntoSerieTemporal(final));
	


	//Como la recta se calcula en forma general, hay que calcular los coeficientes en forma explicita (a y b)
	A = recta.a();
	B = recta.b();
	C = recta.c();

	//Se tienen en cuenta solo los puntos comprendidos entre inicio y fin
	//Por eso se pone fin-1 en el índice, ya que fin no entra en el sumatorio
	
	a = - C / B;
	b = - A / B;
    ise = numeroPuntos * a * a + (_sumaYY[final-1] - _sumaYY[inicial]) + b * b * (_sumaXX[final-1] - _sumaXX[inicial])
    - 2.0 * a * (_sumaY[final-1] - _sumaY[inicial]) - 2.0 * b * (_sumaXY[final-1] - _sumaXY[inicial]) + 2.0 * a * b * (_sumaX[final-1] - _sumaX[inicial]);


	return ise; 
}


long double SerieTemporal::calcularEmaxEntreDosPuntos(int inicial, int final, int &posicion) const
{
	if (inicial == final)
	{
		posicion = inicial;
		return 0;
	}

	assert(inicial >= 0 and inicial < numeroPuntosSerieTemporal()); // Cambio la indexación
	assert(final >= 0 and final < numeroPuntosSerieTemporal()); // Desde 0 hasta n-1

	long double errorMaximo = 0.0;
	long double error = 0.0;

	Recta recta(puntoSerieTemporal(inicial), puntoSerieTemporal(final));
	posicion = inicial;
	   
	for (int i = inicial + 1; i < final; i++) // No debo cambiarlo ? 
	{
		error = recta.distanciaVerticalPuntoRecta(puntoSerieTemporal(i));
		if (error > errorMaximo)
		{
		  errorMaximo = error;
		  posicion = i;
		}
	}
	return errorMaximo;
}

	
void SerieTemporal::mostrarPuntosDominantes()
{
 	Punto p;
  
  for (int t = 0; t < numeroPuntosSerieTemporal(); t++) // Cambio en la indexación
 	{
  	if (dominantePunto(t) == 1)
  	{
   		p = puntoSerieTemporal(t);  
   		cout << "El punto " << t << " de coordenadas x = " << p.x() << " y = " << p.y() <<" \n";
  	}
 	}
}

void SerieTemporal::calcularSumatorios()
{
    long double x, y; //Coordenadas de un punto*/
	//Primero se calculan el valor de los sumatorios para el primer elemento.
    x = puntoSerieTemporal(0).x(); //cordenada x del punto 0
    y = puntoSerieTemporal(0).y(); //cordenada y del punto 0

    _sumaX[0] = x;
    _sumaY[0] = y;
    _sumaXX[0] = x * x;
    _sumaYY[0] = y * y;
    _sumaXY[0] = x * y;

    //Ahora se calculan el resto, sumando al actual el anterior
    for(int i = 1; i < numeroPuntosSerieTemporal(); i++)
	{
        x = puntoSerieTemporal(i).x();
        y = puntoSerieTemporal(i).y();
        _sumaX[i] =_sumaX[i-1] + x;
        _sumaY[i] =_sumaY[i-1] + y;
        _sumaXX[i] =_sumaXX[i-1] + x * x;
        _sumaYY[i] =_sumaYY[i-1] + y * y;
        _sumaXY[i] =_sumaXY[i-1] + x * y;
    }

}
	





