#include <libwebsockets.h>
#include <string.h>

static int callback_http(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len) {
    switch (reason) {
        case LWS_CALLBACK_HTTP:
            {
                const char *response = "HTTP/1.1 200 OK\nContent-Length: 7\n\nSuccess";
                lws_write(wsi, (unsigned char *)response, strlen(response), LWS_WRITE_HTTP);
                return 0;
            }
        default:
            break;
    }

    return lws_callback_http_dummy(wsi, reason, user, in, len);
}

static struct lws_protocols protocols[] = {
    {
        "http-only",
        callback_http,
        0,
    },
    { NULL, NULL, 0, 0 }
};

int main() {
    struct lws_context_creation_info info;
    struct lws_context *context;
    const char *interface = NULL;
    int port = 8000;

    memset(&info, 0, sizeof info);
    info.port = port;
    info.iface = interface;
    info.protocols = protocols;

    context = lws_create_context(&info);
    if (!context) {
        fprintf(stderr, "Erreur lors de la création du contexte libwebsocket\n");
        return 1;
    }

    while (1) {
        lws_service(context, 50);
    }

    lws_context_destroy(context);

    return 0;
}

                