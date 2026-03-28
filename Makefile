CC = gcc
CXX = g++
BISON = bison
FLEX = flex

PARSER = parser
RUN_BIN = bro_run
SRC = input.bro
PRINT_STATUS ?= 0

define log
	@if [ "$(PRINT_STATUS)" = "1" ]; then echo "$(1)"; fi
endef

.SILENT:

.PHONY: all parser gen run run-with-input run-verbose clean

all: run

parser: bro.tab.c lex.yy.c
	$(call log,[build] parser)
	$(CC) bro.tab.c lex.yy.c -o $(PARSER) -lfl

bro.tab.c bro.tab.h: bro.y
	$(call log,[build] bison)
	$(BISON) -d bro.y

lex.yy.c: bro.l bro.tab.h
	$(call log,[build] flex)
	$(FLEX) bro.l

gen: parser $(SRC)
	$(call log,[gen] $(SRC) -> output.cpp)
	./$(PARSER) < $(SRC)

$(RUN_BIN): gen output.cpp
	$(call log,[build] c++)
	$(CXX) output.cpp -o $(RUN_BIN)

run: $(RUN_BIN)
	$(call log,[run] $(RUN_BIN))
	./$(RUN_BIN)

run-verbose: parser $(SRC)
	$(call log,[gen] $(SRC) -> output.cpp (verbose parser))
	BRO_VERBOSE=1 ./$(PARSER) < $(SRC)
	$(call log,[build] c++)
	$(CXX) output.cpp -o $(RUN_BIN)
	$(call log,[run] $(RUN_BIN))
	./$(RUN_BIN)

# Usage: make run-with-input RUNTIME_INPUT=runtime_input.txt
run-with-input: $(RUN_BIN)
	$(call log,[run] $(RUN_BIN) < $(RUNTIME_INPUT))
	./$(RUN_BIN) < $(RUNTIME_INPUT)

clean:
	$(call log,[clean] artifacts)
	rm -f $(PARSER) $(RUN_BIN) bro.tab.c bro.tab.h lex.yy.c output.cpp intermediate.txt
