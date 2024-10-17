#include <stdio.h>
#include <string.h>
#include <hiredis/hiredis.h>
#include "headers/redis.h"
#include "headers/message.h"
#define TIME_LIVE 124

redisContext* connexionToRedis(){
    redisContext *context = redisConnect(IP_ADDRESS, PORT);
    if (!context || context->err)
        return NULL;
    return context;
    //fprintf(stderr, "Error: %s\n", context->errstr);
}
int insertMessageInRedis(Message *message){
    redisContext *context = connexionToRedis();
    if (!message || !context)
        return 0;
    redisReply *reply = redisCommand(context, "HMSET %lld \
        content %s time %s",
     message->id, message->content, message->timesmessage);
    if (!reply || reply->type == REDIS_REPLY_ERROR) {
        freeReplyObject(reply);
        redisFree(context);
        return 0;
    }
    redisReply *reply = redisCommand(context, "EXPIRE %lld %d",
    message->id, TIME_LIVE);
    freeReplyObject(reply);
    redisFree(context); 
    return 1;
}
int insertTopicInRedis(char *topic_name){
    redisContext *context = connexionToRedis();
    if (!topic_name || !context)
        return 0;
    redisReply *reply = redisCommand(context, "HMSET %s\
    topicName %s", topic_name, topic_name);
    if (!reply || reply->type == REDIS_REPLY_ERROR) {
        freeReplyObject(reply);
        redisFree(context);
        return 0;
    }
    freeReplyObject(reply);
    redisFree(context); 
    return 1;
}

char* getMessagesFromRedis(long long int key){
    
    printf("ye1\n");
    redisContext *context = connexionToRedis();
    if (!context)
        return 0;
    int sum = 0;
    printf("yes1\n");
    char *message; 
   
    redisReply *reply = redisCommand(context, "HMGET %lld content time", key);
    if (!reply || reply->type == REDIS_REPLY_ERROR) {
        freeReplyObject(reply);
        redisFree(context);
        return 0;
    } 
    
    printf("yes %d\n", reply->type); 
    sum += strlen(reply->element[0]->str) + strlen(reply->element[1]->str);
    /*message = (char*)malloc(sizeof(char) * sum);
    strcat(message, reply->element[0]->str);
    strcat(message, reply->element[1]->str);
    // Process the reply here
    freeReplyObject(reply);
    redisFree(context); 
    return message;*/
    return "yes";
}
int deleteMessageFromRedis(long long int key){
    redisContext *context = connexionToRedis();
    if (!context)
        return 0;
    redisReply *reply = redisCommand(context, "DEL %lld", key);
    if (!reply || reply->type == REDIS_REPLY_ERROR || reply->type == REDIS_REPLY_NIL) {
        freeReplyObject(reply);
        redisFree(context);
        return 0;
    }
    freeReplyObject(reply);
    redisFree(context);
    return 1;
}
int main() {
    Message *message = createMessage("salut le monde");
    insertMessageInRedis(message);
    printf(" 11%s\n", getMessagesFromRedis(1));
    deleteMessageFromRedis(1);
    return 0;
}
