#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "funcionesGrafos.hpp"


using namespace std;

//Función que carga las ciudades del fichero
void cargarCiudades(const string nombreFichero, vector<string> &nombres)
{
    string aux;
    ifstream fichero;

    //Abrimos fichero para lectura
    fichero.open(nombreFichero.c_str());
    if (!fichero)
    {
        cout << "No se ha podido abrir el fichero \n";
        exit(0);
    }

    //Leemos el fichero y almacenamos las ciudades en el vector de nombres
    while(fichero >> aux)
        nombres.push_back(aux);

    fichero.close();
}

//Función que muestra las ciudades por pantalla. Se usará para seleccionar la ciudad origen
void mostrarCiudades(const vector<string> &ciudad)
{
    for (size_t i = 0; i < ciudad.size(); i++)
        cout << i << ". " << ciudad[i] << endl;
}

//Función que carga la matriz de conexión del grafo desde un fichero de texto.
//La primera línea contendrá el número de nodos y las siguientes serán las filas de la matriz de conexión.
void cargarMatrizConexion(const string nombreFichero, vector <vector<double> > &matrizConexion)
{
    double aux;
    int ordenMatriz;
    ifstream fichero;

    //Abrimos fichero para lectura
    fichero.open(nombreFichero.c_str());
    if (!fichero)
    {
        cout << "No se ha podido abrir el fichero \n";
        exit(0);
    }
    //Leemos el orden de la matriz de conexion que es el primer registro del fichero
    fichero >> ordenMatriz;

    //Ahora reservamos una matriz de conexión
    matrizConexion = vector< vector< double > >(ordenMatriz, vector< double >(ordenMatriz));

    //Ahora cargamos la matriz desde el fichero, leyéndola por filas
    for(int i = 0; i < ordenMatriz; i++)
        for(int j = 0; j < ordenMatriz; j++)
            fichero >> matrizConexion[i][j];

    fichero.close();
}

//Muestra por pantalla la matriz de conexión
void mostrarMatrizConexion(const vector< vector<double>> &matriz)
{
    int n = matriz.size();

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            cout << matriz[i][j] << "  ";
        cout << endl;
    }
}

//Muestra los números de nodos que conforman el vector camino
void mostrarCamino(vector<int> &camino)
{
    for (int i = 0; i < camino.size(); i++)
        cout << camino[i] << " -> ";
    cout << endl;
}

//Muestra la solución óptima al problema del viajante de comercio.
void mostrarSolucionOptima(const vector<string> &nombresCiudades, const vector< vector<double> > &matrizConexion, vector <int> &camino, double distanciaMinima)
{
    cout <<" El recorrido sería: " << endl;
    for (int i = 0; i < camino.size() - 1; i++)
    {
        cout << nombresCiudades[camino[i]] << " -> " << nombresCiudades[camino[i + 1]] << "  " << matrizConexion[camino[i]][camino[i + 1]] << "km" << endl;
    }
    cout << nombresCiudades[camino[camino.size() - 1]] << " -> " << nombresCiudades[camino[0]] << "  " << matrizConexion[camino[camino.size() - 1]][camino[0]] << "km" << endl;

    cout << "El recorrido total son " << distanciaMinima << " km." << endl;
}

//Muestra todos los ciclos hamiltonianos del grafo contenidos en la matriz ciclosHamiltonianos
void mostrarCiclosHamiltonianos(const vector<string> &nombresCiudades, const vector< vector<int> > &ciclosHamiltonianos)
{
    for (int i = 0; i < ciclosHamiltonianos.size(); i++)
    {
        cout <<" CICLO " << i + 1 << " : " << endl;
        for (int j = 0; j < ciclosHamiltonianos[i].size(); j++)
            cout << nombresCiudades[ciclosHamiltonianos[i][j]] << " -> ";
        cout << nombresCiudades[ciclosHamiltonianos[i][0]] << endl;
    }
}

//Esta funcion suma las distancias que componen un camino. En caso de que el camino contenga a todos los nodos y
//forme un ciclo, calcula la longitud del ciclo hamiltoniano ya que añade el lado que cierra el camino.

double sumarDistancias(const vector< vector<double> > &matrizConexion, vector <int> &camino)
{
    double distancia = 0.0;
    
    for (int i = 0; i < camino.size() - 1; i++)
        distancia += matrizConexion[camino[i]][camino[i + 1]];
    
    if (camino.size() == matrizConexion.size())
        //Se ha completado el ciclo y hay que sumar el lado que cierra
        distancia += matrizConexion[camino[camino.size() - 1]][camino[0]];

    return distancia;
}

//Esta función obtiene el siguiente nodo cuando se está calculando un ciclo Hamiltoniano 
//o cuando se está resolviendo el problema del viajante de comercio.
int siguienteNodo(const vector< vector<double> > &m, vector <int> caminoActual, vector <int> &caminoAnterior, vector<bool> visitado)
{
    int n = m.size();

    int iInicial;

    if (caminoAnterior.size() == caminoActual.size()) //Aun no se ha pasado por ahí en la exploración del grafo
        iInicial = 0;
    else 
    // Estamos en la vuelta atrás de la recursividad y se ha pasado por ahí en la exploración del grafo. 
    // Hay que inicializar la i en el nodo siguiente por el que pasó anteriormente.
    {
        iInicial =  caminoAnterior[caminoActual.size()] + 1;
        //Se actualiza el camino anterior para comenzar las exploraciones de nuevo, desde el nuevo nodoinicial;
        caminoAnterior = caminoActual;
    } 

    for(int i = iInicial; i < n; i++)
    {
        if (visitado[i] == false && m[caminoActual[caminoActual.size() - 1]][i] < 10000000.0) //Nodo no visitado y conectado al último visitado
        {
            if (caminoActual.size() < n - 1) //Aún no se ha llegado al último nodo
                return i;
            else //Se ha llegado al último y hay que comprobar si está conectado al primero
            {
                if (m[i][caminoActual[0]] < 10000000.0) //Está conectado al primero y cierra el ciclo
                    return i;
            }
        }
         //En caso contrario no se sigue por ese camino
    }
    return -1; //No ha encontrado ningún nodo no visitado
}

