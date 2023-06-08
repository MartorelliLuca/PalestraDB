#pragma once

#define USERNAME_MAX_SIZE 20 + 1
#define PASSWORD_MAX_SIZE 45 + 1

typedef struct {
    char username[USERNAME_MAX_SIZE] ;
    char password[PASSWORD_MAX_SIZE] ;
} Credentials ;

typedef enum {
    SEGRETERIA = 0,
    PT = 1,
    CLIENTI = 2,
    UTENTI = 3
} Role ;
