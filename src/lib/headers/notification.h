#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#include <sys/queue.h>
#include "topic.h"
#include "message.h"
#include "client.h"
#include "topic.h"

#define SEND_EMAIL "amarcayi@gmail.com"
#define MAX_EMAIL_LENGTH 256

int emailNotification(char* message, char* email);
void pehoulNotification(char *message);
void smsNotification(char *message);
#endif