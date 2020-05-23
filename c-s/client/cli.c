#include "socklib.h"

int talk_with_server(int );

int main(int argc, char *argv[]) {
    int sock_id;
    
    if((sock_id = connect_to_server(argv[1], atoi(argv[2]))) ==-1)
        oops("error");

    talk_with_server(sock_id);
    
    close(sock_id);
}

int talk_with_server(int sock_id) {
    char *buf[BUFSIZ];
    int len;

    if((len = read(sock_id, buf, BUFSIZ)) == -1)
        oops("read error");

    write(1, buf, len);
}
