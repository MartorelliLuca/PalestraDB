#include "menuClienti.h"

int promptMenuClienti(){
    int input;
    printBoldGreen("Cosa vuoi fare? \n");
    printBoldGreen("[1] ");
    printf("INIZIA UNA SESSIONE DI ALLENAMENTO\n");
    printBoldGreen("[2] ");
    printf("VISUALIZZA SCHEDA ATTIVA\n");
    printBoldGreen("[3] ");
    printf("MOSTRA SCHEDE ARCHIVIATE DA VISUALIZZARE\n");
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

int promptMenuSessione(){
    int input;
    printBoldGreen("Cosa vuoi fare? \n");
    printBoldGreen("[1] ");
    printf("ESEGUI ESERCIZIO\n");
    printBoldGreen("[2] ");
    printf("VISCUALIZZA SCHEDA DA FARE\n");
    printBoldGreen("[3] ");
    printf("VISUALIZZA ESERCIZI RESTANTI\n");
    printBoldGreen("[4] ");
    printf("TERMINA SESSIONE\n");
    printBoldGreen("[5] ");
    printf("CLEAN SCREEN\n");
    printBoldGreen(">> ");
    if(!getInteger("", &input)){
            return -1;
    }
    return input;
}

bool isDateValid(const char* dateStr) {
    
    // Verifica il formato
    if (dateStr[4] != '-' || dateStr[7] != '-') {
        return false;
    }

    // Verifica i valori numerici
    int year, month, day;
    if (sscanf(dateStr, "%d-%d-%d", &year, &month, &day) != 3) {
        return false;
    }

    // Verifica i limiti dei valori
    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }

    // Verifica mesi con 30 giorni
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return false;
    }

    // Verifica febbraio
    if (month == 2) {
        if (day > 28) {
            return false;
        }
    }
    return true;
}


bool promptMenuSchedeArchiviate(User *loggedUser) {
    char date[11];
    int fails = 0;
    while (1) {
init:
        if (fails == 3) {
            return false;
        }        
        printBoldGreen("Quale vuoi vedere?\n");
        printBoldGreen("Per favore inserisci il formato data in questo modo: yyyy-mm-dd\n");
        printBoldGreen(">> ");
        fgets(date, sizeof(date), stdin);

        if (isDateValid(date)) {
            strcpy(loggedUser->dataInizioScheda, date);
            break;
        }
        printError("LA DATA INSERITA NON HA SENSO");
        fails++;
        if(strlen(date)<11){
            goto init;
        }
        while ((getchar()) != '\n') {}
    }
    return true;
}

int promptMenuSessione();
