# BroLang

BroLang is a tiny custom language that is compiled in two stages:

1. BroLang source -> generated C++ (`output.cpp`)
2. Generated C++ -> executable (`bro_run`)

It also generates intermediate code in `intermediate.txt`.

## Project Files

- `bro.l`: Lexer (Flex)
- `bro.y`: Parser + code generator (Bison)
- `input.bro`: Default BroLang input file
- `output.cpp`: Generated C++ file
- `intermediate.txt`: Generated intermediate code
- `Makefile`: Build and run shortcuts

## Prerequisites

Install these tools:

- flex
- bison
- gcc
- g++
- make

Example install on Ubuntu/Debian:

```bash
sudo apt update
sudo apt install flex bison gcc g++ make
```

## Quick Start (One Command)

Run BroLang source from `input.bro`:

```bash
make run
```

This command automatically:

1. Builds lexer/parser
2. Parses `input.bro`
3. Generates `output.cpp`
4. Compiles generated C++
5. Runs the executable

By default, output is clean (only your program output).

## Useful Make Commands

Run with build status lines:

```bash
make run PRINT_STATUS=1
```

Run with parser generation messages too:

```bash
make run-verbose PRINT_STATUS=1
```

Run with runtime input redirected from a file (for `askbro` programs):

```bash
make run-with-input RUNTIME_INPUT=runtime_input.txt
```

Use a different BroLang source file:

```bash
make run SRC=my_program.bro
```

Clean generated artifacts:

```bash
make clean
```

## Manual Run Method (Without Make)

```bash
bison -d bro.y
flex bro.l
gcc bro.tab.c lex.yy.c -o parser -lfl
./parser < input.bro
g++ output.cpp -o bro_run
./bro_run
```

## Exact Language Syntax

### Statement Rules

- Semicolon is required for simple statements.
- `ifbro` and `loopbro` blocks use braces and do not need a trailing semicolon.
- Conditions must be inside parentheses.

### Types

- `bro` -> `int`
- `bigbro` -> `long long`
- `lowkey` -> `float`
- `textbro` -> `string`

### Declarations

```text
bro x;
bigbro total;
lowkey ratio;
textbro name;
```

### Declaration with Initialization

```text
bro i = 0;
bigbro n = 1000000;
lowkey p = 3;
textbro title = "BroLang";
```

### Assignment

```text
x = 5;
i = i + 2;
name = "Compiler";
```

### Increment / Decrement

```text
i++;
i--;
```

### Input / Output

```text
askbro x;
askbro name;
saybro x;
saybro name;
saybro "hello";
```

### Conditions

Supported comparisons:

- `>`
- `<`
- `==`

Examples:

```text
ifbro (i==4) {
    saybro "four";
}

ifbro (i<4) {
    saybro "small";
} elsebro {
    saybro "not small";
}
```

### Loop

```text
loopbro (i<3) {
    saybro i;
    i++;
}
```

### Arithmetic Expressions

Supported operators:

- `+`
- `-`
- `*`
- `/`
- `%`

Example:

```text
bro a = 5;
bro b = 2;
bro c = a + b * 3;
bro d = a % b;
```

### Break and Return

`rip` works like `break` and should be used inside loops.

`yeet` works like `return`.

```text
loopbro (i<10) {
    ifbro (i==5) {
        rip;
    }
    i++;
}

yeet;
yeet 0;
```

## Full Example Program

```text
textbro name = "BroLang";
saybro name;

bro i = 0;
loopbro (i<3) {
    ifbro (i%2==0) {
        saybro "even";
    }
    saybro i;
    i++;
}

name = "Compiler";
saybro name;
yeet 0;
```

## Error Behavior

- Undeclared variable usage prints an error message.
- If an undeclared variable appears in an expression, parser substitutes `0` and continues.
- Syntax errors now include line number and nearby token; missing semicolons include a specific hint.
- `rip` outside a loop prints `Error: rip used outside loop`.
- Assigning a string literal to a non-string variable prints a type error.
- Using a string variable in numeric expression or ++/-- prints a type error.

## Outputs

After parsing:

- Generated C++ is written to `output.cpp`
- Intermediate code is written to `intermediate.txt`
