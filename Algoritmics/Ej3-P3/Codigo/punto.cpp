#include "punto.hpp"
#include <math.h>
/* FUNCIONES DE INTERFAZ PARA EL TIPO PUNTO */


long double Punto::distanciaPuntos(const Punto &p)const
{
	//Variables incremento de x e y de un punto al siguiente
 	long double dx,dy;

 	// Obtencion de los incrementos
 	dx = x() - p.x();
 	dy = y() - p.y();

 	return (pow (dx * dx + dy * dy, 0.5));
}