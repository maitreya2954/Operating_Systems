#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int pivot,h,l , p;
int n;
int valid_pivot,exit_flag;

void swap ( int* a, int* b )
{
    int t = *a;
    *a = *b;
    *b = t;
}

void * pivotfinder(void * a)
{
	printf("     |\n     |__pivotfinder invoked...\n");
	int *arr=a;
	int x = arr[h];
    int i = (l - 1);
 
    for (int j = l; j <= h- 1; j++)
    {
        if (arr[j] <= x)
        {
            i++;
            swap (&arr[i], &arr[j]);
        }
    }
    swap (&arr[i + 1], &arr[h]);
    p=i+1;
	pthread_exit(0);
}

void * quicksort(void * a)
{
	printf(" |__Quicksort invoked...\n");
	int *arr=a;
	pthread_t tid2;
	pthread_attr_t at;
	pthread_attr_init(&at);
	int stack[ h - l + 1 ];
    int top = -1;
    stack[ ++top ] = l;
    stack[ ++top ] = h;
 	while ( top >= 0 )
    {
        h = stack[ top-- ];
        l = stack[ top-- ];
        pthread_create(&tid2, &at, pivotfinder, arr);
		pthread_join(tid2, NULL);
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
	pthread_exit(0);
}

int main(int argc, char const *argv[])
{
	pthread_t tid1;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	int a[] = {4, 3, 5, 2, 1, 3, 2, 3};
	n=sizeof(a)/sizeof(a[0]);
	h=n-1;
	l=0;
	printf("%s\n", argv[0]);
	pthread_create(&tid1, &attr, quicksort, a);
	pthread_join(tid1,NULL);
	printf("Sorted array: ");
	for (int i = 0; i < n; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	return 0;
}