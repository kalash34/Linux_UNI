
#include <sys/ipc.h>
#include <sys/sem.h>

int tworzenie(key_t key);

key_t uzyskaj_dostep();

int kolejka(int id);

void inicjalizacja(int id);

void podnies(int id);

void opusc (int id);

void usunSem(int id);


