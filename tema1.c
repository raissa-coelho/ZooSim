#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <conio.h>
#include "print/print.h"

void 
main(int argc, char *argv[]){
    
    present();

    // gcc tema1.c -o tema1
    // ./tema1 [arg]
    printf("Dias: ");
    int dias = atoi(argv[1]);
    printf("%d", dias);

    //print_file(dias);
}