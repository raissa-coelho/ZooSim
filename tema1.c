#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <conio.h>
#include "data/data.h"
#include "print/print.h"

int parseInput(char *arg, char* type,  int* target){
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

    if(argc <= 0){
        fprintf(stderr, "Entrada invalida");
    }else {
        parseInput(argv[0], "%i", &execucao_padrao);
        if (execucao_padrao != 1) {
            if (argc != 6) {
                fprintf(stderr, "Entrada invalida");
            } else {
                parseInput(argv[1], "%i", &leoes);
                parseInput(argv[2], "%i", &suricatos);
                parseInput(argv[3], "%i", &avestruzes);
                parseInput(argv[4], "%i", &comedouro_capacidade);
                parseInput(argv[5], "%i", &veterinario_padrao);
            }
        }

//    present();
//
//    // gcc tema1.c -o tema1
//    // ./tema1 [arg]
//    printf("Dias: ");
//    int dias = atoi(argv[1]);
//    printf("%d", dias);
//
//    //print_file(dias);
        Zoologico *zoo = cria_zoologico(leoes, suricatos, avestruzes, comedouro_capacidade, 30, 30, 30, veterinario_padrao);
        print_zoo(zoo);
        free_zoo(zoo);
        return 0;
    }
    return 1;
}