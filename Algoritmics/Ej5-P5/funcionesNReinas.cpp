#include <vector>
#include <iostream>
#include <limits>
#include <cstdlib>
#include "funcionesNReinas.hpp"

using namespace std;

//Esta función obtiene todas las soluciones al problema de las nReinas usando Backtracking
void nReinasBacktracking(const int n, vector< vector<int>> &soluciones)
{
    vector<int> solucion (n);
    solucion[0] = -1;
    int fila = 0;

    while(fila > -1)
    {
        solucion[fila] = solucion[fila] + 1;
        while(solucion[fila] < n && !lugar(solucion, fila))
            solucion[fila] = solucion[fila] + 1;
        if (solucion[fila] < n)
        {
            if (fila == n - 1)
                soluciones.push_back(solucion);
            else 
            {
                fila = fila + 1;
                solucion[fila] = -1;
            }
        } 
        else
            fila = fila - 1; 
    }
}

//Esta función obtiene una solución al problema de las nReinas usando el método de Las Vegas.
bool nReinasLasVegas(int n, vector<int> &solucion)
{
   	//Completar
    solucion.resize(n);
    
    //Inicializamos la solución a 0
    for (int i = 0; i < n; i++)
        solucion[i] = 0;
    
    //Se han colocado k-1 reinas y se buscan todas las posiciones para la k-ésima
    for (int k = 0; k < n; k++){
        int cont = -1;
        vector<int> posicionesPosibles(n); //Almacena las posiciones posibles para la k-ésima reina
        for (int j = 0; j < n; j++){ //Probamos todas las columnas para la reina k
            solucion[k] = j; //Probamos la reina k en la columna j
            if(lugar(solucion, k)){
                cont++;
                posicionesPosibles[cont] = j; //Almacenamos la posición válida
            }
        } 
        if (cont == -1) //No hay posiciones posibles para la k-ésima reina
            return false;

        //Se puede colocar la reina k y elegimos aleatoriamente una de las posiciones posibles
        int columna = rand() % (cont + 1); //Elegimos un índice aleatorio entre 0 y cont
        solucion[k] = posicionesPosibles[columna]; //Colocamos la reina k en la posición elegida
    }
    return true; //Se han colocado todas las reinas exitosamente
}

//OPCIONAL. Esta función obtiene todas las soluciones al problema de las nReinas usando el método Las Vegas.
void nReinasLasVegasTodas(const int n, vector< vector<int>> &soluciones)
{
	//Completar
    soluciones.clear();
    vector<int> solucion;
    
    //Obtenemos todas las soluciones por backtracking para saber cuántas hay
    vector<vector<int>> soluciones_bt;
    nReinasBacktracking(n, soluciones_bt);
    int num_soluciones_esperadas = soluciones_bt.size();
    
    //Intentamos encontrar todas las soluciones usando Las Vegas
    while (soluciones.size() < num_soluciones_esperadas){
        if(nReinasLasVegas(n, solucion)){
            //Comprobamos si la solución ya está almacenada
            bool encontrada = false;
            for (auto sol: soluciones)
                if (sol == solucion){
                    encontrada = true;
                    break;
                }

            if (!encontrada)
                soluciones.push_back(solucion);
        }
    }
}

//Función que comprueba si la reina que se va a colocar en la fila indicada por el segundo parámetro, 
//apunta a cualquiera de las reinas ubicadas en filas anteriores.
bool lugar(vector<int> &x, const int fila)
{
   //Completar examen
   for(int i=0; i<fila; i++){
        if(x[i] == x[fila] || abs(x[i]-x[fila]) == abs(i-fila))
            return false; //amenaza
   }
   return true;
}

//Función que muestra todas las soluciones obtenidas para el problema de las nReinas
void escribirSoluciones(std::vector< std::vector <int> >&soluciones)
{
    cout << endl;
    for (auto solucion: soluciones)
    {
        cout << "[" ;
        for (auto valor: solucion)
            cout << " " << valor;
        cout << " ]" << endl;
    }
    cout << "Número de soluciones: " << soluciones.size() << endl;
}

//Función que muestra una solución para el problema de las nReinas. Se usa en el método de las Vegas.
void escribirSolucion(std::vector<int> &solucion)
{
    cout << endl;
    cout << "[";
    for(auto valor: solucion)
        cout << " " << valor;
    cout << " ]" << endl;
}

