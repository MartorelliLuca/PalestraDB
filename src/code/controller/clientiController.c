#include "clientiController.h"

#define EXERCISE_MAX_SIZE 31



//[3] MOSTRA SCHEDE ARCHIVIATE
static bool mostraSchedaArchiviata(User *loggedUser){
    int num_schede;
    Date *date = malloc(sizeof(Date));
    if (date == NULL) {
        printf("Errore: impossibile allocare memoria per la struttura date.\n");
        exit(EXIT_FAILURE);
    }
    printSuccess("-- ECCO LE TUE SCHEDE ARCHIVIATE --");
    if(showOldRoutines(loggedUser, &num_schede)){
        printf("\n\nHai %d schede archiviate\n\n", num_schede);
        if(!getDateFromUser(date)){
            return false;
        }
        scegliSchedaArchiviata(loggedUser, date);
        return true;
    }else{
        return false;
    }
}

//[2] MOSTRA SCHEDA ATTIVA
static bool mostraSchedaAttiva(User *loggedUser){
    printSuccess("-- ECCO LA TUA SCHEDA ATTIVA --");
    if (displayNewRoutine(loggedUser))
    {
        return true;
    }
    else
    {
        return false;
    }
}


static bool staiEseguendo(workoutCustomer *workUser, char *esercizio, int serieEsercizio){
    bool prev_error = false;
    int input, failed_attempts, serie=serieEsercizio;
clean_up:
    clearScreen();
    showMyTitle();
    while(true)
    {
        printBoldGreen("SEI ARRIVATO ALLA SERIE N°");
        printf("\033[1;32m%d\033[0m", serie);
        printf("\033[1;32m per l'esercizio: %s\033[0m\n", esercizio);
    
        if(prev_error){
            printError("\t Ripristino menu dopo troppi tentativi errati\n\t Stai più attento!");
            prev_error = false;
        }
        if(failed_attempts == 5){
            prev_error = true;
            goto clean_up;
        }
        input = promptMenuEsercizi();
        switch (input)
        {
        case 1:
            if(!addSetToExercise(workUser, esercizio, &serie)){
                return true;
            }
            printf("%d", serie);
            serie++;
            printSuccess("SERIE AGGIUNTA CON SUCCESSO\n");
            break;
        case 2:                                                     //Termina prima esercizio
            return true;
        case 3:
            if(!displayMissingSets(workUser, esercizio)){
                failed_attempts ++;
            }
            break;
        case 4:
            goto clean_up;
        default:
            printError("Scegli tra le opzioni proposte!");
            failed_attempts ++;
            break;
        }
    }  
}

//[1] ESEGUI ESERCIZIO
static bool eseguiEsercizio(workoutCustomer *workUser){
    puts("");
    puts("");
    showMyTitle();
    char esercizio[EXERCISE_MAX_SIZE];
    int serieEsercizio, len;
    printBoldGreen("QUALE ESERCIZIO VUOI ESEGUIRE?\n");
    fgets(esercizio, EXERCISE_MAX_SIZE, stdin);
    len = strlen(esercizio);
    if (len > 0 && esercizio[len - 1] == '\n') {
        esercizio[len - 1] = '\0';
    }
    if(len>EXERCISE_MAX_SIZE){
        while(getchar() != '\n') ;
    }
    if(performExercise(workUser, esercizio)){
        serieEsercizio = 1;
        staiEseguendo(workUser, esercizio, serieEsercizio);
        return true;
    }else{
        return false;
    }
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
            if(!displayNewRoutine(loggedUser)){
                failed_attempts ++;
            }
            break;
        case 3:
            if(!displayMissingExercises(workUser)){                         //visualizza Esercizi Mancanti
                failed_attempts ++;
            }
            break;
        case 4:
            if(!endWorkout(workUser)){                                      //GUARDA LEAVE MATCH
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