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
#line 6 "interpreter.y"

#include <iostream>
#include <string>

struct SwitchCaseData;

/* pow */
#include <math.h>

/* Use for recovery of runtime errors */
#include <setjmp.h>
#include <signal.h>

/* Error recovery functions */
#include "../error/error.hpp"

/* Macros for the screen */
#include "../includes/macros.hpp"

/* 
  AST class
  IMPORTANT: this file must be before init.hpp
*/
#include "../ast/ast.hpp"

/* Table of symbol */
#include "../table/table.hpp"

#include "../table/numericVariable.hpp"

#include "../table/logicalVariable.hpp"

#include "../table/numericConstant.hpp"

#include "../table/logicalConstant.hpp"

#include "../table/builtinParameter1.hpp"

#include "../table/builtinParameter0.hpp"
#include "../table/builtinParameter2.hpp"

#include "../table/init.hpp"

/*! 
	\brief  Lexical or scanner function
	\return int
	\note   C++ requires that yylex returns an int value
	\sa     yyparser
*/
int yylex();

extern int lineNumber; //!< External line counter

extern bool interactiveMode; //!< Control the interactive mode of execution of the interpreter

extern int control; //!< External: to control the interactive mode in "if" and "while" sentences 

extern std::string progname; //!<  Program name

/*
 jhmp_buf
    This is an array type capable of storing the information of a calling environment to be restored later.
   This information is filled by calling macro setjmp and can be restored by calling function longjmp.
*/
jmp_buf begin; //!<  It enables recovery of runtime errors 

extern lp::Table table; //!< Extern Table of Symbols

extern lp::AST *root; //!< External root of the abstract syntax tree AST


