#include "loginAndRegistrationView.h"

bool promptReg(User *user) {
    printBoldGreen("Inserire le credenziali per registrarsi\n");

    return getRegCredentials(user);

}


bool promptLogin(Credentials *creds) {
    printBoldGreen("Inserire le credenziali\n");

    return getLoginCredentials(creds);

}

int promptInitialMenu(){
    int input;
    printBoldGreen("Cosa vuoi fare? \n");
    printBoldGreen("[1] ");
    printf("LOGIN\n");
    printBoldGreen("[2] ");
    printf("USCIRE\n");
    printBoldGreen(">> ");
    if(!getInteger("", &input)){
            return -1;
    }
    return input;

}