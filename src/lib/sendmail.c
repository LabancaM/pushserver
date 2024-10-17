#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *mailpipe = popen("/usr/sbin/sendmail -t", "w");
    if (mailpipe == NULL) {
        printf("Erreur lors de l'ouverture de sendmail.\n");
        exit(1);
    }

    fprintf(mailpipe, "To: amarcayi@gmail.com\n");
    fprintf(mailpipe, "From: amarcayi@gmail.com\n");
    fprintf(mailpipe, "Subject: Sujet de l'email\n");
    fprintf(mailpipe, "\n");
    fprintf(mailpipe, "Corps de l'email c\n");

    pclose(mailpipe);
    return 0;
}