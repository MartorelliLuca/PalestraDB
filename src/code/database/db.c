#include "db.h"

bool moveArmyBetweenTerritories(char *username, int *num_carri, char *terr1, char *terr2){
	MYSQL_STMT* prepared_stmt;
	MYSQL_BIND param[4];

	// Prepare stored procedure call
	if (!setup_prepared_stmt(&prepared_stmt, "call sposta_carriArmati_tra_territori(?, ?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prepared statement for procedure: sposta_carriArmati_tra_territori", false);
		goto err1;
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[0].buffer = username;
	param[0].buffer_length = strlen(username);

	param[1].buffer_type = MYSQL_TYPE_LONG; // IN
	param[1].buffer = num_carri;
	param[1].buffer_length = sizeof(num_carri);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[2].buffer = terr1;
	param[2].buffer_length = strlen(terr1);

	param[3].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[3].buffer = terr2;
	param[3].buffer_length = strlen(terr2);

	// Binding
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters in procedure: sposta_carriArmati_tra_territori", true);
		goto err;
	}

	// Execution
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Error in execution for procedure: sposta_carriArmati_tra_territori");
		goto err;
	}

	mysql_stmt_close(prepared_stmt);
	return true;
err:
	mysql_stmt_close(prepared_stmt);
err1:
	return false;
}


bool placeArmyOnTerritory(char *username, int *num_carri, char *terr){
	MYSQL_STMT* prepared_stmt;
	MYSQL_BIND param[3];

	// Prepare stored procedure call
	if (!setup_prepared_stmt(&prepared_stmt, "call posiziona_carriArmati_su_territorio(?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prepared statement for procedure: posiziona_carriArmati_su_territorio", false);
		goto err1;
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[0].buffer = username;
	param[0].buffer_length = strlen(username);

	param[1].buffer_type = MYSQL_TYPE_LONG; // IN
	param[1].buffer = num_carri;
	param[1].buffer_length = sizeof(num_carri);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[2].buffer = terr;
	param[2].buffer_length = strlen(terr);
	
	// Binding
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters in procedure: posiziona_carriArmati_su_territorio", true);
		goto err;
	}

	// Execution
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Error in execution for procedure: posiziona_carriArmati_su_territorio");
		goto err;
	}

	mysql_stmt_close(prepared_stmt);
	return true;
err:
	mysql_stmt_close(prepared_stmt);
err1:
	return false;
}

bool attackTerritory(char *username, int *num_carri, char *terr1, char *terr2, int *num_army_loss_attack, int *num_army_loss_defense,int *is_conquered, int *i_won){
	MYSQL_STMT* prepared_stmt;
	MYSQL_BIND param[8];

	// Prepare stored procedure call
	if (!setup_prepared_stmt(&prepared_stmt, "call attacca_territorio(?, ?, ?, ?, ?, ?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prepared statement for procedure: attacca_territorio", false);
		goto err1;
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[0].buffer = username;
	param[0].buffer_length = strlen(username);

	param[1].buffer_type = MYSQL_TYPE_LONG; // IN
	param[1].buffer = num_carri;
	param[1].buffer_length = sizeof(num_carri);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[2].buffer = terr1;
	param[2].buffer_length = strlen(terr1);

	param[3].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[3].buffer = terr2;
	param[3].buffer_length = strlen(terr2);

	param[4].buffer_type = MYSQL_TYPE_LONG; // OUT
	param[4].buffer = num_army_loss_attack;
	param[4].buffer_length = sizeof(num_army_loss_attack);

	param[5].buffer_type = MYSQL_TYPE_LONG; // OUT
	param[5].buffer = num_army_loss_defense;
	param[5].buffer_length = sizeof(num_army_loss_defense);

	param[6].buffer_type = MYSQL_TYPE_LONG; // OUT
	param[6].buffer = is_conquered;
	param[6].buffer_length = sizeof(is_conquered);

	param[7].buffer_type = MYSQL_TYPE_LONG; // OUT
	param[7].buffer = i_won;
	param[7].buffer_length = sizeof(i_won);

	// Binding
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters in procedure: attacca_territorio", true);
		goto err;
	}

	// Execution
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Error in execution for procedure: attacca_territorio");
		goto err;
	}

	// Prepare output params
	memset(param, 0, sizeof(param));
	param[0].buffer_type = MYSQL_TYPE_LONG; // OUT
	param[0].buffer = num_army_loss_attack;
	param[0].buffer_length = sizeof(num_army_loss_attack);

	param[1].buffer_type = MYSQL_TYPE_LONG; // OUT
	param[1].buffer = num_army_loss_defense;
	param[1].buffer_length = sizeof(num_army_loss_defense);

	param[2].buffer_type = MYSQL_TYPE_LONG; // OUT
	param[2].buffer = is_conquered;
	param[2].buffer_length = sizeof(is_conquered);

	param[3].buffer_type = MYSQL_TYPE_LONG; // OUT
	param[3].buffer = i_won;
	param[3].buffer_length = sizeof(i_won);

	// Binding res
	if (mysql_stmt_bind_result(prepared_stmt,param)){
		print_stmt_error(prepared_stmt, "Could not retrieve output in procedure: attacca_territorio");
		goto err;
	}

	// Retrieve output parameter
	if (mysql_stmt_fetch(prepared_stmt)){
		print_stmt_error(prepared_stmt, "Could not buffer result in procedure: attacca_territorio");
		goto err;
	}

	mysql_stmt_close(prepared_stmt);
	return true;
