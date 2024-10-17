#ifndef MESSAGE_H
#define MESSAGE_H
#define MAX_MESSAGE_LENGTH 2048
#include <sys/queue.h>
#include <postgresql/libpq-fe.h>


static int next_id = 0;
typedef struct Message_t{
    unsigned long long int id;
    char timesmessage[25];
    char content[MAX_MESSAGE_LENGTH];
    SLIST_ENTRY(Message_t) next;
} Message;
Message* createMessage(char content[]);
int storeMessage(Message* message);
PGresult* readMessage(long long int id);
int deleteMessage(long long int id);
#endif
