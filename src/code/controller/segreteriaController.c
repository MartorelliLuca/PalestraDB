#include "segreteriaController.h"

static bool registraNuovoCliente(){
    newUser user;
    do {
        memset(&user, 0, sizeof(newUser));
        if(promptReg(&user)){
            if(registerNewCustomer(user)){
                printSuccess("Nuovo cliente registrato correttamente");
                return true;
            }
        }
        return false;
    } while (true) ;
}

bool registraNuovoModeratore(){
    Credentials creds;
    do {
        memset(&creds, 0, sizeof(Credentials));
        /*if(promptLogin(&user)){
            if(registerNewCustomer(user)){
                printSuccess("Nuovo moderatore registrato correttamente");
                return true;
            }
        }*/
        return false;
    } while (true) ;
}

static bool vediReport(){
    do {
        printSuccess("-- GENERAZIONE REPORT INIZIATA --");
        if(retrieveReport()){
            printSuccess("-- GENERAZIONE REPORT TERMINATA --");
            return true;
        }
        return false;
    } while (true) ;
}



void segreteriaController(char *username){
    bool prev_error = false;
clean_up:
    clearScreen();
    showMyTitle();
    puts("\t\t\t\t|‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾|");
    puts("\t\t\t\t|         AREA SEGRETERIA         |");
	puts("\t\t\t\t|_________________________________|");
    printf("\t\t\t\t     Bentornat* %s.\n\n",username);
    int input;
    int failed_attempts = 0;
    while(true)
    {
        if(prev_error){
            printError("\t Ripristino menu dopo troppi tentativi errati\n\t Stai più attento!");
            prev_error = false;
        }
        if(failed_attempts == 5){
            prev_error = true;
            goto clean_up;
        }
        input = promptMenuSegreteria();
        switch (input)
        {
        case 1:
            if(!registraNuovoCliente()){
                failed_attempts ++;
            }
            break;
        case 2:
            if(!vediReport()){
                failed_attempts ++;
            }
            break;
        case 3:
            if(!registraNuovoModeratore()){
                failed_attempts ++;
            }
            break;
        case 4:
            return;
        case 5:
            goto clean_up;
        default:
            printError("Scegli tra le opzioni proposte!");
            failed_attempts ++;
            break;
        }
    }
    
}