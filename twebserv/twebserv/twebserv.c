#include "socklib.h"
#include <sys/stat.h>
#include <pthread.h>
#include <malloc.h>

#define PORTNUM 12345

void setup(pthread_attr_t *);
void *handle(void *fd);
void process_request(char *, int );

/* main */
int main() {
    int sock_id;
    int sock_fd;
    int *fdptr;

    pthread_t thread;
    pthread_attr_t attr;

    if((sock_id = make_server_socket(PORTNUM)) == -1)
        oops("error");

    setup(&attr);

    while(1) {
        if((sock_fd = accept(sock_id, NULL, NULL)) == -1)
            oops("accept error");
        fdptr = malloc(sizeof(int));
        *fdptr = sock_fd;

        pthread_create(&thread, &attr, handle, fdptr);

        close(sock_fd);
    }
}

void setup(pthread_attr_t *attrp) {
    pthread_attr_init(attrp);
    pthread_attr_setdetachstate(attrp, PTHREAD_CREATE_DETACHED);
}   

void *handle(void *fd) { 
    int sock_fd = *(int*) fd;
    free(fd);
    char request[BUFSIZ];
    FILE *fpin;

    fpin = fdopen(sock_fd, "r");
    fgets(request, BUFSIZ, fpin);
    printf("got a call: request %s", request);

    process_request(request, sock_fd);

    fclose(fpin);

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
void process_request(char *req, int fd) {
    char cmd[BUFSIZ], arg[BUFSIZ];

    sscanf(req, "%s%s", cmd, arg);

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










