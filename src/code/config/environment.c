#include "environment.h"

const char *CONFIGURATION_FILE_NAME = "code/config/configuration.properties" ;

bool setEnvironmentVariable(char *environmentToken) ;

bool loadConfiguration() {
    // Open configuration file to prepare env
    FILE *configurationFile = fopen(CONFIGURATION_FILE_NAME, "r") ;
    if (configurationFile == NULL) {
        fprintf(stderr, "Errore apertura file\n") ;
        return false ;
    }

    char *environmentLine = NULL ;
    size_t len ;
    ssize_t nread = getline(&environmentLine, &len, configurationFile) ;
    while (nread > 0) {
        char *environmentToken = strtok(environmentLine, "\n") ;
        
        if (setEnvironmentVariable(environmentToken) == false) {
            free(environmentLine) ;
            fclose(configurationFile) ;
            return false ;
        }

        nread = getline(&environmentLine, &len, configurationFile) ;
    }
    //getline alloca memoria quando viene passata un NULL come puntatore --> libero memoria allocata
    free(environmentLine) ;

    fclose(configurationFile) ;
    return true ;
}


bool setEnvironmentVariable(char *environmentToken) {
    //Function to parse Environment Variable from configuration file
    char *tokenName = strtok(environmentToken, "=") ;
    char *tokenValue = strtok(NULL, "=") ;

    if (setenv(tokenName, tokenValue, 0)) {
        printf("Errore Impostazione Variabile d'Ambiente\n") ;
        return false ;
    }
    return true ;
}
