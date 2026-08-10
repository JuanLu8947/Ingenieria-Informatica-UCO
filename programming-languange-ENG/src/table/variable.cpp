/*!	
	\file    variable.cpp
	\brief   Code of some functions of Variable class
	\author 
	\date    2017-10-19
	\version 1.0
*/


#include <iostream>

#include "variable.hpp"



/*
	Operator
*/

lp::Variable &lp::Variable::operator=(const lp::Variable &v)
  {
 	// Check that is not the current object
		if (this != &v) 
		{
			// Inherited methods
			this->setName(v.getName());

			this->setToken(v.getToken());

		    //  Own method
			this->setType(v.getType());
		}

    // Return the current object
		return *this;
  }


/*	
  	I/O Functions
*/
	

void lp::Variable::read()
{
  // Inherited attributes
   std::cout << "Name of the Variable: ";
   std::cin >> this->_name;

   std::cout << "Token of the Variable: ";
   std::cin >> this->_token;
   // The \n character is read 
   std::cin.ignore(); 

  // Own attribute
   std::cout << "Type of the Variable: ";
   std::cin >> this->_type;
   // The \n character is read 
   std::cin.ignore(); 

}


void lp::Variable::write() const
{
  // Inherited methods
  std::cout << "Name:" << this->getName() << std::endl;
  std::cout << "Token:" << this->getToken() << std::endl;

  //  Own method
  std::cout << "Token:" << this->getType() << std::endl;

}


