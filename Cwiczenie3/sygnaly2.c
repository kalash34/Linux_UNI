


#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>




#define _XOPEN_SOURCE 500
pid_t pid;


void obsluga_sygnalu(int sig)
{
  printf("[%d]otrzymano sygnal: \n",getpid());
  pid = fork();

  if(pid  ==  0)
  {
    printf("[%d] Proces potomny \n",getpid());
    signal(SIGHUP,obsluga_sygnalu);

    execl("./sig2", "sig2", (char *)0);
  }
  else if(pid > 0)
  {
    printf("[%d] Proces macierzysty \n",getpid());
    sleep(60*10);
    exit(0);
  }
  else
  {
    printf("[%d]  Blad funkcji fork \n",getpid());
  }
}

int main ()
{
  signal(SIGHUP,obsluga_sygnalu); //SIGHUp - zakonczenie procesu sterujacego terminalem
  signal (SIGCHLD, SIG_IGN); // ingorujemy sygnal
  signal (SIGCHLD, SIG_DFL); // operacja domyslna
	

  while(1)
  {
    printf("[%d] oczekiwanie na SIGHUP \n",getpid());
    pause();
    // sekwencja ctrl + c - SIGINT
    //   ctrl + \ - SIGQUIT

  }




}



