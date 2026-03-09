%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
int yylex(void);

FILE *out;
#define MAX_SYMBOLS 100

char symbol_table[MAX_SYMBOLS][50];
int symbol_count = 0;

int lookup(char *var) {
    for(int i = 0; i < symbol_count; i++) {
        if(strcmp(symbol_table[i], var) == 0)
            return 1;
    }
    return 0;
}

void insert(char *var) {
    strcpy(symbol_table[symbol_count], var);
    symbol_count++;
}
%}
%union {
    char *str;
}

%token INT LONG_LONG FLOAT COUT CIN IF ELSE WHILE RETURN BREAK
%token <str> IDENTIFIER
%token <str> NUMBER
%type <str> expression

%left '+' '-'
%left '*' '/'

%%
program:
    statements
    ;

statements:
    statement
    | statements statement
    ;

statement:
      declaration
    | assignment
    | if_statement
    | loop_statement
    | print_statement
;

declaration:
    INT IDENTIFIER
    {
        insert($2);
        fprintf(out, "    int %s;\n", $2);
    }
;

assignment:
    IDENTIFIER '=' expression
    {
        if(!lookup($1)) {
            printf("Error: variable %s not declared\n", $1);
        } else {
            fprintf(out, "    %s = %s;\n", $1, $3);
        }
    }
;

if_statement:
    IF condition
    {
        printf("If condition detected\n");
    }
;
loop_statement:
    WHILE condition
    {
        printf("Loop detected\n");
    }
;

condition:
      expression '>' expression
    | expression '<' expression
;
print_statement:
    COUT IDENTIFIER
    {
        fprintf(out, "    cout << %s << endl;\n", $2);
    }
;

expression:
      NUMBER
        { $$ = $1; }
    | IDENTIFIER
        { $$ = $1; }
    | expression '+' expression
        {
            char *temp = malloc(100);
            sprintf(temp, "%s + %s", $1, $3);
            $$ = temp;
        }
    | expression '-' expression
        {
            char *temp = malloc(100);
            sprintf(temp, "%s - %s", $1, $3);
            $$ = temp;
        }
    | expression '*' expression
        {
            char *temp = malloc(100);
            sprintf(temp, "%s * %s", $1, $3);
            $$ = temp;
        }
    | expression '/' expression
        {
            char *temp = malloc(100);
            sprintf(temp, "%s / %s", $1, $3);
            $$ = temp;
        }
;
%%

void yyerror(const char *s) {
    printf("Syntax error\n");
}

int main() {

    out = fopen("output.cpp", "w");

    fprintf(out, "#include <iostream>\n");
    fprintf(out, "using namespace std;\n\n");
    fprintf(out, "int main() {\n");

    yyparse();

    fprintf(out, "}\n");

    fclose(out);

    printf("C++ code generated in output.cpp\n");

    return 0;
}