//Esta función calcula todos los ciclos Hamiltonianos de un grafo.
void obtenerCiclosHamiltonianos(const vector< vector<double> > &m, vector< vector<int> > &ciclos,  
    vector <int> caminoActual, vector <int> &caminoAnterior, vector<bool> visitado, int ciudadOrigen)
{
    int siguiente;

    if (caminoAnterior.size() == caminoActual.size()) //El camino anterior es similar al actual y se incrementa con el actual
        caminoAnterior.push_back(ciudadOrigen);

    //La ciudad origen se añade al camino actual
    caminoActual.push_back(ciudadOrigen);

    //Marcamos como visitada la ciudad origen
    visitado[ciudadOrigen] = true;
    while(1)
    {

        siguiente = siguienteNodo(m, caminoActual, caminoAnterior, visitado);        
        
        if (siguiente == -1 /*and caminoActual.size() == m.size()*/) //No se puede seguir por ese camino
        {
            if (caminoActual.size() == m.size()) //Se ha completado un ciclo y se almacena
                ciclos.push_back(caminoActual);

            break;
        }
        else //Proseguimos la búsqueda del ciclo a partir del último nodo encontrado
            obtenerCiclosHamiltonianos(m, ciclos, caminoActual, caminoAnterior, visitado, siguiente);
    }
}

//Esta función obtiene la solución óptima del problema del viajante de comercio por backtracking.
void obtenerSolucionOptimaSinPoda(const vector< vector<double> > &m, vector <int> caminoActual, vector <int> &caminoAnterior, vector <int> &caminoOptimo, 
                                    double distanciaActual, double &distanciaOptima, vector<bool> visitado, int ciudadOrigen)
{
    int siguiente;

    if (caminoAnterior.size() == caminoActual.size()) //El camino anterior es similar al actual y se incrementa con el actual
        caminoAnterior.push_back(ciudadOrigen);

    //La ciudad origen se añade al camino actual
    caminoActual.push_back(ciudadOrigen);

    //Marcamos como visitada la ciudad origen
    visitado[ciudadOrigen] = true;

    while(1)
    {
        siguiente = siguienteNodo(m, caminoActual, caminoAnterior, visitado);        
        
        if (siguiente == -1 /*and caminoActual.size() == m.size()*/) //No se puede seguir por ese camino
        {
            if (caminoActual.size() == m.size()){
                //Completar examen
                //calc dist tot y si es mas optima -> actu
                double dist = sumarDistancias(m, caminoActual);

                if(dist < distanciaOptima){
                    distanciaOptima = dist;
                    caminoOptimo = caminoActual;
                }
            }

            break;
        }
        else{
            //Completar examen
            obtenerSolucionOptimaSinPoda(m, caminoActual, caminoAnterior, caminoOptimo, distanciaActual, distanciaOptima, visitado, siguiente);
        }
    }
}

//OPCIONAL. Esta función obtiene la solución óptima del problema del viajante de comercio por Backtracking usando poda para acelerar el proceso.
void obtenerSolucionOptimaConPoda(const vector< vector<double> > &m, vector <int> caminoActual, vector <int> &caminoAnterior, vector <int> &caminoOptimo, 
                                    double distanciaActual, double &distanciaOptima, vector<bool> visitado, int ciudadOrigen)
{
    //Completar
    int siguiente;

    if (caminoAnterior.size() == caminoActual.size()) //El camino anterior es similar al actual y se incrementa con el actual
        caminoAnterior.push_back(ciudadOrigen);

    //La ciudad origen se añade al camino actual
    caminoActual.push_back(ciudadOrigen);

    //Marcamos como visitada la ciudad origen
    visitado[ciudadOrigen] = true;

    //Actualizamos la distancia actual
    if (caminoActual.size() > 1)
        distanciaActual += m[caminoActual[caminoActual.size() - 2]][ciudadOrigen];
    
    //PODA: Si la distancia actual ya supera la óptima, no seguimos explorando
    if (distanciaActual >= distanciaOptima)
        return;

    while(true){
        siguiente = siguienteNodo(m, caminoActual, caminoAnterior, visitado);        
        
        if (siguiente == -1 /*and caminoActual.size() == m.size()*/){ //No se puede seguir por ese camino
            if (caminoActual.size() == m.size()){ //Se ha completado un ciclo y se almacena
                //Usamos la función sumarDistancias para calcular la distancia total del ciclo
                double distanciaTotal = sumarDistancias(m, caminoActual);
                
                //Si es mejor que la óptima actual, actualizamos
                if (distanciaTotal < distanciaOptima){
                    distanciaOptima = distanciaTotal;
                    caminoOptimo = caminoActual;
                }
            }
            break;
        }
        else //Proseguimos la búsqueda del ciclo a partir del último nodo encontrado
            obtenerSolucionOptimaSinPoda(m, caminoActual, caminoAnterior, caminoOptimo, distanciaActual, distanciaOptima, visitado, siguiente);
    }
}

