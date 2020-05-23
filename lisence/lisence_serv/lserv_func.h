#include "dgramlib.h"
#include <sys/types.h>
#include <signal.h>
#include <errno.h>

#define MSGLEN 128
#define RECLAIM_INTERVAL 60
#define MAX 3


static int sock_id;
static struct sockaddr_in saddr;
static socklen_t saddrlen;
static char buf_recv[BUFSIZ];
static char buf_send[BUFSIZ];
static char buffer_recv[BUFSIZ];
static char buffer_send[BUFSIZ];
static int ticket[MAX];


void init();
void setup(char *, char *);
void handle_request();
void do_hello(char *);
void do_goodbye(char *);
void do_validate(char *);
void ticket_reclaim();
