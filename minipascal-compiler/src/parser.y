%{
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
%}

%define parse.error verbose

%union {
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
}

%token TPROGRAM TVAR TBEGIN TEND TIF TTHEN TELSE TWHILE TDO TFOR TTO TRETURN
%token TPROCEDURE TFUNCTION TINTEGER TBOOLEAN TTRUE TFALSE TAND TOR TNOT TDIV TMOD
%token TWRITE TWRITELN TREAD
%token TASSIGN TNE TLE TGE TLT TGT TEQ TCOLON TSEMI TDOT TCOMMA TLPAREN TRPAREN TPLUS TMINUS TMUL
%token <ival> TINTLIT
%token <sval> TIDENT TSTRING

%type <program> program
%type <stmt_list> global_vars_opt var_sections var_decl_list stmt_list stmt_list_opt local_vars_opt
%type <func_list> functions_opt
%type <func> function_decl procedure_decl
%type <block> compound_stmt
%type <stmt> statement assignment_stmt if_stmt while_stmt for_stmt return_stmt write_stmt expr_stmt
%type <expr> expr relation arith term unary factor function_call
%type <expr_list> expr_list_opt expr_list write_args_opt write_args
%type <name_list> ident_list
%type <param_list> params_opt param_list
%type <type> type_spec

%nonassoc LOWER_THAN_ELSE
%nonassoc TELSE
%left TOR
%left TAND
%right TNOT
%nonassoc TEQ TNE TLT TGT TLE TGE
%left TPLUS TMINUS
%left TMUL TDIV TMOD
%right UMINUS

%%

program
    : TPROGRAM TIDENT TSEMI global_vars_opt functions_opt compound_stmt TDOT {
          g_root = new Program(std::string($2), $4, $5, $6);
          free($2);
          $$ = g_root;
      }
    ;

global_vars_opt
    : /* empty */               { $$ = new std::vector<Statement*>(); }
    | var_sections              { $$ = $1; }
    ;

var_sections
    : TVAR var_decl_list                    { $$ = $2; }
    | var_sections TVAR var_decl_list       {
          for (auto* stmt : *$3) $1->push_back(stmt);
          delete $3;
          $$ = $1;
      }
    ;

var_decl_list
    : ident_list TCOLON type_spec TSEMI     { $$ = append_statement(nullptr, new VarDeclStmt($1, static_cast<ValueType>($3))); }
    | var_decl_list ident_list TCOLON type_spec TSEMI {
          $$ = append_statement($1, new VarDeclStmt($2, static_cast<ValueType>($4)));
      }
    ;

functions_opt
    : /* empty */               { $$ = new std::vector<FunctionDecl*>(); }
    | functions_opt function_decl  { $$ = append_function($1, $2); }
    | functions_opt procedure_decl { $$ = append_function($1, $2); }
    ;

function_decl
    : TFUNCTION TIDENT TLPAREN params_opt TRPAREN TCOLON type_spec TSEMI local_vars_opt compound_stmt TSEMI {
          $$ = new FunctionDecl(std::string($2), $4, static_cast<ValueType>($7), merge_compound($9, $10));
          free($2);
      }
    ;

procedure_decl
    : TPROCEDURE TIDENT TLPAREN params_opt TRPAREN TSEMI local_vars_opt compound_stmt TSEMI {
          $$ = new FunctionDecl(std::string($2), $4, ValueType::Void, merge_compound($7, $8));
          free($2);
      }
    ;

local_vars_opt
    : /* empty */               { $$ = new std::vector<Statement*>(); }
    | var_sections              { $$ = $1; }
    ;

params_opt
    : /* empty */               { $$ = new std::vector<Parameter>(); }
    | param_list                { $$ = $1; }
    ;

param_list
    : TIDENT TCOLON type_spec   { $$ = append_param(nullptr, $1, $3); }
    | param_list TCOMMA TIDENT TCOLON type_spec { $$ = append_param($1, $3, $5); }
    ;

type_spec
    : TINTEGER                  { $$ = static_cast<int>(ValueType::Integer); }
    | TBOOLEAN                  { $$ = static_cast<int>(ValueType::Boolean); }
    ;

compound_stmt
    : TBEGIN stmt_list_opt TEND { $$ = new CompoundStmt($2); }
    ;

stmt_list_opt
    : /* empty */               { $$ = new std::vector<Statement*>(); }
    | stmt_list                 { $$ = $1; }
    ;

stmt_list
    : statement                 { $$ = append_statement(nullptr, $1); }
    | stmt_list TSEMI statement { $$ = append_statement($1, $3); }
    ;

statement
    : assignment_stmt           { $$ = $1; }
    | if_stmt                   { $$ = $1; }
    | while_stmt                { $$ = $1; }
    | for_stmt                  { $$ = $1; }
    | return_stmt               { $$ = $1; }
    | write_stmt                { $$ = $1; }
    | expr_stmt                 { $$ = $1; }
    | compound_stmt             { $$ = $1; }
    ;

