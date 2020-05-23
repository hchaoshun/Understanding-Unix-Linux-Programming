#include "dgramlib.h"
#include "lserv_func.h"

int main(int argc, char *argv[]) {
    
    void ticket_reclaim();

    unsigned time_left;
    setup(argv[1], argv[2]);
    signal(SIGALRM, ticket_reclaim);
    alarm(RECLAIM_INTERVAL);

    while(1) {
        saddrlen = sizeof(saddr);
        time_left = alarm(0);
        handle_request();
        alarm(time_left);
    }
}
