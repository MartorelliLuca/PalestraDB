#include "giocatoreController.h"

char *g_username;

//[1] VEDI STATO DI GIOCO
static bool vediStatoDiGioco(){
    printSuccess("-- GENERAZIONE STATO DI GIOCO INIZIATA --");
    if(showMatchStatus(g_username)){
        printSuccess("-- GENERAZIONE STATO DI GIOCO TERMINATA --");
        return true;
    }else{
        return false;
    }
}

//[2] SALTA TURNO
static bool saltaTurno(){
    if(skipTurn(g_username)){
        puts("");
        printf("\033[43m%s\033[0m","-- TURNO SALTATO --");
        puts("");
        puts("");
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
                        printWinningTrophy();
                        puts("");
                        puts("");
                    }
                }
                return true;
            }
        }
        return false;
    }while(true);
}

//[4] POSIZIONA CARRI ARMATI SU TERRITORIO
static bool posizionaCarriArmatiSuTerritorio(){
    char nomeTerritorio[VARCHAR45];
    int num_army;
    do{
        memset(&nomeTerritorio, 0, sizeof(nomeTerritorio));
        memset(&num_army, 0, sizeof(num_army));
        if(getPositionArmyInfo(nomeTerritorio, &num_army)){
            //conversione nome territorio in uppercase
            toUpperCase(nomeTerritorio);
            if(placeArmyOnTerritory(g_username, &num_army, nomeTerritorio)){
                printSuccess("-- POSIZIONAMENTO CARRI ARMATI EFFETTUATO CON SUCCESSO --");
                return true;
            }
        }
        return false;
    }while(true);
}

//[5] SPOSTA CARRI ARMATI TRA TERRITORI
static bool spostaCarriArmatiTraTerritori(){
    char nomeTerritorio1[VARCHAR45];
    char nomeTerritorio2[VARCHAR45];
    int num_army;
    do{
        memset(&nomeTerritorio1, 0, sizeof(nomeTerritorio1));
        memset(&nomeTerritorio2, 0, sizeof(nomeTerritorio2));
        memset(&num_army, 0, sizeof(num_army));
        if(getMoveArmyInfo(&num_army, nomeTerritorio1, nomeTerritorio2)){
            //conversione nome territorio in uppercase
            toUpperCase(nomeTerritorio1);
            toUpperCase(nomeTerritorio2);
            if(moveArmyBetweenTerritories(g_username, &num_army, nomeTerritorio1, nomeTerritorio2)){
                printSuccess("-- SPOSTAMENTO CARRI ARMATI EFFETTUATO CON SUCCESSO --");
                return true;
            }
        }
        return false;
    }while(true);
}

//[6] MOSTRA ADIACENZE TERRITORIO
static bool mostraAdiacenzeTerritorio(){
    char nomeTerritorio[VARCHAR45];
    do{
        memset(&nomeTerritorio, 0, sizeof(nomeTerritorio));
        if (getInput("Nome territorio di cui mostrare le adiacenze:\n>> ", nomeTerritorio, 46)) {
            //conversione nome territorio in uppercase
            toUpperCase(nomeTerritorio);
            printSuccess("-- GENERAZIONE LISTA TERRITORI ADIACENTI INIZIATA --");
            if(showAdjacentTerritories(nomeTerritorio)){
                printSuccess("-- GENERAZIONE LISTA TERRITORI ADIACENTI TERMINATA --");
                return true;
            }else{
                return false;
            }
        }
        printError("Errore Lettura Territorio Di Cui Mostrare Le Adiacenze") ;
        return false;
    }while(true);
}

//[7-3] VISUALIZZA STORICO PARTITE
static bool visualizzaStoricoPartite(){
    printSuccess("-- GENERAZIONE STORICO PARTITE INIZIATA --");
    if(showMatchHistory(g_username)){
        printSuccess("-- GENERAZIONE STORICO PARTITE TERMINATA --");
        return true;
    }else{
        return false;
    }
}

