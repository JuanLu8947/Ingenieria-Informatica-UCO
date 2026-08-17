#ifndef AUXILIARES_HPP
#define AUXILIARES_HPP

#include <string>
#include "serietemporal.hpp"

using namespace std;

bool cargarDatos(string &nameF, int &nPuntosSegmentados);
void mostrarResultados(SerieTemporal &serie, long double ISE, long double errorMax, int puntoErrorMax, double tiempo);
void guardarSegmentacion(const SerieTemporal &serie, const string &nameF);

#endif