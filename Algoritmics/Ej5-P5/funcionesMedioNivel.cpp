#include <vector>
#include <string>
#include <iostream>
#include "ClaseTiempo.hpp"
#include "funcionesMedioNivel.hpp"
#include "funcionesGrafos.hpp"
#include "funcionesNReinas.hpp"
#include "ClaseTiempo.hpp"
#include "tiempos.hpp"

using namespace std;

void obtenerCiclosHamiltonianos()
{
    //Objeto clase reloj para medir el tiempo
    Clock tiempo;

    //Matriz de conexion del grafo
    vector< vector<double> > matrizConexion;

    //Vector con los nombres de ciudades
    vector<string> nombresCiudades;

    //Ficherpos que contienen la matriz de conexión y los nombres de l as ciudades.
    string ficheroMatrizConexion = "matrizAndalucia.txt";
    string ficheroCiudades = "ciudadesAndalucia.txt";

    //Ciudad donde comenzará al viajante su recorrido
    int ciudadOrigen;

    //Cargamos las ciudades del fichero
    cargarCiudades(ficheroCiudades, nombresCiudades);

    //cargamos la matriz de conexión del grafo
    cargarMatrizConexion(ficheroMatrizConexion, matrizConexion);

    //Vector de enteros que contendrá los nodos en orden que conforman el camino que se está evaluando.
    vector <int> caminoActual;

    //Vector de enteros que contendrá el camino anterior completo del camino que se está evaluando.
    //Se usa para que en la vuelta atrás de la recursividad, la función siguienteNodo no haga lo mismo que 
    //cuando pasó por ahí la última vez
    vector <int> caminoAnterior;

    //Matriz donde se guardarán los ciclos hamiltonianos
    vector< vector<int> > ciclosHamiltonianos;

    //Seleccionamos la ciudad origen
    mostrarCiudades(nombresCiudades);
    cout << "Seleccione número de la ciudad origen: ";
    cin >> ciudadOrigen;

    int n = matrizConexion.size();

    //Ahora usamos vector de visitados
    vector<bool>  visitado(n, false);

    //Ahora se llama a la función que obtiene los ciclos Hamiltonianos
    tiempo.start();
    obtenerCiclosHamiltonianos(matrizConexion, ciclosHamiltonianos, caminoActual, caminoAnterior, visitado, ciudadOrigen);
    tiempo.stop();
    cout << "ha empleado " << tiempo.elapsed() << " microsegundos \n";

    //Mostramos los ciclos Hamiltonianos
    mostrarCiclosHamiltonianos(nombresCiudades, ciclosHamiltonianos);
}

void viajanteComercioOptimoSinPoda()
{
    //Objeto clase reloj para medir el tiempo
    Clock tiempo;

    //Matriz de conexion del grafo
    vector< vector<double> > matrizConexion;

    //Vector con los nombres de ciudades
    vector<string> nombresCiudades;

    //Ficheros que contienen la matriz de conexión y los nombres de l as ciudades.
    string ficheroMatrizConexion = "matrizAndalucia.txt";
    string ficheroCiudades = "ciudadesAndalucia.txt";

    //Ciudad donde comenzará al viajante su recoorido
    int ciudadOrigen;

    //Cargamos las ciudades desde el fichero
    cargarCiudades(ficheroCiudades, nombresCiudades);

    //cargamos la matriz de conexión del grafo
    cargarMatrizConexion(ficheroMatrizConexion, matrizConexion);

    //Vector de enteros que contendrá los nodos en orden que conforman el camino que se está evaluando.
    vector <int> caminoActual;

    //Vector de enteros que contendrá el camino anterior completo del camino que se está evaluando.
    //Se usa para que en la vuelta atrás de la recursividad, la función siguienteNodo no haga lo mismo que 
    //cuando pasó por ahí la última vez
    vector <int> caminoAnterior;

    //Vector de enteros que contendrá los nodos en orden que conforman el camino óptimo en cada momento.
    //Al final contendrá el camino óptimo global
    vector <int> caminoOptimo;

    //Distancia del camino que se está evaluando
    double distanciaActual = 0.0;

    //Distancia del camino óptimo en cada momento. Se inicializa con infinito
    //Al final contendrá la distancia del camino óptimo
    double distanciaOptima = 100000000.0;

    //Seleccionamos la ciudad origen
    mostrarCiudades(nombresCiudades);
    cout << "Seleccione número de la ciudad origen: ";
    cin >> ciudadOrigen;

    int n = matrizConexion.size();
    
    //Ahora usamos vector de visitados
    vector<bool>  visitado(n, false);

    //Realizamos la búsqueda en profundad para calcular los lados de árbol
    tiempo.start();
    obtenerSolucionOptimaSinPoda(matrizConexion, caminoActual, caminoAnterior, caminoOptimo, distanciaActual, distanciaOptima, visitado, ciudadOrigen);
    tiempo.stop();
    cout << "ha empleado " << tiempo.elapsed() << " microsegundos \n";

    //Mostramos la solución óptima
    mostrarSolucionOptima(nombresCiudades, matrizConexion, caminoOptimo, distanciaOptima);
}

