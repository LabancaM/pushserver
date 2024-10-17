#include <stdio.h>
#include <stdlib.h>
#include "headers/notification.h"



int emailNotification(char* message, char* email){
    if (!email || !*email) {
        printf("Error: email or message is null.\n");
        return 0;
    }
    if (!message || !*message) {
        printf("Error: email or message is null.\n");
        return 0;
    }
    FILE *mailpipe = popen("/usr/sbin/sendmail -t", "w");
    if (mailpipe == NULL) {
        printf("Erreur lors de l'ouverture de sendmail.\n");
        return 0;
    }
    fprintf(mailpipe, "To: %s\n", email);
    fprintf(mailpipe, "From: %s\n", SEND_EMAIL);
    fprintf(mailpipe, "Subject: Notification from push server\n");
    fprintf(mailpipe, "\n");
    fprintf(mailpipe, "%s\n", message);
    int status = pclose(mailpipe);
    if (status != 0) {
        printf("Error: sendmail exited with status %d.\n", status);
        return 0;
    }
    return 1;
}
void pehoulNotification(char *message)
{
    exit(0);
}
void smsNotification(char *message){
    exit(0);
}