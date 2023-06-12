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

bool displayMissingExercises(workoutCustomer *workUser);

bool registerNewCustomer(User user);

bool createNewGameRoom(char *nomeStanza);

bool showOldRoutines(User *user, int *num);

bool displayNewRoutine(User *loggedUser); //valuta di mettere già qua dentro il codice fiscale

bool retrieveReport();

bool scegliSchedaArchiviata(User *loggedUser, Date *date);

bool startWorkout(workoutCustomer *workUser);

bool skipTurn(char *username);

bool performExercise(workoutCustomer *workUser, char *esercizio);

bool endWorkout(workoutCustomer *workUser);

bool getPtCf(User *loggedUser);

bool addSetToExercise(workoutCustomer *workUser, char *esercizio, int *numeroSerie);

bool moveArmyBetweenTerritories(char *username, int *num_carri, char *terr1, char *terr2);

bool displayMissingSets(workoutCustomer *workUser, char *esercizio);

bool getCustomerCf(User *loggedUser);