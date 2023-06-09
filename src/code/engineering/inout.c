#include "inout.h"

bool getInput(char *requestString, char *resultBuffer, int bufferSize) {

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

bool getPositionArmyInfo(char *terr, int *num_carri){
    if (!getInput("Nome territorio su cui posizionare i carri armati:\n>> ", terr, 46)) {
        printError("Errore Lettura Territorio Su Cui Posizionare Carri Armati") ;
        return false ;
    }
    if (!getInteger("Numero di carri da posizionare:\n>> ", num_carri)) {
        printError("Errore Lettura Numero Carri Armati Da Posizionare") ;
        return false ;
    }
    return true ;
}

bool getAttackInfo(char *terr1, char *terr2, int *num_carri){
    if (!getInput("Nome territorio da cui far partire l'attacco:\n>> ", terr1, 46)) {
        printError("Errore Lettura Territorio Partenza Attacco") ;
        return false ;
    }
    if (!getInput("Nome territorio che si vuole attaccare:\n(NB: deve essere adiacente)\n>> ", terr2, 46)) {
        printError("Errore Lettura Territorio Destinazione Attacco") ;
        return false ;
    }
    if (!getInteger("Numero di carri da schierare in attacco(1-3):\n>> ", num_carri)) {
        printError("Errore Lettura Numero Carri Armati In Attacco") ;
        return false ;
    }
    return true ;
}

bool getMoveArmyInfo(int *num_carri, char *terr1, char *terr2){
    if (!getInput("Nome territorio da cui prendere i carri armati per lo spostamento:\n>> ", terr1, 46)) {
        printError("Errore Lettura Territorio Da Cui Spostare Carri Armati") ;
        return false ;
    }
    if (!getInput("Nome territorio su cui spostare i carri armati:\n(NB: deve essere adiacente)\n>> ", terr2, 46)) {
        printError("Errore Lettura Territorio Su Cui Spostare Carri Armati") ;
        return false ;
    }
    if (!getInteger("Numero di carri da spostare:\n>> ", num_carri)) {
        printError("Errore Lettura Numero Carri Armati Da Spostare") ;
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

bool getRegCredentials(newUser *user){
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

void toUpperCase(char *str){
    int i;
    for(i=0; str[i]!='\0'; i++)
    {
        if(str[i]>='a' && str[i]<='z')
        {
            str[i] = str[i] - 32;
        }
    }
}