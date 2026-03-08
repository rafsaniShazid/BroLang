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

[0-9]+       { return NUMBER; }
"=" { return '='; }
"+" { return '+'; }
"-" { return '-'; }
"*" { return '*'; }
"/" { return '/'; }
[a-zA-Z_][a-zA-Z0-9_]* { return IDENTIFIER; }

[ \t\n]+     ;

.            { return yytext[0]; }
%%
