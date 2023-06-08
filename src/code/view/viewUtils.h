#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void clearScreen() ;

void printBoldRed(char *str);

void printError(char *errorMessage);

void printSuccess (char *successMessage);

void showAppTitle() ;

void printWinningTrophy();

void printConqueredTerritory();

void printAttackResults(char *terr1, char *terr2, int carriPersiAtt, int carrPersiDif);
