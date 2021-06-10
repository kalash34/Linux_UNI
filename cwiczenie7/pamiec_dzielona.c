#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <stdlib.h>
#include "semafory.h"
#include "pamiec.h"
#include "unistd.h"
#include <sys/mman.h>

#define SIZE 41



typedef struct Bufor_Cykliczny 
{
    int size;
    char bufor[SIZE];

}   Bufor_Cykliczny;






int rozmiar_pliku(FILE *f)	//funkcja obslugujaca plik
{
	fseek(f,0,SEEK_END);
	int size = ftell(f);
	rewind(f);

	return size;
}

// funkcja symulujaca opoznienie czasu
void time_delay()
{
	int i,j;
	for(i=0; i<5000; i++){
	for(j=0; j<5000; j++);}
}


int main()
{



	// utworzenie/dostep do pamieci dzielonej (odczyt/zapis)
	key_t key = ftok("plik",'A');
	int shm_id = shmget(key,SIZE,IPC_CREAT|0666);

	// utworzenie semafora
	sem sem_id = sem_create("plik2",'B',1);
	set_val(sem_id,0,1);
	
	Bufor_Cykliczny wpd; 
	// otwarcie plikow do odczytu/zapisu
	FILE *wejscie = fopen("input.txt","r");
	FILE *wyjscie = fopen("output.txt","w");
	int i=0;//iterator po rozmiarze pliku
	int size = rozmiar_pliku(wejscie)+40;
       //shmat() dołącza segment pamięci dzielonej Systemu V identyfikowany przez shmid do przestrzeni adresowej procesu, który ją wywołał.
	char *control = (char*)(shmat(shm_id, NULL, 0));
	char *start = control;

	//procesy producenta i konsumenta obsluzone sa w funkcji switch dla argumentu fork()


	switch(fork())
	{
	case -1: perror("Blad funkcji fork \n");
		exit(1);
	case 0:
		 while(i<size)
		{
			fgets(wpd.bufor,40,wejscie);
			get_down(sem_id,0);
			strcpy(control,wpd.bufor); //kopiuemy do bufora pamieci cyklicznej
			get_up(sem_id,0);
			printf("Pobrano z pliku 40 znakow, zachowano w pamieci dzielonej\n");
			sleep(1);
			control =control+ 40;
			if(control - start >= SIZE)
				control = start;
			i =i+ 40;
		}
		
		fclose(wejscie);
		shmdt((void*)(start));
		//shmdt odłącza segment pamięci dzielonej odwzorowany pod adresem podanym w shmaddr z przestrzeni adresowej procesu wywołującego tę funkcję. Przekazany funkcji w parametrze shmaddr adres musi być równy adresowi zwróconemu wcześniej przez wywołanie shmat(). 


		exit(0);
	default: 
		time_delay();
		while(i<size)
		{
			get_down(sem_id,0); //opuszczenie semafora
			strcpy(wpd.bufor,control);  //kopiujemy do bufora
			get_up(sem_id,0);   //podniesienie semafora	
			fputs(wpd.bufor,wyjscie);      // z bufora do pliku
			printf("Odczytano z pamieci dzielonej 40 znakow, pisano do pliku\n");
			sleep(1);        //usypiamy
			control =control+ 40;     //dodajemy do wskaznika 60 znakow
			if(control - start >= SIZE)
				control = start;
			i =i+ 40;
		}

		fclose(wyjscie);
		shmdt((void*)(start));
		
		exit(0);
	}
	return 0;
}

