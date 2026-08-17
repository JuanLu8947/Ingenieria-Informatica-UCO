#include "sistemaEcuaciones.hpp"



using namespace std;

void inicializarInversa(vector < vector < double > >  &inversa);
void trianguloInferior(vector < vector < double > > &A, vector < vector < double > > &inversa);
bool  eliminarCero(vector < vector < double > > &A, vector < vector < double > > &inversa, unsigned int x);
void hacerCerosColumna(vector < vector < double > > &A, vector < vector < double > > &inversa, unsigned int x);
void combinarFilas(vector < vector < double > > &matriz, unsigned int filaOrigen, double factor, unsigned int filaDestino);
double productoDiagonal(const vector < vector < double > > &matriz);
void trianguloSuperior(vector < vector < double > > &A, vector < vector < double > > &inversa);
int eliminarCero2(vector < vector < double > > &A, vector < vector < double > > &inversa, unsigned int x);
void hacerCerosColumna2(vector < vector < double > > &A, vector < vector < double > > &inversa, unsigned int x);
void obtenerUnidad(vector < vector < double > > &A, vector < vector < double > > &inversa);
void multiplicarMatrices(const vector < vector < double > > &m1, const vector < vector < double > > &m2, vector < vector < double > > &producto);


void resolverSistemaEcuaciones(vector < vector < double > > A, vector < vector < double > > B, int n, vector < vector < double > > &X)
{
	vector < vector < double > > inversa; //matriz inversa de la matriz de coeficientes que hay que calcular para resolver el sistema.
	inversa = vector< vector< double > >(n, vector< double >(n)); //Matriz de N x N
	
	//Inicializamos la matriz inversa
	inicializarInversa(inversa);

	//Se triangulariza la matriz por debajo de la diagonal
	trianguloInferior(A, inversa);
	
	//Mostramos determinante
	double determinante = productoDiagonal(A);
	
	if (fabs(determinante) < 0.0000000001) //Si el determinante es 0 no hay solución
	{
		exit(0);
	}
	
	//Se triangulariza la matriz por encima de la diagonal
	trianguloSuperior(A,inversa);
	
	obtenerUnidad(A, inversa);
	
	//Se muestra la inversa
	multiplicarMatrices(inversa, B, X);
}

//Funcion para inicializar la matriz inversa que se inicializa con la matriz unidad
	
void inicializarInversa(vector < vector < double > >  &inversa)
{
 
 for(unsigned int i = 0; i < inversa.size(); i++)
  for(unsigned int j = 0; j < inversa.size(); j++)
   {
    if (i == j)
     inversa[i][j] = 1.0;
    else
     inversa[i][j] = 0.0;
   }
}

//Funcion para triangularizar la matriz por debajo de la diagonal principal
void trianguloInferior(vector < vector < double > > &A, vector < vector < double > > &inversa)
{
	bool correcto;
	for(unsigned int i = 0; i < A.size() - 1; i++)
	{
		if (fabs(A[i][i])< 0.0000000001) //Se ha encontrado un 0 en la diagonal principal, hay que eliminarlo
		{
			correcto = eliminarCero(A, inversa, i);
			if (correcto == false)
			{
				exit(0);
			}
		}
		hacerCerosColumna(A, inversa, i);
	}
}

//Funcion para eliminar un cero de la diagonal principal en la fila x
bool  eliminarCero(vector < vector < double > > &A, vector < vector < double > > &inversa, unsigned int x)
{
	unsigned int i;
	bool correcto = false;
	bool salir = false;

	i = x+1;
	while(salir == false)
	{
		if (i == A.size())
			salir = true;
		else if (fabs(A[i][x]) > 0.0000000001) //Comprueba que no es 0
		{
			salir = true;
			correcto = true;
		}
		else
			i = i + 1;
	}
	if (correcto == true)
	{
		combinarFilas(A, i, 1.0, x);
		combinarFilas(inversa, i, 1.0, x);
	}
	return correcto;
}

