#include <stdio.h>
#include <stdlib.h>
#include "data.h"

Animal* criar_animais(int tipo, int quantidade) {
    Animal* animais = (Animal*) malloc(quantidade * sizeof(Animal));
    if (animais == NULL) {
        printf("Erro: não foi possível alocar memória para os animais\n");
        return NULL;
    }

    for (int i = 0; i < quantidade; i++) {
        animais[i].tipo = tipo;

        switch (tipo) {
            case 1: // Leão
                animais[i].qtd_alimento = 2.0;
                animais[i].horas_sono = rand() % 5 + 8;
                break;
            case 2: // Suricato
                animais[i].qtd_alimento = 0.5;
                animais[i].horas_sono = rand() % 5 + 6;
                break;
            case 3: // Avestruz
                animais[i].qtd_alimento = 1.5;
                animais[i].horas_sono = rand() % 5 + 4;
                break;
            default:
                printf("Erro: tipo de animal inválido\n");
                free(animais);
                return NULL;
        }

        animais[i].id = i + 1;
        animais[i].vezes_comida = 0;
    }

    return animais;
}

Comedouro inicializa_comedouro(int tipo_alimento, float capacidade_max) {
    Comedouro comedouro;
    comedouro.tipo_alimento = tipo_alimento;
    comedouro.qtd_alimento_disp = 0;
    comedouro.capacidade_max = capacidade_max;
    return comedouro;
}

Estoque inicializa_estoque(float carne_disp, float vegetais_disp, float frutas_disp) {
    Estoque estoque;
    estoque.carne_disp = carne_disp;
    estoque.vegetais_disp = vegetais_disp;
    estoque.frutas_disp = frutas_disp;
    // inicializa outros tipos de alimentos
    return estoque;
}

// Inicializa uma lista de veterinários vazia
Veterinario* inicializa_lista_veterinarios(int tamanho) {
    Veterinario* lista = malloc(sizeof(Veterinario) * tamanho);
    if (lista == NULL) {
        printf("Erro ao alocar memória para lista de veterinários\n");
        exit(1);
    }
    for (int i = 0; i < tamanho; i++) {
        lista[i].id = 0;
        lista[i].comedouros_resp = NULL;
        lista[i].num_comedouros_resp = 0;
    }
    return lista;
}

// Inicializa e aloca memória para um veterinário
void inicializa_veterinario(Veterinario* vet, int id, int num_comedouros_resp, int* comedouros_resp) {
    vet->id = id;
    vet->num_comedouros_resp = num_comedouros_resp;
    vet->comedouros_resp = malloc(sizeof(int) * num_comedouros_resp);
    if (vet->comedouros_resp == NULL) {
        printf("Erro ao alocar memória para lista de comedouros responsáveis do veterinário\n");
        exit(1);
    }
    for (int i = 0; i < num_comedouros_resp; i++) {
        vet->comedouros_resp[i] = comedouros_resp[i];
    }
}

Fornecedor inicializa_fornecedor(float carne_entregue, float vegetais_entregues, float frutas_entregues) {
    Fornecedor fornecedor;
    fornecedor.carne_entregue = carne_entregue;
    fornecedor.vegetais_entregues = vegetais_entregues;
    fornecedor.frutas_entregues = frutas_entregues;
    // inicializa outros tipos de alimentos entregues
    return fornecedor;
}
