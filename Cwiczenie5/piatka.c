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

void konsument()
{
    int czytaj_potok;
    while (wartosc < ilosc_danych) //odczytujemy porcje danych z bufora
    {
        czytaj_potok = open("pipe", O_RDONLY);
        char buf[rozmiar_bufora];   //zdefiniowany bufor
	//funkcja write podejmuje probe zpisania ilosci danych okreslonej zmienna rozmiar_bufora okreslonej deskryptorem zapisz_potok
        read(czytaj_potok, buf, rozmiar_bufora); //odczytujemy dane z pliku o deskryptorze czytaj_potok

        printf("Konsument %d pobiera wartosc: %s\n", getpid(), buf);
        wartosc = atoi(buf); //rzutujemy na integera

        if (wartosc == ilosc_danych)
        {
            break;
        }
    }
    close(czytaj_potok); //zamykanie pliku, zwalnianie deskryptora
}



void usuwanie_potoku()
{
    if(unlink("pipe") == -1) //wywolanie funkcji unlink usuwajacej dowiazanie do pliku z argumentu - czyli u nas "pipe"
    {
        perror("Blad funkcji unlink\n");                    
        _exit(EXIT_FAILURE);    //wywolanie systemowe _exit - natychmiastowe zakonczenie procesu,zamkniecie wszystkich deskryptorow nalezacych do procesu
    }				//adopcja wszystkich procesow potomnych przez proces init
    printf("Usunieto Potok.\n");
}
 



int main()
{
    mkfifo("pipe", 0644);
 if (fork() == 0)
    {
        printf("Tworzymy proces producenta %d\n", getpid());
        producent();
        printf("Producent, PID= %d zakonczyl prace\n", getpid());

    if(atexit(usuwanie_potoku) != 0)
    {
        perror("Blad funkcji atexit !!\n");                   
        exit(EXIT_FAILURE); //blad przerwania, wywolanie exit
    }

    }

    if (fork() == 0)
    {
        printf("Tworzymy proces konsumenta %d\n", getpid());
        konsument();
        printf("Konsument, PID= %d zakonczyl prace\n", getpid());
    if(atexit(usuwanie_potoku) != 0)
    {
        perror("Blad funkcji atexit !!\n");                    
        exit(EXIT_FAILURE);
    }
    }

    wait(NULL);
    printf("Procesy potomne dla PID= %d zakonczyly prace \n", getpid());
    exit(0);






}
