# Tutorial completo passo a passo — Mini-Pascal Compiler

## 1. Objetivo
Construir um compilador de brinquedo para uma linguagem Mini-Pascal capaz de receber um arquivo `.pas` e produzir um executável nativo em Linux, usando Flex, Bison e LLVM.

## 2. Configuração do ambiente
Instalação recomendada em Debian/Ubuntu:

```bash
sudo apt update
sudo apt install -y flex bison llvm-dev llvm-runtime clang nasm lld
```

Verificação do ambiente:

```bash
gcc -v
flex --version
bison --version
nasm -v
clang --version
llvm-config --version
```

O resultado validado neste projeto está em `artifacts/toolchain_versions.txt`.

## 3. Estrutura do projeto
```text
include/
  ast.hpp
  codegen.hpp
src/
  lexer.l
  parser.y
  codegen.cpp
  main.cpp
  runtime.c
build/
  parser.output
  lexer.yy.cpp
  parser.tab.cpp
  parser.tab.hpp
tests/
  factor.pas
  isprime.pas
  fibonacci.pas
  pidigits.pas
  out/
docs/
  TUTORIAL_COMPLETO.md
  RELATORIO_FINAL.md
artifacts/
```

## 4. Análise léxica com Flex
O scanner está em `src/lexer.l`.

Ele reconhece:
- palavras-chave (`program`, `var`, `begin`, `end`, `if`, `while`, `for`, `function`, `procedure`, `write`, `writeln`)
- operadores (`+`, `-`, `*`, `div`, `mod`, `=`, `<>`, `<`, `<=`, `>`, `>=`)
- identificadores
- inteiros
- strings simples
- comentários (`#`, `//`, `{ ... }`, `(* ... *)`)

O Flex gera `build/lexer.yy.cpp`.

## 5. Gramática e ações semânticas com Bison
A gramática está em `src/parser.y`.

Ela constrói a AST durante o parsing e suporta:
- programa principal `program ... begin ... end.`
- declarações globais
- funções e procedimentos
- blocos compostos
- expressões aritméticas, relacionais e lógicas
- chamadas de função
- estruturas de controle

O Bison gera:
- `build/parser.tab.cpp`
- `build/parser.tab.hpp`
- `build/parser.output`

## 6. AST
A AST está definida em `include/ast.hpp`.

Principais nós:
- expressões literais (`IntegerExpr`, `BooleanExpr`, `StringExpr`)
- variáveis (`VariableExpr`)
- unárias e binárias
- chamada de função (`CallExpr`)
- comandos (`AssignStmt`, `IfStmt`, `WhileStmt`, `ForStmt`, `ReturnStmt`, `WriteStmt`)
- bloco composto (`CompoundStmt`)
- declaração de função (`FunctionDecl`)
- programa (`Program`)

## 7. Geração de LLVM IR
A geração de código está em `src/codegen.cpp`.

Fluxo principal:
1. declarar runtime (`mp_init_runtime`, `mp_argc`, `mp_argi`, `mp_write_*`)
2. declarar variáveis globais
3. declarar protótipos de funções
4. gerar corpo das funções
5. gerar `main`
6. emitir LLVM IR para arquivo `.ll`

Tipos utilizados:
- `integer` → `i64`
- `boolean` → `i1`
- `string` → `ptr` LLVM

## 8. Vinculação e geração do executável final
O driver em `src/main.cpp` faz o pipeline:

```text
Mini-Pascal (.pas)
  -> parser/AST
  -> LLVM IR (.ll)
  -> llc gera .s e .o
  -> clang vincula runtime.c
  -> executável nativo
```

## 9. Runtime
O arquivo `src/runtime.c` fornece:
- leitura de argumentos da linha de comando
- escrita de inteiros
- escrita de booleanos
- escrita de strings
- quebra de linha

Funções expostas ao código gerado:
- `mp_init_runtime`
- `mp_argc`
- `mp_argi`
- `mp_write_int`
- `mp_writeln_int`
- `mp_write_bool`
- `mp_writeln_bool`
- `mp_write_str`
- `mp_writeln`

## 10. Como compilar e executar os programas de teste
### factor
```bash
./build/minipascalc tests/factor.pas -o tests/out/factor
./tests/out/factor 84
```
Saída esperada aproximada:
```text
2 2 3 7
```

### isprime
```bash
./build/minipascalc tests/isprime.pas -o tests/out/isprime
./tests/out/isprime 97
./tests/out/isprime 91
```
Saídas esperadas:
```text
true
false
```

### fibonacci
```bash
./build/minipascalc tests/fibonacci.pas -o tests/out/fibonacci
./tests/out/fibonacci 10
```
Saída esperada:
```text
55
```

### pidigits
```bash
./build/minipascalc tests/pidigits.pas -o tests/out/pidigits
./tests/out/pidigits 6
```
Saída observada:
```text
3.141594
```

## 11. Problemas comuns e depuração
### Erro de parsing
- confira `;`, `begin/end` e `.` no fim do programa
- veja a linha informada pelo parser

### Símbolo não declarado
- a análise semântica verifica variáveis antes do uso
- declare a variável em `var`

### Erro de link
- confirme se `clang`, `llc` e `llvm-config` estão instalados
- em sistemas com PIE habilitado, o link usa `-no-pie`

### Saída inesperada em `pidigits`
- a implementação usa inteiros de 64 bits
- por segurança, o teste limita `n` a 9 casas decimais

## 12. Resultados gerados
Após rodar os testes, o projeto produz:
- executáveis em `tests/out/`
- LLVM IR em `tests/out/*.ll`
- assembly em `tests/out/*.s`
- objeto em `tests/out/*.o`
- logs em `artifacts/`

## 13. Limitações técnicas
- não há tipo `real`
- não há arrays
- não há escopo de parâmetros por referência
- `pidigits` usa aproximação inteira e não um algoritmo arbitrário de precisão
- a linguagem é um subconjunto de Pascal, não Pascal completo

## 14. Boas práticas adotadas
- projeto modular
- mensagens semânticas e sintáticas explícitas
- geração de IR separada da AST
- runtime pequeno e simples
- automação de testes com script

## 15. Entrega
Arquivos principais exigidos pela proposta estão incluídos:
- `lexer.l`
- `parser.y`
- driver e suporte em C/C++
- geração LLVM IR
- `Makefile`
- script Bash de testes
- programas de teste
- resultados e evidências
- documentação em Markdown
