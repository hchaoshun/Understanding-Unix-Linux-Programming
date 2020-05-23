#include "dgramlib.h"
#include "lclint_func.h"


int main(int argc, char *argv[]) {
    
    setup(argv[1], argv[2]);

    if(get_ticket() == 0)
        exit(0);

    do_regular_work();

    release_ticket();

    shut_down();

    return 0;
}
