/*!	
	\file    keyword.hpp
	\brief   Declaration of Keyword class
	\author  
	\date    2017-12-1
	\version 1.0
*/

#ifndef _KEYWORD_HPP_
#define _KEYWORD_HPP_

#include <string>
#include <iostream>

#include "symbol.hpp"

/*!	
	\namespace lp
	\brief Name space for the subject Language Processors
*/
namespace lp{

/*!	
  \class     Keyword
  \attention Abstrac class
  \brief     Definition of atributes and methods of Keyword class
  \note      Keyword Class publicly inherits from Symbol class
*/
class Keyword:public lp::Symbol
{
/*!		
\name No own attributes of Keyword class
*/




/*!		
\name Public methods of Keyword class
*/
	public:

/*!	
	\name Constructors
*/
		
/*!		
	\brief Constructor with arguments with default values
	\note  Inline function that uses Symbol's constructor as members initializer
	\param name: name of the Keyword
	\param token: token of the Keyword
	\pre   None
	\post  A new Keyword is created with the values of the parameters
	\sa   setName, setToken, setType
*/
	inline Keyword(std::string name="", int token = 0): Symbol(name,token)
	{
		// Empty
	}
		
/*!		
	\brief Copy constructor
	\note  Inline function
	\param k: object of Keyword class
	\pre   None
	\post  A new Keyword is created with the values of an existent Keyword
	\sa    setName, setValue
*/
	inline Keyword(const Keyword & k)
	{
		// Inherited methods
		this->setName(k.getName());
		this->setToken(k.getToken());

	}


/*!	
	\name Operator
*/
	
/*!		
	\brief  Assignment Operator
	\param  k: objecto of Keyword class
	\post   The atributes of this object are equal to the atributes of the parameter
	\return Reference to this object
*/
	Keyword &operator=(const Keyword &k);
		

		
/*!	
	\name I/O Functions
*/
		

/*!		
	\brief Write a Keyword
	\pre   None
	\post  None
    \sa    read
*/
	void write() const;


/*!		
	\brief   Read a Keyword
	\pre     None
	\post    The atributes of the Keyword are modified with the read values
    \sa      writeS
*/
	void read();

	
// End of Keyword class
};

// End of name space lp
}

// End of _KEYWORD_HPP_
#endif
