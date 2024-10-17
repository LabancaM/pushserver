#include <stdlib.h>
#include <string.h>
#include "../headers/notification.h"
#include "../headers/notificationservices.h"
#include "../headers/filter.h"
#include "../Unity/src/unity.h"
#include "../headers/topic.h"
#include "../headers/message.h"
#include "../headers/client.h"
#include <sys/queue.h>

void setUp() {
    SLIST_INIT(&list_topic);
}
void tearDown() {}


void test_createTopic_return_null_where_name_is_null()
{   
    TEST_ASSERT_NULL(createTopic(NULL));
    
}

void test_createTopic_return_null_where_name_is_empty() 
{
    TEST_ASSERT_NULL(createTopic(""));
}

void test_createTopic_create_new_object()
{
    Topic* topic = createTopic("test");
    TEST_ASSERT_NOT_NULL(topic);
}
void test_createTopic_copy_name_in_new_structure()
{
    Topic* topic = createTopic("test");
    TEST_ASSERT_NOT_NULL(topic);
    TEST_ASSERT_EQUAL_STRING("test", topic->name);
}
void test_createTopic_trunc_name_if_name_length_is_higher()
{
    char name[MAX_TOPIC_NAME_LEN + 10];
    int i;
    for (i = 0; i < MAX_TOPIC_NAME_LEN + 10; i++)
        name[i] = 'a';
    name[MAX_TOPIC_NAME_LEN + 9] = '\0';
    Topic* topic = createTopic(name);
    TEST_ASSERT_EQUAL_INT(MAX_TOPIC_NAME_LEN-1, strlen(topic->name));
}
void test_createTopic_initialisation_of_list_messages(){
    Topic* topic = createTopic("test");
    TEST_ASSERT_EQUAL_INT(1, SLIST_EMPTY(&topic->list_message));
}
void test_createTopic_initialisation_of_list_clients(){
    Topic* topic = createTopic("test");
    TEST_ASSERT_EQUAL_INT(1, SLIST_EMPTY(&topic->list_client));
}

void test_createTopic_add_topic_to_list_of_topic(){
    Topic* topic = createTopic("test");
    TEST_ASSERT_NOT_NULL(topic);
    TEST_ASSERT_EQUAL_INT(0, SLIST_EMPTY(&list_topic));
    TEST_ASSERT_EQUAL_INT(1, numberOfTopic(list_topic));
}
void test_createTopic_return_null_if_name_exist()
{
    Topic* topic1 = createTopic("test");
    Topic* topic2 = createTopic("test");
    TEST_ASSERT_NOT_NULL(topic1);
    TEST_ASSERT_NULL(topic2);
}

// add message test
void test_addMessages_return_0_if_topic_or_message_is_null()
{
    Topic* topic = createTopic(NULL);
    Topic* topic2 = createTopic("");
    Message* message = createMessage(NULL);
    Message* message2 = createMessage("");
    Topic* topic3 = createTopic("NULL");
    Message* message3 = createMessage("NULL");
    TEST_ASSERT_EQUAL_INT(0, addMessages(topic, message));
    TEST_ASSERT_EQUAL_INT(0, addMessages(topic2, message));
    TEST_ASSERT_EQUAL_INT(0, addMessages(topic, message2));
    TEST_ASSERT_EQUAL_INT(0, addMessages(topic2, message2));
    TEST_ASSERT_EQUAL_INT(0, addMessages(topic2, message3));
}

void test_addMessages_insert_message_to_topic_list_message()
{
    Topic* topic = createTopic("NULL");
    Message* message = createMessage("NULL");
    Message* message2 = createMessage("NULL2");
    addMessages(topic, message);
    addMessages(topic, message2);
    TEST_ASSERT_NOT_NULL(topic);
    TEST_ASSERT_EQUAL_INT(0, SLIST_EMPTY(&topic->list_message));
    TEST_ASSERT_EQUAL_INT(2, numberOfTopicMessage(topic));
}
void test_addMessages_insert_message_to_databe()
{
    
}
void test_addMessages_send_notification()
{
    
}

// suscribe to topic
void test_subscribe_return_0_if_topic_name_or_client_is_null()
{
    char *topic_name1 = "";
    char *topic_name2 = NULL;
    char *topic_name3 = "troie";
    Client* client= NULL;
    Client client1 = {1, 2, 3};
    TEST_ASSERT_EQUAL_INT(0, subscribe(topic_name1, client));
    TEST_ASSERT_EQUAL_INT(0, subscribe(topic_name2, client));
    TEST_ASSERT_EQUAL_INT(0, subscribe(topic_name3, client));
    TEST_ASSERT_EQUAL_INT(0, subscribe(topic_name1, &client1));   
}
void test_subscribe_if_topic_name_not_exist()
{
    Topic* topic = createTopic("NULL");
    Client client = {1, 2, 3};
    TEST_ASSERT_EQUAL_INT(0, subscribe("topic", &client));
}

