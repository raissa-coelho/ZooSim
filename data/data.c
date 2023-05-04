#include <stdio.h>
#include <stdlib.h>
#include "data.h"

Animal* criar_animais(int tipo, int quantidade) {
    Animal* animais = (Animal*) malloc(quantidade * sizeof(Animal));
    if (animais == NULL) {
        fprintf(stderr,"Erro: não foi possível alocar memória para os animais\n");
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
                fprintf(stderr,"Erro: tipo de animal inválido\n");
                free(animais);
                return NULL;
        }

        animais[i].id = i + 1;
        animais[i].vezes_comida = 0;
    }

    return animais;
}

Comedouro* cria_comedouro(int quantidade) {
    Comedouro* comedouros = calloc(quantidade, sizeof(Comedouro));
    if (comedouros == NULL) {
        fprintf(stderr, "Erro: falha na alocacao de memoria\n");
        return NULL;
    }

    // set default values for each comedouro
    for (int i = 0; i < quantidade; i++) {
        comedouros[i].tipo_alimento = 0;
        comedouros[i].capacidade_max = 0.0f;
        comedouros[i].qtd_alimento_disp = 0.0f;
    }

    return comedouros;
}

void inicializa_comedouro(Comedouro* comedouro, int tipo_alimento, float capacidade_max, float qtd_alimento_disp) {
    if (comedouro == NULL) {
        fprintf(stderr, "Erro: o ponteiro do comedouro eh nulo\n");
        exit(1);
    }

    comedouro->tipo_alimento = tipo_alimento;
    comedouro->capacidade_max = capacidade_max;
    comedouro->qtd_alimento_disp = qtd_alimento_disp;
}

Estoque* inicializa_estoque(float carne_disp, float vegetais_disp, float frutas_disp) {
    Estoque* estoque = malloc(sizeof(Estoque));
    if (estoque == NULL) {
        fprintf(stderr, "Erro: falha na alocacao de memoria\n");
        return NULL;
    }

    estoque->carne_disp = carne_disp;
    estoque->vegetais_disp = vegetais_disp;
    estoque->frutas_disp = frutas_disp;
    // inicializa outros tipos de alimentos

    return estoque;
}

// Inicializa uma lista de veterinários vazia
Veterinario* cria_veterinarios(int tamanho) {
    Veterinario* lista = malloc(sizeof(Veterinario) * tamanho);
    if (lista == NULL) {
        fprintf(stderr, "Erro ao alocar memória para lista de veterinários\n");
        exit(1);
    }
    for (int i = 0; i < tamanho; i++) {
        lista[i].id = i;
        lista[i].comedouros_resp = NULL;
        lista[i].num_comedouros_resp = 0;
    }
    return lista;
}

// Inicializa e aloca memória para um veterinário
void inicializa_veterinario(Veterinario* vet, int num_comedouros_resp, const int* comedouros_resp) {
    vet->num_comedouros_resp = num_comedouros_resp;
    vet->comedouros_resp = malloc(sizeof(int) * num_comedouros_resp);
    if (vet->comedouros_resp == NULL) {
        fprintf(stderr, "Erro ao alocar memória para lista de comedouros responsáveis do veterinário\n");
        exit(1);
    }
    for (int i = 0; i < num_comedouros_resp; i++) {
        vet->comedouros_resp[i] = comedouros_resp[i];
    }
}

Fornecedor* inicializa_fornecedor(float carne_entregue, float vegetais_entregues, float frutas_entregues) {
    Fornecedor* fornecedor = malloc(sizeof(Fornecedor));
    if (fornecedor == NULL) {
        fprintf(stderr, "Error: unable to allocate memory for fornecedor\n");
        return NULL;
    }
    fornecedor->carne_entregue = carne_entregue;
    fornecedor->vegetais_entregues = vegetais_entregues;
    fornecedor->frutas_entregues = frutas_entregues;
    // initialize other types of delivered food
    return fornecedor;
}

