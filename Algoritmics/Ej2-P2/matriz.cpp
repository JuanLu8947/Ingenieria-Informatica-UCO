#include "matrizOpcional.hpp"

Matriz::Matriz(unsigned int f, unsigned int c)
{
    //Completar //Constructor de copia
    _f = f;
    _c = c;
    _m.resize(f);
    for(unsigned int i = 0; i < f; i++)
        _m[i].resize(c, 0.0);  // Inicializar con ceros
};

Matriz::Matriz() : _f(0), _c(0) {}

Matriz::~Matriz() {}

// Métodos de acceso
unsigned int Matriz::getFilas() const
{
    return _f;
}

unsigned int Matriz::getColumnas() const
{
    return _c;
}

void Matriz::setElemento(unsigned int i, unsigned int j, double x)
{
    assert(i < _f and j < _c);
    _m[i][j] = x;
};

double Matriz::getElemento(unsigned int i, unsigned int j) const
{
    assert(i < _f and j < _c);
    return _m[i][j];
};


void Matriz::rellenarMatrizAleatoria()
{
    assert(_f > 0 and _c > 0);
    double signo = -1.0;
    
    for (unsigned int i = 0; i < getFilas(); i++)
        for (unsigned int j = 0; j < getColumnas(); j++)
        {
            if (rand() % 2 == 1)
                signo = -signo;
            setElemento(i, j, signo * (signo * (((1.0 * std::rand()) / RAND_MAX) * 0.000001) + 1.0));
        }
};

void Matriz::rellenarMatrizUnidad()
{
    assert(_f > 0 and _c > 0);
    //Completar examen
    for(unsigned int i=0; i<getFilas(); i++)
        for(unsigned int j=0; j<getColumnas(); j++){
            if(i == j)
                setElemento(i, j, 1.0);
            else
                setElemento(i, j, 0.0);
        }
};

ostream &operator << (ostream &salida, Matriz &z)
{
    salida.setf(ios::fixed);
    salida.precision(4);    
 
    for (unsigned int i = 0; i < z.getFilas(); i++)
    {
        for (unsigned int j = 0; j < z.getColumnas() ; j++) 
            salida << setw(20) << z.getElemento(i, j) << " ";
        salida << "\n";
    }
    return salida;
};

Matriz operator + (const Matriz &x, const Matriz &y)
{
 
    assert(x.getFilas() == y.getFilas() and x.getColumnas() == y.getColumnas());
 
    Matriz suma(x.getFilas(), x.getColumnas());

    for (unsigned int i = 0; i < x.getFilas(); i++)
        for (unsigned int j = 0; j < x.getColumnas() ; j++) 
            suma.setElemento(i, j, x.getElemento(i, j) + y.getElemento(i, j)); 
    
    return suma;
 
};

Matriz operator * (const Matriz &x, const Matriz &y)
{
    //Completar
    assert(x.getColumnas() == y.getFilas()); // A(m,n) * B(n,p) = C(m,p);

    Matriz resultado(x.getFilas(), y.getColumnas());

    for (unsigned int i = 0; i < x.getFilas(); i++) {
        for (unsigned int j = 0; j < y.getColumnas(); j++) {
            double sum = 0.0;
            for (unsigned int k = 0; k < x.getColumnas(); k++){
                sum += x.getElemento(i, k) * y.getElemento(k, j);
            }
            resultado.setElemento(i, j, sum);
        }
    }
    return resultado;
};

int opcion = 0;

Matriz Matriz::potencia(const unsigned int &n)const
{
    assert(_f == _c);
    //Completar examen
    if(n == 0){ //A^0 = I
        Matriz identidad(_f, _c); //getfilas(), getColumnas
        identidad.rellenarMatrizUnidad();
        return identidad;
    }
    else if(n == 1){ //A^1 = A
        return *this;
    }
    else{ //A^n = A * A^n-1
        if(opcion != 2){
            cout << "=Elija un metodo para el 1º metodo=" << endl
                << "1. Metodo Iterativo" << endl
                 << "2. Metodo Recursivo" << endl
                 << "Elige opcion: ";
            cin >> opcion;
        }
        if(opcion == 1){
            Matriz resultado = *this;
            for(int i = 1; i < n; i++){
                resultado = *this * resultado;
            }
            return resultado;
        }
        else if(opcion == 2){
            Matriz resultado = this->potencia(n-1);
            return *this * resultado;
        }
    }
};


Matriz Matriz::potenciaDyV1(const unsigned int &n)const
{
    assert(_f == _c);
    //Completar examen
    if(n == 0){ //A^0 = I
        Matriz identidad(_f, _c); //getfilas(), getColumnas
        identidad.rellenarMatrizUnidad();
        return identidad;
    }
    else if(n == 1){ //A^1 = A
        return *this;
    }
    else if(n%2==0){ //A^n = A^n/2 * A^n/2 = A^2k
        Matriz resultado = this->potenciaDyV1(n/2); //A^n/2
        return resultado * resultado;
    }
    else{ //A^n = A * A^2k //se convierte en un caso par
        return *this * this->potenciaDyV1(n-1);
    }
};

Matriz Matriz::potenciaDyV2(const unsigned int &n)const
{
    assert(_f == _c);
    //Completar examen
    if(n == 0){ //A^0 = I
        Matriz identidad(_f, _c); //getfilas(), getColumnas
        identidad.rellenarMatrizUnidad();
        return identidad;
    }
    else if(n == 1){ //A^1 = A
        return *this;
    }
    //suponemos todo como par
    Matriz resultado = this->potenciaDyV2(n/2);
    resultado = resultado * resultado;
    if(n%2!=0){ //ahora bien si fuera impar;
        resultado = *this * resultado;
    }
    return resultado;
};

bool operator == (const Matriz &x, const Matriz &y)
{
 
    assert(x.getFilas() == y.getFilas() and x.getColumnas() == y.getColumnas());
 
    for (unsigned int i = 0; i < x.getFilas(); i++)
        for (unsigned int j = 0; j < x.getColumnas() ; j++)
            if (fabs(x.getElemento(i, j)- y.getElemento(i, j)) > 0.0000001)
                return false; 
    
    return true;
};
