/*!	
	\file    keyword.cpp
	\brief   Code of some functions of Keyword class
	\author 
	\date    2017-10-19
	\version 1.0
*/


#include <iostream>

#include "keyword.hpp"



/*
	Operator
*/

lp::Keyword &lp::Keyword::operator=(const lp::Keyword &k)
  {
 	// Check that is not the current object
		if (this != &k) 
		{
			// Inherited methods
			this->setName(k.getName());

			this->setToken(k.getToken());
		}

    // Return the current object
		return *this;
  }


/*	
  	I/O Functions
*/
	

void lp::Keyword::read()
{
  // Inherited attributes
   std::cout << "Name of the Keyword: ";
   std::cin >> this->_name;

   std::cout << "Token of the Keyword: ";
   std::cin >> this->_token;
   // The \n character is read 
   std::cin.ignore(); 

}


void lp::Keyword::write() const
{
  // Inherited methods
  std::cout << "Name:" << this->getName() << std::endl;
  std::cout << "Token:" << this->getToken() << std::endl;

}


