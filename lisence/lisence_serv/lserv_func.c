#include "dgramlib.h"
#include "lserv_func.h"

void setup(char *av1, char *av2) {
    if((sock_id = make_dgram_server_socket(av1, atoi(av2))) == -1)
        oops("make server socket error");
    
    saddrlen = sizeof(saddr);
    
    int i;
    for(i = 0 ; i < MAX ; i++)
        ticket[i] = 0;
}



void handle_request() {

    if(recvfrom(sock_id, buf_recv, MSGLEN, 0, (struct sockaddr *)&saddr, &saddrlen) == -1)
       oops("recv error");
    
    if(strncmp(buf_recv, "HELLO", 5) == 0) {
       printf("\nrecv a hello   from:%s\n", buf_recv + 6);
       do_hello(buf_recv + 6);
   }
    else if(strncmp(buf_recv, "GBYE", 4) == 0) {
       printf("\nrecv a goodbye   from:%s\n", buf_recv + 5);
       do_goodbye(buf_recv + 5);
   }
    else if(strncmp(buf_recv, "VAID", 4) == 0)
       do_validate(rep + 5);
    else
        perror("Unknown error");

/*     if(recvfrom(sock_id, buffer_recv, MSGLEN, 0, (struct sockaddr *)&saddr, &saddrlen) == -1) */
   /*      oops("recv error"); */
   /*  */
   /* if(strncmp(buffer_recv, "GBYE", 4) == 0) { */
   /*     printf("\nrecv a goodbye   from:%s\n", buffer_recv + 5); */
   /*     do_goodbye(buffer_recv + 5); */
   /* } */
   /*  */
   /*  else */
   /*      perror("Unknown error"); */
/*  */
}

void do_hello(char *recv) {
    int j;

    for(j = 0 ; ticket[j] != 0 && j < MAX ; j++)
        ;
    if(j != MAX) {
        printf("have ticket/%d   ready send ticket\n\n", j);
        sprintf(buf_send, "TICK %s/%d\n", recv, j);
        ticket[j] = atoi(recv);

    }

    else {
        printf("No ticket   ready send fail\n");
        sprintf(buf_send, "FAIL explanation\n");
    }

    if(sendto(sock_id, buf_send, strlen(buf_send), 0, (struct sockaddr *)&saddr, saddrlen) == -1)
        oops("send TICK or FAIL error");

}

void do_goodbye(char *recv) {
    int tic,id;
    sscanf(recv, "%d %d", &tic, &id);

    if(ticket[id] == tic) {
        printf("ticket valid: %d/%d   ready send thnx\n", tic, id);
        sprintf(buffer_send, "THNX greeting\n");
        ticket[id] = 0;
    }

    else {
        printf("ticket invalid: %d/%d\n", tic, id);
        sprintf(buffer_send, "FAIL explanation\n");
    }

    if(sendto(sock_id, buffer_send, strlen(buffer_send), 0, (struct sockaddr *)&saddr, saddrlen) == -1)
        oops("send  THNX or FAIL eror");

}

void do_validate(char *recv) {
    if(sscanf(recv, "%d/%d", &tic, &id) == 2 && ticket[id] == pid)
        sprintf(buffer_send, "GOOD Valid Ticket\n");
    else
        sprintf(buffer_send, "FILE invalid ticket\n");

    if(sendto(sock_id, buffer_send, strlen(buffer_send), 0, (struct sockaddr *)&saddr, saddrlen) == -1)
    oops("send error");
}


void ticket_reclaim() {
    int i;
    char tick[BUFSIZ];

    for(int i = 0; i < MAX; i++) {
        if((ticket[i] != 0) && (kill(ticket[i], 0) == -1) && (errno == ESRCH)) {
            sprintf(tick, "%s/%d", ticket[i], i);
            printf("ticket %s wrong\n", tick);
            ticket[i] = 0;
        }
    }

    alarm(RECLAIM_INTERVAL);
}







