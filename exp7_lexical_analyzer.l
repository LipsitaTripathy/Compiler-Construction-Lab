
%{
#include <stdio.h>
%}

%option noyywrap

%%
"int"|"float"|"char"|"double"|"if"|"else"|"while"|"for"|"return" {
    printf("%s -> KEYWORD\n", yytext);
}

[0-9]+ {
    printf("%s -> NUMBER\n", yytext);
}

[a-zA-Z_][a-zA-Z0-9_]* {
    printf("%s -> IDENTIFIER\n", yytext);
}

"=="|"!="|"<="|">="|"&&"|"||"|"++"|"--" {
    printf("%s -> OPERATOR\n", yytext);
}

[+\-*/%=<>] {
    printf("%s -> OPERATOR\n", yytext);
}

[{}();,\[\]] {
    printf("%s -> SPECIAL SYMBOL\n", yytext);
}

[ \t\n]+ { /* Ignore whitespace */ }

. {
    printf("%s -> UNKNOWN\n", yytext);
}
%%

int main()
{
    printf("Enter C program (Ctrl+D to finish):\n");
    yylex();
    return 0;
}
