#include "clientiController.h"

#define EXERCISE_MAX_SIZE 20 + 1

char *g_username;
char *g_codFiscale;


//[3] MOSTRA SCHEDE ARCHIVIATE
static bool mostraSchedaArchiviata(User *loggedUser){
    int num_schede;
    printSuccess("-- ECCO LE TUE SCHEDE ARCHIVIATE --");
    if(showOldRoutines(loggedUser, &num_schede)){
        printf("\n\nHai %d schede archiviate\n\n", num_schede);
        printBoldGreen("\n\nVuoi sceglierne una?\n\n");
        if(!promptMenuSchedeArchiviate(loggedUser)){
            printError("FATTO TROPPI ERRORI, STAI PIU' ATTENTO.\n");
            return false;
        }
        printf("%s", loggedUser->dataInizioScheda);
        scegliSchedaArchiviata(loggedUser);
        return true;
    }else{
        return false;
    }
}


//[2] MOSTRA SCHEDA ATTIVA
static bool mostraSchedaAttiva(User *loggedUser){
    printSuccess("-- ECCO LA TUA SCHEDA ATTIVA --");
    if (visualizzaSchedaAttiva(loggedUser))
    {
        return true;
    }
    else
    {
        return false;
    }
}


//[1] ESEGUI ESERCIZIO
static bool eseguiEsercizio(workoutCustomer *workUser){
    char esercizio[EXERCISE_MAX_SIZE];
    printprintBoldGreen("QUALE ESERCIZIO VUOI ESEGUIRE?\n");
    fgets(esercizio, EXERCISE_MAX_SIZE + 1, stdin);
    if(performExercise(workUser, esercizio)){
        printSuccess("-- GENERAZIONE STATO DI GIOCO TERMINATA --");
        return true;
    }else{
        return false;
    }
}

//[3] ATTACCA TERRITORIO
static bool attaccaTerritorio(){
    char nomeTerritorio1[VARCHAR45];
    char nomeTerritorio2[VARCHAR45];
    int num_army;
    int num_army_loss_attack;
    int num_army_loss_defense;
    int is_conquered;
    int i_won;
    do{
        memset(&nomeTerritorio1, 0, sizeof(nomeTerritorio1));
        memset(&nomeTerritorio2, 0, sizeof(nomeTerritorio2));
        memset(&num_army, 0, sizeof(num_army));
        if(getAttackInfo(nomeTerritorio1, nomeTerritorio2, &num_army)){
            //conversione nome territori in uppercase
            toUpperCase(nomeTerritorio1);
            toUpperCase(nomeTerritorio2);
            if(attackTerritory(g_username, &num_army, nomeTerritorio1, nomeTerritorio2, &num_army_loss_attack, &num_army_loss_defense, &is_conquered, &i_won)){
                printAttackResults(nomeTerritorio1,nomeTerritorio2,num_army_loss_attack,num_army_loss_defense);
                puts("");
                puts("");
                if(is_conquered == 1){
                    printConqueredTerritory();
                    puts("");
                    puts("");
                    if(i_won == 1){
                    }
                }
                return true;
            }
        }
        return false;
    }while(true);
}

static bool terminaSessione(workUser){
    return true;
}

//[8] ABBANDONA PARTITA (ESCI DALLA STANZA)
static bool abbandonaPartita(){
    return leaveMatch(g_username);
}

static bool sessioneIniziata(workoutCustomer* workUser, User* loggedUser){
    bool prev_error = false;
clean_up:
    clearScreen();
    showMyTitle();
    printf("\t\t\t\t|‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾|   ORARIO INIZIO: %s\n", workUser->orarioInizio);
    printf("\t\t\t\t|  STAI SVOLGENDO LA TUA SESSIONE  |   DATA SCHEDA:   %s\n", workUser->dataInizioScheda);
	printf("\t\t\t\t|__________________________________|   DATA SESSIONE: %s\n", workUser->dataSessione);
    int input, failed_attempts = 0;
    char * buff;
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
        input = promptMenuSessione();
        switch (input)
        {
        case 1:
            if(!eseguiEsercizio(workUser)){
                failed_attempts ++;
            }
            break;
        case 2:
            if(!visualizzaSchedaAttiva(loggedUser)){
                failed_attempts ++;
            }
            break;
        case 3:
            if(!attaccaTerritorio()){
                failed_attempts ++;
            }
            break;
        case 4:
            if(!terminaSessione(workUser)){                                      //GUARDA LEAVE MATCH
                printf("SESSIONE NON TERMINATA.\n");
                break;
            }
            return true;
        case 5:
            goto clean_up;
        default:
            printError("Scegli tra le opzioni proposte!");
            failed_attempts ++;
            break;
        }
        
    }
    
}


//[1] INIZIA UNA SESSIONE DI ALLENAMENTO
static bool iniziaSessione(User *loggedUser) {
    int input;
    workoutCustomer* workUser = malloc(sizeof(workoutCustomer));
    if (workUser == NULL) {
        printf("Errore: impossibile allocare memoria per la struttura workUser.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(workUser->cf, loggedUser->cf);
    do {
        if (startWorkout(workUser)) {
            if(sessioneIniziata(workUser, loggedUser)){
                free(workUser);
                printSuccess("SESSIONE TERMINATA CON SUCCESSO.\n");
                return true;
            }
            printError("SESSIONE TERMINATA CON ERRORI.\n");
        }
        free(workUser);
        printError("SESSIONE NON INIZATA.\n");
        return false;
    } while (true);
}


void clientiController(char* username){
    bool prev_error = false;
clean_up:
    clearScreen();
    showMyTitle();
    puts("\t\t\t\t|‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾|");
    puts("\t\t\t\t|          AREA  CLIENTI          |");
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
    if(!getCustomerCf(loggedUser)){
        printf("Codice Fiscale non preso.");
        return;
    }
    puts("");
    puts("");
    puts("");
    puts("");
    printf("\033[47m\033[30mCODICE FISCALE: %s\n\n\033[0m", loggedUser->cf);
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
        input = promptMenuClienti();
        switch (input)
        {
        case 1:
            if(!iniziaSessione(loggedUser)){
                failed_attempts ++;
                break;
            }
            goto clean_up;
        case 2:
            if(!mostraSchedaAttiva(loggedUser)){
                failed_attempts ++;
            }
            break;
        case 3:
            if(!mostraSchedaArchiviata(loggedUser)){
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