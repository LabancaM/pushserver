#ifndef NOTIFICATIONSERVICES_H
#define NOTIFICATIONSERVICES_H
#include <sys/queue.h>
#include "topic.h"
#include "message.h"
#include "client.h"

typedef struct Notificationservices{
    Topic* (*createTopics)(char *name);
    int (*deleteTopics)(char *name);
    int (*subscribes)(Topic* topic, Client* client);
    int (*unsubscribes)(Topic* topic, Client* client);
    void (*validadeToken)();
    void (*checkRigth)();
} Notificationservices;
int sendNotification(Topic* topic);
int typeNoficication(Client *client, char *message);
char** typeFilter(Client *client, Topic *topic);
#endif