#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int pid = fork();
	if(pid == 0)
	{
		printf("\nHello from child! parent id: %d my id: %d",);
	}	
	return 0;
}