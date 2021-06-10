Autor: Bartosz Polaszek,                               
========================================================================


* Zawartosc:
============
Program pierwszy jest implementacja algorytmu piekarni
(Bakery's Algorithm)


Opis:

1) Kompilacja:
make all

2) Uruchamianie:
./cw10

3) Dzialanie:

powtorz
    wybieram[i] := true;
    number[i] := max(number[0], number[1], ..., number[n - 1])+1;
    wybieram[i] := false;
    for j := 0 to n - 1
        do begin
            while wybieram[j] do brak_operacji;
            while number[j] != 0
                and (number[j], j) < (number[i], i) do brak_operacji;
        end;

        sekcja_krytyczna
    
    number[i] := 0;
    
        sekcja_reszty

dopoki false;

Wyjasnienie:

Najpierw proces ustawia zmienna wybieram na True- powodujac ze zawartosc wchodzi do sekcji krytycznej. Wtedy zostaje przypisany do niej najwiekszy powiazany "ticket" odwolujacy
sie do innego procesu. Wtedy zmienna choosing ustawia sie na False powodujac ze ma nowy numer "ticket". To jest najtrudniejsza czesc algorytmu.
To w pewnym sensie mala sekcja krytyczna wewnatrz siebie. Powod pierwszych trzech linii to jesli proces modyfikuje wartosc swojego "ticket" to wtedy jakis inny proces nie powinien
miec pozwolenia na sprawdzenie swojej poprzedniej wartosci "ticket", ktora jest teraz przestarzala. Dlatego wewnatrz petli for przed sprawdzeniem wartosci "ticket" najpierw musimy sie
upewnic ze wszystkie inne procesy maja zmienna wybieram na False.
Nastepnie sprawdzamy wartosci "ticket" procesow gdzie procesy z najmniejsza ilosci ticket number/proces id wewnatrz sekcji krytycznej.
Sekcja wyjsciowa resetuje wartosc ticket na zero.

