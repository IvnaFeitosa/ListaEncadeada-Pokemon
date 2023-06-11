#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

void imprimir_pokemon(void* dados) {
    Pokemon* pokemon = (Pokemon*)dados;
    printf("ID: %d\n", pokemon->id);
    printf("Nome: %s\n", pokemon->nome);
    printf("Forca Total: %d\n", pokemon->forca_total);
    printf("Tipo: %s\n", pokemon->tipo);
    printf("Ataque: %d\n", pokemon->ataque);
    printf("Defesa: %d\n", pokemon->defesa);
    printf("Velocidade: %d\n", pokemon->velocidade);
    printf("Geracao: %d\n", pokemon->geracao);
    printf("Regiao: %s\n", pokemon->regiao);
    printf("-----------------\n");
}

void inicializar_lista(Lista** lista) {
    *lista = (Lista*)malloc(sizeof(Lista));
    (*lista)->inicio = NULL;
}

void inserir_elemento_ordenado(Lista** lista, void* dados) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo) {
        novo->dados = dados;

        if ((*lista)->inicio == NULL || ((Pokemon*)dados)->id < ((Pokemon*)((*lista)->inicio->dados))->id) {
            novo->proximo = (*lista)->inicio;
            (*lista)->inicio = novo;
        } else {
            No* atual = (*lista)->inicio;
            while (atual->proximo != NULL && ((Pokemon*)dados)->id > ((Pokemon*)(atual->proximo->dados))->id) {
                atual = atual->proximo;
            }
            novo->proximo = atual->proximo;
            atual->proximo = novo;
        }
    } else {
        printf("\nNão foi possível alocar memória\n");
    }
}

void remover_elemento(Lista** lista, void* dados) {
    if ((*lista)->inicio == NULL) {
        printf("\nLista vazia");
        return;
    } else {
        No* aux = (*lista)->inicio, *anterior = NULL;
        while (aux) {
            if (aux->dados == dados) {
                if (anterior == NULL) {
                    (*lista)->inicio = aux->proximo;
                } else {
                    anterior->proximo = aux->proximo;
                }
                free(aux);
                return;
            }
            anterior = aux;
            aux = aux->proximo;
        }
    }
}

void imprimir_lista(Lista* lista, void (*imprimir_dados)(void* dados)) {
    No* atual = lista->inicio;
    while (atual != NULL) {
        imprimir_dados(atual->dados);
        atual = atual->proximo;
    }
}

void liberar_lista(Lista* lista) {
    No* aux = lista->inicio;
    while (aux) {
        No* proximo = aux->proximo;
        free(aux);
        aux = proximo;
    }
    lista->inicio = NULL;
}
