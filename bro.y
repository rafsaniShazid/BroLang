%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
int yylex(void);
extern int yylineno;
extern char *yytext;

FILE *out;
FILE *icg;
#define MAX_SYMBOLS 100
int temp_count = 1;
int loop_depth = 0;

enum {
    TYPE_INT = 1,
    TYPE_LONG_LONG,
    TYPE_FLOAT,
    TYPE_STRING
};

char* new_temp() {
    char *temp = malloc(10);
    sprintf(temp, "t%d", temp_count++);
    return temp;
}

char symbol_table[MAX_SYMBOLS][50];
int symbol_types[MAX_SYMBOLS];
int symbol_count = 0;

int lookup_index(char *var) {
    for(int i = 0; i < symbol_count; i++) {
        if(strcmp(symbol_table[i], var) == 0)
            return i;
    }
    return -1;
}

int lookup(char *var) {
    return lookup_index(var) != -1;
}

int get_type(char *var) {
    int idx = lookup_index(var);
    if (idx == -1) return 0;
    return symbol_types[idx];
}

void insert(char *var, int type) {
    strcpy(symbol_table[symbol_count], var);
    symbol_types[symbol_count] = type;
    symbol_count++;
}

int is_identifier_like(const char *tok) {
    if (!tok || !tok[0]) return 0;
    return ((tok[0] >= 'a' && tok[0] <= 'z') ||
            (tok[0] >= 'A' && tok[0] <= 'Z') ||
            tok[0] == '_');
}

int is_statement_starter(const char *tok) {
    if (!tok || !tok[0]) return 0;
    return strcmp(tok, "bro") == 0 ||
           strcmp(tok, "bigbro") == 0 ||
           strcmp(tok, "lowkey") == 0 ||
           strcmp(tok, "textbro") == 0 ||
           strcmp(tok, "saybro") == 0 ||
           strcmp(tok, "askbro") == 0 ||
           strcmp(tok, "ifbro") == 0 ||
           strcmp(tok, "loopbro") == 0 ||
           strcmp(tok, "rip") == 0 ||
           strcmp(tok, "yeet") == 0 ||
           strcmp(tok, "elsebro") == 0 ||
           is_identifier_like(tok);
}
%}
%union {
    char *str;
}

%token INT LONG_LONG FLOAT STR COUT CIN IF ELSE WHILE RETURN BREAK INC DEC EQ
%token <str> IDENTIFIER
%token <str> NUMBER
%token <str> STRING
%type <str> expression condition

%left '+' '-'
%left '*' '/' '%'

%%
program:
    statements
    ;

statements:
    statement
    | statements statement
    ;

statement:
            declaration ';'
        | declaration_init ';'
        | assignment ';'
    | string_assignment ';'
        | increment_statement ';'
        | decrement_statement ';'
        | input_statement ';'
        | break_statement ';'
        | return_statement ';'
    | if_statement
    | loop_statement
        | print_statement ';'
;

break_statement:
    BREAK
    {
        if(loop_depth <= 0) {
            printf("Error: rip used outside loop\n");
        } else {
            fprintf(out, "    break;\n");
        }
    }
;

return_statement:
    RETURN
    {
        fprintf(icg, "return 0\n");
        fprintf(out, "    return 0;\n");
    }
    | RETURN expression
    {
        fprintf(icg, "return %s\n", $2);
        fprintf(out, "    return %s;\n", $2);
    }
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
        insert($2, TYPE_INT);
        fprintf(out, "    int %s;\n", $2);
    }
    | LONG_LONG IDENTIFIER
    {
        insert($2, TYPE_LONG_LONG);
        fprintf(out, "    long long %s;\n", $2);
    }
    | FLOAT IDENTIFIER
    {
        insert($2, TYPE_FLOAT);
        fprintf(out, "    float %s;\n", $2);
    }
    | STR IDENTIFIER
    {
        insert($2, TYPE_STRING);
        fprintf(out, "    string %s;\n", $2);
    }
;

declaration_init:
    INT IDENTIFIER '=' expression
    {
        insert($2, TYPE_INT);
        fprintf(icg, "%s = %s\n", $2, $4);
        fprintf(out, "    int %s = %s;\n", $2, $4);
    }
    | LONG_LONG IDENTIFIER '=' expression
    {
        insert($2, TYPE_LONG_LONG);
        fprintf(icg, "%s = %s\n", $2, $4);
        fprintf(out, "    long long %s = %s;\n", $2, $4);
    }
    | FLOAT IDENTIFIER '=' expression
    {
        insert($2, TYPE_FLOAT);
        fprintf(icg, "%s = %s\n", $2, $4);
        fprintf(out, "    float %s = %s;\n", $2, $4);
    }
    | STR IDENTIFIER '=' STRING
    {
        insert($2, TYPE_STRING);
        fprintf(icg, "%s = %s\n", $2, $4);
        fprintf(out, "    string %s = %s;\n", $2, $4);
    }
