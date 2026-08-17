/*! 
  \file mathFunction.hpp
  \brief Prototypes of mathematical functions 
*/

#ifndef _MATHFUNCTION_HPP_
#define _MATHFUNCTION_HPP_

#include <string>

/*!	
	\brief   Compute the neperian logarithm of a real number
	\note    Check first if there is an error in the argument.
	\param	 x: double
	\return  log(x)
	\sa		 errcheck, log
*/
double Log(double x);

/*!	
	\brief   Compute the decimal logarithm of a real number
	\note    Check first if there is an error in the argument.
	\param	 x: double
	\return  log10(x)
	\sa		 errcheck, log10
*/
double Log10(double x);

/*!	
	\brief   Compute the exponential of a real number
	\note    Check first if there is an error in the argument.
	\param	 x: double
	\return  exp(x)
	\sa		 errcheck, exp
*/
double Exp(double x);

/*!	
	\brief   Compute the square root of a real number
	\note    Check first if there is an error in the argument.
	\param	 x: double
	\return  sqrt(x)
	\sa		 errcheck, sqrt
*/
double Sqrt(double x);


/*!	
	\brief   Compute the integer part a real number
	\param	 x: double
	\return  (double) (long) x;
	\sa		 
*/
double integer(double x);

/////////////////////////////////
/*!	
	\brief   Compute a random number
	\return  (double) (long) rand() / RAND_MAX;
	\sa		 
*/
double Random();



////////////////////////////////

/*!	
	\brief   Compute the atan(x/y) 
	\param	 x: double
	\param	 y: double
	\return  atan(x/y)
	\sa		 
*/
double Atan2(double x, double y);



#endif
