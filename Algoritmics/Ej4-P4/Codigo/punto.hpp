#ifndef PUNTO_H
#define PUNTO_H

#include <math.h>
/* Estructura de punto en 2D con coordenadas cartesianas y polares */
class Punto
{
  public:
		Punto()
		{
			_x = 0.0;
			_y = 0.0;
		};
		Punto(long double x, long double y)
    { 
			_x = x;
			_y = y;
		};

		Punto(const Punto &p)
    {
			x(p.x());
			y(p.y());
		};

    Punto & operator=(const Punto &p)
    {
			x(p.x());
			y(p.y());

			return *this;
		};

    bool operator==(const Punto &p) const
    {
			if (fabs(x()- p.x()) < 0.0000001 && fabs(y() - p.y()) < 0.0000001)
				return true;
			return false;
		};
		
		bool operator!=(const Punto &p) const
		{
			if (fabs(x()- p.x()) < 0.0000001 && fabs(y() - p.y()) < 0.0000001)
				return false;
			return true;
		};
		

		inline long double x()const //Observador
		{
			return _x;
		};
			
		inline long double y()const //Observador
		{
			return _y;
		};

		inline void x(const long double &x) //Modificador
		{
			_x = x;
		};

		inline void y(const long double &y) //Modificador
		{
			_y = y;
		};

		long double distanciaPuntos(const Punto &p)const;
		
	private:
 		long double _x; /* Coordenada cartesina x del punto */
 		long double _y; /* Coordenada cartesiana y del punto */
};


#endif
