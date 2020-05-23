#include "dgramlib.h"

int make_dgram_server_socket(char *addr, int port) {
    struct sockaddr_in server_addr;
    int sock_id;

    if((sock_id = socket(PF_INET, SOCK_DGRAM, 0)) == -1)
        oops("socket error");

    bzero(&server_addr, sizeof(server_addr));
    
    server_addr.sin_addr.s_addr = inet_addr(addr);
    server_addr.sin_port = htons(port);
    server_addr.sin_family = AF_INET;

    if(bind(sock_id, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
        oops("bind error");

    return sock_id;
    
}

int make_dgram_client_socket(char *addr, int port, struct sockaddr_in *saddr) {
    int sock;

    if((sock = socket(PF_INET, SOCK_DGRAM, 0)) == -1)
        oops("socket error");

    bzero(saddr, sizeof(saddr));

    saddr->sin_addr.s_addr = inet_addr(addr);
    saddr->sin_port = htons(port);
    saddr->sin_family = AF_INET;

    return sock;
}
