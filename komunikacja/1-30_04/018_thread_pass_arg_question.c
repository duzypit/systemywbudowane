#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define THREADS_NUM 10

int i;

void* thread_fun(void *arg)
{
	printf("thread begin arg = %d\n", *(int*)(arg));
	return NULL;
}

int main() 
{
	pthread_t thread_id[THREADS_NUM];

	for(i = 0 ; i < THREADS_NUM ; i++)
		//starts new therad in calling process
		pthread_create(&thread_id[i], NULL, &thread_fun, &i);

	for(i = 0 ; i < THREADS_NUM ; i++)
		//waits for thread specified by id to terminate
		pthread_join(thread_id[i], NULL);
	
	printf("Main thread end\n");	
	return 0;
}
