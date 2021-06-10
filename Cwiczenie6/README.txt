========================================================================
Autor: Bartosz Polaszek,                               
========================================================================


* Zawartosc:
============
Program jest implementacja problemu wzajemnego wykluczania
przy pomocy semaforow nazwanych.

1.Program sklada sie z biblioteki funkcje.c zawierajaca funkcje do
tworzenia, otwierania uzyskiwania wartosci i zamykania semafora.
Do ich implementacji uzywam bibliotek z funkjcami/wywolaniami systemowymi
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
2.W glownym pliku programu tworze specjalny program "powielacz"-
powielajacy procesy realizujace wzajemne wykluczanie-
w oparciu o funkcje fork i exec.
3.
Sam program sekcji krytycznej uruchamiany przez funkcje exec
umieszczam w osobnym pliku sekcja_krytyczna.c



Aby uruchomic program nalezy uzyc polecenia:


-> Aby uruchomic program, nalezy wykonac komende:
       make run1


-> Aby wyczyscic zawartosc katalogu (usunac zbedne pliki), nalezy wykonac:
       make clean

-> W celu archiwizacji oraz kompresji katalogu nalezy wykonac:
       make tar

