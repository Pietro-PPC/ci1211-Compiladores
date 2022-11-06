#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tab_simbolos.h"

int main(){

	tab_simbolos_t tab;
	tab_simbolos_inic(&tab);

	simbolo_t s;

	s.identificador = malloc(100); strcpy(s.identificador, "Pietro");
	s.categoria = VARIAVEL_SIMPLES;
	s.nivel = 0;
	s.atributos_var = nova_var_simples(1, 2);

	tab_simbolos_insere(&tab, &s);
	printf("Indice do Pietro: %d\n", tab_simbolos_busca(&tab, "Pietro"));

	tab_simbolos_elimina(&tab, 1);
	printf("Indice do Pietro depois de tirar: %d\n", tab_simbolos_busca(&tab, "Pietro"));

	tab_simbolos_destroi(&tab);

	return 0;
}