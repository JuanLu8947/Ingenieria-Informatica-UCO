/*! 	
	\file   symbolInterface.hpp
	\brief  Declaration of abstract SymbolInterface class
	\author 
	\date    2017-12-1
	\version 1.0

*/

#ifndef _SYMBOLINTERFACE_HPP_
#define _SYMBOLINTERFACE_HPP_

#include <string>


/*!	
	\namespace lp
	\brief Name space for the subject Language Processors
*/
namespace lp{


/*!
  \class SymbolInterface
  \brief Prototype of the pure virtual methods 
*/
class SymbolInterface{

/*!	
\name Public methods of SymbolInterface class
*/
	public:

/*!
	\name Observers
*/
/*!	
	\brief   Name of the Symbol
	\warning Pure virtual function: it must be redefined in the heir class
	\pre     None
	\post    None
	\return  Name of the Symbol
	\sa 	 getValue, getToken
*/
	virtual const std::string &getName() const = 0;


/*!	
	\brief   Token of the Symbol
	\warning Pure virtual function: it must be redefined in the heir class
	\pre     None
	\post    None
	\return  int Token of the Symbol
	\sa		 getName, getValue
*/
	virtual int getToken() const = 0;	


	
/*!
	\name Modifiers
*/
		
/*!	
	\brief   This functions modifies the name of the Symbol
	\warning Pure virtual function: it must be redefined in the heir class
	\param   name: new name of the Symbol
	\pre     None
	\post    The name of the Symbol is equal to the parameter 
	\return  void
	\sa 	 setValue, setToken
*/
	virtual void setName(const std::string & name) = 0;
		
/*!	
	\brief   This functions modifies the token of the Symbol
	\warning Pure virtual function: it must be redefined in the heir class
	\param   token: new value of the Symbol
	\pre     None
	\post    The token of the Symbol is equal to the parameter 
	\return  void
	\sa 	 setName, setValue
*/
	virtual void setToken(int token) = 0;


	
// End of definition of SymbolInterface class
};

// End of name space lp
}

// End of _SYMBOLINTERFACE_HPP_
#endif  
