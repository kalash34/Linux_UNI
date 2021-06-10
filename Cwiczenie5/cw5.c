#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "producent.c"
#include "konsument.c"



void usuwanie_potoku()
{
    if(unlink("pipe") == -1) 	//wywolanie funkcji unlink usuwajacej dowiazanie do pliku z argumentu - czyli u nas "pipe"
    {
        perror("Blad funkcji unlink\n");                    
        _exit(EXIT_FAILURE);    //wywolanie systemowe _exit - natychmiastowe zakonczenie procesu,zamkniecie wszystkich deskryptorow nalezacych do procesu
    }				//adopcja wszystkich procesow potomnych przez proces init
    printf("Usunieto Potok.\n");
}
 



int main()
{
    mkfifo("pipe", 0644);
 if (fork() == 0)
    {
        printf("Tworzymy proces producenta %d\n", getpid());
        producent();
        printf("Producent, PID= %d zakonczyl prace\n", getpid());

    if(atexit(usuwanie_potoku) != 0)
    {
        perror("Blad funkcji atexit !!\n");                   
        exit(EXIT_FAILURE); //blad przerwania, wywolanie exit
    }

    }

    if (fork() == 0)
    {
        printf("Tworzymy proces konsumenta %d\n", getpid());
        konsument();
        printf("Konsument, PID= %d zakonczyl prace\n", getpid());
    if(atexit(usuwanie_potoku) != 0)
    {
        perror("Blad funkcji atexit !!\n");                    
        exit(EXIT_FAILURE);
    }
    }

    wait(NULL);
    printf("Procesy potomne dla PID= %d zakonczyly prace \n", getpid());
    exit(0);






}
