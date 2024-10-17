#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *sms_pipe;

    // Open a pipe to Gammu's SMSD-INJECT command
    sms_pipe = popen("gammu-smsd-inject TEXT +22870381826 -text 'Votre message ici'", "r");
    
    if (sms_pipe == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du pipe vers Gammu.");
        return 1;
    }

    pclose(sms_pipe);

    return 0;
}./