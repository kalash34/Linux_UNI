#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>



int main( int argc, char * argv[] ){
int id;
int i;
/*


switch (fork())
{

case -1:
	perror("fork error");
	exit(1);
case 0: 
	//execl("./nowy_program.x","nowy_program.x",NULL);
	execl(argv[1],NULL);
	perror("execl error");
	_exit(2);
default: 



};


-wall -std=c99 -pedantic

*/




for (i = 0; i < 3; i++)
    {
        id = fork();
        switch (id)
        {
        case -1:
            perror("FORK ERROR");
            exit(1);
        case 0:
            sleep(1);
		pid_t pom=getpid();
		//execl(argv[1],NULL);
		execl("/bin/ls", "ls", "-l", (char *)NULL);
		perror("execl error");
	_exit(2);
	


            printf("\nUID= %d GID= %d PID= %d PPID= %d PGID= %d\n", getuid(),getgid(),pom,getppid(),getpgid(pom));

        default:
        
        if (id > 0 && i == 0)
        {
            sleep(20);
        }
    }

}










}
