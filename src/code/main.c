#include "main.h"

int main() {
    clearScreen();
    if (!loadConfiguration()) {
        printError("Errore: Configurazione Ambiente Non Riuscita!") ;
        exit(-1);
    }
    if (connectToDatabase()) {
        loginController() ;
    }
}


