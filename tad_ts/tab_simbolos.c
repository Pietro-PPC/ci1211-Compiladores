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

void *novo_parametro_formal(unsigned short int tipo, unsigned int deslocamento, unsigned short int passagem){
	parametro_formal_av_t *ret;
	ret = malloc( sizeof(parametro_formal_av_t) );

	ret->tipo = tipo;
	ret->deslocamento = deslocamento;
	ret->passagem = passagem;

	return (void *) ret;
}

void destroi_parametro_formal(void *parametro_formal){
	if (parametro_formal)
		free(parametro_formal);
}

void *novo_procedimento(const char *rotulo, unsigned short int num_params){
	procedimento_av_t *ret;
	ret = malloc( sizeof(procedimento_av_t) ); 

	ret->rotulo = malloc( strlen(rotulo)+1 ); strcpy(ret->rotulo, rotulo);
	ret->num_params = num_params;

	return (void *) ret;
}

void destroi_procedimento(void *procedimento){
	procedimento_av_t *proc = (procedimento_av_t *) procedimento;
	if (proc){
		if (proc->rotulo) free(proc->rotulo);
		proc->params = NULL;
		free(proc);
	}
}


/* 
	Passar ponteiro já alocado para atributos variáveis da categoria 
	A variável de categoria informa qual o tipo do atributo variável
*/
void atribui_simbolo (simbolo_t *simb, const char *ident, unsigned short int cat, unsigned short int niv, void *av){

	simb->identificador = malloc( strlen(ident)+1 ); strcpy(simb->identificador, ident);
	simb->categoria = cat;
	simb->nivel = niv;
	simb->atributos_var = av;
}

void tab_simbolos_inic (tab_simbolos_t *tab){
	tab->pilha = NULL;
	tab->tam = 0;
	tab->alloc_tam = 0;
}

void simbolo_destroi_atributos(simbolo_t *simb) {
	if (simb->identificador) free(simb->identificador);
	if (simb->atributos_var){
		if (simb->categoria == VARIAVEL_SIMPLES)
			destroi_var_simples(simb->atributos_var);
		else if (simb->categoria == PARAMETRO_FORMAL)
			destroi_parametro_formal(simb->atributos_var);
		else 
			destroi_procedimento(simb->atributos_var);
		
	}
}

void tab_simbolos_destroi (tab_simbolos_t *tab){
	for (unsigned int i = 0; i < tab->tam; ++i)
		simbolo_destroi_atributos( &(tab->pilha[i]) );

	free(tab->pilha);
	tab->tam = 0;
	tab->alloc_tam = 0;
}

// Faz procedimento apontar para posição acima na pilha caso tenha parametros
void atribuir_inicio_params(simbolo_t *simb){
	procedimento_av_t *av = (procedimento_av_t *) simb->atributos_var;

	if (av->num_params)
		av->params = simb+1; // Posição na pilha logo após
	else 
		av->params = NULL;
}

void tab_simbolos_insere (tab_simbolos_t *tab, simbolo_t *simb){
	if (tab->alloc_tam == tab->tam)
		tab->pilha = realloc(tab->pilha, (tab->alloc_tam + ALLOC_STEP) * sizeof(simbolo_t));
	
	if (simb->categoria == PROCEDIMENTO)
		atribuir_inicio_params(simb);

	memcpy(&(tab->pilha[tab->tam]), simb, sizeof(simbolo_t));
	tab->tam++;
}

/* Se tabela não tem o símbolo, retorna -1 */
int tab_simbolos_busca (tab_simbolos_t *tab, char *ident){ 
	int it = tab->tam-1;
	while (it >= 0){
		if (!strcmp(tab->pilha[it].identificador, ident)) return it; // falta testar o nivel
		it--;
	}
	return it;
}

/* 
	Tem memory leak :/
*/
void tab_simbolos_elimina (tab_simbolos_t *tab, unsigned int n){
	if (n > tab->tam) {
		fprintf(stderr, "Tentaste remover elementos demais da tabela!\n");
		exit(1);
	}

	// Desempilha e libera elemento por elemento
	while (n){
		tab->tam--;
		simbolo_destroi_atributos( &(tab->pilha[tab->tam]) );
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
