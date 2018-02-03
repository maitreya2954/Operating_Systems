#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int sum;

void * sumfunction(void * parameter)
{
	char ** argv=parameter;
	int n=atoi(argv[1]);
	sum=(n*(n+1))/2;
	pthread_exit(0);
}

int main(int argc, char const *argv[])
{
	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_create(&tid, &attr, sumfunction, argv);
	pthread_join(tid, NULL);
	printf("Sum is %d\n", sum);
	return 0;
}