err:
	mysql_stmt_close(prepared_stmt);
err1:
	return false;
}

bool skipTurn(char *username){
	MYSQL_STMT* prepared_stmt;
	MYSQL_BIND param[1];

	// Prepare stored procedure call
	if (!setup_prepared_stmt(&prepared_stmt, "call salta_turno(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prepared statement for procedure: salta_turno", false);
		goto err1;
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[0].buffer = username;
	param[0].buffer_length = strlen(username);

	// Binding
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters in procedure: salta_turno", true);
		goto err;
	}

	// Execution
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Error in execution for procedure: salta_turno");
		goto err;
	}

	mysql_stmt_close(prepared_stmt);
	return true;
err:
	mysql_stmt_close(prepared_stmt);
err1:
	return false;
}

bool showMatchStatus(char *username){
	MYSQL_STMT* prepared_stmt;
	MYSQL_BIND param[1];

	// Prepare stored procedure call
	if (!setup_prepared_stmt(&prepared_stmt, "call vedi_stato_di_gioco(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prepared statement for procedure: vedi_stato_di_gioco", false);
		goto err1;
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[0].buffer = username;
	param[0].buffer_length = strlen(username);

	// Binding
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters in procedure: vedi_stato_di_gioco", true);
		goto err;
	}

	// Execution
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Error in execution for procedure: vedi_stato_di_gioco");
		goto err;
	}

	// Dump of the result set
	dump_result_set(conn, prepared_stmt, "\n\tSTATO DI GIOCO\n");
	mysql_stmt_next_result(prepared_stmt);
	dump_result_set(conn, prepared_stmt, "\n\tARMATE GIOCATORI\n");
	mysql_stmt_next_result(prepared_stmt);
	mysql_stmt_close(prepared_stmt);
	return true;
err:
	mysql_stmt_close(prepared_stmt);
err1:
	return false;
}

bool visualizzaSchedaAttiva(User *loggedUser){
    MYSQL_STMT* prepared_stmt;
    MYSQL_BIND param[1];

    // Prepare stored procedure call
    if (!setup_prepared_stmt(&prepared_stmt, "call visualizza_scheda_attiva(?)", conn)) {
        finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prepared statement for procedure: visualizza_scheda_attiva", false);
        goto err1;
    }

    // Prepare parameters
    memset(param, 0, sizeof(param));

    param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
    param[0].buffer = loggedUser->cf;
    param[0].buffer_length = strlen(loggedUser->cf);

    // Binding
    if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
        finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters in procedure: visualizza_scheda_attiva", true);
        goto err;
    }

    // Execution
    if (mysql_stmt_execute(prepared_stmt) != 0) {
        print_stmt_error(prepared_stmt, "Error in execution for procedure: visualizza_scheda_attiva");
        goto err;
    }

    // Fetch and print the results
	dump_result_set(conn, prepared_stmt, "");
	mysql_stmt_next_result(prepared_stmt);

    mysql_stmt_close(prepared_stmt);
    return true;
