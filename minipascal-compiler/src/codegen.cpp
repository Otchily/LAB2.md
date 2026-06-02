#include "codegen.hpp"

#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include <llvm/IR/Constants.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

namespace mp {

namespace {

[[noreturn]] void fail(const std::string& message) {
    throw std::runtime_error(message);
}

ValueType fromLlvmType(Type* type) {
    if (type->isVoidTy()) return ValueType::Void;
    if (type->isIntegerTy(1)) return ValueType::Boolean;
    if (type->isIntegerTy(64)) return ValueType::Integer;
    return ValueType::String;
}

std::string quote(const std::string& text) {
    std::string out = "'";
    for (char c : text) {
        if (c == '\'') out += "'\\''";
        else out += c;
    }
    out += "'";
    return out;
}

}  // namespace

CodeGenContext::CodeGenContext(std::string moduleName)
    : module(std::make_unique<Module>(moduleName, llvmContext)), builder(llvmContext) {
    enterScope();
}

Type* CodeGenContext::llvmType(ValueType type) {
    switch (type) {
        case ValueType::Integer:
            return Type::getInt64Ty(llvmContext);
        case ValueType::Boolean:
            return Type::getInt1Ty(llvmContext);
        case ValueType::Void:
            return Type::getVoidTy(llvmContext);
        case ValueType::String:
            return PointerType::getUnqual(llvmContext);
    }
    fail("Unknown type");
}

Constant* CodeGenContext::defaultValue(ValueType type) {
    switch (type) {
        case ValueType::Integer:
            return ConstantInt::get(llvmType(ValueType::Integer), 0, true);
        case ValueType::Boolean:
            return ConstantInt::getFalse(llvmContext);
        case ValueType::Void:
            return nullptr;
        case ValueType::String:
            return ConstantPointerNull::get(cast<PointerType>(llvmType(ValueType::String)));
    }
    fail("Unknown type");
}

Value* CodeGenContext::castValue(const TypedValue& value, ValueType targetType, const std::string& what) {
    if (value.type == targetType) return value.value;

    if (value.type == ValueType::Integer && targetType == ValueType::Boolean) {
        return builder.CreateICmpNE(value.value, ConstantInt::get(llvmType(ValueType::Integer), 0), what + ".tobool");
    }
    if (value.type == ValueType::Boolean && targetType == ValueType::Integer) {
        return builder.CreateZExt(value.value, llvmType(ValueType::Integer), what + ".toint");
    }

    fail("Type error: cannot convert value in " + what);
}

Value* CodeGenContext::asCondition(const TypedValue& value, const std::string& what) {
    return castValue(value, ValueType::Boolean, what);
}

void CodeGenContext::enterScope() {
    scopes.emplace_back();
}

void CodeGenContext::exitScope() {
    if (scopes.empty()) fail("Internal error: scope underflow");
    scopes.pop_back();
}

VarInfo* CodeGenContext::lookupVariable(const std::string& name) {
    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
        auto found = it->find(name);
        if (found != it->end()) return &found->second;
    }
    return nullptr;
}

AllocaInst* CodeGenContext::createEntryAlloca(Function* fn, const std::string& name, ValueType type) {
    IRBuilder<> tempBuilder(&fn->getEntryBlock(), fn->getEntryBlock().begin());
    return tempBuilder.CreateAlloca(llvmType(type), nullptr, name);
}

VarInfo& CodeGenContext::declareLocal(const std::string& name, ValueType type) {
    if (scopes.empty()) fail("Internal error: no active scope");
    auto& scope = scopes.back();
    if (scope.count(name)) fail("Semantic error: variable already declared: " + name);
    Function* fn = currentFunction();
    if (!fn) fail("Internal error: local declaration outside function");
    auto* alloca = createEntryAlloca(fn, name, type);
    if (auto* init = defaultValue(type)) {
        builder.CreateStore(init, alloca);
    }
    auto [it, inserted] = scope.emplace(name, VarInfo{alloca, type, false});
    (void)inserted;
    return it->second;
}

