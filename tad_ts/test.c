#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tab_simbolos.h"

int main(){

	tab_simbolos_t tab;
	tab_simbolos_inic(&tab);

	simbolo_t s1, s2;

	s1.identificador = malloc(100); strcpy(s1.identificador, "Pietro variavel simples");
	s1.categoria = VARIAVEL_SIMPLES;
	s1.nivel = 0;
	s1.atributos_var = nova_var_simples(1, 2);


	s2.identificador = malloc(100); strcpy(s2.identificador, "Pietro so que procedimento");
	s2.categoria = PROCEDIMENTO;
	s2.nivel = 0;


	char *rotulo = "Rotulo Pietro";
	insere_parametro_formal();

	s2.atributos_var = novo_procedimento(rotulo);


	tab_simbolos_insere(&tab, &s1);
	printf("Indice do Pietro: %d\n", tab_simbolos_busca(&tab, "Pietro"));

	tab_simbolos_elimina(&tab, 1);
	printf("Indice do Pietro depois de tirar: %d\n", tab_simbolos_busca(&tab, "Pietro"));

	tab_simbolos_destroi(&tab);

	return 0;
}