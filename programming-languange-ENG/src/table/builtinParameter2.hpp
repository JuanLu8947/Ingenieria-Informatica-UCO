/*!	
	\file    builtinParameter2.hpp
	\brief   Declaration of BuiltinParameter2 class
	\author  
	\date    2017-12-7
	\version 1.0
*/

#ifndef _BUILTIN2PARAMETERS_HPP_
#define _BUILTIN2PARAMETERS_HPP_

#include <string>
#include <iostream>

#include "builtin.hpp"

/*!	
	\namespace lp
	\brief Name space for the subject Language Processors
*/
namespace lp{


/*! New type definition: TypePointerDoubleFunction_2 */
typedef double (*TypePointerDoubleFunction_2)(double x,double y);



/*!	
  \class BuiltinParameter2
  \brief Definition of atributes and methods of BuiltinParameter2 class
  \note  BuiltinParameter2 Class publicly inherits from Constant class
*/
class BuiltinParameter2:public lp::Builtin
{
/*!		
\name Private atributes of BuiltinParameter2 class
*/
	private:
        lp::TypePointerDoubleFunction_2 _function; //!< \brief function of the BuiltinParameter2 

/*!		
\name Public methods of BuiltinParameter2 class
*/
	public:

/*!	
	\name Constructors
*/
		
/*!		
	\brief Constructor 
	\note  Inline function that uses Constant's constructor as members initializer
	\param name: name of the BuiltinParameter2
	\param token: token of the BuiltinParameter2
	\param nParameters: number of parameters of the BuiltinParameter2
	\param function: numeric function of the BuiltinParameter2
	\pre   None
	\post  A new BuiltinParameter2 is created with the functions of the parameters
	\sa    setFunction
*/
	inline BuiltinParameter2(std::string name, 
							  int token, 
							  int nParameters,
						      lp::TypePointerDoubleFunction_2 function): 
							  Builtin(name,token,nParameters)
	{
		this->setFunction(function);
	}
		
/*!		
	\brief Copy constructor
	\note  Inline function
	\param f: object of BuiltinParameter2 class
	\pre   None
	\post  A new BuiltinParameter2 is created with the functions of an existent BuiltinParameter2
	\sa    setName, setToken,  setNParameters,  setFunction
*/
	BuiltinParameter2(const BuiltinParameter2 & f)
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
	\brief  Public method that returns the function of the BuiltinParameter2
	\note   Función inline
	\pre    None
	\post   None
    \return Function of the BuiltinParameter2
	\sa		getFunction
*/
	lp::TypePointerDoubleFunction_2 getFunction() const
	{
		return this->_function;
	}



/*!	
	\name Modifier
*/
		
/*!	
	\brief   This functions modifies the function of the BuiltinParameter2
	\note    Inline function
	\param   function: new function of the BuiltinParameter2
	\pre     None
	\post    The function of the BuiltinParameter2 is equal to the parameter 
	\return  void
	\sa 	 setFunction
*/
	inline void setFunction(const lp::TypePointerDoubleFunction_2 & function)
	{
	    this->_function = function;
	}



/*!	
	\name Operators
*/
	
/*!		
	\brief  Assignment Operator
	\param  f: objectoof BuiltinParameter2 class
	\post   The atributes of this object are equal to the atributes of the parameter
	\return Reference to this object
*/
	BuiltinParameter2 &operator=(const BuiltinParameter2 &f);
	
	
// End of BuiltinParameter2 class
};

// End of name space lp
}

// End of _BUILTIN2PARAMETERS_HPP_
#endif
