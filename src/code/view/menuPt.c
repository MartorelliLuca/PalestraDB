#include "menuPt.h"


int promptMenuPt(){
    int input;
    printBoldGreen("Cosa vuoi fare? \n");
    printBoldGreen("[1] ");
    printf("ARCHIVIA UNA SCHEDA\n");
    printBoldGreen("[2] ");
    printf("CREA UNA NUOVA SCHEDA\n");
    printBoldGreen("[3] ");
    printf("MODIFICA SCHEDA NON COMPLETATA\n");
    printBoldGreen("[4] ");
    printf("FAI UN REPORT SUI CLIENTI\n");
    printBoldGreen("[5] ");
    printf("MOSTRA LA SCHEDA DI UN MIO CLIENTE\n");
    printBoldGreen("[6] ");
    printf("MOSTRA TUTTI I MIEI CLIENTI\n");
    printBoldGreen("[7] ");
    printf("TORNA AL MENU PRINCIPALE\n");
    printBoldGreen("[8] ");
    printf("CLEAN SCREEN\n");
    printBoldGreen(">> ");
    if(!getInteger("", &input)){
            return -1;
    }
    return input;
}