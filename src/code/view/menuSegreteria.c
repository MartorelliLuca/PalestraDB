#include "menuSegreteria.h"

int promptMenuSegreteria(){
    int input;
    printBoldGreen("Cosa vuoi fare? \n");
    printBoldGreen("[1] ");
    printf("AGGIUNGI NUOVO CLIENTE\n");
    printBoldGreen("[2] ");
    printf("AGGIUNGI NUOVO PERSONAL TRAINER\n");
    printBoldGreen("[3] ");
    printf("AGGIUNGI ESERCIZIO\n");
    printBoldGreen("[4] ");
    printf("MOSTRA TUTTI GLI ESERCIZI DELLA PALESTRA\n");
    printBoldGreen("[5] ");
    printf("TORNA AL MENU PRINCIPALE\n");
    printBoldGreen("[6] ");
    printf("CLEAN SCREEN\n");
    printBoldGreen(">> ");
    if(!getInteger("", &input)){
            return -1;
    }
    return input;
}