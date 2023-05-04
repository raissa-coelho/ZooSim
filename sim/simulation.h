#ifndef ZOOSIM_SIMULATION_H
#define ZOOSIM_SIMULATION_H

#include "data.h"
#include <unistd.h>

// Funções que simulam as rotinas diárias dos animais
void* animal_thread(void* arg, Comedouro *comedouro);
void exibir_animal(Animal* animal);
void alimentar_animal(Animal* animal, Comedouro* comedouro);
void dormir_animal(Animal* animal);

// Funções que simulam as rotinas diárias dos veterinários
int verifica_comedouros(const int *arr, int count, Comedouro *comedouros);
void* preenche_comedouro(Comedouro *comedouro, Estoque *estoque);
void* veterinario_thread(void* arg, int vet_id);
void* fornecedor_thread(Fornecedor *fornecedor, Estoque *estoque);

// Função que coordena as atividades diárias do zoológico
void* coordinator_thread(void* arg);

// Função para simular o zoológico
void simular_zoologico(Zoologico* zoologico, int num_dias);

#endif //ZOOSIM_SIMULATION_H