err:
    mysql_stmt_close(prepared_stmt);
err1:
    return false;
}

bool leaveMatch(char *username){
	MYSQL_STMT* prepared_stmt;
	MYSQL_BIND param[1];

	// Prepare stored procedure call
	if (!setup_prepared_stmt(&prepared_stmt, "call rimuovi_partecipante(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prepared statement for procedure: rimuovi_partecipante", false);
		goto err1;
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[0].buffer = username;
	param[0].buffer_length = strlen(username);

	// Binding
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters in procedure: rimuovi_partecipante", true);
		goto err;
	}

	// Execution
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Error in execution for procedure: rimuovi_partecipante");
		goto err;
	}

	mysql_stmt_close(prepared_stmt);
	return true;
err:
	mysql_stmt_close(prepared_stmt);
err1:
	return false;
}

bool showMatchHistory(char *username){
	MYSQL_STMT* prepared_stmt;
	MYSQL_BIND param[1];

	// Prepare stored procedure call
	if (!setup_prepared_stmt(&prepared_stmt, "call vedi_storico_partite(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prepared statement for procedure: vedi_storico_partite", false);
		goto err1;
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[0].buffer = username;
	param[0].buffer_length = strlen(username);

	// Binding
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters in procedure: vedi_storico_partite", true);
		goto err;
	}

	// Execution
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Error in execution for procedure: vedi_storico_partite");
		goto err;
	}

	// Dump of the result set
	dump_result_set(conn, prepared_stmt, "\n\tSTORICO PARTITE\n");
	mysql_stmt_next_result(prepared_stmt);
	mysql_stmt_close(prepared_stmt);
	return true;
err:
	mysql_stmt_close(prepared_stmt);
err1:
	return false;
}

bool enterInGameRoom(char *username, char *nomeStanza, int *idPartita){
	MYSQL_STMT* prepared_stmt;
	MYSQL_BIND param[3];

	// Prepare stored procedure call
	if (!setup_prepared_stmt(&prepared_stmt, "call aggiungi_partecipante(?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prepared statement for procedure: aggiungi_partecipante", false);
		goto err1;
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[0].buffer = username;
	param[0].buffer_length = strlen(username);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[1].buffer = nomeStanza;
	param[1].buffer_length = strlen(nomeStanza);

	param[2].buffer_type = MYSQL_TYPE_LONG; // OUT
	param[2].buffer = idPartita;
	param[2].buffer_length = sizeof(idPartita);

	// Binding
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters in procedure: aggiungi_partecipante", true);
		goto err;
	}

	// Execution
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Error in execution for procedure: aggiungi_partecipante");
		goto err;
	}

	// Prepare output params
	memset(param, 0, sizeof(param));
	param[0].buffer_type = MYSQL_TYPE_LONG; // OUT
	param[0].buffer = idPartita;
	param[0].buffer_length = sizeof(idPartita);

	// Binding res
	if (mysql_stmt_bind_result(prepared_stmt,param)){
		print_stmt_error(prepared_stmt, "Could not retrieve output in procedure: aggiungi_partecipante");
		goto err;
	}

	// Retrieve output parameter
	if (mysql_stmt_fetch(prepared_stmt)){
		print_stmt_error(prepared_stmt, "Could not buffer result in procedure: aggiungi_partecipante");
		goto err;
	}
	mysql_stmt_close(prepared_stmt);
	return true;
err:
	mysql_stmt_close(prepared_stmt);
err1:
	return false;
}

bool createNewGameRoom(char *nomeStanza){
	MYSQL_STMT* prepared_stmt;
	MYSQL_BIND param[1];

	// Prepare stored procedure call
	if (!setup_prepared_stmt(&prepared_stmt, "call crea_nuova_stanza(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prepared statement for procedure: crea_nuova_stanza", false);
		goto err1;
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[0].buffer = nomeStanza;
	param[0].buffer_length = strlen(nomeStanza);

	// Binding
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters in procedure: crea_nuova_stanza", true);
		goto err;
	}

	// Execution
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Error in execution for procedure: crea_nuova_stanza");
		goto err;
	}

	mysql_stmt_close(prepared_stmt);
	return true;
