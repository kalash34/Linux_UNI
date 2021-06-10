
Demonstracja uzycia mechanizmu pamieci dzielonej
Autor: Bartosz Polaszek

* Zawartosc:

Program jest implementacja problemu producenta-konsumenta
przy pomocy pamieci dzielonej oraz semaforow. 
Zamiast potokow do przechowania danych uzywamy bufora cyklicznego
umieszczonego w pamieci dzielonej, gdzie elementami sa porcje bajtow.
Programy dla producenta i konsumenta wywolujemy 
w procesach potomnych utworzonych przez fork().


Wielkosc pamieci dzielonej okreslono na 160 bajtow.
Zapis i odczyt z niej bedzie nastepowal cyklicznie po 40 bajtow - po zapisie 40 bajtow wskaznik zapisu/odczytu zostanie przesuniety o 40 bajtow 'dalej', a gdy dotrze do konca obszaru powroci na poczatek obszaru pamieci dzielonej.

Proces potomny odpowiedzialny jest za odczytywanie kolejnych porcji znakow z pliku i umieszczanie ich w pamieci dzielonej. Odbywa sie to w petli - fgets odczytuje dane z pliku a strcpy w sekcji krytycznej wstawia te dane do pamieci poczawszy od danego wskaznika. Wskaznik ten jest nastepnie przesuwany o 40 pozycji (znakow). Proces jest wstrzymywany, nastepnie sprawdza sie czy osiagnieto koniec obszaru pamieci dzielonej. Jesli tak wskaznik jest przesuwany na pozycje poczatkowa.

Petla odczytujaca wykonuje sie tak dlugo az zostana przeczytane wszystkie znaki pliku zrodlowego.




Przed tym inicjiujemy semafory i pamiec dzielona, a po zakonczeniu procesow potomnych
czyscimy semafor i pamiec.

W osobnym pliku tworze biblioteke do podstawowych operacji na semaforach i pamieci
dzielonej. Z tych bibliotek utworzone sa biblioteki statyczna i dzielona przez plik Makefile.



Aby uruchomic program nalezy uzyc polecenia:


-> Aby uruchomic program, nalezy wykonac komende:
       make run1


-> Aby wyczyscic zawartosc katalogu (usunac zbedne pliki), nalezy wykonac:
       make clean

-> W celu archiwizacji oraz kompresji katalogu nalezy wykonac:
       make tar

