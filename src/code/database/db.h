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

bool registerNewPt(User user);

bool displayRoutine(User *loggedUser, User *cliente);

bool showOldRoutines(User *user, int *num);

bool displayNewRoutine(User *loggedUser); //valuta di mettere già qua dentro il codice fiscale

bool retrieveReport(User *loggedUser,Date *date1, Date *date2);

bool scegliSchedaArchiviata(User *loggedUser, Date *date);

bool startWorkout(workoutCustomer *workUser);

bool completedRoutine(char *Cliente, Date *date);

bool performExercise(workoutCustomer *workUser, char *esercizio);

bool endWorkout(workoutCustomer *workUser);

bool getPtCf(User *loggedUser);

bool addSetToExercise(workoutCustomer *workUser, char *esercizio, int *numeroSerie);

bool displayMissingSets(workoutCustomer *workUser, char *esercizio);

bool getCustomerCf(User *loggedUser);

bool archiveRoutine(User *loggedUser, char *cf);

bool createNewRoutine(User *loggedUser, char *Cliente, char dataInizioScheda[DATE_SIZE]);

bool showAllMyCustomers(User *loggedUser);

bool recoverSessionData(workoutCustomer *workUser);

bool addGymExercise(char esercizio[EXERCISE_MAX_SIZE]);

bool displayAllExercises();

bool printAllNotCompletedRoutines(User *loggedUser);

bool chooseNotCompletedRoutine(char cliente[USERNAME_MAX_SIZE], char data[DATE_SIZE], int *maxPosition);

bool insertExercise(char Cliente[USERNAME_MAX_SIZE], Date *date, char esercizio[EXERCISE_MAX_SIZE], int *i, int *serie, int *ripetizioni);