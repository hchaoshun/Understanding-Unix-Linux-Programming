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

int make_dgram_client_socket() {
    int sock;
    struct sockaddr_in cliaddr;
    
    if((sock = socket(PF_INET, SOCK_DGRAM, 0)) == -1)
        oops("socket error");
    

}


