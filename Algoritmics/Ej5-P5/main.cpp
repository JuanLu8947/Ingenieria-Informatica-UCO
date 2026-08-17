#include <iostream>
#include "funcionesMedioNivel.hpp"

using namespace std;

int main()
{     
    int opcion;
    do
    {
      cout << "1. Calcular ciclos hamiltonianos" << endl;
      cout << "2. Algoritmo óptimo Viajante de comercio sin poda" << endl;
      cout << "3. Algoritmo óptimo Viajante de comercio con poda" << endl;
      cout << "4. N-Reinas por método de Backtracking" << endl;
      cout << "5. N-Reinas por método de las Vegas (una solución)" << endl;
      cout << "6. N-Reinas por método de las Vegas (todas las soluciones)" << endl;
      cout << "0. Salir del programa" << endl;

      cout << "Seleecione una opción: ";

      cin >> opcion;
      
      switch(opcion){
         case 0:
            cout <<"Saliendo del programa "<< endl;
            break;
 
         case 1:
         	//Ya está hecho
            obtenerCiclosHamiltonianos(); 
            break;

         case 2:
         	//Obligatorio
            viajanteComercioOptimoSinPoda();
            break;

         case 3:
         	//Opcional
            viajanteComercioOptimoConPoda();
            break;

         case 4:
         	//Ya está hecho
            nReinasBacktracking();
            break;

         case 5:
         	//Obligatorio
            nReinasLasVegas();
            break;

         case 6:
         	//Opcional
            nReinasLasVegasTodas();
            break;            

         default:
            cout << "Opcion incorrecta" << endl;
         
      }
    }while(opcion != 0);

    return 0;
}




