#include "ptController.h"
#define CF_MAX_SIZE 20 + 1
#define EXERCISE_MAX_SIZE 30 + 1

bool generaReport(User *loggedUser)
{
    Date *date1 = malloc(sizeof(Date));
    if (date1 == NULL)
    {
        printf("Errore: impossibile allocare memoria per la struttura date1.\n");
        exit(EXIT_FAILURE);
    }
    Date *date2 = malloc(sizeof(Date));
    if (date2 == NULL)
    {
        printf("Errore: impossibile allocare memoria per la struttura date2.\n");
        exit(EXIT_FAILURE);
    }
    printBoldGreen("STAI PER INSERIRE LA PRIMA DATA PER L'INTERVALLO DEL REPORT\n");
    if (!getDateFromUser(date1))
    {
        return false;
    }
    printBoldGreen("STAI PER INSERIRE LA PRIMA DATA PER L'INTERVALLO DEL REPORT\n");
    if (!getDateFromUser(date2))
    {
        return false;
    }
    printSuccess("-- ECCO IL REPORT PER I TUOI CLIENTI --");
    if (!retrieveReport(loggedUser, date1, date2))
    {
        return false;
    }
    free(date1);
    free(date2);
    return true;
}

static bool mostraSchedaAttivaCliente(User *loggedUser, User *cliente)
{
    // piccola modifica per i pt che prima scelgono il cliente e poi vedono la sua scheda
    while (1)
    {
        if (getInput("INSERISCI IL CODICE FISCALE DEL CLIENTE DI CUI DESIDERI VISUALIZZARE LA SCHEDA DI ALLENAMENTO\n>> ", cliente->cf, USERNAME_MAX_SIZE))
        {
            break;
        }
    }
    printf("\n\033[47m\033[30m-- ECCO LA SCHEDA ATTIVA \033[0m");
    printf("\033[47m\033[30mDI %s --\033[0m\n\n", cliente->cf);
    if (displayRoutine(loggedUser, cliente))
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool inserisciAltriEsercizi(char *Cliente, Date *date, int maxPosition){
    clearScreen();
    int numEsercizi;
    char esercizio[EXERCISE_MAX_SIZE], answer[3];
    
    showMyTitle();
    puts("\t\t\t\t|‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾|");
    puts("\t\t\t\t|    INSERIMENTO ALTRI ESERCIZI    |");
    puts("\t\t\t\t|__________________________________|");
    printf("\033[44m\033[0m\n");
    
    if (!getInteger("QUANTI ESERCIZI VUOI METTERE ANCORA NELLA SCHEDA?\n>> ", &numEsercizi))
    {
        return true;
    }
    
    maxPosition++;
    for (int i = 0; i < numEsercizi; i++)
    {
          //prettamente estetico
        puts("");
        puts("");
        printBoldGreen("INSERISCI L'ESERCIZIO NUMERO ");
        printf("\033[1;32m%d\033[0m", maxPosition);
        printBoldGreen(" DELLA SCHEDA\n>> ");
        fgets(esercizio, EXERCISE_MAX_SIZE, stdin);
        esercizio[strcspn(esercizio, "\n")] = '\0';
        
        int serie, ripetizioni;
        while (!getInteger("Inserisci il numero di serie da fare\n>> ", &serie)){}
        while (!getInteger("Inserisci il numero di ripetizioni da fare\n>> ", &ripetizioni)){}

        if (!insertExercise(Cliente, date, esercizio, &maxPosition, &serie, &ripetizioni)){
            printError("ESERCIZIO NON INSERITO CORRETTAMENTE.");
            i--;
        }
        else {
            maxPosition++;
        }
    }
    
    while(1)
    {
        getInput("\n\n\nSEI SODDSFATTO DELLA SCHEDA?\nLA CONSIDERI COMPLETATA?\nPER FAVORE RISPONDI CON SI O NO\n>> ", answer, 3);
        
        if (strcasecmp(answer, "si\0") == 0)
        {
            if(completedRoutine(Cliente, date)){
                printSuccess("LA SCHEDA E' STATA COMPLETATA CON SUCCESSO");
                return true;
            }
            return false;
        }else if (strcasecmp(answer, "no\0") == 0){
            printSuccess("SCHEDA FATTA, MA NON ANCORA COMPLETATA");
            return true;
        }
        else{
            printError("RISPOSTA NON ACCETTABILE");
        }
    }
    
    return true;
}

bool inserisciEsercizi(char *Cliente, Date *date){
    clearScreen();
    int numEsercizi;
    char esercizio[EXERCISE_MAX_SIZE], answer[3];
    
    showMyTitle();
    puts("\t\t\t\t|‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾|");
    puts("\t\t\t\t|       INSERIMENTO ESERCIZI       |");
    puts("\t\t\t\t|__________________________________|");
    printf("\033[44m\033[0m\n");
    
    if (!getInteger("QUANTI ESERCIZI VUOI METTERE NELLA SCHEDA?\n>> ", &numEsercizi))
    {
        return true;
    }
    
    int posizione = 1;
    for (int i = 0; i < numEsercizi; i++)
    {          
        //prettamente estetico
        puts("");
        puts("");
        printBoldGreen("INSERISCI L'ESERCIZIO NUMERO ");
        printf("\033[1;32m%d\033[0m", posizione);
        printBoldGreen(" DELLA SCHEDA\n>> ");
        fgets(esercizio, EXERCISE_MAX_SIZE, stdin);
        esercizio[strcspn(esercizio, "\n")] = '\0';
        
        int serie, ripetizioni;
        while (!getInteger("Inserisci il numero di serie da fare\n>> ", &serie)){}
        while (!getInteger("Inserisci il numero di ripetizioni da fare\n>> ", &ripetizioni)){}

        if (!insertExercise(Cliente, date, esercizio, &posizione, &serie, &ripetizioni)){
            printError("ESERCIZIO NON INSERITO CORRETTAMENTE.");
            i--;
        }
        else {
            posizione++;
        }
    }
    
    while(1)
    {
        getInput("\n\nSEI SODDSFATTO DELLA SCHEDA?\nLA CONSIDERI COMPLETATA?\nPER FAVORE RISPONDI CON SI O NO\n>> ", answer, 3);
        
        if (strcasecmp(answer, "si\0") == 0)
        {
            if(completedRoutine(Cliente, date)){
                printSuccess("LA SCHEDA E' STATA CREATA CON SUCCESSO");
                return true;
            }
            return false;
        }else if (strcasecmp(answer, "no\0") == 0){
            printSuccess("SCHEDA FATTA, MA NON COMPLETATA");
            return true;
        }
        else{
            printError("RISPOSTA NON ACCETTABILE");
        }
    }
}


bool archiviaScheda(User *loggedUser)
{
    int len;
    char Cliente[CF_MAX_SIZE];
    clearScreen();
    showMyTitle();
    puts("\t\t\t\t|‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾|");
    puts("\t\t\t\t|       ARCHIVIAZIONE SCHEDA       |");
    puts("\t\t\t\t|__________________________________|");
    printf("\033[44m\033[0m\n");
    puts("");
    puts("");
    if (showAllMyCustomers(loggedUser))
    {
        printBoldGreen("\n\nSELEZIONA IL CLIENTE AL QUALE VUOI ARCHIVIARE LA SCHEDA ATTIVA\n");
        printBoldGreen(">> ");
        fgets(Cliente, CF_MAX_SIZE, stdin);
        len = strlen(Cliente);
        if (len == CF_MAX_SIZE-1){
            while (getchar() != '\n'){}
        }
        if (Cliente[len - 1] == '\n'){
            Cliente[len - 1] = '\0';
        }
        if (archiveRoutine(loggedUser, Cliente)){
            return true;
        }
        return false;
    }else{
        printError("ERRORE IN APERTURA LISTA CLIENTI");
        return false;
    }
}

bool creaNuovaSchedaAttiva(User *loggedUser)
{
    int len;
    char Cliente[CF_MAX_SIZE], dataInizioScheda[DATE_SIZE];
    clearScreen();
    showMyTitle();
    printf("\033[47m\033[30m\033[0m");
    puts("\t\t\t\t|‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾|");
    puts("\t\t\t\t|      CREAZIONE NUOVA SCHEDA      |");
    puts("\t\t\t\t|__________________________________|");

    puts("");
    puts("");
    if (showAllMyCustomers(loggedUser)){
        printBoldGreen("\n\nSELEZIONA IL CLIENTE AL QUALE VUOI CREARE UNA NUOVA SCHEDA\n");
        printBoldGreen(">> ");
        fgets(Cliente, CF_MAX_SIZE, stdin);
        len = strlen(Cliente);
        if (len == CF_MAX_SIZE-1){
            while (getchar() != '\n'){}
        }
        if (Cliente[len - 1] == '\n'){
            Cliente[len - 1] = '\0';
        }
        if (createNewRoutine(loggedUser, Cliente, dataInizioScheda)){
            Date *date = malloc(sizeof(Date));
            if (date == NULL){
                printf("Errore: impossibile allocare memoria per la struttura date.\n");
                exit(EXIT_FAILURE);
            }
            if (!convertDateFromDb(date, dataInizioScheda)){
                free(date);
                return false;
            }
            if(inserisciEsercizi(Cliente, date)){
                free(date);
                return true;
            }
            free(date);
            return false;
        }
        return false;
    }else{
        printError("ERRORE IN APERTURA LISTA CLIENTI");
        return false;
    }
}

bool modificaScheda(User *loggedUser){
    char cliente[CF_MAX_SIZE], dataInit[DATE_SIZE];
    int maxPosition;
    if(printAllNotCompletedRoutines(loggedUser)){
        getInput("\n\nQUALE SCHEDA VUOI MODIFICARE? (PER FAVORE INSERIRE IL CODICE FISCALE)\n>> ", cliente, CF_MAX_SIZE);
        if(chooseNotCompletedRoutine(cliente, dataInit, &maxPosition)){
            printSuccess("ECCO LA SCHEDA SUA SCHEDA NON COMPLETA");
            puts("");
            Date *date = malloc(sizeof(Date));
            if (date == NULL){
                printf("Errore: impossibile allocare memoria per la struttura date.\n");
                exit(EXIT_FAILURE);
            }
            if (!convertDateFromDb(date, dataInit)){
                free(date);
                return false;
            }
            if(inserisciAltriEsercizi(cliente, date, maxPosition)){
                free(date);
                return true;
            }
            free(date);
            return false;
        }
        return false;
    }
    return false;
}


void ptController(char *username)
{
    bool prev_error = false;
clean_up:
    clearScreen();
    showMyTitle();
    puts("\t\t\t\t|‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾|");
    puts("\t\t\t\t|      AREA PERSONAL TRAINER      |");
    puts("\t\t\t\t|_________________________________|");
    printf("\t\t\t\t     Bentornato/a %s.\n\n", username);
    int input;
    int failed_attempts = 0;

    User *loggedUser = malloc(sizeof(User));
    if (loggedUser == NULL){
        printError("Errore: impossibile allocare memoria per la struttura loggedUser.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(loggedUser->username, username);
    if (!getPtCf(loggedUser)){
        printError("Codice Fiscale non preso.\n");
        exit(EXIT_FAILURE);
    }
    puts("");
    puts("");
    puts("");
    puts("");
    printf("\033[47m\033[30mCODICE FISCALE: %s\033[0m", loggedUser->cf);
    puts("");
    puts("");
    while (true){
        if (prev_error){
            printError("\t Ripristino menu dopo troppi tentativi errati\n\t Stai più attento!");
            prev_error = false;
        }
        if (failed_attempts == 5){
            prev_error = true;
            goto clean_up;
        }
        input = promptMenuPt();
        switch (input)
        {
        case 1:
            if (!archiviaScheda(loggedUser)){
                failed_attempts++;
                break;
            }
            goto clean_up;
        case 2:
            if (!creaNuovaSchedaAttiva(loggedUser)){
                failed_attempts++;
            }
            break;
        case 3:
            if(!modificaScheda(loggedUser)){      //mostra tutte le schede non completate
                failed_attempts ++;               //scegline una
            }                                     //modificala
            break;
        case 4:
            if (generaReport(loggedUser)){
                printSuccess("REPORT STAMPATO CON SUCCESSO.");
                puts("");
                break;
            }
            printError("UNA DELLE DUE DATE CHE HAI PASSATO NEL REPORT NON HA SENSO");
            break;
        case 5:
            User *Cliente = malloc(sizeof(User));
            if (Cliente == NULL){
                printf("Errore: impossibile allocare memoria per la struttura Cliente.\n");
                exit(EXIT_FAILURE);
            }
            if (!mostraSchedaAttivaCliente(loggedUser, Cliente)){
                failed_attempts++;
            }
            free(Cliente);
            break;
        case 6:
            showAllMyCustomers(loggedUser);
            break;
        case 7:
            free(loggedUser);
            return;
        case 8:
            goto clean_up;
        default:
            printError("Scegli tra le opzioni proposte!");
            failed_attempts++;
            break;
        }
    }
}