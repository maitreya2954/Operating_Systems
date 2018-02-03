#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{

	int pid = fork();
	if (pid > 0)
	{
        //PARENT
        sleep(1);
		printf("\nI am Parent with id: %d  and my parent id: %d \n\n",getpid(),getppid());
		//execlp("ps","ps","-A",NULL);
		execl("/home/maitreya/Desktop/OS-Lab/forking/Sorting","Sorting",NULL);
   	}
 
    else if(pid == 0)
	{
		char *array[]={"-A",NULL};
		printf("\nI am child with id: %d  and my parent id: %d \n\n",getpid(),getppid());
		//execlp("ps","ps","-A",NULL);
		execvp("ls",array);
	} 
	else
	{
		printf("\nFailed to fork process 1\n");
        exit(1);
	}  
	       
	return(0);
}