#include "db.h"


bool archiveRoutine(User *loggedUser, char *cf){
	MYSQL_STMT* prepared_stmt;
	MYSQL_BIND param[2];

	// Prepare stored procedure call
	if (!setup_prepared_stmt(&prepared_stmt, "call archivia_scheda(?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prepared statement for procedure: archivia_scheda", false);
		goto err1;
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[0].buffer = cf;
	param[0].buffer_length = strlen(cf);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[1].buffer = loggedUser->cf;
	param[1].buffer_length = strlen(loggedUser->cf);

	// Binding
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters in procedure: archivia_scheda", true);
		goto err;
	}

	// Execution
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Error in execution for procedure: archivia_scheda");
		goto err;
	}
	
	mysql_stmt_next_result(prepared_stmt);
	mysql_stmt_close(prepared_stmt);
	return true;
err:
	mysql_stmt_close(prepared_stmt);
err1:
	return false;
}



bool showAllMyCustomers(User *loggedUser){
	MYSQL_STMT* prepared_stmt;
	MYSQL_BIND param[1];

	// Prepare stored procedure call
	if (!setup_prepared_stmt(&prepared_stmt, "call visualizza_clienti(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prepared statement for procedure: visualizza_clienti", false);
		goto err1;
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[0].buffer = loggedUser->cf;
	param[0].buffer_length = strlen(loggedUser->cf);

	// Binding
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters in procedure: visualizza_clienti", true);
		goto err;
	}

	// Execution
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Error in execution for procedure: visualizza_clienti");
		goto err;
	}
	
	dump_result_set(conn, prepared_stmt, "\n");
	mysql_stmt_next_result(prepared_stmt);
	mysql_stmt_close(prepared_stmt);
	return true;
err:
	mysql_stmt_close(prepared_stmt);
err1:
	return false;
}

bool addSetToExercise(workoutCustomer *workUser, char *esercizio, int *numeroSerie){
	MYSQL_STMT* prepared_stmt;
	MYSQL_BIND param[5];

	// Prepare stored procedure call
	if (!setup_prepared_stmt(&prepared_stmt, "call aggiungi_serie_esercizio(?, ?, ?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prepared statement for procedure: aggiungi_serie_esercizio", false);
		goto err1;
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[0].buffer = esercizio;
	param[0].buffer_length = strlen(esercizio);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[1].buffer = workUser->dataSessione;
	param[1].buffer_length = strlen(workUser->dataSessione);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[2].buffer = workUser->dataInizioScheda;
	param[2].buffer_length = strlen(workUser->dataInizioScheda);
	
	param[3].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[3].buffer = workUser->cf;
	param[3].buffer_length = strlen(workUser->cf);

	param[4].buffer_type = MYSQL_TYPE_LONG; // IN
	param[4].buffer = numeroSerie;
	param[4].buffer_length = sizeof(int);


	// Binding
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters in procedure: aggiungi_serie_esercizio", true);
		goto err;
	}

	// Execution
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Error in execution for procedure: aggiungi_serie_esercizio");
		goto err;
	}

	dump_result_set(conn, prepared_stmt, "\n");
	mysql_stmt_next_result(prepared_stmt);
	mysql_stmt_close(prepared_stmt);
	return true;
err:
	mysql_stmt_close(prepared_stmt);
err1:
	return false;
}

bool performExercise(workoutCustomer *workUser, char *esercizio){
	MYSQL_STMT* prepared_stmt;
	MYSQL_BIND param[4];

	// Prepare stored procedure call
	if (!setup_prepared_stmt(&prepared_stmt, "call esegui_esercizio(?, ?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prepared statement for procedure: esegui_esercizio", false);
		goto err1;
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[0].buffer = esercizio;
	param[0].buffer_length = strlen(esercizio);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[1].buffer = workUser->dataSessione;
	param[1].buffer_length = strlen(workUser->dataSessione);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[2].buffer = workUser->dataInizioScheda;
	param[2].buffer_length = strlen(workUser->dataInizioScheda);

	param[3].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[3].buffer = workUser->cf;
	param[3].buffer_length = strlen(workUser->cf);

	// Binding
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters in procedure: esegui_esercizio", true);
		goto err;
	}

	// Execution
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Error in execution for procedure: esegui_esercizio");
		goto err;
	}
	dump_result_set(conn, prepared_stmt, "Esercizio iniziato correttamente.\n");
	mysql_stmt_next_result(prepared_stmt);
	mysql_stmt_close(prepared_stmt);
	return true;
