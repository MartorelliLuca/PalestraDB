#include "menuPt.h"


int promptMenuPt(){
    int input;
    printBoldGreen("Cosa vuoi fare? \n");
    printBoldGreen("[1] ");
    printf("ARCHIVIA UNA SCHEDA\n");
    printBoldGreen("[2] ");
    printf("CREA UNA NUOVA SCHEDA\n");
    printBoldGreen("[3] ");
    printf("TORNA AL MENU PRINCIPALE\n");
    printBoldGreen("[4] ");
    printf("CLEAN SCREEN\n");
    printBoldGreen(">> ");
    if(!getInteger("", &input)){
            return -1;
    }
    return input;
}