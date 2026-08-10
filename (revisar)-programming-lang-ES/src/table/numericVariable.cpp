/*!	
	\file    numericVariable.cpp
	\brief   Code of some functions of NumericVariable class
	\author 
	\date    2017-10-19
	\version 1.0
*/


#include <iostream>

// Delete the comment if you want to use atof in the operator overload >>
// #include <stdlib.h>

#include "numericVariable.hpp"


/*
 Definitions of the read and write functions of the NumericVariable class 
*/

void lp::NumericVariable::read()
{
  // Inherited attributes
   std::cout << "Name of the NumericVariable: ";
   std::cin >> this->_name;

   std::cout << "Token of the NumericVariable: ";
   std::cin >> this->_token;
   // The \n character is read 
   std::cin.ignore(); 

   std::cout << "Type of the NumericVariable: ";
   std::cin >> this->_type;
   // The \n character is read 
   std::cin.ignore(); 


   // Own attribute
   std::cout << "Value of the NumericVariable: ";
   std::cin >> this->_value;
   // The \n character is read 
   std::cin.ignore(); 
}


void lp::NumericVariable::write() const
{
  // Inherited methods
  std::cout << "Name:" << this->getName() << std::endl;
  std::cout << "Token:" << this->getToken() << std::endl;
  std::cout << "Type:" << this->getType() << std::endl;

  // Own method
  std::cout << "Value:" << this->getValue() << std::endl;
}

lp::NumericVariable &lp::NumericVariable::operator=(const lp::NumericVariable &n)
  {
 	// Check that is not the current object
		if (this != &n) 
		{
			// Inherited methods
			this->setName(n.getName());

			this->setToken(n.getToken());

			this->setType(n.getType());

			// Own method
			this->setValue(n.getValue());
		}

    // Return the current object
		return *this;
  }


/*!	
	\namespace lp
	\brief Name space for the subject Language Processors
*/
namespace lp{

std::istream &operator>>(std::istream &i, lp::NumericVariable &n)
{
  // Inherited attributes
  i >> n._name;

  i >> n._token;
  // The \n character is read 
  i.ignore();


  i >> n._type;
  // The \n character is read 
  i.ignore();


  i >> n._token;
  // The \n character is read 
  i.ignore();

  ////////////////////////////////////

  // Own attribute

  i >> n._value;
  // The \n character is read 
  i.ignore();

  ////////////////////////////////////

/* Alternative way using an auxiliar string 

  std::string auxiliar;

  std::getline(i,auxiliar);
  n._token = atof(auxiliar.c_str());

  std::getline(i,auxiliar);
  n._type = atof(auxiliar.c_str());

  std::getline(i,auxiliar);
  n._value = atof(auxiliar.c_str());

*/

  // The input stream is returned
  return i;
}


std::ostream &operator<<(std::ostream &o, lp::NumericVariable const &n)
{
  // Inherited attributes
  o << n._name << std::endl;

  o << n._token << std::endl;

  o << n._type << std::endl;

  // Own attribute
  o << n._value << std::endl;

  // The output stream is returned
  return o;
}

// End of name space lp
} 




