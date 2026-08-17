/*!	
	\file    builtinParameter0.hpp
	\brief   Declaration of BuiltinParameter0 class
	\author  
	\date    2017-12-7
	\version 1.0
*/

#ifndef _BUILTINPARAMETER0_HPP_
#define _BUILTINPARAMETER0_HPP_

#include <string>
#include <iostream>

#include "builtin.hpp"

/*!	
	\namespace lp
	\brief Name space for the subject Language Processors
*/
namespace lp{


/*! New type definition: TypePointerDoubleFunction_0 */
typedef double (*TypePointerDoubleFunction_0)();



/*!	
  \class BuiltinParameter0
  \brief Definition of atributes and methods of BuiltinParameter0 class
  \note  BuiltinParameter0 Class publicly inherits from Constant class
*/
class BuiltinParameter0:public lp::Builtin
{
/*!		
\name Private atributes of BuiltinParameter0 class
*/
	private:
        lp::TypePointerDoubleFunction_0 _function; //!< \brief function of the BuiltinParameter0 

/*!		
\name Public methods of BuiltinParameter0 class
*/
	public:

/*!	
	\name Constructors
*/
		
/*!		
	\brief Constructor 
	\note  Inline function that uses Constant's constructor as members initializer
	\param name: name of the BuiltinParameter0
	\param token: token of the BuiltinParameter0
	\param nParameters: número de parámetros of the BuiltinParameter0
	\param function: numeric function of the BuiltinParameter0
	\pre   None
	\post  A new BuiltinParameter0 is created with the functions of the parameters
	\sa    setFunction
*/
	inline BuiltinParameter0(std::string name, 
							  int token, 
							  int nParameters,
						      lp::TypePointerDoubleFunction_0 function): 
							  Builtin(name,token,nParameters)
	{
		this->setFunction(function);
	}
		
/*!		
	\brief Copy constructor
	\note  Inline function
	\param f: object of BuiltinParameter0 class
	\pre   None
	\post  A new BuiltinParameter0 is created with the functions of an existent BuiltinParameter0
	\sa    setName, setToken,  setNParameters,  setFunction
*/
	BuiltinParameter0(const BuiltinParameter0 & f)
	{
		// Inherited methods
		this->setName(f.getName());

		this->setToken(f.getToken());

		this->setNParameters(f.getNParameters());
		
		// Own method
		this->setFunction(f.getFunction());
	}


/*!	
	\name Observer
*/
	
/*!	
	\brief  Public method that returns the function of the BuiltinParameter0
	\note   Función inline
	\pre    None
	\post   None
    \return Function of the BuiltinParameter0
	\sa		getFunction
*/
	lp::TypePointerDoubleFunction_0 getFunction() const
	{
		return this->_function;
	}



/*!	
	\name Modifier
*/
		
/*!	
	\brief   This functions modifies the function of the BuiltinParameter0
	\note    Inline function
	\param   function: new function of the BuiltinParameter0
	\pre     None
	\post    The function of the BuiltinParameter0 is equal to the parameter 
	\return  void
	\sa 	 setFunction
*/
	inline void setFunction(const lp::TypePointerDoubleFunction_0 & function)
	{
	    this->_function = function;
	}



		
/*!	
	\name Operators
*/
	
/*!		
	\brief  Assignment Operator
	\param  f: objectoof BuiltinParameter0 class
	\post   The atributes of this object are equal to the atributes of the parameter
	\return Reference to this object
*/
	BuiltinParameter0 &operator=(const BuiltinParameter0 &f);
	
	
// End of BuiltinParameter0 class
};

// End of name space lp
}

// End of _BUILTINPARAMETER0_HPP_
#endif
