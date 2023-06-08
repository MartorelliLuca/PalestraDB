#include "connector.h"

MYSQL *conn ;


bool connectToDatabase() {
    char *host = getenv(DB_HOST) ;
    char *port = getenv(DB_PORT) ;
    char *databaseName = getenv(DB_NAME) ;
    char *loginUser = getenv(DB_UTENTI_USER) ;
    char *loginPassword = getenv(DB_UTENTI_PASSWD) ;
    unsigned int timeout = 300;
	bool reconnect = true;

    if (host == NULL || port == NULL || loginUser == NULL || loginPassword == NULL || databaseName == NULL) {
        printError("Errore: Variabili d'ambiente non trovate") ;
        return false ;
    }

    conn = mysql_init(NULL) ;
    if (conn == NULL) {
        printError("Errore: Inizializzazione librerie non riuscita");
        return false ;
    }

    if (mysql_real_connect(
        conn, 
        host, 
        loginUser, 
        loginPassword, 
        databaseName, 
        atoi(port), 
        NULL, CLIENT_MULTI_STATEMENTS | CLIENT_MULTI_RESULTS | CLIENT_COMPRESS | CLIENT_INTERACTIVE | CLIENT_REMEMBER_OPTIONS) == NULL) {
            print_sql_error(conn, "Errore SQL: Connessione al Database non riuscita\n") ;
            return false ;
    }
    
	if (mysql_options(conn, MYSQL_OPT_CONNECT_TIMEOUT, &timeout)) {
		print_sql_error(conn, "Errore SQL: [mysql_options] failed.");
	}

	if(mysql_options(conn, MYSQL_OPT_RECONNECT, &reconnect)) {
		print_sql_error(conn, "Errore SQL: [mysql_options] failed.");
	}    

    return true ;
}