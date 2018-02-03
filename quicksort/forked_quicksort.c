#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
void printArr( int arr[], int n )
{
    int i;
    for ( i = 0; i < n; ++i )
        printf( "%d ", arr[i] );
}
 
int main()
{
    int arr[] = {4, 3, 5, 2, 1, 3, 2, 3};
    int n = sizeof( arr ) / sizeof( *arr );
    int flag=1;
    int l=0,h=n-1,p;
    pid_t pid = vfork();
    if (pid==0)
    {
	    
	    int stack[ h - l + 1 ];
	    int top = -1;
	    stack[ ++top ] = l;
	    stack[ ++top ] = h;
	    while ( top >= 0 )
	    {
	        h = stack[ top-- ];
	        l = stack[ top-- ];
	 
	 		sleep(1);
	        if ( p-1 > l )
	        {
	            stack[ ++top ] = l;
	            stack[ ++top ] = p - 1;
	        }
	 
	        if ( p+1 < h )
	        {
	            stack[ ++top ] = p + 1;
	            stack[ ++top ] = h;
	        }
	    }
	    flag=0;
	    printArr( arr, n );
	    exit(0);
	}
	else if(pid>0)
		{
			//sleep(1);
		while(flag)
		{
			int x = arr[h];
		    int i = (l - 1);
		 
		    for (int j = l; j <= h- 1; j++)
		    {
		        if (arr[j] <= x)
		        {
		            i++;
		            int temp=arr[i];
		            arr[i]=arr[j];
		            arr[j]=arr[i];
		        }
		    }
		    int temp=arr[i+1];
		    arr[i+1]=arr[h];
		    arr[h]=temp;
		    p = (i + 1);
		    sleep(1);
		}

	}
   
    return 0;
}