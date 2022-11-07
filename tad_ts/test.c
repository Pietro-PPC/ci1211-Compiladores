#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tab_simbolos.h"

int main(){

	tab_simbolos_t tab;
	tab_simbolos_inic(&tab);

	simbolo_t s1, s2, s3;

	s1.identificador = malloc(100); strcpy(s1.identificador, "Pietro variavel simples");
	s1.categoria = VARIAVEL_SIMPLES;
	s1.nivel = 0;
	s1.atributos_var = nova_var_simples(1, 2);
	tab_simbolos_insere(&tab, &s1);


	s2.identificador = malloc(100); strcpy(s2.identificador, "Pietro so que procedimento");
	s2.categoria = PROCEDIMENTO;
	s2.nivel = 0;
	char *rotulo = malloc(100); strcpy(rotulo, "Rotulo Pietro");
	s2.atributos_var = novo_procedimento(rotulo, 1, tab_simbolos_topo(&tab)+1);
	tab_simbolos_insere(&tab, &s2);

	s3.identificador = malloc(100); strcpy(s3.identificador, "Parametro formal 1");
	s3.categoria = PARAMETRO_FORMAL;
	s3.nivel = 1;
	s3.atributos_var = novo_parametro_formal(TIPO_INT, 0, PASSAGEM_VALOR);
	tab_simbolos_insere(&tab, &s3);

	printf("Indice do Pietro: %d\n", tab_simbolos_busca(&tab, "Pietro so que procedimento"));

	tab_simbolos_destroi(&tab);

	return 0;
}