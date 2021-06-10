
#include "pthread.h"  
#include "stdio.h"
#include "unistd.h"  
#include "string.h"
  


#define MEMBAR __sync_synchronize()
#define LICZNIK_WATKOW 8
  
volatile int tickets[LICZNIK_WATKOW];
volatile int wybieram[LICZNIK_WATKOW];
  

volatile int zasob;
  
void blokuj(int thread)
{
  
    wybieram[thread] = 1;
  
    MEMBAR;
  
    int max_ticket = 0;
  

    for (int i = 0; i < LICZNIK_WATKOW; ++i) {
  
        int ticket = tickets[i];
        max_ticket = ticket > max_ticket ? ticket : max_ticket;
    }
  
    tickets[thread] = max_ticket + 1;
  
    MEMBAR;
    wybieram[thread] = 0;
    MEMBAR;
  
    for (int other = 0; other < LICZNIK_WATKOW; ++other) {
  
        while (wybieram[other]) {
        }
  
        MEMBAR;
  
        while (tickets[other] != 0 && (tickets[other]
                                           < tickets[thread]
                                       || (tickets[other]
                                               == tickets[thread]
                                           && other < thread))) {
        }
    }
}
  
void odblokuj(int thread)
{
  
    MEMBAR;
    tickets[thread] = 0;
}

void uzyj_zasobu(int thread)
{
  
    if (zasob != 0) {
    printf("Zasob zostal nabyty przez %d, ale jest ciagle w uzyciu przez- %d!\n", thread, zasob);
    }
  
    zasob = thread;
    printf("%d uzywanie zrodla.. \n", thread);
  
    MEMBAR;
    sleep(2);
    zasob = 0;
}
  
void* cialo_watku(void* arg)
{
  
    long thread = (long)arg;
    blokuj(thread);
    uzyj_zasobu(thread);
    odblokuj(thread);

    return NULL;
}
  




int main(int argc, char** argv)
{
  
    memset((void*)tickets, 0, sizeof(tickets));
    memset((void*)wybieram, 0, sizeof(wybieram));
    zasob = 0;
  
  
    pthread_t threads[LICZNIK_WATKOW];
  
    for (int i = 0; i < LICZNIK_WATKOW; ++i) {
  
        pthread_create(&threads[i], NULL, &cialo_watku, (void*)((long)i));
    }
  
    for (int i = 0; i < LICZNIK_WATKOW; ++i) {
  
        pthread_join(threads[i], NULL);
    }
  
    return 0;
}


