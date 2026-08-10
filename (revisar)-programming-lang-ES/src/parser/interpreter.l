/*! 
  \file interpreter.l
  \brief Lexical or scanner file
*/
%{
#include <iostream>

/*********************/
/* NEW in example 4 */
/* atof */
#include <stdlib.h>
/*********************/

/* Macros for the screen */
#include "../includes/macros.hpp"

/*********************/
/* 
  NEW in example 16 
  AST class
  IMPORTANT: must be written before interpreter.tab.h
*/
#include "../ast/ast.hpp"
/*********************/

/*  interpreter.tab.h contains the numeric values of the tokens produced by the parser */
#include "interpreter.tab.h"

/********************/
/* NEW in example 3 */
#include "../error/error.hpp"
/********************/


/*********************************************/
/* NEW in example 7 */
/* Table of symbols */
#include "../table/table.hpp"

#include "../table/numericVariable.hpp"

extern lp::Table table; //!< External Table of Symbols
/*********************************************/

extern int lineNumber; //!< External line counter

/* uso de strdup */
#include <string.h>

std::string decode(const char *text)
{
	std::string aux;
	for(size_t i=0; text[i]!='\0'; ++i)
	{
		if(text[i] == '\\')
		{
			++i; /*al detectar '\' se avanza una pos*/

			if (text[i] == '\0')
			{
				break;
			}

			switch(text[i])
			{
				case 'n':
					aux.push_back('\n');
					break;
				case 't':
					aux.push_back('\t');
					break;
				case '\\':
					aux.push_back('\\');
					break;
				case '\'':
					aux.push_back('\'');
					break;
				default:
					aux.push_back('\\');
					aux.push_back(text[i]);
					break;
			}
		}
		else{
			aux.push_back(text[i]);
		}
	}

	return aux;
}

%}
%option noyywrap case-insensitive

/*! \name REGULAR DEFINITIONS  */

DIGIT  [0-9] 

LETTER [a-zA-Z]


INT {DIGIT}+

REAL_FIJO {INT}\.{INT}

REAL_EXP ({INT}|{REAL_FIJO})[eE][+-]?{INT}

NUMERO {INT}|{REAL_FIJO}|{REAL_EXP}

cadena \'([^\'\\]|\\.)*\'


IDENTIFIER  {LETTER}("_"?({LETTER}|{DIGIT}))*


/* NEW in example 3 */
/* STATE  */
%x ERROR COMMENT

/*! \name REGULAR EXPRESSIONS  */
%%

[ \t\r] 	{ ; }    /* skip white space, retornos de carga & tabular */

#.* {;} /*Ignore comments*/

"(*" {BEGIN(COMMENT);}

<COMMENT>.	{;} /*ignora el contenido interno del comment*/

<COMMENT>"*)" 	{
					/*fin del comment se vuelve al estado i0*/
					BEGIN(INITIAL);
				}

<COMMENT>\n 	{ 
                	/* Si hay un salto de línea en el comentario, se cuenta */
                	lineNumber++; 
                }

\n      { 
			/* Line counter */
           	lineNumber++; 
	
			/* MODIFIED in example 3 */
			/* COMMENTED in example 5 */
        	/* return NEWLINE; */
        }

";"		{
			/* NEW in example 5 */
			return SEMICOLON;
		}


":"		{
			/* NEW*/
			return COLON;
		}



","		{
			/* NEW in example 14 */
			return COMMA;
		}

{NUMERO}  {
					  /* MODIFIED in example 4 */
					  /* Conversion of type and sending of the numerical value to the parser */
					   yylval.number = atof(yytext); 

                       return NUMBER; 
                      }


{cadena}  		{
					/* Eliminar la comilla final*/
					yytext[yyleng-1] = '\0';

					/*eliminar la comilla inicial*/
					yytext++;

					/*actualizar el tamao de la cadena */
					yyleng--;

					/*Interpretar secuencias de escape*/
					std::string aux = decode(yytext);

					yylval.string =  strdup(aux.c_str());
					/* 
                         strdup() function returns a pointer to a new string 
                         which  is a duplicate of the string yytext
                     */

                    return STRING; 
                }


