/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 7 "interpreter.y"

#include <iostream>
#include <string>

/*******************************************/
/* NEW in example 5 */
/* pow */
#include <math.h>
/*******************************************/

/*******************************************/
/* NEW in example 6 */
/* Use for recovery of runtime errors */
#include <setjmp.h>
#include <signal.h>
/*******************************************/

/* Error recovery functions */
#include "../error/error.hpp"

/* Macros for the screen */
#include "../includes/macros.hpp"


/*******************************************/
/* 
  NEW in example 16
  AST class
  IMPORTANT: this file must be before init.hpp
*/
#include "../ast/ast.hpp"


/*******************************************/
/* NEW in example 7 */
/* Table of symbol */
#include "../table/table.hpp"
/*******************************************/

/*******************************************/
#include "../table/numericVariable.hpp"
/*******************************************/

/* NEW in example 15 */
#include "../table/logicalVariable.hpp"

/*******************************************/
/* NEW in example 11 */
#include "../table/numericConstant.hpp"
/*******************************************/

/*******************************************/
/* NEW in example 15 */
#include "../table/logicalConstant.hpp"
/*******************************************/

/*******************************************/
/* NEW in example 13 */
#include "../table/builtinParameter1.hpp"
/*******************************************/

/*******************************************/
/* NEW in example 14 */
#include "../table/builtinParameter0.hpp"
#include "../table/builtinParameter2.hpp"
/*******************************************/


/*******************************************/
/* NEW in example 10 */
#include "../table/init.hpp"
/*******************************************/

/*! 
	\brief  Lexical or scanner function
	\return int
	\note   C++ requires that yylex returns an int value
	\sa     yyparser
*/
int yylex();


extern int lineNumber; //!< External line counter


/* NEW in example 15 */
extern bool interactiveMode; //!< Control the interactive mode of execution of the interpreter

/* New in example 17 */
extern int control; //!< External: to control the interactive mode in "if" and "while" sentences 




/***********************************************************/
/* NEW in example 2 */
extern std::string progname; //!<  Program name
/***********************************************************/

/*******************************************/
/* NEW in example 6 */
/*
 jhmp_buf
    This is an array type capable of storing the information of a calling environment to be restored later.
   This information is filled by calling macro setjmp and can be restored by calling function longjmp.
*/
jmp_buf begin; //!<  It enables recovery of runtime errors 
/*******************************************/


/*******************************************/
/* NEW in example 7 */
extern lp::Table table; //!< Extern Table of Symbols

/*******************************************/
/* NEW in example 16 */
extern lp::AST *root; //!< External root of the abstract syntax tree AST


