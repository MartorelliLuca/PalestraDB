#include "menuGiocatore.h"

int promptMenuGiocatore(){
    int input;
    printBoldRed("Cosa vuoi fare? \n");
    printBoldRed("[1] ");
    printf("ENTRA IN UNA STANZA DI GIOCO\n");
    printBoldRed("[2] ");
    printf("MOSTRA STANZE DISPONIBILI\n");
    printBoldRed("[3] ");
    printf("VISUALIZZA STORICO PARTITE\n");
    printBoldRed("[4] ");
    printf("TORNA AL MENU PRINCIPALE\n");
    printBoldRed("[5] ");
    printf("CLEAN SCREEN\n");
    printBoldRed(">> ");
    if(!getInteger("", &input)){
            return -1;
    }
    return input;
}

int promptMenuStanza(){
    int input;
    printBoldRed("Cosa vuoi fare? \n");
    printBoldRed("[1] ");
    printf("VEDI STATO DI GIOCO\n");
    printBoldRed("[2] ");
    printf("SALTA TURNO\n");
    printBoldRed("[3] ");
    printf("ATTACCA TERRITORIO\n");
    printBoldRed("[4] ");
    printf("POSIZIONA CARRI ARMATI SU TERRITORIO\n");
    printBoldRed("[5] ");
    printf("SPOSTA CARRI ARMATI TRA TERRITORI\n");
    printBoldRed("[6] ");
    printf("MOSTRA ADIACENZE TERRITORIO\n");
    printBoldRed("[7] ");
    printf("VISUALIZZA STORICO PARTITE\n");
    printBoldRed("[8] ");
    printf("ABBANDONA PARTITA (ESCI DALLA STANZA)\n");
    printBoldRed("[9] ");
    printf("CLEAN SCREEN\n");
    printBoldRed(">> ");
    if(!getInteger("", &input)){
            return -1;
    }
    return input;
}