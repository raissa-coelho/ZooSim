#ifndef ZOOSIM_SIMULATION_H
#define ZOOSIM_SIMULATION_H

#include "data.h"
#include <unistd.h>

struct animal_args{
    Animal *animal;
    Comedouro *comedouro;
} typedef AnimalArgs;

struct fornecedor_args{
    Fornecedor *fornecedor;
    Estoque *estoque;
} typedef FornecedorArgs;

struct veterinario_args{
    Zoologico *zoologico;
    int vet_id;
} typedef VeterinarioArgs;


// Funções que simulam as rotinas diárias dos animais
void* animal_thread(void* arg);
void exibir_animal(Animal* animal);
void alimentar_animal(Animal* animal, Comedouro* comedouro);
void dormir_animal(Animal* animal);

// Funções que simulam as rotinas diárias dos veterinários
int verifica_comedouros(const int *arr, int count, Comedouro *comedouros);
void* preenche_comedouro(Comedouro *comedouro, Estoque *estoque);
void* veterinario_thread(void* arg);
void* fornecedor_thread(void* arg);

// Função que coordena as atividades diárias do zoológico
void* coordinator_thread(void* arg);

// Função para simular o zoológico
void simular_zoologico(Zoologico* zoologico, int num_dias);

#endif //ZOOSIM_SIMULATION_H
