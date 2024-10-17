#include <stdio.h>
#include <stdlib.h>
#include <postgresql/libpq-fe.h>
#include "headers/message.h"
#include "headers/posgres.h"

// Connexion à la base de données

PGconn *connectToDatabase() {
    PGconn *conn;
    // Connection parameters
    const char *const keywords[] = {"host","dbname", "user", "password", NULL};
    const char *const values[] = {HOST, DBNAME, USER, PASSWORD, NULL};
    conn = PQconnectdbParams(keywords, values,0);
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Erreur de connexion à la base de données : %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        return NULL;
    }
    return conn;
}

// Insertion dans la base de données
int insertIntoDatabase(Message *message) {
    if (!message)
        return 0;
    PGconn *conn = connectToDatabase();
        if (!conn)
            return 0;
    char query[10024];
    sprintf(query, "INSERT INTO message (id, content, time) VALUES (%lld, '%s', '%s')",
     message->id, message->content, message->timesmessage);
    PGresult *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        //fprintf(stderr, "Erreur d'insertion dans la base de données : %s\n", PQerrorMessage(conn));
        PQclear(res);
        return 0;
    }
    PQclear(res);
    PQfinish(conn);
    return 1;
}

// Récupération de données depuis la base de données
PGresult *retrieveFromDatabase(long long int id) {
    PGconn *conn = connectToDatabase();
    if (conn == NULL)
        return NULL;
    char query[500];
    sprintf(query, "SELECT content, time FROM message where id=%lld", id);
    PGresult *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        //fprintf(stderr, "Erreur de récupération depuis la base de données : %s\n", PQerrorMessage(conn));
        PQclear(res);
        return NULL;
    }
    if ( PQntuples(res) == 0)
        return NULL;
    PQfinish(conn);
    return res;
}

// Suppression dans la base de données
int deleteFromDatabase(long long id){
    PGconn *conn = connectToDatabase();
        if (conn == NULL)
            return 0;
    char query[50];
    sprintf(query, "DELETE FROM message where id= %lld", id);
    PGresult *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Erreur de suppression depuis la base de données : %s\n", PQerrorMessage(conn));
        PQclear(res);
        return 0;
    }
    int row_deleted = atoi(PQcmdTuples(res));
    if (row_deleted == 0)
        return 0;
    PQclear(res);
    PQfinish(conn);
    return 1;
}
void clearTable() {
     PGconn *conn = connectToDatabase();
        if (conn == NULL)
            exit(1);

    const char *truncateQuery = "TRUNCATE TABLE message;";
    PGresult *res = PQexec(conn, truncateQuery);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        printf("Table truncation failed: %s\n", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }

    PQclear(res);
}
