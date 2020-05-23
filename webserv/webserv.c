#include <sys/stat.h>
#include <signal.h>
#include <errno.h>

#include "socklib.h"
#include "varlib.h"

#define PORTNUM 12345

void setupvars();
void child_wait(int);
void process_request(char *, int, struct sockaddr_in *);

/* main */
int main() {
    int sock_id;
    int sock_fd;
    FILE *fpin;
    char request[BUFSIZ];

    int len;
    struct sockaddr_in clnt_addr;

    signal(SIGCHLD, child_wait);

    if((sock_id = make_server_socket(PORTNUM)) == -1)
        oops("error");

    setupvars();

    while(1) {

        len = sizeof(struct sockaddr);
        if((sock_fd = accept(sock_id, (struct sockaddr *)&clnt_addr, &len)) == -1)
            oops("accept error");
        
        if(sock_id == -1)
            if(errno == EINTR)
                continue;
            else
                break;

        fpin = fdopen(sock_fd, "r");

        fgets(request, BUFSIZ, fpin);
        
        printf("got a call: request %s", request);
    //    read_unntil_crnl(request);

        process_request(request, sock_fd, &clnt_addr);

        close(sock_fd);
        fclose(fpin);
    }
}

void setupvars() {
    VLstore("SERVER_SOFTWARE", "Simple-Webserv 0.2");
    VLexport("SERVER_SOFTWARE");
    VLstore("SERVER_NAME", "123.206.93.100");
    VLexport("SERVER_NAME");
}

void child_wait(int signum) {
    while(waitpid(-1, NULL, WNOHANG) > 0);
}

void header(FILE *, char *);
void cannot_do(int);

int not_exit( char *);
void do_404(char *, int);

int lsadir(char *);
void do_ls(char *, int);

int ends_in_cgi(char *);
void do_exec(char *, int);

void do_cat(char *, int );

/* process_request */
void process_request(char *req, int fd, struct sockaddr_in *caller) {
    char cmd[BUFSIZ], arg[BUFSIZ];
    char portnumstr[BUFSIZ];

    if(fork() != 0)
        return;
    
    VLstore("REMOTE_ADDR", inet_ntoa(caller->sin_addr));
    VLexport("REMOTE_ADDR");
    sprintf(portnumstr, "%d", ntohs(caller->sin_port));
    VLstore("REMOTE_PORT", portnumstr);
    VLexport("REMOTE_PORT");

//    strcpy(arg, "./");
    sscanf(req, "%s%s", cmd, arg);

    VLstore("REQUEST_METHOD", cmd);
    VLexport("REQUEST_METHOD");
    VLstore("REQUEST_URI", arg);
    VLexport("REQUEST_URI");

    if(strcmp(cmd, "GET") != 0)
        cannot_do(fd);
    else if(not_exit(arg))
        do_404(arg, fd);

    else if(lsadir(arg))
        do_ls(arg, fd);

    else if(ends_in_cgi(arg))
        do_exec(arg, fd);

    else 
        do_cat(arg, fd);
}

void header(FILE *fp, char *content_type) {
    fprintf(fp, "HTTP/1.0 200 OK \n");
    if(content_type)
        fprintf(fp, "Content-type: %s\n", content_type);
}
/* operate error */
void cannot_do(int fd) {
    FILE *fout;

    if((fout = fdopen(fd, "w")) == NULL)
        oops("open error");

    fprintf(fout, "HTTP/1.0 501 NOT Implemented\n");
    fprintf(fout, "Content-type: text/plian\n");

    fclose(fout);
}

/* 404 error */
int not_exit(char *arg) {
    struct stat info;
    return (stat(arg, &info) != 0);
}

void do_404(char *arg, int fd) {
    FILE *fpout;

    if((fpout = fdopen(fd, "w")) == NULL)
        oops("error");

    fprintf(fpout, "HTTP/1.0 404 Not Found\n");
    fprintf(fpout, "The item you request: %s\nis not found\n", arg);

    fclose(fpout);
}

/* ls operation */
int lsadir(char *f) {
    struct stat info;

    return (stat(f, &info) != -1 && S_ISDIR(info.st_mode));
}

void do_ls(char *arg, int fd) {
    FILE *fp;
    fp = fdopen(fd, "w");

    header(fp, "text/plain");
    fprintf(fp, "\n");
    fflush(fp);

    dup2(fd, 1);
    dup2(fd, 2);
    close(fd);

    execl("/bin/ls", "ls", arg, NULL);
    oops(" exec error");
}

/* exec a dir */
char *file_type(char *f) {
    char *cp;

    if((cp = strrchr(f, '.')) != NULL)
        return cp + 1;
    else
        return " ";
}

int ends_in_cgi(char *arg) {
    return (strcmp(file_type(arg), "cgi") == 0);   
}

void do_exec(char *arg, int fd) {
    FILE *fp;
    if((fp = fdopen(fd, "w")) == NULL)
        oops("fdopen error");

    header(fp, NULL);
    fflush(fp);

    dup2(fd, 1);
    dup2(fd, 2);
    close(fd);
    
    execlp(arg, arg, NULL);
    perror(arg);
}

/* cat file */
void do_cat(char *f, int fd) {
    char *extension = file_type(f);
    char *content = "text/plain";
    if(strcmp(extension, "html") == 0)
        content = "text/html";
    else if(strcmp(extension, "gif") == 0)
        content = "image/gif";

    FILE *fpout, *fpin;
    int c;

    if((fpout = fdopen(fd, "w")) == NULL)
        oops("error");
    if((fpin = fopen(f, "r")) == NULL)
        oops("fopen error");

    header(fpout, content);

    while((c = fgetc(fpin)) != EOF)
        fputc(c, fpout);

    fclose(fpout);
    fclose(fpin);
}