#line 191 "interpreter.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "interpreter.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_COLON = 4,                      /* COLON  */
  YYSYMBOL_READ = 5,                       /* READ  */
  YYSYMBOL_READSTRING = 6,                 /* READSTRING  */
  YYSYMBOL_PRINT = 7,                      /* PRINT  */
  YYSYMBOL_IF = 8,                         /* IF  */
  YYSYMBOL_THEN = 9,                       /* THEN  */
  YYSYMBOL_ELSE = 10,                      /* ELSE  */
  YYSYMBOL_ENDIF = 11,                     /* ENDIF  */
  YYSYMBOL_WHILE = 12,                     /* WHILE  */
  YYSYMBOL_DO = 13,                        /* DO  */
  YYSYMBOL_ENDWHILE = 14,                  /* ENDWHILE  */
  YYSYMBOL_REPEAT = 15,                    /* REPEAT  */
  YYSYMBOL_UNTIL = 16,                     /* UNTIL  */
  YYSYMBOL_FOR = 17,                       /* FOR  */
  YYSYMBOL_ENDFOR = 18,                    /* ENDFOR  */
  YYSYMBOL_FROM = 19,                      /* FROM  */
  YYSYMBOL_STEP = 20,                      /* STEP  */
  YYSYMBOL_TO = 21,                        /* TO  */
  YYSYMBOL_SWITCH = 22,                    /* SWITCH  */
  YYSYMBOL_CASE = 23,                      /* CASE  */
  YYSYMBOL_DEFAULT = 24,                   /* DEFAULT  */
  YYSYMBOL_ENDSWITCH = 25,                 /* ENDSWITCH  */
  YYSYMBOL_CLEARSCREEN = 26,               /* CLEARSCREEN  */
  YYSYMBOL_PLACE = 27,                     /* PLACE  */
  YYSYMBOL_TEXT = 28,                      /* TEXT  */
  YYSYMBOL_COLOR_YELLOW = 29,              /* COLOR_YELLOW  */
  YYSYMBOL_COLOR_BLUE = 30,                /* COLOR_BLUE  */
  YYSYMBOL_RESET_TEXT = 31,                /* RESET_TEXT  */
  YYSYMBOL_LETFCURLYBRACKET = 32,          /* LETFCURLYBRACKET  */
  YYSYMBOL_RIGHTCURLYBRACKET = 33,         /* RIGHTCURLYBRACKET  */
  YYSYMBOL_ASSIGNMENT = 34,                /* ASSIGNMENT  */
  YYSYMBOL_TERNARIO = 35,                  /* TERNARIO  */
  YYSYMBOL_COMMA = 36,                     /* COMMA  */
  YYSYMBOL_NUMBER = 37,                    /* NUMBER  */
  YYSYMBOL_BOOL = 38,                      /* BOOL  */
  YYSYMBOL_STRING = 39,                    /* STRING  */
  YYSYMBOL_VARIABLE = 40,                  /* VARIABLE  */
  YYSYMBOL_UNDEFINED = 41,                 /* UNDEFINED  */
  YYSYMBOL_CONSTANT = 42,                  /* CONSTANT  */
  YYSYMBOL_BUILTIN = 43,                   /* BUILTIN  */
  YYSYMBOL_OR = 44,                        /* OR  */
  YYSYMBOL_AND = 45,                       /* AND  */
  YYSYMBOL_GREATER_OR_EQUAL = 46,          /* GREATER_OR_EQUAL  */
  YYSYMBOL_LESS_OR_EQUAL = 47,             /* LESS_OR_EQUAL  */
  YYSYMBOL_GREATER_THAN = 48,              /* GREATER_THAN  */
  YYSYMBOL_LESS_THAN = 49,                 /* LESS_THAN  */
  YYSYMBOL_EQUAL = 50,                     /* EQUAL  */
  YYSYMBOL_NOT_EQUAL = 51,                 /* NOT_EQUAL  */
  YYSYMBOL_NOT = 52,                       /* NOT  */
  YYSYMBOL_PLUS = 53,                      /* PLUS  */
  YYSYMBOL_MINUS = 54,                     /* MINUS  */
  YYSYMBOL_MULTIPLICATION = 55,            /* MULTIPLICATION  */
  YYSYMBOL_DIVISION = 56,                  /* DIVISION  */
  YYSYMBOL_MODULO = 57,                    /* MODULO  */
  YYSYMBOL_FLOOR_DIV = 58,                 /* FLOOR_DIV  */
  YYSYMBOL_LPAREN = 59,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 60,                    /* RPAREN  */
  YYSYMBOL_CONCAT = 61,                    /* CONCAT  */
  YYSYMBOL_PLUS_EQUAL = 62,                /* PLUS_EQUAL  */
  YYSYMBOL_MINUS_EQUAL = 63,               /* MINUS_EQUAL  */
  YYSYMBOL_MULTIPLICATION_EQUAL = 64,      /* MULTIPLICATION_EQUAL  */
  YYSYMBOL_DIVISION_EQUAL = 65,            /* DIVISION_EQUAL  */
  YYSYMBOL_PLUS_PLUS = 66,                 /* PLUS_PLUS  */
  YYSYMBOL_MINUS_MINUS = 67,               /* MINUS_MINUS  */
  YYSYMBOL_FACT = 68,                      /* FACT  */
  YYSYMBOL_UNARY = 69,                     /* UNARY  */
  YYSYMBOL_POWER = 70,                     /* POWER  */
  YYSYMBOL_YYACCEPT = 71,                  /* $accept  */
  YYSYMBOL_program = 72,                   /* program  */
  YYSYMBOL_stmtlist = 73,                  /* stmtlist  */
  YYSYMBOL_stmt = 74,                      /* stmt  */
  YYSYMBOL_block = 75,                     /* block  */
  YYSYMBOL_controlSymbol = 76,             /* controlSymbol  */
  YYSYMBOL_if = 77,                        /* if  */
  YYSYMBOL_while = 78,                     /* while  */
  YYSYMBOL_repeat = 79,                    /* repeat  */
  YYSYMBOL_dowhile = 80,                   /* dowhile  */
  YYSYMBOL_for = 81,                       /* for  */
  YYSYMBOL_switch = 82,                    /* switch  */
  YYSYMBOL_case = 83,                      /* case  */
  YYSYMBOL_cond = 84,                      /* cond  */
  YYSYMBOL_asgn = 85,                      /* asgn  */
  YYSYMBOL_print = 86,                     /* print  */
  YYSYMBOL_read = 87,                      /* read  */
  YYSYMBOL_readstring = 88,                /* readstring  */
  YYSYMBOL_clearscreen = 89,               /* clearscreen  */
  YYSYMBOL_place = 90,                     /* place  */
  YYSYMBOL_text = 91,                      /* text  */
  YYSYMBOL_exp = 92,                       /* exp  */
  YYSYMBOL_listOfExp = 93,                 /* listOfExp  */
  YYSYMBOL_restOfListOfExp = 94            /* restOfListOfExp  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1141

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  71
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  88
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  211

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   325


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   253,   253,   267,   272,   295,   306,   311,   316,   321,
     326,   331,   336,   342,   348,   353,   358,   363,   368,   373,
     379,   387,   395,   403,   413,   425,   435,   446,   457,   465,
     475,   483,   493,   502,   514,   521,   527,   532,   536,   540,
     544,   548,   552,   556,   560,   564,   570,   575,   581,   588,
     595,   601,   606,   612,   616,   622,   629,   633,   637,   643,
     649,   655,   661,   667,   673,   679,   685,   691,   697,   704,
     710,   714,   718,   724,   730,   737,   784,   790,   796,   802,
     808,   814,   820,   826,   832,   842,   847,   858,   863
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "COLON",
  "READ", "READSTRING", "PRINT", "IF", "THEN", "ELSE", "ENDIF", "WHILE",
  "DO", "ENDWHILE", "REPEAT", "UNTIL", "FOR", "ENDFOR", "FROM", "STEP",
  "TO", "SWITCH", "CASE", "DEFAULT", "ENDSWITCH", "CLEARSCREEN", "PLACE",
  "TEXT", "COLOR_YELLOW", "COLOR_BLUE", "RESET_TEXT", "LETFCURLYBRACKET",
  "RIGHTCURLYBRACKET", "ASSIGNMENT", "TERNARIO", "COMMA", "NUMBER", "BOOL",
  "STRING", "VARIABLE", "UNDEFINED", "CONSTANT", "BUILTIN", "OR", "AND",
  "GREATER_OR_EQUAL", "LESS_OR_EQUAL", "GREATER_THAN", "LESS_THAN",
  "EQUAL", "NOT_EQUAL", "NOT", "PLUS", "MINUS", "MULTIPLICATION",
  "DIVISION", "MODULO", "FLOOR_DIV", "LPAREN", "RPAREN", "CONCAT",
  "PLUS_EQUAL", "MINUS_EQUAL", "MULTIPLICATION_EQUAL", "DIVISION_EQUAL",
  "PLUS_PLUS", "MINUS_MINUS", "FACT", "UNARY", "POWER", "$accept",
  "program", "stmtlist", "stmt", "block", "controlSymbol", "if", "while",
  "repeat", "dowhile", "for", "switch", "case", "cond", "asgn", "print",
  "read", "readstring", "clearscreen", "place", "text", "exp", "listOfExp",
  "restOfListOfExp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-60)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-35)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -60,    10,    75,   -60,   -60,   -60,   -41,   -16,   120,   -60,
     -60,   -60,   -60,   -60,   -60,   -10,    -8,    18,   -60,   -60,
     -25,     0,     5,    13,   -60,   -60,   -60,   -60,    47,    51,
     -60,   -60,    52,    53,    69,    74,    76,    81,    82,   -34,
     -14,   -60,   -60,   -60,   -60,    30,   120,   120,   120,   120,
     995,    34,    34,    62,   -60,    55,    34,    36,   120,   -60,
     -60,   315,   845,   120,   120,   120,   120,   -60,   -60,   863,
     -60,   -60,   -60,   -60,   -60,   -60,   -60,   -60,   -60,   -60,
     -60,    38,    39,    40,    44,   120,   165,    35,    35,   887,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   120,   120,   -60,   120,   120,    99,    96,
     -60,   357,    91,    89,   -60,   768,   -60,   -25,     0,   120,
      78,   -60,   995,   995,   995,   995,   995,   -60,   995,   -60,
     -60,   -60,   -60,   795,    54,   -60,  1021,  1046,  1071,  1071,
    1071,  1071,  1071,  1071,   588,   588,   -49,   -49,   -49,   -49,
     -24,    35,   914,   -60,   -60,   399,    34,   120,   -60,    -1,
     120,   941,   120,   120,   -60,   -60,   -60,   273,   441,   104,
     -60,   741,   120,   -60,   114,   -60,   968,    84,   822,   795,
     -60,   -60,   -60,    34,   120,   617,   120,   -60,   -60,   120,
     -60,   483,   -60,   683,   -60,   644,   526,   995,   -60,   -60,
     120,   185,   -60,   -60,   568,   710,   231,   -60,   -60,   610,
     -60
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     0,     1,     5,     6,     0,     0,     0,    22,
      22,    22,    22,    22,    22,    53,     0,     0,    58,     3,
       0,     0,     0,     0,     4,    20,    13,    14,     0,     0,
      17,    18,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    59,    73,    72,    74,     0,     0,     0,     0,     0,
      48,     0,     0,     0,     3,     0,     0,     0,     0,    56,
      57,     0,     0,     0,     0,     0,     0,    38,    41,     0,
      39,    42,    15,    16,     7,     8,     9,    10,    11,    12,
      19,     0,     0,     0,     0,    85,    84,    66,    67,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    71,     0,     0,     0,     0,
       3,     0,     0,     0,    54,     0,    21,    72,    74,     0,
       0,    36,    35,    37,    40,    43,    44,    47,    46,    49,
      50,    51,    52,    87,     0,    65,    83,    82,    77,    79,
      76,    78,    80,    81,    60,    61,    62,    63,    68,    64,
      70,    69,     0,     3,     3,     0,     0,     0,    22,     0,
       0,     0,     0,     0,    86,    75,    34,     0,     0,     0,
      26,     0,     0,    22,     0,    30,     0,    65,     0,    87,
       3,    23,    25,     0,     0,     0,     0,     3,    55,     0,
      88,     0,    27,     0,     3,     0,     0,    45,    24,     3,
       0,     0,     3,    31,     0,     0,     0,    28,     3,     0,
      29
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -60,   -60,   -19,   -60,   -60,    -9,   -60,   -60,   -60,   -60,
     -60,   -60,   -60,   -45,   -42,   -60,   -60,   -60,   -60,   -60,
     -60,   -33,   -60,   -59
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    24,    25,    51,    26,    27,    28,    29,
      30,    31,   159,   108,    32,    33,    34,    35,    36,    37,
      38,    50,   134,   164
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      61,    52,    53,    54,    55,    56,    81,   109,    82,    62,
       3,   113,   104,    86,    87,    88,    89,   120,    39,   105,
     121,   106,   173,   174,   175,   115,    83,   127,    84,   122,
     123,   124,   125,   126,    69,   111,   128,    63,    64,    65,
      66,    67,    68,    40,   105,    70,   106,    59,    60,    57,
      72,    58,   133,    71,    73,    74,    75,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,    76,   151,   152,    -2,     4,    77,     5,    78,
       6,     7,     8,     9,    79,    80,   161,    10,    11,    85,
      12,   155,    13,   107,   110,   112,   114,    14,   129,   130,
     131,    15,    16,    17,   132,   106,    18,    19,   153,   154,
     157,   170,   158,   162,   165,    20,   183,    21,   187,   -34,
     190,     0,     0,     0,   171,     0,     0,   176,     0,   178,
     179,     0,     0,     0,   167,   168,     0,     0,   192,   185,
       0,    22,    23,     0,     0,     0,     0,     0,     0,   172,
       0,   193,     0,   195,     0,     0,   197,    41,     0,    42,
      43,   191,    44,    45,   186,     0,     0,   205,   196,     0,
       0,     0,    46,    47,    48,   201,     0,     0,     0,    49,
     204,     0,     0,   206,     0,     0,     4,     0,     5,   209,
       6,     7,     8,     9,     0,     0,     0,    10,    11,     0,
      12,     0,    13,     0,     0,     0,     0,    14,   -32,   -32,
     -32,    15,    16,    17,     0,     0,    18,    19,    98,    99,
     100,   101,   102,   103,     0,    20,   104,    21,     0,     0,
       0,     0,     4,   105,     5,   106,     6,     7,     8,     9,
       0,     0,     0,    10,    11,     0,    12,     0,    13,     0,
       0,    22,    23,    14,   -33,   -33,   -33,    15,    16,    17,
       0,     0,    18,    19,     0,     0,     0,     0,     0,     0,
       0,    20,     0,    21,     4,     0,     5,     0,     6,     7,
       8,     9,     0,   180,   181,    10,    11,     0,    12,     0,
      13,     0,     0,     0,     0,    14,     0,    22,    23,    15,
      16,    17,     0,     0,    18,    19,     0,     0,     0,     0,
       0,     0,     0,    20,     0,    21,     4,     0,     5,     0,
       6,     7,     8,     9,     0,     0,     0,    10,    11,     0,
      12,     0,    13,     0,     0,     0,     0,    14,     0,    22,
      23,    15,    16,    17,     0,     0,    18,    19,   116,     0,
       0,     0,     0,     0,     0,    20,     0,    21,     4,     0,
       5,     0,     6,     7,     8,     9,     0,     0,     0,    10,
      11,     0,    12,   156,    13,     0,     0,     0,     0,    14,
       0,    22,    23,    15,    16,    17,     0,     0,    18,    19,
       0,     0,     0,     0,     0,     0,     0,    20,     0,    21,
       4,     0,     5,     0,     6,     7,     8,     9,     0,     0,
       0,    10,    11,     0,    12,     0,    13,     0,     0,     0,
       0,    14,     0,    22,    23,    15,    16,    17,     0,     0,
      18,    19,   169,     0,     0,     0,     0,     0,     0,    20,
       0,    21,     4,     0,     5,     0,     6,     7,     8,     9,
       0,     0,     0,    10,    11,   182,    12,     0,    13,     0,
       0,     0,     0,    14,     0,    22,    23,    15,    16,    17,
       0,     0,    18,    19,     0,     0,     0,     0,     0,     0,
       0,    20,     0,    21,     4,     0,     5,     0,     6,     7,
       8,     9,     0,     0,   198,    10,    11,     0,    12,     0,
      13,     0,     0,     0,     0,    14,     0,    22,    23,    15,
      16,    17,     0,     0,    18,    19,     0,     0,     0,     0,
       0,     0,     0,    20,     0,    21,     0,     4,     0,     5,
       0,     6,     7,     8,     9,     0,     0,     0,    10,    11,
       0,    12,     0,    13,     0,     0,     0,     0,    14,    22,
      23,   203,    15,    16,    17,     0,     0,    18,    19,     0,
       0,     0,     0,     0,     0,     0,    20,     0,    21,     4,
       0,     5,     0,     6,     7,     8,     9,     0,     0,     0,
      10,    11,     0,    12,     0,    13,   207,     0,     0,     0,
      14,     0,    22,    23,    15,    16,    17,     0,     0,    18,
      19,     0,     0,     0,     0,     0,     0,     0,    20,     0,
      21,     4,     0,     5,     0,     6,     7,     8,     9,     0,
       0,   194,    10,    11,     0,    12,     0,    13,   210,     0,
       0,     0,    14,     0,    22,    23,    15,    16,    17,     0,
       0,    18,    19,   100,   101,   102,   103,     0,   202,   104,
      20,     0,    21,     0,     0,     0,   105,     0,   106,     0,
       0,    90,    91,    92,    93,    94,    95,    96,    97,     0,
      98,    99,   100,   101,   102,   103,    22,    23,   104,     0,
       0,     0,     0,     0,     0,   105,     0,   106,    90,    91,
      92,    93,    94,    95,    96,    97,   199,    98,    99,   100,
     101,   102,   103,   200,     0,   104,     0,     0,     0,     0,
       0,     0,   105,     0,   106,     0,     0,     0,     0,     0,
       0,     0,     0,   208,     0,     0,     0,    90,    91,    92,
      93,    94,    95,    96,    97,     0,    98,    99,   100,   101,
     102,   103,     0,     0,   104,     0,     0,     0,     0,     0,
       0,   105,     0,   106,    90,    91,    92,    93,    94,    95,
      96,    97,   184,    98,    99,   100,   101,   102,   103,     0,
       0,   104,     0,     0,     0,     0,     0,     0,   105,     0,
     106,     0,     0,     0,     0,    90,    91,    92,    93,    94,
      95,    96,    97,     0,    98,    99,   100,   101,   102,   103,
       0,     0,   104,     0,   160,     0,     0,     0,     0,   105,
       0,   106,    90,    91,    92,    93,    94,    95,    96,    97,
       0,    98,    99,   100,   101,   102,   103,     0,     0,   104,
       0,   163,     0,     0,     0,     0,   105,     0,   106,    90,
      91,    92,    93,    94,    95,    96,    97,     0,    98,    99,
     100,   101,   102,   103,     0,     0,   104,     0,   189,     0,
       0,     0,     0,   105,     0,   106,    90,    91,    92,    93,
      94,    95,    96,    97,     0,    98,    99,   100,   101,   102,
     103,     0,    41,   104,    42,   117,     0,   118,    45,     0,
     105,     0,   106,     0,     0,     0,     0,    46,    47,    48,
      41,     0,    42,   117,   119,   118,    45,     0,     0,     0,
       0,    22,    23,     0,     0,    46,    47,    48,     0,     0,
       0,     0,    49,     0,     0,     0,     0,     0,     0,    22,
      23,    90,    91,    92,    93,    94,    95,    96,    97,     0,
      98,    99,   100,   101,   102,   103,     0,   135,   104,     0,
       0,     0,     0,     0,     0,   105,     0,   106,    90,    91,
      92,    93,    94,    95,    96,    97,     0,    98,    99,   100,
     101,   102,   103,     0,   166,   104,     0,     0,     0,     0,
       0,     0,   105,     0,   106,    90,    91,    92,    93,    94,
      95,    96,    97,     0,    98,    99,   100,   101,   102,   103,
       0,   177,   104,     0,     0,     0,     0,     0,     0,   105,
       0,   106,    90,    91,    92,    93,    94,    95,    96,    97,
       0,    98,    99,   100,   101,   102,   103,     0,   188,   104,
       0,     0,     0,     0,     0,     0,   105,     0,   106,    90,
      91,    92,    93,    94,    95,    96,    97,     0,    98,    99,
     100,   101,   102,   103,     0,     0,   104,     0,     0,     0,
       0,     0,     0,   105,     0,   106,    91,    92,    93,    94,
      95,    96,    97,     0,    98,    99,   100,   101,   102,   103,
       0,     0,   104,     0,     0,     0,     0,     0,     0,   105,
       0,   106,    92,    93,    94,    95,    96,    97,     0,    98,
      99,   100,   101,   102,   103,     0,     0,   104,     0,     0,
       0,     0,     0,     0,   105,     0,   106,   -35,   -35,   -35,
     -35,   -35,   -35,     0,    98,    99,   100,   101,   102,   103,
       0,     0,   104,     0,     0,     0,     0,     0,     0,   105,
       0,   106
};

static const yytype_int16 yycheck[] =
{
      19,    10,    11,    12,    13,    14,    40,    52,    42,    34,
       0,    56,    61,    46,    47,    48,    49,    62,    59,    68,
      62,    70,    23,    24,    25,    58,    40,    69,    42,    62,
      63,    64,    65,    66,    34,    54,    69,    62,    63,    64,
      65,    66,    67,    59,    68,    40,    70,    29,    30,    59,
       3,    59,    85,    40,     3,     3,     3,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,     3,   106,   107,     0,     1,     3,     3,     3,
       5,     6,     7,     8,     3,     3,   119,    12,    13,    59,
      15,   110,    17,    59,    32,    40,    60,    22,    60,    60,
      60,    26,    27,    28,    60,    70,    31,    32,     9,    13,
      19,   156,    23,    35,    60,    40,    12,    42,     4,    35,
     179,    -1,    -1,    -1,   157,    -1,    -1,   160,    -1,   162,
     163,    -1,    -1,    -1,   153,   154,    -1,    -1,   183,   172,
      -1,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,   158,
      -1,   184,    -1,   186,    -1,    -1,   189,    37,    -1,    39,
      40,   180,    42,    43,   173,    -1,    -1,   200,   187,    -1,
      -1,    -1,    52,    53,    54,   194,    -1,    -1,    -1,    59,
     199,    -1,    -1,   202,    -1,    -1,     1,    -1,     3,   208,
       5,     6,     7,     8,    -1,    -1,    -1,    12,    13,    -1,
      15,    -1,    17,    -1,    -1,    -1,    -1,    22,    23,    24,
      25,    26,    27,    28,    -1,    -1,    31,    32,    53,    54,
      55,    56,    57,    58,    -1,    40,    61,    42,    -1,    -1,
      -1,    -1,     1,    68,     3,    70,     5,     6,     7,     8,
      -1,    -1,    -1,    12,    13,    -1,    15,    -1,    17,    -1,
      -1,    66,    67,    22,    23,    24,    25,    26,    27,    28,
      -1,    -1,    31,    32,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    40,    -1,    42,     1,    -1,     3,    -1,     5,     6,
       7,     8,    -1,    10,    11,    12,    13,    -1,    15,    -1,
      17,    -1,    -1,    -1,    -1,    22,    -1,    66,    67,    26,
      27,    28,    -1,    -1,    31,    32,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    40,    -1,    42,     1,    -1,     3,    -1,
       5,     6,     7,     8,    -1,    -1,    -1,    12,    13,    -1,
      15,    -1,    17,    -1,    -1,    -1,    -1,    22,    -1,    66,
      67,    26,    27,    28,    -1,    -1,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    40,    -1,    42,     1,    -1,
       3,    -1,     5,     6,     7,     8,    -1,    -1,    -1,    12,
      13,    -1,    15,    16,    17,    -1,    -1,    -1,    -1,    22,
      -1,    66,    67,    26,    27,    28,    -1,    -1,    31,    32,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,    42,
       1,    -1,     3,    -1,     5,     6,     7,     8,    -1,    -1,
      -1,    12,    13,    -1,    15,    -1,    17,    -1,    -1,    -1,
      -1,    22,    -1,    66,    67,    26,    27,    28,    -1,    -1,
      31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    40,
      -1,    42,     1,    -1,     3,    -1,     5,     6,     7,     8,
      -1,    -1,    -1,    12,    13,    14,    15,    -1,    17,    -1,
      -1,    -1,    -1,    22,    -1,    66,    67,    26,    27,    28,
      -1,    -1,    31,    32,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    40,    -1,    42,     1,    -1,     3,    -1,     5,     6,
       7,     8,    -1,    -1,    11,    12,    13,    -1,    15,    -1,
      17,    -1,    -1,    -1,    -1,    22,    -1,    66,    67,    26,
      27,    28,    -1,    -1,    31,    32,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    40,    -1,    42,    -1,     1,    -1,     3,
      -1,     5,     6,     7,     8,    -1,    -1,    -1,    12,    13,
      -1,    15,    -1,    17,    -1,    -1,    -1,    -1,    22,    66,
      67,    25,    26,    27,    28,    -1,    -1,    31,    32,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,    42,     1,
      -1,     3,    -1,     5,     6,     7,     8,    -1,    -1,    -1,
      12,    13,    -1,    15,    -1,    17,    18,    -1,    -1,    -1,
      22,    -1,    66,    67,    26,    27,    28,    -1,    -1,    31,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      42,     1,    -1,     3,    -1,     5,     6,     7,     8,    -1,
      -1,     4,    12,    13,    -1,    15,    -1,    17,    18,    -1,
      -1,    -1,    22,    -1,    66,    67,    26,    27,    28,    -1,
      -1,    31,    32,    55,    56,    57,    58,    -1,     4,    61,
      40,    -1,    42,    -1,    -1,    -1,    68,    -1,    70,    -1,
      -1,    44,    45,    46,    47,    48,    49,    50,    51,    -1,
      53,    54,    55,    56,    57,    58,    66,    67,    61,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    -1,    70,    44,    45,
      46,    47,    48,    49,    50,    51,    13,    53,    54,    55,
      56,    57,    58,    20,    -1,    61,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    -1,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    13,    -1,    -1,    -1,    44,    45,    46,
      47,    48,    49,    50,    51,    -1,    53,    54,    55,    56,
      57,    58,    -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    -1,    70,    44,    45,    46,    47,    48,    49,
      50,    51,    21,    53,    54,    55,    56,    57,    58,    -1,
      -1,    61,    -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,
      70,    -1,    -1,    -1,    -1,    44,    45,    46,    47,    48,
      49,    50,    51,    -1,    53,    54,    55,    56,    57,    58,
      -1,    -1,    61,    -1,    36,    -1,    -1,    -1,    -1,    68,
      -1,    70,    44,    45,    46,    47,    48,    49,    50,    51,
      -1,    53,    54,    55,    56,    57,    58,    -1,    -1,    61,
      -1,    36,    -1,    -1,    -1,    -1,    68,    -1,    70,    44,
      45,    46,    47,    48,    49,    50,    51,    -1,    53,    54,
      55,    56,    57,    58,    -1,    -1,    61,    -1,    36,    -1,
      -1,    -1,    -1,    68,    -1,    70,    44,    45,    46,    47,
      48,    49,    50,    51,    -1,    53,    54,    55,    56,    57,
      58,    -1,    37,    61,    39,    40,    -1,    42,    43,    -1,
      68,    -1,    70,    -1,    -1,    -1,    -1,    52,    53,    54,
      37,    -1,    39,    40,    59,    42,    43,    -1,    -1,    -1,
      -1,    66,    67,    -1,    -1,    52,    53,    54,    -1,    -1,
      -1,    -1,    59,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      67,    44,    45,    46,    47,    48,    49,    50,    51,    -1,
      53,    54,    55,    56,    57,    58,    -1,    60,    61,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    -1,    70,    44,    45,
      46,    47,    48,    49,    50,    51,    -1,    53,    54,    55,
      56,    57,    58,    -1,    60,    61,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    -1,    70,    44,    45,    46,    47,    48,
      49,    50,    51,    -1,    53,    54,    55,    56,    57,    58,
      -1,    60,    61,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      -1,    70,    44,    45,    46,    47,    48,    49,    50,    51,
      -1,    53,    54,    55,    56,    57,    58,    -1,    60,    61,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,    70,    44,
      45,    46,    47,    48,    49,    50,    51,    -1,    53,    54,
      55,    56,    57,    58,    -1,    -1,    61,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    -1,    70,    45,    46,    47,    48,
      49,    50,    51,    -1,    53,    54,    55,    56,    57,    58,
      -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      -1,    70,    46,    47,    48,    49,    50,    51,    -1,    53,
      54,    55,    56,    57,    58,    -1,    -1,    61,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    -1,    70,    46,    47,    48,
      49,    50,    51,    -1,    53,    54,    55,    56,    57,    58,
      -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      -1,    70
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    72,    73,     0,     1,     3,     5,     6,     7,     8,
      12,    13,    15,    17,    22,    26,    27,    28,    31,    32,
      40,    42,    66,    67,    74,    75,    77,    78,    79,    80,
      81,    82,    85,    86,    87,    88,    89,    90,    91,    59,
      59,    37,    39,    40,    42,    43,    52,    53,    54,    59,
      92,    76,    76,    76,    76,    76,    76,    59,    59,    29,
      30,    73,    34,    62,    63,    64,    65,    66,    67,    34,
      40,    40,     3,     3,     3,     3,     3,     3,     3,     3,
       3,    40,    42,    40,    42,    59,    92,    92,    92,    92,
      44,    45,    46,    47,    48,    49,    50,    51,    53,    54,
      55,    56,    57,    58,    61,    68,    70,    59,    84,    84,
      32,    73,    40,    84,    60,    92,    33,    40,    42,    59,
      84,    85,    92,    92,    92,    92,    92,    85,    92,    60,
      60,    60,    60,    92,    93,    60,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,     9,    13,    73,    16,    19,    23,    83,
      36,    92,    35,    36,    94,    60,    60,    73,    73,    33,
      84,    92,    76,    23,    24,    25,    92,    60,    92,    92,
      10,    11,    14,    12,    21,    92,    76,     4,    60,    36,
      94,    73,    84,    92,     4,    92,    73,    92,    11,    13,
      20,    73,     4,    25,    73,    92,    73,    18,    13,    73,
      18
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    71,    72,    73,    73,    73,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    75,    76,    77,    77,    78,    79,    80,    81,    81,
      82,    82,    83,    83,    84,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    86,    87,
      87,    88,    88,    89,    89,    90,    91,    91,    91,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    93,    93,    94,    94
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     1,     2,     2,     2,
       2,     2,     2,     1,     1,     2,     2,     1,     1,     2,
       1,     3,     0,     6,     8,     6,     5,     7,    10,    12,
       5,     8,     5,     6,     3,     3,     3,     3,     2,     2,
       3,     2,     2,     3,     3,     7,     3,     3,     2,     4,
       4,     4,     4,     1,     3,     6,     2,     2,     1,     1,
       3,     3,     3,     3,     3,     3,     2,     2,     3,     3,
       3,     2,     1,     1,     1,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     0,     2,     0,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: stmtlist  */
