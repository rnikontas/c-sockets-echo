#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "socks.h"

void init_server(unsigned int port, int origin, char* msg)
{
    struct sockaddr_in address;
    char buffer[1024] = {0};
    char* init_msg = "Hello!";
    int address_length = sizeof(address);
    int options = 1;
    int client;

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == 0)
    {
        perror("Couldn't create socket.\n");
        exit(0);
    }

    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &options, sizeof(options)))
    {
        perror("Couldn't set socket options.\n");
        exit(0);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(sock, (struct sockaddr*)&address, sizeof(address)) < 0)
    {
        perror("Couldn't bind socket.\n");
        exit(0);
    }

    if (listen(sock, 3) < 0)
    {
        perror("Failed to listen.\n");
        exit(0);
    }

    if ((client = accept(sock, (struct sockaddr*)&address, (socklen_t*)&address_length)) < 0)
    {
        perror("Couldn't contact client.\n");
        exit(0);
    }

    switch(origin)
    {
        case YES:
                printf("Sending message %s to %s:%d\n", init_msg, inet_ntoa(address.sin_addr), port);
                send(client, init_msg, strlen(init_msg), 0);
                printf("Initializing SERVER on port %d\n", port + (CHAIN_LENGTH - 1));
                init_server(port + (CHAIN_LENGTH - 1), END, "");
            break;

        case NO:
                strcat(msg, "..echo!..");
                printf("Sending message %s to %s:%d\n", msg, inet_ntoa(address.sin_addr), port);
                send(client, msg, strlen(msg), 0);
            break;

        case END:
            read(client, buffer, 1024);
            getpeername(client, (struct sockaddr*)&address, (socklen_t*)address_length);
            printf("Received data from %s:%d:\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
            printf("%s\n", buffer);
            break;
    }
}


