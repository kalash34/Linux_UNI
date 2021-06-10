========================================================================
Autor: Bartosz Polaszek,                               
========================================================================


* Zawartosc:
============
1.
plik klient

   Wyslij wiadomosc do serwera server.c odbierajac
   zawartosc pliku nazwanego w linii polecen, oraz otrzymaj

   zawartosc pliku przez pare wiadmosci wyslanych spowrotem przez serwer. Wyswietl
   calkowita liczbe bitow i wiadomosci otrzymane. Server i klient komunikuja sie przez
   kolejki System V



2.
plik serwer
   Plik serwera ktory uzywa System V kolejek komunikatow do przechwytywania wiadomosci klienta
   (client.c) Klient wysyla wiadomosc poczatkowa
   nazwa oczekiwanego pliku, oraz identyfikator wiadomosci danej kolejki 
   uzyty do wyslania zawartosci pliku spowrotem do dziecka. Serwer probuje
   otworzyc oczekiwany plik. Jezeli plik nie moze byc otwarty, to bledna odpowiedz
   
   Inczej zawartosc oczekiwanego pliku jest wysylana seria wiadomosci
   
   Program obsluguje wiele kolejek komunikatow. Serwer utrzymuje
   kolejke (ze znanym kluczem) zadedykowana do przychodzacych requestow klienta. Kazdy
   klient tworzy wlasna prywatna kolejke ktora jest uzywana do przekazywania
   wiadomosci z serwera spowrotem do klienta

   Program operuje jako konkurencyjny serwer, forkuje nowy proces potomny aby
   obsluzyc kazdego klienta request dopoki czeka na wiadomosc nastepnego klienta.



Aby uruchomic program nalezy uzyc polecenia:


-> Aby uruchomic program, nalezy wykonac komende:
       make all


-> Aby wyczyscic zawartosc katalogu (usunac zbedne pliki), nalezy wykonac:
       make clean

-> W celu archiwizacji oraz kompresji katalogu nalezy wykonac:
       make tar

