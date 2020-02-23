#ifndef CN_SOCKETS_SOCKS_H
#define CN_SOCKETS_SOCKS_H

#endif

#define SERVER 1
#define CLIENT 0
#define END 2
#define YES 1
#define NO 0
#define CHAIN_LENGTH 3 // Edit this to make the chain longer

void init_server(unsigned int port, int origin, char* msg);
void init_client(unsigned int port, int next_type, unsigned int next_port, char* data);