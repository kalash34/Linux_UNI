
/* client.c

   Wyslij wiadomosc do serwera server.c odbierajac
   zawartosc pliku nazwanego w linii polecen, oraz otrzymaj

   zawartosc pliku przez pare wiadmosci wyslanych spowrotem przez serwer. Wyswietl
   calkowita liczbe bitow i wiadomosci otrzymane. Server i klient komunikuja sie przez
   kolejki System V
*/

#include "wiadomosc.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <stddef.h>                     
#include <limits.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

static int clientId;

static void usunKolejke(void)
{
    if (msgctl(clientId, IPC_RMID, NULL) == -1)
        perror("msgctl");
}

int main(int argc, char *argv[])
{
    struct requestMsg req;
    struct responseMsg resp;
    int serverId, numMsgs;
    ssize_t msgLen, totBytes;

    if (argc != 2 || strcmp(argv[1], "--help") == 0){
        perror("sciezka pliku\n");}

    if (strlen(argv[1]) > sizeof(req.pathname) - 1){
        perror("Sciezka za dluga \n");}
    
    /* Odbierz identyfikator kolejki serwera; stworz kolejke odpowiedzi*/

    serverId = msgget(SERVER_KEY, S_IWUSR);
    if (serverId == -1){
        perror("msgget - kolejka komunikatow serwera");}

    clientId = msgget(IPC_PRIVATE, S_IRUSR | S_IWUSR | S_IWGRP);
    if (clientId == -1){
        perror("msgget - kolejka komunikatow klienta");}

    if (atexit(usunKolejke) != 0){
        perror("atexit");
	}
    /* Wyslij wiadomosc pytajac o plik nazwany w argv[1] */

    req.mtype = 1;                      /* Kazdy typ */
    req.clientId = clientId;
    strncpy(req.pathname, argv[1], sizeof(req.pathname) - 1);
    req.pathname[sizeof(req.pathname) - 1] = '\0';

                                        /* string jest przetwarzany */

    if (msgsnd(serverId, &req, REQ_MSG_SIZE, 0) == -1){
        perror("msgsnd");
	}
    /* Wez pierwsza odpowiedz ktora moze byc notyfikacja bledu */

    msgLen = msgrcv(clientId, &resp, RESP_MSG_SIZE, 0, 0);
    if (msgLen == -1){
        perror("msgrcv");}

    if (resp.mtype == RESP_MT_FAILURE) {
        printf("%s\n", resp.data);      /* Wyswietl wiadomosc z servera */
        exit(EXIT_FAILURE);
    }

    /* Plik zostal otwarty z sukcesem; wiadomosc procesu
       (wlaczajac aktualnie odczytana) containing file data */

    totBytes = msgLen;                  /* Policz pierwsza wiadomosc */
    for (numMsgs = 1; resp.mtype == RESP_MT_DATA; numMsgs++) {
        msgLen = msgrcv(clientId, &resp, RESP_MSG_SIZE, 0, 0);
        if (msgLen == -1)
            perror("msgrcv");

        totBytes += msgLen;
    }

    printf("Otrzymano %zd bajtow (%d wiadomosci)\n", (long) totBytes, numMsgs);
   

    exit(EXIT_SUCCESS);
}