err:
	mysql_stmt_close(prepared_stmt);
err1:
	return false;
}

bool displayNewRoutine(User *loggedUser){
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

bool endWorkout(workoutCustomer *workUser){
	MYSQL_STMT* prepared_stmt;
	MYSQL_BIND param[4];

	// Prepare stored procedure call
	if (!setup_prepared_stmt(&prepared_stmt, "call termina_sessione(?, ?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prepared statement for procedure: termina_sessione", false);
		goto err1;
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[0].buffer = workUser->dataSessione;
	param[0].buffer_length = strlen(workUser->dataSessione);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[1].buffer = workUser->orarioInizio;
	param[1].buffer_length = strlen(workUser->orarioInizio);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[2].buffer = workUser->dataInizioScheda;
	param[2].buffer_length = strlen(workUser->dataInizioScheda);

	param[3].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[3].buffer = workUser->cf;
	param[3].buffer_length = strlen(workUser->cf);

	// Binding
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters in procedure: termina_sessione", true);
		goto err;
	}

	// Execution
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Error in execution for procedure: termina_sessione");
		goto err;
	}

	mysql_stmt_close(prepared_stmt);
	return true;
err:
	mysql_stmt_close(prepared_stmt);
err1:
	return false;
}

bool showOldRoutines(User *loggedUser, int *numSchede) {
    MYSQL_STMT* prepared_stmt;
    MYSQL_BIND param[2];

    // Prepare stored procedure call
    if (!setup_prepared_stmt(&prepared_stmt, "call visualizza_schede_archiviate(?, ?)", conn)) {
        finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prepared statement for procedure: visualizza_schede_archiviate", false);
        goto err1;
    }

    // Prepare parameters
    memset(param, 0, sizeof(param));

    param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
    param[0].buffer = loggedUser->cf;
    param[0].buffer_length = strlen(loggedUser->cf);

    param[1].buffer_type = MYSQL_TYPE_LONG; // OUT
    param[1].buffer = numSchede;
	param[1].buffer_length = sizeof(numSchede);


    // Binding
    if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
        finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters in procedure: visualizza_schede_archiviate", true);
        goto err;
    }

    // Execution
    if (mysql_stmt_execute(prepared_stmt) != 0) {
        print_stmt_error(prepared_stmt, "Error in execution for procedure: visualizza_schede_archiviate");
        goto err;
    }

    // Fetch and print the results
	dump_result_set(conn, prepared_stmt, "");
	mysql_stmt_next_result(prepared_stmt);

    // Binding per l'output
    memset(param, 0, sizeof(param));
    param[0].buffer_type = MYSQL_TYPE_LONG; // OUT
    param[0].buffer = numSchede;
	param[0].buffer_length = sizeof(numSchede);


    // Binding res
	if (mysql_stmt_bind_result(prepared_stmt,param)){
		print_stmt_error(prepared_stmt, "Could not retrieve output in procedure: visualizza_schede_archiviate");
		goto err;
	}

	// Retrieve output parameter
	if (mysql_stmt_fetch(prepared_stmt)){
		print_stmt_error(prepared_stmt, "Could not buffer result in procedure: visualizza_schede_archiviate");
		goto err;
	}

    mysql_stmt_close(prepared_stmt);
    return true;

err:
    mysql_stmt_close(prepared_stmt);
err1:
    return false;
}


