#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

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
