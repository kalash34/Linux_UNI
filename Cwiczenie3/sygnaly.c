
#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500
#include<stdio.h>
#include<signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

  
// Definiujemy handler dla SIGINT
// na klawiaturze ctrl-c


pid_t pid;
void handle_signal(int sig)
{
    printf("przechwycono sygnal uzytkownika! dla PID= %d\n", getpid());
	//wyswietlamy proces dla ktorego przechwycono sygnal!
	   // kill(pid, SIGUSR1);
}


void handler2(char sig)
{
switch(sig){
case 'a':  
	if (signal(SIGQUIT,SIG_DFL) == SIG_ERR){	//domyslna obsluga
	perror("Funkcja signal ma problem z SIGQUIT(SIG_DFL)");
	exit(EXIT_FAILURE);
	}
break;
case 'b': if (signal(SIGQUIT,SIG_IGN) == SIG_ERR){	//ignorowanie
	perror("Funkcja signal ma problem z SIGQUIT(SIG_IGN");
	exit(EXIT_FAILURE);
}
break;						//obsluga uzytkownika
case 'c': if (signal(SIGUSR1,handle_signal) == SIG_ERR){
	perror("Funkcja signal ma problem z SIGINT");
	exit(EXIT_FAILURE);
	}
break;
}
pause();
}



int main()
{
char sig='c';
//domyslnie program wywoluje dla polecenia kill -USR1 [pid_procesu] z innej konsoli!!



    printf("obsluga sygnalow\n");

    printf("PID procesu: %d\n", getpid());
//SIGQUIT - sekwencja wyjscia z klawiatury
//SIG_DFL - podstawowa obsluga sygnalu
//SIG_IGN - ignorujemy sygnal
  handler2(sig);

    return 0;
}