#line 143 "interpreter.tab.c"

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
  YYSYMBOL_STRING = 37,                    /* STRING  */
  YYSYMBOL_NUMBER = 38,                    /* NUMBER  */
  YYSYMBOL_BOOL = 39,                      /* BOOL  */
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
  YYSYMBOL_FLOOR_DIVISION = 58,            /* FLOOR_DIVISION  */
  YYSYMBOL_LPAREN = 59,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 60,                    /* RPAREN  */
  YYSYMBOL_CONCATENATION = 61,             /* CONCATENATION  */
  YYSYMBOL_PLUS_EQUAL = 62,                /* PLUS_EQUAL  */
  YYSYMBOL_MINUS_EQUAL = 63,               /* MINUS_EQUAL  */
  YYSYMBOL_MULTIPLICATION_EQUAL = 64,      /* MULTIPLICATION_EQUAL  */
  YYSYMBOL_DIVISION_EQUAL = 65,            /* DIVISION_EQUAL  */
  YYSYMBOL_PLUS_PLUS = 66,                 /* PLUS_PLUS  */
  YYSYMBOL_MINUS_MINUS = 67,               /* MINUS_MINUS  */
  YYSYMBOL_FACTORIAL = 68,                 /* FACTORIAL  */
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
  YYSYMBOL_for = 80,                       /* for  */
  YYSYMBOL_dowhile = 81,                   /* dowhile  */
  YYSYMBOL_switch = 82,                    /* switch  */
  YYSYMBOL_cases = 83,                     /* cases  */
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
#define YYLAST   1135

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  71
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  88
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  210

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
       0,   169,   169,   183,   188,   211,   221,   226,   231,   236,
     241,   246,   251,   256,   261,   266,   271,   276,   281,   286,
     291,   298,   306,   313,   325,   338,   350,   360,   369,   379,
     391,   397,   407,   416,   427,   433,   438,   443,   447,   451,
     455,   459,   463,   467,   471,   475,   479,   483,   489,   496,
     501,   507,   512,   518,   523,   530,   537,   541,   545,   551,
     556,   561,   566,   571,   576,   581,   586,   591,   597,   602,
     606,   611,   615,   620,   625,   630,   677,   683,   689,   695,
     701,   707,   713,   719,   725,   735,   739,   750,   754
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
  "RIGHTCURLYBRACKET", "ASSIGNMENT", "TERNARIO", "COMMA", "STRING",
  "NUMBER", "BOOL", "VARIABLE", "UNDEFINED", "CONSTANT", "BUILTIN", "OR",
  "AND", "GREATER_OR_EQUAL", "LESS_OR_EQUAL", "GREATER_THAN", "LESS_THAN",
  "EQUAL", "NOT_EQUAL", "NOT", "PLUS", "MINUS", "MULTIPLICATION",
  "DIVISION", "MODULO", "FLOOR_DIVISION", "LPAREN", "RPAREN",
  "CONCATENATION", "PLUS_EQUAL", "MINUS_EQUAL", "MULTIPLICATION_EQUAL",
  "DIVISION_EQUAL", "PLUS_PLUS", "MINUS_MINUS", "FACTORIAL", "UNARY",
  "POWER", "$accept", "program", "stmtlist", "stmt", "block",
  "controlSymbol", "if", "while", "repeat", "for", "dowhile", "switch",
  "cases", "cond", "asgn", "print", "read", "readstring", "clearscreen",
  "place", "text", "exp", "listOfExp", "restOfListOfExp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-57)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-35)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -57,    11,   139,   -57,   -57,   -57,   -27,   -17,  1076,   -57,
     -57,   -57,   -57,   -57,   -57,   -16,     0,     8,   -57,   -57,
       2,   -12,    22,    23,   -57,   -57,   -57,   -57,    67,   -57,
     -57,   -57,    68,    69,    79,    86,    89,    90,    91,   -34,
     -30,   -57,   -57,   -57,   -57,    36,  1076,  1076,  1076,  1076,
     978,    37,    37,    65,   -57,    59,    37,    41,  1076,   -57,
     -57,   316,   828,  1076,  1076,  1076,  1076,   -57,   -57,   846,
     -57,   -57,   -57,   -57,   -57,   -57,   -57,   -57,   -57,   -57,
      42,    43,    44,    45,  1076,   166,    39,    39,   870,  1076,
    1076,  1076,  1076,  1076,  1076,  1076,  1076,  1076,  1076,  1076,
    1076,  1076,  1076,  1076,   -57,  1076,  1076,    97,    94,   -57,
     358,    93,    87,   -57,   752,   -57,     2,   -12,  1076,    78,
     -57,   978,   978,   978,   978,   978,   -57,   978,   -57,   -57,
     -57,   -57,   779,    55,   -57,  1004,  1029,  1054,  1054,  1054,
    1054,  1054,  1054,   589,   589,   -54,   -54,   -54,   -54,   -37,
      39,   897,   -57,   -57,   400,    37,  1076,   -57,    16,  1076,
     924,  1076,  1076,   -57,   -57,   -57,   274,   442,   106,   -57,
     725,  1076,   -57,   -57,    96,   951,    85,   806,   779,   -57,
     -57,   -57,    37,  1076,    30,   485,  1076,   -57,  1076,   -57,
     527,   118,   667,   -57,   -57,   618,   978,   -57,   -57,   -57,
    1076,   186,   -57,   569,   694,   232,   -57,   -57,   611,   -57
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     0,     1,     5,     6,     0,     0,     0,    22,
      22,    22,    22,    22,    22,    53,     0,     0,    58,     3,
       0,     0,     0,     0,     4,    20,    10,    11,     0,    13,
      14,    19,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    74,    59,    72,    73,     0,     0,     0,     0,     0,
      48,     0,     0,     0,     3,     0,     0,     0,     0,    56,
      57,     0,     0,     0,     0,     0,     0,    38,    41,     0,
      39,    42,    12,     7,     8,     9,    15,    16,    17,    18,
       0,     0,     0,     0,    85,    84,    65,    66,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    71,     0,     0,     0,     0,     3,
       0,     0,     0,    54,     0,    21,    72,    73,     0,     0,
      36,    35,    37,    40,    43,    44,    47,    46,    49,    50,
      51,    52,    87,     0,    64,    83,    82,    77,    79,    76,
      78,    80,    81,    60,    61,    62,    63,    67,    68,    69,
      70,     0,     3,     3,     0,     0,     0,    22,    22,     0,
       0,     0,     0,    86,    75,    34,     0,     0,     0,    26,
       0,     0,     3,    30,     0,     0,    64,     0,    87,     3,
      23,    25,     0,     0,     0,     0,     0,    55,     0,    88,
       0,     0,     0,     3,    31,     0,    45,    24,    29,     3,
       0,     0,     3,     0,     0,     0,    28,     3,     0,    27
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -57,   -57,   -19,   -57,   -57,    15,   -57,   -57,   -57,   -57,
     -57,   -57,   -57,   -47,   -39,   -57,   -57,   -57,   -57,   -57,
     -57,   -45,   -57,   -56
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    24,    25,    51,    26,    27,    28,    29,
      30,    31,   158,   107,    32,    33,    34,    35,    36,    37,
      38,    50,   133,   163
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      61,    85,    86,    87,    88,   108,    80,   103,    81,   112,
      82,     3,    83,   114,   104,   119,   105,   121,   122,   123,
     124,   125,    69,   120,   127,    52,    53,    54,    55,    56,
     126,   104,    39,   105,   193,   110,    62,    59,    60,   132,
     172,   173,    40,    57,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,    58,
     150,   151,    70,    71,    63,    64,    65,    66,    67,    68,
      72,    73,    74,   160,    89,    90,    91,    92,    93,    94,
      95,    96,    75,    97,    98,    99,   100,   101,   102,    76,
     154,   103,    77,    78,    79,    84,   106,   109,   104,   111,
     105,   113,   128,   129,   130,   131,   152,   153,   169,   105,
     157,   170,   156,   161,   175,   164,   177,   178,   182,   186,
     -34,   198,   189,     0,     0,     0,   184,     0,     0,     0,
       0,     0,     0,   166,   167,   191,     0,     0,   192,    -2,
       4,   195,     5,   196,     6,     7,     8,     9,     0,     0,
       0,    10,    11,   185,    12,   204,    13,     0,     0,     0,
     190,    14,     0,     0,     0,    15,    16,    17,     0,     0,
      18,    19,   171,   174,   201,     0,     0,     0,     0,    20,
     203,    21,     0,   205,     0,     0,     0,     4,   208,     5,
       0,     6,     7,     8,     9,     0,     0,     0,    10,    11,
       0,    12,     0,    13,     0,    22,    23,     0,    14,   -32,
     -32,   -32,    15,    16,    17,     0,     0,    18,    19,    97,
      98,    99,   100,   101,   102,     0,    20,   103,    21,     0,
       0,     0,     0,     4,   104,     5,   105,     6,     7,     8,
       9,     0,     0,     0,    10,    11,     0,    12,     0,    13,
       0,     0,    22,    23,    14,   -33,   -33,   -33,    15,    16,
      17,     0,     0,    18,    19,     0,     0,     0,     0,     0,
       0,     0,    20,     0,    21,     4,     0,     5,     0,     6,
       7,     8,     9,     0,   179,   180,    10,    11,     0,    12,
       0,    13,     0,     0,     0,     0,    14,     0,    22,    23,
      15,    16,    17,     0,     0,    18,    19,     0,     0,     0,
       0,     0,     0,     0,    20,     0,    21,     4,     0,     5,
       0,     6,     7,     8,     9,     0,     0,     0,    10,    11,
       0,    12,     0,    13,     0,     0,     0,     0,    14,     0,
      22,    23,    15,    16,    17,     0,     0,    18,    19,   115,
       0,     0,     0,     0,     0,     0,    20,     0,    21,     4,
       0,     5,     0,     6,     7,     8,     9,     0,     0,     0,
      10,    11,     0,    12,   155,    13,     0,     0,     0,     0,
      14,     0,    22,    23,    15,    16,    17,     0,     0,    18,
      19,     0,     0,     0,     0,     0,     0,     0,    20,     0,
      21,     4,     0,     5,     0,     6,     7,     8,     9,     0,
       0,     0,    10,    11,     0,    12,     0,    13,     0,     0,
       0,     0,    14,     0,    22,    23,    15,    16,    17,     0,
       0,    18,    19,   168,     0,     0,     0,     0,     0,     0,
      20,     0,    21,     4,     0,     5,     0,     6,     7,     8,
       9,     0,     0,     0,    10,    11,   181,    12,     0,    13,
       0,     0,     0,     0,    14,     0,    22,    23,    15,    16,
      17,     0,     0,    18,    19,     0,     0,     0,     0,     0,
       0,     0,    20,     0,    21,     0,     4,     0,     5,     0,
       6,     7,     8,     9,     0,     0,     0,    10,    11,     0,
      12,     0,    13,     0,     0,     0,     0,    14,    22,    23,
     194,    15,    16,    17,     0,     0,    18,    19,     0,     0,
       0,     0,     0,     0,     0,    20,     0,    21,     4,     0,
       5,     0,     6,     7,     8,     9,     0,     0,   197,    10,
      11,     0,    12,     0,    13,     0,     0,     0,     0,    14,
       0,    22,    23,    15,    16,    17,     0,     0,    18,    19,
       0,     0,     0,     0,     0,     0,     0,    20,     0,    21,
       4,     0,     5,     0,     6,     7,     8,     9,     0,     0,
       0,    10,    11,     0,    12,     0,    13,   206,     0,     0,
       0,    14,     0,    22,    23,    15,    16,    17,     0,     0,
      18,    19,     0,     0,     0,     0,     0,     0,     0,    20,
       0,    21,     4,     0,     5,     0,     6,     7,     8,     9,
       0,     0,   202,    10,    11,     0,    12,     0,    13,   209,
       0,     0,     0,    14,     0,    22,    23,    15,    16,    17,
       0,     0,    18,    19,    99,   100,   101,   102,     0,     0,
     103,    20,     0,    21,     0,     0,     0,   104,     0,   105,
       0,     0,    89,    90,    91,    92,    93,    94,    95,    96,
       0,    97,    98,    99,   100,   101,   102,    22,    23,   103,
     199,     0,     0,     0,     0,     0,   104,   200,   105,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   207,     0,     0,
       0,    89,    90,    91,    92,    93,    94,    95,    96,     0,
      97,    98,    99,   100,   101,   102,     0,     0,   103,     0,
       0,     0,     0,     0,     0,   104,     0,   105,    89,    90,
      91,    92,    93,    94,    95,    96,   183,    97,    98,    99,
     100,   101,   102,     0,     0,   103,     0,     0,     0,     0,
       0,     0,   104,     0,   105,     0,     0,     0,     0,    89,
      90,    91,    92,    93,    94,    95,    96,     0,    97,    98,
      99,   100,   101,   102,     0,     0,   103,     0,   159,     0,
       0,     0,     0,   104,     0,   105,    89,    90,    91,    92,
      93,    94,    95,    96,     0,    97,    98,    99,   100,   101,
     102,     0,     0,   103,     0,   162,     0,     0,     0,     0,
     104,     0,   105,    89,    90,    91,    92,    93,    94,    95,
      96,     0,    97,    98,    99,   100,   101,   102,     0,     0,
     103,     0,   188,     0,     0,     0,     0,   104,     0,   105,
      89,    90,    91,    92,    93,    94,    95,    96,     0,    97,
      98,    99,   100,   101,   102,    41,    42,   103,   116,     0,
     117,    45,     0,     0,   104,     0,   105,     0,     0,     0,
      46,    47,    48,    41,    42,     0,   116,   118,   117,    45,
       0,     0,     0,     0,    22,    23,     0,     0,    46,    47,
      48,     0,     0,     0,     0,    49,     0,     0,     0,     0,
       0,     0,    22,    23,    89,    90,    91,    92,    93,    94,
      95,    96,     0,    97,    98,    99,   100,   101,   102,     0,
     134,   103,     0,     0,     0,     0,     0,     0,   104,     0,
     105,    89,    90,    91,    92,    93,    94,    95,    96,     0,
      97,    98,    99,   100,   101,   102,     0,   165,   103,     0,
       0,     0,     0,     0,     0,   104,     0,   105,    89,    90,
      91,    92,    93,    94,    95,    96,     0,    97,    98,    99,
     100,   101,   102,     0,   176,   103,     0,     0,     0,     0,
       0,     0,   104,     0,   105,    89,    90,    91,    92,    93,
      94,    95,    96,     0,    97,    98,    99,   100,   101,   102,
       0,   187,   103,     0,     0,     0,     0,     0,     0,   104,
       0,   105,    89,    90,    91,    92,    93,    94,    95,    96,
       0,    97,    98,    99,   100,   101,   102,     0,     0,   103,
       0,     0,     0,     0,     0,     0,   104,     0,   105,    90,
      91,    92,    93,    94,    95,    96,     0,    97,    98,    99,
     100,   101,   102,     0,     0,   103,     0,     0,     0,     0,
       0,     0,   104,     0,   105,    91,    92,    93,    94,    95,
      96,     0,    97,    98,    99,   100,   101,   102,     0,     0,
     103,     0,     0,     0,     0,     0,     0,   104,     0,   105,
     -35,   -35,   -35,   -35,   -35,   -35,     0,    97,    98,    99,
     100,   101,   102,    41,    42,   103,    43,     0,    44,    45,
       0,     0,   104,     0,   105,     0,     0,     0,    46,    47,
      48,     0,     0,     0,     0,    49
};

