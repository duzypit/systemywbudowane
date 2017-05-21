#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define ELEMS_NUM 10

int buff[ELEMS_NUM];
int buff_index;
pthread_mutex_t buff_mutex;
sem_t buff_sem_full;

int push_front(int val)
{
	if(buff_index < ELEMS_NUM) {
		buff[buff_index++] = val;
		return 0;
	} else 
		return -1;
}

int pop_front()
{
	if(buff_index > 0)
		return buff[--buff_index];
	else
		return -1;
}

void* producer(void* arg)
{
	int result;
	while(1) {
		for(int i = 0 ; i < 20 ; i++) {
			pthread_mutex_lock(&buff_mutex);
				result = push_front(i);
				printf("producer : %d | result = %d\n", i, result); 
			pthread_mutex_unlock(&buff_mutex);
		
			if(result != -1)
				sem_post(&buff_sem_full);
		}
		sleep(10);
	}
}

void* consumer(void* arg)
{
	int temp;
	while(1) {
		printf("consumer - sem_wait\n");
		//decrement (locks) the semaphore
		//int sem_wait(sem_t *sem);
		sem_wait(&buff_sem_full);
		printf("consumer - po sem_wait\n");

		pthread_mutex_lock(&buff_mutex);
			temp = pop_front();
			printf("consumer : %d\n", temp);
		pthread_mutex_unlock(&buff_mutex);		
	}
}

int main() 
{
	pthread_t th1, th2;
	pthread_mutex_init(&buff_mutex, NULL);
	//Initialize an unnamed semaphore
	//int sem_init(sem_t *sem, int pshared, unsigned int value);
	//sem_t *sem - init unnamed semaphore at the addres pointed
	//int pshared semaphore is shared between the threads of a process or between processes
	//value - init val
	sem_init(&buff_sem_full, 0, 0);
	
	pthread_create(&th1, NULL, producer, NULL);
	pthread_create(&th2, NULL, consumer, NULL);

	pthread_join(th1, NULL);
	pthread_join(th2, NULL);

	return 0;
}
