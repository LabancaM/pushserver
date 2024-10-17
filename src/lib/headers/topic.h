#ifndef TOPICS_H
#define TOPICS_H
#define MAX_TOPIC_NAME_LEN 128
#include <sys/queue.h>
#include "message.h"
#include "client.h"



typedef SLIST_HEAD(message_list, Message_t) message_list_t;
typedef SLIST_HEAD(client_list, Client_t) client_list_t;
/**
 * struct Topic - topic of messages
 * 
 * @name: name of topic
 * @description: description of topic
 * @messages: list of topic message's
 * @clients: list of topic client's
 */
typedef struct Topic_t{
    char name[MAX_TOPIC_NAME_LEN];
    message_list_t list_message;
    client_list_t list_client;
    SLIST_ENTRY(Topic_t) next;
} Topic;

Topic* createTopic(char *name);
int addMessages(Topic* topic, Message* message);
int pushMessages(Topic* topic, Message* message);
int subscribe(char* topic_name, Client* client);
int unsubscribe(char* topic_name, Client* client);
int deleteTopic(char* topic_name);
typedef SLIST_HEAD(topic_list, Topic_t) topic_list_t;
extern topic_list_t list_topic;
int numberOfTopic(topic_list_t list_topic);
int numberOfTopicMessage(Topic *topic);
int numberOfTopicClient(Topic *topic);
#endif