//Funcion que hace ceros en una columna

void hacerCerosColumna(vector < vector < double > > &A, vector < vector < double > > &inversa, unsigned int x)
{
	double aux;

	for(unsigned int i = x+1; i < A.size(); i++)
	{
		aux = -A[i][x]/A[x][x];
		combinarFilas(A, x, aux, i);
		combinarFilas(inversa, x, aux, i);
	}
}

//Esta funcion se usa para hacer combinaciones lineales en filas en una matriz
// En este caso, la fila origen se multiplica por factor y se suma a la destino
void combinarFilas(vector < vector < double > > &matriz, unsigned int filaOrigen, double factor, unsigned int filaDestino)
{
	for(unsigned int i = 0; i < matriz.size(); i++)
		matriz[filaDestino][i] = matriz[filaDestino][i] + factor * matriz[filaOrigen][i];
}

//Esta función calcula el valor del producto de los elementos de la diagonal principal de la matriz
double productoDiagonal(const vector < vector < double > > &matriz)
{
	double d = 1.0;

	for(unsigned int i = 0; i < matriz.size(); i++)
		d = d * matriz[i][i];

	return d;  
}

//Funcion para triangularizar la matriz por encima de la diagonal principal
void trianguloSuperior(vector < vector < double > > &A, vector < vector < double > > &inversa)
{
	bool correcto;
	for(unsigned int i = A.size() - 1; i > 0; i--)
	{
		if (fabs(A[i][i])< 0.0000000001) //Comprueba que es 0
		{
			correcto = eliminarCero2(A, inversa, i);
			if (correcto == false)
			{
				exit(0);
			}
		}
		hacerCerosColumna2(A, inversa, i);
	}
}

//Funcion para eliminar ceros hacia arriba
int eliminarCero2(vector < vector < double > > &A, vector < vector < double > > &inversa, unsigned int x)
{
	int i;
	bool correcto = false;
	bool salir = false;

	i = x - 1;
	while(salir == false)
	{
		if (i == -1)
			salir = true;
		else if (fabs(A[i][x]) > 0.0000000001)
		{
			salir = true;
			correcto = true;
		}
		else
			i = i - 1;
	}
	if (correcto == true)
	{
		combinarFilas(A, i, 1.0, x);
		combinarFilas(inversa, i, 1.0, x);
	}
	return correcto;
}

//Funcion para hacer ceros en el triángulo superior
void hacerCerosColumna2(vector < vector < double > > &A, vector < vector < double > > &inversa, unsigned int x)
{
	double aux;

	for(int i = x-1; i >= 0; i--)
	{
		aux = -A[i][x] / A[x][x];
		combinarFilas(A, x, aux, i);
		combinarFilas(inversa, x, aux, i);
	}
}

void obtenerUnidad(vector < vector < double > > &A, vector < vector < double > > &inversa)
{
	double aux;

	for(unsigned int i = 0; i < A.size(); i++)
	{
		aux = A[i][i];
		for(unsigned int j = 0; j < A.size(); j++)
		{
			A[i][j] = A[i][j] / aux;
			inversa[i][j] = inversa[i][j] / aux;
		}
	}
}
void multiplicarMatrices(const vector < vector < double > > &m1, const vector < vector < double > > &m2, vector < vector < double > > &producto)
{
	producto.resize(m1.size());
    for (unsigned int i = 0; i < m1.size(); i++) {
        producto[i].resize(m2[0].size());
    }
	for(unsigned int i = 0; i < m1.size(); i++) //Recorre filas de la primera matriz
	{
		for(unsigned int j = 0; j < m2[0].size(); j++) //Recorre columnas de la segunda matriz
		{
			producto[i][j] = 0.0;
			for(unsigned int k = 0; k < m1[0].size(); k++) //Recorre los elementos a multiplicar (numero de columnas de la primera matriz)
				producto[i][j] = producto [i][j] + m1[i][k]*m2[k][j];
		}
	}
}

