#define _SVID_SOURCE

#include "funkcje.h"

#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<unistd.h>
#include<stdlib.h>
 
 
 
union semun
{	int val; //wartość  SETVAL
	struct semid_ds *buf; //bufor dla IPC_stat/IPC_SET
	unsigned short *tab;	//tablica dla GETALL,SETALL
};
 
 
 
 
 
 
int tworzenie(key_t key)
{
	int id; //id dla zbioru semaforów
	id=semget(key,1,IPC_CREAT|0666);	
	if(id==-1)
	{	perror("błąd tworzenia semafora\n");
		exit(1);	
	}							/*tworzy zbiór  składający się z 1 semafora dla klucza key o*/ 			//flagach dostępu IPC_CREAT|IPC_EXCL|0666 
	return id;			//0666-mozliwosc wykonywania wszystkich operacji przez 														wszystkie 														procesy
 
 
}

key_t uzyskaj_dostep()
{
	key_t key;	
	key=ftok("./semafory",'B');
	return key;
 
}
int kolejka(int id)
{
	int licznik;
	licznik = semctl(id, 0, GETNCNT); //odczytanie liczby procesów czekających
	if(licznik==-1) perror("błąd GETNCNT");	
	return licznik;
}
void inicjalizacja(int id)
{
	union semun kontrola;
	kontrola.val=1;
	semctl(id,0,SETVAL,kontrola); /* argumenty identyfikator zbioru semaforow (zwracany przez semget),semnum: numer*/ 		
	fprintf(stdout,"semafor zainicjowany : podniesiony\n");	//semafora w zbiorze,cmd kodpolecenia,arg 								//parametry polecenia			
							//ustawia SETVAL na 1
 
}
 
void podnies(int id)
{
 
	struct sembuf semOp;
	semOp.sem_num=0;
	semOp.sem_op = 1;	//wartość sem_op= 1->semafor podniesiony
	semOp.sem_flg=0; 
	semop(id,&semOp,1);
	printf("semafor podniesiony!\n");
 
}
void opusc (int id)
{
 
	struct sembuf semOp;
	semOp.sem_num=0;
	semOp.sem_op=-1;		//wartość semo_op=-1 ->semafor opuszczony
	semOp.sem_flg=0;
	semop(id,&semOp,1);
	printf("semafor opuszczony! \n");
 
}
void usunSem(int id)
{
 
	semctl(id,0,IPC_RMID);
	fprintf(stdout,"semafor został usunięty!\n");
}
