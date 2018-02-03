#include <stdio.h>
#include <stdlib.h>
#include <string.h> // memset
#include <pthread.h> // pthread_t, pthread_create, pthread_join
#include <semaphore.h> // sem_init, sem_wait, sem_post
#include <unistd.h>



#define SLEEP_MAX 5

sem_t sem_stu;
sem_t sem_ta;

sem_t mutex;  //to avoid multiple students threads reading same value of next_seat and changing the value of chair[next_seat] simultaneously
//pthread_mutex_t mutex;

int max_seats;

int chair[10];
int count = 0; //number of waiting students
int next_seat = 0;
int next_teach = 0;

void print_chair()
{
	printf("waiting students : ");
	for (int i = 0; i < max_seats; ++i)
	{
		printf("[%d] %d ", i+1, chair[i]);
	}
	printf("\n");
}

void * student_task(void * student_id)
{
	int id = *(int*)student_id;
	printf("[stu] student %d is doing task\n",id);			
	while(1)
	{
		sleep(rand() % SLEEP_MAX + 1);
		sem_wait(&mutex);
		//pthread_mutex_lock(&mutex);
		if(count < max_seats)	
		{

			chair[next_seat] = id;
			count++;
			printf("[stu] student %d is waiting\n",id);
			print_chair();
			next_seat = (next_seat+1) % max_seats;
			sem_post(&mutex);
			//pthread_mutex_unlock(&mutex);
			sem_post(&sem_stu);
			sem_wait(&sem_ta);
		}
		else //no more chairs
		{
			sem_post(&mutex);
			//pthread_mutex_unlock(&mutex);
			printf("[stu] no more chairs. student %d is doing task\n",id);	
		}
	}				
}

void * ta_teaching()
{
	while(1)
	{
		while(count==0)
		{
			printf("[ta]TA is sleeping\n");
			sleep(1);
		}
		sem_wait(&sem_stu);	
		//sem_wait(&mutex);
		//pthread_mutex_lock(&mutex);
		printf("[ta] TA is teaching student %d    ",chair[next_teach]);	
		chair[next_teach]=0;
		count--;
		print_chair();
		next_teach = (next_teach + 1) % max_seats;
		sleep(rand() % SLEEP_MAX + 1);
		printf("[ta] teaching finish.\n");	
		//sem_post(&mutex);
		//pthread_mutex_unlock(&mutex);
		sem_post(&sem_ta);
	}	
}



int main(int argc, char **argv)
{
	if (argc!=3)
	{
		printf("Usage: ./a.out [Number of students] [No of waitng seats]\n");
		exit(1);
	}
	else
	{
		int student_num=atoi(argv[1]);
		max_seats=atoi(argv[2]);
		int student_ids[student_num];
		pthread_t students[student_num];
		pthread_t ta;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		memset(student_ids, 0, student_num);
		sem_init(&sem_stu,0,0);
		sem_init(&sem_ta,0,1);
		
		srand((unsigned)time(NULL));

		sem_init(&mutex,0,1);
		//pthread_mutex_init(&mutex,NULL);

		pthread_create(&ta, &attr,ta_teaching,NULL);

		for(int i=0; i<student_num; i++)
		{
			student_ids[i] = i+1;
			pthread_create(&students[i], &attr, student_task, (void*) &student_ids[i]);
		} 
		
		pthread_join(ta, NULL);
		
		for(int i=0; i<student_num;i++)
		{
			pthread_join(students[i],NULL);
		}	
	}
		
	
	return 0;
}



