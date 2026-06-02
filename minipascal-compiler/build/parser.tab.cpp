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
#line 1 "src/parser.y"

#include "ast.hpp"

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>

using namespace mp;

extern int yylex();
extern int yylineno;
void yyerror(const char* msg);

Program* g_root = nullptr;

static std::vector<Statement*>* append_statement(std::vector<Statement*>* list, Statement* stmt) {
    if (!list) list = new std::vector<Statement*>();
    list->push_back(stmt);
    return list;
}

static std::vector<FunctionDecl*>* append_function(std::vector<FunctionDecl*>* list, FunctionDecl* fn) {
    if (!list) list = new std::vector<FunctionDecl*>();
    list->push_back(fn);
    return list;
}

static std::vector<Expr*>* append_expr(std::vector<Expr*>* list, Expr* expr) {
    if (!list) list = new std::vector<Expr*>();
    list->push_back(expr);
    return list;
}

static std::vector<std::string>* append_name(std::vector<std::string>* list, char* name) {
    if (!list) list = new std::vector<std::string>();
    list->push_back(std::string(name));
    free(name);
    return list;
}

static std::vector<Parameter>* append_param(std::vector<Parameter>* list, char* name, int type) {
    if (!list) list = new std::vector<Parameter>();
    list->emplace_back(std::string(name), static_cast<ValueType>(type));
    free(name);
    return list;
}

static CompoundStmt* merge_compound(std::vector<Statement*>* decls, CompoundStmt* body) {
    if (!body) body = new CompoundStmt();
    body->prepend(decls);
    return body;
}

#line 126 "build/parser.tab.cpp"

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

