
/* 

   Plik serwera ktory uzywa System V kolejek komunikatow do przechwytywania wiadomosci klienta
   (client.c) Klient wysyla wiadomosc poczatkowa
   nazwa oczekiwanego pliku, oraz identyfikator wiadomosci danej kolejki 
   uzyty do wyslania zawartosci pliku spowrotem do dziecka. Serwer probuje
   otworzyc oczekiwany plik. Jezeli plik nie moze byc otwarty, to bledna odpowiedz
   
   Inczej zawartosc oczekiwanego pliku jest wysylana seria wiadomosci
   
   Program obsluguje wiele kolejek komunikatow. Serwer utrzymuje
   kolejke (ze znanym kluczem) zadedykowana do przychodzacych requestow klienta. Kazdy
   klient tworzy wlasna prywatna kolejke ktora jest uzywana do przekazywania
   wiadomosci z serwera spowrotem do klienta

   Program operuje jako konkurencyjny serwer, forkuje nowy proces potomny aby
   obsluzyc kazdego klienta request dopoki czeka na wiadomosc nastepnego klienta.
*/

#include "wiadomosc.h"
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <stddef.h>                     
#include <limits.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>


static void grimReaper(int sig) /* SIGCHLD obsluga */
{
    int savedErrno;

    savedErrno = errno;                 /* waitpid() moze zmienic 'errno' */
    while (waitpid(-1, NULL, WNOHANG) > 0)
        continue;
    errno = savedErrno;
}

static void serveRequest(const struct requestMsg *req) /* Wykonane w procesie potomnym: obsluz pojedynczy klient */
{
    int fd;
    ssize_t numRead;
    struct responseMsg resp;

    fd = open(req->pathname, O_RDONLY);
    if (fd == -1) {                     /* Blad odczytu: wyslij tekst bledu */
        resp.mtype = RESP_MT_FAILURE;
        snprintf(resp.data, sizeof(resp.data), "%s", "Nie mozna otworzyc");

	printf("wiadomosc= %s",resp.data);

        msgsnd(req->clientId, &resp, strlen(resp.data) + 1, 0);
        exit(EXIT_FAILURE);             /* wyjdz */
    }

    /* Przekaz zawartosc pliku we wiadomosciach typu RESP_MT_DATA. Nie mozemy
       okreslic read() albo msgsnd() bledy since bo nie mozemy okreslic klienta */

    resp.mtype = RESP_MT_DATA;
    while ((numRead = read(fd, resp.data, RESP_MSG_SIZE)) > 0)
        if (msgsnd(req->clientId, &resp, numRead, 0) == -1)
            break;

    /* Wyslij wiadomosc typu RESP_MT_END zeby zaznaczyc koniec pliku */

    resp.mtype = RESP_MT_END;
    msgsnd(req->clientId, &resp, 0, 0);         /* Zerowa dlugosc mtext */
}

int main(int argc, char *argv[])
{
    struct requestMsg req;
    pid_t pid;
    ssize_t msgLen;
    int serverId;
    struct sigaction sa;

    /* Stworz kolejke wiadomosci serwera */

    serverId = msgget(SERVER_KEY, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR | S_IWGRP);
    if (serverId == -1){
        perror("msgget");
	}
    /*  SIGCHLD przechwytywanie  */

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = grimReaper;

    if (sigaction(SIGCHLD, &sa, NULL) == -1)
        perror("sigaction");

    /* Czytaj requesty, obsluz kazda w procesie potomnym */

    for (;;) {

	//otrzymana wiadomosc
        msgLen = msgrcv(serverId, &req, REQ_MSG_SIZE, 0, 0);



        if (msgLen == -1) {
            if (errno == EINTR)         /* Czy zaklocone przez SIGHANDLER ?*/
                continue;               /* zrestartuj msgrcv() */
            perror("msgrcv");           /* Jakis inny blad */
            break;                      /* przerwij petle */
        }

        pid = fork();                   /* Stworz proces potomny */
        if (pid == -1) {
            perror("fork");


            break;
        }

        if (pid == 0) {                 /* dziecko przechwytuje request */
            serveRequest(&req);
            _exit(EXIT_SUCCESS);
        }

        /* Rodzic iteruje by otrzymac nastepny request klienta */
    }

    /* Jezeli msgrcv() albo fork() da blad, usun server MQ i wyjdz */

    if (msgctl(serverId, IPC_RMID, NULL) == -1)
        perror("msgctl");
    exit(EXIT_SUCCESS);
}
