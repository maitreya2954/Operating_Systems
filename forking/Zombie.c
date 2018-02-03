#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{

	int pid = fork();
	if (pid == 0)
	{
        //CHILD 
       printf("\nChild starting...\n");
		printf("\nI am Child with id: %d  and my parent id: %d \n\n",getpid(),getppid());
		printf("\nChild Killed...\n");
   	}
 
    else if(pid > 0)
	{
		//PARENT
		wait(0);
		printf("\n\nZombie Parent starting...\n");
		printf("\nI am Parent with id: %d  and my parent id: %d \n\n",getpid(),getppid());
		printf("parent Killed\n");		
	} 
	else
	{
		printf("\nFailed to fork process 1\n");
        exit(1);
	}  
	       
	return(0);
}