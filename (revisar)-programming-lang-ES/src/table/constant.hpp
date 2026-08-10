/*!	
	\file    constant.hpp
	\brief   Declaration of Constant class
	\author  
	\date    2017-12-5
	\version 1.0
*/

#ifndef _CONSTANT_HPP_
#define _CONSTANT_HPP_

#include <string>
#include <iostream>

#include "symbol.hpp"

/*!	
	\namespace lp
	\brief Name space for the subject Language Processors
*/
namespace lp{

/*!	
  \class     Constant
  \attention Abstrac class
  \brief     Definition of atributes and methods of Constant class
  \note      Constant Class publicly inherits from Symbol class
*/
class Constant:public lp::Symbol
{
/*!		
\name Protected atribute of Constant class
*/
	protected:
		int      	_type;    //!< \brief Type of the  Constant: NUMERICVAR, STRINGVAR

/*!		
\name Public methods of Constant class
*/
	public:

/*!	
	\name Constructors
*/
		
/*!		
	\brief Constructor with arguments with default values
	\note  Inline function that uses Symbol's constructor as members initializer
	\param name: name of the Constant
	\param token: token of the Constant
	\param type: type of the Constant
	\pre   None
	\post  A new Constant is created with the values of the parameters
	\sa   setName, setToken, setType
*/
	inline Constant(std::string name="", int token = 0, int type = 0): Symbol(name,token)
	{
		this->setType(type);
	}
		
/*!		
	\brief Copy constructor
	\note  Inline function
	\param c: object of Constant class
	\pre   None
	\post  A new Constant is created with the values of an existent Constant
	\sa    setName, setValue
*/
	inline Constant(const Constant & c)
	{
		// Inherited methods
		this->setName(c.getName());
		this->setToken(c.getToken());

		//  Own method
		this->setType(c.getType());
	}


/*!	
	\name Observer
*/

/*!
	\brief   Public method that returns the type of the Constant
	\note    Inline function
	\pre     None
	\post    None
	\return  int Type of the Constant
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
	\brief   This functions modifies the token of the Constant
	\note    Función inline
	\param   type: new type of the Constant
	\pre     None
	\post    The type of the Constant is equal to the parameter 
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
	\param  c: objecto of Constant class
	\post   The atributes of this object are equal to the atributes of the parameter
	\return Reference to this object
*/
	Constant &operator=(const Constant &c);
		

		
/*!	
	\name I/O Functions
*/
		

/*!		
	\brief Write a Constant
	\note  Virtual method: can be redefined in the heir class
	\pre   None
	\post  None
    \sa    read
*/
	virtual void write() const;


/*!		
	\brief   Read a Constant
	\note    Virtual method: can be redefined in the heir class
	\pre     None
	\post    The atributes of the Constant are modified with the read values
    \sa      writeS
*/
	virtual void read();

	
// End of Constant class
};

// End of name space lp
}

// End of _CONSTANT_HPP_
#endif
