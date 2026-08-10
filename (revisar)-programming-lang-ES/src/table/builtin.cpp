/*!	
	\file    builtin.cpp
	\brief   Code of some functions of Builtin class
	\author 
	\date    2017-12-7
	\version 1.0
*/


#include <iostream>

#include "builtin.hpp"



/*
	Operator
*/

lp::Builtin &lp::Builtin::operator=(const lp::Builtin &b)
  {
 	// Check that is not the current object
		if (this != &b) 
		{
			// Inherited methods
			this->setName(b.getName());

			this->setToken(b.getToken());

		    //  Own method
			this->setNParameters(b.getNParameters());
		}

    // Return the current object
		return *this;
  }


/*	
  	I/O Functions
*/
	

void lp::Builtin::read()
{
  // Inherited attributes
   std::cout << "Name of the Builtin: ";
   std::cin >> this->_name;

   std::cout << "Token of the Builtin: ";
   std::cin >> this->_token;
   // The \n character is read 
   std::cin.ignore(); 

  // Own attribute
   std::cout << "NParameters of the Builtin: ";
   std::cin >> this->_nParameters;
   // The \n character is read 
   std::cin.ignore(); 

}


void lp::Builtin::write() const
{
  // Inherited methods
  std::cout << "Name:" << this->getName() << std::endl;
  std::cout << "Token:" << this->getToken() << std::endl;

  //  Own method
  std::cout << "Token:" << this->getNParameters() << std::endl;

}


