/*!	

	\file   table.cpp
	\brief   Code of some functions of Table class
	\author  
	\date    2017-12-13
	\version 1.0
*/

#include <map>

#include <cassert>

#include <iostream>

#include "table.hpp"



bool lp::Table::lookupSymbol(const std::string & name) const 
{		
	if (this->_table.find(name) !=  this->_table.end())
		return true;
	else
		return false;
}


lp::Symbol * lp::Table::getSymbol(const std::string & name)
{
 #ifndef NDEBUG
   // Precondition
   assert (this->lookupSymbol(name) == true);
 #endif //NDEBUG

	return	this->_table[name];
}



void lp::Table::installSymbol(Symbol * s)
{
 #ifndef NDEBUG
  // Precondition
   assert (this->lookupSymbol(s->getName()) == false);
 #endif //NDEBUG

   // The pointer to symbol is inserted in the map
	this->_table[s->getName()] = s;

 #ifndef NDEBUG
  // Postcondition
   assert (this->lookupSymbol(s->getName()) == true);
 #endif //NDEBUG
}



void lp::Table::eraseSymbol(const std::string & name)
{
 #ifndef NDEBUG
  // Precondition
   assert (this->lookupSymbol(name) == true);
 #endif //NDEBUG

   // The symbol "name" is deleted from the map
	this->_table.erase(name);

 #ifndef NDEBUG
  // Postcondition
   assert (this->lookupSymbol(name) == false);
 #endif //NDEBUG
}


void lp::Table::printTable()
{
	for(std::map<std::string, lp::Symbol *>::const_iterator it = this->_table.begin();
        it != this->_table.end();
        ++it)
    {
		std::cout<<it->first<<", "<<getSymbol(it->first)->getToken()<< std::endl;
	}
}




