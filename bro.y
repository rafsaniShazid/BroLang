%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
int yylex(void);

FILE *out;
FILE *icg;
#define MAX_SYMBOLS 100
int temp_count = 1;

char* new_temp() {
    char *temp = malloc(10);
    sprintf(temp, "t%d", temp_count++);
    return temp;
}

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

%token INT LONG_LONG FLOAT COUT CIN IF ELSE WHILE RETURN BREAK INC EQ
%token <str> IDENTIFIER
%token <str> NUMBER
%token <str> STRING
%type <str> expression condition

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
    | declaration_init
    | assignment
    | increment_statement
    | input_statement
    | if_statement
    | loop_statement
    | print_statement
;

input_statement:
    CIN IDENTIFIER
    {
        if(!lookup($2)) {
            printf("Error: variable %s not declared\n", $2);
        } else {
            fprintf(out, "    cin >> %s;\n", $2);
        }
    }
;

declaration:
    INT IDENTIFIER
    {
        insert($2);
        fprintf(out, "    int %s;\n", $2);
    }
    | LONG_LONG IDENTIFIER
    {
        insert($2);
        fprintf(out, "    long long %s;\n", $2);
    }
    | FLOAT IDENTIFIER
    {
        insert($2);
        fprintf(out, "    float %s;\n", $2);
    }
;

declaration_init:
    INT IDENTIFIER '=' expression
    {
        insert($2);
        fprintf(icg, "%s = %s\n", $2, $4);
        fprintf(out, "    int %s = %s;\n", $2, $4);
    }
    | LONG_LONG IDENTIFIER '=' expression
    {
        insert($2);
        fprintf(icg, "%s = %s\n", $2, $4);
        fprintf(out, "    long long %s = %s;\n", $2, $4);
    }
    | FLOAT IDENTIFIER '=' expression
    {
        insert($2);
        fprintf(icg, "%s = %s\n", $2, $4);
        fprintf(out, "    float %s = %s;\n", $2, $4);
    }
;

increment_statement:
    IDENTIFIER INC
    {
        if(!lookup($1)) {
            printf("Error: variable %s not declared\n", $1);
        } else {
            fprintf(icg, "%s = %s + 1\n", $1, $1);
            fprintf(out, "    %s++;\n", $1);
        }
    }
;

assignment:
    IDENTIFIER '=' expression
    {
        if(!lookup($1)) {
            printf("Error: variable %s not declared\n", $1);
        } else {
            fprintf(icg, "%s = %s\n", $1, $3);
            fprintf(out, "    %s = %s;\n", $1, $3);
        }
    }
;

if_head:
    IF condition
    {
        fprintf(out,"    if(%s) {\n",$2);
    }
;

if_statement:
    if_head '{' statements '}'
    {
        fprintf(out,"    }\n");
    }
    | if_head '{' statements '}' ELSE
    {
        fprintf(out,"    } else {\n");
    }
    '{' statements '}'
    {
        fprintf(out,"    }\n");
    }
;

loop_statement:
    WHILE condition
    {
        fprintf(out,"    while(%s) {\n",$2);
    }
    '{' statements '}'
    {
        fprintf(out,"    }\n");
    }
;

condition:
      expression '>' expression
      {
          char *temp = malloc(100);
          sprintf(temp, "%s > %s", $1, $3);
          $$ = temp;
      }
    | expression '<' expression
      {
          char *temp = malloc(100);
          sprintf(temp, "%s < %s", $1, $3);
          $$ = temp;
      }
    | expression EQ expression
      {
          char *temp = malloc(100);
          sprintf(temp, "%s == %s", $1, $3);
          $$ = temp;
      }
;

print_statement:
    COUT IDENTIFIER
    {
        fprintf(out, "    cout << %s << endl;\n", $2);
    }
    | COUT STRING
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
    char *temp = new_temp();
    fprintf(icg, "%s = %s + %s\n", temp, $1, $3);

    char *expr = malloc(100);
    sprintf(expr, "%s + %s", $1, $3);
    $$ = expr;
}

| expression '-' expression
{
    char *temp = new_temp();
    fprintf(icg, "%s = %s - %s\n", temp, $1, $3);

    char *expr = malloc(100);
    sprintf(expr, "%s - %s", $1, $3);
    $$ = expr;
}

| expression '*' expression
{
    char *temp = new_temp();
    fprintf(icg, "%s = %s * %s\n", temp, $1, $3);

    char *expr = malloc(100);
    sprintf(expr, "%s * %s", $1, $3);
    $$ = expr;
}

| expression '/' expression
{
    char *temp = new_temp();
    fprintf(icg, "%s = %s / %s\n", temp, $1, $3);

    char *expr = malloc(100);
    sprintf(expr, "%s / %s", $1, $3);
    $$ = expr;
}
;
%%

void yyerror(const char *s) {
    printf("Syntax error\n");
}

int main() {

    out = fopen("output.cpp", "w");
    icg = fopen("intermediate.txt", "w");

    fprintf(out, "#include <iostream>\n");
    fprintf(out, "using namespace std;\n\n");
    fprintf(out, "int main() {\n");

    yyparse();

    fprintf(out, "}\n");

    fclose(out);
    fclose(icg);

    printf("C++ code generated in output.cpp\n");
    printf("Intermediate code generated in intermediate.txt\n");

    return 0;
}