#line 254 "interpreter.y"
                  { 
		    // Create a new AST
			(yyval.prog) = new lp::AST((yyvsp[0].stmts)); 

			// Assign the AST to the root
			root = (yyval.prog); 

			// End of parsing
			//	return 1;
		  }
#line 1877 "interpreter.tab.c"
    break;

  case 3: /* stmtlist: %empty  */
#line 267 "interpreter.y"
                  { 
			// create a empty list of statements
			(yyval.stmts) = new std::list<lp::Statement *>(); 
		  }
#line 1886 "interpreter.tab.c"
    break;

  case 4: /* stmtlist: stmtlist stmt  */
#line 273 "interpreter.y"
                  { 
			// copy up the list and add the stmt to it
			(yyval.stmts) = (yyvsp[-1].stmts);
			(yyval.stmts)->push_back((yyvsp[0].st));

			// Control the interative mode of execution of the interpreter
			if (interactiveMode == true && control == 0)
 			{
				for(std::list<lp::Statement *>::iterator it = (yyval.stmts)->begin(); 
						it != (yyval.stmts)->end(); 
						it++)
				{
					/*(*it)->printAST();*/
					(*it)->evaluate();
					
				}

				// Delete the AST code, because it has already run in the interactive mode.
				(yyval.stmts)->clear();
			}
		}
