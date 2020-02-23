# c-sockets-echo
Simple C sockets server/client implementation for Vilnius University Computer Networks class.  

You can pass arguments to create sockets instead of navigating the GUI:
Server: `./Program -s [PORT]`  
Client: `./Program -c [PORT] -X`, where X can be either c (client) or s (server).

By default the chain length is 3, requiring 3 instances and their roles are as follows:
1. [Origin] Server {1} & [End] Server {3}
2. Client {1} & Server {2}
3. Client {2} & Client {3}

The correct order for executing the above would be:
`./Program -s 6969`
`./Program -c 6969 -s`
`./Program -c 6970 -c`

Chain length can be modified by editing the CHAIN_LENGTH define in `socks.h`
