#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char* nome;
    int forca_total;
    char* tipo;
    int ataque;
    int defesa;
    int velocidade;
    int geracao;

} Pokemon;

typedef struct No {
    void* dados;
    struct No* proximo;
} No;

typedef struct {
    No* inicio;
} Lista;

void inicializar_lista(Lista** lista) {
    *lista = (Lista*)malloc(sizeof(Lista));
    (*lista)->inicio = NULL;
}

void liberar_lista(Lista* lista) {
    No* atual = lista->inicio;
    while (atual != NULL) {
        No* proximo = atual->proximo;
        free(atual->dados);
        free(atual);
        atual = proximo;
    }
    free(lista);
}

void imprimir_pokemon(void* dados) {
    Pokemon* pokemon = (Pokemon*)dados;
    printf("ID: %d\n", pokemon->id);
    printf("Nome: %s\n", pokemon->nome);
    printf("Força Total: %d\n", pokemon->forca_total);
    printf("Tipo: %s\n", pokemon->tipo);
    printf("Ataque: %d\n", pokemon->ataque);
    printf("Defesa: %d\n", pokemon->defesa);
    printf("Velocidade: %d\n", pokemon->velocidade);
    printf("Geração: %d\n", pokemon->geracao);
    printf("-------------------------------\n");
}

void imprimir_lista(Lista* lista, void (*imprimir_dados)(void*)) {
    No* atual = lista->inicio;
    while (atual != NULL) {
        imprimir_dados(atual->dados);
        atual = atual->proximo;
    }
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

int main() {
    FILE* file = fopen("dados/pokemon.csv", "r");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    Lista* lista_pokemon;
    inicializar_lista(&lista_pokemon);

    char buffer[1024];
    fgets(buffer, sizeof(buffer), file);

    while (fgets(buffer, sizeof(buffer), file)) {
        Pokemon* pokemon = (Pokemon*)malloc(sizeof(Pokemon));
        if (!pokemon) {
            printf("Erro ao alocar memória.\n");
            break;
        }

        char* id_text = strtok(buffer, ",");
        char* nome_text = strtok(NULL, ",");
        char* total_force_text = strtok(NULL, ",");
        char* tipo_text = strtok(NULL, ",");
        char* ataque_text = strtok(NULL, ",");
        char* defesa_text = strtok(NULL, ",");
        char* velocidade_text = strtok(NULL, ",");
        char* geracao_text = strtok(NULL, ",");

        if (id_text && nome_text && total_force_text && tipo_text && ataque_text && defesa_text && velocidade_text && geracao_text ) {
            pokemon->id = atoi(id_text);
            pokemon->nome = strdup(nome_text);
            pokemon->forca_total = atoi(total_force_text);
            pokemon->tipo = strdup(tipo_text);
            pokemon->ataque = atoi(ataque_text);
            pokemon->defesa = atoi(defesa_text);
            pokemon->velocidade = atoi(velocidade_text);
            pokemon->geracao = atoi(geracao_text);

            inserir_elemento_ordenado(&lista_pokemon, pokemon);
        } else {
            free(pokemon);
            printf("Erro ao ler os dados do arquivo.\n");
            break;
        }
    }

    fclose(file);

    printf("Pokémons:\n");
    imprimir_lista(lista_pokemon, imprimir_pokemon);

    liberar_lista(lista_pokemon);

    return 0;
}