VarInfo& CodeGenContext::declareGlobal(const std::string& name, ValueType type) {
    auto& scope = scopes.front();
    if (scope.count(name)) fail("Semantic error: global already declared: " + name);
    auto* gv = new GlobalVariable(*module,
                                  llvmType(type),
                                  false,
                                  GlobalValue::ExternalLinkage,
                                  defaultValue(type),
                                  name);
    auto [it, inserted] = scope.emplace(name, VarInfo{gv, type, true});
    (void)inserted;
    return it->second;
}

void CodeGenContext::bindLocal(const std::string& name, llvm::Value* address, ValueType type) {
    if (scopes.empty()) fail("Internal error: no active scope");
    auto& scope = scopes.back();
    if (scope.count(name)) fail("Semantic error: duplicate symbol: " + name);
    scope.emplace(name, VarInfo{address, type, false});
}

void CodeGenContext::declareRuntime() {
    auto* voidTy = llvmType(ValueType::Void);
    auto* intTy = llvmType(ValueType::Integer);
    auto* boolTy = llvmType(ValueType::Boolean);
    auto* ptrTy = llvmType(ValueType::String);

    module->getOrInsertFunction("mp_init_runtime", FunctionType::get(voidTy, {intTy, ptrTy}, false));
    module->getOrInsertFunction("mp_argc", FunctionType::get(intTy, {}, false));
    module->getOrInsertFunction("mp_argi", FunctionType::get(intTy, {intTy}, false));
    module->getOrInsertFunction("mp_write_int", FunctionType::get(voidTy, {intTy}, false));
    module->getOrInsertFunction("mp_writeln_int", FunctionType::get(voidTy, {intTy}, false));
    module->getOrInsertFunction("mp_write_bool", FunctionType::get(voidTy, {boolTy}, false));
    module->getOrInsertFunction("mp_writeln_bool", FunctionType::get(voidTy, {boolTy}, false));
    module->getOrInsertFunction("mp_write_str", FunctionType::get(voidTy, {ptrTy}, false));
    module->getOrInsertFunction("mp_writeln", FunctionType::get(voidTy, {}, false));
}

Function* CodeGenContext::getFunction(const std::string& name) {
    return module->getFunction(name);
}

Function* CodeGenContext::currentFunction() const {
    if (functionStack.empty()) return nullptr;
    return functionStack.back().function;
}

ValueType CodeGenContext::currentReturnType() const {
    if (functionStack.empty()) return ValueType::Integer;
    return functionStack.back().returnType;
}

void CodeGenContext::pushFunction(Function* fn, ValueType returnType) {
    functionStack.push_back(FunctionFrame{fn, returnType});
}

void CodeGenContext::popFunction() {
    if (functionStack.empty()) fail("Internal error: function stack underflow");
    functionStack.pop_back();
}

void CodeGenContext::emitPrint(const TypedValue& value, bool newlineAfterValue) {
    switch (value.type) {
        case ValueType::Integer:
            builder.CreateCall(getFunction(newlineAfterValue ? "mp_writeln_int" : "mp_write_int"),
                               {castValue(value, ValueType::Integer, "print-int")});
            break;
        case ValueType::Boolean:
            builder.CreateCall(getFunction(newlineAfterValue ? "mp_writeln_bool" : "mp_write_bool"),
                               {castValue(value, ValueType::Boolean, "print-bool")});
            break;
        case ValueType::String:
            if (newlineAfterValue) {
                builder.CreateCall(getFunction("mp_write_str"), {value.value});
                builder.CreateCall(getFunction("mp_writeln"), {});
            } else {
                builder.CreateCall(getFunction("mp_write_str"), {value.value});
            }
            break;
        case ValueType::Void:
            fail("Cannot print a void value");
    }
}

void CodeGenContext::emitPrintNewline() {
    builder.CreateCall(getFunction("mp_writeln"), {});
}

TypedValue IntegerExpr::codegen(CodeGenContext& ctx) {
    return TypedValue{ConstantInt::get(ctx.llvmType(ValueType::Integer), value, true), ValueType::Integer};
}

TypedValue BooleanExpr::codegen(CodeGenContext& ctx) {
    return TypedValue{value ? ConstantInt::getTrue(ctx.llvmContext) : ConstantInt::getFalse(ctx.llvmContext), ValueType::Boolean};
}

