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

typedef struct ExprNode ExprNode;
ExprNode* make_expr(const char *text, int type);

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

int is_numeric_type(int type) {
    return type == TYPE_INT || type == TYPE_LONG_LONG || type == TYPE_FLOAT;
}

const char* type_name(int type) {
    if (type == TYPE_INT) return "bro";
    if (type == TYPE_LONG_LONG) return "bigbro";
    if (type == TYPE_FLOAT) return "lowkey";
    if (type == TYPE_STRING) return "textbro";
    return "unknown";
}

int promote_numeric_type(int a, int b) {
    return (a > b) ? a : b;
}

int can_assign_numeric(int target, int source) {
    if (!is_numeric_type(target) || !is_numeric_type(source)) return 0;
    if (target == TYPE_FLOAT) return 1;
    if (target == TYPE_LONG_LONG) return source == TYPE_INT || source == TYPE_LONG_LONG;
    if (target == TYPE_INT) return source == TYPE_INT;
    return 0;
}

int literal_numeric_type(const char *literal) {
    return strchr(literal, '.') ? TYPE_FLOAT : TYPE_INT;
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

%code requires {
typedef struct ExprNode {
    char *text;
    int type;
} ExprNode;
}

%union {
    char *str;
    ExprNode *expr;
}

%token INT LONG_LONG FLOAT STR COUT CIN IF ELSE WHILE RETURN BREAK INC DEC EQ
%token <str> IDENTIFIER
%token <str> NUMBER
%token <str> STRING
%type <expr> expression
%type <str> condition

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
        fprintf(icg, "return %s\n", $2->text);
        fprintf(out, "    return %s;\n", $2->text);
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
        if(!can_assign_numeric(TYPE_INT, $4->type)) {
            printf("Type error: cannot assign %s expression to bro variable %s\n", type_name($4->type), $2);
            fprintf(out, "    int %s;\n", $2);
        } else {
            fprintf(icg, "%s = %s\n", $2, $4->text);
            fprintf(out, "    int %s = %s;\n", $2, $4->text);
        }
    }
    | LONG_LONG IDENTIFIER '=' expression
    {
        insert($2, TYPE_LONG_LONG);
        if(!can_assign_numeric(TYPE_LONG_LONG, $4->type)) {
            printf("Type error: cannot assign %s expression to bigbro variable %s\n", type_name($4->type), $2);
            fprintf(out, "    long long %s;\n", $2);
        } else {
            fprintf(icg, "%s = %s\n", $2, $4->text);
            fprintf(out, "    long long %s = %s;\n", $2, $4->text);
        }
    }
    | FLOAT IDENTIFIER '=' expression
    {
        insert($2, TYPE_FLOAT);
        if(!can_assign_numeric(TYPE_FLOAT, $4->type)) {
            printf("Type error: cannot assign %s expression to lowkey variable %s\n", type_name($4->type), $2);
            fprintf(out, "    float %s;\n", $2);
        } else {
            fprintf(icg, "%s = %s\n", $2, $4->text);
            fprintf(out, "    float %s = %s;\n", $2, $4->text);
        }
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
            printf("Type error: cannot assign numeric expression to textbro variable %s\n", $1);
        } else if(!can_assign_numeric(get_type($1), $3->type)) {
            printf("Type error: cannot assign %s expression to %s variable %s\n", type_name($3->type), type_name(get_type($1)), $1);
        } else {
            fprintf(icg, "%s = %s\n", $1, $3->text);
            fprintf(out, "    %s = %s;\n", $1, $3->text);
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
                    sprintf(temp, "%s > %s", $1->text, $3->text);
          $$ = temp;
      }
    | expression '<' expression
      {
          char *temp = malloc(100);
                    sprintf(temp, "%s < %s", $1->text, $3->text);
          $$ = temp;
      }
    | expression EQ expression
      {
          char *temp = malloc(100);
                    sprintf(temp, "%s == %s", $1->text, $3->text);
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
        {
            $$ = make_expr($1, literal_numeric_type($1));
        }

    | IDENTIFIER
        {
            if(!lookup($1)) {
                printf("Error: variable %s not declared\n", $1);
                $$ = make_expr("0", TYPE_INT);
            } else if(get_type($1) == TYPE_STRING) {
                printf("Error: string variable %s cannot be used in numeric expression\n", $1);
                $$ = make_expr("0", TYPE_INT);
            } else {
                $$ = make_expr($1, get_type($1));
            }
        }

| expression '+' expression
{
    char *temp = new_temp();
    fprintf(icg, "%s = %s + %s\n", temp, $1->text, $3->text);

    char *expr = malloc(100);
    sprintf(expr, "%s + %s", $1->text, $3->text);
    $$ = make_expr(expr, promote_numeric_type($1->type, $3->type));
}

| expression '-' expression
{
    char *temp = new_temp();
    fprintf(icg, "%s = %s - %s\n", temp, $1->text, $3->text);

    char *expr = malloc(100);
    sprintf(expr, "%s - %s", $1->text, $3->text);
    $$ = make_expr(expr, promote_numeric_type($1->type, $3->type));
}

| expression '*' expression
{
    char *temp = new_temp();
    fprintf(icg, "%s = %s * %s\n", temp, $1->text, $3->text);

    char *expr = malloc(100);
    sprintf(expr, "%s * %s", $1->text, $3->text);
    $$ = make_expr(expr, promote_numeric_type($1->type, $3->type));
}

| expression '/' expression
{
    char *temp = new_temp();
    fprintf(icg, "%s = %s / %s\n", temp, $1->text, $3->text);

    char *expr = malloc(100);
    sprintf(expr, "%s / %s", $1->text, $3->text);
    $$ = make_expr(expr, promote_numeric_type($1->type, $3->type));
}

| expression '%' expression
{
    char *temp = new_temp();
    fprintf(icg, "%s = %s %% %s\n", temp, $1->text, $3->text);

    char *expr = malloc(100);
    sprintf(expr, "%s %% %s", $1->text, $3->text);
    $$ = make_expr(expr, promote_numeric_type($1->type, $3->type));
}
;
%%

ExprNode* make_expr(const char *text, int type) {
    ExprNode *node = malloc(sizeof(ExprNode));
    node->text = strdup(text);
    node->type = type;
    return node;
}

void yyerror(const char *s) {
    const char *tok = (yytext && yytext[0]) ? yytext : "EOF";
    if (strcmp(tok, "}") == 0 || strcmp(tok, "EOF") == 0 || is_statement_starter(tok)) {
        printf("Syntax error at line %d near '%s': possible missing ';' before this token\n", yylineno, tok);
    } else {
        printf("Syntax error at line %d near '%s'\n", yylineno, tok);
    }
}

int main() {
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

    return 0;
}
