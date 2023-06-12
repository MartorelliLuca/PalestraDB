#include "ptController.h"
#define CF_MAX_SIZE 20 + 1


bool archiviaScheda(User *loggedUser){

    int len, failed_attempts = 0;
    char Cliente[CF_MAX_SIZE], *cancella;

clean_up:
    clearScreen();
    showMyTitle();
    puts("\t\t\t\t|‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾|");
    puts("\t\t\t\t|       ARCHIVIAZIONE SCHEDA       |");
	puts("\t\t\t\t|__________________________________|");
    
    while(true)
    {
        if(failed_attempts == 5){
            printError("\t Ripristino menu dopo troppi tentativi errati\n\t Stai più attento!");
            return false;
        }
        if(1){ //showAllMyCustomers(loggedUser)
            printBoldGreen("\n\nSeleziona il cliente al quale vuoi archiviare la scheda\n\n");
            fgets(Cliente, CF_MAX_SIZE, stdin);
            len=strlen(Cliente);
            if(len>=18){
                while (getchar() != '\n'){}
                printError("TROPPI CARATTERI INSERITI: UN CODICE FISCALE HA MASSIMO 16 CARATTERI\n\n");
                failed_attempts++;
                goto clean_up;
            }
            if(len<=16){
                printError("POCHI CARATTERI INSERITI: UN CODICE FISCALE HA MASSIMO 16 CARATTERI\n\n");
                failed_attempts++;
                goto clean_up;
            }
            if(Cliente[len-1]=='\n'){
                Cliente[len-1]='\0';
            }
            fgets(cancella, 10, stdin);
            return true;
        }else{
            return false;
        }
    }
}


bool creaNuovaSchedaAttiva(User *loggedUser){
    return true;
}

void ptController(char* username){
    bool prev_error = false;
clean_up:
    clearScreen();
    showMyTitle();
    puts("\t\t\t\t|‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾|");
    puts("\t\t\t\t|      AREA PERSONAL TRAINER      |");
	puts("\t\t\t\t|_________________________________|");
    printf("\t\t\t\t     Bentornato/a %s.\n\n",username);
    int input;
    int failed_attempts = 0;

    User* loggedUser = malloc(sizeof(User));
    if (loggedUser == NULL) {
        printf("Errore: impossibile allocare memoria per la struttura loggedUser.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(loggedUser->username, username);
    if(!getPtCf(loggedUser)){
        printf("Codice Fiscale non preso.");
        return;
    }
    puts("");
    puts("");
    puts("");
    puts("");
    printf("\033[47m\033[30mCODICE FISCALE: %s\033[0m", loggedUser->cf);
    puts("");
    puts("");
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
        input = promptMenuPt();
        switch (input)
        {
        case 1:
            if(!archiviaScheda(loggedUser)){
                failed_attempts ++;
                break;
            }
            goto clean_up;
        case 2:
            if(!creaNuovaSchedaAttiva(loggedUser)){
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