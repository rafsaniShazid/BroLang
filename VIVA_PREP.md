# BroLang Viva Prep Guide

This file explains the complete project in exam-ready language.
Use it as your speaking script and revision notes.

## 1. Compiler Pipeline End-to-End

### Overview
BroLang uses a classic two-stage compile pipeline:

1. BroLang source (`input.bro`) is parsed and translated into C++ (`output.cpp`).
2. Generated C++ is compiled by `g++` into a native executable (`bro_run`).

It also emits teaching/debug output as intermediate code in `intermediate.txt`.

### Step-by-step flow

1. Source file: `input.bro`
2. Lexer (`bro.l`) converts character stream into tokens.
3. Parser/codegen (`bro.y`) checks grammar + semantic rules and emits:
   - `output.cpp`
   - `intermediate.txt`
4. C++ compiler (`g++`) compiles `output.cpp` into `bro_run`.
5. Executable runs and prints final output.

Short pipeline form:

`input.bro -> tokens -> parse/semantic checks -> output.cpp + intermediate.txt -> bro_run -> terminal output`

## 2. Lexical Analysis (Flex)

Implemented in `bro.l`.

### What lexer does
The lexer reads raw characters and classifies them into tokens used by Bison.

### Token categories

1. Keywords:
   - `bro`, `bigbro`, `lowkey`, `textbro`
   - `saybro`, `askbro`
   - `ifbro`, `elsebro`, `loopbro`
   - `rip`, `yeet`

2. Identifiers:
   - Pattern: `[a-zA-Z_][a-zA-Z0-9_]*`

3. Numbers:
   - Pattern: `[0-9]+`

4. Strings:
   - Pattern: `"[^"]*"`

5. Operators:
   - Arithmetic: `+`, `-`, `*`, `/`, `%`
   - Increment/decrement: `++`, `--`
   - Assignment/comparison: `=`, `==`, `<`, `>`

6. Symbols:
   - `{`, `}`, `(`, `)`, `;`

7. Whitespace:
   - Ignored

## 3. Parsing and Grammar (Bison)

Implemented in `bro.y`.

### Statement model
BroLang is semicolon-based for simple statements.

Examples requiring `;`:
- declarations
- assignments
- `askbro`
- `saybro`
- `i++`, `i--`
- `rip`, `yeet`

Block statements (`ifbro`, `loopbro`) use braces and do not need a trailing semicolon.

### Control-flow grammar constraints

1. Conditions must be parenthesized:
   - `ifbro (i==2) { ... }`
   - `loopbro (i<10) { ... }`

2. If-else structure:
   - `ifbro (...) { ... }`
   - `ifbro (...) { ... } elsebro { ... }`

## 4. Semantic Checks

Also handled in `bro.y` during parse actions.

### Key checks

1. Declaration-before-use:
- Any variable used in assignment, expression, input/output, increment/decrement must be declared first.

2. Type checks:
- Numeric expressions reject string variables.
- String assignment to non-string variable is rejected.
- `++` / `--` on string variable is rejected.

3. `rip` scope check:
- `rip;` is only valid inside loops.
- Outside loop, compiler reports an error.

## 5. Code Generation Strategy

Core idea: direct translation from BroLang grammar actions to C++ output lines.

### Why this matters
This is the center of the project: each grammar rule both validates and generates code.

### Mapping examples

1. `bro x;` -> `int x;`
2. `bigbro n = 10;` -> `long long n = 10;`
3. `textbro s = "hi";` -> `string s = "hi";`
4. `saybro x;` -> `cout << x << endl;`
5. `askbro x;` -> `cin >> x;`
6. `ifbro (...) { ... }` -> `if (...) { ... }`
7. `loopbro (...) { ... }` -> `while (...) { ... }`
8. `rip;` -> `break;`
9. `yeet;` -> `return 0;`
10. `yeet expr;` -> `return expr;`

### Intermediate code
Arithmetic operations also write simplified three-address-like steps to `intermediate.txt`.

## 6. Error Handling Quality

### Syntax diagnostics
`yyerror` is improved to report:
- line number
- near token
- missing semicolon hint when likely

Example style:
- `Syntax error at line 2 near 'saybro': possible missing ';' before this token`

### Semantic diagnostics
Examples:
- undeclared variable
- invalid string/numeric operation
- `rip` outside loop

## 7. Supported Language Features (Current)

1. Types:
- `bro` (`int`)
- `bigbro` (`long long`)
- `lowkey` (`float`)
- `textbro` (`string`)

2. Declarations and initialization
3. Assignment
4. Arithmetic: `+ - * / %`
5. Input/output: `askbro`, `saybro`
6. If/else and while-style loop
7. Increment/decrement: `++`, `--`
8. `rip` (break)
9. `yeet` (return)
10. Intermediate code generation

## 8. Build/Run Workflow

### Manual workflow

1. `bison -d bro.y`
2. `flex bro.l`
3. `gcc bro.tab.c lex.yy.c -o parser -lfl`
4. `./parser < input.bro`
5. `g++ output.cpp -o bro_run`
6. `./bro_run`

### Makefile workflow

1. Default run:
- `make run`

2. Runtime input from file:
- `make run-with-input RUNTIME_INPUT=runtime_input.txt`

## 9. Design Tradeoffs

### Why direct codegen to C++?

1. Simplicity:
- No VM design needed.

2. Teachable:
- Easy to show mapping from source statement to generated C++ line.

3. Fast to demo:
- You can produce runnable native output quickly.

4. Reuse mature backend:
- Let `g++` handle optimization and machine code generation.

### Alternative options (not chosen)

1. Interpreter:
- Easier to skip C++ step, but runtime semantics implementation grows quickly.

2. Bytecode VM:
- More flexible architecture, but significantly more complex for course scope.

## 10. Limitation Awareness and Future Work

### Current limitations

1. Type system is basic (no advanced coercion or full static type inference).
2. String support is limited to declaration/init/assignment/input/output; no full string algebra API.
3. Error recovery is basic (parser reports and continues in limited ways).
4. No function definitions/user-defined procedures.

### Good future improvements

1. Better parser recovery rules to continue after syntax errors.
2. Richer type checking and clearer type mismatch messages.
3. Full string expression support and library-like operations.
4. Function support and scope management.
5. Symbol table enhancements (scoped blocks, redeclaration checks).

## Short Viva Closing Script

"This project demonstrates a compact compiler pipeline: Flex tokenizes source, Bison parses and performs semantic checks, and grammar actions directly generate C++ plus intermediate code. The generated C++ is compiled by g++ to native executable output. I focused on clarity and teachability: each BroLang construct maps visibly to C++, while semantic checks catch undeclared variables, invalid type operations, and invalid loop control usage."
