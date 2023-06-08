#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <mysql/mysql.h>
#include "../database/dbUtils.h"
#include "../view/viewUtils.h"
#include "inout.h"

#define DB_HOST "DB.HOST"
#define DB_PORT "DB.PORT"
#define DB_NAME "DB.NAME"

#define DB_UTENTI_USER "UTENTI.USER"
#define DB_UTENTI_PASSWD "UTENTI.PASSWD" 

#define DB_PT_USER "PT.USER"
#define DB_PT_PASSWD "PT.PASSWD"

#define DB_CLIENTI_USER "CLIENTI.USER"
#define DB_CLIENTI_PASSWD "CLIENTI.PASSWD"

#define DB_SEGRETERIA_USER "SEGRETERIA.USER"
#define DB_SEGRETERIA_PASSWD "SEGRETERIA.PASSWD"

extern MYSQL *conn ;

bool connectToDatabase() ;