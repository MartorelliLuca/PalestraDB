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
    printf("RECUPERA SESSIONE INIZIATA\n");
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

int promptMenuSessione(){
    int input;
    printBoldGreen("Cosa vuoi fare? \n");
    printBoldGreen("[1] ");
    printf("ESEGUI ESERCIZIO\n");
    printBoldGreen("[2] ");
    printf("VISUALIZZA SCHEDA DA FARE\n");
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


bool getUserInput(char *resultBuffer, int bufferSize) {

    printBoldGreen("Inserire Data Assenza [yyyy-mm-dd] >>> ") ;

    //Alloco un buffer di dimensione pari alla massima dimensione valida per l'input più uno per lo \n
    char inputBuffer[bufferSize + 1] ;

    //Lettura al massimo di inputMaxSize - 1 caratteri incluso, se lo trova, il \n
    if (fgets(inputBuffer, bufferSize + 1, stdin) == NULL) {
        printError("Errore Scansione Input") ;
        return false ;
    }

    //Rimozione eventuale \n letto da fgets
    for (int i = 0 ; i < (int) strlen(inputBuffer) ; i++){
        if (inputBuffer[i] == '\n') inputBuffer[i] = '\0' ;
    }
    /*
        Se ho una lunghezza di ciò che ho letto pari al massimo leggibile, 
        significa che sul canale di input è rimasto ALMENO lo \n,
        quindi devo rimuovere il resto dell'input per non leggerlo alla lettura successiva.
        Significa inoltre che ho letto almeno un carattere in più della dimensione massima prevista e quindi l'input
        non è valido
    */

    if ((int) strlen(inputBuffer) == bufferSize) {
        while(getchar() != '\n') ;
        printError("Input Inserito Troppo Lungo") ;
        return false ;
    }

    strcpy(resultBuffer, inputBuffer) ;

    /*
        Aggiunta controllo input non vuoto.
        Vantaggi:
            - evito di ricontrollare ogni volta che la funzione viene chiamata
            - Se viene chiesto un input all'utente ci si aspetta che esso venga inserito. 
            - Se non lo fa c'è un errore e posso ritornare false 
    */
    if (strlen(resultBuffer) == 0) return false ;
    return true ;
}

bool isDateValid(char* dateStr) {
    
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

bool verifyAndParseDate(Date *datePtr, char *dateString) {
    
    if(!isDateValid(dateString)){
        return false;
    }

    char *yearString = strtok(dateString, "-") ;
    char *monthString = strtok(NULL, "-") ;
    char *dayString = strtok(NULL, "-") ;
    if (strlen(yearString) == 4 && strlen(monthString) == 2 && strlen(dayString) == 2) {
        datePtr->year = atoi(yearString) ;
        datePtr->month = atoi(monthString) ;
        datePtr->day = atoi(dayString) ;
        return true ;
    }
    return false ;
}


bool getDateFromUser(Date *datePtr) {
    char dateString[strlen("yyyy-mm-dd") + 1] ;
    if (!(getUserInput(dateString, strlen("yyyy-mm-dd") + 1))) {
        printError("Errore Inserimento Data") ;
        return false ;
    }

    if (!verifyAndParseDate(datePtr, dateString)) {
        printError("Formato della Data Inserita non Valido") ;
        return false ;
    }

    return true ;
}



int promptMenuEsercizi(){
    int input;
    printBoldGreen("Cosa vuoi fare? \n");
    printBoldGreen("[1] ");
    printf("FAI UN'ALTRA SERIE\n");
    printBoldGreen("[2] ");
    printf("VAI AL PROSSIMO ESERCIZIO\n");
    printBoldGreen("[3] ");
    printf("VISUALIZZA SERIE RESTANTI\n");
    printBoldGreen("[4] ");
    printf("CLEAN SCREEN\n");
    printBoldGreen(">> ");
    if(!getInteger("", &input)){
            return -1;
    }
    return input;
}
