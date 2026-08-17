/*!	
	\file    logicalConstant.hpp
	\brief   Declaration of LogicalConstant class
	\author  
	\date    2017-12-5
	\version 1.0
*/

#ifndef _LOGICALCONSTANT_HPP_
#define _LOGICALCONSTANT_HPP_

#include <string>
#include <iostream>

#include "constant.hpp"

/*!	
	\namespace lp
	\brief Name space for the subject Language Processors
*/
namespace lp{

/*!	
  \class LogicalConstant
  \brief Definition of atributes and methods of LogicalConstant class
  \note  LogicalConstant Class publicly inherits from Constant class
*/
class LogicalConstant:public lp::Constant
{
/*!		
\name Private atributes of LogicalConstant class
*/
	private:
		bool	_value;   //!< \brief Logical value of the LogicalConstant

/*!		
\name Public methods of LogicalConstant class
*/
	public:

/*!	
	\name Constructors
*/
		
/*!		
	\brief Constructor with arguments with default values
	\note  Inline function that uses Constant's constructor as members initializer
	\param name: name of the LogicalConstant
	\param token: token of the LogicalConstant
	\param type: type of the LogicalConstant
	\param value: logical value of the LogicalConstant
	\pre   None
	\post  A new LogicalConstant is created with the values of the parameters
	\sa   setName, setValue
*/
	inline LogicalConstant(std::string name="", int token = 0, int type = 0, bool value=true): 
 	Constant(name,token,type)
	{
		this->setValue(value);
	}
		
/*!		
	\brief Copy constructor
	\note  Inline function
	\param n: object of LogicalConstant class
	\pre   None
	\post  A new LogicalConstant is created with the values of an existent LogicalConstant
	\sa    setName, setValue
*/
	LogicalConstant(const LogicalConstant & n)
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
	\brief  Public method that returns the value of the LogicalConstant
	\note   Función inline
	\pre    None
	\post   None
    \return Value of the LogicalConstant
	\sa		getValue
*/
	inline bool getValue() const
	{
		return this->_value;
	}



/*!	
	\name Modifier
*/
		
/*!	
	\brief   This functions modifies the value of the LogicalConstant
	\note    Inline function
	\param   value: new value of the LogicalConstant
	\pre     None
	\post    The value of the LogicalConstant is equal to the parameter 
	\return  void
	\sa 	 setValue
*/
	inline void setValue(const bool & value)
	{
	    this->_value = value;
	}



		
/*!	
	\name I/O Functions
*/
		
/*!		
	\brief Read a LogicalConstant
	\pre   None
	\post  The atributes of the LogicalConstant are modified with the read values
    \sa    write
*/
	void read();

	
/*!		
	\brief Write a LogicalConstant
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
	\param  n: objectoof LogicalConstant class
	\post   The atributes of this object are equal to the atributes of the parameter
	\return Reference to this object
*/
	LogicalConstant &operator=(const LogicalConstant &n);
	

 //! \name Friend functions
/*!		
	\brief  Insertion operator
	\param  i: input stream
	\param  n: object of LogicalConstant class
	\pre    nome
	\post   The atributes of the LogicalConstant are modified with the inserted values from the input stream
	\return The input stream
*/
	friend std::istream &operator>>(std::istream &i, LogicalConstant &n);

/*!		
	\brief  Extraction operator
	\param  o: output stream
	\param  n: object of LogicalConstant class
	\pre    nome
	\post   The atributes of the LogicalConstant are written in the output stream
	\return The output stream
*/
	friend std::ostream &operator<<(std::ostream &o, LogicalConstant const &n);
	
// End of LogicalConstant class
};

// End of name space lp
}

// End of _LOGICALCONSTANT_HPP_
#endif
