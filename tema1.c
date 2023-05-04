#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <conio.h>
#include "data/data.h"
#include "print/print.h"

int main(int argc, char *argv[]){
    
//    present();
//
//    // gcc tema1.c -o tema1
//    // ./tema1 [arg]
//    printf("Dias: ");
//    int dias = atoi(argv[1]);
//    printf("%d", dias);
//
//    //print_file(dias);
    Zoologico *zoo = cria_zoologico(4,10, 7, 30, 30,30,30, 1);
    print_zoo(zoo);
    return 0;
}