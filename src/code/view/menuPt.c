#include "menuPt.h"


int promptMenuPt(){
    int input;
    printBoldGreen("Cosa vuoi fare? \n");
    printBoldGreen("[1] ");
    printf("ARCHIVIA UNA SCHEDA\n");
    printBoldGreen("[2] ");
    printf("CREA UNA NUOVA SCHEDA\n");
    printBoldGreen("[3] ");
    printf("MODIFICA LA SCHEDA, DI UN MIO CLIENTE, NON COMPLETATA\n");
    printBoldGreen("[4] ");
    printf("FAI UN REPORT SUI CLIENTI\n");
    printBoldGreen("[5] ");
    printf("MOSTRA LA SCHEDA DI UN QUALUNQUE CLIENTE\n");
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


bool convertDateFromDb(Date *datePtr, char *dateString) {
    char *cancella;
    char *yearString = strtok(dateString, "-") ;
    printf("GIORNO: %s\n", yearString);
    char *monthString = strtok(NULL, "-") ;
    printf("MESE: %s\n", monthString);
    char *dayString = strtok(NULL, "-") ;
    printf("GIORNO: %s\n", dayString);
    printf("%s", dateString);
    fflush(stdout);
    sleep(5);
    if (strlen(yearString) == 4 && strlen(monthString) == 2 && strlen(dayString) == 2) {
        datePtr->year = atoi(yearString) ;
        datePtr->month = atoi(monthString) ;
        datePtr->day = atoi(dayString) ;
        fgets(cancella, 10, stdin);
        return true ;
    }
    return false ;

    return true ;
}