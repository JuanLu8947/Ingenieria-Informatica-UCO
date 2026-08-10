/*! 
  \file interpreter.l
  \brief Lexical or scanner file
*/
%{
#include <iostream>

/* atof */
#include <stdlib.h>

#include <string>

/* Macros for the screen */
#include "../includes/macros.hpp"

/*
  AST class
  IMPORTANT: must be written before interpreter.tab.h
*/
#include "../ast/ast.hpp"

/*  interpreter.tab.h contains the numeric values of the tokens produced by the parser */
#include "interpreter.tab.h"

#include "../error/error.hpp"

/* Table of symbols */
#include "../table/table.hpp"

#include "../table/numericVariable.hpp"

extern lp::Table table; //!< External Table of Symbols
/*********************************************/

extern int lineNumber; //!< External line counter

/* uso de strdup */
#include <string.h>

std::string decodeStringLiterals(const char *text)
{
	std::string result;

	for (size_t i = 0; text[i] != '\0'; ++i)
	{
		if (text[i] == '\\')
		{
			++i;
			if (text[i] == '\0')
			{
				break;
			}

			switch (text[i])
			{
				case 'n':
					result.push_back('\n');
					break;
				case 't':
					result.push_back('\t');
					break;
				case '\\':
					result.push_back('\\');
					break;
				case '\'':
					result.push_back('\'');
					break;
				default:
					result.push_back('\\');
					result.push_back(text[i]);
					break;
			}
		}
		else
		{
			result.push_back(text[i]);
		}
	}

	return result;
}

%}
%option case-insensitive noyywrap

/*! \name REGULAR DEFINITIONS  */

DIGIT  [0-9] 

LETTER [a-zA-Z]

IDENTIFIER  {LETTER}("_"?({LETTER}|{DIGIT}))*

cadena \'([^\'\\]|\\.)*\'

/*  NUMBER  */
entero      {DIGIT}+
real_fijo   {DIGIT}+\.{DIGIT}+

real_exp    ({entero}|{real_fijo})[eE][+-]?{entero}

numero      {entero}|{real_fijo}|{real_exp}

/* STATE  */
%x ERROR COMMENT

/*! \name REGULAR EXPRESSIONS  */
%%

[ \t\r] { ; }    /* skip white space, tabs and Windows CR */

#.*       {   /* Ignorar comentarios
		    	 Si una línea comienza con el carácter #, 
		    	 seguido de cualquier cosa (.*), 
		    	 se reconoce # como un token.
		        */  
		        ;
		    }


"(*"    { BEGIN(COMMENT); }

<COMMENT>"*)"   { 
				    /* Fin del comentario: se vuelve al estado por defecto */
				    BEGIN(INITIAL); /* sentencia equivalente: BEGIN 0 */
			    }

<COMMENT>.  {
			    /* Se descarta todo lo que haya contenido en el comentario */
			    ;	
            }

<COMMENT>\n 	{ 
                	/* Si hay un salto de línea en el comentario, se cuenta */
                	lineNumber++; 
                }

\n      { /* Line counter */
           lineNumber++;
          /* return NEWLINE; */
        }

";"     {   return SEMICOLON;   }

","     {   return COMMA;   }

":"     {   return COLON;   }

{numero}   	{
	            yylval.number = atof(yytext); 

	            return NUMBER;   
	        }

{cadena}	{
	            yytext[yyleng-1] = '\0'; /* Se elimina la comilla final */

                yytext++; /* Se elimina la comilla inicial */

                yyleng--; /* Se actualiza el tamaño de la cadena */

				/* Interpretar secuencias de escape: \n, \t, \\, \' */

				std::string decoded = decodeStringLiterals(yytext);
				yylval.string = strdup(decoded.c_str());

                return STRING;
            }

{IDENTIFIER}    {
	                std::string identifier(yytext);

	                /* strdup() function returns a pointer to a new string which is a duplicate of the string yytext */
	                yylval.string =  strdup(yytext);

	                /* If the identifier is not in the table of symbols then it is inserted */
	                if (table.lookupSymbol(identifier) == false){
	                	/* The identifier is inserted into the symbol table as undefined Variable with value 0.0 */
	                	lp::NumericVariable *n = new lp::NumericVariable(identifier,VARIABLE,UNDEFINED,0.0);
	                	/* A pointer to the new NumericVariable is inserted into the table of symbols */
	                	table.installSymbol(n);

	                	return VARIABLE;
	                }
	                else{
	                	lp::Symbol *s = table.getSymbol(identifier);
	                	return s->getToken();
	                }
                }

"-"    { return MINUS;  } 
"+"    { return PLUS;   } 

"*"    { return MULTIPLICATION; } 


"//"	{ return FLOOR_DIVISION; }


"/"    { return DIVISION; } 

"("    { return LPAREN; } 
")"    { return RPAREN; } 

"%"    { return MODULO; }

"^"    { return POWER; }

":="   { return ASSIGNMENT; }


"+:="	{ return PLUS_EQUAL; }

"-:="	{ return MINUS_EQUAL; }

"*:="	{ return MULTIPLICATION_EQUAL; }

"/:="	{ return DIVISION_EQUAL; }

"++"	{	return PLUS_PLUS;	}
"--"	{	return MINUS_MINUS;	}


"="    { return EQUAL; } 

"<>"   { return NOT_EQUAL; }

">="   { return GREATER_OR_EQUAL; }

"<="   { return LESS_OR_EQUAL; }

">"    { return GREATER_THAN; } 

"<"    { return LESS_THAN; } 

"{"    { return LETFCURLYBRACKET; } 

"}"    { return RIGHTCURLYBRACKET; }


"!"    { return FACTORIAL; }

"?"    { return TERNARIO; }

"||"   { return CONCATENATION; }


<<EOF>> { /* The interpreter finishes when finds the end of file character */
        	return 0;
        }

.   { 
    	/* Any other character */
    	/* Change to error state */
    	BEGIN(ERROR); 
    	yymore();  
    }

<ERROR>[^0-9+\-*/()\^% \t\n\;a-zA-Z=<>!&] {
                                          	yymore(); 
                                          }

<ERROR>(.|\n) { 
              	yyless(yyleng-1); 
              	warning("Lexical error", yytext);
              	BEGIN(INITIAL);
              }
              
%%
