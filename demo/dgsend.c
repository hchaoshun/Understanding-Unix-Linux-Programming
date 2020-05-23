#include "dgramlib.h"

int main(int argc, char *argv[]) {
    struct sockaddr_in saddr;
    int sock_id;

    if(argc != 4)
        fprintf(stderr, "error\n");

    if((sock_id = make_dgram_client_socket(argv[1], atoi(argv[2]), &saddr)) == -1)
        oops("error");

    if(sendto(sock_id, argv[3], sizeof(argv[3]), 0, (struct sockaddr *)&saddr, sizeof(saddr)) == -1)
        oops("send failed");

    return 0;

}