#include "parser.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TPROGRAM = 3,                   /* TPROGRAM  */
  YYSYMBOL_TVAR = 4,                       /* TVAR  */
  YYSYMBOL_TBEGIN = 5,                     /* TBEGIN  */
  YYSYMBOL_TEND = 6,                       /* TEND  */
  YYSYMBOL_TIF = 7,                        /* TIF  */
  YYSYMBOL_TTHEN = 8,                      /* TTHEN  */
  YYSYMBOL_TELSE = 9,                      /* TELSE  */
  YYSYMBOL_TWHILE = 10,                    /* TWHILE  */
  YYSYMBOL_TDO = 11,                       /* TDO  */
  YYSYMBOL_TFOR = 12,                      /* TFOR  */
  YYSYMBOL_TTO = 13,                       /* TTO  */
  YYSYMBOL_TRETURN = 14,                   /* TRETURN  */
  YYSYMBOL_TPROCEDURE = 15,                /* TPROCEDURE  */
  YYSYMBOL_TFUNCTION = 16,                 /* TFUNCTION  */
  YYSYMBOL_TINTEGER = 17,                  /* TINTEGER  */
  YYSYMBOL_TBOOLEAN = 18,                  /* TBOOLEAN  */
  YYSYMBOL_TTRUE = 19,                     /* TTRUE  */
  YYSYMBOL_TFALSE = 20,                    /* TFALSE  */
  YYSYMBOL_TAND = 21,                      /* TAND  */
  YYSYMBOL_TOR = 22,                       /* TOR  */
  YYSYMBOL_TNOT = 23,                      /* TNOT  */
  YYSYMBOL_TDIV = 24,                      /* TDIV  */
  YYSYMBOL_TMOD = 25,                      /* TMOD  */
  YYSYMBOL_TWRITE = 26,                    /* TWRITE  */
  YYSYMBOL_TWRITELN = 27,                  /* TWRITELN  */
  YYSYMBOL_TREAD = 28,                     /* TREAD  */
  YYSYMBOL_TASSIGN = 29,                   /* TASSIGN  */
  YYSYMBOL_TNE = 30,                       /* TNE  */
  YYSYMBOL_TLE = 31,                       /* TLE  */
  YYSYMBOL_TGE = 32,                       /* TGE  */
  YYSYMBOL_TLT = 33,                       /* TLT  */
  YYSYMBOL_TGT = 34,                       /* TGT  */
  YYSYMBOL_TEQ = 35,                       /* TEQ  */
  YYSYMBOL_TCOLON = 36,                    /* TCOLON  */
  YYSYMBOL_TSEMI = 37,                     /* TSEMI  */
  YYSYMBOL_TDOT = 38,                      /* TDOT  */
  YYSYMBOL_TCOMMA = 39,                    /* TCOMMA  */
  YYSYMBOL_TLPAREN = 40,                   /* TLPAREN  */
  YYSYMBOL_TRPAREN = 41,                   /* TRPAREN  */
  YYSYMBOL_TPLUS = 42,                     /* TPLUS  */
  YYSYMBOL_TMINUS = 43,                    /* TMINUS  */
  YYSYMBOL_TMUL = 44,                      /* TMUL  */
  YYSYMBOL_TINTLIT = 45,                   /* TINTLIT  */
  YYSYMBOL_TIDENT = 46,                    /* TIDENT  */
  YYSYMBOL_TSTRING = 47,                   /* TSTRING  */
  YYSYMBOL_LOWER_THAN_ELSE = 48,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_UMINUS = 49,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 50,                  /* $accept  */
  YYSYMBOL_program = 51,                   /* program  */
  YYSYMBOL_global_vars_opt = 52,           /* global_vars_opt  */
  YYSYMBOL_var_sections = 53,              /* var_sections  */
  YYSYMBOL_var_decl_list = 54,             /* var_decl_list  */
  YYSYMBOL_functions_opt = 55,             /* functions_opt  */
  YYSYMBOL_function_decl = 56,             /* function_decl  */
  YYSYMBOL_procedure_decl = 57,            /* procedure_decl  */
  YYSYMBOL_local_vars_opt = 58,            /* local_vars_opt  */
  YYSYMBOL_params_opt = 59,                /* params_opt  */
  YYSYMBOL_param_list = 60,                /* param_list  */
  YYSYMBOL_type_spec = 61,                 /* type_spec  */
  YYSYMBOL_compound_stmt = 62,             /* compound_stmt  */
  YYSYMBOL_stmt_list_opt = 63,             /* stmt_list_opt  */
  YYSYMBOL_stmt_list = 64,                 /* stmt_list  */
  YYSYMBOL_statement = 65,                 /* statement  */
  YYSYMBOL_assignment_stmt = 66,           /* assignment_stmt  */
  YYSYMBOL_if_stmt = 67,                   /* if_stmt  */
  YYSYMBOL_while_stmt = 68,                /* while_stmt  */
  YYSYMBOL_for_stmt = 69,                  /* for_stmt  */
  YYSYMBOL_return_stmt = 70,               /* return_stmt  */
  YYSYMBOL_write_stmt = 71,                /* write_stmt  */
  YYSYMBOL_expr_stmt = 72,                 /* expr_stmt  */
  YYSYMBOL_write_args_opt = 73,            /* write_args_opt  */
  YYSYMBOL_write_args = 74,                /* write_args  */
  YYSYMBOL_expr = 75,                      /* expr  */
  YYSYMBOL_relation = 76,                  /* relation  */
  YYSYMBOL_arith = 77,                     /* arith  */
  YYSYMBOL_term = 78,                      /* term  */
  YYSYMBOL_unary = 79,                     /* unary  */
  YYSYMBOL_factor = 80,                    /* factor  */
  YYSYMBOL_function_call = 81,             /* function_call  */
  YYSYMBOL_expr_list_opt = 82,             /* expr_list_opt  */
  YYSYMBOL_expr_list = 83,                 /* expr_list  */
  YYSYMBOL_ident_list = 84                 /* ident_list  */
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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   166

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  85
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  164

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   304


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
      45,    46,    47,    48,    49
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   106,   106,   114,   115,   119,   120,   128,   129,   135,
     136,   137,   141,   148,   155,   156,   160,   161,   165,   166,
     170,   171,   175,   179,   180,   184,   185,   189,   190,   191,
     192,   193,   194,   195,   196,   200,   207,   208,   212,   216,
     223,   224,   228,   229,   230,   234,   238,   239,   243,   244,
     245,   246,   250,   251,   252,   256,   257,   258,   259,   260,
     261,   262,   266,   267,   268,   272,   273,   274,   275,   279,
     280,   281,   282,   286,   287,   288,   289,   290,   291,   295,
     302,   303,   307,   308,   312,   313
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
  "\"end of file\"", "error", "\"invalid token\"", "TPROGRAM", "TVAR",
  "TBEGIN", "TEND", "TIF", "TTHEN", "TELSE", "TWHILE", "TDO", "TFOR",
  "TTO", "TRETURN", "TPROCEDURE", "TFUNCTION", "TINTEGER", "TBOOLEAN",
  "TTRUE", "TFALSE", "TAND", "TOR", "TNOT", "TDIV", "TMOD", "TWRITE",
  "TWRITELN", "TREAD", "TASSIGN", "TNE", "TLE", "TGE", "TLT", "TGT", "TEQ",
  "TCOLON", "TSEMI", "TDOT", "TCOMMA", "TLPAREN", "TRPAREN", "TPLUS",
  "TMINUS", "TMUL", "TINTLIT", "TIDENT", "TSTRING", "LOWER_THAN_ELSE",
  "UMINUS", "$accept", "program", "global_vars_opt", "var_sections",
  "var_decl_list", "functions_opt", "function_decl", "procedure_decl",
  "local_vars_opt", "params_opt", "param_list", "type_spec",
  "compound_stmt", "stmt_list_opt", "stmt_list", "statement",
  "assignment_stmt", "if_stmt", "while_stmt", "for_stmt", "return_stmt",
  "write_stmt", "expr_stmt", "write_args_opt", "write_args", "expr",
  "relation", "arith", "term", "unary", "factor", "function_call",
  "expr_list_opt", "expr_list", "ident_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-72)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      23,   -38,    10,    -6,   -72,    37,     0,   -72,    54,   -72,
       0,     4,    17,     0,    31,    68,     6,     9,    41,    47,
     -72,   -72,    18,     0,    68,   -72,   -72,    26,   -72,    52,
      52,    50,    52,    43,    65,     5,   -72,   102,    73,   -72,
     -72,   -72,   -72,   -72,   -72,   -72,   -72,   -72,    76,    83,
     -72,    88,   -72,   -72,   -72,    52,    52,    52,    52,   -72,
     101,     7,   -72,    69,    -7,   -72,   -72,   -72,    67,   109,
      98,    19,    19,    52,    52,   -72,     9,    97,    97,   -72,
     -72,     3,   -72,   -72,     9,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,     9,    52,
     -72,   103,   106,    98,   105,    98,    98,   107,   108,   -72,
     114,   110,   113,   112,   -72,   133,   -72,   -72,    48,    48,
      48,    48,    48,    48,    -7,    -7,   -72,   -72,   -72,   -72,
     100,   -72,    34,   -72,   -72,    52,    68,   117,   111,   119,
       9,    52,   -72,    98,    98,   -72,    37,   120,    68,   -72,
      96,    54,   153,    68,   122,     9,   123,   -72,    37,   -72,
     -72,   153,   124,   -72
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     3,     0,     9,     4,    84,
       5,     0,     0,     0,     0,     0,     0,    23,     0,     0,
      10,    11,     0,     6,     0,    20,    21,     0,    85,     0,
       0,     0,    40,     0,    44,     0,    34,     0,    24,    25,
      27,    28,    29,    30,    31,    32,    33,    45,     0,     0,
       2,     0,     7,    74,    75,     0,     0,     0,     0,    73,
      76,     0,    54,    61,    64,    68,    72,    77,     0,     0,
      41,    46,    46,     0,    80,    22,     0,    16,    16,     8,
      71,     0,    70,    69,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      49,     0,    47,    48,     0,    35,    82,     0,    81,    26,
       0,     0,    17,     0,    78,    36,    53,    52,    56,    58,
      60,    57,    59,    55,    62,    63,    66,    67,    65,    38,
       0,    42,     0,    43,    79,     0,     0,     0,     0,     0,
       0,     0,    51,    50,    83,    18,    14,     0,     0,    37,
       0,    15,     0,     0,     0,     0,     0,    19,    14,    39,
      13,     0,     0,    12
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -72,   -72,   -72,   157,   150,   -72,   -72,   -72,     8,    86,
     -72,   -22,   -12,   -72,   -72,   -71,   -72,   -72,   -72,   -72,
     -72,   -72,   -72,    93,   -72,   -26,    42,    45,    36,   -46,
     -72,   -16,   -72,   -72,    -3
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     7,   151,    10,    12,    20,    21,   152,   111,
     112,    27,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,   101,   102,   103,    62,    63,    64,    65,
      66,    67,   107,   108,    11
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      22,    47,    51,    61,    68,   109,    70,    14,     3,    80,
       4,    82,    83,   115,    17,    84,    29,    95,    96,    30,
      14,    31,    17,    32,    85,    86,     1,   129,    85,    86,
      81,     5,    18,    19,    73,    33,    34,    97,    53,    54,
      15,     6,    55,    16,   114,    74,     9,   105,   106,   126,
     127,   128,    28,    53,    54,    35,    50,    55,    13,    56,
      47,    57,    58,    52,    59,    60,   100,    24,    47,   149,
      16,    53,    54,   130,    56,    55,    57,    58,    98,    59,
      60,   142,    47,    71,   159,    25,    26,    48,    85,    86,
      93,    94,    56,    49,    57,    58,    69,    59,    60,    87,
      88,    89,    90,    91,    92,    72,   143,   155,    75,   144,
      76,    93,    94,   141,   145,   150,    77,    85,    86,    85,
      86,    85,    86,    78,    47,    79,   154,   116,   117,   124,
     125,   157,   118,   119,   120,   121,   122,   123,    99,    47,
     156,    74,   140,   110,   131,   132,   133,   135,   134,   162,
     136,   137,   138,   139,   146,   148,   153,   147,    17,   158,
     160,   163,     8,    23,   113,   104,   161
};

