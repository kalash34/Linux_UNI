#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define _XOPEN_SOURCE 500


int main(){


int bb;
int i;


  pid_t pid, ppid, pgid;
  gid_t gid;
  uid_t uid;

//cw 1 a


	uid= getuid();
	pid= getpid();
	gid = getgid();
	ppid = getppid();
	pgid = getpgid(pid);

	printf("Zad 1a\n ");

	/* PID procesu  */

	if (pid < 0) {
	  perror("Blad pid");
	} else {
	  printf("PID= %d ", pid);
	}

	/* PID rodzica */
	if (ppid < 0) {
	  perror("Blad ppid");
	} else {
	  printf("PPID= %d ", ppid);
	}

	/* ID grupy */
	if (gid < 0) {
	  perror("Blad gid");
	} else {
	  printf("GID= %d ", gid);
	}

	

	/* uid */
	if (uid < 0) {
	  perror("Blad uid");
	} else {
	  printf("UID= %d ", uid);
	}


	/* PGID grupy */
	if (pgid < 0) {
	  perror("Blad pgid");
	} else {
	  printf("PGID= %d ", pgid);
	}

	

	printf("\n");
	
	printf("\n");

//cw 1 b)


printf(" Zad 1 b) \n");

for (i = 0; i < 3; i++)
    {
        bb = fork();
        switch (bb)
        {
        case -1:
            perror("Blad forkowania");
            exit(1);
        case 0:
           wait(NULL);
	   pid_t pom= getpid();

            printf("UID= %d GID= %d PID= %d PPID= %d PGID= %d\n", getuid(),getgid(),getpid(),getppid(),getpgid(pom));

        default:
        
        if (bb > 0 && i == 0)
        {
		//czekamy
            sleep(7);
        }

	}
    }





}



