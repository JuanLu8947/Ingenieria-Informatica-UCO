/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_INTERPRETER_TAB_H_INCLUDED
# define YY_YY_INTERPRETER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEMICOLON = 258,               /* SEMICOLON  */
    COLON = 259,                   /* COLON  */
    READ = 260,                    /* READ  */
    READSTRING = 261,              /* READSTRING  */
    PRINT = 262,                   /* PRINT  */
    IF = 263,                      /* IF  */
    THEN = 264,                    /* THEN  */
    ELSE = 265,                    /* ELSE  */
    ENDIF = 266,                   /* ENDIF  */
    WHILE = 267,                   /* WHILE  */
    DO = 268,                      /* DO  */
    ENDWHILE = 269,                /* ENDWHILE  */
    REPEAT = 270,                  /* REPEAT  */
    UNTIL = 271,                   /* UNTIL  */
    FOR = 272,                     /* FOR  */
    ENDFOR = 273,                  /* ENDFOR  */
    FROM = 274,                    /* FROM  */
    STEP = 275,                    /* STEP  */
    TO = 276,                      /* TO  */
    SWITCH = 277,                  /* SWITCH  */
    CASE = 278,                    /* CASE  */
    DEFAULT = 279,                 /* DEFAULT  */
    ENDSWITCH = 280,               /* ENDSWITCH  */
    CLEARSCREEN = 281,             /* CLEARSCREEN  */
    PLACE = 282,                   /* PLACE  */
    TEXT = 283,                    /* TEXT  */
    COLOR_YELLOW = 284,            /* COLOR_YELLOW  */
    COLOR_BLUE = 285,              /* COLOR_BLUE  */
    RESET_TEXT = 286,              /* RESET_TEXT  */
    LETFCURLYBRACKET = 287,        /* LETFCURLYBRACKET  */
    RIGHTCURLYBRACKET = 288,       /* RIGHTCURLYBRACKET  */
    ASSIGNMENT = 289,              /* ASSIGNMENT  */
    TERNARIO = 290,                /* TERNARIO  */
    COMMA = 291,                   /* COMMA  */
    NUMBER = 292,                  /* NUMBER  */
    BOOL = 293,                    /* BOOL  */
    STRING = 294,                  /* STRING  */
    VARIABLE = 295,                /* VARIABLE  */
    UNDEFINED = 296,               /* UNDEFINED  */
    CONSTANT = 297,                /* CONSTANT  */
    BUILTIN = 298,                 /* BUILTIN  */
    OR = 299,                      /* OR  */
    AND = 300,                     /* AND  */
    GREATER_OR_EQUAL = 301,        /* GREATER_OR_EQUAL  */
    LESS_OR_EQUAL = 302,           /* LESS_OR_EQUAL  */
    GREATER_THAN = 303,            /* GREATER_THAN  */
    LESS_THAN = 304,               /* LESS_THAN  */
    EQUAL = 305,                   /* EQUAL  */
    NOT_EQUAL = 306,               /* NOT_EQUAL  */
    NOT = 307,                     /* NOT  */
    PLUS = 308,                    /* PLUS  */
    MINUS = 309,                   /* MINUS  */
    MULTIPLICATION = 310,          /* MULTIPLICATION  */
    DIVISION = 311,                /* DIVISION  */
    MODULO = 312,                  /* MODULO  */
    FLOOR_DIV = 313,               /* FLOOR_DIV  */
    LPAREN = 314,                  /* LPAREN  */
    RPAREN = 315,                  /* RPAREN  */
    CONCAT = 316,                  /* CONCAT  */
    PLUS_EQUAL = 317,              /* PLUS_EQUAL  */
    MINUS_EQUAL = 318,             /* MINUS_EQUAL  */
    MULTIPLICATION_EQUAL = 319,    /* MULTIPLICATION_EQUAL  */
    DIVISION_EQUAL = 320,          /* DIVISION_EQUAL  */
    PLUS_PLUS = 321,               /* PLUS_PLUS  */
    MINUS_MINUS = 322,             /* MINUS_MINUS  */
    FACT = 323,                    /* FACT  */
    UNARY = 324,                   /* UNARY  */
    POWER = 325                    /* POWER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 141 "interpreter.y"

  double number;
  char * string; 				 /* NEW in example 7 */
  bool logic;						 /* NEW in example 15 */
  lp::ExpNode *expNode;  			 /* NEW in example 16 */
  std::list<lp::ExpNode *>  *parameters;    // New in example 16; NOTE: #include<list> must be in interpreter.l, init.cpp, interpreter.cpp
  std::list<lp::Statement *> *stmts; /* NEW in example 16 */
  std::list<lp::CaseStmt *> *cases;
  lp::Statement *st;				 /* NEW in example 16 */
  lp::AST *prog;					 /* NEW in example 16 */

#line 146 "interpreter.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_INTERPRETER_TAB_H_INCLUDED  */
