#ifndef LISTA_H
#define LISTA_H

typedef struct pokemon {
    int id;
    char* nome;
    int forca_total;
    char* tipo;
    int ataque;
    int defesa;
    int velocidade;
    int geracao;
} Pokemon;

typedef struct no {
    void* dados;
    struct no* proximo;
} No;

typedef struct lista {
    No* inicio;
} Lista;

void imprimir_pokemon(void* dados);
void inicializar_lista(Lista** lista);
void inserir_elemento(Lista** lista, void* dados);
void remover_elemento(Lista** lista, void* dados);
void imprimir_lista(Lista* lista, void (*imprimir_dados)(void* dados));
void liberar_lista(Lista* lista);

#endif
