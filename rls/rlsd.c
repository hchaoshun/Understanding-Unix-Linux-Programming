#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define PORTNUM 15000
#define oops(s) {perror(s);exit(1);}

int main(int argc, int *argv[]) {
    struct sockaddr_in saddr;
    int sock_id;
    int sock_fd;
    FILE *fpin, *fpout;
    FILE *fp;
    char command[BUFSIZ];
    char buf[BUFSIZ];
    char c;

    char *myaddr = "115.28.53.241";

    /* socket */
    sock_id = socket(PF_INET, SOCK_STREAM, 0);
    if(sock_id == -1)
        oops("socket error");

    /* bind */
    bzero((void *)&saddr, sizeof(saddr));

    saddr.sin_addr.s_addr = inet_addr(myaddr);
    saddr.sin_port = htons(PORTNUM);
    saddr.sin_family = AF_INET;

    if(bind(sock_id,(struct sockaddr *) &saddr, sizeof(saddr)) == -1)
        oops("bind error");
    
    /* listen */
    if(listen(sock_id, 1) == -1)
        oops("listen error");
    
    /* main loop */
    while(1) {
        sock_fd = accept(sock_id, NULL, NULL);
        if(sock_fd == -1)
            oops("accept error");
        
        if((fpin = fdopen(sock_fd, "r")) == NULL)
            oops("error");

        if((fpout = fdopen(sock_fd, "w")) == NULL)
            oops("error");

        if((fgets(buf, BUFSIZ, fpin)) == NULL)
            oops("error");

        sprintf(command, "ls %s", buf);

        if((fp = popen("command", "r")) == NULL)
            oops("error");
        
        while(c = fgetc(fp) != EOF)
            fputc(c, fpout);
                

        fclose(fpin);
        fclose(fpout);
        pclose(fp);
    }
    





}