//[8] ABBANDONA PARTITA (ESCI DALLA STANZA)
static bool abbandonaPartita(){
    return leaveMatch(g_username);
}

void giocatoreInStanzaController(char *nomeStanza, int idPartita){
    bool prev_error = false;
clean_up:
    clearScreen();
    showAppTitle();
    printf("\t\t\t\t|‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾|\n");
    printf("\t\t\t\t|   SEI IN UNA STANZA DI GIOCO    |   NomeStanza: %s\n",nomeStanza);
	printf("\t\t\t\t|_________________________________|   CodicePartita: %d\n",idPartita);
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
        input = promptMenuStanza();
        switch (input)
        {
        case 1:
            if(!vediStatoDiGioco()){
                failed_attempts ++;
            }
            break;
        case 2:
            if(!saltaTurno()){
                failed_attempts ++;
            }
            break;
        case 3:
            if(!attaccaTerritorio()){
                failed_attempts ++;
            }
            break;
        case 4:
            if(!posizionaCarriArmatiSuTerritorio()){
                failed_attempts ++;
            }
            break;
        case 5:
            if(!spostaCarriArmatiTraTerritori()){
                failed_attempts ++;
            }
            break;
        case 6:
            if(!mostraAdiacenzeTerritorio()){
                failed_attempts ++;
            }
            break;
        case 7:
            if(!visualizzaStoricoPartite()){
                failed_attempts ++;
            }
            break;
        case 8:
            if(abbandonaPartita()){
                return;
            }else{
                failed_attempts ++;
            }
            break;
        case 9:
            goto clean_up;
        default:
            printError("Scegli tra le opzioni proposte!");
            failed_attempts ++;
            break;
        }
    }
    
}

//[2] MOSTRA STANZE DISPONIBILI
static bool mostraStanzeDisponibili(){
    printSuccess("-- GENERAZIONE LISTA STANZE DISPONIBILI INIZIATA --");
    if(showAvailableGameRooms()){
        printSuccess("-- GENERAZIONE LISTA STANZE DISPONIBILI TERMINATA --");
        return true;
    }else{
        return false;
    }
}

//[1] ENTRA IN UNA STANZA DI GIOCO
static bool entraInStanza(){
    char nomeStanza[VARCHAR45];
    char input;
    int idPartita;
    do {
        memset(&nomeStanza, 0, sizeof(nomeStanza));
        if(getInput("Inserire il nome della stanza di gioco in cui si vuole entrare:\n>> ", nomeStanza, VARCHAR45)){
            if(enterInGameRoom(g_username, nomeStanza, &idPartita)){
                giocatoreInStanzaController(nomeStanza, idPartita);
                return true;
            }else{
                int fail = 0;
                do{
                    if(fail == 3){
                        break;
                    }
                    if(getInput("Vuoi vedere la lista delle stanze disponibili? (s/n): ", &input, 2)){
                        if(input == 's'){
                            mostraStanzeDisponibili();
                            break;
                        }else if(input == 'n'){
                            break;
                        }else{
                            printError("Selezione errata, scegliere tra 's' e 'n'");
                            fail ++;
                        }
                    }else{
                        fail ++;
                    }
                }while(true);
            }
        }
        return false;
    } while (true) ;
}

void giocatoreController(char* username){
    g_username = username;
    bool prev_error = false;
clean_up:
    clearScreen();
    showAppTitle();
    puts("\t\t\t\t|‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾|");
    puts("\t\t\t\t|         AREA GIOCATORI          |");
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
        input = promptMenuGiocatore();
        switch (input)
        {
        case 1:
            if(!entraInStanza()){
                failed_attempts ++;
                break;
            }
            goto clean_up;
        case 2:
            if(!mostraStanzeDisponibili()){
                failed_attempts ++;
            }
            break;
        case 3:
            if(!visualizzaStoricoPartite()){
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