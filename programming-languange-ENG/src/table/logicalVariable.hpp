/*!	
	\file    logicalVariable.hpp
	\brief   Declaration of LogicalVariable class
	\author  
	\date    2017-12-1
	\version 1.0
*/

#ifndef _LOGICALVARIABLE_HPP_
#define _LOGICALVARIABLE_HPP_

#include <string>
#include <iostream>

#include "variable.hpp"

/*!	
	\namespace lp
	\brief Name space for the subject Language Processors
*/
namespace lp{

/*!	
  \class LogicalVariable
  \brief Definition of atributes and methods of LogicalVariable class
  \note  LogicalVariable Class publicly inherits from Variable class
*/
class LogicalVariable:public lp::Variable
{
/*!		
\name Private atributes of LogicalVariable class
*/
	private:
		bool      _value;   //!< \brief Logical value of the LogicalVariable

/*!		
\name Public methods of LogicalVariable class
*/
	public:

/*!	
	\name Constructors
*/
		
/*!		
	\brief Constructor with arguments with default values
	\note  Inline function that uses Variable's constructor as members initializer
	\param name: name of the LogicalVariable
	\param token: token of the LogicalVariable
	\param type: type of the LogicalVariable
	\param value: numeric value of the LogicalVariable
	\pre   None
	\post  A new LogicalVariable is created with the values of the parameters
	\sa   setName(), setValue()
*/
	inline LogicalVariable(std::string name="", int token = 0, int type = 0, bool value=false): 
 	Variable(name,token,type)
	{
		this->setValue(value);
	}
		
/*!		
	\brief Copy constructor
	\note  Inline function
	\param n: object of LogicalVariable class
	\pre   None
	\post  A new LogicalVariable is created with the values of an existent LogicalVariable
	\sa    setName(), setValue()
*/
	LogicalVariable(const LogicalVariable & n)
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
	\brief  Public method that returns the value of the LogicalVariable
	\note   Función inline
	\pre    None
	\post   None
    \return Value of the LogicalVariable
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
	\brief   This functions modifies the value of the LogicalVariable
	\note    Inline function
	\param   value: new value of the LogicalVariable
	\pre     None
	\post    The value of the LogicalVariable is equal to the parameter 
	\return  void
	\sa 	 setValue
*/
	inline void setValue(bool value)
	{
	    this->_value = value;
	}



		
/*!	
	\name I/O Functions
*/
		
/*!		
	\brief Read a LogicalVariable
	\pre   None
	\post  The atributes of the LogicalVariable are modified with the read values
    \sa    write
*/
	void read();

	
/*!		
	\brief Write a LogicalVariable
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
	\param  n: objectoof LogicalVariable class
	\post   The atributes of this object are equal to the atributes of the parameter
	\return Reference to this object
*/
	LogicalVariable &operator=(const LogicalVariable &n);
	

 //! \name Friend functions
/*!		
	\brief  Insertion operator
	\param  i: input stream
	\param  n: object of LogicalVariable class
	\pre    nome
	\post   The atributes of the LogicalVariable are modified with the inserted values from the input stream
	\return The input stream
*/
	friend std::istream &operator>>(std::istream &i, LogicalVariable &n);

/*!		
	\brief  Extraction operator
	\param  o: output stream
	\param  n: object of LogicalVariable class
	\pre    nome
	\post   The atributes of the LogicalVariable are written in the output stream
	\return The output stream
*/
	friend std::ostream &operator<<(std::ostream &o, LogicalVariable const &n);
	
// End of LogicalVariable class
};

// End of name space lp
}

// End of _LOGICALVARIABLE_HPP_
#endif
