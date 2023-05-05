#include <stdio.h>
#include "data/data.h"
#include "sim/simulation.h"

int parseInput(char *arg, char* type,  void* target){
    int retVal = sscanf (arg, type, target) != 1;
    if (retVal) {
        fprintf(stderr, "error - not an integer");
    }
    return retVal;
}

int main(int argc, char *argv[]){
    int leoes = 4;
    int suricatos = 10;
    int avestruzes = 7;
    int comedouro_capacidade = 30;
    int veterinario_padrao = 1;
    int execucao_padrao = 1;
    int dias = 1;
    for(int i = 0; i < argc; i++){
        printf("%s ", argv[i]);
    }
    printf("\n");
    if(argc <= 0){
        fprintf(stderr, "Entrada invalida");
        exit(1);
    }else {
        parseInput(argv[1], "%i", &execucao_padrao);
        if (execucao_padrao != 1) {
            if (argc != 8) {
                fprintf(stderr, "Entrada invalida");
                exit(1);
            } else {
                parseInput(argv[2], "%i", &leoes);
                parseInput(argv[3], "%i", &suricatos);
                parseInput(argv[4], "%i", &avestruzes);
                parseInput(argv[5], "%i", &comedouro_capacidade);
                parseInput(argv[6], "%i", &veterinario_padrao);
                parseInput(argv[7], "%i", &dias);
            }
        }

        Zoologico *zoo = cria_zoologico(leoes, suricatos, avestruzes, comedouro_capacidade, 30, 30, 30, veterinario_padrao);
        simular_zoologico(zoo, dias);
        print_zoo(zoo);
        //free_zoo(zoo);
        return 0;
    }
    return 1;
}