;

string_assignment:
    IDENTIFIER '=' STRING
    {
        if(!lookup($1)) {
            printf("Error: variable %s not declared\n", $1);
        } else if(get_type($1) != TYPE_STRING) {
            printf("Error: variable %s is not string type\n", $1);
        } else {
            fprintf(icg, "%s = %s\n", $1, $3);
            fprintf(out, "    %s = %s;\n", $1, $3);
        }
    }
;

increment_statement:
    IDENTIFIER INC
    {
        if(!lookup($1)) {
            printf("Error: variable %s not declared\n", $1);
        } else if(get_type($1) == TYPE_STRING) {
            printf("Error: cannot increment string variable %s\n", $1);
        } else {
            fprintf(icg, "%s = %s + 1\n", $1, $1);
            fprintf(out, "    %s++;\n", $1);
        }
    }
;

decrement_statement:
    IDENTIFIER DEC
    {
        if(!lookup($1)) {
            printf("Error: variable %s not declared\n", $1);
        } else if(get_type($1) == TYPE_STRING) {
            printf("Error: cannot decrement string variable %s\n", $1);
        } else {
            fprintf(icg, "%s = %s - 1\n", $1, $1);
            fprintf(out, "    %s--;\n", $1);
        }
    }
;

assignment:
    IDENTIFIER '=' expression
    {
        if(!lookup($1)) {
            printf("Error: variable %s not declared\n", $1);
        } else if(get_type($1) == TYPE_STRING) {
            printf("Error: assign string literals to string variable %s\n", $1);
        } else {
            fprintf(icg, "%s = %s\n", $1, $3);
            fprintf(out, "    %s = %s;\n", $1, $3);
        }
    }
;

if_head:
    IF '(' condition ')'
    {
        fprintf(out,"    if(%s) {\n",$3);
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
    WHILE '(' condition ')'
    {
        fprintf(out,"    while(%s) {\n",$3);
    }
    '{'
    {
        loop_depth++;
    }
    statements '}'
    {
        loop_depth--;
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
        if(!lookup($2)) {
            printf("Error: variable %s not declared\n", $2);
        } else {
            fprintf(out, "    cout << %s << endl;\n", $2);
        }
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
        {
            if(!lookup($1)) {
                printf("Error: variable %s not declared\n", $1);
                $$ = "0";
            } else if(get_type($1) == TYPE_STRING) {
                printf("Error: string variable %s cannot be used in numeric expression\n", $1);
                $$ = "0";
            } else {
                $$ = $1;
            }
        }

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

| expression '%' expression
{
    char *temp = new_temp();
    fprintf(icg, "%s = %s %% %s\n", temp, $1, $3);

    char *expr = malloc(100);
    sprintf(expr, "%s %% %s", $1, $3);
    $$ = expr;
}
;
%%

void yyerror(const char *s) {
    const char *tok = (yytext && yytext[0]) ? yytext : "EOF";
    if (strcmp(tok, "}") == 0 || strcmp(tok, "EOF") == 0 || is_statement_starter(tok)) {
        printf("Syntax error at line %d near '%s': possible missing ';' before this token\n", yylineno, tok);
    } else {
        printf("Syntax error at line %d near '%s'\n", yylineno, tok);
    }
}

int main() {
    int verbose = 0;
    const char *verbose_env = getenv("BRO_VERBOSE");
    if (verbose_env && strcmp(verbose_env, "1") == 0) {
        verbose = 1;
    }

    out = fopen("output.cpp", "w");
    icg = fopen("intermediate.txt", "w");

    fprintf(out, "#include <iostream>\n");
    fprintf(out, "#include <string>\n");
    fprintf(out, "using namespace std;\n\n");
    fprintf(out, "int main() {\n");

    yyparse();

    fprintf(out, "}\n");

    fclose(out);
    fclose(icg);

    if (verbose) {
        printf("C++ code generated in output.cpp\n");
        printf("Intermediate code generated in intermediate.txt\n");
    }

    return 0;
}
