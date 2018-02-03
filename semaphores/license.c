#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

struct data
{
    int useridno;
};

sem_t license;

void * user_init(void * parameter)
{
    struct data * info = parameter;
    int userid= info->useridno;
    userid++;
    int usage=1;
    while(1)
    {   
        printf("User %d waiting for license\n", userid);
        sem_wait(&license);
        printf("                                    User %d license acquired for %d times\n", userid, usage);
        usage++;
        sleep(3);
        //printf("    User %d closing application...\n", userid);
        sem_post(&license);
        printf("                                                                                User %d released license\n", userid);
        sleep(1);
    }
}

int main(int argc, char const *argv[])
{
    if(argc!=3)
    {
        printf("Usage: ./a.out [number of users] [number of licences]\n");
        exit(1);
    }
    else
    {
        int users,licenses;
        users=atoi(argv[1]);
        licenses=atoi(argv[2]);
        sem_init(&license, 0, licenses);
        pthread_t user[users];
        pthread_attr_t attr;
        pthread_attr_init (&attr);
        for (int i = 0; i < users; ++i)
        {
            struct data * info = (struct data *)malloc(sizeof(struct data));
            info->useridno=i;
            pthread_create(&user[i], &attr, user_init, info);
        }
        for (int i = 0; i < users; ++i)
        {
            pthread_join(user[i], NULL);
        }
    }
    sem_destroy(&license);
    return 0;
}