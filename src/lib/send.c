#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

#define SERVER "smtp.gmail.com"
#define PORT 587

int main() {
    int sock;
    struct sockaddr_in server;
    char message[2000];

    // Create a socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    // Configure the server address
    server.sin_addr.s_addr = inet_addr(SERVER);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Connection failed");
        exit(1);
    }

    // Prepare the email message
    snprintf(message, sizeof(message), "EHLO example.com\r\nMAIL FROM:\
     <amarcayi@gmail.com>\r\nRCPT TO: <amarcayi@gmail.com>\
     \r\nDATA\r\nSubject: Test Email\r\n\r\nHello, this is a test email \
     from a C program.\r\n.\r\n");

    // Send the email
    if (send(sock, message, strlen(message), 0) < 0) {
        perror("Send failed");
        exit(1);
    }

    // Close the socket
    close(sock);

    return 0;
}