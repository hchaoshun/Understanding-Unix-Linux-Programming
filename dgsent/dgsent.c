#include "dgramlib.h"

int main(int argc, char *argv[]) {
    int sock_id;
    struct sockaddr_in cliaddr;
    char buf[BUFSIZ];
    size_t len;

    if((sock_id = make_dgram_client_socket(argv[1], argv[2], &cliaddr)) == -1)
        oops("sock error");

    if(sendto(sock_id, argv[3], strlen(argv[3]), 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr)) == -1)
        oops("sentto error");

//    if((len = recvfrom(sock_id, buf, BUFSIZ, 0, NULL, NULL)) > 0) {
//        buf[len] = '\0';
//        printf("%s\n", buf);
//    }
//    else
//        printf("no reply|\n");
//    return 0;
    

}
