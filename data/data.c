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