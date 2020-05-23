#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORTNUM 15000
#define oops(s) {perror(s);exit(1);}

int main(int argc, char *argv[]) {
    struct sockaddr_in servaddr;
    int sock_id;
    int length;
    char buf[BUFSIZ];
    char *myaddr = "115.28.53.241";
    
    if(argc != 3)
        oops("error");

    /* socket */
    if((sock_id = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        oops("socket error");
    
    /* connect */
    bzero((void *)&servaddr, sizeof(servaddr));

    servaddr.sin_addr.s_addr = inet_addr(myaddr);
    servaddr.sin_port = htons(PORTNUM);
    servaddr.sin_family = AF_INET;
    
    if(connect(sock_id, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
        oops("connect error");

    /* write/read */
    if(write(sock_id, argv[2], BUFSIZ) == -1)
        oops("write error");
    
    if(write(sock_id, "\n", 1) == -1)
        oops("write error");

    while((length = read(sock_id, buf, BUFSIZ)) > 0)
        if(write(1 ,buf ,length) == -1)
            oops("write");
    
    close(sock_id);
        
}
