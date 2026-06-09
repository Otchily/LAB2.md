# Mini-Pascal Toy Compiler com Flex, Bison e LLVM

## Equipe
- Cesar José Santana
- João Alfredo


## Visão geral
Este projeto implementa um compilador de brinquedo para uma linguagem **Mini-Pascal** em Linux, usando:
- **Flex** para análise léxica
- **Bison** para análise sintática
- **LLVM IR API em C++** para geração de código intermediário
- **llc + clang** para gerar assembly, objeto e executável nativo

O compilador lê arquivos `.pas` e produz:
- executável nativo
- arquivo LLVM IR (`.ll`)
- assembly (`.s`)
- objeto (`.o`)

## Estrutura do projeto
- `src/lexer.l`: scanner Flex
- `src/parser.y`: gramática Bison
- `include/ast.hpp`: AST
- `include/codegen.hpp`: contexto de geração de código
- `src/codegen.cpp`: geração de LLVM IR
- `src/main.cpp`: driver principal do compilador
- `src/runtime.c`: runtime de suporte para I/O e argumentos
- `tests/*.pas`: programas obrigatórios
- `tests/out/`: executáveis e artefatos gerados
- `artifacts/`: evidências e logs

## Requisitos atendidos
- tipos `integer` e `boolean`
- declaração de variáveis
- atribuição
- `if then else`
- `while`
- `for ... to ... do`
- funções e procedimentos
- operadores aritméticos, relacionais e lógicos
- `write` e `writeln`
- leitura de argumento de linha de comando com `argi()` e `argc()`
- comentários com `#`, `//`, `{}` e `(* *)`
- geração de executável nativo

## Compilação do compilador
```bash
make
```

## Compilar um programa Mini-Pascal
```bash
./build/minipascalc tests/factor.pas -o tests/out/factor
```

## Executar um programa compilado
```bash
./tests/out/factor 84
```

## Script de teste automático
```bash
bash scripts/run_tests.sh
```

## Observações
- O compilador foi validado em ambiente Linux x86-64.
- O programa `pidigits.pas` usa uma aproximação inteira de π limitada a 9 casas decimais para evitar overflow em `int64`.
  