err:
	mysql_stmt_close(prepared_stmt);
err1:
	return false;

}

bool retrieveReport(){
	MYSQL_STMT* prepared_stmt;

	// Prepare stored procedure call
	if (!setup_prepared_stmt(&prepared_stmt, "call report_moderatori()", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prepared statement for procedure: report_moderatori", false);
		goto err1;
	}

	// Execution
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Error in execution for procedure: report_moderatori");
		goto err;
	}

	// Dump of the result set
	dump_result_set(conn, prepared_stmt, "\n\tREPORT MODERATORI\n");
	mysql_stmt_next_result(prepared_stmt);
	dump_result_set(conn, prepared_stmt, "");
	mysql_stmt_next_result(prepared_stmt);
	dump_result_set(conn, prepared_stmt, "");
	mysql_stmt_next_result(prepared_stmt);
	mysql_stmt_close(prepared_stmt);
	return true;
err:
	mysql_stmt_close(prepared_stmt);
err1:
	return false;
}

bool registerNewCustomer(User user){
	MYSQL_STMT* prepared_stmt;
	MYSQL_BIND param[5];

	// Prepare stored procedure call
	if (!setup_prepared_stmt(&prepared_stmt, "call aggiungi_cliente(?, ?, ?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prepared statement for procedure: aggiungi_cliente", false);
		goto err1;
	}
	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[0].buffer = user.cf;
	param[0].buffer_length = strlen(user.cf);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[1].buffer = user.nome;
	param[1].buffer_length = strlen(user.nome);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[2].buffer = user.cognome;
	param[2].buffer_length = strlen(user.cognome);

	param[3].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[3].buffer = user.username;
	param[3].buffer_length = strlen(user.username);

	param[4].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[4].buffer = user.password;
	param[4].buffer_length = strlen(user.password);

	// Binding
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters in procedure: aggiungi_cliente", true);
		goto err;
	}

	// Execution
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Error in execution for procedure: aggiungi_cliente");
		goto err;
	}

	mysql_stmt_close(prepared_stmt);
	return true;
err:
	mysql_stmt_close(prepared_stmt);
err1:
	return false;
}

bool registerNewPlayer(Credentials creds){
	MYSQL_STMT* prepared_stmt;
	MYSQL_BIND param[4];

	// Prepare stored procedure call
	if (!setup_prepared_stmt(&prepared_stmt, "call registra_nuovo_giocatore(?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prepared statement for procedure: registra_nuovo_giocatore", false);
		goto err1;
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[0].buffer = creds.username;
	param[0].buffer_length = strlen(creds.username);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[1].buffer = creds.password;
	param[1].buffer_length = strlen(creds.password);

	// Binding
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters in procedure: registra_nuovo_giocatore", true);
		goto err;
	}

	// Execution
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Error in execution for procedure: registra_nuovo_giocatore");
		goto err;
	}

	mysql_stmt_close(prepared_stmt);
	return true;
err:
	mysql_stmt_close(prepared_stmt);
err1:
	return false;
}

bool showAdjacentTerritories(char *terr){
    MYSQL_STMT* prepared_stmt;
	MYSQL_BIND param[1];

	// Prepare stored procedure call
	if (!setup_prepared_stmt(&prepared_stmt, "call mostra_adiacenze_territorio(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prepared statement for procedure: mostra_adiacenze_territorio", false);
		goto err1;
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[0].buffer = terr;
	param[0].buffer_length = strlen(terr);

	// Binding
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters in procedure: mostra_adiacenze_territorio", true);
		goto err;
	}

	// Execution
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Error in execution for procedure: mostra_adiacenze_territorio");
		goto err;
	}

	// Dump of the result set
	dump_result_set(conn, prepared_stmt, "\n\tTERRITORI ADIACENTI\n");
	mysql_stmt_next_result(prepared_stmt);
	mysql_stmt_close(prepared_stmt);
	return true;
