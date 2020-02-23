#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "socks.h"

void init_client(unsigned int port, int next_type, unsigned int next_port, char* data)
{
    int sock = 0;
    struct sockaddr_in server_address;
    char buffer[1024] = {0};

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        printf("Couldn't create socket.\n");
        exit(0);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(port);

    if (connect(sock, (struct sockaddr*)&server_address, sizeof(server_address)) < 0)
    {
        printf("Couldn't connect!\n");
        exit(0);
    }

    if (next_type != -1)
    {
        read(sock, buffer, 1024);
        printf("Received data from %s:%d:\n", inet_ntoa(server_address.sin_addr), server_address.sin_port);
        printf("%s\n", buffer);
    }
    else
    {
        strcat(data, "..finished!");
        printf("Sending message %s to %s:%d\n", data, inet_ntoa(server_address.sin_addr), port);
        send(sock, data, strlen(data), 0);
    }

    switch (next_type)
    {
        case CLIENT:
            printf("Initializing CLIENT on port %d\n", next_port);
            init_client(next_port, -1, -1, buffer);
            break;

        case SERVER:
            printf("Initializing SERVER on port %d\n", next_port);
            init_server(next_port, NO, buffer);
            break;

        case -1:
            break;
    }
}