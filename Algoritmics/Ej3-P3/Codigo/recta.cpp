#include <math.h>
#include <cassert>
#include "recta.hpp"
#include "punto.hpp"

/* La recta se va a representar en forma general ax + by + c = 0 */

Recta::Recta(const Punto &p1, const Punto &p2)
{
 	a(p1.y() - p2.y());
 	b(p2.x() - p1.x());
	c(p1.x() * (-(p1.y() - p2.y())) + p1.y() * (-(p2.x() - p1.x())));
}

Recta::Recta(const Recta &r) //Constructor de copia
{
	a(r.a());
	b(r.b());
	c(r.c());
}

Recta & Recta::operator=(const Recta &r) //Sobrecarga de la asignacion
{
	a(r.a());
	b(r.b());
	c(r.c());

	return *this;
}

long double Recta::distanciaPuntoRecta(const Punto &punto)const
{
 	long double distancia;

 	distancia = fabs( a() * punto.x() + b() * punto.y() + c()) / pow( a() * a() + b() * b(), 0.5);

 	return distancia;
}

long double Recta::distanciaVerticalPuntoRecta(const Punto &punto)const
{
 	long double distancia;

 	distancia = fabs(punto.y() + a()*punto.x()/b() + c()/b());

 	return distancia;
}

int Recta::signoPuntoRecta(const Punto &punto)const
{  
  long double valor;
  valor = a() * punto.x() + b() * punto.y() + c();

  if (valor > 0.0) //El punto está por encima de la recta
    return 1;
  else if (valor < 0.0) //El punto está por debajo de la recta
    return -1;
  else //El punto está en la recta
    return 0;
}
