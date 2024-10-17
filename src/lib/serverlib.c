#include <libwebsockets.h>
#include <string.h>

static int callback_http(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len) {
    switch (reason) {
        case LWS_CALLBACK_HTTP: {
            const char *uri = (const char *)in;

            if (lws_hdr_total_length(wsi, WSI_TOKEN_GET_URI) == 0) {
                // Gérer une requête POST pour créer un sujet, supprimer un sujet, envoyer un message, etc.
                if (strcmp(uri, "/create_topic") == 0) {
                    // Logique pour créer un nouveau sujet
                    create_topic("Nouveau sujet");
                    lws_return_http_status(wsi, HTTP_STATUS_OK, NULL);
                } else if (strcmp(uri, "/delete_topic") == 0) {
                    // Logique pour supprimer un sujet
                    // Supprimer le sujet ici
                    lws_return_http_status(wsi, HTTP_STATUS_OK, NULL);
                } else if (strcmp(uri, "/send_message") == 0) {
                    // Logique pour envoyer un message à un sujet
                    // Envoyer le message ici
                    lws_return_http_status(wsi, HTTP_STATUS_OK, NULL);
                } else {
                    lws_return_http_status(wsi, HTTP_STATUS_NOT_FOUND, NULL);
                }
            } else {
                lws_return_http_status(wsi, HTTP_STATUS_BAD_REQUEST, NULL);
            }

            break;
        }
        // Autres cas à gérer selon vos besoins
    }

    return 0;
}