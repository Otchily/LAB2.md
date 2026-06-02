#pragma once

#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace llvm {
class Value;
class Function;
}

namespace mp {

class CodeGenContext;

enum class ValueType {
    Integer,
    Boolean,
    Void,
    String
};

struct TypedValue {
    llvm::Value* value;
    ValueType type;
};

struct Parameter {
    std::string name;
    ValueType type;

    Parameter(std::string n, ValueType t) : name(std::move(n)), type(t) {}
};

class Expr {
  public:
    virtual ~Expr() = default;
    virtual TypedValue codegen(CodeGenContext& ctx) = 0;
};

class Statement {
  public:
    virtual ~Statement() = default;
    virtual void codegen(CodeGenContext& ctx) = 0;
};

class IntegerExpr : public Expr {
  public:
    long long value;
    explicit IntegerExpr(long long v) : value(v) {}
    TypedValue codegen(CodeGenContext& ctx) override;
};

class BooleanExpr : public Expr {
  public:
    bool value;
    explicit BooleanExpr(bool v) : value(v) {}
    TypedValue codegen(CodeGenContext& ctx) override;
};

class StringExpr : public Expr {
  public:
    std::string value;
    explicit StringExpr(std::string v) : value(std::move(v)) {}
    TypedValue codegen(CodeGenContext& ctx) override;
};

class VariableExpr : public Expr {
  public:
    std::string name;
    explicit VariableExpr(std::string n) : name(std::move(n)) {}
    TypedValue codegen(CodeGenContext& ctx) override;
};

class UnaryExpr : public Expr {
  public:
    std::string op;
    std::unique_ptr<Expr> expr;

    UnaryExpr(std::string oper, Expr* rhs) : op(std::move(oper)), expr(rhs) {}
    TypedValue codegen(CodeGenContext& ctx) override;
};

class BinaryExpr : public Expr {
  public:
    std::string op;
    std::unique_ptr<Expr> lhs;
    std::unique_ptr<Expr> rhs;

    BinaryExpr(Expr* left, std::string oper, Expr* right)
        : op(std::move(oper)), lhs(left), rhs(right) {}
    TypedValue codegen(CodeGenContext& ctx) override;
};

class CallExpr : public Expr {
  public:
    std::string callee;
    std::vector<std::unique_ptr<Expr>> args;

    CallExpr(std::string name, std::vector<Expr*>* rawArgs) : callee(std::move(name)) {
        if (rawArgs) {
            for (auto* arg : *rawArgs) {
                args.emplace_back(arg);
            }
            delete rawArgs;
        }
    }
    TypedValue codegen(CodeGenContext& ctx) override;
};

class CompoundStmt : public Statement {
  public:
    std::vector<std::unique_ptr<Statement>> statements;

    CompoundStmt() = default;
    explicit CompoundStmt(std::vector<Statement*>* rawStatements) {
        if (rawStatements) {
            for (auto* stmt : *rawStatements) {
                statements.emplace_back(stmt);
            }
            delete rawStatements;
        }
    }

    void prepend(std::vector<Statement*>* rawStatements) {
        if (!rawStatements || rawStatements->empty()) {
            delete rawStatements;
            return;
        }
        std::vector<std::unique_ptr<Statement>> merged;
        merged.reserve(rawStatements->size() + statements.size());
        for (auto* stmt : *rawStatements) {
            merged.emplace_back(stmt);
        }
        for (auto& stmt : statements) {
            merged.emplace_back(std::move(stmt));
        }
        statements = std::move(merged);
        delete rawStatements;
    }

    void codegen(CodeGenContext& ctx) override;
};

class VarDeclStmt : public Statement {
  public:
    std::vector<std::string> names;
    ValueType type;

    VarDeclStmt(std::vector<std::string>* rawNames, ValueType t) : type(t) {
        if (rawNames) {
            names = *rawNames;
            delete rawNames;
        }
    }
    void codegen(CodeGenContext& ctx) override;
};

class AssignStmt : public Statement {
  public:
    std::string name;
    std::unique_ptr<Expr> expr;

    AssignStmt(std::string n, Expr* e) : name(std::move(n)), expr(e) {}
    void codegen(CodeGenContext& ctx) override;
};

class ExprStmt : public Statement {
  public:
    std::unique_ptr<Expr> expr;
    explicit ExprStmt(Expr* e) : expr(e) {}
    void codegen(CodeGenContext& ctx) override;
};

class IfStmt : public Statement {
  public:
    std::unique_ptr<Expr> condition;
    std::unique_ptr<Statement> thenBranch;
    std::unique_ptr<Statement> elseBranch;

    IfStmt(Expr* cond, Statement* thenStmt, Statement* elseStmt = nullptr)
        : condition(cond), thenBranch(thenStmt), elseBranch(elseStmt) {}
    void codegen(CodeGenContext& ctx) override;
};

class WhileStmt : public Statement {
  public:
    std::unique_ptr<Expr> condition;
    std::unique_ptr<Statement> body;

    WhileStmt(Expr* cond, Statement* loopBody) : condition(cond), body(loopBody) {}
    void codegen(CodeGenContext& ctx) override;
};

class ForStmt : public Statement {
  public:
    std::string varName;
    std::unique_ptr<Expr> start;
    std::unique_ptr<Expr> finish;
    std::unique_ptr<Statement> body;

    ForStmt(std::string n, Expr* s, Expr* f, Statement* b)
        : varName(std::move(n)), start(s), finish(f), body(b) {}
    void codegen(CodeGenContext& ctx) override;
};

class ReturnStmt : public Statement {
  public:
    std::unique_ptr<Expr> expr;

    explicit ReturnStmt(Expr* e = nullptr) : expr(e) {}
    void codegen(CodeGenContext& ctx) override;
};

class WriteStmt : public Statement {
  public:
    bool newline;
    std::vector<std::unique_ptr<Expr>> args;

    WriteStmt(bool nl, std::vector<Expr*>* rawArgs) : newline(nl) {
        if (rawArgs) {
            for (auto* arg : *rawArgs) {
                args.emplace_back(arg);
            }
            delete rawArgs;
        }
    }
    void codegen(CodeGenContext& ctx) override;
};

class FunctionDecl {
  public:
    std::string name;
    std::vector<Parameter> params;
    ValueType returnType;
    std::unique_ptr<CompoundStmt> body;

    FunctionDecl(std::string n, std::vector<Parameter>* rawParams, ValueType ret, CompoundStmt* b)
        : name(std::move(n)), returnType(ret), body(b) {
        if (rawParams) {
            params = *rawParams;
            delete rawParams;
        }
    }

    llvm::Function* declare(CodeGenContext& ctx);
    void codegen(CodeGenContext& ctx);
};

class Program {
  public:
    std::string name;
    std::vector<std::unique_ptr<Statement>> globals;
    std::vector<std::unique_ptr<FunctionDecl>> functions;
    std::unique_ptr<CompoundStmt> mainBlock;

    Program(std::string n,
            std::vector<Statement*>* rawGlobals,
            std::vector<FunctionDecl*>* rawFunctions,
            CompoundStmt* mainBody)
        : name(std::move(n)), mainBlock(mainBody) {
        if (rawGlobals) {
            for (auto* stmt : *rawGlobals) {
                globals.emplace_back(stmt);
            }
            delete rawGlobals;
        }
        if (rawFunctions) {
            for (auto* fn : *rawFunctions) {
                functions.emplace_back(fn);
            }
            delete rawFunctions;
        }
    }

    void codegen(CodeGenContext& ctx);
};

}  // namespace mp
