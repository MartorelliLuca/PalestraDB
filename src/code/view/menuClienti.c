#include "menuClienti.h"

int promptMenuClienti(){
    int input;
    printBoldGreen("Cosa vuoi fare? \n");
    printBoldGreen("[1] ");
    printf("INIZIA UNA SESSIONE DI ALLENAMENTO\n");
    printBoldGreen("[2] ");
    printf("VISUALIZZA SCHEDA ATTIVA\n");
    printBoldGreen("[3] ");
    printf("SCEGLI SCHEDE ARCHIVIATE DA VISUALIZZARE\n");
    printBoldGreen("[4] ");
    printf("TORNA AL MENU PRINCIPALE\n");
    printBoldGreen("[5] ");
    printf("CLEAN SCREEN\n");
    printBoldGreen(">> ");
    if(!getInteger("", &input)){
            return -1;
    }
    return input;
}

int promptMenuStanza(){
    int input;
    printBoldGreen("Cosa vuoi fare? \n");
    printBoldGreen("[1] ");
    printf("VEDI STATO DI GIOCO\n");
    printBoldGreen("[2] ");
    printf("SALTA TURNO\n");
    printBoldGreen("[3] ");
    printf("ATTACCA TERRITORIO\n");
    printBoldGreen("[4] ");
    printf("POSIZIONA CARRI ARMATI SU TERRITORIO\n");
    printBoldGreen("[5] ");
    printf("SPOSTA CARRI ARMATI TRA TERRITORI\n");
    printBoldGreen("[6] ");
    printf("MOSTRA ADIACENZE TERRITORIO\n");
    printBoldGreen("[7] ");
    printf("VISUALIZZA STORICO PARTITE\n");
    printBoldGreen("[8] ");
    printf("ABBANDONA PARTITA (ESCI DALLA STANZA)\n");
    printBoldGreen("[9] ");
    printf("CLEAN SCREEN\n");
    printBoldGreen(">> ");
    if(!getInteger("", &input)){
            return -1;
    }
    return input;
}