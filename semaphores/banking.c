/*Simulate a Banking Scenario using semaphores for the following description:

Bank shall maintain an overall balance and there shall be three counters supported in the bank for credit or debit 
operations by customers. 

Number of customers accessing counters should be dynamic.  A withdrawal or credit transaction by a customer
 thread would update both his local account balance and a global overall bank balance. 

Synchronize the balance statistic (both local and global ) to allow across account (differing account 
numbers / customers) and within account transactions. (Two different account withdrawals should not violate
the overall balance and the order of credit / debit operations should be synchronised in the case of within
 account transactions.)

 Differentiate multiple transactions by the same customer with a transaction id. 

 Also support a shared token generator for use by the counters which shall be mapped on to transaction ids/customer
  threads for performing the transaction. 

 Adopt standard banking convention such as a minimum balance for each customer and an 
 minimum overall bank balance =  minimum balance of all customers.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

# define CREDIT 0
# define DEBIT 1

# define DEPOSIT 10
# define WITHDRAW 11
# define ANTHR_ACC 12
//random genertation
# define BALANCE 101
# define TRANS_TYPE 102
# define AMOUNT_GEN 103
# define ACCOUNT_NUM 104

float BANK_BALANCE=0.0;
float MIN_BANK_BALANCE=0.0;
float MIN_BALANCE=2000.0;
int CUST_COUNT=0;
int COUNTER_COUNT=3;
int MAX_TRANSACTION_ID=0;
int MAX_TOKEN=0;
int next_counter=0;
int count=0;
int * counter_customer;



struct account
{
	float balance;
	int accountno;
}**details;

struct form
{
	int accountno;
	int counter_num;
	int type;
	float amount;
	int anthraccno;
	
}**customer_forms;

sem_t * sem_counter;
sem_t mutex, counter_mutex;

int random_gen(int type)
{
	if(type == BALANCE)
		return(((rand()%102200)/23)+MIN_BALANCE);
	else if(type == TRANS_TYPE)
		return((rand()%3)+10);
	else if(type == ACCOUNT_NUM)
		return((rand()%CUST_COUNT)+1);
	else if(type == AMOUNT_GEN)
		return(((rand()%100000)+1000)/23);
	return(0);
}

void * customer_thread(void * parameter)
{
	struct account * info = parameter;
	printf("%f %d\n", info->balance, info->accountno);
	while(1)
	{
		sem_wait(&counter_mutex);
		if(count<COUNTER_COUNT)
		{
			
			customer_forms[info->accountno-1] = (struct form *)malloc(sizeof(struct form));
			counter_customer[next_counter] = info->accountno-1;
			customer_forms[info->accountno-1]->accountno = info->accountno;
			customer_forms[info->accountno-1]->counter_num = next_counter;
			customer_forms[info->accountno-1]->type = random_gen(TRANS_TYPE);
			if(customer_forms[info->accountno-1]->type == ANTHR_ACC)
			{
				customer_forms[info->accountno-1]->anthraccno = random_gen(ACCOUNT_NUM);
			}
			else
			{
				customer_forms[info->accountno-1]->anthraccno = 0;
			}
			customer_forms[info->accountno-1]->amount = random_gen(AMOUNT_GEN);
			next_counter = (next_counter+1)%COUNTER_COUNT;
			count++;
			//printf("count - %d\n", count);
			sem_post(&counter_mutex);
			sem_wait(&sem_counter[customer_forms[info->accountno-1]->counter_num]);
		}
		else
		{
			sem_post(&counter_mutex);
			//printf("count - %d\n", count);
		}
		sleep(2);
	}
}


void * counter_thread(void * parameter)
{
	int counter_number = *(int *)parameter;
	//printf("counter number - %d\n", counter_number);
	while(1)
	{
		if(counter_customer[counter_number-1])
		{

			int token = ++MAX_TOKEN;
			int transactionid = ++MAX_TRANSACTION_ID;
			int customer_id = counter_customer[counter_number-1];
			printf("[%d] counter %d taking customer %d\n",counter_number, counter_number, customer_id+1);
			sem_wait(&mutex);
			if(customer_forms[customer_id]->type == WITHDRAW)
			{
				
				if(details[customer_id]->balance - customer_forms[customer_id]->amount >= MIN_BALANCE )
				{
					BANK_BALANCE = BANK_BALANCE + customer_forms[customer_id]->amount;
					details[customer_id]->balance = details[customer_id]->balance - customer_forms[customer_id]->amount;
					printf("[%d] token - %d transaction ID - %d transaction type - WITHDRAW customer ID - %d amount - %f accountno - %d\n", counter_number, token, transactionid, customer_id+1, customer_forms[customer_id]->amount, customer_forms[customer_id]->anthraccno);
				}
				else				
				{
					printf("[%d] token - %d transaction ID - %d transaction type - WITHDRAW customer ID - %d amount - %f accountno - %d\n", counter_number, token, transactionid, customer_id+1, customer_forms[customer_id]->amount, customer_forms[customer_id]->anthraccno);
					printf("[%d] Sufficient Balance is not present to be withdraw\n", counter_number);
				}
			}
			else if(customer_forms[customer_id]->type == DEPOSIT)
			{
				BANK_BALANCE = BANK_BALANCE + customer_forms[customer_id]->amount;
				details[customer_id]->balance = details[customer_id]->balance + customer_forms[customer_id]->amount;
				printf("[%d] token - %d transaction ID - %d transaction type - DEPOSIT customer ID - %d amount - %f accountno - %d\n", counter_number, token, transactionid, customer_id+1, customer_forms[customer_id]->amount, customer_forms[customer_id]->anthraccno);
			}
			else if(customer_forms[customer_id]->type == ANTHR_ACC)
			{
				printf("[%d] token - %d transaction ID - %d transaction type - ANOTHER ACCOUNT customer ID - %d amount - %f accountno - %d\n", counter_number, token, transactionid, customer_id+1, customer_forms[customer_id]->amount, customer_forms[customer_id]->anthraccno);
				if(details[customer_id]->balance - customer_forms[customer_id]->amount >= MIN_BALANCE && customer_forms[customer_id]->anthraccno <= CUST_COUNT)
				{
					details[customer_forms[customer_id]->anthraccno-1]->balance = details[customer_forms[customer_id]->anthraccno-1]->balance + customer_forms[customer_id]->amount;
					details[customer_id]->balance = details[customer_id]->balance - customer_forms[customer_id]->amount;
				}
				else if(!(customer_forms[customer_id]->anthraccno <= CUST_COUNT))
				{
					printf("[%d] Invalid Account Number\n", counter_number);
				}
				else				
				{
					printf("[%d] Sufficient Balance is not present to be Transferred\n", counter_number);
				}
				
			}
			sem_wait(&counter_mutex);
			counter_customer[counter_number-1]=0;
			count--;
			//printf("count - %d\n", count);
			sem_post(&counter_mutex);
			sem_post(&mutex);
			sem_post(&sem_counter[counter_number-1]);	
		}
		sleep(1);
	}
}



int main(int argc, char const *argv[])
{
	if(argc!=2)
	{
		printf("Usage: ./a.out [no of bank customers]\n");
		exit(1);
	}
	else
	{
		srand((unsigned)time(NULL));
		CUST_COUNT = atoi(argv[1]);
		MIN_BANK_BALANCE = CUST_COUNT * MIN_BALANCE;
		pthread_t customer[CUST_COUNT], counter[COUNTER_COUNT];
		pthread_attr_t attr;
		pthread_attr_init (&attr);
		int counter_num[COUNTER_COUNT];
		counter_customer = (int *)malloc(sizeof(int) * COUNTER_COUNT);
		memset(counter_customer, 0, COUNTER_COUNT);
		details = (struct account **)malloc(sizeof(struct account *) * CUST_COUNT);
		customer_forms = (struct form **)malloc(sizeof(struct form *) * CUST_COUNT);
		sem_counter = (sem_t *)malloc(sizeof(sem_t) * COUNTER_COUNT);
		for (int i = 0; i < COUNTER_COUNT; ++i)
		{
			sem_init(&sem_counter[i], 0, 0);
		}
		sem_init(&mutex, 0, 1);
		sem_init(&counter_mutex, 0, 1);
		for (int i = 0; i < COUNTER_COUNT; ++i)
		{
			counter_num[i]=i+1;
			pthread_create(&counter[i], &attr, counter_thread, (void *) &counter_num[i]);
		}
		for (int i = 0; i < CUST_COUNT; ++i)
		{
			details[i] = (struct account *)malloc(sizeof(struct account));
			details[i]->balance = random_gen(BALANCE);
			BANK_BALANCE = BANK_BALANCE + details[i]->balance;
			details[i]->accountno = i+1;
			pthread_create(&customer[i], &attr, customer_thread, details[i]);
		}
		for (int i = 0; i < CUST_COUNT; ++i)
		{
			pthread_join(customer[i], NULL);
		}
		for (int i = 0; i < COUNTER_COUNT; ++i)
		{
			pthread_join(counter[i], NULL);
		}
	}
	return 0;
}