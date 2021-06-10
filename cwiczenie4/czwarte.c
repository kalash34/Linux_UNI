#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>


int pomiar_lini(FILE *plik)
{
	fseek(plik,0,SEEK_END); //ustawiamy kursor na poczatku pliku
	int linia = ftell(plik);
	rewind(plik);	//resetujemy pozycje kursora


	return linia;
}



int main(int argc, char *argv[])
{
	
	//deskryptory plikow
	int filedes[2];
	
	//sprawdzamy czy funkcja pipe nie zwroci nam bledu
	if(pipe(filedes)==-1)
	{
		perror("Blad funkcji pipe   !\n");
		
		
	}

	
	int pomiar, rozmiar;
	//otwieramy pliki na ktorych bedziemy operowac
	FILE *surowiec = fopen("surowiec.txt","r");
	FILE *towar = fopen("towar.txt","w");

	//zmienne pomocnicze na dane
	char odczytaj_bufor[61];
	char zapisz_bufor[61];

	rozmiar = pomiar_lini(surowiec)+60;

	pomiar = 0; //mierzymy wczytywane linie

	
	switch(fork())
	{
	case -1: perror("Blad fork\n");
		exit(1);
	
	case 0: close(filedes[0]); //zamykamy deskryptor
		while(pomiar<=rozmiar)
		{
			fgets(odczytaj_bufor,60,surowiec);	//pobieramy linie z pliku
			write(filedes[1],odczytaj_bufor,60);
			printf("Wczytano z pliku do potoku :\n%s\n",odczytaj_bufor);
			pomiar = pomiar+60; 			//zwiekszamy pomiar
			//usypiamy
			sleep(1);
		}

		close(filedes[1]); //zamykamy deskryptor
		
		break;
	default: close(filedes[1]); //zamykamy deskryptor
		while(pomiar<=rozmiar)
		{
			read(filedes[0],zapisz_bufor,60);
			fputs(zapisz_bufor,towar); //zapisujemy linie do pliku
			printf("Odczytano z potoku do pliku :\n%s\n",zapisz_bufor);
			pomiar =pomiar+60; //zwiekszamy pomiar
			sleep(1);
		}
		close(filedes[0]);
	}
	fclose(surowiec);
	fclose(towar);
	
}




