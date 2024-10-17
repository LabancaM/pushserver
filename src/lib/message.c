#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <postgresql/libpq-fe.h>
#include "headers/message.h"
#include "headers/posgres.h"

Message* createMessage(char *content) {
    Message *message;
    time_t currentTime;
    struct tm *localTime;
    int length_time;
    if (!content || !*content)
        return 0;
    if (!(message=(Message*)malloc(sizeof(Message))))
        return 0;
    snprintf(message->content, MAX_MESSAGE_LENGTH, "%s", content);
    // Get the current time
    currentTime = time(NULL);
    localTime = localtime(&currentTime);
    length_time = strlen(asctime(localTime));
    snprintf(message->timesmessage, length_time, "%s", asctime(localTime));
    message->id = ++next_id;  
    return message;
}

int storeMessage(Message* message){
    if (!message)
        return 0;
    insertIntoDatabase(message);
}

PGresult* readMessage(long long int id) {
    retrieveFromDatabase(id);
}

int deleteMessage(long long int id) {
    deleteMessage(id);
}