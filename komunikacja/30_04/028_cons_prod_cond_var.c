#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define ELEMS_NUM 10

int buff[ELEMS_NUM];
int buff_index;
pthread_mutex_t buff_mutex;
pthread_cond_t buff_cond_full, buff_cond_empty;

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

				if(buff_index == ELEMS_NUM)
					pthread_cond_wait(&buff_cond_empty, &buff_mutex);
				
				result = push_front(i);
				printf("producer : %d | result = %d\n", i, result);
				
				pthread_cond_signal(&buff_cond_full);
 
			pthread_mutex_unlock(&buff_mutex);

		}
		sleep(10);
	}
}

void* consumer(void* arg)
{
	int temp;
	while(1) {
		pthread_mutex_lock(&buff_mutex);

			if(buff_index == 0)
				pthread_cond_wait(&buff_cond_full, &buff_mutex);
			
			temp = pop_front();
			printf("consumer : %d\n", temp);

			pthread_cond_signal(&buff_cond_empty);
			
		pthread_mutex_unlock(&buff_mutex);
	
	}

}

int main() 
{
	pthread_t th1, th2;
	pthread_mutex_init(&buff_mutex, NULL);
	pthread_cond_init(&buff_cond_empty, NULL);
	pthread_cond_init(&buff_cond_full, NULL);
	
	pthread_create(&th1, NULL, producer, NULL);
	pthread_create(&th2, NULL, consumer, NULL);

	pthread_join(th1, NULL);
	pthread_join(th2, NULL);

	return 0;
}