#line 1912 "interpreter.tab.c"
    break;

  case 5: /* stmtlist: stmtlist error  */
#line 296 "interpreter.y"
      { 
			 // just copy up the stmtlist when an error occurs
			 (yyval.stmts) = (yyvsp[-1].stmts);

			 // The previous look-ahead token ought to be discarded with `yyclearin;'
			 yyclearin; 
       }
#line 1924 "interpreter.tab.c"
    break;

  case 6: /* stmt: SEMICOLON  */
#line 307 "interpreter.y"
          {
		// Create a new empty statement node
		(yyval.st) = new lp::EmptyStmt(); 
	  }
#line 1933 "interpreter.tab.c"
    break;

  case 7: /* stmt: asgn SEMICOLON  */
#line 312 "interpreter.y"
          {
		// Default action
		// $$ = $1;
	  }
#line 1942 "interpreter.tab.c"
    break;

  case 8: /* stmt: print SEMICOLON  */
#line 317 "interpreter.y"
          {
		// Default action
		// $$ = $1;
	  }
#line 1951 "interpreter.tab.c"
    break;

  case 9: /* stmt: read SEMICOLON  */
#line 322 "interpreter.y"
          {
		// Default action
		// $$ = $1;
	  }
#line 1960 "interpreter.tab.c"
    break;

  case 10: /* stmt: readstring SEMICOLON  */
