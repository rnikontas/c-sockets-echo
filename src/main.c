#include <stdio.h>
#include "socks.h"
#include <string.h>

int main(int argc, char *argv[])
{
    int arg_port; // Only used if cmd arguments are supplied
    int type = -1;
    unsigned int port = 0;
    unsigned long length;
    switch(argc)
    {
        case 1:
            printf("Select executable type:\n");
            printf("0 | Client\n");
            printf("1 | Server\n");
            scanf("%d", &type);
            printf("Enter port:\n");
            scanf("%d", &port);
            switch (type)
            {
                case CLIENT:
                    printf("Create additional socket: 0 for client, 1 for server:\n");
                    int server = -1;
                    scanf("%d", &server);
                    if (server == 0) // Client
                    {
                        printf("Initializing CLIENT on port %d\n", port);
                        init_client(port, CLIENT, port + 1, "");
                    } else // Server
                    {
                        printf("Initializing CLIENT on port %d\n", port);
                        init_client(port, SERVER, port + 1, "");
                    }
                    break;
                case SERVER:
                    printf("Initializing SERVER on port %d\n", port);
                    init_server(port, YES, "");
                    break;
                default:
                    perror("Unknown command inputted. Exiting...\n");
                return 0;
            }
            break;
        case 3:
            if (strncmp(argv[1], "-s", strlen(argv[1])) != 0)
            {
                printf("%s argument unknown. Exiting...\n", argv[1]);
                break;
            }
            sscanf(argv[2], "%d", &arg_port);
            if ((arg_port < 0) || (arg_port > 65536))
            {
                perror("Incorrect port. Exiting...\n");
                break;
            }
            printf("Initializing SERVER on port %d\n", arg_port);
            init_server(arg_port, YES, "");
            break;
        case 4:
            if (strncmp(argv[1], "-c", strlen(argv[1])) != 0)
            {
                printf("Second argument can be -c only. Exiting...\n");
                break;
            }
            sscanf(argv[2], "%d", &arg_port);
            if ((arg_port < 0) || (arg_port > 65536))
            {
                perror("Incorrect port. Exiting...\n");
                break;
            }
            if (strncmp(argv[3], "-c", strlen(argv[3])) == 0)
            {
                printf("Initializing CLIENT on port %d\n", arg_port);
                init_client(arg_port, CLIENT, arg_port + 1, "");
            } else if (strncmp(argv[3], "-s", strlen(argv[3])) == 0)
            {
                printf("Initializing CLIENT on port %d\n", arg_port);
                init_client(arg_port, SERVER, arg_port + 1, "");
            } else
            {
                printf("%s argument unknown. Exiting....\n", argv[3]);
                break;
            }
            break;
    }
    return 0;
}
