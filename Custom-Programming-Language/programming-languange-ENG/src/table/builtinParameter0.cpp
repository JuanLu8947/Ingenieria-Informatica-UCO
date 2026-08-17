/*!	
	\file    builtinParameter0.cpp
	\brief   Code of some functions of BuiltinParameter0 class
	\author 
	\date    2017-10-19
	\version 1.0
*/


#include <iostream>

// Delete the comment if you want to use atof in the operator overload >>
// #include <stdlib.h>

#include "builtinParameter0.hpp"


lp::BuiltinParameter0 &lp::BuiltinParameter0::operator=(const lp::BuiltinParameter0 &f)
  {
 	// Check that is not the current object
		if (this != &f) 
		{
			// Inherited methods
			this->setName(f.getName());

			this->setToken(f.getToken());

			this->setNParameters(f.getNParameters());

			// Own method
			this->setFunction(f.getFunction());
		}

    // Return the current object
		return *this;
  }