void test_subscribe_insert_client_to_topic_list_clients()
{
    Topic* topic = createTopic("Sam");
    TEST_ASSERT_EQUAL_INT(1, numberOfTopic(list_topic));
    Client client = {1, 2, 3};
    TEST_ASSERT_EQUAL_INT(0, numberOfTopicClient(topic));
    TEST_ASSERT_EQUAL_INT(1, subscribe(topic->name, &client));
    TEST_ASSERT_EQUAL_INT(0, SLIST_EMPTY(&topic->list_client));
    TEST_ASSERT_EQUAL_INT(1, numberOfTopicClient(topic));
}
void test_subscribe_several_time_same_client()
{
    Topic* topic = createTopic("NULL");
    Client client = {1, 2, 3};
    TEST_ASSERT_EQUAL_INT(1, subscribe(topic->name, &client));
    TEST_ASSERT_EQUAL_INT(0, subscribe(topic->name, &client));
}
// suscribe
void test_unsubscribe_return_0_if_topic_name_or_client_is_null()
{
    char *topic_name1 = "";
    char *topic_name2 = NULL;
    char *topic_name3 = "troie";
    Client* client= NULL;
    Client client1 = {1, 2, 3};
    TEST_ASSERT_EQUAL_INT(0, unsubscribe(topic_name1, client));
    TEST_ASSERT_EQUAL_INT(0, unsubscribe(topic_name2, client));
    TEST_ASSERT_EQUAL_INT(0, unsubscribe(topic_name3, client));
    TEST_ASSERT_EQUAL_INT(0, unsubscribe(topic_name1, &client1));
}

void test_unsubscribe_if_topic_name_not_exist()
{
    Topic* topic = createTopic("NULL");
    Client client = {1, 2, 3};
    TEST_ASSERT_EQUAL_INT(0, unsubscribe("topic", &client));
}
void test_unsubscribe_if_client_not_among_topic_client()
{
    Topic* topic = createTopic("NULL");
    Client client = {1, 2, 3};
    Client client1 = {2, 2, 3};
    TEST_ASSERT_EQUAL_INT(1, subscribe("NULL", &client));
    TEST_ASSERT_EQUAL_INT(1, unsubscribe("NULL", &client));
    TEST_ASSERT_EQUAL_INT(0, unsubscribe("NULL", &client1));
}

void test_unsubscribe_remove_client_to_topic_list_clients()
{
    Topic* topic = createTopic("NULL");
    Client client1 = {1, 2, 3};
    Client client2 = {2, 2, 3};
    Client client3 = {3, 2, 3};
    subscribe(topic->name, &client1);
    subscribe(topic->name, &client2);
    subscribe(topic->name, &client3);
    TEST_ASSERT_EQUAL_INT(3, numberOfTopicClient(topic));
    unsubscribe(topic->name, &client2);
    unsubscribe(topic->name, &client1);
    TEST_ASSERT_EQUAL_INT(0, SLIST_EMPTY(&topic->list_client));
    TEST_ASSERT_EQUAL_INT(1, numberOfTopicClient(topic));
    
}

// delete topic
void test_deleteTopic_return_0_if_name_is_null_or_empty()
{
    char* name1 = NULL;
    char* name2 = "";
    TEST_ASSERT_EQUAL_INT(0, deleteTopic(name1));
    TEST_ASSERT_EQUAL_INT(0, deleteTopic(name2));
}

void test_deleteTopic_remove_topic_in_list_topic()
{
    Topic* topic = createTopic("MANI");
    TEST_ASSERT_EQUAL_INT(1, deleteTopic(topic->name));
}
void test_deleteTopic_return_0_if_topic_not_exit()
{
    Topic* topic = createTopic("MANI");
    TEST_ASSERT_EQUAL_INT(0, deleteTopic("topic->name"));
}

int main(){
    UNITY_BEGIN();
    // Run the test for the create topic
    RUN_TEST(test_createTopic_return_null_where_name_is_null);
    RUN_TEST(test_createTopic_return_null_where_name_is_empty);
    RUN_TEST(test_createTopic_create_new_object);
    RUN_TEST(test_createTopic_copy_name_in_new_structure);
    RUN_TEST(test_createTopic_trunc_name_if_name_length_is_higher);
    RUN_TEST(test_createTopic_add_topic_to_list_of_topic);
    RUN_TEST(test_createTopic_return_null_if_name_exist);
    RUN_TEST(test_createTopic_initialisation_of_list_messages);
    RUN_TEST(test_createTopic_initialisation_of_list_clients);
    
    //Run the test for the add message
    //RUN_TEST(test_addMessages_return_0_if_topic_or_message_is_null);
    //RUN_TEST(test_addMessages_insert_message_to_topic_list_message);
    
    // Run test for subscribe
    RUN_TEST(test_subscribe_return_0_if_topic_name_or_client_is_null);
    RUN_TEST(test_subscribe_if_topic_name_not_exist);
    RUN_TEST(test_subscribe_insert_client_to_topic_list_clients);
    RUN_TEST(test_subscribe_several_time_same_client);
    
    //Run test for unsubscribe
    RUN_TEST(test_unsubscribe_return_0_if_topic_name_or_client_is_null);
    RUN_TEST(test_unsubscribe_if_topic_name_not_exist);
    RUN_TEST(test_unsubscribe_remove_client_to_topic_list_clients);
    RUN_TEST(test_unsubscribe_if_client_not_among_topic_client);
    
    //Run test for delete topic
    RUN_TEST(test_deleteTopic_return_0_if_name_is_null_or_empty);
    RUN_TEST(test_deleteTopic_remove_topic_in_list_topic);
    RUN_TEST(test_deleteTopic_return_0_if_topic_not_exit);
    return UNITY_END();
}