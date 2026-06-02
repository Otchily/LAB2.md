#pragma once

#include "ast.hpp"

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

namespace mp {

struct VarInfo {
    llvm::Value* address;
    ValueType type;
    bool isGlobal;
};

class CodeGenContext {
  public:
    llvm::LLVMContext llvmContext;
    std::unique_ptr<llvm::Module> module;
    llvm::IRBuilder<> builder;

    explicit CodeGenContext(std::string moduleName);

    llvm::Type* llvmType(ValueType type);
    llvm::Constant* defaultValue(ValueType type);
    llvm::Value* castValue(const TypedValue& value, ValueType targetType, const std::string& what);
    llvm::Value* asCondition(const TypedValue& value, const std::string& what);

    void enterScope();
    void exitScope();

    VarInfo* lookupVariable(const std::string& name);
    VarInfo& declareLocal(const std::string& name, ValueType type);
    VarInfo& declareGlobal(const std::string& name, ValueType type);
    void bindLocal(const std::string& name, llvm::Value* address, ValueType type);

    void declareRuntime();
    llvm::Function* getFunction(const std::string& name);

    llvm::Function* currentFunction() const;
    ValueType currentReturnType() const;
    void pushFunction(llvm::Function* fn, ValueType returnType);
    void popFunction();

    llvm::AllocaInst* createEntryAlloca(llvm::Function* fn, const std::string& name, ValueType type);
    void emitPrint(const TypedValue& value, bool newlineAfterValue);
    void emitPrintNewline();

  private:
    struct FunctionFrame {
        llvm::Function* function;
        ValueType returnType;
    };

    std::vector<std::map<std::string, VarInfo>> scopes;
    std::vector<FunctionFrame> functionStack;
};

void generateObjectFile(CodeGenContext& ctx, const std::string& filename);
void generateAssemblyFile(CodeGenContext& ctx, const std::string& filename);
void generateIRFile(CodeGenContext& ctx, const std::string& filename);

}  // namespace mp
