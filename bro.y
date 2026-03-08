%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex(void);
%}

%token INT LONG_LONG FLOAT COUT CIN IF ELSE WHILE RETURN BREAK NUMBER IDENTIFIER

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
    ;

declaration:
    INT IDENTIFIER
    {
        printf("Declared variable\n");
    }
    ;
%%

void yyerror(const char *s) {
    printf("Syntax error\n");
}

int main() {
    return yyparse();
}
