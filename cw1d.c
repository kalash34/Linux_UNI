#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>







//przechowamy sobie wydruk pokolen w buforze na tekst
void wiadomosc(const char * wiad, int blad)
{
  char s[1024];
  snprintf(s, sizeof s, "PID %d: %s", (int) getpid(), wiad);

  if (blad)
  {
    errno = blad;
    perror(s);
    exit(EXIT_FAILURE);
  }

  puts(s);
}

int main()
{


  int Liczba_pokolen=4;
  pid_t pid = 0;

  //Na bierzaco wyswietlamy tworzone dzieci w pokoleniach
  int g=0;

  for (g = 0; g < Liczba_pokolen; g++)
  {
    wiadomosc("Przed Fork", 0);

    switch (pid = fork())
    {
      case -1:
      {
        wiadomosc("blad!", errno);

        break;
      }

      case 0:
      {
        wiadomosc("Nowe Dziecko", 0);

        break;
      }

      default:
      {
        char s[1024];
        snprintf(s, sizeof s, "Stworzno dziecko o PID= %d", (int) pid);
        wiadomosc(s, 0);
        g = Liczba_pokolen;   /* koniec petli */

        break;
      }
    }
  }

  wiadomosc("Sleep na 4 sekundy. ", 0);
  sleep(4);

  if (0 != pid)                           /* jesli  fork'owalismy dziecko */
  {
    wiadomosc("Czekamy na dziecko az sie skonczy. ", 0);
    if (-1 == wait(NULL))                 /* czekamy na dziecko */
    {
      wiadomosc("wait() -niepowodzenie", errno);
    }
  }

  wiadomosc("Dziecko sie skonczylo", 0);

  return EXIT_SUCCESS;
}


