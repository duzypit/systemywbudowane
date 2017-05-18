#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define THREADS_NUM 10
int temp;

void* thread_fun(void *arg)
{
	int local = temp++;
	printf("New thread id = %d | ends within %d\n", local, 10 + local*2);
	sleep(10 + local*2);
	printf("New thread id end = %d\n", local);

	return NULL;
}

int main() 
{
	pthread_t thread_id[THREADS_NUM];
		
	for(int i = 0 ; i < THREADS_NUM ; i++)
		//pthread_create - starts new thread in calling process
		pthread_create(&thread_id[i], NULL, &thread_fun, NULL);

	for(int i = 0 ; i < THREADS_NUM ; i++)
		//pthread_join(id, retval) function waits for the thread specified by id to terminate
		pthread_join(thread_id[i], NULL);
	
	printf("Main thread end\n");	
	return 0;
}