static const yytype_int16 yycheck[] =
{
      19,    46,    47,    48,    49,    52,    40,    61,    42,    56,
      40,     0,    42,    58,    68,    62,    70,    62,    63,    64,
      65,    66,    34,    62,    69,    10,    11,    12,    13,    14,
      69,    68,    59,    70,     4,    54,    34,    29,    30,    84,
      24,    25,    59,    59,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,    59,
     105,   106,    40,    40,    62,    63,    64,    65,    66,    67,
       3,     3,     3,   118,    44,    45,    46,    47,    48,    49,
      50,    51,     3,    53,    54,    55,    56,    57,    58,     3,
     109,    61,     3,     3,     3,    59,    59,    32,    68,    40,
      70,    60,    60,    60,    60,    60,     9,    13,   155,    70,
      23,   156,    19,    35,   159,    60,   161,   162,    12,    23,
      35,     3,   178,    -1,    -1,    -1,   171,    -1,    -1,    -1,
      -1,    -1,    -1,   152,   153,   182,    -1,    -1,   183,     0,
       1,   186,     3,   188,     5,     6,     7,     8,    -1,    -1,
      -1,    12,    13,   172,    15,   200,    17,    -1,    -1,    -1,
     179,    22,    -1,    -1,    -1,    26,    27,    28,    -1,    -1,
      31,    32,   157,   158,   193,    -1,    -1,    -1,    -1,    40,
     199,    42,    -1,   202,    -1,    -1,    -1,     1,   207,     3,
      -1,     5,     6,     7,     8,    -1,    -1,    -1,    12,    13,
      -1,    15,    -1,    17,    -1,    66,    67,    -1,    22,    23,
      24,    25,    26,    27,    28,    -1,    -1,    31,    32,    53,
      54,    55,    56,    57,    58,    -1,    40,    61,    42,    -1,
      -1,    -1,    -1,     1,    68,     3,    70,     5,     6,     7,
       8,    -1,    -1,    -1,    12,    13,    -1,    15,    -1,    17,
      -1,    -1,    66,    67,    22,    23,    24,    25,    26,    27,
      28,    -1,    -1,    31,    32,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    40,    -1,    42,     1,    -1,     3,    -1,     5,
       6,     7,     8,    -1,    10,    11,    12,    13,    -1,    15,
      -1,    17,    -1,    -1,    -1,    -1,    22,    -1,    66,    67,
      26,    27,    28,    -1,    -1,    31,    32,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    40,    -1,    42,     1,    -1,     3,
      -1,     5,     6,     7,     8,    -1,    -1,    -1,    12,    13,
      -1,    15,    -1,    17,    -1,    -1,    -1,    -1,    22,    -1,
      66,    67,    26,    27,    28,    -1,    -1,    31,    32,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,    42,     1,
      -1,     3,    -1,     5,     6,     7,     8,    -1,    -1,    -1,
      12,    13,    -1,    15,    16,    17,    -1,    -1,    -1,    -1,
      22,    -1,    66,    67,    26,    27,    28,    -1,    -1,    31,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      42,     1,    -1,     3,    -1,     5,     6,     7,     8,    -1,
      -1,    -1,    12,    13,    -1,    15,    -1,    17,    -1,    -1,
      -1,    -1,    22,    -1,    66,    67,    26,    27,    28,    -1,
      -1,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      40,    -1,    42,     1,    -1,     3,    -1,     5,     6,     7,
       8,    -1,    -1,    -1,    12,    13,    14,    15,    -1,    17,
      -1,    -1,    -1,    -1,    22,    -1,    66,    67,    26,    27,
      28,    -1,    -1,    31,    32,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    40,    -1,    42,    -1,     1,    -1,     3,    -1,
       5,     6,     7,     8,    -1,    -1,    -1,    12,    13,    -1,
      15,    -1,    17,    -1,    -1,    -1,    -1,    22,    66,    67,
      25,    26,    27,    28,    -1,    -1,    31,    32,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    40,    -1,    42,     1,    -1,
       3,    -1,     5,     6,     7,     8,    -1,    -1,    11,    12,
      13,    -1,    15,    -1,    17,    -1,    -1,    -1,    -1,    22,
      -1,    66,    67,    26,    27,    28,    -1,    -1,    31,    32,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,    42,
       1,    -1,     3,    -1,     5,     6,     7,     8,    -1,    -1,
      -1,    12,    13,    -1,    15,    -1,    17,    18,    -1,    -1,
      -1,    22,    -1,    66,    67,    26,    27,    28,    -1,    -1,
      31,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,
      -1,    42,     1,    -1,     3,    -1,     5,     6,     7,     8,
      -1,    -1,     4,    12,    13,    -1,    15,    -1,    17,    18,
      -1,    -1,    -1,    22,    -1,    66,    67,    26,    27,    28,
      -1,    -1,    31,    32,    55,    56,    57,    58,    -1,    -1,
      61,    40,    -1,    42,    -1,    -1,    -1,    68,    -1,    70,
      -1,    -1,    44,    45,    46,    47,    48,    49,    50,    51,
      -1,    53,    54,    55,    56,    57,    58,    66,    67,    61,
      13,    -1,    -1,    -1,    -1,    -1,    68,    20,    70,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    13,    -1,    -1,
      -1,    44,    45,    46,    47,    48,    49,    50,    51,    -1,
      53,    54,    55,    56,    57,    58,    -1,    -1,    61,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    -1,    70,    44,    45,
      46,    47,    48,    49,    50,    51,    21,    53,    54,    55,
      56,    57,    58,    -1,    -1,    61,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    -1,    70,    -1,    -1,    -1,    -1,    44,
      45,    46,    47,    48,    49,    50,    51,    -1,    53,    54,
      55,    56,    57,    58,    -1,    -1,    61,    -1,    36,    -1,
      -1,    -1,    -1,    68,    -1,    70,    44,    45,    46,    47,
      48,    49,    50,    51,    -1,    53,    54,    55,    56,    57,
      58,    -1,    -1,    61,    -1,    36,    -1,    -1,    -1,    -1,
      68,    -1,    70,    44,    45,    46,    47,    48,    49,    50,
      51,    -1,    53,    54,    55,    56,    57,    58,    -1,    -1,
      61,    -1,    36,    -1,    -1,    -1,    -1,    68,    -1,    70,
      44,    45,    46,    47,    48,    49,    50,    51,    -1,    53,
      54,    55,    56,    57,    58,    37,    38,    61,    40,    -1,
      42,    43,    -1,    -1,    68,    -1,    70,    -1,    -1,    -1,
      52,    53,    54,    37,    38,    -1,    40,    59,    42,    43,
      -1,    -1,    -1,    -1,    66,    67,    -1,    -1,    52,    53,
      54,    -1,    -1,    -1,    -1,    59,    -1,    -1,    -1,    -1,
      -1,    -1,    66,    67,    44,    45,    46,    47,    48,    49,
      50,    51,    -1,    53,    54,    55,    56,    57,    58,    -1,
      60,    61,    -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,
      70,    44,    45,    46,    47,    48,    49,    50,    51,    -1,
      53,    54,    55,    56,    57,    58,    -1,    60,    61,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    -1,    70,    44,    45,
      46,    47,    48,    49,    50,    51,    -1,    53,    54,    55,
      56,    57,    58,    -1,    60,    61,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    -1,    70,    44,    45,    46,    47,    48,
      49,    50,    51,    -1,    53,    54,    55,    56,    57,    58,
      -1,    60,    61,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      -1,    70,    44,    45,    46,    47,    48,    49,    50,    51,
      -1,    53,    54,    55,    56,    57,    58,    -1,    -1,    61,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,    70,    45,
      46,    47,    48,    49,    50,    51,    -1,    53,    54,    55,
      56,    57,    58,    -1,    -1,    61,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    -1,    70,    46,    47,    48,    49,    50,
      51,    -1,    53,    54,    55,    56,    57,    58,    -1,    -1,
      61,    -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,    70,
      46,    47,    48,    49,    50,    51,    -1,    53,    54,    55,
      56,    57,    58,    37,    38,    61,    40,    -1,    42,    43,
      -1,    -1,    68,    -1,    70,    -1,    -1,    -1,    52,    53,
      54,    -1,    -1,    -1,    -1,    59
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    72,    73,     0,     1,     3,     5,     6,     7,     8,
      12,    13,    15,    17,    22,    26,    27,    28,    31,    32,
      40,    42,    66,    67,    74,    75,    77,    78,    79,    80,
      81,    82,    85,    86,    87,    88,    89,    90,    91,    59,
      59,    37,    38,    40,    42,    43,    52,    53,    54,    59,
      92,    76,    76,    76,    76,    76,    76,    59,    59,    29,
      30,    73,    34,    62,    63,    64,    65,    66,    67,    34,
      40,    40,     3,     3,     3,     3,     3,     3,     3,     3,
      40,    42,    40,    42,    59,    92,    92,    92,    92,    44,
      45,    46,    47,    48,    49,    50,    51,    53,    54,    55,
      56,    57,    58,    61,    68,    70,    59,    84,    84,    32,
      73,    40,    84,    60,    92,    33,    40,    42,    59,    84,
      85,    92,    92,    92,    92,    92,    85,    92,    60,    60,
      60,    60,    92,    93,    60,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,     9,    13,    73,    16,    19,    23,    83,    36,
      92,    35,    36,    94,    60,    60,    73,    73,    33,    84,
      92,    76,    24,    25,    76,    92,    60,    92,    92,    10,
      11,    14,    12,    21,    92,    73,    23,    60,    36,    94,
      73,    84,    92,     4,    25,    92,    92,    11,     3,    13,
      20,    73,     4,    73,    92,    73,    18,    13,    73,    18
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    71,    72,    73,    73,    73,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    75,    76,    77,    77,    78,    79,    80,    80,    81,
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
       1,     1,     2,     1,     1,     2,     2,     2,     2,     1,
       1,     3,     0,     6,     8,     6,     5,    12,    10,     8,
       5,     7,     5,     6,     3,     3,     3,     3,     2,     2,
       3,     2,     2,     3,     3,     7,     3,     3,     2,     4,
       4,     4,     4,     1,     3,     6,     2,     2,     1,     1,
       3,     3,     3,     3,     3,     2,     2,     3,     3,     3,
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
#line 170 "interpreter.y"
                  { 
		    // Create a new AST
			(yyval.prog) = new lp::AST((yyvsp[0].stmts)); 

			// Assign the AST to the root
			root = (yyval.prog); 

			// End of parsing
			//	return 1;
		  }
#line 1824 "interpreter.tab.c"
    break;

  case 3: /* stmtlist: %empty  */
#line 183 "interpreter.y"
                  { 
			// create a empty list of statements
			(yyval.stmts) = new std::list<lp::Statement *>(); 
		  }
#line 1833 "interpreter.tab.c"
    break;

  case 4: /* stmtlist: stmtlist stmt  */
#line 189 "interpreter.y"
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
#line 1859 "interpreter.tab.c"
    break;

  case 5: /* stmtlist: stmtlist error  */
#line 212 "interpreter.y"
      { 
			 // just copy up the stmtlist when an error occurs
			 (yyval.stmts) = (yyvsp[-1].stmts);

			 // The previous look-ahead token ought to be discarded with `yyclearin;'
			 yyclearin; 
       }
#line 1871 "interpreter.tab.c"
    break;

  case 6: /* stmt: SEMICOLON  */
#line 222 "interpreter.y"
          {
		// Create a new empty statement node
		(yyval.st) = new lp::EmptyStmt(); 
	  }
#line 1880 "interpreter.tab.c"
    break;

  case 7: /* stmt: asgn SEMICOLON  */
#line 227 "interpreter.y"
          {
		// Default action
		// $$ = $1;
	  }
#line 1889 "interpreter.tab.c"
    break;

  case 8: /* stmt: print SEMICOLON  */
#line 232 "interpreter.y"
          {
		// Default action
		// $$ = $1;
	  }
#line 1898 "interpreter.tab.c"
    break;

  case 9: /* stmt: read SEMICOLON  */
#line 237 "interpreter.y"
          {
		// Default action
		// $$ = $1;
	  }
#line 1907 "interpreter.tab.c"
    break;

  case 10: /* stmt: if  */
#line 242 "interpreter.y"
          {
	 	// Default action
	 	// $$ = $1;
	  }
#line 1916 "interpreter.tab.c"
    break;

  case 11: /* stmt: while  */
#line 247 "interpreter.y"
          {
	 	// Default action
	 	// $$ = $1;
	  }
#line 1925 "interpreter.tab.c"
    break;

  case 12: /* stmt: repeat SEMICOLON  */
#line 252 "interpreter.y"
          {
	 	// Default action
	 	// $$ = $1;
	  }
#line 1934 "interpreter.tab.c"
    break;

  case 13: /* stmt: for  */
#line 257 "interpreter.y"
          {
	 	// Default action
	 	// $$ = $1;
	  }
#line 1943 "interpreter.tab.c"
    break;

  case 14: /* stmt: dowhile  */
#line 262 "interpreter.y"
          {
	 	// Default action
	 	// $$ = $1;
	  }
#line 1952 "interpreter.tab.c"
    break;

  case 15: /* stmt: readstring SEMICOLON  */
#line 267 "interpreter.y"
          {
	 	// Default action
	 	// $$ = $1;
	  }
#line 1961 "interpreter.tab.c"
    break;

  case 16: /* stmt: clearscreen SEMICOLON  */
#line 272 "interpreter.y"
          {
 	 	// Default action
 	 	// $$ = $1;
	  }
#line 1970 "interpreter.tab.c"
    break;

  case 17: /* stmt: place SEMICOLON  */
#line 277 "interpreter.y"
          {
 	 	// Default action
 	 	// $$ = $1;
	  }
#line 1979 "interpreter.tab.c"
    break;

  case 18: /* stmt: text SEMICOLON  */
#line 282 "interpreter.y"
          {
	  	// Default action
	  	// $$ = $1;
	  }
#line 1988 "interpreter.tab.c"
    break;

  case 19: /* stmt: switch  */
#line 287 "interpreter.y"
          {
	 	// Default action
	 	// $$ = $1;
	  }
#line 1997 "interpreter.tab.c"
    break;

  case 20: /* stmt: block  */
#line 292 "interpreter.y"
          {
	 	// Default action
	 	// $$ = $1;
	  }
#line 2006 "interpreter.tab.c"
    break;

  case 21: /* block: LETFCURLYBRACKET stmtlist RIGHTCURLYBRACKET  */
#line 299 "interpreter.y"
                {
			// Create a new block of statements node
			(yyval.st) = new lp::BlockStmt((yyvsp[-1].stmts)); 
		}
#line 2015 "interpreter.tab.c"
    break;

  case 22: /* controlSymbol: %empty  */
#line 306 "interpreter.y"
                                {
					// To control the interactive mode in "if" and "while" sentences
					control++;
				}
#line 2024 "interpreter.tab.c"
    break;

  case 23: /* if: IF controlSymbol cond THEN stmtlist ENDIF  */
#line 314 "interpreter.y"
    {
		lp::BlockStmt *aux = new lp::BlockStmt((yyvsp[-1].stmts)); //bloque aux de statements para el bloque if

		// Create a new if statement node
		(yyval.st) = new lp::IfStmt((yyvsp[-3].expNode), aux);

		// To control the interactive mode
		control--;
	}
#line 2038 "interpreter.tab.c"
    break;

  case 24: /* if: IF controlSymbol cond THEN stmtlist ELSE stmtlist ENDIF  */
#line 326 "interpreter.y"
         {
		lp::BlockStmt *aux1 = new lp::BlockStmt((yyvsp[-3].stmts)); //bloque aux de statements para el bloque if: consecuente
		lp::BlockStmt *aux2 = new lp::BlockStmt((yyvsp[-1].stmts)); //bloque aux de statements para el bloque if: alternativa

		// Create a new if statement node
		(yyval.st) = new lp::IfStmt((yyvsp[-5].expNode),aux1,aux2);

		// To control the interactive mode
		control--;
	 }
#line 2053 "interpreter.tab.c"
    break;

  case 25: /* while: WHILE controlSymbol cond DO stmtlist ENDWHILE  */
#line 339 "interpreter.y"
                {
			lp::BlockStmt *aux = new lp::BlockStmt((yyvsp[-1].stmts)); //bloque aux de statements para el bloque de WHILE

			// Create a new while statement node
			(yyval.st) = new lp::WhileStmt((yyvsp[-3].expNode), aux);

			// To control the interactive mode
			control--;
    }
#line 2067 "interpreter.tab.c"
    break;

  case 26: /* repeat: REPEAT controlSymbol stmtlist UNTIL cond  */
#line 351 "interpreter.y"
                {
			lp::BlockStmt *aux = new lp::BlockStmt((yyvsp[-2].stmts)); //bloque aux de statements para el bloque de repeat

			(yyval.st) = new lp::RepeatStmt(aux, (yyvsp[0].expNode)); //crea un nuevo nodo de repetición

			control--; //Sirve para controloar el modo interactivo
		}
#line 2079 "interpreter.tab.c"
    break;

  case 27: /* for: FOR controlSymbol VARIABLE FROM exp TO exp STEP exp DO stmtlist ENDFOR  */
#line 361 "interpreter.y"
                {
			lp::BlockStmt *aux = new lp::BlockStmt((yyvsp[-1].stmts)); //bloque aux de statements para el bloque de FOR

			(yyval.st) = new lp::ForStmt((yyvsp[-9].string), (yyvsp[-7].expNode), (yyvsp[-5].expNode), (yyvsp[-3].expNode), aux); //crea un nuevo nodo de repetición

			control--; //Sirve para controloar el modo interactivo
		}
#line 2091 "interpreter.tab.c"
    break;

  case 28: /* for: FOR controlSymbol VARIABLE FROM exp TO exp DO stmtlist ENDFOR  */
#line 370 "interpreter.y"
                {
			lp::BlockStmt *aux = new lp::BlockStmt((yyvsp[-1].stmts)); //bloque aux de statements para el bloque de FOR

			(yyval.st) = new lp::ForStmt((yyvsp[-7].string), (yyvsp[-5].expNode), (yyvsp[-3].expNode), aux); //crea un nuevo nodo de repetición

			control--; //Sirve para controloar el modo interactivo
		}
#line 2103 "interpreter.tab.c"
    break;

  case 29: /* dowhile: DO controlSymbol LETFCURLYBRACKET stmtlist RIGHTCURLYBRACKET WHILE cond SEMICOLON  */
#line 380 "interpreter.y"
                {
			lp::BlockStmt *aux = new lp::BlockStmt((yyvsp[-4].stmts)); //bloque aux de statements para el bloque de DOWHILE

			// Create a new dowhile statement node
			(yyval.st) = new lp::RepeatStmt(aux, (yyvsp[-1].expNode));

			// To control the interactive mode
			control--;
    }
#line 2117 "interpreter.tab.c"
    break;

  case 30: /* switch: SWITCH controlSymbol cond cases ENDSWITCH  */
#line 392 "interpreter.y"
                {
			(yyval.st) = new lp::SwitchStmt((yyvsp[-2].expNode), (yyvsp[-1].cases)); //crea un nuevo nodo switch
		
			control--;
		}
#line 2127 "interpreter.tab.c"
    break;

  case 31: /* switch: SWITCH controlSymbol cond cases DEFAULT stmtlist ENDSWITCH  */
#line 398 "interpreter.y"
                {
			lp::BlockStmt *aux = new lp::BlockStmt((yyvsp[-1].stmts)); //bloque aux de statements para el bloque de FOR

			(yyval.st) = new lp::SwitchStmt((yyvsp[-4].expNode), (yyvsp[-3].cases), aux); //crea un nuevo nodo switch
		
			control--;
		}
#line 2139 "interpreter.tab.c"
    break;

  case 32: /* cases: CASE controlSymbol exp COLON stmtlist  */
#line 408 "interpreter.y"
                {
			lp::BlockStmt *aux = new lp::BlockStmt((yyvsp[0].stmts)); //bloque aux de statements

			(yyval.cases) = new std::list<lp::CaseStmt *>();
			(yyval.cases)->push_back(new lp::CaseStmt((yyvsp[-2].expNode), aux));
			
			control--;
		}
#line 2152 "interpreter.tab.c"
    break;

  case 33: /* cases: cases controlSymbol CASE exp COLON stmtlist  */
#line 417 "interpreter.y"
                {
			lp::BlockStmt *aux = new lp::BlockStmt((yyvsp[0].stmts)); //bloque aux de statements

			(yyval.cases) = (yyvsp[-5].cases);
			(yyval.cases)->push_back(new lp::CaseStmt((yyvsp[-2].expNode), aux));

			control--;
		}
#line 2165 "interpreter.tab.c"
    break;

  case 34: /* cond: LPAREN exp RPAREN  */
#line 428 "interpreter.y"
                { 
			(yyval.expNode) = (yyvsp[-1].expNode);
		}
#line 2173 "interpreter.tab.c"
    break;

  case 35: /* asgn: VARIABLE ASSIGNMENT exp  */
#line 434 "interpreter.y"
                { 
			// Create a new assignment node
			(yyval.st) = new lp::AssignmentStmt((yyvsp[-2].string), (yyvsp[0].expNode));
		}
#line 2182 "interpreter.tab.c"
    break;

  case 36: /* asgn: VARIABLE ASSIGNMENT asgn  */
#line 439 "interpreter.y"
                { 
			// Create a new assignment node
			(yyval.st) = new lp::AssignmentStmt((yyvsp[-2].string), (lp::AssignmentStmt *) (yyvsp[0].st));
		}
#line 2191 "interpreter.tab.c"
    break;

  case 37: /* asgn: VARIABLE PLUS_EQUAL exp  */
#line 444 "interpreter.y"
                {
			(yyval.st) = new lp::AssignmentStmt((yyvsp[-2].string), new lp::PlusNode(new lp::VariableNode((yyvsp[-2].string)), (yyvsp[0].expNode)));
		}
#line 2199 "interpreter.tab.c"
    break;

  case 38: /* asgn: VARIABLE PLUS_PLUS  */
#line 448 "interpreter.y"
                {
			(yyval.st) = new lp::AssignmentStmt((yyvsp[-1].string), new lp::PlusNode(new lp::VariableNode((yyvsp[-1].string)), new lp::NumberNode(1)));
		}
#line 2207 "interpreter.tab.c"
    break;

  case 39: /* asgn: PLUS_PLUS VARIABLE  */
#line 452 "interpreter.y"
                {
			(yyval.st) = new lp::AssignmentStmt((yyvsp[0].string), new lp::PlusNode(new lp::VariableNode((yyvsp[0].string)), new lp::NumberNode(1)));
		}
#line 2215 "interpreter.tab.c"
    break;

  case 40: /* asgn: VARIABLE MINUS_EQUAL exp  */
#line 456 "interpreter.y"
                {
			(yyval.st) = new lp::AssignmentStmt((yyvsp[-2].string), new lp::MinusNode(new lp::VariableNode((yyvsp[-2].string)), (yyvsp[0].expNode)));
		}
#line 2223 "interpreter.tab.c"
    break;

  case 41: /* asgn: VARIABLE MINUS_MINUS  */
#line 460 "interpreter.y"
                {
			(yyval.st) = new lp::AssignmentStmt((yyvsp[-1].string), new lp::MinusNode(new lp::VariableNode((yyvsp[-1].string)), new lp::NumberNode(1)));
		}
#line 2231 "interpreter.tab.c"
    break;

  case 42: /* asgn: MINUS_MINUS VARIABLE  */
#line 464 "interpreter.y"
                {
			(yyval.st) = new lp::AssignmentStmt((yyvsp[0].string), new lp::MinusNode(new lp::VariableNode((yyvsp[0].string)), new lp::NumberNode(1)));
		}
#line 2239 "interpreter.tab.c"
    break;

  case 43: /* asgn: VARIABLE MULTIPLICATION_EQUAL exp  */
#line 468 "interpreter.y"
                {
			(yyval.st) = new lp::AssignmentStmt((yyvsp[-2].string), new lp::MultiplicationNode(new lp::VariableNode((yyvsp[-2].string)), (yyvsp[0].expNode)));
		}
#line 2247 "interpreter.tab.c"
    break;

  case 44: /* asgn: VARIABLE DIVISION_EQUAL exp  */
#line 472 "interpreter.y"
                {
			(yyval.st) = new lp::AssignmentStmt((yyvsp[-2].string), new lp::DivisionNode(new lp::VariableNode((yyvsp[-2].string)), (yyvsp[0].expNode)));
		}
#line 2255 "interpreter.tab.c"
    break;

  case 45: /* asgn: VARIABLE ASSIGNMENT cond TERNARIO exp COMMA exp  */
#line 476 "interpreter.y"
                {
		    (yyval.st) = new lp::AssignmentStmt((yyvsp[-6].string), new lp::AlternativeNode((yyvsp[-4].expNode), (yyvsp[-2].expNode), (yyvsp[0].expNode)));
		}
#line 2263 "interpreter.tab.c"
    break;

  case 46: /* asgn: CONSTANT ASSIGNMENT exp  */
#line 480 "interpreter.y"
                {   
 			execerror("Semantic error in assignment: it is not allowed to modify a constant ", (yyvsp[-2].string));
		}
#line 2271 "interpreter.tab.c"
    break;

  case 47: /* asgn: CONSTANT ASSIGNMENT asgn  */
#line 484 "interpreter.y"
                {   
 			execerror("Semantic error in multiple assignment: it is not allowed to modify a constant ",(yyvsp[-2].string));
		}
#line 2279 "interpreter.tab.c"
    break;

  case 48: /* print: PRINT exp  */
#line 490 "interpreter.y"
                {
			// Create a new print node
			(yyval.st) = new lp::PrintStmt((yyvsp[0].expNode));
		}
#line 2288 "interpreter.tab.c"
    break;

  case 49: /* read: READ LPAREN VARIABLE RPAREN  */
#line 497 "interpreter.y"
                {
			// Create a new read node
			(yyval.st) = new lp::ReadStmt((yyvsp[-1].string));
		}
#line 2297 "interpreter.tab.c"
    break;

  case 50: /* read: READ LPAREN CONSTANT RPAREN  */
#line 502 "interpreter.y"
                {   
 			execerror("Semantic error in \"read statement\": it is not allowed to modify a constant ",(yyvsp[-1].string));
		}
#line 2305 "interpreter.tab.c"
    break;

  case 51: /* readstring: READSTRING LPAREN VARIABLE RPAREN  */
#line 508 "interpreter.y"
                         {
			 	// Create a new read node
			 	(yyval.st) = new lp::ReadStringStmt((yyvsp[-1].string));
			 }
#line 2314 "interpreter.tab.c"
    break;

  case 52: /* readstring: READSTRING LPAREN CONSTANT RPAREN  */
#line 513 "interpreter.y"
                         {   
 			 	execerror("Semantic error in \"read_string statement\": it is not allowed to modify a constant ",(yyvsp[-1].string));
			 }
#line 2322 "interpreter.tab.c"
    break;

  case 53: /* clearscreen: CLEARSCREEN  */
#line 519 "interpreter.y"
                     {
		 	  // Create a new clear screen node
		 	  (yyval.st) = new lp::ClearScreenStmt();
		     }
#line 2331 "interpreter.tab.c"
    break;

  case 54: /* clearscreen: CLEARSCREEN LPAREN RPAREN  */
#line 524 "interpreter.y"
                     {
		 	  // Allow clearscreen() syntax too
		 	  (yyval.st) = new lp::ClearScreenStmt();
		     }
#line 2340 "interpreter.tab.c"
    break;

  case 55: /* place: PLACE LPAREN exp COMMA exp RPAREN  */
#line 531 "interpreter.y"
                {
			// Create a new place(row,col) node
			(yyval.st) = new lp::PlaceStmt((yyvsp[-3].expNode), (yyvsp[-1].expNode));
		}
#line 2349 "interpreter.tab.c"
    break;

  case 56: /* text: TEXT COLOR_YELLOW  */
#line 538 "interpreter.y"
                {
			(yyval.st) = new lp::TextStmt(YELLOW);
		}
#line 2357 "interpreter.tab.c"
    break;

  case 57: /* text: TEXT COLOR_BLUE  */
#line 542 "interpreter.y"
                {
			(yyval.st) = new lp::TextStmt(BLUE);
		}
#line 2365 "interpreter.tab.c"
    break;

  case 58: /* text: RESET_TEXT  */
#line 546 "interpreter.y"
                {
			(yyval.st) = new lp::TextStmt(RESET);
		}
#line 2373 "interpreter.tab.c"
    break;

  case 59: /* exp: NUMBER  */
#line 552 "interpreter.y"
                { 
			// Create a new number node
			(yyval.expNode) = new lp::NumberNode((yyvsp[0].number));
		}
#line 2382 "interpreter.tab.c"
    break;

  case 60: /* exp: exp PLUS exp  */
#line 557 "interpreter.y"
                { 
			// Create a new plus node
			(yyval.expNode) = new lp::PlusNode((yyvsp[-2].expNode), (yyvsp[0].expNode));
		}
#line 2391 "interpreter.tab.c"
    break;

  case 61: /* exp: exp MINUS exp  */
#line 562 "interpreter.y"
        {
			// Create a new minus node
			(yyval.expNode) = new lp::MinusNode((yyvsp[-2].expNode), (yyvsp[0].expNode));
		}
#line 2400 "interpreter.tab.c"
    break;

  case 62: /* exp: exp MULTIPLICATION exp  */
#line 567 "interpreter.y"
                { 
			// Create a new multiplication node
			(yyval.expNode) = new lp::MultiplicationNode((yyvsp[-2].expNode), (yyvsp[0].expNode));
		}
#line 2409 "interpreter.tab.c"
    break;

  case 63: /* exp: exp DIVISION exp  */
#line 572 "interpreter.y"
                {
		  // Create a new division node	
		  (yyval.expNode) = new lp::DivisionNode((yyvsp[-2].expNode), (yyvsp[0].expNode));
	    }
#line 2418 "interpreter.tab.c"
    break;

  case 64: /* exp: LPAREN exp RPAREN  */
#line 577 "interpreter.y"
        { 
		    // just copy up the expression node 
			(yyval.expNode) = (yyvsp[-1].expNode);
		}
#line 2427 "interpreter.tab.c"
    break;

  case 65: /* exp: PLUS exp  */
#line 582 "interpreter.y"
                { 
		  // Create a new unary plus node	
  		  (yyval.expNode) = new lp::UnaryPlusNode((yyvsp[0].expNode));
		}
#line 2436 "interpreter.tab.c"
    break;

  case 66: /* exp: MINUS exp  */
#line 587 "interpreter.y"
                { 
		  // Create a new unary minus node	
  		  (yyval.expNode) = new lp::UnaryMinusNode((yyvsp[0].expNode));
		}
#line 2445 "interpreter.tab.c"
    break;

  case 67: /* exp: exp MODULO exp  */
#line 592 "interpreter.y"
                {
		  // Create a new modulo node	

		  (yyval.expNode) = new lp::ModuloNode((yyvsp[-2].expNode), (yyvsp[0].expNode));
       	}
#line 2455 "interpreter.tab.c"
    break;

  case 68: /* exp: exp FLOOR_DIVISION exp  */
#line 598 "interpreter.y"
                {
			(yyval.expNode) = new lp::FloorDivisionNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
		}
#line 2463 "interpreter.tab.c"
    break;

  case 69: /* exp: exp CONCATENATION exp  */
#line 603 "interpreter.y"
                {
			(yyval.expNode) = new lp::ConcatNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
		}
#line 2471 "interpreter.tab.c"
    break;

  case 70: /* exp: exp POWER exp  */
#line 607 "interpreter.y"
        { 
		  // Create a new power node	
  		  (yyval.expNode) = new lp::PowerNode((yyvsp[-2].expNode), (yyvsp[0].expNode));
		}
#line 2480 "interpreter.tab.c"
    break;

  case 71: /* exp: exp FACTORIAL  */
#line 612 "interpreter.y"
                {
			(yyval.expNode) = new lp::FactorialNode((yyvsp[-1].expNode));
		}
#line 2488 "interpreter.tab.c"
    break;

  case 72: /* exp: VARIABLE  */
#line 616 "interpreter.y"
                {
		  // Create a new variable node	
		  (yyval.expNode) = new lp::VariableNode((yyvsp[0].string));
		}
#line 2497 "interpreter.tab.c"
    break;

  case 73: /* exp: CONSTANT  */
#line 621 "interpreter.y"
                {
		  // Create a new constant node	
		  (yyval.expNode) = new lp::ConstantNode((yyvsp[0].string));
		}
#line 2506 "interpreter.tab.c"
    break;

  case 74: /* exp: STRING  */
#line 626 "interpreter.y"
                { 
		  // Create a new string node
		  (yyval.expNode) = new lp::StringNode((yyvsp[0].string)); 
		}
#line 2515 "interpreter.tab.c"
    break;

  case 75: /* exp: BUILTIN LPAREN listOfExp RPAREN  */
#line 631 "interpreter.y"
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
#line 2565 "interpreter.tab.c"
    break;

  case 76: /* exp: exp GREATER_THAN exp  */
#line 678 "interpreter.y"
                        {
			  // Create a new "greater than" node	
 				(yyval.expNode) = new lp::GreaterThanNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
			}
#line 2574 "interpreter.tab.c"
    break;

  case 77: /* exp: exp GREATER_OR_EQUAL exp  */
#line 684 "interpreter.y"
                        {
			  // Create a new "greater or equal" node	
 				(yyval.expNode) = new lp::GreaterOrEqualNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
			}
#line 2583 "interpreter.tab.c"
    break;

  case 78: /* exp: exp LESS_THAN exp  */
#line 690 "interpreter.y"
                        {
			  // Create a new "less than" node	
 				(yyval.expNode) = new lp::LessThanNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
			}
#line 2592 "interpreter.tab.c"
    break;

  case 79: /* exp: exp LESS_OR_EQUAL exp  */
#line 696 "interpreter.y"
                        {
			  // Create a new "less or equal" node	
 				(yyval.expNode) = new lp::LessOrEqualNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
			}
#line 2601 "interpreter.tab.c"
    break;

  case 80: /* exp: exp EQUAL exp  */
#line 702 "interpreter.y"
                        {
			  // Create a new "equal" node	
 				(yyval.expNode) = new lp::EqualNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
			}
#line 2610 "interpreter.tab.c"
    break;

  case 81: /* exp: exp NOT_EQUAL exp  */
#line 708 "interpreter.y"
                        {
			  // Create a new "not equal" node	
 				(yyval.expNode) = new lp::NotEqualNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
			}
#line 2619 "interpreter.tab.c"
    break;

  case 82: /* exp: exp AND exp  */
#line 714 "interpreter.y"
                        {
			  // Create a new "logic and" node	
 				(yyval.expNode) = new lp::AndNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
			}
#line 2628 "interpreter.tab.c"
    break;

  case 83: /* exp: exp OR exp  */
#line 720 "interpreter.y"
                        {
			  // Create a new "logic or" node	
 				(yyval.expNode) = new lp::OrNode((yyvsp[-2].expNode),(yyvsp[0].expNode));
			}
#line 2637 "interpreter.tab.c"
    break;

  case 84: /* exp: NOT exp  */
#line 726 "interpreter.y"
                        {
			  // Create a new "logic negation" node	
 				(yyval.expNode) = new lp::NotNode((yyvsp[0].expNode));
			}
#line 2646 "interpreter.tab.c"
    break;

  case 85: /* listOfExp: %empty  */
#line 735 "interpreter.y"
                        {
			    // Create a new list STL
				(yyval.parameters) = new std::list<lp::ExpNode *>(); 
			}
#line 2655 "interpreter.tab.c"
    break;

  case 86: /* listOfExp: exp restOfListOfExp  */
#line 740 "interpreter.y"
                        {
				(yyval.parameters) = (yyvsp[0].parameters);

				// Insert the expression in the list of expressions
				(yyval.parameters)->push_front((yyvsp[-1].expNode));
			}
#line 2666 "interpreter.tab.c"
    break;

  case 87: /* restOfListOfExp: %empty  */
#line 750 "interpreter.y"
                                {
				    // Create a new list STL
					(yyval.parameters) = new std::list<lp::ExpNode *>(); 
				}
#line 2675 "interpreter.tab.c"
    break;

  case 88: /* restOfListOfExp: COMMA exp restOfListOfExp  */
#line 755 "interpreter.y"
                                {
					// Get the list of expressions
					(yyval.parameters) = (yyvsp[0].parameters);

					// Insert the expression in the list of expressions
					(yyval.parameters)->push_front((yyvsp[-1].expNode));
				}
#line 2687 "interpreter.tab.c"
    break;


#line 2691 "interpreter.tab.c"

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

#line 764 "interpreter.y"

