#include <vector>    // necesario para el contenedor Vector2D
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <math.h>
#include <cassert>
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
}

//Destructor
SerieTemporal::~SerieTemporal() 
{
	_puntoSerieTemporal.clear();
	_dominante.clear();
}

//Constructor de copia.

SerieTemporal::SerieTemporal(const SerieTemporal &serieTemporal)
{ 
	//Asignamos numero de puntos
 	numeroPuntosSerieTemporal(serieTemporal.numeroPuntosSerieTemporal());

 	// Asignamos todos los puntos del serieTemporal
 	for (int i = 0; i < numeroPuntosSerieTemporal(); i++) 
 	{ 
	   	_puntoSerieTemporal.push_back(serieTemporal.puntoSerieTemporal(i));
	   	_dominante.push_back(serieTemporal.dominantePunto(i));
 	} 
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
 	for(int i = 0 ;i < numeroPuntosSerieTemporal() ; i++) 
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
 
 	for (int t = 0; t < numeroPuntosSerieTemporal(); t++)
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

	  	while (!dominantePunto(t)) // Se localiza extremo derecho del intervalo
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


	  	tIzquierda = tDerecha; //Para el siguiente intervalo tDerecha sera tIzquierda 
 	} while (tDerecha != numeroPuntosSerieTemporal() -1);
}


long double SerieTemporal::calcularIseEntreDosPuntos(int inicial, int final) const
{
	assert(inicial >= 0 and inicial < numeroPuntosSerieTemporal()); 
	assert(final >= 0 and final < numeroPuntosSerieTemporal());

	long double ise = 0.0;
	long double error = 0.0;
	int begin, end;

	if (inicial == final)
	return 0.0;
	    
	Punto p;
	
	begin = inicial;
	end = final;

	Recta recta(puntoSerieTemporal(inicial), puntoSerieTemporal(final));

	assert(inicial <= final);
    
	//Los errores se calculan con distancias de puntos a rectas
    for (int i = begin; i <= end; i++)
    {
        error = recta.distanciaVerticalPuntoRecta(puntoSerieTemporal(i));
        ise += error * error;
    }

	return ise; 
}


long double SerieTemporal::calcularEmaxEntreDosPuntos(int inicial, int final, int &posicion) const
{
	if (inicial == final)
	{
		posicion = inicial;
		return 0;
	}

	assert(inicial >= 0 and inicial < numeroPuntosSerieTemporal()); 
	assert(final >= 0 and final < numeroPuntosSerieTemporal()); 

	long double errorMaximo = 0.0;
	long double error = 0.0;

	Recta recta(puntoSerieTemporal(inicial), puntoSerieTemporal(final));
	posicion = inicial;
	   
	for (int i = inicial + 1; i < final; i++) 
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
  
  for (int t = 0; t < numeroPuntosSerieTemporal(); t++)
 	{
  	if (dominantePunto(t) == 1)
  	{
   		p = puntoSerieTemporal(t);  
   		cout << "El punto " << t << " de coordenadas x = " << p.x() << " y = " << p.y() <<" \n";
  	}
 	}
}

