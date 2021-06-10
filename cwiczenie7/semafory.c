#ifndef _SEM_LIB_
#define _SEM_LIB_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "semafory.h"

// stworzenie zbioru semaforow
sem sem_create(const char *file, char p, int sem_count)
{
	key_t key = ftok(file,p);
	return semget(key,sem_count,IPC_CREAT|0666);
}

// ustawienie wartosci semafora sem_num w zbiorze sem_id
void set_val(sem sem_id, int sem_num, int val)
{
	semctl(sem_id, sem_num, SETVAL, val);
}

// pobranie wartosci semafora sem_num w zbiorze sem_id
int get_val(sem sem_id, int sem_num)
{
	return semctl(sem_id, sem_num, GETVAL);
}

// pobranie liczby procesow czekajacych na PODNIESIENIE semafora sem_num
int get_ncnt(sem sem_id, int sem_num)
{
	return semctl(sem_id, sem_num, GETNCNT);
}

// pobranie liczby procesow czekajacych na OPUSZCZENIE semafora sem_num
int get_zcnt(sem sem_id, int sem_num)
{
	return semctl(sem_id, sem_num, GETZCNT);
}

// usuniecie zbioru semaforow
void sem_delete(sem sem_id)
{
	semctl(sem_id,0,IPC_RMID);
}

// opuszczenie semafora sem_num
void get_down(sem sem_id, int sem_num)
{
	struct sembuf bufor = {sem_num,-1,0};
	semop(sem_id, &bufor, 1);
}

// podniesienie semafora sem_num
void get_up(sem sem_id, int sem_num)
{
	struct sembuf bufor = {sem_num,1,0};
	semop(sem_id, &bufor, 1);
}

// wypisuje wartosci GETVAL, GETNCNT, GETZCNT
void sem_describe(sem semid, int i)
{
	while((i--)>0) printf("\t");
	int pomiar;
	pomiar = get_val(semid,0);
	printf("[ GETVAL: %d; ", pomiar);
	pomiar = get_ncnt(semid,0);
	printf("GETNCNT: %d; ", pomiar);
	pomiar = get_zcnt(semid,0);
	printf("GETZCNT: %d ]\n", pomiar);
}
#endif