void viajanteComercioOptimoConPoda()
{
    //Objeto clase reloj para medir el tiempo
    Clock tiempo;

    //Matriz de conexion del grafo
    vector< vector<double> > matrizConexion;

    //Vector con los nombres de ciudades
    vector<string> nombresCiudades;

    //Ficheros que contienen la matriz de conexión y los nombres de l as ciudades.
    string ficheroMatrizConexion = "matrizAndalucia.txt";
    string ficheroCiudades = "ciudadesAndalucia.txt";

    //Ciudad donde comenzará al viajante su recoorido
    int ciudadOrigen;

    //Cargamos las ciudades desde el fichero
    cargarCiudades(ficheroCiudades, nombresCiudades);

    //cargamos la matriz de conexión del grafo
    cargarMatrizConexion(ficheroMatrizConexion, matrizConexion);

    //Vector de enteros que contendrá los nodos en orden que conforman el camino que se está evaluando.
    vector <int> caminoActual;

    //Vector de enteros que contendrá el camino anterior completo del camino que se está evaluando.
    //Se usa para que en la vuelta atrás de la recursividad, la función siguienteNodo no haga lo mismo que 
    //cuando pasó por ahí la última vez
    vector <int> caminoAnterior;

    //Vector de enteros que contendrá los nodos en orden que conforman el camino óptimo en cada momento.
    //Al final contendrá el camino óptimo global
    vector <int> caminoOptimo;

    //Distancia del camino que se está evaluando
    double distanciaActual = 0.0;

    //Distancia del camino óptimo en cada momento. Se inicializa con infinito
    //Al final contendrá la distancia del camino óptimo
    double distanciaOptima = 100000000.0;

    //Seleccionamos la ciudad origen
    mostrarCiudades(nombresCiudades);
    cout << "Seleccione número de la ciudad origen: ";
    cin >> ciudadOrigen;

    int n = matrizConexion.size();
    
    //Ahora usamos vector de visitados
    vector<bool>  visitado(n, false);

    //Realizamos la búsqueda en profundad para calcular los lados de árbol
    tiempo.start();
    obtenerSolucionOptimaConPoda(matrizConexion, caminoActual, caminoAnterior, caminoOptimo, distanciaActual, distanciaOptima, visitado, ciudadOrigen);
    tiempo.stop();
    cout << "ha empleado " << tiempo.elapsed() << " microsegundos \n";

    //Mostramos la solución óptima
    mostrarSolucionOptima(nombresCiudades, matrizConexion, caminoOptimo, distanciaOptima);
}

void nReinasBacktracking()
{
    int reinas;
    cout << endl;
    cout << "Introduzca el número de reinas" << endl;
    cin >> reinas;

    std::vector< std::vector<int> > soluciones;
    Clock time;

    time.start();
    nReinasBacktracking(reinas, soluciones);
    time.stop();
    cout << endl;
    escribirSoluciones(soluciones);
    cout << "Tiempo tardado: " << time.elapsed()/1000.0 << "ms" << endl;
}

void nReinasLasVegas()
{
    int reinas;
    int no_exitos = 1;
    cout << endl;
    cout << "Introduzca el número de reinas" << endl;
    cin >> reinas;

    std::vector<int> solucion;
    Clock time;
    bool exito = false;

    time.start();
    while (!exito && no_exitos < 1000000){
        exito = nReinasLasVegas(reinas, solucion);
        no_exitos++;
    }
    time.stop();

    escribirSolucion(solucion);
    cout << "Tiempo tardado: " << time.elapsed()/1000.0 << "ms" << endl;
    cout << endl;
    cout << "Intentos realizados: " << no_exitos << endl;
}

//OPCIONAL
void nReinasLasVegasTodas()
{
	//Completar
    int reinas;
    cout << "Introduzca el número de reinas: ";
    cin >> reinas;
    
    vector<vector<int>> soluciones;
    
    double tiempo = medirTiempo(reinas, soluciones);

    escribirSoluciones(soluciones);
    cout << "Tiempo tardado: " << tiempo << "ms = " << tiempo/1000.0  << "s"
         << endl;
}
