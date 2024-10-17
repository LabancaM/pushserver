#include <stdlib.h>
#include <string.h>
#include <postgresql/libpq-fe.h>
#include "/home/marc/soude/push/lib/Unity-master/src/unity.h"
#include "../headers/message.h"
#include "../headers/posgres.h"


void setUp() {
    clearTable();
}
void tearDown() {}
// connetion do datase
void connectToDatabase_return_not_NULL_if_succed()
{   
    TEST_ASSERT_NOT_NULL(connectToDatabase());
    
}
//insert into database
void insertIntoDatabase_return_0_if_message_is_null()
{
    TEST_ASSERT_EQUAL_INT(0,insertIntoDatabase(NULL));
}
void insertIntoDatabase_return_0_if_connexion_to_db_fail()
{
    Message *message = createMessage("je vous aime1");
    TEST_ASSERT_NOT_NULL(message);
    TEST_ASSERT_EQUAL_INT(1,insertIntoDatabase(message));
}
void insertIntoDatabase_return_0_if_insertion_failed()
{
    Message *message = createMessage("je vous aime2");
    TEST_ASSERT_NOT_NULL(message);
    TEST_ASSERT_EQUAL_INT(1,insertIntoDatabase(message));
    TEST_ASSERT_EQUAL_INT(0,insertIntoDatabase(message));
}
void insertIntoDatabase_return_1_if_insertion_succeed()
{
    Message *message = createMessage("je vous aime3");
    TEST_ASSERT_NOT_NULL(message);
    TEST_ASSERT_EQUAL_INT(1,insertIntoDatabase(message));
}
// Récupération de données depuis la base de données
void retrieveFromDatabase_return_null_if_connexion_to_db_fail()
{
    Message *message = createMessage("je vous aime4");
    TEST_ASSERT_NOT_NULL(message);
    TEST_ASSERT_EQUAL_INT(1,insertIntoDatabase(message));
    TEST_ASSERT_NOT_NULL(retrieveFromDatabase(message->id));
}
void retrieveFromDatabase_return_null_if_id_not_exist()
{
    TEST_ASSERT_NULL(retrieveFromDatabase(1));
}
void retrieveFromDatabase_return_res_if_retrieve_is_succeed()
{
    Message *message = createMessage("je vous aime5");
    TEST_ASSERT_NOT_NULL(message);
    TEST_ASSERT_EQUAL_INT(1,insertIntoDatabase(message));
    TEST_ASSERT_NOT_NULL(retrieveFromDatabase(message->id));
}
//delete
void deleteFromDatabase_return_0_if_id_not_exist()
{
    TEST_ASSERT_EQUAL_INT(0,deleteFromDatabase(1));
}
void deleteFromDatabase_return_1_if_delete_succeed()
{
    Message *message = createMessage("je vous aime7");
    TEST_ASSERT_NOT_NULL(message);
    TEST_ASSERT_EQUAL_INT(1,insertIntoDatabase(message));
    TEST_ASSERT_EQUAL_INT(1, deleteFromDatabase(message->id));
}


int main(){
    UNITY_BEGIN();
    //connexion to database
    RUN_TEST(connectToDatabase_return_not_NULL_if_succed);
    //insertion in data base
    RUN_TEST(insertIntoDatabase_return_0_if_message_is_null);
    RUN_TEST(insertIntoDatabase_return_0_if_connexion_to_db_fail);
    RUN_TEST(insertIntoDatabase_return_0_if_insertion_failed);
    RUN_TEST(insertIntoDatabase_return_1_if_insertion_succeed);
    // Récupération de données depuis la base de données
    RUN_TEST(retrieveFromDatabase_return_null_if_connexion_to_db_fail);
    RUN_TEST(retrieveFromDatabase_return_null_if_id_not_exist);
    RUN_TEST(retrieveFromDatabase_return_res_if_retrieve_is_succeed);
    // Suppression dans la base de données
    RUN_TEST(deleteFromDatabase_return_0_if_id_not_exist);
    RUN_TEST(deleteFromDatabase_return_1_if_delete_succeed);
    return UNITY_END();
}