TypedValue StringExpr::codegen(CodeGenContext& ctx) {
    return TypedValue{ctx.builder.CreateGlobalStringPtr(value), ValueType::String};
}

TypedValue VariableExpr::codegen(CodeGenContext& ctx) {
    auto* var = ctx.lookupVariable(name);
    if (!var) fail("Semantic error: undeclared variable " + name);
    auto* loaded = ctx.builder.CreateLoad(ctx.llvmType(var->type), var->address, name + ".val");
    return TypedValue{loaded, var->type};
}

TypedValue UnaryExpr::codegen(CodeGenContext& ctx) {
    auto rhs = expr->codegen(ctx);
    if (op == "-") {
        auto* value = ctx.castValue(rhs, ValueType::Integer, "unary-minus");
        return TypedValue{ctx.builder.CreateNeg(value, "negtmp"), ValueType::Integer};
    }
    if (op == "not") {
        auto* value = ctx.castValue(rhs, ValueType::Boolean, "not");
        return TypedValue{ctx.builder.CreateNot(value, "nottmp"), ValueType::Boolean};
    }
    fail("Unsupported unary operator: " + op);
}

TypedValue BinaryExpr::codegen(CodeGenContext& ctx) {
    auto left = lhs->codegen(ctx);
    auto right = rhs->codegen(ctx);

    if (op == "+" || op == "-" || op == "*" || op == "div" || op == "mod") {
        auto* l = ctx.castValue(left, ValueType::Integer, "arith-left");
        auto* r = ctx.castValue(right, ValueType::Integer, "arith-right");
        if (op == "+") return TypedValue{ctx.builder.CreateAdd(l, r, "addtmp"), ValueType::Integer};
        if (op == "-") return TypedValue{ctx.builder.CreateSub(l, r, "subtmp"), ValueType::Integer};
        if (op == "*") return TypedValue{ctx.builder.CreateMul(l, r, "multmp"), ValueType::Integer};
        if (op == "div") return TypedValue{ctx.builder.CreateSDiv(l, r, "divtmp"), ValueType::Integer};
        return TypedValue{ctx.builder.CreateSRem(l, r, "modtmp"), ValueType::Integer};
    }

    if (op == "and" || op == "or") {
        auto* l = ctx.castValue(left, ValueType::Boolean, "logic-left");
        auto* r = ctx.castValue(right, ValueType::Boolean, "logic-right");
        if (op == "and") return TypedValue{ctx.builder.CreateAnd(l, r, "andtmp"), ValueType::Boolean};
        return TypedValue{ctx.builder.CreateOr(l, r, "ortmp"), ValueType::Boolean};
    }

    if (left.type != right.type) {
        if ((left.type == ValueType::Integer && right.type == ValueType::Boolean) ||
            (left.type == ValueType::Boolean && right.type == ValueType::Integer)) {
            left.value = ctx.castValue(left, ValueType::Integer, "compare-left");
            left.type = ValueType::Integer;
            right.value = ctx.castValue(right, ValueType::Integer, "compare-right");
            right.type = ValueType::Integer;
        } else {
            fail("Type error: incompatible operands for operator " + op);
        }
    }

    if (left.type == ValueType::Integer) {
        auto* l = ctx.castValue(left, ValueType::Integer, "cmp-left");
        auto* r = ctx.castValue(right, ValueType::Integer, "cmp-right");
        if (op == "=") return TypedValue{ctx.builder.CreateICmpEQ(l, r, "eqtmp"), ValueType::Boolean};
        if (op == "<>") return TypedValue{ctx.builder.CreateICmpNE(l, r, "netmp"), ValueType::Boolean};
        if (op == "<") return TypedValue{ctx.builder.CreateICmpSLT(l, r, "lttmp"), ValueType::Boolean};
        if (op == "<=") return TypedValue{ctx.builder.CreateICmpSLE(l, r, "letmp"), ValueType::Boolean};
        if (op == ">") return TypedValue{ctx.builder.CreateICmpSGT(l, r, "gttmp"), ValueType::Boolean};
        if (op == ">=") return TypedValue{ctx.builder.CreateICmpSGE(l, r, "getmp"), ValueType::Boolean};
    }

    if (left.type == ValueType::Boolean) {
        auto* l = ctx.castValue(left, ValueType::Boolean, "cmp-left-bool");
        auto* r = ctx.castValue(right, ValueType::Boolean, "cmp-right-bool");
        if (op == "=") return TypedValue{ctx.builder.CreateICmpEQ(l, r, "eqbool"), ValueType::Boolean};
        if (op == "<>") return TypedValue{ctx.builder.CreateICmpNE(l, r, "nebool"), ValueType::Boolean};
    }

    fail("Unsupported operator: " + op);
}

