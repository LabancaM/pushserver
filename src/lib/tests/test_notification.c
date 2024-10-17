#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/message.h"
#include "hiredis/hiredis.h"
#include "/home/marc/soude/push/lib/Unity-master/src/unity.h"
#include "../headers/notification.h"

void setUp() {
}
void tearDown() {}

void emailNotification_return_0_if_message_or_email_is_null()
{
    char* message1 = NULL;
    char* message2 = "";
    char* email1 = "";
    char* email2 = NULL;
    TEST_ASSERT_EQUAL_INT(0, emailNotification(message1, email1));
    TEST_ASSERT_EQUAL_INT(0, emailNotification(message1, email2));
    TEST_ASSERT_EQUAL_INT(0, emailNotification(message2, email1));
    TEST_ASSERT_EQUAL_INT(0, emailNotification(message2, email2));
}

void emailNotification_return_1_if_email_succeed()
{
    char* message1 = "you are the best";
    char* email1 = "amarcayi@gmail.com";
    TEST_ASSERT_EQUAL_INT(1, emailNotification(message1, email1));
}
int main(){
    UNITY_BEGIN();
    // Run the test for sendemail
    RUN_TEST(emailNotification_return_0_if_message_or_email_is_null);
    RUN_TEST(emailNotification_return_1_if_email_succeed);
    //RUN_TEST(emailNotification_return_0_if_email_pipe_fail);
    
    return UNITY_END();
}