static const yytype_uint8 yycheck[] =
{
      12,    17,    24,    29,    30,    76,    32,    10,    46,    55,
       0,    57,    58,    84,     5,     8,     7,    24,    25,    10,
      23,    12,     5,    14,    21,    22,     3,    98,    21,    22,
      56,    37,    15,    16,    29,    26,    27,    44,    19,    20,
      36,     4,    23,    39,    41,    40,    46,    73,    74,    95,
      96,    97,    46,    19,    20,    46,    38,    23,     4,    40,
      76,    42,    43,    37,    45,    46,    47,    36,    84,   140,
      39,    19,    20,    99,    40,    23,    42,    43,    11,    45,
      46,    47,    98,    40,   155,    17,    18,    46,    21,    22,
      42,    43,    40,    46,    42,    43,    46,    45,    46,    30,
      31,    32,    33,    34,    35,    40,   132,    11,     6,   135,
      37,    42,    43,    13,   136,   141,    40,    21,    22,    21,
      22,    21,    22,    40,   140,    37,   148,    85,    86,    93,
      94,   153,    87,    88,    89,    90,    91,    92,    29,   155,
     152,    40,     9,    46,    41,    39,    41,    39,    41,   161,
      36,    41,    39,    41,    37,    36,    36,    46,     5,    37,
      37,    37,     5,    13,    78,    72,   158
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    51,    46,     0,    37,     4,    52,    53,    46,
      54,    84,    55,     4,    84,    36,    39,     5,    15,    16,
      56,    57,    62,    54,    36,    17,    18,    61,    46,     7,
      10,    12,    14,    26,    27,    46,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    81,    46,    46,
      38,    61,    37,    19,    20,    23,    40,    42,    43,    45,
      46,    75,    76,    77,    78,    79,    80,    81,    75,    46,
      75,    40,    40,    29,    40,     6,    37,    40,    40,    37,
      79,    75,    79,    79,     8,    21,    22,    30,    31,    32,
      33,    34,    35,    42,    43,    24,    25,    44,    11,    29,
      47,    73,    74,    75,    73,    75,    75,    82,    83,    65,
      46,    59,    60,    59,    41,    65,    76,    76,    77,    77,
      77,    77,    77,    77,    78,    78,    79,    79,    79,    65,
      75,    41,    39,    41,    41,    39,    36,    41,    39,    41,
       9,    13,    47,    75,    75,    61,    37,    46,    36,    65,
      75,    53,    58,    36,    61,    11,    62,    61,    37,    65,
      37,    58,    62,    37
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    50,    51,    52,    52,    53,    53,    54,    54,    55,
      55,    55,    56,    57,    58,    58,    59,    59,    60,    60,
      61,    61,    62,    63,    63,    64,    64,    65,    65,    65,
      65,    65,    65,    65,    65,    66,    67,    67,    68,    69,
      70,    70,    71,    71,    71,    72,    73,    73,    74,    74,
      74,    74,    75,    75,    75,    76,    76,    76,    76,    76,
      76,    76,    77,    77,    77,    78,    78,    78,    78,    79,
      79,    79,    79,    80,    80,    80,    80,    80,    80,    81,
      82,    82,    83,    83,    84,    84
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     7,     0,     1,     2,     3,     4,     5,     0,
       2,     2,    11,     9,     0,     1,     0,     1,     3,     5,
       1,     1,     3,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     4,     6,     4,     8,
       1,     2,     4,     4,     1,     1,     0,     1,     1,     1,
       3,     3,     3,     3,     1,     3,     3,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     1,     2,
       2,     2,     1,     1,     1,     1,     1,     1,     3,     4,
       0,     1,     1,     3,     1,     3
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
  case 2: /* program: TPROGRAM TIDENT TSEMI global_vars_opt functions_opt compound_stmt TDOT  */
#line 106 "src/parser.y"
                                                                             {
          g_root = new Program(std::string((yyvsp[-5].sval)), (yyvsp[-3].stmt_list), (yyvsp[-2].func_list), (yyvsp[-1].block));
          free((yyvsp[-5].sval));
          (yyval.program) = g_root;
      }
#line 1585 "build/parser.tab.cpp"
    break;

  case 3: /* global_vars_opt: %empty  */
#line 114 "src/parser.y"
                                { (yyval.stmt_list) = new std::vector<Statement*>(); }
#line 1591 "build/parser.tab.cpp"
    break;

  case 4: /* global_vars_opt: var_sections  */
#line 115 "src/parser.y"
                                { (yyval.stmt_list) = (yyvsp[0].stmt_list); }
#line 1597 "build/parser.tab.cpp"
    break;

  case 5: /* var_sections: TVAR var_decl_list  */
#line 119 "src/parser.y"
                                            { (yyval.stmt_list) = (yyvsp[0].stmt_list); }
#line 1603 "build/parser.tab.cpp"
    break;

  case 6: /* var_sections: var_sections TVAR var_decl_list  */
#line 120 "src/parser.y"
                                            {
          for (auto* stmt : *(yyvsp[0].stmt_list)) (yyvsp[-2].stmt_list)->push_back(stmt);
          delete (yyvsp[0].stmt_list);
          (yyval.stmt_list) = (yyvsp[-2].stmt_list);
      }
#line 1613 "build/parser.tab.cpp"
    break;

  case 7: /* var_decl_list: ident_list TCOLON type_spec TSEMI  */
#line 128 "src/parser.y"
                                            { (yyval.stmt_list) = append_statement(nullptr, new VarDeclStmt((yyvsp[-3].name_list), static_cast<ValueType>((yyvsp[-1].type)))); }
#line 1619 "build/parser.tab.cpp"
    break;

  case 8: /* var_decl_list: var_decl_list ident_list TCOLON type_spec TSEMI  */
#line 129 "src/parser.y"
                                                      {
          (yyval.stmt_list) = append_statement((yyvsp[-4].stmt_list), new VarDeclStmt((yyvsp[-3].name_list), static_cast<ValueType>((yyvsp[-1].type))));
      }
#line 1627 "build/parser.tab.cpp"
    break;

  case 9: /* functions_opt: %empty  */
#line 135 "src/parser.y"
                                { (yyval.func_list) = new std::vector<FunctionDecl*>(); }
#line 1633 "build/parser.tab.cpp"
    break;

  case 10: /* functions_opt: functions_opt function_decl  */
#line 136 "src/parser.y"
                                   { (yyval.func_list) = append_function((yyvsp[-1].func_list), (yyvsp[0].func)); }
#line 1639 "build/parser.tab.cpp"
    break;

  case 11: /* functions_opt: functions_opt procedure_decl  */
#line 137 "src/parser.y"
                                   { (yyval.func_list) = append_function((yyvsp[-1].func_list), (yyvsp[0].func)); }
#line 1645 "build/parser.tab.cpp"
    break;

  case 12: /* function_decl: TFUNCTION TIDENT TLPAREN params_opt TRPAREN TCOLON type_spec TSEMI local_vars_opt compound_stmt TSEMI  */
#line 141 "src/parser.y"
                                                                                                            {
          (yyval.func) = new FunctionDecl(std::string((yyvsp[-9].sval)), (yyvsp[-7].param_list), static_cast<ValueType>((yyvsp[-4].type)), merge_compound((yyvsp[-2].stmt_list), (yyvsp[-1].block)));
          free((yyvsp[-9].sval));
      }
#line 1654 "build/parser.tab.cpp"
    break;

  case 13: /* procedure_decl: TPROCEDURE TIDENT TLPAREN params_opt TRPAREN TSEMI local_vars_opt compound_stmt TSEMI  */
#line 148 "src/parser.y"
                                                                                            {
          (yyval.func) = new FunctionDecl(std::string((yyvsp[-7].sval)), (yyvsp[-5].param_list), ValueType::Void, merge_compound((yyvsp[-2].stmt_list), (yyvsp[-1].block)));
          free((yyvsp[-7].sval));
      }
#line 1663 "build/parser.tab.cpp"
    break;

  case 14: /* local_vars_opt: %empty  */
#line 155 "src/parser.y"
                                { (yyval.stmt_list) = new std::vector<Statement*>(); }
#line 1669 "build/parser.tab.cpp"
    break;

  case 15: /* local_vars_opt: var_sections  */
#line 156 "src/parser.y"
                                { (yyval.stmt_list) = (yyvsp[0].stmt_list); }
#line 1675 "build/parser.tab.cpp"
    break;

  case 16: /* params_opt: %empty  */
#line 160 "src/parser.y"
                                { (yyval.param_list) = new std::vector<Parameter>(); }
#line 1681 "build/parser.tab.cpp"
    break;

  case 17: /* params_opt: param_list  */
#line 161 "src/parser.y"
                                { (yyval.param_list) = (yyvsp[0].param_list); }
#line 1687 "build/parser.tab.cpp"
    break;

  case 18: /* param_list: TIDENT TCOLON type_spec  */
#line 165 "src/parser.y"
                                { (yyval.param_list) = append_param(nullptr, (yyvsp[-2].sval), (yyvsp[0].type)); }
#line 1693 "build/parser.tab.cpp"
    break;

  case 19: /* param_list: param_list TCOMMA TIDENT TCOLON type_spec  */
#line 166 "src/parser.y"
                                                { (yyval.param_list) = append_param((yyvsp[-4].param_list), (yyvsp[-2].sval), (yyvsp[0].type)); }
#line 1699 "build/parser.tab.cpp"
    break;

  case 20: /* type_spec: TINTEGER  */
#line 170 "src/parser.y"
                                { (yyval.type) = static_cast<int>(ValueType::Integer); }
#line 1705 "build/parser.tab.cpp"
    break;

  case 21: /* type_spec: TBOOLEAN  */
#line 171 "src/parser.y"
                                { (yyval.type) = static_cast<int>(ValueType::Boolean); }
#line 1711 "build/parser.tab.cpp"
    break;

  case 22: /* compound_stmt: TBEGIN stmt_list_opt TEND  */
#line 175 "src/parser.y"
                                { (yyval.block) = new CompoundStmt((yyvsp[-1].stmt_list)); }
#line 1717 "build/parser.tab.cpp"
    break;

  case 23: /* stmt_list_opt: %empty  */
#line 179 "src/parser.y"
                                { (yyval.stmt_list) = new std::vector<Statement*>(); }
#line 1723 "build/parser.tab.cpp"
    break;

  case 24: /* stmt_list_opt: stmt_list  */
#line 180 "src/parser.y"
                                { (yyval.stmt_list) = (yyvsp[0].stmt_list); }
#line 1729 "build/parser.tab.cpp"
    break;

  case 25: /* stmt_list: statement  */
#line 184 "src/parser.y"
                                { (yyval.stmt_list) = append_statement(nullptr, (yyvsp[0].stmt)); }
#line 1735 "build/parser.tab.cpp"
    break;

  case 26: /* stmt_list: stmt_list TSEMI statement  */
#line 185 "src/parser.y"
                                { (yyval.stmt_list) = append_statement((yyvsp[-2].stmt_list), (yyvsp[0].stmt)); }
#line 1741 "build/parser.tab.cpp"
    break;

  case 27: /* statement: assignment_stmt  */
#line 189 "src/parser.y"
                                { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1747 "build/parser.tab.cpp"
    break;

  case 28: /* statement: if_stmt  */
#line 190 "src/parser.y"
                                { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1753 "build/parser.tab.cpp"
    break;

  case 29: /* statement: while_stmt  */
#line 191 "src/parser.y"
                                { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1759 "build/parser.tab.cpp"
    break;

  case 30: /* statement: for_stmt  */
#line 192 "src/parser.y"
                                { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1765 "build/parser.tab.cpp"
    break;

  case 31: /* statement: return_stmt  */
#line 193 "src/parser.y"
                                { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1771 "build/parser.tab.cpp"
    break;

  case 32: /* statement: write_stmt  */
#line 194 "src/parser.y"
                                { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1777 "build/parser.tab.cpp"
    break;

  case 33: /* statement: expr_stmt  */
#line 195 "src/parser.y"
                                { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1783 "build/parser.tab.cpp"
    break;

  case 34: /* statement: compound_stmt  */
#line 196 "src/parser.y"
                                { (yyval.stmt) = (yyvsp[0].block); }
#line 1789 "build/parser.tab.cpp"
    break;

  case 35: /* assignment_stmt: TIDENT TASSIGN expr  */
#line 200 "src/parser.y"
                                {
          (yyval.stmt) = new AssignStmt(std::string((yyvsp[-2].sval)), (yyvsp[0].expr));
          free((yyvsp[-2].sval));
      }
#line 1798 "build/parser.tab.cpp"
    break;

  case 36: /* if_stmt: TIF expr TTHEN statement  */
#line 207 "src/parser.y"
                                                     { (yyval.stmt) = new IfStmt((yyvsp[-2].expr), (yyvsp[0].stmt), nullptr); }
#line 1804 "build/parser.tab.cpp"
    break;

  case 37: /* if_stmt: TIF expr TTHEN statement TELSE statement  */
#line 208 "src/parser.y"
                                                     { (yyval.stmt) = new IfStmt((yyvsp[-4].expr), (yyvsp[-2].stmt), (yyvsp[0].stmt)); }
#line 1810 "build/parser.tab.cpp"
    break;

  case 38: /* while_stmt: TWHILE expr TDO statement  */
#line 212 "src/parser.y"
                                { (yyval.stmt) = new WhileStmt((yyvsp[-2].expr), (yyvsp[0].stmt)); }
#line 1816 "build/parser.tab.cpp"
    break;

  case 39: /* for_stmt: TFOR TIDENT TASSIGN expr TTO expr TDO statement  */
#line 216 "src/parser.y"
                                                      {
          (yyval.stmt) = new ForStmt(std::string((yyvsp[-6].sval)), (yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].stmt));
          free((yyvsp[-6].sval));
      }
#line 1825 "build/parser.tab.cpp"
    break;

  case 40: /* return_stmt: TRETURN  */
#line 223 "src/parser.y"
                                 { (yyval.stmt) = new ReturnStmt(); }
#line 1831 "build/parser.tab.cpp"
    break;

  case 41: /* return_stmt: TRETURN expr  */
#line 224 "src/parser.y"
                                 { (yyval.stmt) = new ReturnStmt((yyvsp[0].expr)); }
#line 1837 "build/parser.tab.cpp"
    break;

  case 42: /* write_stmt: TWRITE TLPAREN write_args_opt TRPAREN  */
#line 228 "src/parser.y"
                                              { (yyval.stmt) = new WriteStmt(false, (yyvsp[-1].expr_list)); }
#line 1843 "build/parser.tab.cpp"
    break;

  case 43: /* write_stmt: TWRITELN TLPAREN write_args_opt TRPAREN  */
#line 229 "src/parser.y"
                                              { (yyval.stmt) = new WriteStmt(true, (yyvsp[-1].expr_list)); }
#line 1849 "build/parser.tab.cpp"
    break;

  case 44: /* write_stmt: TWRITELN  */
#line 230 "src/parser.y"
                                               { (yyval.stmt) = new WriteStmt(true, new std::vector<Expr*>()); }
#line 1855 "build/parser.tab.cpp"
    break;

  case 45: /* expr_stmt: function_call  */
#line 234 "src/parser.y"
                                 { (yyval.stmt) = new ExprStmt((yyvsp[0].expr)); }
#line 1861 "build/parser.tab.cpp"
    break;

  case 46: /* write_args_opt: %empty  */
#line 238 "src/parser.y"
                                { (yyval.expr_list) = new std::vector<Expr*>(); }
#line 1867 "build/parser.tab.cpp"
    break;

  case 47: /* write_args_opt: write_args  */
#line 239 "src/parser.y"
                                { (yyval.expr_list) = (yyvsp[0].expr_list); }
#line 1873 "build/parser.tab.cpp"
    break;

  case 48: /* write_args: expr  */
#line 243 "src/parser.y"
                                { (yyval.expr_list) = append_expr(nullptr, (yyvsp[0].expr)); }
#line 1879 "build/parser.tab.cpp"
    break;

  case 49: /* write_args: TSTRING  */
#line 244 "src/parser.y"
                                { (yyval.expr_list) = append_expr(nullptr, new StringExpr(std::string((yyvsp[0].sval)))); free((yyvsp[0].sval)); }
#line 1885 "build/parser.tab.cpp"
    break;

  case 50: /* write_args: write_args TCOMMA expr  */
#line 245 "src/parser.y"
                                { (yyval.expr_list) = append_expr((yyvsp[-2].expr_list), (yyvsp[0].expr)); }
#line 1891 "build/parser.tab.cpp"
    break;

  case 51: /* write_args: write_args TCOMMA TSTRING  */
#line 246 "src/parser.y"
                                { (yyval.expr_list) = append_expr((yyvsp[-2].expr_list), new StringExpr(std::string((yyvsp[0].sval)))); free((yyvsp[0].sval)); }
#line 1897 "build/parser.tab.cpp"
    break;

  case 52: /* expr: expr TOR relation  */
#line 250 "src/parser.y"
                                { (yyval.expr) = new BinaryExpr((yyvsp[-2].expr), "or", (yyvsp[0].expr)); }
#line 1903 "build/parser.tab.cpp"
    break;

  case 53: /* expr: expr TAND relation  */
#line 251 "src/parser.y"
                                { (yyval.expr) = new BinaryExpr((yyvsp[-2].expr), "and", (yyvsp[0].expr)); }
#line 1909 "build/parser.tab.cpp"
    break;

  case 54: /* expr: relation  */
#line 252 "src/parser.y"
                                { (yyval.expr) = (yyvsp[0].expr); }
#line 1915 "build/parser.tab.cpp"
    break;

  case 55: /* relation: arith TEQ arith  */
#line 256 "src/parser.y"
                                { (yyval.expr) = new BinaryExpr((yyvsp[-2].expr), "=", (yyvsp[0].expr)); }
#line 1921 "build/parser.tab.cpp"
    break;

  case 56: /* relation: arith TNE arith  */
#line 257 "src/parser.y"
                                { (yyval.expr) = new BinaryExpr((yyvsp[-2].expr), "<>", (yyvsp[0].expr)); }
#line 1927 "build/parser.tab.cpp"
    break;

  case 57: /* relation: arith TLT arith  */
#line 258 "src/parser.y"
                                { (yyval.expr) = new BinaryExpr((yyvsp[-2].expr), "<", (yyvsp[0].expr)); }
#line 1933 "build/parser.tab.cpp"
    break;

  case 58: /* relation: arith TLE arith  */
#line 259 "src/parser.y"
                                { (yyval.expr) = new BinaryExpr((yyvsp[-2].expr), "<=", (yyvsp[0].expr)); }
#line 1939 "build/parser.tab.cpp"
    break;

  case 59: /* relation: arith TGT arith  */
#line 260 "src/parser.y"
                                { (yyval.expr) = new BinaryExpr((yyvsp[-2].expr), ">", (yyvsp[0].expr)); }
#line 1945 "build/parser.tab.cpp"
    break;

  case 60: /* relation: arith TGE arith  */
#line 261 "src/parser.y"
                                { (yyval.expr) = new BinaryExpr((yyvsp[-2].expr), ">=", (yyvsp[0].expr)); }
#line 1951 "build/parser.tab.cpp"
    break;

  case 61: /* relation: arith  */
#line 262 "src/parser.y"
                                { (yyval.expr) = (yyvsp[0].expr); }
#line 1957 "build/parser.tab.cpp"
    break;

  case 62: /* arith: arith TPLUS term  */
#line 266 "src/parser.y"
                                { (yyval.expr) = new BinaryExpr((yyvsp[-2].expr), "+", (yyvsp[0].expr)); }
#line 1963 "build/parser.tab.cpp"
    break;

  case 63: /* arith: arith TMINUS term  */
#line 267 "src/parser.y"
                                { (yyval.expr) = new BinaryExpr((yyvsp[-2].expr), "-", (yyvsp[0].expr)); }
#line 1969 "build/parser.tab.cpp"
    break;

  case 64: /* arith: term  */
#line 268 "src/parser.y"
                                { (yyval.expr) = (yyvsp[0].expr); }
#line 1975 "build/parser.tab.cpp"
    break;

  case 65: /* term: term TMUL unary  */
#line 272 "src/parser.y"
                                { (yyval.expr) = new BinaryExpr((yyvsp[-2].expr), "*", (yyvsp[0].expr)); }
#line 1981 "build/parser.tab.cpp"
    break;

  case 66: /* term: term TDIV unary  */
#line 273 "src/parser.y"
                                { (yyval.expr) = new BinaryExpr((yyvsp[-2].expr), "div", (yyvsp[0].expr)); }
#line 1987 "build/parser.tab.cpp"
    break;

  case 67: /* term: term TMOD unary  */
#line 274 "src/parser.y"
                                { (yyval.expr) = new BinaryExpr((yyvsp[-2].expr), "mod", (yyvsp[0].expr)); }
#line 1993 "build/parser.tab.cpp"
    break;

  case 68: /* term: unary  */
#line 275 "src/parser.y"
                                { (yyval.expr) = (yyvsp[0].expr); }
#line 1999 "build/parser.tab.cpp"
    break;

  case 69: /* unary: TMINUS unary  */
#line 279 "src/parser.y"
                                { (yyval.expr) = new UnaryExpr("-", (yyvsp[0].expr)); }
#line 2005 "build/parser.tab.cpp"
    break;

  case 70: /* unary: TPLUS unary  */
#line 280 "src/parser.y"
                                { (yyval.expr) = (yyvsp[0].expr); }
#line 2011 "build/parser.tab.cpp"
    break;

  case 71: /* unary: TNOT unary  */
#line 281 "src/parser.y"
                                { (yyval.expr) = new UnaryExpr("not", (yyvsp[0].expr)); }
#line 2017 "build/parser.tab.cpp"
    break;

  case 72: /* unary: factor  */
#line 282 "src/parser.y"
                                { (yyval.expr) = (yyvsp[0].expr); }
#line 2023 "build/parser.tab.cpp"
    break;

  case 73: /* factor: TINTLIT  */
#line 286 "src/parser.y"
                                { (yyval.expr) = new IntegerExpr((yyvsp[0].ival)); }
#line 2029 "build/parser.tab.cpp"
    break;

  case 74: /* factor: TTRUE  */
#line 287 "src/parser.y"
                                { (yyval.expr) = new BooleanExpr(true); }
#line 2035 "build/parser.tab.cpp"
    break;

  case 75: /* factor: TFALSE  */
#line 288 "src/parser.y"
                                { (yyval.expr) = new BooleanExpr(false); }
#line 2041 "build/parser.tab.cpp"
    break;

  case 76: /* factor: TIDENT  */
#line 289 "src/parser.y"
                                { (yyval.expr) = new VariableExpr(std::string((yyvsp[0].sval))); free((yyvsp[0].sval)); }
#line 2047 "build/parser.tab.cpp"
    break;

  case 77: /* factor: function_call  */
#line 290 "src/parser.y"
                                { (yyval.expr) = (yyvsp[0].expr); }
#line 2053 "build/parser.tab.cpp"
    break;

  case 78: /* factor: TLPAREN expr TRPAREN  */
#line 291 "src/parser.y"
                                { (yyval.expr) = (yyvsp[-1].expr); }
#line 2059 "build/parser.tab.cpp"
    break;

  case 79: /* function_call: TIDENT TLPAREN expr_list_opt TRPAREN  */
#line 295 "src/parser.y"
                                           {
          (yyval.expr) = new CallExpr(std::string((yyvsp[-3].sval)), (yyvsp[-1].expr_list));
          free((yyvsp[-3].sval));
      }
#line 2068 "build/parser.tab.cpp"
    break;

  case 80: /* expr_list_opt: %empty  */
#line 302 "src/parser.y"
                                { (yyval.expr_list) = new std::vector<Expr*>(); }
#line 2074 "build/parser.tab.cpp"
    break;

  case 81: /* expr_list_opt: expr_list  */
#line 303 "src/parser.y"
                                { (yyval.expr_list) = (yyvsp[0].expr_list); }
#line 2080 "build/parser.tab.cpp"
    break;

  case 82: /* expr_list: expr  */
#line 307 "src/parser.y"
                                { (yyval.expr_list) = append_expr(nullptr, (yyvsp[0].expr)); }
#line 2086 "build/parser.tab.cpp"
    break;

  case 83: /* expr_list: expr_list TCOMMA expr  */
#line 308 "src/parser.y"
                                { (yyval.expr_list) = append_expr((yyvsp[-2].expr_list), (yyvsp[0].expr)); }
#line 2092 "build/parser.tab.cpp"
    break;

  case 84: /* ident_list: TIDENT  */
#line 312 "src/parser.y"
                                { (yyval.name_list) = append_name(nullptr, (yyvsp[0].sval)); }
#line 2098 "build/parser.tab.cpp"
    break;

  case 85: /* ident_list: ident_list TCOMMA TIDENT  */
#line 313 "src/parser.y"
                                { (yyval.name_list) = append_name((yyvsp[-2].name_list), (yyvsp[0].sval)); }
#line 2104 "build/parser.tab.cpp"
    break;


#line 2108 "build/parser.tab.cpp"

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

#line 316 "src/parser.y"


void yyerror(const char* msg) {
    std::fprintf(stderr, "Syntax error at line %d: %s\n", yylineno, msg);
}
