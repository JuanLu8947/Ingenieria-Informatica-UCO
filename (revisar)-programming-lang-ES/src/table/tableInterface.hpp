/*!	

	\file    tableInterface.hpp
	\brief   Declaration of abstract TableInterface class
	\author  
	\date    2017-12-1
	\version 1.0
*/

#ifndef _TABLEINTERFACE_HPP_
#define _TABLEINTERFACE_HPP_

#include <string>

#include "symbol.hpp"

/*!	
	\namespace lp
	\brief Name space for the subject Language Processors
*/
namespace lp{
/*!	
  \class TableInterface
  \brief Specificatons of the pure virtual methods
*/
class TableInterface{

/*!		
\name Public methods of SymbolInterface class
*/

/*!	
	\name Observers
*/

/*!		
	\brief   lookup a Symbol in the Table
	\warning Pure virtual function: it must be redefined in the heir class
	\param 	 name of a Symbol
	\pre     none
	\return  true, if the Symbol exists; false, otherwise 
	\sa      getSymbol
*/
	virtual  bool lookupSymbol(const std::string & name) const = 0;


/*!		
	\brief   Get the Symbol saved in the Table
	\warning Pure virtual function: it must be redefined in the heir class
	\pre     The Symbol must be in the table
	\return  The Symbol with the searched name
	\sa      lookupSymbol
*/
	virtual  lp::Symbol * getSymbol(const std::string & name) = 0;


/*!		
	\brief   Check if the Table is empty
	\warning Pure virtual function: it must be redefined in the heir class
	\return  true, if the table is empty; false, otherwise
	\sa      getNumberOfSymbols
*/
	virtual bool isEmpty()  const = 0;

/*!		
	\brief   Return the number of Symbols saved in the Table
	\warning Pure virtual function: it must be redefined in the heir class
	\return  Integer number 
	\sa      isEmpty
*/
	virtual  int getNumberOfSymbols() const = 0;


/*!	
	\name Modifiers
*/

/*!		
	\brief   Insert a new Symbol in the Table
	\warning Pure virtual function: it must be redefined in the heir class
	\param  s: new Symbol
	\pre    The Symbol "s" must not be in the Table 
	\post   The Symbol "s" must be in the Table 
	\return void
	\sa     lookupSymbol
*/
	virtual  void installSymbol(Symbol * s) = 0;
	

// End of TableInterface class
};

// End of name space lp
}

// End of _TABLE_HPP_
#endif