assignment_stmt
    : TIDENT TASSIGN expr       {
          $$ = new AssignStmt(std::string($1), $3);
          free($1);
      }
    ;

if_stmt
    : TIF expr TTHEN statement %prec LOWER_THAN_ELSE { $$ = new IfStmt($2, $4, nullptr); }
    | TIF expr TTHEN statement TELSE statement       { $$ = new IfStmt($2, $4, $6); }
    ;

while_stmt
    : TWHILE expr TDO statement { $$ = new WhileStmt($2, $4); }
    ;

for_stmt
    : TFOR TIDENT TASSIGN expr TTO expr TDO statement {
          $$ = new ForStmt(std::string($2), $4, $6, $8);
          free($2);
      }
    ;

return_stmt
    : TRETURN                    { $$ = new ReturnStmt(); }
    | TRETURN expr               { $$ = new ReturnStmt($2); }
    ;

write_stmt
    : TWRITE TLPAREN write_args_opt TRPAREN   { $$ = new WriteStmt(false, $3); }
    | TWRITELN TLPAREN write_args_opt TRPAREN { $$ = new WriteStmt(true, $3); }
    | TWRITELN                                 { $$ = new WriteStmt(true, new std::vector<Expr*>()); }
    ;

expr_stmt
    : function_call              { $$ = new ExprStmt($1); }
    ;

write_args_opt
    : /* empty */               { $$ = new std::vector<Expr*>(); }
    | write_args                { $$ = $1; }
    ;

write_args
    : expr                      { $$ = append_expr(nullptr, $1); }
    | TSTRING                   { $$ = append_expr(nullptr, new StringExpr(std::string($1))); free($1); }
    | write_args TCOMMA expr    { $$ = append_expr($1, $3); }
    | write_args TCOMMA TSTRING { $$ = append_expr($1, new StringExpr(std::string($3))); free($3); }
    ;

expr
    : expr TOR relation         { $$ = new BinaryExpr($1, "or", $3); }
    | expr TAND relation        { $$ = new BinaryExpr($1, "and", $3); }
    | relation                  { $$ = $1; }
    ;

relation
    : arith TEQ arith           { $$ = new BinaryExpr($1, "=", $3); }
    | arith TNE arith           { $$ = new BinaryExpr($1, "<>", $3); }
    | arith TLT arith           { $$ = new BinaryExpr($1, "<", $3); }
    | arith TLE arith           { $$ = new BinaryExpr($1, "<=", $3); }
    | arith TGT arith           { $$ = new BinaryExpr($1, ">", $3); }
    | arith TGE arith           { $$ = new BinaryExpr($1, ">=", $3); }
    | arith                     { $$ = $1; }
    ;

arith
    : arith TPLUS term          { $$ = new BinaryExpr($1, "+", $3); }
    | arith TMINUS term         { $$ = new BinaryExpr($1, "-", $3); }
    | term                      { $$ = $1; }
    ;

term
    : term TMUL unary           { $$ = new BinaryExpr($1, "*", $3); }
    | term TDIV unary           { $$ = new BinaryExpr($1, "div", $3); }
    | term TMOD unary           { $$ = new BinaryExpr($1, "mod", $3); }
    | unary                     { $$ = $1; }
    ;

unary
    : TMINUS unary %prec UMINUS { $$ = new UnaryExpr("-", $2); }
    | TPLUS unary               { $$ = $2; }
    | TNOT unary                { $$ = new UnaryExpr("not", $2); }
    | factor                    { $$ = $1; }
    ;

factor
    : TINTLIT                   { $$ = new IntegerExpr($1); }
    | TTRUE                     { $$ = new BooleanExpr(true); }
    | TFALSE                    { $$ = new BooleanExpr(false); }
    | TIDENT                    { $$ = new VariableExpr(std::string($1)); free($1); }
    | function_call             { $$ = $1; }
    | TLPAREN expr TRPAREN      { $$ = $2; }
    ;

function_call
    : TIDENT TLPAREN expr_list_opt TRPAREN {
          $$ = new CallExpr(std::string($1), $3);
          free($1);
      }
    ;

expr_list_opt
    : /* empty */               { $$ = new std::vector<Expr*>(); }
    | expr_list                 { $$ = $1; }
    ;

expr_list
    : expr                      { $$ = append_expr(nullptr, $1); }
    | expr_list TCOMMA expr     { $$ = append_expr($1, $3); }
    ;

ident_list
    : TIDENT                    { $$ = append_name(nullptr, $1); }
    | ident_list TCOMMA TIDENT  { $$ = append_name($1, $3); }
    ;

%%

void yyerror(const char* msg) {
    std::fprintf(stderr, "Syntax error at line %d: %s\n", yylineno, msg);
}
