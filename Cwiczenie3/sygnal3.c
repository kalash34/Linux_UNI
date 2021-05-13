
#define _XOPEN_SOURCE 700
#include <assert.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>




volatile sig_atomic_t is_child = 0;


int main(int argc, char **argv) {

    pid_t pid, pgid;

    (void)argv;
   // signal(SIGINT, obsluga_sygnalu);
   // signal(SIGUSR1, obsluga_sygnalu);

    pid = fork();
    assert(pid != -1); //assert oczekuje prawdy w argumencie, inaczej zwraca i wyswietla blad

    if (pid == 0) {
        is_child = 1;
        if (argc > 1) {

            /* Zmien pgid
             * Nowe bedzie inne niz poprzednie, ktore bylo rowne rodzicowi
             * man stpgid mowi:
             * > Dziecko ma unikalne ID i to ID rozni sie od
             * > ID kazdej istniejacej grupy procesow (setpgid(2)) albo sesji.
             */

            setpgid(0, 0);
        }
        printf(" PROCES DZIECKO pid, pgid = %ju, %ju\n", (uintmax_t)getpid(), (uintmax_t)getpgid(0));
        assert(kill(getppid(), SIGUSR1) == 0);
        while (1);
        exit(EXIT_SUCCESS);
    }

    /* poczkekaj az dziecko wysle SIGUSR1. */

    pause();
    pgid = getpgid(0);

    printf("pid rodzica, pgid = %ju, %ju\n", (uintmax_t)getpid(), (uintmax_t)pgid);

    /* ujemny pierwszy argument oznacza wyslanie sygnalu do grupy procesow */

    kill(-pgid, SIGINT);
    while (1);
}
