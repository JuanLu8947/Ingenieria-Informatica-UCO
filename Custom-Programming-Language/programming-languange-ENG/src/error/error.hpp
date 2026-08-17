/*! 
  \file error.hpp
  \brief Prototypes of error recovery functions 
*/

#ifndef _ERROR_HPP_
#define _ERROR_HPP_

#include <string>

/*! 
	\brief  Parser error recovery function
	\return void
	\param  errorMessage: Parser error message
	\sa     warning
*/
void yyerror(std::string errorMessage);

/*! 
	\brief  Show the error messages
	\return void
	\param  errorMessage1: first error message
	\param  errorMessage2: second error message
	\sa     yyerror, execerror
*/
void warning(std::string errorMessage1,std::string errorMessage2);


/*! 
	\brief  Run time error recovery function
	\return void
	\param  errorMessage1: first error message
	\param  errorMessage2: second error message
	\sa     warning, longjmp
*/
void execerror(std::string errorMessage1,std::string errorMessage2);


/*! 
	\brief  Run time error recovery function
	\return void
	\param  p 
	\sa     warning
*/
void fpecatch(int p);

// NEW in example 13

/*! 
	\brief  Control EDOM or ERANGE errors
	\param  d: double
	\param  s: 
	\return If an EDOM or ERANGE error has occurred, an error message is displayed; otherwise it returns the value "d"
	\sa     execerror
*/
double errcheck(double d, std::string s);


#endif 
