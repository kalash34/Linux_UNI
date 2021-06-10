#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>


const int ilosc_danych2 = 10;
int wartosc2 = 0;

int const rozmiar_bufora2= 50;



void konsument()
{
    int czytaj_potok;
    while (wartosc < ilosc_danych2) //odczytujemy porcje danych z bufora
    {
        czytaj_potok = open("pipe", O_RDONLY);
        char buf[rozmiar_bufora2];   //zdefiniowany bufor
	//funkcja write podejmuje probe zpisania ilosci danych okreslonej zmienna rozmiar_bufora okreslonej deskryptorem zapisz_potok
        read(czytaj_potok, buf, rozmiar_bufora2); //odczytujemy dane z pliku o deskryptorze czytaj_potok

        printf("Konsument %d pobiera wartosc: %s\n", getpid(), buf);
        wartosc = atoi(buf); //rzutujemy na integera

        if (wartosc2 == ilosc_danych2)
        {
            break;
        }
    }
    close(czytaj_potok); //zamykanie pliku, zwalnianie deskryptora
}
