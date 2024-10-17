#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/message.h"
#include "hiredis/hiredis.h"
#include "/home/marc/soude/push/lib/Unity-master/src/unity.h"

void setUp() {
    
}
void tearDown() {}

void test_createMessage_return_null_where_content_is_null_or_empty()
{   
    TEST_ASSERT_NULL(createMessage(NULL));
    TEST_ASSERT_NULL(createMessage(""));
    
}
void test_createMessage_create_new_object()
{
    Message* message = createMessage("nouvelle notification");
    TEST_ASSERT_NOT_NULL(message);
}
void test_createMessage_copy_content_in_new_structure()
{
    Message* message = createMessage("nouvelle notification");
    TEST_ASSERT_EQUAL_STRING("nouvelle notification", message->content);
}
void test_createMessage_trunc_name_if_content_length_is_higher()
{
    char content[MAX_MESSAGE_LENGTH + 10];
    int i;
    for (i = 0; i < MAX_MESSAGE_LENGTH + 10; i++)
        content[i] = 'a';
    content[MAX_MESSAGE_LENGTH + 9] = '\0';
    Message* message = createMessage(content);
    TEST_ASSERT_EQUAL_INT(MAX_MESSAGE_LENGTH-1, strlen(message->content));
}
void test_createMessage_put_timestamp_in_new_structure()
{
    Message* message = createMessage("nouvelle notification");
    TEST_ASSERT_EQUAL_INT(24, strlen(message->timesmessage));
}
void test_createMessage_id_auto_incrementation()
{
    Message* message = createMessage("nouvelle notification");
    TEST_ASSERT_EQUAL_INT(5, message->id);
    Message* message2 = createMessage("nouvelle notification2");
    TEST_ASSERT_EQUAL_INT(6, message2->id);
}

// Run the test for store message
void test_storeMessage_return_0_where_message_is_null()
{   
    TEST_ASSERT_EQUAL_INT(0,storeMessage(NULL));
}



int main(){
    UNITY_BEGIN();
    // Run the test for create message
    RUN_TEST(test_createMessage_return_null_where_content_is_null_or_empty);
    RUN_TEST(test_createMessage_create_new_object);
    RUN_TEST(test_createMessage_copy_content_in_new_structure);
    RUN_TEST(test_createMessage_trunc_name_if_content_length_is_higher);
    RUN_TEST(test_createMessage_put_timestamp_in_new_structure);
    RUN_TEST(test_createMessage_id_auto_incrementation);

    // Run the test for store message
    RUN_TEST(test_storeMessage_return_0_where_message_is_null);
    return UNITY_END();
}

