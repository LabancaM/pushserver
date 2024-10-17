#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/queue.h>
#include <postgresql/libpq-fe.h>
#include "headers/topic.h"
#include "headers/notification.h"
#include "headers/notificationservices.h"
#include "headers/filter.h"
#include "headers/message.h"
#include "headers/posgres.h"

/**
 * @list_topics: List of all topics.
 */
//SLIST_HEAD(TopicHead, Topic) list_topics = SLIST_HEAD_INITIALIZER(list_topics);
topic_list_t list_topic = SLIST_HEAD_INITIALIZER(list_topic);
/**
 * createTopic - initialization of topic
 *
 * @name: name of topic
 *
 * Return: A pointer to the newly created topic, or NULL if an error occurred.
 */

Topic* createTopic(char* name){
    Topic *topic;
    Topic *current = SLIST_FIRST(&list_topic);
    if (!name || !*name)
        return 0;
    
    if (!(topic=(Topic*)malloc(sizeof(Topic))))
        return 0;
    //check if topic is yet existed
    while (current != NULL) {
        if (strcmp(current->name, name) == 0)
            return 0;
        current = SLIST_NEXT(current, next);
    }
    // copy name in topic name
    snprintf(topic->name, MAX_TOPIC_NAME_LEN, "%s", name);
    //initialisation list of message
    SLIST_INIT(&topic->list_message);
    //initialisation list of client
    SLIST_INIT(&topic->list_client);
    //insert topic in the list of topic
    SLIST_INSERT_HEAD(&list_topic, topic, next);
    insertTopicInRedis(name);
    return topic;
}

/**
 * addMessages - add message to topic message list
 *
 * @topic: topic
 * @message: message to add
 *
 * Return: 1 if is successfull otherwise 0
 */
int addMessages(Topic* topic, Message* message){
    if (!topic  || !message)
        return 0;
    //insert message in database
    insertIntoDatabase(message);
    //insert  message topic list of message
    SLIST_INSERT_HEAD(&topic->list_message, message, next);
    if (sendNotification(topic)){
        deleteMessage(message->id);
    }
    return 1;
}
int pushMessages(Topic* topic, Message* message){
    if (!topic  || !message)
        return 0;
    SLIST_INSERT_HEAD(&topic->list_message, message, next);
    return 1;
}

/**
 * subscribe - suscribe to topic
 *
 * @topic: topic
 * @client: suscribe client
 *
 * Return: 1 if is successfull add otherwise 0
 */
int subscribe(char* topic_name, Client* client){
    if (!topic_name  || !*topic_name || !client)
        return 0;
    Topic* current = SLIST_FIRST(&list_topic);
    while(current != NULL){
        // search if client exists
        Client* current_client =SLIST_FIRST(&current->list_client);    
        while (current_client != NULL) {
            if (current_client->id == client->id) 
                return 0;
            current_client = SLIST_NEXT(current_client, next);
        }
        if(strcmp(current->name, topic_name) == 0){
            SLIST_INSERT_HEAD(&current->list_client, client, next);
            return 1;
        }
        current = SLIST_NEXT(current, next);
    }
    return 0;
}

/**
 * unsubscribe - unsuscribe to topic
 *
 * @topic: topic
 * @client: unsuscribe client
 *
 * Return: 0 if is successfull add otherwise 1
 */
int unsubscribe(char* topic_name, Client* client){
    // chech if name or client is null
    if (!topic_name  || !*topic_name || !client)
        return 0;
    // search if topic exist
    Topic* current_topic =SLIST_FIRST(&list_topic);
    while(current_topic != NULL){
        if(strcmp(current_topic->name, topic_name) == 0){
            Client* current_client =SLIST_FIRST(&current_topic->list_client);
            // search if client exists
            while (current_client != NULL) {
                if (current_client->id == client->id) {
                    SLIST_REMOVE(&current_topic->list_client, current_client, Client_t, next);
                    return 1;
                }
                current_client = SLIST_NEXT(current_client, next);
            }
            return 0;
        }
        current_topic = SLIST_NEXT(current_topic, next);
    }
    return 0;
}

/**
 * deleteTopic - delete topic
 *
 * @name: name of topic
 *
 * Return: 1 if is successfull delete otherwise 0
 */
int deleteTopic(char* topic_name){
    Topic *topic;
    if (!topic_name || !*topic_name)
        return 0;
    // Find the topic with the given name
    Topic* current_topic =SLIST_FIRST(&list_topic);
    while(current_topic != NULL){
        if(strcmp(current_topic->name, topic_name) == 0)
            break;
        current_topic = SLIST_NEXT(current_topic, next);
    }
    if (!current_topic)
        return 0;
        
    // Remove the topic from the list of topics
    SLIST_REMOVE(&list_topic, current_topic, Topic_t, next);
    // Free all messages in the topic
    Message* message;
    while (!SLIST_EMPTY(&current_topic->list_message)) {
        message = SLIST_FIRST(&current_topic->list_message);
        SLIST_REMOVE_HEAD(&topic->list_message, next);
        free(message);
    }

    // Free all clients in the topic
    Client* client;
    while (!SLIST_EMPTY(&current_topic->list_client)) {
        client = SLIST_FIRST(&current_topic->list_client);
        SLIST_REMOVE_HEAD(&current_topic->list_client, next);
        free(client);
    }
    // Free the topic itself
    free(current_topic);
    return 1;
}
// get number of topic
int numberOfTopic(topic_list_t list_topic){
    Topic *current = SLIST_FIRST(&list_topic);
    int count = 0;
    while (current != NULL) {
        count++;
        current = SLIST_NEXT(current, next);
    }
    return count;
}
int numberOfTopicMessage(Topic *topic){
    Message *current = SLIST_FIRST(&topic->list_message);
    int count = 0;
    while (current != NULL) {
        count++;
        current = SLIST_NEXT(current, next);
    }
    return count;
}
int numberOfTopicClient(Topic *topic){
    if(!topic)
        return 0;
    Client *current = SLIST_FIRST(&topic->list_client);
    int count = 0;
    while (current != NULL) {
        count++;
        current = SLIST_NEXT(current, next);
    }
    return count;
}
