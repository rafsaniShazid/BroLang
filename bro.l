%{
#include <stdio.h>
#include "bro.tab.h"
%}

%option noyywrap

%%
"bro"        { return INT; }
"bigbro"     { return LONG_LONG; }
"lowkey"     { return FLOAT; }
"saybro"     { return COUT; }
"askbro"     { return CIN; }
"ifbro"      { return IF; }
"elsebro"    { return ELSE; }
"loopbro"    { return WHILE; }
"yeet"       { return RETURN; }
"rip"        { return BREAK; }

"{"  { return '{'; }
"}"  { return '}'; }
[0-9]+ {
    yylval.str = strdup(yytext);
    return NUMBER;
}
"=" { return '='; }
"++" { return INC; }
"+" { return '+'; }
"-" { return '-'; }
"*" { return '*'; }
"/" { return '/'; }
">"  { return '>'; }
"<"  { return '<'; }
"=="  { return EQ; }

\"[^\"]*\" { yylval.str = strdup(yytext); return STRING; }

[a-zA-Z_][a-zA-Z0-9_]* {
    yylval.str = strdup(yytext);
    return IDENTIFIER;
}

[ \t\n]+     ;

.            { return yytext[0]; }
%%
