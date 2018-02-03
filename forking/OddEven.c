#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int n;
	printf("Enter the total no. of numbers you want to print\n");
	scanf("%d", &n);
	int a[n];

	int pid = vfork();
	if (pid == 0)
	{
        //CHILD ODD
        printf("\nI am Child with id: %d and my parent id: %d \n\n",getpid(),getppid());
        for (int i = 1; i < n ; i = i + 2)
    	{
	    	// printf("%d\n",i);
	    	// sleep(1);
	    	a[i] = i;
    	}
    	exit(0);

   	}
 
    else if(pid > 0)
	{
		//PARENT EVEN
				
		printf("\nI am Parent with id: %d and my parent id: %d \n\n",getpid(),getppid());
		for (int i = 0; i < n ; i = i + 2)
    	{
	    	// printf("%d\n",i);
	    	// sleep(1);
	    	a[i] = i;
    	}

	} 
	else
	{
		printf("\nFailed to fork process 1\n");
        exit(1);
	}  
	printf("Array: ");
	for (int i = 0; i < n; ++i)
		printf("%d  ",a[i] );
	
	
	return(0);
}