#line 327 "interpreter.y"
          {
	 	// Default action
	 	// $$ = $1;
	  }
#line 1969 "interpreter.tab.c"
    break;

  case 11: /* stmt: clearscreen SEMICOLON  */
#line 332 "interpreter.y"
          {
 	 	// Default action
 	 	// $$ = $1;
	  }
#line 1978 "interpreter.tab.c"
    break;

  case 12: /* stmt: place SEMICOLON  */
#line 337 "interpreter.y"
          {
 	 	// Default action
 	 	// $$ = $1;
	  }
#line 1987 "interpreter.tab.c"
    break;

  case 13: /* stmt: if  */
#line 343 "interpreter.y"
         {
		// Default action
		// $$ = $1;
	 }
#line 1996 "interpreter.tab.c"
    break;

  case 14: /* stmt: while  */
#line 349 "interpreter.y"
         {
		// Default action
		// $$ = $1;
	 }
#line 2005 "interpreter.tab.c"
    break;

  case 15: /* stmt: repeat SEMICOLON  */
#line 354 "interpreter.y"
         {
		// Default action
		// $$ = $1;
	 }
#line 2014 "interpreter.tab.c"
    break;

  case 16: /* stmt: dowhile SEMICOLON  */
#line 359 "interpreter.y"
         {
		// Default action
		// $$ = $1;
	 }
#line 2023 "interpreter.tab.c"
    break;

  case 17: /* stmt: for  */
#line 364 "interpreter.y"
         {
		// Default action
		// $$ = $1;
	 }
#line 2032 "interpreter.tab.c"
    break;

  case 18: /* stmt: switch  */
#line 369 "interpreter.y"
         {
		// Default action
		// $$ = $1;
	 }
#line 2041 "interpreter.tab.c"
    break;

  case 19: /* stmt: text SEMICOLON  */
#line 374 "interpreter.y"
          {
	  	// Default action
	  	// $$ = $1;
	  }
#line 2050 "interpreter.tab.c"
    break;

  case 20: /* stmt: block  */
#line 380 "interpreter.y"
         {
		// Default action
		// $$ = $1;
	 }
