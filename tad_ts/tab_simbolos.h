#ifndef __TAB_SIMBOLOS__
#define __TAB_SIMBOLOS__

#define ALLOC_STEP 1024

typedef struct variavel_simples_av_s {
	unsigned short int tipo;
	unsigned int deslocamento;
} variavel_simples_av_t;

typedef struct simbolo_s {
	char *identificador;
	unsigned short int categoria;
	unsigned short int nivel;
	void *atributos_var;
} simbolo_t;

typedef struct tab_simbolos_s {
	simbolo_t *pilha;
	unsigned int tam;
	unsigned int alloc_tam;
} tab_simbolos_t;

void tab_simbolos_init (tab_simbolos_t *tab);
void tab_simbolos_destroy (tab_simbolos_t *tab);

void tab_simbolos_insere (tab_simbolos_t *tab, simbolo_t *simb);

void tab_simbolos_busca (tab_simbolos_t *tab, char *ident);

void tab_simbolos_elimina (tab_simbolos_t *tab, unsigned int n);


#endif
