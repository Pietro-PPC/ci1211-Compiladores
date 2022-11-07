#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tab_simbolos.h"

int main(){

	tab_simbolos_t tab;
	tab_simbolos_inic(&tab);

	simbolo_t s1, s2, s3;

	atribui_simbolo(&s1, "Pietro variavel simples", VARIAVEL_SIMPLES, 0, nova_var_simples(1, 2) );
	tab_simbolos_insere(&tab, &s1);

	void *proc = novo_procedimento("Rotulo Pietro", 1);
	atribui_simbolo (&s2, "Pietro so que procedimento", PROCEDIMENTO, 0, proc);
	tab_simbolos_insere(&tab, &s2);

	void *pf = novo_parametro_formal(TIPO_INT, 0, PASSAGEM_VALOR);
	atribui_simbolo (&s3, "Parametro formal 1", PARAMETRO_FORMAL, 1, pf);
	tab_simbolos_insere(&tab, &s3);

	printf("Indice do Pietro: %d\n", tab_simbolos_busca(&tab, "Pietro so que procedimento"));

	tab_simbolos_destroi(&tab);

	return 0;
}