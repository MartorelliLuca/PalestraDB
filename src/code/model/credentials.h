#pragma once

#define NOME_MAX_SIZE 25 + 1
#define COGNOME_MAX_SIZE 15 + 1
#define USERNAME_MAX_SIZE 20 + 1 //Username e CF hanno stessa lunghezza massima
#define PASSWORD_MAX_SIZE 45 + 1

typedef struct {
    char username[USERNAME_MAX_SIZE] ;
    char password[PASSWORD_MAX_SIZE] ;
} Credentials ;

typedef enum {
    PT = 0,
    SEGRETERIA = 1,
    CLIENTI = 2,
    UTENTI = 3
} Role ;

typedef struct {
    char cf[USERNAME_MAX_SIZE] ;
    char nome[NOME_MAX_SIZE] ;
    char cognome[COGNOME_MAX_SIZE] ;
    char username[USERNAME_MAX_SIZE] ;
    char password[PASSWORD_MAX_SIZE] ;
} newUser ;
