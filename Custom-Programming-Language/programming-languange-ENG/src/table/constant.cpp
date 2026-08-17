/*!	
	\file    constant.cpp
	\brief   Code of some functions of Constant class
	\author 
	\date    2017-10-19
	\version 1.0
*/


#include <iostream>

#include "constant.hpp"



/*
	Operator
*/

lp::Constant &lp::Constant::operator=(const lp::Constant &c)
  {
 	// Check that is not the current object
		if (this != &c) 
		{
			// Inherited methods
			this->setName(c.getName());

			this->setToken(c.getToken());

		    //  Own method
			this->setType(c.getType());
		}

    // Return the current object
		return *this;
  }


/*	
  	I/O Functions
*/
	

void lp::Constant::read()
{
  // Inherited attributes
   std::cout << "Name of the Constant: ";
   std::cin >> this->_name;

   std::cout << "Token of the Constant: ";
   std::cin >> this->_token;
   // The \n character is read 
   std::cin.ignore(); 

  // Own attribute
   std::cout << "Type of the Constant: ";
   std::cin >> this->_type;
   // The \n character is read 
   std::cin.ignore(); 

}


void lp::Constant::write() const
{
  // Inherited methods
  std::cout << "Name:" << this->getName() << std::endl;
  std::cout << "Token:" << this->getToken() << std::endl;

  //  Own method
  std::cout << "Token:" << this->getType() << std::endl;

}


