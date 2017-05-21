#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* thread_fun(void *arg)
{
	//pthreada_self - function returns the ID of calling thread
	printf("New thread id = %li\n", pthread_self());
	return NULL;
}

int main() 
{
	pthread_t thread_id;
	
	//pthread create - function starts new thread in calling process
	if(0 == pthread_create(&thread_id, NULL, &thread_fun, NULL)) {
		printf("Main thread id = %li | new thread = %li\n", pthread_self(), thread_id);
	} else {
		printf("Thread creation error\n");
	}
		
	sleep(1);
	
	return 0;
}
