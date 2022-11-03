#include "tab_simbolos.h"

void tab_simbolos_init (tab_simbolos_t *tab){
	tab->pilha = NULL;
	tab->tam = 0;
	tab->alloc_tam = 0;
}

/* 
	TODO: Ainda tem que ver alocação dinâmica nos atributos variáveis
*/
void tab_simbolos_destroy (tab_simbolos_t *tab){
	for (unsigned int i = 0; i < tab->tam; ++i){
		if (tab->pilha[i]->identificador) free(tab[i]->identificador);
		if (tab->pilha[i]->atributos_var) free(tab[i]->atributos_var); // talvez não seja só isso
	}
	free(tab->pilha);
}

void tab_simbolos_insere (tab_simbolos_t *tab, simbolo_t *simb){
	if (tab->alloc_tam == tab->tam)
		tab->pilha = realloc(tab->pilha, (tab->alloc_tam + ALLOC_STEP) * sizeof(simbolo_t));
	
	memcpy(tab->pilha[tab->tam], simb, sizeof(simbolo_t));
	tab->tam++;
}

int tab_simbolos_busca (tab_simbolos_t *tab, char *ident){
	int it = tab->tam-1;
	while (it >= 0){
		if (!strcmp(tab->pilha[it]->identificador, ident)) return it;
		it--;
	}
	return it;
}

/* Talvez mudar para uma alocação de passo binário depois */
void tab_simbolos_elimina (tab_simbolos_t *tab, unsigned int n){
	if (n > tab->tam) {
		fprintf(stderr, "Tentaste remover elementos demais da tabela!\n");
		exit(1);
	}

	tab->tam -= n;

	// Fase de realocação
	unsigned int exceeding_blocks = (tab->alloc_tam - tab->tam)/ALLOC_STEP;
	if (exceeding_blocks){
		unsigned int novo_tam = tab->alloc_tam - exceeding_blocks*ALLOC_STEP;
		tab->pilha = realloc(tab->pilha, novo_tam * sizeof(simbolo_t) );
		tab->alloc_tam = novo_tam;
	}
}