bool chooseNotCompletedRoutine(char *cliente, char *date, int *maxPosition){
	MYSQL_STMT* prepared_stmt;
    MYSQL_BIND param[3];

    // Prepare stored procedure call
    if (!setup_prepared_stmt(&prepared_stmt, "call scegli_scheda_attiva_non_completa(?, ?, ?)", conn)) {
        finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prepared statement for procedure: scegli_scheda_attiva_non_completa", false);
        goto err1;
    }

    // Prepare parameters
    memset(param, 0, sizeof(param));

    param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
    param[0].buffer = cliente;
    param[0].buffer_length = strlen(cliente);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING; //OUT
	param[1].buffer = date;
	param[1].buffer_length = strlen(date);

	param[2].buffer_type = MYSQL_TYPE_LONG; //OUT
	param[2].buffer = maxPosition;
	param[2].buffer_length = sizeof(*maxPosition);

    // Binding
    if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
        finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters in procedure: scegli_scheda_attiva_non_completa", true);
        goto err;
    }

    // Execution
    if (mysql_stmt_execute(prepared_stmt) != 0) {
        print_stmt_error(prepared_stmt, "Error in execution for procedure: scegli_scheda_attiva_non_completa");
        goto err;
    }

	// Binding per l'output
    memset(param, 0, sizeof(param));
    param[0].buffer_type = MYSQL_TYPE_STRING; // OUT
    param[0].buffer = date;
	param[0].buffer_length = strlen(date);

	param[1].buffer_type = MYSQL_TYPE_LONG; //OUT
	param[1].buffer = maxPosition;
	param[1].buffer_length = sizeof(*maxPosition);

	dump_result_set(conn, prepared_stmt, "");
	mysql_stmt_next_result(prepared_stmt);

    // Binding res
	if (mysql_stmt_bind_result(prepared_stmt,param)){
		print_stmt_error(prepared_stmt, "Could not retrieve output in procedure: scegli_scheda_attiva_non_completa");
		goto err;
	}

	// Retrieve output parameter
	if (mysql_stmt_fetch(prepared_stmt)){
		print_stmt_error(prepared_stmt, "Could not buffer result in procedure: scegli_scheda_attiva_non_completa");
		goto err;
	}

    // Fetch and print the results
	mysql_stmt_next_result(prepared_stmt);

    mysql_stmt_close(prepared_stmt);
    return true;

err:
    mysql_stmt_close(prepared_stmt);
err1:
    return false;

}

bool scegliSchedaArchiviata(User *loggedUser, Date *data){
	MYSQL_STMT* prepared_stmt;
    MYSQL_BIND param[2];

    // Prepare stored procedure call
    if (!setup_prepared_stmt(&prepared_stmt, "call scegli_scheda_archiviata(?, ?)", conn)) {
        finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prepared statement for procedure: scegli_scheda_archiviata", false);
        goto err1;
    }

    // Prepare parameters
    memset(param, 0, sizeof(param));

    param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
    param[0].buffer = loggedUser->cf;
    param[0].buffer_length = strlen(loggedUser->cf);

    MYSQL_TIME mysqlDate;
    prepareDateParam(data, &mysqlDate);

	param[1].buffer_type = MYSQL_TYPE_DATE;
	param[1].buffer = &mysqlDate;
	param[1].buffer_length = sizeof(MYSQL_TIME);


    // Binding
    if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
        finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters in procedure: scegli_scheda_archiviata", true);
        goto err;
    }

    // Execution
    if (mysql_stmt_execute(prepared_stmt) != 0) {
        print_stmt_error(prepared_stmt, "Error in execution for procedure: scegli_scheda_archiviata");
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

bool startWorkout(workoutCustomer *workUser){
	MYSQL_STMT* prepared_stmt;
	MYSQL_BIND param[4];

	// Prepare stored procedure call
	if (!setup_prepared_stmt(&prepared_stmt, "call inizia_sessione(?, ?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prepared statement for procedure: inizia_sessione", false);
		goto err1;
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[0].buffer = workUser->cf;
	param[0].buffer_length = strlen(workUser->cf);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING; // OUT
	param[1].buffer = workUser->dataInizioScheda;
	param[1].buffer_length = strlen(workUser->dataInizioScheda);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING; // OUT
	param[2].buffer = workUser->dataSessione;
	param[2].buffer_length = strlen(workUser->dataSessione);

	param[3].buffer_type = MYSQL_TYPE_VAR_STRING; // OUT
	param[3].buffer = workUser->orarioInizio;
	param[3].buffer_length = strlen(workUser->orarioInizio);


	// Binding
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters in procedure: inizia_sessione", true);
		goto err;
	}

	// Execution
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Error in execution for procedure: inizia_sessione");
		goto err;
	}

	// Prepare output params
	memset(param, 0, sizeof(param));
	param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // OUT
	param[0].buffer = workUser->dataInizioScheda;
	param[0].buffer_length = DATE_SIZE - 1;

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING; // OUT
	param[1].buffer = workUser->dataSessione;
	param[1].buffer_length = DATE_SIZE - 1;

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING; // OUT
	param[2].buffer = workUser->orarioInizio;
	param[2].buffer_length = TIME_SIZE - 1;


	// Binding res
	if (mysql_stmt_bind_result(prepared_stmt,param)){
		print_stmt_error(prepared_stmt, "Could not retrieve output in procedure: inizia_sessione");
		goto err;
	}

	// Retrieve output parameter
	if (mysql_stmt_fetch(prepared_stmt)){
		print_stmt_error(prepared_stmt, "Could not buffer result in procedure: inizia_sessione");
		goto err;
	}
	dump_result_set(conn, prepared_stmt, "");
	mysql_stmt_next_result(prepared_stmt);
	mysql_stmt_close(prepared_stmt);
	return true;
err:
	mysql_stmt_close(prepared_stmt);
err1:
	return false;
}

