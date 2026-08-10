/*!	
	\file    builtin.hpp
	\brief   Declaration of Builtin (built-in function) class
	\author  
	\date    2017-12-7
	\version 1.0
*/

#ifndef _BUILTIN_HPP_
#define _BUILTIN_HPP_

#include <string>
#include <iostream>

#include "symbol.hpp"

/*!	
	\namespace lp
	\brief Name space for the subject Language Processors
*/
namespace lp{

/*!	
  \class     Builtin
  \attention Abstrac class
  \brief     Definition of atributes and methods of Builtin class
  \note      Builtin Class publicly inherits from Symbol class
*/
class Builtin:public lp::Symbol
{
/*!		
\name Protected atribute of Builtin class
*/
	protected:
		int      	_nParameters;    //!< \brief Number of parameters of Builtin

/*!		
\name Public methods of Builtin class
*/
	public:

/*!	
	\name Constructors
*/
		
/*!		
	\brief Constructor with arguments with default values
	\note  Inline function that uses Symbol's constructor as members initializer
	\param name: name of the Builtin
	\param token: token of the Builtin
	\param nParameters: nParameters of the Builtin
	\pre   None
	\post  A new Builtin is created with the values of the parameters
	\sa   setName, setToken, setNParameters
*/
	inline Builtin(std::string name="", int token = 0, int nParameters = 0): Symbol(name,token)
	{
		this->setNParameters(nParameters);
	}
		
/*!		
	\brief Copy constructor
	\note  Inline function
	\param b: object of Builtin class
	\pre   None
	\post  A new Builtin is created with the values of an existent Builtin
	\sa    setName, setValue
*/
	inline Builtin(const Builtin & b)
	{
		// Inherited methods
		this->setName(b.getName());
		this->setToken(b.getToken());

		//  Own method
		this->setNParameters(b.getNParameters());
	}


/*!	
	\name Observer
*/

/*!
	\brief   Public method that returns the nParameters of the Builtin
	\note    Inline function
	\pre     None
	\post    None
	\return  int NParameters of the Builtin
	\sa		 getName, getToken
*/
	inline int getNParameters() const
	{
		return this->_nParameters;
	}	


/*!	
	\name Modifier
*/


/*!	
	\brief   This functions modifies the token of the Builtin
	\note    Función inline
	\param   nParameters: new nParameters of the Builtin
	\pre     None
	\post    The nParameters of the Builtin is equal to the parameter 
	\return  void
	\sa 	 setName, setToken
*/
	inline void setNParameters(int nParameters) 
	{
	    this->_nParameters = nParameters;
	}


/*!	
	\name Operator
*/
	
/*!		
	\brief  Assignment Operator
	\param  b: object of Builtin class
	\post   The atributes of this object are equal to the atributes of the parameter
	\return Reference to this object
*/
	Builtin &operator=(const Builtin &b);
		

		
/*!	
	\name I/O Functions
*/
		

/*!		
	\brief Write a Builtin
	\note  Virtual method: can be redefined in the heir class
	\pre   None
	\post  None
    \sa    read
*/
	virtual void write() const;


/*!		
	\brief   Read a Builtin
	\note    Virtual method: can be redefined in the heir class
	\pre     None
	\post    The atributes of the Builtin are modified with the read values
    \sa      writeS
*/
	virtual void read();

	
// End of Builtin class
};

// End of name space lp
}

// End of _BUILTIN_HPP_
#endif