#line 2059 "interpreter.tab.c"
    break;

  case 21: /* block: LETFCURLYBRACKET stmtlist RIGHTCURLYBRACKET  */
#line 388 "interpreter.y"
                {
			// Create a new block of statements node
			(yyval.st) = new lp::BlockStmt((yyvsp[-1].stmts)); 
		}
#line 2068 "interpreter.tab.c"
    break;

  case 22: /* controlSymbol: %empty  */
#line 395 "interpreter.y"
                {
			// To control the interactive mode in "if" and "while" sentences
			control++;
		}
#line 2077 "interpreter.tab.c"
    break;

  case 23: /* if: IF controlSymbol cond THEN stmtlist ENDIF  */
#line 404 "interpreter.y"
    {
		// Create a new if statement node
		(yyval.st) = new lp::IfStmt((yyvsp[-3].expNode), new lp::BlockStmt((yyvsp[-1].stmts)));

		// To control the interactive mode
		control--;
	}
#line 2089 "interpreter.tab.c"
    break;

  case 24: /* if: IF controlSymbol cond THEN stmtlist ELSE stmtlist ENDIF  */
#line 414 "interpreter.y"
         {
		// Create a new if statement node
		
		(yyval.st) = new lp::IfStmt((yyvsp[-5].expNode), new lp::BlockStmt((yyvsp[-3].stmts)), new lp::BlockStmt((yyvsp[-1].stmts)));

		// To control the interactive mode
		control--;
	 }
#line 2102 "interpreter.tab.c"
    break;

  case 25: /* while: WHILE controlSymbol cond DO stmtlist ENDWHILE  */
#line 426 "interpreter.y"
                {
			// Create a new while statement node
			(yyval.st) = new lp::WhileStmt((yyvsp[-3].expNode),  new lp::BlockStmt((yyvsp[-1].stmts)));

			// To control the interactive mode
			control--;
    	}
#line 2114 "interpreter.tab.c"
    break;

  case 26: /* repeat: REPEAT controlSymbol stmtlist UNTIL cond  */
#line 436 "interpreter.y"
                {
			// Create a new repeat statement node
			(yyval.st) = new lp::RepeatStmt(new lp::BlockStmt((yyvsp[-2].stmts)), (yyvsp[0].expNode));

			// To control the interactive mode
			control--;
    	}
#line 2126 "interpreter.tab.c"
    break;

  case 27: /* dowhile: DO controlSymbol LETFCURLYBRACKET stmtlist RIGHTCURLYBRACKET WHILE cond  */
#line 447 "interpreter.y"
                {
			// Create a new dowhile statement node
			(yyval.st) = new lp::RepeatStmt(new lp::BlockStmt((yyvsp[-3].stmts)), (yyvsp[0].expNode));

			// To control the interactive mode
			control--;
    	}
#line 2138 "interpreter.tab.c"
    break;

  case 28: /* for: FOR controlSymbol VARIABLE FROM exp TO exp DO stmtlist ENDFOR  */
#line 458 "interpreter.y"
        {
		// Create a new for statement node
		(yyval.st) = new lp::ForStmt((yyvsp[-7].string), (yyvsp[-5].expNode), (yyvsp[-3].expNode), new lp::BlockStmt((yyvsp[-1].stmts)));
		
		// To control the interactive mode
		control--;
	}
#line 2150 "interpreter.tab.c"
    break;

  case 29: /* for: FOR controlSymbol VARIABLE FROM exp TO exp STEP exp DO stmtlist ENDFOR  */
#line 466 "interpreter.y"
        {
		// Create a new for statement node
		(yyval.st) = new lp::ForStmt((yyvsp[-9].string), (yyvsp[-7].expNode), (yyvsp[-5].expNode), (yyvsp[-3].expNode), new lp::BlockStmt((yyvsp[-1].stmts)));
		
		// To control the interactive mode
		control--;
	}
#line 2162 "interpreter.tab.c"
    break;

  case 30: /* switch: SWITCH controlSymbol cond case ENDSWITCH  */
#line 476 "interpreter.y"
                {
		// Create a new switch statement node
			(yyval.st) = new lp::SwitchStmt((yyvsp[-2].expNode), (yyvsp[-1].cases));

			// To control the interactive mode
			control--;
    	}
#line 2174 "interpreter.tab.c"
    break;

  case 31: /* switch: SWITCH controlSymbol cond case DEFAULT COLON stmtlist ENDSWITCH  */
#line 484 "interpreter.y"
                {
			// Create a new switch statement node
			(yyval.st) = new lp::SwitchStmt((yyvsp[-5].expNode), (yyvsp[-4].cases), new lp::BlockStmt((yyvsp[-1].stmts)));

			// To control the interactive mode
			control--;
	}
#line 2186 "interpreter.tab.c"
    break;

  case 32: /* case: CASE controlSymbol exp COLON stmtlist  */
#line 494 "interpreter.y"
                {
			// Create a new case list statement node
			(yyval.cases) = new std::list<lp::CaseStmt *>();
			(yyval.cases)->push_back(new lp::CaseStmt((yyvsp[-2].expNode), new lp::BlockStmt((yyvsp[0].stmts))));

			// To control the interactive mode
			control--;
    	}
#line 2199 "interpreter.tab.c"
    break;

  case 33: /* case: case CASE controlSymbol exp COLON stmtlist  */
#line 503 "interpreter.y"
                {
			// Create a new case list statement node
			(yyval.cases) = (yyvsp[-5].cases);
			(yyval.cases)->push_back(new lp::CaseStmt((yyvsp[-2].expNode), new lp::BlockStmt((yyvsp[0].stmts))));

			// To control the interactive mode
			control--;
    	}
#line 2212 "interpreter.tab.c"
    break;

  case 34: /* cond: LPAREN exp RPAREN  */
#line 515 "interpreter.y"
                { 
			(yyval.expNode) = (yyvsp[-1].expNode);
		}
#line 2220 "interpreter.tab.c"
    break;

  case 35: /* asgn: VARIABLE ASSIGNMENT exp  */
#line 522 "interpreter.y"
                { 
			// Create a new assignment node
			(yyval.st) = new lp::AssignmentStmt((yyvsp[-2].string), (yyvsp[0].expNode));
		}
#line 2229 "interpreter.tab.c"
    break;

  case 36: /* asgn: VARIABLE ASSIGNMENT asgn  */
#line 528 "interpreter.y"
                { 
			// Create a new assignment node
			(yyval.st) = new lp::AssignmentStmt((yyvsp[-2].string), (lp::AssignmentStmt *) (yyvsp[0].st));
		}
#line 2238 "interpreter.tab.c"
    break;

  case 37: /* asgn: VARIABLE PLUS_EQUAL exp  */
#line 533 "interpreter.y"
                {
			(yyval.st) = new lp::AssignmentStmt((yyvsp[-2].string), new lp::PlusNode(new lp::VariableNode((yyvsp[-2].string)), (yyvsp[0].expNode)));
		}
#line 2246 "interpreter.tab.c"
    break;

  case 38: /* asgn: VARIABLE PLUS_PLUS  */
#line 537 "interpreter.y"
                {
			(yyval.st) = new lp::AssignmentStmt((yyvsp[-1].string), new lp::PlusNode(new lp::VariableNode((yyvsp[-1].string)), new lp::NumberNode(1)));
		}
#line 2254 "interpreter.tab.c"
    break;

  case 39: /* asgn: PLUS_PLUS VARIABLE  */
#line 541 "interpreter.y"
                {
			(yyval.st) = new lp::AssignmentStmt((yyvsp[0].string), new lp::PlusNode(new lp::VariableNode((yyvsp[0].string)), new lp::NumberNode(1)));
		}
#line 2262 "interpreter.tab.c"
    break;

  case 40: /* asgn: VARIABLE MINUS_EQUAL exp  */
