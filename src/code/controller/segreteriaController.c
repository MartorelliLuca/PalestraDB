#include "segreteriaController.h"

static bool registraNuovoCliente(){
    clearScreen();
    User user;
    int failed_attempts = 0;
    do {
        showMyTitle();
        puts("\t\t\t\t|‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾|");
	    puts("\t\t\t\t|      REGISTRAZIONE CLIENTE      |");
	    puts("\t\t\t\t|_________________________________|\n");
        if(failed_attempts == 3){
            printError("HAI FATTO TROPPI ERRORI, FAI PIU' ATTENZIONE.");
            return false;
        }
        memset(&user, 0, sizeof(User));
        if(promptReg(&user)){
            if(registerNewCustomer(user)){
                printSuccess("Nuovo cliente registrato correttamente");
                return true;
            }
        }
        failed_attempts ++;
        printf("\033[41mErrore numero %d, su 3 consentiti\033[0m",failed_attempts);

    } while (true) ;
}

static bool registraNuovoPT(){
    User user;
    int failed_attempts = 0;
    do {
        clearScreen();
        showMyTitle();
        puts("\t\t\t\t|‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾|");
	    puts("\t\t\t\t|  REGISTRAZIONE PERSONAL TRAINER  |");
	    puts("\t\t\t\t|__________________________________|\n");
        if(failed_attempts == 3){
            printError("HAI FATTO TROPPI ERRORI, FAI PIU' ATTENZIONE.");
            return false;
        }
        memset(&user, 0, sizeof(User));
        if(promptReg(&user)){
            if(registerNewCustomer(user)){
                printSuccess("Nuovo PT registrato correttamente");
                return true;
            }
        }
        failed_attempts ++;
        printf("\033[41mErrore numero %d\033[0m",failed_attempts);
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
    printf("\t\t\t\t      Bentornata %s.\n\n",username);
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
            if(!registraNuovoPT()){
                failed_attempts ++;
            }
            break;
        case 3:
            return;
        case 4:
            goto clean_up;
        default:
            printError("Scegli tra le opzioni proposte!");
            failed_attempts ++;
            break;
        }
    }
    
}