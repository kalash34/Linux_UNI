========================================================================
Autor: Bartosz Polaszek,                               
========================================================================


* Zawartosc:
============
Program pierwszy jest implementacja problemu producenta i konsumenta
przy pomocy potokow nazwanych

1.
Tworzymy funkcje producent zapisujacej dane z bufora do pliku okreslonego deskryptorem zapisz_potok
Dane sa symbolicznie reprezentowane przez liczby calkowite, w stalej zapisujemy rozmiar naszego bufora.
Wywolujemy funkcje write. Wypelniamy bufor.
Zamykamy potok.

2.
Tworzymy funkcje konsument reprezentujaca proces konsumenta
Odczytujemy dane z pliku o deskryptorze czytaj_potok.
Zamykamy potok.

3.
W funkcji main tworzymy potok o sciezce "pipe" i prawach dostepu 0644
i uruchamiamy procesy producenta i konsumenta w dwoch procesach potomnych.

Usuwamy potok.


Program Drugi:

Program drugi jest implementacja problemu producenta i konsumenta
przy pomocy potokow nazwanych tak aby dzialaly dla niezaleznych procesow.
W glownym programie wywolujemy procesy producenta i konsumenta i usuwamy funkcja atexit.
W pliku makefile zamieszczamy komende xterm sluzaca do uruchomienia programow w dwoch terminalach.



-> Aby uruchomic program1, nalezy wykonac komende:
       make jeden


-> Aby uruchomic program2, nalezy wykonac komende:
       make dwa


-> Aby wyczyscic zawartosc katalogu (usunac zbedne pliki), nalezy wykonac:
       make clean

-> W celu archiwizacji oraz kompresji katalogu nalezy wykonac:
       make tar

