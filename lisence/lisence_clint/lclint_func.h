#include "dgramlib.h"

static int sock_id = -1;
static int pid = -1;
static struct sockaddr_in saddr_send;
static struct sockaddr_in saddr_recv;
static socklen_t saddrlen;
static int ticket_flag = 0;
static char buf_send[BUFSIZ];
static char buf_recv[BUFSIZ];
static char buffer_send[BUFSIZ];
static char buffer_recv[BUFSIZ];

#define MSGLEN 128

void do_tick(char *);
void do_fail(char *);
void do_thnx(char *);
void do_failed(char *);

void setup(char *, char *);
int get_ticket();
void do_regular_work();
int release_ticket();
int validate_ticket();
void shut_down();