TypedValue CallExpr::codegen(CodeGenContext& ctx) {
    if (callee == "argc") {
        if (!args.empty()) fail("argc expects no arguments");
        return TypedValue{ctx.builder.CreateCall(ctx.getFunction("mp_argc"), {}), ValueType::Integer};
    }
    if (callee == "argi") {
        if (args.size() != 1) fail("argi expects one integer argument");
        auto arg = args[0]->codegen(ctx);
        return TypedValue{ctx.builder.CreateCall(ctx.getFunction("mp_argi"),
                                                 {ctx.castValue(arg, ValueType::Integer, "argi")}),
                          ValueType::Integer};
    }

    Function* fn = ctx.getFunction(callee);
    if (!fn) fail("Semantic error: unknown function " + callee);
    if (fn->arg_size() != args.size()) fail("Semantic error: wrong number of arguments in call to " + callee);

    std::vector<Value*> values;
    values.reserve(args.size());

    auto it = fn->arg_begin();
    for (std::size_t i = 0; i < args.size(); ++i, ++it) {
        auto value = args[i]->codegen(ctx);
        ValueType target = fromLlvmType(it->getType());
        values.push_back(ctx.castValue(value, target, "call-arg"));
    }

    auto* result = ctx.builder.CreateCall(fn, values, fn->getReturnType()->isVoidTy() ? "" : callee + ".ret");
    return TypedValue{result, fromLlvmType(fn->getReturnType())};
}

void CompoundStmt::codegen(CodeGenContext& ctx) {
    for (auto& stmt : statements) {
        if (ctx.builder.GetInsertBlock()->getTerminator()) break;
        stmt->codegen(ctx);
    }
}

void VarDeclStmt::codegen(CodeGenContext& ctx) {
    for (const auto& name : names) {
        if (ctx.currentFunction()) ctx.declareLocal(name, type);
        else ctx.declareGlobal(name, type);
    }
}

void AssignStmt::codegen(CodeGenContext& ctx) {
    auto* var = ctx.lookupVariable(name);
    if (!var) fail("Semantic error: assignment to undeclared variable " + name);
    auto value = expr->codegen(ctx);
    ctx.builder.CreateStore(ctx.castValue(value, var->type, "assign"), var->address);
}

void ExprStmt::codegen(CodeGenContext& ctx) {
    expr->codegen(ctx);
}

void IfStmt::codegen(CodeGenContext& ctx) {
    auto cond = condition->codegen(ctx);
    auto* condValue = ctx.asCondition(cond, "if");

    Function* fn = ctx.currentFunction();
    auto* thenBB = BasicBlock::Create(ctx.llvmContext, "then", fn);
    auto* elseBB = elseBranch ? BasicBlock::Create(ctx.llvmContext, "else", fn)
                              : BasicBlock::Create(ctx.llvmContext, "else");
    auto* mergeBB = BasicBlock::Create(ctx.llvmContext, "ifend", fn);

    if (elseBranch) ctx.builder.CreateCondBr(condValue, thenBB, elseBB);
    else ctx.builder.CreateCondBr(condValue, thenBB, mergeBB);

    ctx.builder.SetInsertPoint(thenBB);
    ctx.enterScope();
    thenBranch->codegen(ctx);
    ctx.exitScope();
    if (!ctx.builder.GetInsertBlock()->getTerminator()) ctx.builder.CreateBr(mergeBB);

    if (elseBranch) {
        ctx.builder.SetInsertPoint(elseBB);
        ctx.enterScope();
        elseBranch->codegen(ctx);
        ctx.exitScope();
        if (!ctx.builder.GetInsertBlock()->getTerminator()) ctx.builder.CreateBr(mergeBB);
    }

    ctx.builder.SetInsertPoint(mergeBB);
}

