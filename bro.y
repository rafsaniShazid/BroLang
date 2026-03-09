%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex(void);
%}

%token INT LONG_LONG FLOAT COUT CIN IF ELSE WHILE RETURN BREAK NUMBER IDENTIFIER

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
        printf("Declared variable\n");
    }
    ;

assignment:
    IDENTIFIER '=' expression
    {
        printf("Assigned expression\n");
    }
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
        printf("Print statement\n");
    }
;

expression:
      NUMBER
    | IDENTIFIER
    | expression '+' expression
    | expression '-' expression
    | expression '*' expression
    | expression '/' expression
    ;
%%

void yyerror(const char *s) {
    printf("Syntax error\n");
}

int main() {
    return yyparse();
}