Zoologico* cria_zoologico(int num_leoes, int num_suricatos, int num_avestruses, int qtd_comedouros, float capacidade_max_comedouro, float carne_inicial, float vegetais_iniciais, float frutas_iniciais, int num_veterinarios) {
    Zoologico *zoo = NULL;

    zoo = (Zoologico*) malloc(sizeof (Zoologico));
    if(zoo == NULL){
        fprintf(stderr,"Erro: não foi possível alocar memória para os animais\n");
        exit(1);
    }

    // Inicializa os animais
    zoo->animais = (Animal*) malloc((num_leoes + num_suricatos + num_avestruses) * sizeof(Animal));
    if (zoo->animais == NULL) {
        fprintf(stderr,"Erro: não foi possível alocar memória para os animais\n");
        exit(1);
    }
    zoo->num_animais = num_leoes + num_suricatos + num_avestruses;

    Animal* leoes = criar_animais(1, num_leoes);
    Animal* suricatos = criar_animais(2, num_suricatos);
    Animal* avestruzes = criar_animais(3, num_avestruses);

    // Concatena os animais criados em uma única lista de animais
    for (int i = 0; i < num_leoes; i++) {
        zoo->animais[i] = leoes[i];
    }
    for (int i = 0; i < num_suricatos; i++) {
        zoo->animais[num_leoes + i] = suricatos[i];
    }
    for (int i = 0; i < num_avestruses; i++) {
        zoo->animais[num_leoes + num_suricatos + i] = avestruzes[i];
    }

    free(leoes);
    free(suricatos);
    free(avestruzes);

    // Inicializa os comedouros
    zoo->num_comedouros = qtd_comedouros;
    zoo->comedouros = cria_comedouro(qtd_comedouros);
    if (zoo->comedouros == NULL) {
        fprintf(stderr, "Erro: falha na alocacao de memoria para os comedouros\n");
        exit(1);
    }
    for (int i = 0; i < qtd_comedouros; i++) {
        inicializa_comedouro(&(zoo->comedouros[i]), 0, capacidade_max_comedouro, 0.0f);
    }

    // Inicializa o estoque
    zoo->estoque = inicializa_estoque(carne_inicial, vegetais_iniciais, frutas_iniciais);

    if (zoo->estoque == NULL) {
        fprintf(stderr, "Erro: falha na alocacao de memoria\n");
        exit(1);
    }

    // Inicializa os veterinarios
    Veterinario* veterinarios = cria_veterinarios(num_veterinarios);
    if (veterinarios == NULL) {
        fprintf(stderr, "Erro: falha na alocacao de memoria\n");
        exit(1);
    }
    zoo->veterinarios = veterinarios;
    zoo->num_veterinarios = num_veterinarios;

    // Inicializa o fornecedor
    Fornecedor* fornecedor = inicializa_fornecedor(0, 0, 0);
    if (fornecedor == NULL) {
        fprintf(stderr, "Erro: não foi possível inicializar o fornecedor\n");
        exit(1);
    }
    zoo->fornecedor = fornecedor;

    return zoo;
}

void free_zoo(Zoologico* zoo) {
    // Free memory for the animals
    for (int i = 0; i < zoo->num_animais; i++) {
        free(&(zoo->animais[i]));
    }
    free(zoo->animais);

    // Free memory for the comedouros
    for (int i = 0; i < zoo->num_comedouros; i++) {
        free(&(zoo->comedouros[i]));
    }
    free(zoo->comedouros);

    // Free memory for the veterinarios
    for (int i = 0; i < zoo->num_veterinarios; i++) {
        free(zoo->veterinarios[i].comedouros_resp);
        free(&(zoo->veterinarios[i]));
    }
    free(zoo->veterinarios);

    // Free memory for the fornecedor
    free(zoo->fornecedor);

    // Free memory for the estoque
    free(zoo->estoque);
}