#include "dgramlib.h"

int make_dgram_server_socket(int port, char *myaddr) {
    struct sockaddr_in saddr;
    int sock_id;

    /* socket */
    if((sock_id = socket(PF_INET, SOCK_DGRAM, 0)) == -1)
            oops("socket error");

    /* bind */
    bzero(&saddr, sizeof(saddr)); 
    
    saddr.sin_addr.s_addr = inet_addr(myaddr);
    saddr.sin_port = htons(port); 
    saddr.sin_family = AF_INET; 
    
    if(bind(sock_id, (struct sockaddr *)&saddr, sizeof(saddr)) == -1)
        oops("bind error");

    return sock_id;
}

int make_dgram_client_socket(char *argv1, char *argv2, struct sockaddr_in *cliaddr) {
    int sock;
    
    if((sock = socket(PF_INET, SOCK_DGRAM, 0)) == -1)
        oops("socket error");
    
    bzero(cliaddr, sizeof(cliaddr));
    cliaddr->sin_addr.s_addr = inet_addr(argv1);
    cliaddr->sin_port = htons(atoi(argv2));
    cliaddr->sin_family = AF_INET;

    return sock;

}