err:
	mysql_stmt_close(prepared_stmt);
err1:
	return false;
}

bool getCustomerCf(User* loggedUser) {
    MYSQL_STMT* prepared_stmt;
    MYSQL_BIND param[2];

    // Prepare stored procedure call
    if (!setup_prepared_stmt(&prepared_stmt, "call prendi_cliente_cf(?)", conn)) {
        finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prepared statement for procedure: prendi_cliente_cf", false);
        goto err1;
    }

    // Prepare parameters
    memset(param, 0, sizeof(param));

    User* lUser = malloc(sizeof(User));
    if (lUser == NULL) {
        printf("Errore: impossibile allocare memoria per la struttura lUser.\n");
        exit(EXIT_FAILURE);
    }

    param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
    param[0].buffer = loggedUser->username;
    param[0].buffer_length = strlen(loggedUser->username);

    param[1].buffer_type = MYSQL_TYPE_VAR_STRING; // OUT
    param[1].buffer = lUser->cf;
    param[1].buffer_length = sizeof(lUser->cf);

    // Binding
    if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
        print_stmt_error(prepared_stmt, "Could not bind parameters in procedure: login");
        goto err;
    }

    // Execution
    if (mysql_stmt_execute(prepared_stmt) != 0) {
        print_stmt_error(prepared_stmt, "Error in execution for procedure: login");
        goto err;
    }

    // Prepare output parameters
    memset(param, 0, sizeof(param));
    param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // OUT
    param[0].buffer = lUser->cf;
    param[0].buffer_length = sizeof(lUser->cf);

    if (mysql_stmt_bind_result(prepared_stmt, param)) {
        print_stmt_error(prepared_stmt, "Could not retrieve output in procedure: prendi_cliente_cf");
        goto err;
    }

    // Retrieve output parameter
    if (mysql_stmt_fetch(prepared_stmt)) {
        print_stmt_error(prepared_stmt, "Could not buffer results in procedure: prendi_cliente_cf");
        goto err;
    }

    strcpy(loggedUser->cf, lUser->cf);

    mysql_stmt_close(prepared_stmt);
    free(lUser);
    return true;

err:
    mysql_stmt_close(prepared_stmt);
err1:
    free(lUser);
    return false;
}

	


Role logAsUser(Credentials creds) {
	MYSQL_STMT* login_procedure; 
    
	MYSQL_BIND param[3]; // Used both for input and output
	int role = 0;

	if (!setup_prepared_stmt(&login_procedure, "call login(?, ?, ?)", conn)) {
		print_stmt_error(login_procedure, "Unable to initialize prepared statement for procedure: login");
		goto err1;
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[0].buffer = creds.username;
	param[0].buffer_length = strlen(creds.username);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[1].buffer = creds.password;
	param[1].buffer_length = strlen(creds.password);

	param[2].buffer_type = MYSQL_TYPE_LONG; // OUT
	param[2].buffer = &role;
	param[2].buffer_length = sizeof(role);

	// Binding
	if (mysql_stmt_bind_param(login_procedure, param) != 0) { // Note _param
		print_stmt_error(login_procedure, "Could not bind parameters in procedure: login");
		goto err;
	}

	// Execution 
	if (mysql_stmt_execute(login_procedure) != 0) {
		print_stmt_error(login_procedure, "Error in execution for procedure: login");
		goto err;
	}

	// Prepare output parameters
	memset(param, 0, sizeof(param));
	param[0].buffer_type = MYSQL_TYPE_LONG; // OUT
	param[0].buffer = &role;
	param[0].buffer_length = sizeof(role);

	if (mysql_stmt_bind_result(login_procedure, param)) {
		print_stmt_error(login_procedure, "Could not retrieve output in procedure: aggiungi_partecipante");
		goto err;
	}

	// Retrieve output parameter
	if (mysql_stmt_fetch(login_procedure)) {
		print_stmt_error(login_procedure, "Could not buffer results in procedure: aggiungi_partecipante");
		goto err;
	}

	mysql_stmt_close(login_procedure);
	return role;

err:
	mysql_stmt_close(login_procedure);
err1:
	return UTENTI;
}
