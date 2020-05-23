#include "dgramlib.h"

void say_who_called(struct sockaddr_in *);

int main(int argc, char *argv[]) {
    struct sockaddr_in saddr;
    int sock_id;
    char buf[BUFSIZ];
    int msglen;
    socklen_t saddrlen;

    if((sock_id = make_dgram_server_socket(argv[1], atoi(argv[2]))) == -1)
        oops("make addr error");

    while((msglen = (recvfrom(sock_id, buf, BUFSIZ, 0, (struct sockaddr *)&saddr, &saddrlen))) >0)
    {
        buf[msglen] = '\0';
        printf("got a message: %s\n", buf);

        say_who_called(&saddr);
    }
    
    return 0;
}

void say_who_called(struct sockaddr_in *saddr) {
    char host[BUFSIZ];
    int port;

    strncpy(host, inet_ntoa(saddr->sin_addr), BUFSIZ);
    port = ntohs(saddr->sin_port);

    printf("from: %s:%d\n", host, port);
}
