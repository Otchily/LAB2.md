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

#ifndef YY_YY_BUILD_PARSER_TAB_HPP_INCLUDED
# define YY_YY_BUILD_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
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
    TPROGRAM = 258,                /* TPROGRAM  */
    TVAR = 259,                    /* TVAR  */
    TBEGIN = 260,                  /* TBEGIN  */
    TEND = 261,                    /* TEND  */
    TIF = 262,                     /* TIF  */
    TTHEN = 263,                   /* TTHEN  */
    TELSE = 264,                   /* TELSE  */
    TWHILE = 265,                  /* TWHILE  */
    TDO = 266,                     /* TDO  */
    TFOR = 267,                    /* TFOR  */
    TTO = 268,                     /* TTO  */
    TRETURN = 269,                 /* TRETURN  */
    TPROCEDURE = 270,              /* TPROCEDURE  */
    TFUNCTION = 271,               /* TFUNCTION  */
    TINTEGER = 272,                /* TINTEGER  */
    TBOOLEAN = 273,                /* TBOOLEAN  */
    TTRUE = 274,                   /* TTRUE  */
    TFALSE = 275,                  /* TFALSE  */
    TAND = 276,                    /* TAND  */
    TOR = 277,                     /* TOR  */
    TNOT = 278,                    /* TNOT  */
    TDIV = 279,                    /* TDIV  */
    TMOD = 280,                    /* TMOD  */
    TWRITE = 281,                  /* TWRITE  */
    TWRITELN = 282,                /* TWRITELN  */
    TREAD = 283,                   /* TREAD  */
    TASSIGN = 284,                 /* TASSIGN  */
    TNE = 285,                     /* TNE  */
    TLE = 286,                     /* TLE  */
    TGE = 287,                     /* TGE  */
    TLT = 288,                     /* TLT  */
    TGT = 289,                     /* TGT  */
    TEQ = 290,                     /* TEQ  */
    TCOLON = 291,                  /* TCOLON  */
    TSEMI = 292,                   /* TSEMI  */
    TDOT = 293,                    /* TDOT  */
    TCOMMA = 294,                  /* TCOMMA  */
    TLPAREN = 295,                 /* TLPAREN  */
    TRPAREN = 296,                 /* TRPAREN  */
    TPLUS = 297,                   /* TPLUS  */
    TMINUS = 298,                  /* TMINUS  */
    TMUL = 299,                    /* TMUL  */
    TINTLIT = 300,                 /* TINTLIT  */
    TIDENT = 301,                  /* TIDENT  */
    TSTRING = 302,                 /* TSTRING  */
    LOWER_THAN_ELSE = 303,         /* LOWER_THAN_ELSE  */
    UMINUS = 304                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 58 "src/parser.y"

    long long ival;
    char* sval;
    int type;
    mp::Expr* expr;
    mp::Statement* stmt;
    mp::CompoundStmt* block;
    mp::FunctionDecl* func;
    mp::Program* program;
    std::vector<mp::Statement*>* stmt_list;
    std::vector<mp::FunctionDecl*>* func_list;
    std::vector<mp::Expr*>* expr_list;
    std::vector<std::string>* name_list;
    std::vector<mp::Parameter>* param_list;

#line 129 "build/parser.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_BUILD_PARSER_TAB_HPP_INCLUDED  */
