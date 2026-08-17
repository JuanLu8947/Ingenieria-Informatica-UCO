#ifndef SerieTemporal_H
#define SerieTemporal_H
   
#include <vector>    // necesario para el contenedor Vector2D
#include <algorithm>
#include "punto.hpp"


using namespace std; //Para usar Vector de la STL

/* Estructura del serieTemporal, que contendr� n puntos */
class SerieTemporal
{
	public:
			
		SerieTemporal(char *nombreFichero);
		~SerieTemporal();
		inline int numeroPuntosSerieTemporal()const //Observador
   		{
			return _numeroPuntos;
		}
		
		inline void numeroPuntosSerieTemporal(const int &n) //Modificador
		{
 			_numeroPuntos = n;
		}

		inline Punto puntoSerieTemporal(const int &posicion)const //Observador
		{
			return _puntoSerieTemporal[posicion];
		}

		inline void puntoSerieTemporal(const Punto &p, const int &posicion) //Modificador
		{
			_puntoSerieTemporal[posicion] = p; 
		}

		inline bool dominantePunto(const int &posicion)const //Observador
		{
 			return _dominante[posicion];
		}

		inline void dominantePunto(const int &posicion, const bool &dominante)	//Modificador
		{
 			_dominante[posicion] = dominante;
		}
		
		void guardarSerieTemporal(char *nombre)const; //Guarda en un fichero los pumntos de la serie temporal
    	void guardarSegmentacion(char *nombre)const; //Guarda en un fichero los puntos de la segmentacion de la serie temporal.
		int contarPuntosDominantes()const;
		//Esta función calcula los errores globales de la segmentación y el punto en el que se produce el error máximo
    	void erroresSegmentacion(long double &sumaErrorCuadrado, long double &errorMaximo, int &posicionMaximo)const;
    	long double calcularIseEntreDosPuntos(int inicial, int final)const;
    	long double calcularEmaxEntreDosPuntos(int inicial, int final, int &posicion) const;
    	void mostrarPuntosDominantes();
		
	private:
		int _numeroPuntos; /* Numero depuntos del serieTemporal */
		vector<Punto> _puntoSerieTemporal; /* Vector para los puntos del serieTemporal */
		vector<bool> _dominante; /* Valor booleano que indica si el punto es dominante (true) o no (false) */
		vector <long double>  _sumaX, _sumaY, _sumaXX, _sumaYY, _sumaXY; //variables para calcular los sumatorios
		void calcularSumatorios(); //Función que calcula los sumatorios.
};




#endif
