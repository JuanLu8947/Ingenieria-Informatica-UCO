#ifndef RECTA_H
#define RECTA_H
#include <cassert>
#include "punto.hpp"


/* La recta se va a representar en forma general ax + by + c = 0 */
class Recta
{
	public:
		Recta(const Punto &p1, const Punto &p2);
		Recta(const Recta &r); //Constructor de copia
		Recta & operator=(const Recta &r); //Sobrecarga de la asignacion
		inline long double a()const //Observador
		{
 			return _a;
		};

		inline long double b()const //Observador
		{
 			return _b;
		};

		inline long double c()const //Observador
		{
 			return _c;
		};

		inline void a(const long double &a) //Modificador
		{
			_a = a;
		};

		inline void b(const long double &b) //Modificador
		{
			_b = b;
		};

		inline void c(const long double &c) //Modificador
		{
			_c = c;
		};
    
    inline long double m() const
    {
      assert(fabs(b()) > 0.0000001);
      return -a()/b();
    }
      

		long double distanciaPuntoRecta(const Punto &punto)const;
		long double distanciaVerticalPuntoRecta(const Punto &punto)const;
		int signoPuntoRecta(const Punto &punto)const;

	private:
 		long double _a;
 		long double _b;
 		long double _c;
};





#endif
