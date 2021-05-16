========================================================================
Autor: Bartosz Polaszek,                               
========================================================================


* Zawartosc:
============

Katalog zawiera program cwiczenie 1  w C.

1ab) cwiczenia a i b:
Program wypisuje identyfikatory UID, GID, PID, PPID oraz PGID
dla danego procesu.
Nastepnie w petli for wykonujemy funkcje fork trzy razy dla procesu macierzystego i wszystkich procesow potomnych.
Przy pomocy funkcji wait(NULL) sprawiamy ze proces czeka na zakonczenie wszystkich procesow potomnych.
Do obslugi bledow uzywamy podstawowej funkcji perror wypisujacej komunikat o bledzie.


1c) cwiczenie c:
Nastepnie w petli for wykonujemy funkcje fork trzy razy dla procesu macierzystego i wszystkich procesow potomnych.
(analogicznie do poprzedniego)
Przy pomocy funkcji sleep sprawiamy ze proces init adoptuje wszystkie procesy potomne. (drzewo procesow jest w pliku procesy-ale dla wiekszej ilosci
wywolan petli zeby bylo widac lepiej)


1d) w petli for forkujemy aby uwidocznic tworzone dzieci dla okreslonej przez uzytkownika liczby pokolen.
Przechowujemy stworzone dzieci w buforze na tekst.

1e)Analogicznie do b ale sprawiamy przy pomocy funkcji setpgid ze kazdy proces potomny staje sie liderem wlasnej grupy procesow.




Aby uruchomic programy nalezy uzyc polecenia:


-> Aby uruchomic program1ab, nalezy wykonac komende:
       make run1

-> Aby uruchomic program1c, nalezy wykonac komende:
       make run2

-> Aby uruchomic program1d, nalezy wykonac komende:
       make run3

-> Aby uruchomic program1e, nalezy wykonac komende:
       make run4

-> Aby wyczyscic zawartosc katalogu (usunac zbedne pliki), nalezy wykonac:
       make clean

-> W celu archiwizacji oraz kompresji katalogu nalezy wykonac:
       make tar

