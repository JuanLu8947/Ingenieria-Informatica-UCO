/*!	
	\file    variable.hpp
	\brief   Declaration of Variable class
	\author  
	\date    2017-12-1
	\version 1.0
*/

#ifndef _VARIABLE_HPP_
#define _VARIABLE_HPP_

#include <string>
#include <iostream>

#include "symbol.hpp"

/*!	
	\namespace lp
	\brief Name space for the subject Language Processors
*/
namespace lp{

/*!	
  \class     Variable
  \attention Abstrac class
  \brief     Definition of atributes and methods of Variable class
  \note      Variable Class publicly inherits from Symbol class
*/
class Variable:public lp::Symbol
{
/*!		
\name Protected atribute of Variable class
*/
	protected:
		int      	_type;    //!< \brief Type of the  Variable: UNDEFINED, NUMERICVAR, STRINGVAR, LOGICALVAR

/*!		
\name Public methods of Variable class
*/
	public:

/*!	
	\name Constructors
*/
		
/*!		
	\brief Constructor with arguments with default values
	\note  Inline function that uses Symbol's constructor as members initializer
	\param name: name of the Variable
	\param token: token of the Variable
	\param type: type of the Variable
	\pre   None
	\post  A new Variable is created with the values of the parameters
	\sa   setName, setToken, setType
*/
	inline Variable(std::string name="", int token = 0, int type = 0): Symbol(name,token)
	{
		this->setType(type);
	}
		
/*!		
	\brief Copy constructor
	\note  Inline function
	\param s: object of Variable class
	\pre   None
	\post  A new Variable is created with the values of an existent Variable
	\sa    setName, setValue
*/
	inline Variable(const Variable & s)
	{
		// Inherited methods
		this->setName(s.getName());
		this->setToken(s.getToken());

		//  Own method
		this->setType(s.getType());
	}


/*!	
	\name Observer
*/

/*!
	\brief   Public method that returns the type of the Variable
	\note    Inline function
	\pre     None
	\post    None
	\return  int Type of the Variable
	\sa		 getName, getToken
*/
	inline int getType() const
	{
		return this->_type;
	}	


/*!	
	\name Modifier
*/


/*!	
	\brief   This functions modifies the token of the Variable
	\note    Función inline
	\param   type: new type of the Variable
	\pre     None
	\post    The type of the Variable is equal to the parameter 
	\return  void
	\sa 	 setName, setToken
*/
	inline void setType(int type) 
	{
	    this->_type = type;
	}


/*!	
	\name Operator
*/
	
/*!		
	\brief  Assignment Operator
	\param  v: objecto of Variable class
	\post   The atributes of this object are equal to the atributes of the parameter
	\return Reference to this object
*/
	Variable &operator=(const Variable &v);
		

		
/*!	
	\name I/O Functions
*/
		

/*!		
	\brief Write a Variable
	\note  Virtual method: can be redefined in the heir class
	\pre   None
	\post  None
    \sa    read
*/
	virtual void write() const;


/*!		
	\brief   Read a Variable
	\note   Virtual method: can be redefined in the heir class
	\pre     None
	\post    The atributes of the Variable are modified with the read values
    \sa      writeS
*/
	virtual void read();

	
// End of Variable class
};

// End of name space lp
}

// End of _VARIABLE_HPP_
#endif
