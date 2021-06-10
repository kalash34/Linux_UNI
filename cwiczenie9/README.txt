========================================================================
Autor: Bartosz Polaszek,                               
========================================================================


* Zawartosc:
============
Program pierwszy jest implementacja problemu wzajemnego wykluczania
przy pomocy watkow


Demonstracja dzialania watkow

Opis:

1) Kompilacja:
make all

2) Uruchamianie:
./cw9

3) Dzialanie:

Program uruchamia cztery watki.
Wyniki ich dzialania wyswietlane sa w lewej czesci ekranu w formacie:

Program operuje na 4 watkach, rezultaty ich dzialania prezentuja sie w lewej czesci
ekranu.


Kazdy z czterech watkow wyswietla taka informacje, podaje przy tym swoj numer 
zmienna liczba to wartosc zwiazana z watkiem. Jest inkrementowana co okreslony odstep czasu.

Gdy liczba=50 jest zerowana, naliczanie trwa nadal.

Gdy nastapi 6 inkrementacji w watku nastepuje wejscie do sekcji krytycznej.
Komunikat  zamieniany jest z Processing na "Zamiar dostania sie do sekcji krytycznej" gdy inny watek jest w sekcji 
- dzialanie watku jest wstrzymywane do czasu zwolnienia sekcji.

Sekcja-Krytyczna:

wypisanie numeru watku 
wpisanie do zamiennej globalnej wartosci  watku 
Zmiana opisu watku
wyjscie z sekcji krytycznej




