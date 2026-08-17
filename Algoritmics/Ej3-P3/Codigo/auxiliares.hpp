#ifndef AUXILIARES_HPP
#define AUXILIARES_HPP

#include <string>
#include "serietemporal.hpp"
#include <vector>

using namespace std;

bool cargarDatos(string &nameF, int &nPuntosSegmentados);
void inicializarDominantes(SerieTemporal &Serie, vector<int> &dom);
void mostrarResultados(const SerieTemporal &Serie, const string &nombreMetodo);
void guardarSegmentacion(const SerieTemporal &Serie, const string &nameF, const string &nombreMetodo);

#endif