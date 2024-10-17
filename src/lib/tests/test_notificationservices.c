#include <stdlib.h>
#include <string.h>
#include "../Unity/src/unity.h"
#include "../headers/topic.h"
#include "../headers/message.h"
#include "../headers/client.h"
#include "../headers/notificationservices.h"
#include "../headers/notification.h"
#include "../headers/client.h"
#include "../headers/filter.h"
#include <sys/queue.h>

void setUp() {
    SLIST_INIT(&list_topic);
}
void tearDown() {}

void test_typeFilter_return_array_of_string_if_succeed()
{
    Client client = {1, 2, 3};
    
    Topic* topic = createTopic("topic");
    subscribe(topic->name, &client);
    Message* Message1 = createMessage("sol1");
    Message* Message2 = createMessage("sol2");
    Message* Message3 = createMessage("sol3");
    pushMessages(topic, Message1);
    pushMessages(topic, Message2);
    pushMessages(topic, Message3);
    //char** messages = typeFilter(&client, topic);
    //int length = sizeof(messages) / sizeof(messages[0]);
    //printf("%s", typeFilter(&client, topic)[0]);
}
void test_sendNotification_return_0_if_topic_is_null()
{   
    TEST_ASSERT_EQUAL_INT(0, sendNotification(NULL));
    
}
void test_sendNotification_return_0_if_client_not_exist()
{   
    Topic* topic = createTopic("topic");
    TEST_ASSERT_EQUAL_INT(0, sendNotification(topic));
    
}
void test_sendNotification_return_1_if_notification_sent()
{
    Client client = {1, 2, 1};
    Client client1 = {2, 2, 2};
    Client client3 = {3, 2, 3};
    Topic* topic = createTopic("topic");
    subscribe(topic->name, &client);
    subscribe(topic->name, &client1);
    subscribe(topic->name, &client3);
    Message* Message1 = createMessage("sol1");
    Message* Message2 = createMessage("sol2");
    Message* Message3 = createMessage("sol3");
    pushMessages(topic, Message1);
    pushMessages(topic, Message2);
    pushMessages(topic, Message3);
    TEST_ASSERT_EQUAL_INT(1, sendNotification(topic));
}



int main(){
    UNITY_BEGIN();
    //RUN_TEST(test_typeFilter_return_array_of_string_if_succeed);
    // Run the test for the create topic
    RUN_TEST(test_sendNotification_return_0_if_topic_is_null);
    RUN_TEST(test_sendNotification_return_0_if_client_not_exist);
    RUN_TEST(test_sendNotification_return_1_if_notification_sent);
    
    return UNITY_END();
}