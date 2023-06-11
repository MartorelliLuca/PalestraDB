#include <mysql/mysql.h>
#include "../controller/loginController.h"
#include "../engineering/connector.h"
#include <string.h>
#include <stdio.h>
#include "../engineering/inout.h"
#include "../model/structs.h"
#include "dbUtils.h"
#include "../view/viewUtils.h"

#define VARCHAR45 45 + 1

Role logAsUser(Credentials creds);

bool registerNewPlayer(Credentials creds);

bool registerNewCustomer(User user);

bool createNewGameRoom(char *nomeStanza);

bool showOldRoutines(User *user, int *num);

bool visualizzaSchedaAttiva(User *loggedUser); //valuta di mettere già qua dentro il codice fiscale

bool retrieveReport();

bool scegliSchedaArchiviata(User *loggedUser);

bool startWorkout(workoutCustomer *workUser);

bool skipTurn(char *username);

bool performExercise(workoutCustomer *workUser, char *esercizio);

bool leaveMatch(char *username);

bool attackTerritory(char *username, int *num_carri, char *terr1, char *terr2, int *num_army_loss_attack, int *num_army_loss_defense,int *is_conquered, int *i_won);

bool placeArmyOnTerritory(char *username, int *num_carri, char *terr);

bool moveArmyBetweenTerritories(char *username, int *num_carri, char *terr1, char *terr2);

bool showAdjacentTerritories(char *terr);

bool getCustomerCf(User *loggedUser);