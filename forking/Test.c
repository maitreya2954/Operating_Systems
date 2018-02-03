#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
	printf("The passed argumnets are:\n");
	for (int i = 0; i < argc; ++i)
		printf("%s   ",argv[i]);   
	printf("\n");	    
    
	return 0;
}