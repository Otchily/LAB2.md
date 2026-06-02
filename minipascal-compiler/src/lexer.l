%{
#include "ast.hpp"
#include "parser.tab.hpp"

#include <string>
#include <cstring>

#define SAVE_TOKEN    yylval.sval = strdup(yytext)
%}

%option noyywrap
%option nounput
%option noinput
%option yylineno
%option caseless

DIGIT       [0-9]
ALPHA       [a-zA-Z_]
ALNUM       [a-zA-Z0-9_]
WS          [ \t\r\n]+

%%

{WS}                    ;   /* ignore whitespace */

"{"[^}]*"}"             ;   /* Block comment { ... } */
"(*"([^*]|\*[^)])*"*)"  ;   /* Block comment (* ... *) */
"//"[^\n]*              ;   /* Line comment // ... */
"#"[^\n]*               ;   /* Line comment # ... */

"program"               { return TPROGRAM;     }
"var"                   { return TVAR;         }
"begin"                 { return TBEGIN;       }
"end"                   { return TEND;         }
"if"                    { return TIF;          }
"then"                  { return TTHEN;        }
"else"                  { return TELSE;        }
"while"                 { return TWHILE;       }
"do"                    { return TDO;          }
"for"                   { return TFOR;         }
"to"                    { return TTO;          }
"return"                { return TRETURN;      }
"procedure"             { return TPROCEDURE;   }
"function"              { return TFUNCTION;    }
"integer"               { return TINTEGER;     }
"boolean"               { return TBOOLEAN;     }
"true"                  { return TTRUE;        }
"false"                 { return TFALSE;       }
"and"                   { return TAND;         }
"or"                    { return TOR;          }
"not"                   { return TNOT;         }
"div"                   { return TDIV;         }
"mod"                   { return TMOD;         }
"write"                 { return TWRITE;       }
"writeln"               { return TWRITELN;     }
"read"                  { return TREAD;        }

":="                    { return TASSIGN;      }
"<>"                    { return TNE;          }
"<="                    { return TLE;          }
">="                    { return TGE;          }
"<"                     { return TLT;          }
">"                     { return TGT;          }
"="                     { return TEQ;          }
":"                     { return TCOLON;       }
";"                     { return TSEMI;        }
"."                     { return TDOT;         }
","                     { return TCOMMA;       }
"("                     { return TLPAREN;      }
")"                     { return TRPAREN;      }
"+"                     { return TPLUS;        }
"-"                     { return TMINUS;       }
"*"                     { return TMUL;         }

\'([^\\'\n]|\\.)*\'     { yylval.sval = strdup(yytext+1); yylval.sval[yyleng-2] = '\0'; return TSTRING; }

{DIGIT}+                { yylval.ival = atoll(yytext); return TINTLIT; }

{ALPHA}{ALNUM}*         { SAVE_TOKEN; return TIDENT; }

.                       {
                            fprintf(stderr, "Lexical error: unexpected character '%s' at line %d\n", yytext, yylineno);
                        }

%%