{IDENTIFIER}   		 {
						 /* NEW in example 7 */
						 std::string identifier(yytext);

						/* 
                          strdup() function returns a pointer to a new string 
                          which  is a duplicate of the string yytext
                        */
						  yylval.string =  strdup(yytext);

						/* If the identifier is not in the table of symbols then it is inserted */	
						 if (table.lookupSymbol(identifier) == false)
							{
								/* 
								 The identifier is inserted into the symbol table 
								 as undefined Variable with value 0.0
								*/
								lp::NumericVariable *n = new lp::NumericVariable(identifier,VARIABLE,UNDEFINED,0.0);

								/* A pointer to the new NumericVariable is inserted into the table of symbols */
								table.installSymbol(n);

								return VARIABLE;
							}

						/* MODIFIED in example 11 */
						/* 
							If the identifier is in the table of symbols then its token is returned 
								The identifier can be a variable or a numeric constant
						*/
						else 
							{
								lp::Symbol	*s = table.getSymbol(identifier);

/*
								std::cout << "lex: "<< s->getName() 
										  << "token " << s->getToken()
  										  << std::endl; 
*/

								/*  If the identifier is in the table then its token is returned  */
								return s->getToken();
							}
                     }

"-"		{ return MINUS;  } 			/* NEW in example 3 */
"+"		{ return PLUS;   } 			/* NEW in example 3 */

"*"	    { return MULTIPLICATION; } 	/* NEW in example 3 */
"/"     { return DIVISION; } 		/* NEW in example 3 */


"//"     { return FLOOR_DIV; } 		/* NEW */


"("     { return LPAREN; } 			/* NEW in example 3 */
")"	    { return RPAREN; } 			/* NEW in example 3 */

"^"	    { return POWER; }			/* NEW in example 5 */


":=" 	{ return ASSIGNMENT; }		/* NEW*/


"="	{ return EQUAL; }



"+:="	{ return PLUS_EQUAL; }

"-:="	{ return MINUS_EQUAL; }

"*:="	{ return MULTIPLICATION_EQUAL; }

"/:="	{ return DIVISION_EQUAL; }

"++"	{	return PLUS_PLUS;	}
"--"	{	return MINUS_MINUS;	}


"<>"	{ return NOT_EQUAL; }		/* NEW in example 15 */

">="	{ return GREATER_OR_EQUAL; }/* NEW in example 15 */

"<="	{ return LESS_OR_EQUAL; }	/* NEW in example 15 */

">"		{ return GREATER_THAN; }	/* NEW in example 15 */

"<"		{ return LESS_THAN; }		/* NEW in example 15 */


"||"	{ return CONCAT; }

"!"    { return FACT; }

"?"    { return TERNARIO; }


"{"		{ return LETFCURLYBRACKET; } 	/* NEW in example 17 */

"}"		{ return RIGHTCURLYBRACKET; }	/* NEW in example 17 */


<<EOF>> { /* The interpreter finishes when finds the end of file character */
		/*  PLACE(24,10);
	  	  std::cout <<  BICYAN;
	   	  std::cout <<  ">>>>>>> End of program <<<<<<<";
	 	  std::cout << std::endl;
	   	  std::cout << RESET;
		  PLACE(25,1);
		*/
	  	  return 0;
	}


.								{ 	
									/* Any other character */
									/* MODIFIIED in example 3 */
									/* Change to error state */
									BEGIN(ERROR); 

									/* 
										The current value of yytext 
										will be concatenated with the next character
									*/
									yymore();  
								}

<ERROR>[^0-9+\-*/()\^% \t\n\;a-zA-Z=<>!&]	{ /* MODIFIED in examples 5, 7, 15 */
								  /* NEW in example 3 */
								  /* 
									The current value of yytext 
									will be concatenated with the next character
								  */
									yymore(); 
								}

<ERROR>(.|\n)                { 
								/* NEW in example 3 */
								/* Rewind one position */
								yyless(yyleng-1); 

								/* Display the error message */
								warning("Lexical error", yytext);

								/* Restore the initial state */
   								BEGIN(INITIAL);
							}
%%

