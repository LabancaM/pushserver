#ifndef FILTER_H
#define FILTER_H
#include <sys/queue.h>
#include "topic.h"
#include "message.h"
#include "client.h"
#include "topic.h"

char** countMessage(Topic *topic);
char** lastMessage(Topic *topic);
char** allMessage(Topic *topic);
#endif

