/**
 * @file dos_detector.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include "system.hpp"


/**
 * @brief Run the DOS detection algorithm.
 * @arg log is the system's log.
 * @arg max_acc is the number max of accesses per hour allowed.
 * @arg m is the initial size of the hash table.
*/
void dos_detector(Log &log, int max_acc, size_t m);
