#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>


const int ilosc_danych = 10;
int wartosc = 0;

int const rozmiar_bufora= 50;



//proces producenta
void producent()
{
    int zapisz_potok; //nasz deskryptor
    while (wartosc < ilosc_danych) //wypelniamy bufor danymi
    {
        zapisz_potok = open("pipe", O_WRONLY);
        wartosc++;
        char str[rozmiar_bufora];  //ciag znakow o rozmiarze bufora
        sprintf(str, "%d", wartosc);
        printf("Producent %d tworzy wartosc: %s\n", getpid(), str);
        write(zapisz_potok, str, rozmiar_bufora); //funkcja write podejmuje probe zpisania ilosci danych okreslonej zmienna rozmiar_bufora okreslonej deskryptorem zapisz_potok

        if (wartosc == ilosc_danych)
        {
            break;
        }
    }
    close(zapisz_potok); //zamykanie pliku, zwalnianie deskryptora
}
