#include "dgramlib.h"
#include "lclint_func.h"


void setup(char *av1, char *av2) {
    pid = getpid();

    if((sock_id = make_dgram_client_socket(av1, atoi(av2), &saddr_send)) == -1)
        oops("make dgram client socket error");

    saddrlen = sizeof(saddr_send);
}

int get_ticket() {

    if(ticket_flag)
        return 1;

    sprintf(buf_send, "HELLO %d", pid);

    if(sendto(sock_id, buf_send, sizeof(buf_send), 0, (struct sockaddr *)&saddr_send, saddrlen) == -1)
        oops("send  HELLO error");

    if(recvfrom(sock_id, buf_recv, MSGLEN, 0, (struct sockaddr *)&saddr_recv, &saddrlen) == -1)
        oops("recv TICK error");

    if(strncmp(buf_recv, "TICK", 4) == 0) {
        ticket_flag = 1;
        do_tick(buf_recv + 5);
    }
    else if(strncmp(buf_recv, "FAIL", 4) == 0)
        do_fail(buf_recv);
    else
        printf("Unknown error\n");
    
    return ticket_flag;
}

void do_tick(char *recv) {
    printf("\ngot ticket, ticket_id: %s\n", recv);
}

void do_fail(char *recv) {
    printf("sorry, %s\n", recv);
}

void do_regular_work() {
    sleep(10);
    if(validate_ticket() != 0) {
        printf("Server errors. please try later.\n");
        return;
    }
    printf("working...\n");
    sleep(10);
    printf("done!\n");

}

int release_ticket() {

    if(!(ticket_flag))
        return 0;

    sprintf(buffer_send, "GBYE %s", buf_recv +5);

    if(sendto(sock_id, buffer_send, sizeof(buffer_send), 0, (struct sockaddr *)&saddr_send, sizeof(saddr_send)) == -1)
        oops("send GBYE error");

    if(recvfrom(sock_id, buffer_recv, MSGLEN, 0, (struct sockaddr *)&saddr_recv, &saddrlen) == -1)
        oops("recv THNX error");

    if(strncmp(buffer_recv, "THNX", 4) == 0) {
        ticket_flag = 0;
        do_thnx(buffer_recv);
    }

    else if(strncmp(buffer_recv, "FAIL", 4) == 0)
        do_failed(buffer_recv);

    else
        printf("Unknown error\n");

    return ticket_flag;
}

void do_thnx(char *recv) {
    printf("%s\n", recv);
}

void do_failed(char *recv) {
    printf("%s, your ticket is error\n", recv);
}

void shut_down() {
    if(close(sock_id) == -1)
        perror("shut down  error");
}

int validate_ticket() {
    if(!(ticket_flag))
        return 0;
    sprintf(buffer_send, "VAID %s", buf_recv + 5);
    
    if(sendto(sock_id, buffer_send, sizeof(buffer_send), 0, (struct sockaddr *)&saddr_send, sizeof(saddr_send)) == -1)
        oops("send VAID error");

    if(recvfrom(sock_id, buffer_recv, MSGLEN, 0, (struct sockaddr *)&saddr_recv, &saddrlen) == -1)
        oops("recv VAID error");

    if(strncmp(buffer_recv, "GOOD", 4) == 0)
        return 0;
    if(strncmp(buffer_recv, "FAIL", 4) == 0) 
        ticket_flag = 0;
    return -1;
}













