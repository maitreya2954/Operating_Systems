#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char const *argv[])
{
	pid_t pid=fork();
	if (pid==0)
	{	
		sleep(1);
		printf("1\n");
		sleep(1);
		printf("2\n");
	}
	else if(pid > 0)
	{
		printf("I am parent\n");
		sleep(1);
		printf("I am parent again\n");
	}
	else
		exit(1);
	return 0;
}