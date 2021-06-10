
/* wiadomosc.h

   
*/


#include <sys/types.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <stddef.h>                     
#include <limits.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>

#define SERVER_KEY 0x1aaaaaa1           /* Klucz kolejki */

struct requestMsg {                     /* Request'y (klient do server) */
    long mtype;                         /* Unused */
    int  clientId;                      /* ID kolejki klienta */
    char pathname[PATH_MAX];            /* plik zwracany */
};

/* REQ_MSG_SIZE liczy rozmiar 'mtext' czesci z 'requestMsg' struct
   Uzywamy offsetof() by przechwycic mozliwosc ze sa bity
   miedzy 'clientId' oraz 'pathname' polami */


#define REQ_MSG_SIZE (offsetof(struct requestMsg, pathname) - \
                      offsetof(struct requestMsg, clientId) + PATH_MAX)

#define RESP_MSG_SIZE 8192

struct responseMsg {                    /* Odpowiedzi (server do klienta) */
    long mtype;                         /* Jedna z RESP_MT_* wartosci ponizej */
    char data[RESP_MSG_SIZE];           /* Zawartosc pliku / wiadomosc odpowiadajaca */
};

/* Rodzaje odpowiedzi z servera do klienta */

#define RESP_MT_FAILURE 1               /* Plik nie moze byc otwarty */
#define RESP_MT_DATA    50               /* Zawartosc wiadomosci  */
#define RESP_MT_END     3               /* Tresc pliku kompletna */
