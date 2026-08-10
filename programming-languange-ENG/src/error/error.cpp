/*! 
  \file error.cpp
  \brief Code of error recovery functions 
*/


// cerr, endl
#include <iostream>

#include <string>

/*  longjmp */
#include <setjmp.h>

// ERANGE, EDOM
#include <errno.h>

#include "error.hpp"

// Macros for the screen
#include "../includes/macros.hpp"

extern int lineNumber; //!< // Reference to line counter

extern std::string progname; //!<  Reference to program name

extern jmp_buf begin; //!< Used for error recovery 

// NEW
extern int errno; //!<  ReferenceReference to the global variable that controls errors in the mathematical code


void warning(std::string errorMessage1,std::string errorMessage2)
{
  std::cerr << IGREEN; 
  std::cerr << " Program: " << progname << std::endl;
  std::cerr << BIRED; 
  std::cerr << " Error line " << lineNumber 
            << " --> " << errorMessage1 << std::endl;
  std::cerr << RESET; 


  if (errorMessage2.compare("")!=0)
		 std::cerr << "\t" << errorMessage2 << std::endl;
}

void yyerror(std::string errorMessage)
{
	warning("Parser error",errorMessage);
}


void execerror(std::string errorMessage1,std::string errorMessage2)
{
 warning(errorMessage1,errorMessage2); 

 longjmp(begin,0); /* return to a viable state */
}

void fpecatch(int signum)     
{
 execerror("Run time","floating point error");
}



// NEW in example 13
double errcheck(double d, std::string s)
{
  if (errno==EDOM)
    {
     errno=0;
     std::string msg("Runtime error --> argument out of domain");
 
     std::cout << msg << std::endl;
     execerror(s,msg);
    }
   else if (errno==ERANGE)
           {
		 	std::string msg("Runtime error --> result out of range");
            errno=0;
            execerror(s,msg);
           }

 return d;
}