#line 545 "interpreter.y"
                {
			(yyval.st) = new lp::AssignmentStmt((yyvsp[-2].string), new lp::MinusNode(new lp::VariableNode((yyvsp[-2].string)), (yyvsp[0].expNode)));
		}
#line 2270 "interpreter.tab.c"
    break;

  case 41: /* asgn: VARIABLE MINUS_MINUS  */
#line 549 "interpreter.y"
                {
			(yyval.st) = new lp::AssignmentStmt((yyvsp[-1].string), new lp::MinusNode(new lp::VariableNode((yyvsp[-1].string)), new lp::NumberNode(1)));
		}
#line 2278 "interpreter.tab.c"
    break;

  case 42: /* asgn: MINUS_MINUS VARIABLE  */
#line 553 "interpreter.y"
                {
			(yyval.st) = new lp::AssignmentStmt((yyvsp[0].string), new lp::MinusNode(new lp::VariableNode((yyvsp[0].string)), new lp::NumberNode(1)));
		}
#line 2286 "interpreter.tab.c"
    break;

  case 43: /* asgn: VARIABLE MULTIPLICATION_EQUAL exp  */
#line 557 "interpreter.y"
                {
			(yyval.st) = new lp::AssignmentStmt((yyvsp[-2].string), new lp::MultiplicationNode(new lp::VariableNode((yyvsp[-2].string)), (yyvsp[0].expNode)));
		}
#line 2294 "interpreter.tab.c"
    break;

  case 44: /* asgn: VARIABLE DIVISION_EQUAL exp  */
#line 561 "interpreter.y"
                {
			(yyval.st) = new lp::AssignmentStmt((yyvsp[-2].string), new lp::DivisionNode(new lp::VariableNode((yyvsp[-2].string)), (yyvsp[0].expNode)));
		}
#line 2302 "interpreter.tab.c"
    break;

  case 45: /* asgn: VARIABLE ASSIGNMENT cond TERNARIO exp COMMA exp  */
#line 565 "interpreter.y"
                {
		    (yyval.st) = new lp::AssignmentStmt((yyvsp[-6].string), new lp::AlternativeNode((yyvsp[-4].expNode), (yyvsp[-2].expNode), (yyvsp[0].expNode)));
		}
#line 2310 "interpreter.tab.c"
    break;

  case 46: /* asgn: CONSTANT ASSIGNMENT exp  */
#line 571 "interpreter.y"
                {   
 			execerror("Semantic error in assignment: it is not allowed to modify a constant ", (yyvsp[-2].string));
		}
#line 2318 "interpreter.tab.c"
    break;

  case 47: /* asgn: CONSTANT ASSIGNMENT asgn  */
#line 576 "interpreter.y"
                {   
 			execerror("Semantic error in multiple assignment: it is not allowed to modify a constant ",(yyvsp[-2].string));
		}
#line 2326 "interpreter.tab.c"
    break;

  case 48: /* print: PRINT exp  */
#line 582 "interpreter.y"
                {
			// Create a new print node
			 (yyval.st) = new lp::PrintStmt((yyvsp[0].expNode));
		}
#line 2335 "interpreter.tab.c"
    break;

  case 49: /* read: READ LPAREN VARIABLE RPAREN  */
#line 589 "interpreter.y"
                {
			// Create a new read node
			 (yyval.st) = new lp::ReadStmt((yyvsp[-1].string));
		}
#line 2344 "interpreter.tab.c"
    break;

  case 50: /* read: READ LPAREN CONSTANT RPAREN  */
#line 596 "interpreter.y"
                {   
 			execerror("Semantic error in \"read statement\": it is not allowed to modify a constant ",(yyvsp[-1].string));
		}
#line 2352 "interpreter.tab.c"
    break;

  case 51: /* readstring: READSTRING LPAREN VARIABLE RPAREN  */
#line 602 "interpreter.y"
                    {
		    	// Create a new readstring node
		    	(yyval.st) = new lp::ReadStringStmt((yyvsp[-1].string));
		    }
#line 2361 "interpreter.tab.c"
    break;

  case 52: /* readstring: READSTRING LPAREN CONSTANT RPAREN  */
#line 607 "interpreter.y"
                    {   
 		    	execerror("Semantic error in \"readstring statement\": it is not allowed to modify a constant ",(yyvsp[-1].string));
		    }
#line 2369 "interpreter.tab.c"
    break;

  case 53: /* clearscreen: CLEARSCREEN  */
#line 613 "interpreter.y"
                                {
			 		(yyval.st) = new lp::ClearScreenStmt();
				}
#line 2377 "interpreter.tab.c"
    break;

  case 54: /* clearscreen: CLEARSCREEN LPAREN RPAREN  */
#line 617 "interpreter.y"
                                {   
			 		(yyval.st) = new lp::ClearScreenStmt();
 				}
#line 2385 "interpreter.tab.c"
    break;

  case 55: /* place: PLACE LPAREN exp COMMA exp RPAREN  */
#line 623 "interpreter.y"
                {
			// Create a new place(row,col) node
			(yyval.st) = new lp::PlaceStmt((yyvsp[-3].expNode), (yyvsp[-1].expNode));
		}
#line 2394 "interpreter.tab.c"
    break;

  case 56: /* text: TEXT COLOR_YELLOW  */
#line 630 "interpreter.y"
                {
			(yyval.st) = new lp::TextStmt(YELLOW);
		}
#line 2402 "interpreter.tab.c"
    break;

  case 57: /* text: TEXT COLOR_BLUE  */
#line 634 "interpreter.y"
                {
			(yyval.st) = new lp::TextStmt(BLUE);
		}
#line 2410 "interpreter.tab.c"
    break;

  case 58: /* text: RESET_TEXT  */
#line 638 "interpreter.y"
                {
			(yyval.st) = new lp::TextStmt(RESET);
		}
#line 2418 "interpreter.tab.c"
    break;

  case 59: /* exp: NUMBER  */
#line 644 "interpreter.y"
                { 
			// Create a new number node
			(yyval.expNode) = new lp::NumberNode((yyvsp[0].number));
		}
#line 2427 "interpreter.tab.c"
    break;

  case 60: /* exp: exp PLUS exp  */
#line 650 "interpreter.y"
                { 
			// Create a new plus node
			 (yyval.expNode) = new lp::PlusNode((yyvsp[-2].expNode), (yyvsp[0].expNode));
		 }
#line 2436 "interpreter.tab.c"
    break;

  case 61: /* exp: exp MINUS exp  */
#line 656 "interpreter.y"
        {
			// Create a new minus node
			(yyval.expNode) = new lp::MinusNode((yyvsp[-2].expNode), (yyvsp[0].expNode));
		}
#line 2445 "interpreter.tab.c"
    break;

  case 62: /* exp: exp MULTIPLICATION exp  */
#line 662 "interpreter.y"
                { 
			// Create a new multiplication node
			(yyval.expNode) = new lp::MultiplicationNode((yyvsp[-2].expNode), (yyvsp[0].expNode));
		}
#line 2454 "interpreter.tab.c"
    break;

  case 63: /* exp: exp DIVISION exp  */
#line 668 "interpreter.y"
                {
		  // Create a new division node	
		  (yyval.expNode) = new lp::DivisionNode((yyvsp[-2].expNode), (yyvsp[0].expNode));
	   }
#line 2463 "interpreter.tab.c"
    break;

  case 64: /* exp: exp FLOOR_DIV exp  */
#line 674 "interpreter.y"
                {
		  // Create a new division node	
		  (yyval.expNode) = new lp::FloorDivisionNode((yyvsp[-2].expNode), (yyvsp[0].expNode));
	   }
#line 2472 "interpreter.tab.c"
    break;

  case 65: /* exp: LPAREN exp RPAREN  */
#line 680 "interpreter.y"
        { 
		    // just copy up the expression node 
			(yyval.expNode) = (yyvsp[-1].expNode);
		 }
