#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

//why pointer
void* thread_fun(void *arg)
{
	printf("thread arg 1 = %d\n", *(int*)(arg));
	*(int*)(arg) = 10;
	printf("thread arg 1 = %d\n", *(int*)(arg));
	return NULL;
}

int main() 
{
	pthread_t thread_id;
	int temp = 5;
	//starts new thread in the calling process
	pthread_create(&thread_id, NULL, thread_fun, &temp);
	//waits fo the specified thread to terminate
	pthread_join(thread_id, NULL);

	printf("main thread temp = %d\n", temp);	
	
	return 0;
}
