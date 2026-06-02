# Relatório final — Compilador Mini-Pascal

## Identificação
- Faculdade: _preencher se necessário_
- Curso: _preencher se necessário_
- Disciplina: Compiladores / Laboratório
- Projeto: Construir um compilador de brinquedo para Mini-Pascal usando Flex, Bison e LLVM
- Integrantes:
  - Cesar José Santana
  - João Alfredo
  - Leonardo de Souza

## Resumo
Este trabalho implementa um compilador de brinquedo para uma linguagem Mini-Pascal, com análise léxica em Flex, análise sintática em Bison e geração de código intermediário com a API LLVM em C++. O compilador gera LLVM IR, assembly, objeto e executável nativo, além de suportar os quatro programas de teste pedidos: fatoração, primalidade, Fibonacci e dígitos de π.

## Objetivos atendidos
- scanner com expressões regulares e tokens principais
- parser com gramática livre de contexto
- AST para representação sintática
- verificação semântica básica
- geração de LLVM IR
- ligação com runtime em C
- geração de executáveis nativos
- documentação e automação de testes

## Linguagem implementada
### Tipos
- `integer`
- `boolean`

### Recursos da linguagem
- declaração de variáveis
- atribuição com `:=`
- `if then else`
- `while`
- `for ... to ... do`
- funções e procedimentos
- `write` e `writeln`
- operadores aritméticos, lógicos e relacionais
- acesso à linha de comando com `argi()` e `argc()`

## Arquitetura
1. **Flex** tokeniza a entrada.
2. **Bison** reconhece a gramática e constrói a AST.
3. **AST** representa o programa de forma estruturada.
4. **CodeGen** percorre a AST e emite LLVM IR.
5. **llc** converte IR em assembly/objeto.
6. **clang** liga o runtime e gera o executável final.

## Arquivos principais
- `src/lexer.l`
- `src/parser.y`
- `include/ast.hpp`
- `include/codegen.hpp`
- `src/codegen.cpp`
- `src/main.cpp`
- `src/runtime.c`
- `Makefile`
- `scripts/run_tests.sh`

## Evidências de ambiente
Ver `artifacts/toolchain_versions.txt`.

## Evidências de execução
Ver:
- `artifacts/factor_output.txt`
- `artifacts/isprime_output.txt`
- `artifacts/isprime_output_91.txt`
- `artifacts/fibonacci_output.txt`
- `artifacts/pidigits_output.txt`
- `artifacts/execution_evidence.png`

## Resultados observados
- `factor 84` → `2 2 3 7`
- `isprime 97` → `true`
- `isprime 91` → `false`
- `fibonacci 10` → `55`
- `pidigits 6` → `3.141594`

## Uso de IA
### Assistente utilizado
- Genspark AI Assistant

### Uso realizado
- apoio na estruturação do compilador
- revisão iterativa do scanner, parser e codegen
- organização da documentação
- preparação do pacote final

### Observação ética
O código foi organizado para estudo e entrega acadêmica. Recomenda-se leitura, revisão e entendimento do material antes da apresentação.

## Prompts-base em inglês utilizados no desenvolvimento
1. `Build a toy Mini-Pascal compiler in C++ using Flex, Bison and LLVM IRBuilder, with integer and boolean types, if/while/for, functions, procedures, write/writeln and command-line integer arguments.`
2. `Review the grammar and AST integration for a Flex/Bison compiler and ensure the generated LLVM IR can be lowered to assembly and a native executable on Linux.`
3. `Write a clear markdown tutorial explaining project structure, lexical analysis, parsing, semantic checks, LLVM IR generation, linking, testing, and debugging.`

## Limitações técnicas
- sem `real`
- sem arrays
- sem registros/records
- sem otimizações avançadas
- `pidigits` limitado por precisão inteira de 64 bits

## Melhorias futuras
- adicionar tipo `real`
- suporte a arrays
- suporte a escopos mais ricos e shadowing formal
- mensagens de erro mais detalhadas com contexto léxico
- pipeline com testes unitários adicionais

## Referências de estudo
- Proposta do projeto fornecida pelo usuário
- Documentação LLVM
- Tutoriais de compiladores com Flex/Bison/LLVM
