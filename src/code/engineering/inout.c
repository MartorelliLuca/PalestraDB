#include "inout.h"


bool getInput(char *requestString, char *resultBuffer, int bufferSize){

    printBoldGreen(requestString) ;

    // +1 is for \n special char
    char inputBuffer[bufferSize + 1] ;

    //reading inputMaxSize - 1 chars \n included, if any
    if (fgets(inputBuffer, bufferSize + 1, stdin) == NULL) {
        printError("couldn't scan input") ;
        return false ;
    }

    //removing \n, if any
    for (int i = 0 ; i < (int) strlen(inputBuffer) ; i++) {
        if (inputBuffer[i] == '\n') {
            inputBuffer[i] = '\0' ;
        }
    } 

    if ((int) strlen(inputBuffer) == bufferSize) {
        while(getchar() != '\n') ;
        printError("input exceeds max buffer size") ;
        return false ;
    }

    strcpy(resultBuffer, inputBuffer) ;

    //check for empty input
    if (strlen(resultBuffer) == 0) {
        return false ;
    }
    return true ;
}

bool getLoginCredentials(Credentials *creds){
    if (!getInput("Username: ", creds->username, USERNAME_MAX_SIZE)) {
        printError("Errore Lettura Username") ;
        return false ;
    }
    if (!getInput("Password: ", creds->password, PASSWORD_MAX_SIZE)) {
        printError("Errore Lettura Password") ;
        return false ;
    }
    return true ;
}

bool getRegCredentials(User *user){
    if (!getInput("Codice Fiscale: ", user->cf, USERNAME_MAX_SIZE)) {
        printError("Errore Lettura Codice Fiscale") ;
        return false ;
    }
    if (!getInput("Nome: ", user->nome, NOME_MAX_SIZE)) {
        printError("Errore Lettura Nome");
        return false ;
    }

    if (!getInput("Cognome: ", user->cognome, COGNOME_MAX_SIZE)) {
        printError("Errore Lettura Cognome");
        return false ;
    }

    if (!getInput("Username: ", user->username, USERNAME_MAX_SIZE)) {
        printError("Errore Lettura Username");
        return false ;
    }

    if (!getInput("Password: ", user->password, PASSWORD_MAX_SIZE)) {
        printError("Errore Lettura Password");
        return false ;
    }
    return true ;
}

bool convertDateFromDb(Date *datePtr, char *dateString){
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

    return true ;
}

bool getInteger(char* domanda, int *integerPtr) {
    char integerStringBuff[11 + 1] ;
    if (!getInput(domanda, integerStringBuff, 11 + 1)) {
        printError("Errore Inserimento Codice Numerico") ;
        return false ;
    }
    char *checkString = "\0" ;
    errno = 0;
    long longInput = strtol(integerStringBuff, &checkString, 10) ;
    if (errno != 0) {
        printError("Numero Non Valido") ;
        errno = 0 ;
        return false ;
    }
    if (*checkString != '\0') {
        printError("Numero Non Valido") ;
        errno = 0 ;
        return false ;
    } ;
    if (longInput > INT_MAX || longInput < INT_MIN) return false ;
    *integerPtr = (int) longInput ;
    return true ;
}