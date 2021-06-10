#define _SVID_SOURCE
#include<sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include<sys/ipc.h>
#include <sys/wait.h>
#include<sys/sem.h>
#include <unistd.h>
//#include "funkcje.c"	//program służy do wykonywania sekcji krytycznej
 
#include "funkcje.h"
 
int main()
{
	key_t key;
	key=uzyskaj_dostep();	
	int number=tworzenie(key);		//pobieram klucz
 
 
	opusc(number);
	fprintf(stdout,"Sekcja krytyczna!\n");
	while(1)
	{
        	printf("proces: PID= %d rozpoczal sekcje krytyczna \n",getpid());
		sleep(4);
		break;
        }
	printf("Sekcja krytyczna zakonczona\n");
	int ileProcesow;
	ileProcesow=kolejka(number);
	printf("W kolejce do semafora czeka %d procesow!\n",ileProcesow);
	podnies(number);
 
	return 0;
 
 
 
}
