#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

#define BACKLOG 1
#define oops(s) {perror(s); return -1;}

int make_server_socket_q(int, int);
int make_server_socket(int );
int connect_to_server(char *, int );
