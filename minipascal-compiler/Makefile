CXX := clang++
CC := clang
LEX := flex
YACC := bison
LLVM_CXXFLAGS := $(shell llvm-config --cxxflags)
LLVM_LDFLAGS := $(shell llvm-config --ldflags --system-libs --libs core)
RUNTIME_SRC := $(abspath src/runtime.c)

CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -fexceptions -Iinclude -Isrc -Ibuild $(LLVM_CXXFLAGS) -fexceptions -DRUNTIME_SOURCE=\"$(RUNTIME_SRC)\"
LDFLAGS := $(LLVM_LDFLAGS)

SRC_DIR := src
BUILD_DIR := build
BIN := $(BUILD_DIR)/minipascalc

all: $(BIN)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/parser.tab.cpp $(BUILD_DIR)/parser.tab.hpp: $(SRC_DIR)/parser.y | $(BUILD_DIR)
	$(YACC) -d -v --defines=$(BUILD_DIR)/parser.tab.hpp -o $(BUILD_DIR)/parser.tab.cpp $(SRC_DIR)/parser.y

$(BUILD_DIR)/lexer.yy.cpp: $(SRC_DIR)/lexer.l $(BUILD_DIR)/parser.tab.hpp | $(BUILD_DIR)
	$(LEX) -o $(BUILD_DIR)/lexer.yy.cpp $(SRC_DIR)/lexer.l

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp include/ast.hpp include/codegen.hpp $(BUILD_DIR)/parser.tab.hpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/codegen.o: $(SRC_DIR)/codegen.cpp include/ast.hpp include/codegen.hpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/parser.tab.o: $(BUILD_DIR)/parser.tab.cpp include/ast.hpp include/codegen.hpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/lexer.yy.o: $(BUILD_DIR)/lexer.yy.cpp $(BUILD_DIR)/parser.tab.hpp include/ast.hpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN): $(BUILD_DIR)/main.o $(BUILD_DIR)/codegen.o $(BUILD_DIR)/parser.tab.o $(BUILD_DIR)/lexer.yy.o
	$(CXX) $^ $(LDFLAGS) -o $@

clean:
	rm -rf $(BUILD_DIR) tests/out artifacts

.PHONY: all clean
