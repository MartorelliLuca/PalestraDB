#include "loginController.h"

static bool switchRole(Role role) {
    char *databaseName = getenv("DB.NAME") ;
    char *username ;
    char *password ;

    switch(role) {
        case SEGRETERIA :
            username = getenv(DB_SEGRETERIA_USER) ;
            password = getenv(DB_SEGRETERIA_PASSWD) ;
            break ;
        case PT :
            username = getenv(DB_PT_USER) ;
            password = getenv(DB_PT_PASSWD) ;
            break ;
        case CLIENTI :
            username = getenv(DB_CLIENTI_USER) ;
            password = getenv(DB_CLIENTI_PASSWD) ;
            break ;
        case UTENTI :
            username = getenv(DB_UTENTI_USER) ;
            password = getenv(DB_UTENTI_PASSWD) ;
            break ;
    }

    if (username == NULL) {
        printError("Errore1 : Variabili d'Ambiente Non Trovate") ;
        return false ;
    }

    if (password == NULL) {
        printError("Errore2 : Variabili d'Ambiente Non Trovate") ;
        return false ;
    }

    if (databaseName == NULL) {
        printError("Errore3 : Variabili d'Ambiente Non Trovate") ;
        return false ;
    }

    if (mysql_change_user(conn, username, password, databaseName) != 0) {
        print_sql_error(conn, "Errore SQL: Impossibile Cambiare Privilegi Utente") ;
        return false ;
    }

    return true ;
}

static bool successLogin(Role myRole, char* username) {
    clearScreen() ;
    showMyTitle() ;
    bool flag = false;

    if (switchRole(myRole) == false) {
        return false;
    }

    switch (myRole) {
        case  PT:
            ptController(username) ;
            flag = true ;
            break;
        case SEGRETERIA :
            segreteriaController(username) ;
            flag = true ;
            break;
        case CLIENTI :
            clientiController(username) ;
            flag = true ;
            break;
        case UTENTI :
            printError("login fallito");
            break;
    }
    
    switchRole(UTENTI) ;
    return flag;
}

static void login(){
    clearScreen();
    showMyTitle();
    puts("\t\t\t\t|‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾|");
	puts("\t\t\t\t|             LOGIN               |");
	puts("\t\t\t\t|_________________________________|\n");
    Credentials creds ;
    int failed_attempts = 0;

    do {
        if(failed_attempts == 3){
            return;
        }
        memset(&creds, 0, sizeof(Credentials)) ;
        Role myRole = UTENTI ;

        if (promptLogin(&creds)) {
            myRole = logAsUser(creds) ;
            if (myRole == UTENTI) {
                printError("LOGIN FALLITO: Username e/o Password non corrispondono ad alcun utente") ;
                failed_attempts ++;
            }
            else {
                if(successLogin(myRole, creds.username)){
                    return;
                }
            }
        }else{
            failed_attempts ++;
        }
    } while (true) ;    
}


void loginController() {
main_menu:
    clearScreen();
    showMyTitle();
    puts("\t\t\t\t|‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾|");
	puts("\t\t\t\t|         MENU PRINCIPALE         |");
	puts("\t\t\t\t|_________________________________|\n");
    int input;
    int failed_attempts = 0;
    while (true) {
        if(failed_attempts == 3){
            goto main_menu;
        }
        input = promptInitialMenu();
		switch (input)
        {
            case 1:
                login();
                goto main_menu;
                break;
            case 2:
                puts("");
                printf("\033[42m%s\033[0m", "------------------------ARRIVEDERCI------------------------");
                puts("");
                puts("");
                mysql_close(conn);
                exit(0);
            default:
                printError("Scegli tra le opzioni proposte!");
                failed_attempts ++;
                break;
        }
	}
    
}