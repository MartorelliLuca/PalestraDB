#include "loginAndRegistrationView.h"



bool promptLoginAndRegistration(Credentials *creds) {
    printBoldRed("Inserire le credenziali\n");

    return getCredentials(creds);

}

int promptInitialMenu(){
    int input;
    printBoldRed("Cosa vuoi fare? \n");
    printBoldRed("[1] ");
    printf("LOGIN\n");
    printBoldRed("[2] ");
    printf("USCIRE\n");
    printBoldRed(">> ");
    if(!getInteger("", &input)){
            return -1;
    }
    return input;

}