void WhileStmt::codegen(CodeGenContext& ctx) {
    Function* fn = ctx.currentFunction();
    auto* condBB = BasicBlock::Create(ctx.llvmContext, "while.cond", fn);
    auto* bodyBB = BasicBlock::Create(ctx.llvmContext, "while.body", fn);
    auto* endBB = BasicBlock::Create(ctx.llvmContext, "while.end", fn);

    ctx.builder.CreateBr(condBB);

    ctx.builder.SetInsertPoint(condBB);
    auto cond = condition->codegen(ctx);
    ctx.builder.CreateCondBr(ctx.asCondition(cond, "while"), bodyBB, endBB);

    ctx.builder.SetInsertPoint(bodyBB);
    ctx.enterScope();
    body->codegen(ctx);
    ctx.exitScope();
    if (!ctx.builder.GetInsertBlock()->getTerminator()) ctx.builder.CreateBr(condBB);

    ctx.builder.SetInsertPoint(endBB);
}

void ForStmt::codegen(CodeGenContext& ctx) {
    auto* var = ctx.lookupVariable(varName);
    if (!var) fail("Semantic error: for loop variable not declared: " + varName);
    if (var->type != ValueType::Integer) fail("Semantic error: for loop variable must be integer: " + varName);

    auto startValue = start->codegen(ctx);
    auto finishValue = finish->codegen(ctx);

    ctx.builder.CreateStore(ctx.castValue(startValue, ValueType::Integer, "for-start"), var->address);

    auto* fn = ctx.currentFunction();
    auto* limitAlloca = ctx.createEntryAlloca(fn, varName + ".limit", ValueType::Integer);
    ctx.builder.CreateStore(ctx.castValue(finishValue, ValueType::Integer, "for-limit"), limitAlloca);

    auto* condBB = BasicBlock::Create(ctx.llvmContext, "for.cond", fn);
    auto* bodyBB = BasicBlock::Create(ctx.llvmContext, "for.body", fn);
    auto* stepBB = BasicBlock::Create(ctx.llvmContext, "for.step", fn);
    auto* endBB = BasicBlock::Create(ctx.llvmContext, "for.end", fn);

    ctx.builder.CreateBr(condBB);

    ctx.builder.SetInsertPoint(condBB);
    auto* current = ctx.builder.CreateLoad(ctx.llvmType(ValueType::Integer), var->address, varName + ".cur");
    auto* limit = ctx.builder.CreateLoad(ctx.llvmType(ValueType::Integer), limitAlloca, varName + ".limitv");
    auto* cond = ctx.builder.CreateICmpSLE(current, limit, "forcond");
    ctx.builder.CreateCondBr(cond, bodyBB, endBB);

    ctx.builder.SetInsertPoint(bodyBB);
    ctx.enterScope();
    body->codegen(ctx);
    ctx.exitScope();
    if (!ctx.builder.GetInsertBlock()->getTerminator()) ctx.builder.CreateBr(stepBB);

    ctx.builder.SetInsertPoint(stepBB);
    auto* loaded = ctx.builder.CreateLoad(ctx.llvmType(ValueType::Integer), var->address, varName + ".stepv");
    auto* next = ctx.builder.CreateAdd(loaded, ConstantInt::get(ctx.llvmType(ValueType::Integer), 1), "fornext");
    ctx.builder.CreateStore(next, var->address);
    ctx.builder.CreateBr(condBB);

    ctx.builder.SetInsertPoint(endBB);
}

void ReturnStmt::codegen(CodeGenContext& ctx) {
    auto expected = ctx.currentReturnType();
    if (expected == ValueType::Void) {
        if (expr) fail("Semantic error: procedure cannot return a value");
        ctx.builder.CreateRetVoid();
        return;
    }

    if (!expr) fail("Semantic error: non-void function must return a value");
    auto value = expr->codegen(ctx);
    ctx.builder.CreateRet(ctx.castValue(value, expected, "return"));
}

