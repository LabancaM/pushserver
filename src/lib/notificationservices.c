#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/queue.h>
#include <postgresql/libpq-events.h>
#include "headers/posgres.h"
#include "headers/notificationservices.h"
#include "headers/topic.h"
#include "headers/message.h"
#include "headers/client.h"
#include "headers/filter.h"
#include "headers/notification.h"


Topic* createTopics(char *name){
    return createTopic(name);
}
int deleteTopics(char *name){
    return deleteTopic(name);
}
int subscribes(Topic* topic, Client* client){
    return subscribe(topic->name, client);
}
int unsubscribes(Topic* topic, Client* client){
    return unsubscribe(topic->name, client);
}

//strategy of notification type
int typeNoficication(Client *client, char *message){
    if (!client || !message)
        return 0;
    if (client->type_notification == NOTIFICATION_EMAIL){
        emailNotification(message, "amarcayi@gmail.com");
        return 1;
    }
    else if (client->type_notification == NOTIFICATION_DIRECT)
    {
        pehoulNotification(message);
        return 1;
    }
    else if (client->type_notification == NOTIFICATION_SMS)
    {
        smsNotification(message);
        return 1;
    }
    return 0;
}

//strategy of filter type
char** typeFilter(Client *client, Topic *topic){
    if (!client || !topic)
    return 0;   
    if (client->type_filter == FILTER_COUNT_MESSAGE)
        return countMessage(topic); 
    else if (client->type_filter == FILTER_LAST_MESSAGE)
        return lastMessage(topic);
    else if (client->type_filter == FILTER_ALL_MESSAGE)
        return allMessage(topic);   
}
//void validadeToken();

// send notification to client
int sendNotification(Topic* topic){
    long long int message_id;
    if (!topic)
        return 0;
    Client *current_client = SLIST_FIRST(&topic->list_client);
    if (!current_client)
        return 0;
    int j = 0;
    while (current_client){
        //call filter
        char** messages = typeFilter(current_client, topic);
        if (!messages) {
            current_client = SLIST_NEXT(current_client, next);
            continue;
        }
        int i = 0;
        while (messages[i])
        {
            typeNoficication(current_client, messages[i]);
            i++;
        }
        current_client = SLIST_NEXT(current_client, next);
    }
    return 1;
}
//void checkRigth();