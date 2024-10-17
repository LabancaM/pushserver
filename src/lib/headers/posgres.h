#ifndef POSGRES_H
#define POSGRES_H
#include "message.h"
#define HOST "127.0.0.1"
#define USER "marc"
#define PASSWORD "totototo"
#define PORT 5432
#define DBNAME "labanca"

PGconn *connectToDatabase();
int insertIntoDatabase(Message *message);
PGresult *retrieveFromDatabase(long long int id);
int deleteFromDatabase(long long id);
void clearTable();
#endif