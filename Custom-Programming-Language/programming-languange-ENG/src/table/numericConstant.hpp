/*!	
	\file    numericConstant.hpp
	\brief   Declaration of NumericConstant class
	\author  
	\date    2017-12-5
	\version 1.0
*/

#ifndef _NUMERICCONSTANT_HPP_
#define _NUMERICCONSTANT_HPP_

#include <string>
#include <iostream>

#include "constant.hpp"

/*!	
	\namespace lp
	\brief Name space for the subject Language Processors
*/
namespace lp{

/*!	
  \class NumericConstant
  \brief Definition of atributes and methods of NumericConstant class
  \note  NumericConstant Class publicly inherits from Constant class
*/
class NumericConstant:public lp::Constant
{
/*!		
\name Private atributes of NumericConstant class
*/
	private:
		double      _value;   //!< \brief Numeric value of the NumericConstant

/*!		
\name Public methods of NumericConstant class
*/
	public:

/*!	
	\name Constructors
*/
		
/*!		
	\brief Constructor with arguments with default values
	\note  Inline function that uses Constant's constructor as members initializer
	\param name: name of the NumericConstant
	\param token: token of the NumericConstant
	\param type: type of the NumericConstant
	\param value: numeric value of the NumericConstant
	\pre   None
	\post  A new NumericConstant is created with the values of the parameters
	\sa   setName, setValue
*/
	inline NumericConstant(std::string name="", int token = 0, int type = 0, double value=0.0): 
 	Constant(name,token,type)
	{
		this->setValue(value);
	}
		
/*!		
	\brief Copy constructor
	\note  Inline function
	\param n: object of NumericConstant class
	\pre   None
	\post  A new NumericConstant is created with the values of an existent NumericConstant
	\sa    setName, setValue
*/
	NumericConstant(const NumericConstant & n)
	{
		// Inherited methods
		this->setName(n.getName());

		this->setToken(n.getToken());

		this->setType(n.getType());
		
		// Own method
		this->setValue(n.getValue());
	}


/*!	
	\name Observer
*/
	
/*!	
	\brief  Public method that returns the value of the NumericConstant
	\note   Función inline
	\pre    None
	\post   None
    \return Value of the NumericConstant
	\sa		getValue
*/
	inline double getValue() const
	{
		return this->_value;
	}



/*!	
	\name Modifier
*/
		
/*!	
	\brief   This functions modifies the value of the NumericConstant
	\note    Inline function
	\param   value: new value of the NumericConstant
	\pre     None
	\post    The value of the NumericConstant is equal to the parameter 
	\return  void
	\sa 	 setValue
*/
	inline void setValue(const double & value)
	{
	    this->_value = value;
	}



		
/*!	
	\name I/O Functions
*/
		
/*!		
	\brief Read a NumericConstant
	\pre   None
	\post  The atributes of the NumericConstant are modified with the read values
    \sa    write
*/
	void read();

	
/*!		
	\brief Write a NumericConstant
	\pre   None
	\post  None
    \sa    read
*/
	void write() const;


/*!	
	\name Operators
*/
	
/*!		
	\brief  Assignment Operator
	\param  n: objectoof NumericConstant class
	\post   The atributes of this object are equal to the atributes of the parameter
	\return Reference to this object
*/
	NumericConstant &operator=(const NumericConstant &n);
	

 //! \name Friend functions
/*!		
	\brief  Insertion operator
	\param  i: input stream
	\param  n: object of NumericConstant class
	\pre    nome
	\post   The atributes of the NumericConstant are modified with the inserted values from the input stream
	\return The input stream
*/
	friend std::istream &operator>>(std::istream &i, NumericConstant &n);

/*!		
	\brief  Extraction operator
	\param  o: output stream
	\param  n: object of NumericConstant class
	\pre    nome
	\post   The atributes of the NumericConstant are written in the output stream
	\return The output stream
*/
	friend std::ostream &operator<<(std::ostream &o, NumericConstant const &n);
	
// End of NumericConstant class
};

// End of name space lp
}

// End of _NUMERICCONSTANT_HPP_
#endif