#line 2481 "interpreter.tab.c"
    break;

  case 66: /* exp: PLUS exp  */
#line 686 "interpreter.y"
                { 
		  // Create a new unary plus node	
  		  (yyval.expNode) = new lp::UnaryPlusNode((yyvsp[0].expNode));
		}
#line 2490 "interpreter.tab.c"
    break;

  case 67: /* exp: MINUS exp  */
#line 692 "interpreter.y"
                { 
		  // Create a new unary minus node	
  		  (yyval.expNode) = new lp::UnaryMinusNode((yyvsp[0].expNode));
		}
#line 2499 "interpreter.tab.c"
    break;

  case 68: /* exp: exp MODULO exp  */
#line 698 "interpreter.y"
                {
		  // Create a new modulo node	

		  (yyval.expNode) = new lp::ModuloNode((yyvsp[-2].expNode), (yyvsp[0].expNode));
       }
#line 2509 "interpreter.tab.c"
    break;

  case 69: /* exp: exp POWER exp  */
#line 705 "interpreter.y"
        { 
		  // Create a new power node	
  		  (yyval.expNode) = new lp::PowerNode((yyvsp[-2].expNode), (yyvsp[0].expNode));
		}
#line 2518 "interpreter.tab.c"
    break;

  case 70: /* exp: exp CONCAT exp  */
#line 711 "interpreter.y"
                {
			(yyval.expNode) = new lp::ConcatNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
		}
#line 2526 "interpreter.tab.c"
    break;

  case 71: /* exp: exp FACT  */
#line 715 "interpreter.y"
                {
			(yyval.expNode) = new lp::FactNode((yyvsp[-1].expNode));
		}
#line 2534 "interpreter.tab.c"
    break;

  case 72: /* exp: VARIABLE  */
#line 719 "interpreter.y"
                {
		  // Create a new variable node	
		  (yyval.expNode) = new lp::VariableNode((yyvsp[0].string));
		}
#line 2543 "interpreter.tab.c"
    break;

  case 73: /* exp: STRING  */
#line 725 "interpreter.y"
                {
		  // Create a new string node	
		  (yyval.expNode) = new lp::StringNode((yyvsp[0].string));
		}
#line 2552 "interpreter.tab.c"
    break;

  case 74: /* exp: CONSTANT  */
#line 731 "interpreter.y"
                {
		  // Create a new constant node	
		  (yyval.expNode) = new lp::ConstantNode((yyvsp[0].string));

		}
#line 2562 "interpreter.tab.c"
    break;

  case 75: /* exp: BUILTIN LPAREN listOfExp RPAREN  */
#line 738 "interpreter.y"
                {
			// Get the identifier in the table of symbols as Builtin
			lp::Builtin *f= (lp::Builtin *) table.getSymbol((yyvsp[-3].string));

			// Check the number of parameters 
			if (f->getNParameters() ==  (int) (yyvsp[-1].parameters)->size())
			{
				switch(f->getNParameters())
				{
					case 0:
						{
							// Create a new Builtin Function with 0 parameters node	
							(yyval.expNode) = new lp::BuiltinFunctionNode_0((yyvsp[-3].string));
						}
						break;

					case 1:
						{
							// Get the expression from the list of expressions
							lp::ExpNode *e = (yyvsp[-1].parameters)->front();

							// Create a new Builtin Function with 1 parameter node	
							(yyval.expNode) = new lp::BuiltinFunctionNode_1((yyvsp[-3].string),e);
						}
						break;

					case 2:
						{
							// Get the expressions from the list of expressions
							lp::ExpNode *e1 = (yyvsp[-1].parameters)->front();
							(yyvsp[-1].parameters)->pop_front();
							lp::ExpNode *e2 = (yyvsp[-1].parameters)->front();

							// Create a new Builtin Function with 2 parameters node	
							(yyval.expNode) = new lp::BuiltinFunctionNode_2((yyvsp[-3].string),e1,e2);
						}
						break;

					default:
				  			 execerror("Syntax error: too many parameters for function ", (yyvsp[-3].string));
				} 
			}
			else
	  			 execerror("Syntax error: incompatible number of parameters for function", (yyvsp[-3].string));
		}
#line 2612 "interpreter.tab.c"
    break;

  case 76: /* exp: exp GREATER_THAN exp  */
#line 785 "interpreter.y"
                {
		  // Create a new "greater than" node	
 			(yyval.expNode) = new lp::GreaterThanNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
		}
#line 2621 "interpreter.tab.c"
    break;

  case 77: /* exp: exp GREATER_OR_EQUAL exp  */
#line 791 "interpreter.y"
                {
		  // Create a new "greater or equal" node	
 			(yyval.expNode) = new lp::GreaterOrEqualNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
		}
#line 2630 "interpreter.tab.c"
    break;

  case 78: /* exp: exp LESS_THAN exp  */
#line 797 "interpreter.y"
                {
		  // Create a new "less than" node	
 			(yyval.expNode) = new lp::LessThanNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
		}
#line 2639 "interpreter.tab.c"
    break;

  case 79: /* exp: exp LESS_OR_EQUAL exp  */
#line 803 "interpreter.y"
                {
		  // Create a new "less or equal" node	
 			(yyval.expNode) = new lp::LessOrEqualNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
		}
#line 2648 "interpreter.tab.c"
    break;

  case 80: /* exp: exp EQUAL exp  */
#line 809 "interpreter.y"
                {
		  // Create a new "equal" node	
 			(yyval.expNode) = new lp::EqualNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
		}
#line 2657 "interpreter.tab.c"
    break;

  case 81: /* exp: exp NOT_EQUAL exp  */
#line 815 "interpreter.y"
                {
		  // Create a new "not equal" node	
 			(yyval.expNode) = new lp::NotEqualNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
		}
#line 2666 "interpreter.tab.c"
    break;

  case 82: /* exp: exp AND exp  */
#line 821 "interpreter.y"
                {
		  // Create a new "logic and" node	
 			(yyval.expNode) = new lp::AndNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
		}
#line 2675 "interpreter.tab.c"
    break;

  case 83: /* exp: exp OR exp  */
#line 827 "interpreter.y"
                {
		  // Create a new "logic or" node	
 			(yyval.expNode) = new lp::OrNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
		}
#line 2684 "interpreter.tab.c"
    break;

  case 84: /* exp: NOT exp  */
#line 833 "interpreter.y"
                {
		  // Create a new "logic negation" node	
 			(yyval.expNode) = new lp::NotNode((yyvsp[0].expNode));
		}
#line 2693 "interpreter.tab.c"
    break;

  case 85: /* listOfExp: %empty  */
#line 842 "interpreter.y"
                        {
			    // Create a new list STL
				(yyval.parameters) = new std::list<lp::ExpNode *>(); 
			}
#line 2702 "interpreter.tab.c"
    break;

  case 86: /* listOfExp: exp restOfListOfExp  */
#line 848 "interpreter.y"
                        {
				(yyval.parameters) = (yyvsp[0].parameters);

				// Insert the expression in the list of expressions
				(yyval.parameters)->push_front((yyvsp[-1].expNode));
			}
#line 2713 "interpreter.tab.c"
    break;

  case 87: /* restOfListOfExp: %empty  */
#line 858 "interpreter.y"
                        {
			    // Create a new list STL
				(yyval.parameters) = new std::list<lp::ExpNode *>(); 
			}
#line 2722 "interpreter.tab.c"
    break;

  case 88: /* restOfListOfExp: COMMA exp restOfListOfExp  */
#line 864 "interpreter.y"
                        {
				// Get the list of expressions
				(yyval.parameters) = (yyvsp[0].parameters);

				// Insert the expression in the list of expressions
				(yyval.parameters)->push_front((yyvsp[-1].expNode));
			}
#line 2734 "interpreter.tab.c"
    break;


#line 2738 "interpreter.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 875 "interpreter.y"




