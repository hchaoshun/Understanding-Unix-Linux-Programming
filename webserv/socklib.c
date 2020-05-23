#include "socklib.h"

int make_server_socket(int portnum) {
    return make_server_socket_q(portnum, BACKLOG);
}

int make_server_socket_q(int portnum, int backlog) {
    
    struct sockaddr_in saddr;
    int sock_id_serv;
    char *myaddr = "123.206.93.100";

    /* socket */
    if((sock_id_serv = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        oops("socket error");

    /* bind*/

    bzero(&saddr, sizeof(saddr));

    saddr.sin_addr.s_addr = inet_addr(myaddr);
    saddr.sin_port = htons(portnum);
    saddr.sin_family = AF_INET;

    if(bind(sock_id_serv, (struct sockaddr *)&saddr, sizeof(saddr)) == -1)
        oops("bind error");

    /* listen */
    if(listen(sock_id_serv, backlog) == -1)
        oops("listen error");

    return sock_id_serv;
    
}

int connect_to_server(char *hostname, int portnum) {
    
    struct sockaddr_in caddr;
    int sock_id_cli;
    
    /* socket */
    if((sock_id_cli = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        oops("socket error");

    /* connect */
    bzero(&caddr, sizeof(caddr));
    
    caddr.sin_addr.s_addr = inet_addr(hostname);
    caddr.sin_port = htons(portnum);
    caddr.sin_family = AF_INET;

    if((connect(sock_id_cli, (struct sockaddr *)&caddr, sizeof(caddr))) == -1)
        oops("connect error");
    
    return sock_id_cli;

}
