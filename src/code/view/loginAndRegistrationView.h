#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../engineering/inout.h"
#include "viewUtils.h"

bool promptLogin(Credentials *creds) ;
bool promptReg(User *loggedUser) ;

int promptInitialMenu();