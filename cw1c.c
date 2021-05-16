#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>



int main(){


int bb;
int i;


// init adopcja ---> ppid=1

printf(" Zad 1 c) \n");


for (i = 0; i < 3; i++ ){
        bb = fork();
        switch (bb)
        {
        case -1:
            perror("Blad forkowania");
            exit(1);
        case 0:
            sleep(1);
    
	   pid_t pid= getpid();

            printf("UID= %d GID= %d PID= %d PPID= %d PGID= %d \n", getuid(),getgid(),getpid(),getppid(),getpgid(pid));

        default:
        
        if (bb > 0 && i == 0)
        {
            sleep(7);
        }

	}

    }



}
