bool createNewRoutine(User *loggedUser, char *Cliente, char dataInizioScheda[DATE_SIZE]){
	MYSQL_STMT* prepared_stmt;
	MYSQL_BIND param[3];

	// Prepare stored procedure call
	if (!setup_prepared_stmt(&prepared_stmt, "call crea_nuova_scheda(?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prepared statement for procedure: crea_nuova_scheda", false);
		goto err1;
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[0].buffer = Cliente;
	param[0].buffer_length = strlen(Cliente);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[1].buffer = loggedUser->cf;
	param[1].buffer_length = strlen(loggedUser->cf);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING; // OUT
	param[2].buffer = dataInizioScheda;
	param[2].buffer_length = strlen(dataInizioScheda);
	

	// Binding
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters in procedure: crea_nuova_scheda", true);
		goto err;
	}

	// Execution
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Error in execution for procedure: crea_nuova_scheda");
		goto err;
	}

	// Prepare output params
	memset(param, 0, sizeof(param));
	param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // OUT
	param[0].buffer = dataInizioScheda;
	param[0].buffer_length = DATE_SIZE - 1;

	// Binding res
	if (mysql_stmt_bind_result(prepared_stmt,param)){
		print_stmt_error(prepared_stmt, "Could not retrieve output in procedure: crea_nuova_scheda");
		goto err;
	}

	// Retrieve output parameter
	if (mysql_stmt_fetch(prepared_stmt)){
		print_stmt_error(prepared_stmt, "Could not buffer result in procedure: crea_nuova_scheda");
		goto err;
	}

	mysql_stmt_close(prepared_stmt);
	return true;
err:
	mysql_stmt_close(prepared_stmt);
err1:
	return false;

}

