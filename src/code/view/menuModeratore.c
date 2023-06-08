#include "menuModeratore.h"

int promptMenuModeratore(){
    int input;
    printBoldRed("Cosa vuoi fare? \n");
    printBoldRed("[1] ");
    printf("CREA NUOVA STANZA DI GIOCO\n");
    printBoldRed("[2] ");
    printf("VISUALIZZA REPORT\n");
    printBoldRed("[3] ");
    printf("REGISTRA NUOVO MODERATORE\n");
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