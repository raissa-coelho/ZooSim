#include <stdio.h>
#include <stdlib.h>
#include "print.h"

void present(){
    printf("---Animais no Zoo---\n");
    printf("Leões : 4\nSuricatos: 10\nAvestruzes: 7\n");
    printf("---Staff---\nVeterinários: 2\nFornecedor: 1\n");
}

void print_file(int dias){
    FILE *f;
    f = fopen("resultados.txt", "w");
    if (f == NULL){
        printf("Oops!...No file");
        exit(1);
    }
    fprintf(f, "%s", "---Animais no Zoo---\n");
    fprintf(f, "%s", "Leões : 4\nSuricatos: 10\nAvestruzes: 7\n");
    fprintf(f, "%s", "---Staff---\nVeterinários: 2\nFornecedor: 1\n");
    fprintf(f, "%s", "Dias: ");
    fprintf(f, "%d", dias);

    fclose(f);
}
