#ifndef CLIENT_H
#define CLIENT_H
#define CONSUMER 1
#define PRODUCER 2
#define NOTIFICATION_DIRECT 1
#define NOTIFICATION_EMAIL 2
#define NOTIFICATION_SMS 3
#define FILTER_COUNT_MESSAGE 1
#define FILTER_LAST_MESSAGE 2
#define FILTER_ALL_MESSAGE 3

typedef struct Client_t{
    long int id;
    int type_notification;
    int type_filter;
    //char* email;
    //char* number;
    SLIST_ENTRY(Client_t) next;
} Client; 
//void update(char *data);
#endif