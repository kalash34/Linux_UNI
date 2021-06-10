========================================================================
Autor: Bartosz Polaszek,                               
========================================================================


* Zawartosc:
============
Program jest implementacja problemu producenta i konsumenta
przy pomocy potokow nienazwanych

1.
Tworzymy potok za pomoca funkcji pipe
Otwieramy plik do odczytu i zapisu
Tworzymy proces potomny w ktorym odczytujemy dane do potoku, a rodzic pobiera dane z potoku i dostarcza je do
pliku wyjsciowego

2.
Na poczatku odczytania zamykamy potok
W petli pobieramy dane do bufora, zapisujemy funkcja write
Zamykamy potok


Proces macierzysty zamyka potok do zapisu.

Odczytujemy dane funkcja read, zapisujemy w pliku funkcja fputs.
Na koncu zamykamy potok do odczytu.

Aby uruchomic program nalezy uzyc polecenia:


-> Aby uruchomic program, nalezy wykonac komende:
       make all


-> Aby wyczyscic zawartosc katalogu (usunac zbedne pliki), nalezy wykonac:
       make clean

-> W celu archiwizacji oraz kompresji katalogu nalezy wykonac:
       make tar

