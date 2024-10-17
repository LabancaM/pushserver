#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/queue.h>
#include <hiredis/hiredis.h>
#include "headers/message.h"
#include "headers/topic.h"
#include "postgresql/libpq-fe.h"
#include "headers/filter.h"

char** countMessage(Topic *topic){
    int count = 0;
    char message[200];
    char *value;
    char **tab;
    if (!topic)
        return 0;
    Message *current = SLIST_FIRST(&topic->list_message);
    while (current){
        if(!readMessage(current->id)){
            SLIST_REMOVE_HEAD(&topic->list_message, next);
            current = SLIST_NEXT(current, next);
            continue;
        }
        count++;
        current = SLIST_NEXT(current, next);
    }
    free(current);
    snprintf(message, sizeof(message), "vous avez recu %d\
    message(s) sur le topic %s", count, topic->name);
    value = (char*) malloc(strlen(message) + 1);
    strncpy(value, message, strlen(message));
    tab = (char**)malloc(2 * sizeof(char*));
    tab[0] = value;
    tab[1] = NULL;
    return tab;
    //return value;
}
char** lastMessage(Topic *topic){
    int length;
    char *value;
    char **tab;
    tab = (char**)malloc(2 * sizeof(char*));
    if (!topic)
        return 0;
    Message* message = (Message*) malloc(sizeof(Message));
    if (!message)
        return 0;
    if (!SLIST_EMPTY(&topic->list_message)) {
        message = SLIST_FIRST(&topic->list_message);
        while(!readMessage(message->id)){
            SLIST_REMOVE_HEAD(&topic->list_message, next);
            message = SLIST_FIRST(&topic->list_message);
        }
        if (!message)
            return 0;
        length = strlen(topic->name) + strlen(message->timesmessage); 
        length =+ strlen(message->content) ;
        char *save = "le dernier message sur le topic '%s' est: \n %s \n Heure: %s\n";
        length += strlen(save);
        char content[++length * 2];
        snprintf(content, sizeof(content), "le dernier message sur le topic '%s' est: %s Heure: %s\n",
         topic->name, message->content, message->timesmessage);
        value = (char*) malloc(strlen(content) + 1);
        strncpy(value, content, strlen(content));
        free(message);
        tab[0] = value;
        tab[1] = NULL;
        return tab;
        //return value;
    }
    else
    {
        tab[0] = "Pas de message recu";
        tab[1] = NULL;
        return tab;
    }
        
    return 0;  
}

char** allMessage(Topic *topic){
     if (!topic)
        return 0;
    const int count = numberOfTopicMessage(topic);
    int length;
    char **tab;
    char *value;
    if (!topic)
        return 0;
    Message *current = SLIST_FIRST(&topic->list_message);
    if (!current){
        tab = (char**)malloc(2 * sizeof(char*));
        tab[0] = "Pas de message publié";
        tab[1] = NULL;
        return tab;
    }
    int i = 0; 
    tab = (char**) malloc(count * sizeof(char*) + 1);
    while (current){
        if(!readMessage(current->id)){
            SLIST_REMOVE_HEAD(&topic->list_message, next);
            current = SLIST_NEXT(current, next);
            continue;
        }
        length = strlen(topic->name) + strlen(current->timesmessage); 
        length += (strlen(current->content) + 50);
        char *save = "Topic '%s':\nHeure et date d'envoie: %s\nContenue: %s\n\n";
        length += strlen(save);
        char content [++length * 2];
        snprintf(content, sizeof(content), save,
         topic->name, current->timesmessage, current->content);
        tab[i] = (char*) malloc(strlen(content) + 1); 
        strncpy(tab[i], content, strlen(content));
        i++;
        current = SLIST_NEXT(current, next);
    }
    free(current);
    tab[count] = NULL;
    return tab;
}
