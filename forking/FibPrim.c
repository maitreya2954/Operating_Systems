#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int n;

	printf("Enter the value of n\n");
	scanf("%d",&n);

	int pid = vfork();

	if (pid == 0)
	{
		//Child Prime Number
		printf("\nI am Child with id: %d  and my parent id: %d \n\n",getpid(),getppid());
		printf("Generating first %d Prime Numbers ... \n\n",n);

		int flag = 1, num = 0, data = 2;

		while (num < n) {
			for (int i = 2; i <= data - 1; i++)
			 {
				if (data % i == 0) 
				{
					flag = 0;
					break;
				}
			}

			/* print prime numbers alone */
			if (flag) 
			{
				printf("%d ", data);
				num = num + 1;
			}

			data = data + 1;
			flag = 1;
		}
		exit(0);

   	}
 
    else if(pid > 0)
	{
		wait(NULL);
		//PARENT Fibonacci Numbers

		printf("\nI am Parent with id: %d and my parent id: %d \n\n",getpid(),getppid());
		printf("Generating first %d Fibonacci Numbers\n\n",n);
		n=n-2;
		int fib1 = 0, fib2 = 1, fib3, count = 0;
	
	    printf("%d ", fib1);
	    printf("%d ", fib2);
		while (count < n)
	    {
	        fib3 = fib1 + fib2;
	        count++;
	        printf("%d ", fib3);
	        fib1 = fib2;
	        fib2 = fib3;
	   	}

		printf("\n");
		exit(0);
				
	} 

	else
	{
		printf("\nFailed to fork process 1\n");
        exit(1);
	}  
	
	//printf("parent id --%d my id --%d\n",getppid(),getpid());
       
	return(0);
}