bool recoverSessionData(workoutCustomer *workUser){
	MYSQL_STMT* prepared_stmt;
	MYSQL_BIND param[4];
	
	// Prepare stored procedure call
	if (!setup_prepared_stmt(&prepared_stmt, "call recupera_dati_sessione(?, ?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prepared statement for procedure: recupera_dati_sessione", false);
		goto err1;
	}
	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[0].buffer = workUser->cf;
	param[0].buffer_length = strlen(workUser->cf);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING; // OUT
	param[1].buffer = workUser->dataSessione;
	param[1].buffer_length = strlen(workUser->dataSessione);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING; // OUT
	param[2].buffer = workUser->dataInizioScheda;
	param[2].buffer_length = strlen(workUser->dataInizioScheda);

	param[3].buffer_type = MYSQL_TYPE_VAR_STRING; // OUT
	param[3].buffer = workUser->orarioInizio;
	param[3].buffer_length = strlen(workUser->orarioInizio);


	// Binding
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters in procedure: recupera_dati_sessione", true);
		goto err;
	}

	// Execution
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Error in execution for procedure: recupera_dati_sessione");
		goto err;
	}

	// Prepare output params
	param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // OUT
	param[0].buffer = workUser->dataSessione;
	param[0].buffer_length = DATE_SIZE - 1;

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING; // OUT
	param[1].buffer = workUser->dataInizioScheda;
	param[1].buffer_length = DATE_SIZE - 1;

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING; // OUT
	param[2].buffer = workUser->orarioInizio;
	param[2].buffer_length = TIME_SIZE - 1;

	// Binding res
	if (mysql_stmt_bind_result(prepared_stmt,param)){
		print_stmt_error(prepared_stmt, "Could not retrieve output in procedure: recupera_dati_sessione");
		goto err;
	}
	
	// Retrieve output parameter
	if (mysql_stmt_fetch(prepared_stmt)){
		print_stmt_error(prepared_stmt, "Could not buffer result in procedure: recupera_dati_sessione");
		goto err;
	}

	dump_result_set(conn, prepared_stmt, "");
	mysql_stmt_next_result(prepared_stmt);
    
	mysql_stmt_close(prepared_stmt);
	return true;
err:
	mysql_stmt_close(prepared_stmt);
err1:
	return false;
}


bool completedRoutine(char *Cliente, Date *date){
		MYSQL_STMT* prepared_stmt;
	MYSQL_BIND param[2];
	
	// Prepare stored procedure call
	if (!setup_prepared_stmt(&prepared_stmt, "call scheda_completata(?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prepared statement for procedure: scheda_completata", false);
		goto err1;
	}
	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[0].buffer = Cliente;
	param[0].buffer_length = strlen(Cliente);

	MYSQL_TIME mysqlDate;
    prepareDateParam(date, &mysqlDate);

	param[1].buffer_type = MYSQL_TYPE_DATE; 		//IN
	param[1].buffer = &mysqlDate;
	param[1].buffer_length = sizeof(MYSQL_TIME);

	// Binding
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters in procedure: scheda_completata", true);
		goto err;
	}

	// Execution
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Error in execution for procedure: scheda_completata");
		goto err;
	}

	dump_result_set(conn, prepared_stmt, "");
	mysql_stmt_next_result(prepared_stmt);
    
	mysql_stmt_close(prepared_stmt);
	return true;
err:
	mysql_stmt_close(prepared_stmt);
err1:
	return false;
}

bool insertExercise(char Cliente[USERNAME_MAX_SIZE], Date *date, char esercizio[EXERCISE_MAX_SIZE], int *posizione, int *serie, int *ripetizioni){
	MYSQL_STMT* prepared_stmt;
    MYSQL_BIND param[6];

	// Prepare stored procedure call
    if (!setup_prepared_stmt(&prepared_stmt, "call inserisci_esercizio(?, ?, ?, ?, ?, ?)", conn)) {
        finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prepared statement for procedure: inserisci_esercizio", false);
        goto err1;
    }

	// Prepare parameters
    memset(param, 0, sizeof(param));


    param[0].buffer_type = MYSQL_TYPE_STRING; 	//IN
    param[0].buffer = Cliente;
    param[0].buffer_length = strlen(Cliente);

	param[1].buffer_type = MYSQL_TYPE_STRING; 	//IN
    param[1].buffer = esercizio;
    param[1].buffer_length = strlen(esercizio);

	param[2].buffer_type = MYSQL_TYPE_LONG; 		//IN
    param[2].buffer = ripetizioni;
    param[2].buffer_length = sizeof(ripetizioni);
	
	param[3].buffer_type = MYSQL_TYPE_LONG; 		//IN
    param[3].buffer = serie;
    param[3].buffer_length = sizeof(serie);

	param[4].buffer_type = MYSQL_TYPE_LONG; 		//IN
    param[4].buffer = posizione;
    param[4].buffer_length = sizeof(posizione);
	
	MYSQL_TIME mysqlDate;
    prepareDateParam(date, &mysqlDate);

	param[5].buffer_type = MYSQL_TYPE_DATE; 		//IN
	param[5].buffer = &mysqlDate;
	param[5].buffer_length = sizeof(MYSQL_TIME);

	// Binding
    if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
        finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters in procedure: inserisci_esercizio", true);
        goto err;
    }
    
    // Execution
    if (mysql_stmt_execute(prepared_stmt) != 0) {

		print_stmt_error(prepared_stmt, "Error in execution for procedure: inserisci_esercizio");
        goto err;
    }
	
	mysql_stmt_next_result(prepared_stmt);
    mysql_stmt_close(prepared_stmt);
    return true;

