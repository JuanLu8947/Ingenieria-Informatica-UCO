/*!	
	\file   init.hpp
	\brief   Prototype of the function for the initialization of table of symbols
	\author  
	\date    2017-12-5
	\version 1.0
*/

#ifndef _INIT_HPP_
#define _INIT_HPP_

// sin, cos, atan, fabs, ...
#include <math.h>

#include "table.hpp"

// IMPORTANT: This file must be before y.tab.h
#include "../ast/ast.hpp"
///////////////////////////////////////

//  interpreter.tab.h contains the number values of the tokens produced by the parser
#include "../parser/interpreter.tab.h"

///////////////////////////////////////
// NEW in example 13
#include "mathFunction.hpp"
#include "builtinParameter1.hpp"
///////////////////////////////////////

///////////////////////////////////////
// NEW in example 14
#include "builtinParameter0.hpp"
#include "builtinParameter2.hpp"
///////////////////////////////////////

/*!
  \ brief Predefined numeric constants
*/
static struct {
          std::string name ;
	      double value;
	      } numericConstant[] = {
	                    {"pi",    3.14159265358979323846},
	                    {"e",     2.71828182845904523536},
	                    {"gamma", 0.57721566490153286060},
	                    {"deg",  57.29577951308232087680},
	                    {"phi",   1.61803398874989484820},
	                    {"",      0}
	                   };

/*!
  \ brief Predefined logical constants
*/
static struct {
          std::string name ;
	      bool value;
	      } logicalConstant[] = { 
	                    {"verdadero", true},
	                    {"falso", false},
	                    {"",      0}
	                   };

/*!
  \ brief Predefined keywords
*/
static struct {
          std::string name ;
	      int token;
	      } keyword[] = { 
	                    {"leer",  READ},
	                    {"leer_cadena",  READSTRING},
	                    {"escribir", PRINT},
						{"si",	  IF},   
						{"entonces",  THEN},   
						{"si_no",  ELSE}, 
						{"fin_si", ENDIF},
						{"mientras", WHILE},
						{"hacer",    DO},
						{"fin_mientras", ENDWHILE},
						{"repetir", REPEAT},
						{"hasta", UNTIL},
						{"para",   FOR},
						{"fin_para", ENDFOR},
						{"desde",  FROM},
						{"paso",  STEP},
						{"hacia",    TO},
						{"selector", SWITCH},
						{"caso",   CASE},
						{"defecto", DEFAULT},
						{"fin_selector", ENDSWITCH},
						{"borrar_pantalla", CLEARSCREEN},
						{"lugar", PLACE},
						{"mod",   MODULO},
						{"o",    OR},
						{"y",   AND},
						{"no",   NOT},
		                {"text", TEXT},
		                {"yellow", COLOR_YELLOW},
		                {"blue", COLOR_BLUE},
						{"reset", RESET_TEXT},
	                    {"",      0}
	                   };
static struct {    /* Predefined functions names */ 
                std::string name ;
				lp::TypePointerDoubleFunction_1 function;
              } function_1 [] = {
	                   {"seno",     sin},
		               {"coseno",     cos},
		               {"atan",    atan},
		               {"log",     Log},
		               {"log10",   Log10},
		               {"exp",     Exp},
		               {"raiz",    Sqrt},
		               {"parte_entera", integer},
		               {"abs",     fabs},   
		               {"",       0}
		              };

static struct {   
                std::string name ;
				lp::TypePointerDoubleFunction_0 function;
              } function_0 [] = {
						{"random", Random},
		                {"",       0}
		              };

static struct {    /* Nombres predefinidos de funciones con 2 argumentos */ 
                std::string name ;
				lp::TypePointerDoubleFunction_2 function;
              } function_2 [] = {
	                   {"atan2",   Atan2},
		               {"",       0}
		              };

/*!		
	\brief   Initialize the table of symbols
	\return  void 
*/

void init(lp::Table &t);

// End of _INIT_HPP_
#endif
