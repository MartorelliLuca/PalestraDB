#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>
#include <stdbool.h>
#include "../model/credentials.h"
#include "../view/viewUtils.h"

void toUpperCase(char *str);

char multiChoice(char* domanda, char choices[], int num);

bool getInput(char *requestString, char *resultBuffer, int bufferSize);

bool getInteger(char* domanda, int *integerPtr);

bool getCredentials(Credentials *creds);

bool getAttackInfo(char *terr1, char *terr2, int *num_carri);

bool getMoveArmyInfo(int *num_carri, char *terr1, char *terr2);

bool getPositionArmyInfo(char *terr, int *num_carri);