void WriteStmt::codegen(CodeGenContext& ctx) {
    for (auto& arg : args) {
        auto value = arg->codegen(ctx);
        ctx.emitPrint(value, false);
    }
    if (newline) ctx.emitPrintNewline();
}

Function* FunctionDecl::declare(CodeGenContext& ctx) {
    if (ctx.getFunction(name)) return ctx.getFunction(name);

    std::vector<Type*> argTypes;
    argTypes.reserve(params.size());
    for (const auto& param : params) {
        argTypes.push_back(ctx.llvmType(param.type));
    }

    auto* ft = FunctionType::get(ctx.llvmType(returnType), argTypes, false);
    auto* fn = Function::Create(ft, Function::ExternalLinkage, name, ctx.module.get());

    std::size_t index = 0;
    for (auto& arg : fn->args()) {
        arg.setName(params[index++].name);
    }
    return fn;
}

void FunctionDecl::codegen(CodeGenContext& ctx) {
    auto* fn = declare(ctx);
    if (!fn->empty()) fail("Semantic error: duplicate function definition " + name);

    auto* entry = BasicBlock::Create(ctx.llvmContext, name + ".entry", fn);
    ctx.builder.SetInsertPoint(entry);
    ctx.pushFunction(fn, returnType);
    ctx.enterScope();

    for (auto& arg : fn->args()) {
        auto paramType = fromLlvmType(arg.getType());
        auto* alloca = ctx.createEntryAlloca(fn, std::string(arg.getName()), paramType);
        ctx.builder.CreateStore(&arg, alloca);
        ctx.bindLocal(std::string(arg.getName()), alloca, paramType);
    }

    body->codegen(ctx);

    if (!ctx.builder.GetInsertBlock()->getTerminator()) {
        if (returnType == ValueType::Void) ctx.builder.CreateRetVoid();
        else ctx.builder.CreateRet(ctx.defaultValue(returnType));
    }

    verifyFunction(*fn);
    ctx.exitScope();
    ctx.popFunction();
}

void Program::codegen(CodeGenContext& ctx) {
    ctx.declareRuntime();

    for (auto& global : globals) global->codegen(ctx);
    for (auto& fn : functions) fn->declare(ctx);
    for (auto& fn : functions) fn->codegen(ctx);

    auto* int32Ty = Type::getInt32Ty(ctx.llvmContext);
    auto* ptrTy = ctx.llvmType(ValueType::String);
    auto* mainType = FunctionType::get(int32Ty, {int32Ty, ptrTy}, false);
    auto* mainFn = Function::Create(mainType, Function::ExternalLinkage, "main", ctx.module.get());

    auto argIt = mainFn->arg_begin();
    argIt->setName("argc");
    (++argIt)->setName("argv");

    auto* entry = BasicBlock::Create(ctx.llvmContext, "entry", mainFn);
    ctx.builder.SetInsertPoint(entry);
    ctx.pushFunction(mainFn, ValueType::Integer);
    ctx.enterScope();

    auto argBegin = mainFn->arg_begin();
    auto* argc64 = ctx.builder.CreateSExt(&*argBegin, ctx.llvmType(ValueType::Integer), "argc64");
    auto* argvPtr = &*(++argBegin);
    ctx.builder.CreateCall(ctx.getFunction("mp_init_runtime"), {argc64, argvPtr});

    mainBlock->codegen(ctx);

    if (!ctx.builder.GetInsertBlock()->getTerminator()) {
        ctx.builder.CreateRet(ConstantInt::get(int32Ty, 0));
    }

    verifyFunction(*mainFn);
    verifyModule(*ctx.module, &errs());
    ctx.exitScope();
    ctx.popFunction();
}

void generateIRFile(CodeGenContext& ctx, const std::string& filename) {
    std::error_code ec;
    raw_fd_ostream out(filename, ec, sys::fs::OF_None);
    if (ec) fail("Unable to open IR output file: " + filename);
    ctx.module->print(out, nullptr);
}

void generateObjectFile(CodeGenContext&, const std::string&) {
    fail("generateObjectFile is not used by this project driver");
}

void generateAssemblyFile(CodeGenContext&, const std::string&) {
    fail("generateAssemblyFile is not used by this project driver");
}

}  // namespace mp
