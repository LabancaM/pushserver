#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/message.h"
#include "../headers/filter.h"
#include "../headers/topic.h"
#include "hiredis/hiredis.h"
#include "../Unity/src/unity.h"
 
void setUp() {
    SLIST_INIT(&list_topic);
}
void tearDown(){}

void test_countMessage_return_null_if_topic_is_null(){
    Topic* topic = createTopic(NULL);
    TEST_ASSERT_NULL(countMessage(topic));
}
void test_countMessage_return_string_0_message_if_list_of_message_is_empty(){
    Topic* topic = createTopic("info sur l'exercice");
    TEST_ASSERT_EQUAL_STRING("vous avez recu 0 message(s) sur le topic info sur l'exercice",
    countMessage(topic)[0]);
}
void test_countMessage_return_string_of_number_of_message_in_topic() {
    Topic* topic = createTopic("info sur l'exercice");
    Message* message = createMessage("la solution de l'exercice 2");
    Message* message2 = createMessage("la solution de l'exercice 3");
    Message* message3 = createMessage("la solution de l'exercice 4");
    Message* message4 = NULL;
    TEST_ASSERT_EQUAL_INT(1,pushMessages(topic, message));
    TEST_ASSERT_EQUAL_INT(1,pushMessages(topic, message2));
    TEST_ASSERT_EQUAL_INT(1,pushMessages(topic, message3));
    TEST_ASSERT_EQUAL_INT(0,pushMessages(topic, message4));
    TEST_ASSERT_EQUAL_STRING("vous avez recu 3 message(s) sur le topic info sur l'exercice", 
    countMessage(topic)[0]);
}
// test for last message

void test_lastMessage_return_null_if_topic_is_null(){
    Topic* topic = createTopic(NULL);
    TEST_ASSERT_NULL(lastMessage(topic));
}
void test_lastMessage_return_string_if_list_of_message_is_empty(){
    Topic* topic = createTopic("info sur l'exercice");
    TEST_ASSERT_EQUAL_STRING("Pas de message recu", lastMessage(topic)[0]);
}
void test_lastMessage_return_string_of_last_message_in_topic() {
    Topic* topic = createTopic("info sur l'exercice");
    Message* message = createMessage("la solution de l'exercice 2");
    Message* message2 = createMessage("la solution de l'exercice 3");
    Message* message3 = createMessage("la solution de l'exercice 4");
    Message* message4 = NULL;
    TEST_ASSERT_EQUAL_INT(1,pushMessages(topic, message));
    TEST_ASSERT_EQUAL_INT(1,pushMessages(topic, message2));
    TEST_ASSERT_EQUAL_INT(1,pushMessages(topic, message3));
    TEST_ASSERT_EQUAL_INT(0,pushMessages(topic, message4));
    //printf("%ld", strlen(lastMessage(topic)));
    TEST_ASSERT_EQUAL_INT(119, strlen(lastMessage(topic)[0]));
}

// test for all message
void test_allMessage_return_null_if_topic_is_null(){
    Topic* topic = NULL;
    TEST_ASSERT_NULL(allMessage(topic));
}
void test_allMessage_return_string_if_list_of_message_is_empty(){
    Topic* topic = createTopic("info sur l'exercice");
    TEST_ASSERT_EQUAL_STRING("Pas de message publié", allMessage(topic)[0]);
}
void test_allMessage_return_array_of_string_if_list_of_message_is_not_empty() {
    Topic* topic = createTopic("info sur l'exercice");
    Message* message = createMessage("la solution de l'exercice 2");
    Message* message2 = createMessage("la solution de l'exercice 3");
    Message* message3 = createMessage("la solution de l'exercice 4");
    TEST_ASSERT_EQUAL_INT(1,pushMessages(topic, message));
    TEST_ASSERT_EQUAL_INT(1,pushMessages(topic, message2));
    TEST_ASSERT_EQUAL_INT(1,pushMessages(topic, message3));
    TEST_ASSERT_EQUAL_INT(117, strlen(allMessage(topic)[2]));
}



int main(){
    UNITY_BEGIN();
    // Run the test for count message
    RUN_TEST(test_countMessage_return_null_if_topic_is_null);
    RUN_TEST(test_countMessage_return_string_0_message_if_list_of_message_is_empty);
    RUN_TEST(test_countMessage_return_string_of_number_of_message_in_topic);
    // Run the test for last message
    RUN_TEST(test_lastMessage_return_null_if_topic_is_null);
    RUN_TEST(test_lastMessage_return_string_if_list_of_message_is_empty);
    RUN_TEST(test_lastMessage_return_string_of_last_message_in_topic);
    // Run the test for all message
    RUN_TEST(test_allMessage_return_null_if_topic_is_null);
    RUN_TEST(test_allMessage_return_string_if_list_of_message_is_empty);
    RUN_TEST(test_allMessage_return_array_of_string_if_list_of_message_is_not_empty);
    
    return UNITY_END();
}
