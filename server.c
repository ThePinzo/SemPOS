#include "server.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <pthread.h>


int main(int argc, char *argv[]) {
    int socket_desc, socket_client, *newsockfd, port,
            c = sizeof(struct sockaddr_in);
    struct sockaddr_in server, client;

    if (argc < 2) {
        fprintf(stderr, "Error, no port provided\n");
        exit(1);
    }

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc < 0) {
        error("Error opening socket.");
    }

    port = atoi(argv[1]);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    if (bind(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0)
        error("Error on binding");

    listen(socket_desc, 5);
    socket_client = accept(socket_desc, (struct sockaddr *) &client, (socklen_t *) &c);

    while (socket_client) {

        pthread_t sniffer;
        newsockfd = malloc(1);
        *newsockfd = socket_client;
        pthread_create(&sniffer, NULL, , (void *) newsockfd);
        pthread_join(sniffer, NULL);

    }
    if (socket_client < 0) {
        error("Accept failed.");
    }

    return 0;
}