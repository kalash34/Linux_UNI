#define _SVID_SOURCE
#include<sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <unistd.h>
#include "funkcje.c"
 
 
int main()
{
 
	int liczba;
	printf("Podaj ilość procesów dla programu powielacza\n");
	scanf("%d",&liczba);	
	key_t key;
	key=uzyskaj_dostep();	
	int number=tworzenie(key);
	printf("semafor utworzony\n");		
	inicjalizacja(number);
	int i=0;
 
	while(i<liczba)
	{
		pid_t pid=fork();
		if( pid==-1)
		{	
 
				perror("błąd funkcji fork\n");
				exit(1);		
		}		
		if(pid== 0)	//proces potomny
		{
				printf("proces nr:%d",getpid());
				execl("./sekcja_krytyczna","sekcja_krytyczna.c",NULL);
				perror("execl error\n");	
		}			
		else
		{		sleep(4);	//proces macierzysty
 
		}		
		i++;

	} 
	int sprawdz_ilosc;
	sprawdz_ilosc=kolejka(number);
	if(sprawdz_ilosc<1)	
	{	usunSem(number);	//sprawdzamy ilosc procesow w kolejce

	}	

		fprintf(stdout,"Koniec\n");
	return 0;
	}


