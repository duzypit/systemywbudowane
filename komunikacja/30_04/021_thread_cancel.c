#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* thread_fun(void *arg)
{
	printf("thread fun\n");
	sleep(30);
	printf("thread fun - end\n");	
	return NULL;
}

int main() 
{
	//??o co tu chodzi??
	pthread_t thread_id;
	pthread_attr_t thread_attr;

	pthread_attr_init (&thread_attr);
	pthread_attr_setdetachstate (&thread_attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&thread_id, &thread_attr, &thread_fun, NULL);
	pthread_attr_destroy(&thread_attr);

	printf("Main thread - nie blokujemy\n");
	sleep(20);
	pthread_cancel(thread_id);
	sleep(10);
	printf("Main thread - konczymy\n");

	return 0;
}
