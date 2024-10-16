%{
#include <stdio.h>
%}

%%

'first'		{ printf("Matched: first\n");}
'second'	{ printf("Matched: second\n");}
.|n		{ /* unmatched input */}	

%%

int main() {
	yylex();
	return 0;
}
