#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>
#include <stdbool.h>
#include "../model/structs.h"
#include "../view/viewUtils.h"

bool getDateFromUser(Date *date);

bool getInput(char *requestString, char *resultBuffer, int bufferSize);

bool getInteger(char* domanda, int *integerPtr);

bool getLoginCredentials(Credentials *creds);

bool getRegCredentials(User *user);
