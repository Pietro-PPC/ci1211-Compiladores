#ifndef __TAB_SIMBOLOS__
#define __TAB_SIMBOLOS__

#define ALLOC_STEP 1024

#define CAT_INDEFINIDA 0
#define VARIAVEL_SIMPLES 1
#define PARAMETRO_FORMAL 2
#define PROCEDIMENTO 3

#define PASSAGEM_VALOR 1
#define PASSAGEM_REFERENCIA 2

#define TIPO_INT 1

typedef struct simbolo_s {
	char *identificador;
	unsigned short int categoria;
	unsigned short int nivel;
	void *atributos_var;
} simbolo_t;

typedef struct var_simples_av_s {
	unsigned short int tipo;
	unsigned int deslocamento;
} var_simples_av_t;

typedef struct parametro_formal_av_s {
	unsigned short int tipo;
	unsigned int deslocamento;
	unsigned short int passagem;
} parametro_formal_av_t;

typedef struct procedimento_av_s {
	char *rotulo;
	unsigned short int num_params;
	simbolo_t *params;
} procedimento_av_t;

typedef struct tab_simbolos_s {
	simbolo_t *pilha;
	unsigned int tam;
	unsigned int alloc_tam;
} tab_simbolos_t;


void *nova_var_simples(unsigned short int tipo, unsigned int deslocamento);
void destroi_var_simples(void *var_simples);

void *novo_parametro_formal(unsigned short int tipo, unsigned int deslocamento, unsigned short int passagem);
void destroi_parametro_formal(void *parametro_formal);

void *novo_procedimento(char *rotulo, unsigned short int num_params, simbolo_t *params);
void destroi_procedimento(void *procedimento);

void atribui_simbolo (simbolo_t *simb, char *ident, unsigned short int cat, unsigned short int niv, void *av);
simbolo_t *tab_simbolos_topo(tab_simbolos_t *tab);

void tab_simbolos_inic (tab_simbolos_t *tab);
void tab_simbolos_destroi (tab_simbolos_t *tab);

void tab_simbolos_insere (tab_simbolos_t *tab, simbolo_t *simb);

int tab_simbolos_busca (tab_simbolos_t *tab, char *ident);

void tab_simbolos_elimina (tab_simbolos_t *tab, unsigned int n);


#endif
