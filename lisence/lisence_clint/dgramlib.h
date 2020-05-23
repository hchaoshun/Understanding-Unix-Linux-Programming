#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define oops(s) {perror(s); exit(1);}

int make_dgram_server_socket(char *, int );
int make_dgram_client_socket(char *, int , struct sockaddr_in *); 
