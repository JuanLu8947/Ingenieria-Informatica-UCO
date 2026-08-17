/*! 
  \file mathFunction.cpp
  \brief Code of mathematical functions 
*/


#include <iostream>

#include <string>

// rand, RAND_MAX
#include <stdlib.h>


// sin, cos, atan, fabs, ...
#include <math.h>

#include "mathFunction.hpp"

// errcheck
#include "../error/error.hpp"

double Log(double x)
{
 std::string msg("Neperian logarithm");
 return errcheck(log(x),msg);
 }


double Log10(double x)
{
 std::string msg("Decimal logarithm");
 return errcheck(log10(x),msg);
}


double Exp(double x)
{
 std::string msg("Exponential");

 return errcheck(exp(x),msg);
}

double Sqrt(double x)
{
 std::string msg("Square root");
 return errcheck(sqrt(x),msg);
}


double integer(double x)
{
 return  (double) (long) x;
}


////////////////////////////////

double Random()
{
 srand (time(NULL));

 return (double) (long) rand() / RAND_MAX;
}


///////////////////////////////

double Atan2(double x, double y)
{
 return errcheck(atan(x/y),"double tangent arc");
}





