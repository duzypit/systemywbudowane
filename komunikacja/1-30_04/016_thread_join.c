#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* thread_fun(void *arg)
{
	printf("New thread\n");
	sleep(5);
	printf("New thread ends\n");
	return NULL;
}

int main() 
{
	pthread_t thread_id;
	//create new thread in calling process	
	if(0 == pthread_create(&thread_id, NULL, &thread_fun, NULL)) 
	{
		printf("Main threads waits...\n");
		//waits for specified thread by id to terminate
		if(0 == pthread_join(thread_id, NULL)) 
			printf("Main threads ends\n");
		else
			printf("pthread_join error\n"); 
	}
	else 
	{
		printf("thread_create error\n");
	}	
	
	return 0;
}