err:
    mysql_stmt_close(prepared_stmt);
err1:
    return false;
}

bool retrieveReport(User *loggedUser,Date *date1, Date *date2){
	MYSQL_STMT* prepared_stmt;
	MYSQL_BIND param[3];
	
	// Prepare stored procedure call
	if (!setup_prepared_stmt(&prepared_stmt, "call genera_report(?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prepared statement for procedure: genera_report", false);
		goto err1;
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[0].buffer = loggedUser->cf;
	param[0].buffer_length = strlen(loggedUser->cf);

	MYSQL_TIME mysqlDate1;
    prepareDateParam(date1, &mysqlDate1);

	param[1].buffer_type = MYSQL_TYPE_DATE; //IN
	param[1].buffer = &mysqlDate1;
	param[1].buffer_length = sizeof(MYSQL_TIME);

	MYSQL_TIME mysqlDate2;
    prepareDateParam(date2, &mysqlDate2);

	param[2].buffer_type = MYSQL_TYPE_DATE; //IN
	param[2].buffer = &mysqlDate2;
	param[2].buffer_length = sizeof(MYSQL_TIME);

	// Binding
    if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
        finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters in procedure: genera_report", true);
        goto err;
    }

    // Execution
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Error in execution for procedure: genera_report");
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


bool printAllNotCompletedRoutines(User *loggedUser){
	MYSQL_STMT* prepared_stmt;
    MYSQL_BIND param[1];

    // Prepare stored procedure call
    if (!setup_prepared_stmt(&prepared_stmt, "call visualizza_schede_non_completate(?)", conn)) {
        finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prepared statement for procedure: visualizza_schede_non_completate", false);
        goto err1;
    }

    // Prepare parameters
    memset(param, 0, sizeof(param));

    param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
    param[0].buffer = loggedUser->cf;
    param[0].buffer_length = strlen(loggedUser->cf);

    // Binding
    if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
        finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters in procedure: visualizza_schede_non_completate", true);
        goto err;
    }

    // Execution
    if (mysql_stmt_execute(prepared_stmt) != 0) {
        print_stmt_error(prepared_stmt, "Error in execution for procedure: visualizza_schede_non_completate");
        goto err;
    }

    // Fetch and print the results
	dump_result_set(conn, prepared_stmt, "\n\nECCO TUTTE LE SCHEDE NON COMPLETE CHE PUOI MODIFICARE");
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

bool displayMissingExercises(workoutCustomer *workUser){
	MYSQL_STMT* prepared_stmt;
	MYSQL_BIND param[3];

	// Prepare stored procedure call
	if (!setup_prepared_stmt(&prepared_stmt, "call visualizza_esercizi_mancanti(?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prepared statement for procedure: visualizza_esercizi_mancanti", false);
		goto err1;
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[0].buffer = workUser->cf;
	param[0].buffer_length = strlen(workUser->cf);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[1].buffer = workUser->dataSessione;
	param[1].buffer_length = strlen(workUser->dataSessione);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[2].buffer = workUser->dataInizioScheda;
	param[2].buffer_length = strlen(workUser->dataInizioScheda);


	// Binding
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters in procedure: visualizza_esercizi_mancanti", true);
		goto err;
	}

	// Execution
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Error in execution for procedure: visualizza_esercizi_mancanti");
		goto err;
	}

	dump_result_set(conn, prepared_stmt, "\n");
	mysql_stmt_next_result(prepared_stmt);
	mysql_stmt_close(prepared_stmt);
	return true;
err:
	mysql_stmt_close(prepared_stmt);
err1:
	return false;
}

