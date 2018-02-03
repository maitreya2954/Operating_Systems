#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

char *str1 = "./MatMul";
char *str2 = "./MatInv";
char *str3 = "./QuickSort";

void *runner(void *param)
{
	system(param);
	pthread_exit(0);
}



int main(int argc, char *argv[])
{
	int i, policy;
	pthread_t tid[3];
	pthread_attr_t attr;
	/* get the default attributes */
	
	pthread_attr_init(&attr);
	
	//CHECK THE SCHEDULINIG POLICY INITIALLY

	/* get the current scheduling policy */
	if (pthread_attr_getschedpolicy(&attr, &policy) != 0)
		printf("Unable to get policy. \n");
	else 
	{
		if (policy == SCHED_OTHER)
			printf("initially SCHED OTHER \n");
		else if (policy == SCHED_RR)
			printf("initially SCHED RR \n");
		else if (policy == SCHED_FIFO)
			printf("initially SCHED FIFO \n");
	}
	/* set the scheduling policy - FIFO, RR, or OTHER */
	pthread_attr_setschedpolicy(&attr, SCHED_FIFO);

	//CHECK THE SCHEDULINIG POLICY FINALLY

	if (pthread_attr_getschedpolicy(&attr, &policy) != 0)
		printf("Unable to get policy. \n");
	else 
	{
		if (policy == SCHED_OTHER)
			printf("finally SCHED OTHER \n");
		else if (policy == SCHED_RR)
			printf("finally SCHED RR \n");
		else if (policy == SCHED_FIFO)
			printf("finally SCHED FIFO \n");
	}

	pthread_create(&tid[0],&attr,runner,str1);
	pthread_create(&tid[1],&attr,runner,str2);
	pthread_create(&tid[2],&attr,runner,str3);
	
	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
	pthread_join(tid[2],NULL);

}
