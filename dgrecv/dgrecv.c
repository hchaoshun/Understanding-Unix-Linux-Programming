#include "dgramlib.h"


void say_who_called(struct sockaddr_in *);
void reply_to_sender(int , char *, struct sockaddr_in *,socklen_t );

int main(int argc, char *argv[])  {
    int sock_id;
    char buf[BUFSIZ];
    struct sockaddr_in saddr;
    socklen_t sender_len;
    int length;

    if((sock_id = make_dgram_server_socket(atoi(argv[2]), argv[1])) == -1)
            oops("error");

    while((length = recvfrom(sock_id, buf, BUFSIZ, 0,(struct sockaddr *)&saddr, &sender_len)) > 0) {
        buf[length] = '\n';
        printf("got a message: %s\n", buf);
        
        say_who_called(&saddr);
        reply_to_sender(sock_id, buf, &saddr, sender_len);
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

void reply_to_sender(int sock, char *msg, struct sockaddr_in *saddr, socklen_t sender_len) {
    char reply[BUFSIZ];
    sprintf(reply, "Thank you for your %d size\n", strlen(msg));
    sendto(sock, reply, BUFSIZ, 0, (struct sockaddr *)&saddr, sender_len);
}