bool displayMissingSets(workoutCustomer *workUser, char* esercizio){
    MYSQL_STMT* prepared_stmt;
	MYSQL_BIND param[4];

	// Prepare stored procedure call
	if (!setup_prepared_stmt(&prepared_stmt, "call visualizza_serie_mancanti(?, ?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prepared statement for procedure: visualizza_serie_mancanti", false);
		goto err1;
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[0].buffer = workUser->cf;
	param[0].buffer_length = strlen(workUser->cf);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[1].buffer = esercizio;
	param[1].buffer_length = strlen(esercizio);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[2].buffer = workUser->dataSessione;
	param[2].buffer_length = strlen(workUser->dataSessione);

	param[3].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[3].buffer = workUser->dataInizioScheda;
	param[3].buffer_length = strlen(workUser->dataInizioScheda);

	// Binding
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters in procedure: visualizza_serie_mancantiv", true);
		goto err;
	}

	// Execution
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Error in execution for procedure: visualizza_serie_mancanti");
		goto err;
	}

	// Dump of the result set
	dump_result_set(conn, prepared_stmt, "\n");
	mysql_stmt_next_result(prepared_stmt);
	mysql_stmt_close(prepared_stmt);
	return true;
err:
	mysql_stmt_close(prepared_stmt);
err1:
	return false;
}

bool getPtCf(User* loggedUser) {
    MYSQL_STMT* prepared_stmt;
    MYSQL_BIND param[2];

    // Prepare stored procedure call
    if (!setup_prepared_stmt(&prepared_stmt, "call prendi_pt_cf(?)", conn)) {
        finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prepared statement for procedure: prendi_pt_cf", false);
        goto err1;
    }

    // Prepare parameters
    memset(param, 0, sizeof(param));

    param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
    param[0].buffer = loggedUser->username;
    param[0].buffer_length = strlen(loggedUser->username);

    param[1].buffer_type = MYSQL_TYPE_VAR_STRING; // OUT
    param[1].buffer = loggedUser->cf;
    param[1].buffer_length = sizeof(loggedUser->cf);

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
    param[0].buffer = loggedUser->cf;
    param[0].buffer_length = sizeof(loggedUser->cf);

    if (mysql_stmt_bind_result(prepared_stmt, param)) {
        print_stmt_error(prepared_stmt, "Could not retrieve output in procedure: prendi_pt_cf");
        goto err;
    }

    // Retrieve output parameter
    if (mysql_stmt_fetch(prepared_stmt)) {
        print_stmt_error(prepared_stmt, "Could not buffer results in procedure: prendi_pt_cf");
        goto err;
    }


    mysql_stmt_close(prepared_stmt);
    return true;

err:
    mysql_stmt_close(prepared_stmt);
err1:
    return false;
}


bool displayRoutine(User *loggedUser, User *cliente){
	MYSQL_STMT* prepared_stmt;
    MYSQL_BIND param[2];

    // Prepare stored procedure call
    if (!setup_prepared_stmt(&prepared_stmt, "call pt_visualizza_scheda_attiva(?, ?)", conn)) {
        finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize prepared statement for procedure: pt_visualizza_scheda_attiva", false);
        goto err1;
    }

    // Prepare parameters
    memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
    param[0].buffer = cliente->cf;
    param[0].buffer_length = strlen(cliente->cf);

    param[1].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
    param[1].buffer = loggedUser->cf;
    param[1].buffer_length = strlen(loggedUser->cf);

    // Binding
    if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
        finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters in procedure: pt_visualizza_scheda_attiva", true);
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
