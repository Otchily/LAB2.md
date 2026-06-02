#include "ast.hpp"
#include "codegen.hpp"

#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>

extern int yyparse();
extern FILE* yyin;
extern mp::Program* g_root;

namespace {

std::string shellQuote(const std::string& text) {
    std::string out = "'";
    for (char c : text) {
        if (c == '\'') out += "'\\''";
        else out += c;
    }
    out += "'";
    return out;
}

void runOrFail(const std::string& command) {
    int rc = std::system(command.c_str());
    if (rc != 0) {
        throw std::runtime_error("Falha ao executar comando externo do pipeline de compilacao.");
    }
}

}  // namespace

int main(int argc, char** argv) {
    try {
        if (argc < 2) {
            std::cerr << "Uso: minipascalc <arquivo.pas> [-o executavel]\n";
            return 1;
        }

        std::filesystem::path inputPath;
        std::filesystem::path outputExe;

        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "-o") {
                if (i + 1 >= argc) throw std::runtime_error("Faltou o nome do executavel apos -o");
                outputExe = argv[++i];
            } else {
                inputPath = arg;
            }
        }

        if (inputPath.empty()) throw std::runtime_error("Nenhum arquivo fonte informado.");
        if (outputExe.empty()) outputExe = inputPath.stem().string();

        yyin = std::fopen(inputPath.c_str(), "r");
        if (!yyin) throw std::runtime_error("Nao foi possivel abrir o arquivo fonte: " + inputPath.string());

        int parseResult = yyparse();
        std::fclose(yyin);
        if (parseResult != 0 || g_root == nullptr) throw std::runtime_error("Falha de parsing.");

        mp::CodeGenContext context(inputPath.stem().string());
        g_root->codegen(context);

        auto base = outputExe;
        auto llPath = base;
        llPath += ".ll";
        auto asmPath = base;
        asmPath += ".s";
        auto objPath = base;
        objPath += ".o";

        mp::generateIRFile(context, llPath.string());

        runOrFail("llc -filetype=asm -o " + shellQuote(asmPath.string()) + " " + shellQuote(llPath.string()));
        runOrFail("llc -filetype=obj -o " + shellQuote(objPath.string()) + " " + shellQuote(llPath.string()));
        runOrFail("clang -no-pie " + shellQuote(objPath.string()) + " " + shellQuote(std::string(RUNTIME_SOURCE)) + " -o " + shellQuote(outputExe.string()));

        std::cout << "OK\n";
        std::cout << "Executavel: " << outputExe << "\n";
        std::cout << "LLVM IR: " << llPath << "\n";
        std::cout << "ASM: " << asmPath << "\n";
        std::cout << "OBJ: " << objPath << "\n";
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "Erro: " << ex.what() << "\n";
        return 1;
    }
}
