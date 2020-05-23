#include "socklib.h"

#define PORTNUM 12345
int process_request(int );

int main() {
    int sock_id;
    int sock_fd;

    if((sock_id = make_server_socket(PORTNUM)) == -1)
        oops("error");

    while(1) {
        if((sock_fd = accept(sock_id, NULL, NULL)) == -1)
            oops("accept error");
        
        process_request(sock_fd);
        close(sock_fd);
    }
}

//int process_request(int sock_fd) {
    
//    time_t now;
//    char *cp;
//    time(&now);
//    cp = ctime(&now);
//    write(sock_fd, cp, strlen(cp));
    
//}

int process_request(int sock_fd) {
    int pid;
    pid =fork();

    switch(pid) {
        case -1 : oops("error");
        case 0 : dup2(sock_fd, 1);
                 close(sock_fd);
                 execl("/bin/date", "date", NULL);
                 oops("end");
        default: wait(NULL);         
    }
}
