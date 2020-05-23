#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORTNUM 54321
#define MYADDR "115.28.53.241"

#define oops(s) {perror(s); exit(1);}

int make_dgram_server_socket(int, char *);
int make_dgram_client_socket();
