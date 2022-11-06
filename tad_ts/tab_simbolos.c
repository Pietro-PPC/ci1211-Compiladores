#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tab_simbolos.h"

void *nova_var_simples(unsigned short int tipo, unsigned int deslocamento){
	var_simples_av_t *ret;
	ret = malloc( sizeof(var_simples_av_t) );

	ret->tipo = tipo;
	ret->deslocamento = deslocamento;

	return (void *) ret;
}

void destroi_var_simples(void *var_simples){
	if (var_simples)
		free(var_simples);
}

/* 
	Passar ponteiro já alocado para atributos variáveis da categoria 
	A variável de categoria informa qual o tipo do atributo variável
*/
void atribui_simbolo (simbolo_t *simb, char *ident, unsigned short int cat, unsigned short int niv, void *av){
	simb->identificador = ident;
	simb->categoria = cat;
	simb->nivel = niv;
	simb->atributos_var = av;
}

void tab_simbolos_inic (tab_simbolos_t *tab){
	tab->pilha = NULL;
	tab->tam = 0;
	tab->alloc_tam = 0;
}

/* 
	TODO: Ainda tem que ver alocação dinâmica nos atributos variáveis
*/
void tab_simbolos_destroi (tab_simbolos_t *tab){
	for (unsigned int i = 0; i < tab->tam; ++i){
		if (tab->pilha[i].identificador) free(tab->pilha[i].identificador);
		if (tab->pilha[i].atributos_var) free(tab->pilha[i].atributos_var); // Não funciona pra procedimentos.
	}
	free(tab->pilha);
}

void tab_simbolos_insere (tab_simbolos_t *tab, simbolo_t *simb){
	if (tab->alloc_tam == tab->tam)
		tab->pilha = realloc(tab->pilha, (tab->alloc_tam + ALLOC_STEP) * sizeof(simbolo_t));
	
	memcpy(&tab->pilha[tab->tam], simb, sizeof(simbolo_t));
	tab->tam++;
}

/* Se tabela não tem o símbolo, retorna -1 */
int tab_simbolos_busca (tab_simbolos_t *tab, char *ident){
	int it = tab->tam-1;
	while (it >= 0){
		if (!strcmp(tab->pilha[it].identificador, ident)) return it;
		it--;
	}
	return it;
}

void simbolo_destroi_atributos(simbolo_t *simb) {
	if (simb->identificador) free(simb->identificador);
	if (simb->atributos_var){
		if (simb->categoria == VARIAVEL_SIMPLES)
			destroi_var_simples(simb->atributos_var);
		// Falta teste de parametro formal e procedimento
	}
}

/* 
	Talvez mudar para uma alocação de passo binário depois (provavelmente sem tempo irmão) 
	Tem memory leak :/
*/

void tab_simbolos_elimina (tab_simbolos_t *tab, unsigned int n){
	if (n > tab->tam) {
		fprintf(stderr, "Tentaste remover elementos demais da tabela!\n");
		exit(1);
	}

	// Desempilha e libera elemento por elemento
	while (n){
		simbolo_destroi_atributos( &tab->pilha[--tab->tam] );		
		n--;
	}

	// Fase de realocação
	unsigned int exceeding_blocks = (tab->alloc_tam - tab->tam)/ALLOC_STEP;
	if (exceeding_blocks){
		unsigned int novo_tam = tab->alloc_tam - exceeding_blocks*ALLOC_STEP;
		tab->pilha = realloc(tab->pilha, novo_tam * sizeof(simbolo_t) );
		tab->alloc_tam = novo_tam;
	}
}
