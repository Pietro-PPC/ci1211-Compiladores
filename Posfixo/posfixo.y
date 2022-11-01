
%{
#include <stdio.h>
%}

%token IDENT_INT IDENT_BOOL MAIS MENOS OR AND ASTERISCO DIV ABRE_PARENTESES FECHA_PARENTESES

%%

geral : expr | disj ;

expr       : expr MAIS termo {printf ("+"); } |
             expr MENOS termo {printf ("-"); } | 
             termo
;


termo      : termo ASTERISCO fator  {printf ("*"); }| 
             termo DIV fator  {printf ("/"); }|
             fator
;

fator      : IDENT_INT { printf ("A"); }
;



disj       : disj OR conj { printf(" or "); } |
             conj
;

conj       : conj AND lit { printf(" and "); } |
             lit
;

lit        : IDENT_BOOL { printf("B"); }
;


%%

main (int argc, char** argv) {
   yyparse();
   printf("\n");
}

