#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT_DIR"

mkdir -p tests/out artifacts

make -j2

./build/minipascalc tests/factor.pas -o tests/out/factor
./build/minipascalc tests/isprime.pas -o tests/out/isprime
./build/minipascalc tests/fibonacci.pas -o tests/out/fibonacci
./build/minipascalc tests/pidigits.pas -o tests/out/pidigits

./tests/out/factor 84 | tee artifacts/factor_output.txt
./tests/out/isprime 97 | tee artifacts/isprime_output.txt
./tests/out/isprime 91 | tee artifacts/isprime_output_91.txt
./tests/out/fibonacci 10 | tee artifacts/fibonacci_output.txt
./tests/out/pidigits 6 | tee artifacts/pidigits_output.txt

echo "Todos os testes principais foram executados com sucesso."
