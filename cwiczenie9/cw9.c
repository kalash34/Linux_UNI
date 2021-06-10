#define _REENTRANT
#include <pthread.h>
#include <stdio.h>

#define MAX 50


// zm globalna- domyslnie wartosc 0


unsigned int zm_global;

// muteks wspolny dla czterech watkow



pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


//identyfikatory

pthread_t watki[4];



void gotoxy(unsigned int x, unsigned int y)
{
	printf("\033[%d;%dH", y, x);
}

// obsluga sekcji krytycznej:
// 1) zapis wartosci z watku -> zmienna globalna
// 2) wyswietlenie informacji w czesci watku i czesci s.k.
// 3) uspienie watku w sekcji krytycznej na 4 sekundy

void sekcja_krytyczna(int nr_watku, unsigned int wartosc)
{
	zm_global = wartosc;
	gotoxy(1,nr_watku*2);	printf("\tW sekcji krytycznej...                  \n");
	gotoxy(72,2);		printf("%4d\n",nr_watku);
	gotoxy(74,3);		printf("%2d\n",wartosc);
	sleep(4);
	gotoxy(72,2);		printf("brak\n");
}

void obsluga(int nr_watku)
{
	int a = 0;
	int licznik = 0;
	gotoxy(1,2*nr_watku);	printf("\tWykonywanie...\n");

	while(1)
	{
		gotoxy(14, 1+(nr_watku-1)*2);	printf("%2d\n", a);	sleep(nr_watku);

		if(licznik==6)
		{
			gotoxy(1,2*nr_watku);  printf("\tWatek chce wejsc do sekcji krytycznej\n");
			pthread_mutex_lock(&mutex);
			sekcja_krytyczna(nr_watku,a);
			pthread_mutex_unlock(&mutex);
			gotoxy(1,2*nr_watku);  printf("\tProcessing...                        \n");
			licznik = 0;
		}
		a += 1;
		if(a>=MAX) a=0;
		licznik++;
	}

}	

void *funkcja1(void *p)
{
	obsluga(1);
}


void *funkcja2(void *p)
{
	obsluga(2);
}


void *funkcja3(void *p)
{
	obsluga(3);
}


void *funkcja4(void *p)
{
	obsluga(4);
}




int main()
{


	system("clear");
//drukujemy informacje
	printf("Watek pierwszy: a =\n\nWatek drugi: b =\n\nWatek trzeci: c =\n\nWatek czwarty: d =\n\n");

	gotoxy(60,1);	printf("SEKCJA KRYTYCZNA");
	gotoxy(58,2);	printf("AKTUALNY WATEK: brak");
	gotoxy(45,3);	printf("ZMIENNA GLOBALBA:   0");

//wskazniki do funkcji
	void *(*(funkcja[4]))(void *) = {funkcja1, funkcja2, funkcja3, funkcja4};

// tworzymy watki
	int i;
	for(i=0; i<4; i++){
		pthread_create(watki+i, NULL, funkcja[i], 0);
	}

// wstrzymanie wykonywania main() do momentu zakonczenia watku watki[0]
// (nigdy nie nastapi;

	pthread_join(watki[0],0);


	return 0;
}









