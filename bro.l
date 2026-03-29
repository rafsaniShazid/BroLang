%{
#include <stdio.h>
#include "bro.tab.h"
%}

%option noyywrap yylineno

%%
"bro"        { return INT; }
"bigbro"     { return LONG_LONG; }
"lowkey"     { return FLOAT; }
"textbro"    { return STR; }
"saybro"     { return COUT; }
"askbro"     { return CIN; }
"ifbro"      { return IF; }
"elsebro"    { return ELSE; }
"loopbro"    { return WHILE; }
"yeet"       { return RETURN; }
"rip"        { return BREAK; }

"{"  { return '{'; }
"}"  { return '}'; }
"("  { return '('; }
")"  { return ')'; }
";"  { return ';'; }
[0-9]+(\.[0-9]+)? {
    yylval.str = strdup(yytext);
    return NUMBER;
}
"=" { return '='; }
"++" { return INC; }
"--" { return DEC; }
"+" { return '+'; }
"-" { return '-'; }
"*" { return '*'; }
"/" { return '/'; }
"%" { return '%'; }
">"  { return '>'; }
"<"  { return '<'; }
"=="  { return EQ; }

\"[^\"]*\" { yylval.str = strdup(yytext); return STRING; }

[a-zA-Z_][a-zA-Z0-9_]* {
    yylval.str = strdup(yytext);
    return IDENTIFIER;
}

[ \t\n]+     ;

. {
    fprintf(stderr, "Lexical error at line %d: invalid token '%s'\n", yylineno, yytext);
    /* Skip invalid character and continue scanning. */
}
%%
