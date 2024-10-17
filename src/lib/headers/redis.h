#ifndef REDIS_H
#define REDIS_H
#include <sys/queue.h>
#include <hiredis/hiredis.h>
#include <stdlib.h>
#include "message.h"
#define IP_ADDRESS "127.0.0.1"
#define PORT 6379

redisContext* connexionToRedis();
int insertMessageInRedis(Message *message);
char* getMessagesFromRedis(long long int key);
int deleteMessageFromRedis(long long int key);
#endif