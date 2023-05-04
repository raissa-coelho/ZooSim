#ifndef ZOOSIM_DATA_H
#define ZOOSIM_DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct Animal {
    int tipo; // 1 = leão, 2 = zebra, 3 = girafa, etc.
    int id;
    float qtd_alimento;
    int vezes_comida;
    int horas_sono;
} Animal;

typedef struct Comedouro {
    int tipo_alimento; // 1 = carne, 2 = vegetais, 3 = frutas, etc.
    float qtd_alimento_disp;
    float capacidade_max;
    pthread_mutex_t mutex;
} Comedouro;

typedef struct Estoque {
    float carne_disp;
    float vegetais_disp;
    float frutas_disp;
    // outros tipos de alimentos
} Estoque;

typedef struct Veterinario {
    int id;
    int* comedouros_resp; // lista de identificadores dos comedouros pelos quais é responsável
    int num_comedouros_resp; // número de comedouros pelos quais é responsável
} Veterinario;

typedef struct Fornecedor {
    float carne_entregue;
    float vegetais_entregues;
    float frutas_entregues;
    // outros tipos de alimentos entregues
} Fornecedor;

typedef struct Zoologico {
    Animal* animais; // Lista com os animais, dinamicamente alocada
    int num_animais;
    Comedouro* comedouros; //Lista com os comedouros, dinamicamente alocada
    int num_comedouros;
    Estoque* estoque;
    Veterinario* veterinarios; //Lista com os veterinarios, dinamicamente alocada
    int num_veterinarios;
    Fornecedor* fornecedor;
} Zoologico;

int* sort_animals(int *arr, int len);
Animal* criar_animais(int tipo, int quantidade);
Comedouro* cria_comedouro(int quantidade);
void inicializa_comedouro(Comedouro* comedouro, int tipo_alimento, float capacidade_max, float qtd_alimento_disp);
Estoque* inicializa_estoque(float carne_disp, float vegetais_disp, float frutas_disp);
Veterinario* cria_veterinarios(int tamanho);
void inicializa_veterinario(Veterinario* vet, int num_comedouros_resp, const int* comedouros_resp);
Fornecedor* inicializa_fornecedor(float carne_entregue, float vegetais_entregues, float frutas_entregues);
Zoologico* cria_zoologico(int num_leoes, int num_suricatos, int num_avestruses, float capacidade_max_comedouro, float carne_inicial, float vegetais_iniciais, float frutas_iniciais, int vet_padrao);
void print_zoo(Zoologico* zoo);
void free_zoo(Zoologico* zoo);

#endif //ZOOSIM_DATA_H
