/*!	

	\file   table.hpp
	\brief  Declaration of TableInterface class
	\author  
	\date    2017-12-13
	\version 1.0
*/

#ifndef _TABLE_HPP_
#define _TABLE_HPP_

#include <string>

#include <map>

#include "tableInterface.hpp"



/*!	
	\namespace lp
	\brief Name space for the subject Language Processors
*/
namespace lp{
/*!	
  \class Table
  \brief Definition of atributes and methods of Table class
*/
class Table: public lp::TableInterface
{

/*!		
\name Private atribute of Symbol class
*/
	private:
	std::map<std::string, lp::Symbol *> _table;   //!< map of strings and pointers to Symbol

/*!		
\name Public methods of Table class
*/

  public: 


/*!	
	\name Constructor
*/
	/*! 
		\brief Constructor of Table class  
		\note  Función inline
		\pre   None
		\post  The Table is empty
	*/
	Table()
	{
		// The method of STL is used.
		this->_table.clear();
	}

/*!	
	\name Destroyer
*/

	/*! 
		\brief Destroyer of Table class  
		\note  Función inline
		\pre   None
		\post  The Table is empty
	*/
	inline ~Table()
	{
		// The method of STL is used.
		this->_table.clear();
	}


/*!
	\name Observers
*/

/*!		
	\brief   lookup a Symbol in the Table
	\param 	 name of a Symbol
	\pre     none
	\return  true, if the Symbol exists; false, otherwise 
	\sa      getSymbol()
*/
	bool lookupSymbol(const std::string & name) const ;
	

/*!		
	\brief  Get the pointer to Symbol saved in the Table
	\pre    The Symbol must be in the table
	\return The Symbol with the searched name
	\sa     lookupSymbol(), operator[]
*/
	lp::Symbol * getSymbol(const std::string & name);


/*!		
	\brief   Check if the Table is empty
	\note	 Inline function
	\return  true, if the table is empty; false, otherwise
	\sa      getNumberOfSymbols()
*/
	inline bool isEmpty() const
	{
		// The method empty of STL is used.
		return _table.empty();
	}

/*!		
	\brief   Return the number of Symbols saved in the Table
	\note	 Inline function
	\return  Integer number 
	\sa      isEmpty()
*/
	inline  int getNumberOfSymbols() const 
	{
		// The method size of STL is used.
		return _table.size();
	}


/*!	
	\name Modifiers
*/

/*!		
	\brief  Insert a new pointer to Symbol in the Table
	\param  s: new pointer to Symbol
	\pre    The Symbol "s" must not be in the Table 
	\post   The Symbol "s" must be in the Table 
	\return void
	\sa     lookupSymbol(), eraseSymbol()
*/
	void installSymbol(Symbol * s);


/*!		
	\brief  Delete a Symbol in the Table
	\param  name:  name of the Symbol to be deleted
	\pre    The Symbol "name" must be in the Table
	\post   The Symbol "name" must not be in the Table
	\return void
	\sa     lookupSymbol(),installSymbol()
*/
	void eraseSymbol(const std::string & name);

/*!	
	\name Output print
*/


/*!		
	\brief  Print the Table
	\return void
*/
	void printTable();



// End of Table class
};

// End of name space lp
}

// End of _TABLE_HPP_
#endif
