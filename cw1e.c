

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>





#define _XOPEN_SOURCE 500







int main(){


int i,bb;




printf(" Zad 1 e) \n");

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
	   pid_t pgrp=getpgrp();
	   setpgid(pom, pgrp);
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
