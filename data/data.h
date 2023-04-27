#ifndef ZOOSIM_DATA_H
#define ZOOSIM_DATA_H

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
    Animal* animais;
    int num_animais;
    Comedouro* comedouros;
    int num_comedouros;
    Estoque estoque;
    Veterinario* veterinarios;
    int num_veterinarios;
    Fornecedor fornecedor;
} Zoologico;

#endif //ZOOSIM_DATA_H
