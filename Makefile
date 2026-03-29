CC = gcc
CXX = g++
BISON = bison
FLEX = flex

PARSER = parser
RUN_BIN = bro_run
SRC = input.bro

.SILENT:

.PHONY: all parser gen run run-with-input clean

all: run

parser: bro.tab.c lex.yy.c
	$(CC) bro.tab.c lex.yy.c -o $(PARSER) -lfl

bro.tab.c bro.tab.h: bro.y
	$(BISON) -d bro.y

lex.yy.c: bro.l bro.tab.h
	$(FLEX) bro.l

gen: parser $(SRC)
	./$(PARSER) < $(SRC)

$(RUN_BIN): gen output.cpp
	$(CXX) output.cpp -o $(RUN_BIN)

run: $(RUN_BIN)
	./$(RUN_BIN)

# Usage: make run-with-input RUNTIME_INPUT=runtime_input.txt
run-with-input: $(RUN_BIN)
	./$(RUN_BIN) < $(RUNTIME_INPUT)

clean:
	rm -f $(PARSER) $(RUN_BIN) bro.tab.c bro.tab.h lex.yy.c output.cpp intermediate.txt
