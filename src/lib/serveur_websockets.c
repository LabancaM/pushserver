#include <libwebsockets.h>
#include <string.h>
#include <stdio.h>
#include <sys/queue.h>
#include <postgresql/libpq-fe.h>
#include "headers/message.h"
#include "headers/topic.h"
#include "headers/client.h"
#include "headers/filter.h"

//Fonction pour envoyer un message WebSocket à un client distant
void send_websocket_message(struct lws *wsi, const char *message) {
    if (lws_write(wsi, (unsigned char *)message, strlen(message), LWS_WRITE_TEXT) < 0) {
        fprintf(stderr, "Erreur lors de l'envoi du message WebSocket\n");
    }
}
// Callback de gestion des événements HTTP
static int callback_http(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len) {
    switch (reason) {
        case LWS_CALLBACK_HTTP:
            {
                char *uri = (char *)in;
                if (strstr(uri, "/notifications/topics/{id}/consumers/{id}") != NULL) {
                    // Logique d'abonnement au topic
                    // Extraire les informations du client de la requête HTTP
                    // Ajouter le client à la liste des abonnés au topic
                    subscribe(topic_name, client)
                } else if (strstr(uri,"/unsubscribe") != NULL) {
                    // Logique de désabonnement au topic
                    // Extraire les informations du client de la requête HTTP
                    // Retirer le client de la liste des abonnés au topic
                    // Répondre avec un message approprié
                }

                break;
            }
        default:
            break;
    }

    return 0;
}
// Callback de gestion des événements WebSocket
static int callback_websocket(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len) {
    switch (reason) {
        case LWS_CALLBACK_ESTABLISHED:
            printf("Connexion établie avec un client distant\n");

            // Exemple de notification WebSocket à un client distant
            struct Client client;
            // Remplir les détails du client
            strcpy(client.nom, "Client1");
            client.id = 1;
            strcpy(client.type_connexion, "WebSocket");

            char message[100];
            sprintf(message, "Bonjour %s, votre id est %d, vous utilisez la connexion de type %s", client.nom, client.id, client.type_connexion);

            // Envoi du message au client connecté
            send_websocket_message(wsi, message);
            break;

        case LWS_CALLBACK_RECEIVE:
            // Traiter les messages reçus des clients distants
            break;

        default:
            break;
    }

    return 0;
}

int main() {
    struct lws_context_creation_info info;
    struct lws_protocols protocols[] = {
        {
            "http",
            callback_http,
            0,
            0
        },
        {
            "websocket-protocol",
            callback_websocket,
            0,
            0
        },
        {NULL, NULL, 0, 0}
    };

    memset(&info, 0, sizeof(info));
    info.port = 8000; // Port sur lequel le serveur WebSocket écoutera
    info.protocols = protocols;

    // Initialisation du contexte WebSocket
    struct lws_context *context = lws_create_context(&info, NULL);
    if (!context) {
        fprintf(stderr, "Erreur lors de la création du contexte WebSocket\n");
        return 1;
    }

    printf("Serveur WebSocket en cours d'exécution...\n");

    // Boucle principale du serveur WebSocket
    while (1) {
        lws_service(context, 50); // Traitement des événements pendant 50 ms
    }

    lws_context_destroy(context);

    return 0;
}


if (strstr(uri, "/subscribe") != NULL) {
                    // Logique d'abonnement au topic
                    char client_name[50];
                    int client_id;
                    char client_connexion_type[20];

                    // Extraire les informations du client de la requête HTTP
                    lws_hdr_copy(wsi, client_name, sizeof(client_name), WSI_TOKEN_HTTP_URI_ARGS, "name");
                    lws_hdr_copy(wsi, &client_id, sizeof(client_id), WSI_TOKEN_HTTP_URI_ARGS, "id");
                    lws_hdr_copy(wsi, client_connexion_type, sizeof(client_connexion_type), WSI_TOKEN_HTTP_URI_ARGS, "connexion_type");

                    // Ajouter le client à la liste des abonnés au topic
                    struct Client new_client;
                    strcpy(new_client.nom, client_name);
                    new_client.id = client_id;
                    strcpy(new_client.type_connexion, client_connexion_type);
                    
                    // Ajouter le nouveau client à la liste des clients abonnés (vous devrez gérer la logique pour ajouter à la liste correctement)
                    // clients[num_clients] = new_client; // Ajouter le client à la liste

                    // Répondre avec un message approprié
                    const char *response = "Client abonné au topic avec succès!";
                    lws_return_http_status(wsi, HTTP_STATUS_OK, (unsigned char *)response, strlen(response));

// Extraire les informations du client de la requête HTTP
Client* getClientInformation(){
    Client client;
    struct lws *wsi;
    lws_hdr_copy(wsi, client.id, sizeof(client_name), WSI_TOKEN_HTTP_URI_ARGS, "id");
    lws_hdr_copy(wsi, client.type_filter, sizeof(client_id), WSI_TOKEN_HTTP_URI_ARGS, "type_filter");
    lws_hdr_copy(wsi, client.type_notification, sizeof(client_connexion_type), WSI_TOKEN_HTTP_URI_ARGS, "connexion_type");

}

static int callback_http(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len) {
    switch (reason) {
        case LWS_CALLBACK_HTTP: {
            // Traiter les requêtes HTTP
            if (lws_hdr_total_length(wsi, WSI_TOKEN_GET_URI) == 0) {
                // Gérer une requête POST pour créer un sujet, supprimer un sujet, envoyer un message, etc.
                // Implémenter la logique correspondante ici
            }

            // Envoyer une réponse HTTP appropriée
            lws_return_http_status(wsi, HTTP_STATUS_OK, NULL);
            break;
        }
        // Autres cas à gérer selon vos besoins
    }

    return 0;
}