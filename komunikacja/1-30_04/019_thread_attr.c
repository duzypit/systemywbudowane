#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* thread_fun(void *arg)
{
	printf("thread fun\n");
	sleep(5);
	printf("thread fun - end\n");	
	//When a detached thread terminates, its resources are
    //automatically released back to the system without the need for
    //another thread to join with the terminated thread.
	return NULL;
}

int main() 
{
	//??co tu się dzieje??
	pthread_t thread_id;
	pthread_attr_t thread_attr;
	// function initializes the thread attributes object pointed to by attr with default attribute values. 
	pthread_attr_init (&thread_attr);
	//function sets the detach state attribute of the thread attributes object referred to by attr to the value specified in detachstate.
    // PTHREAD_CREATE_DETACHED - Threads that are created using attr will be created in a detached state.
    //PTHREAD_CREATE_JOINABLE - Threads that are created using attr will be created in a joinable state.
	pthread_attr_setdetachstate (&thread_attr, PTHREAD_CREATE_JOINABLE);
	//starts new thread in calling process
	pthread_create(&thread_id, &thread_attr, &thread_fun, NULL);
	//When a thread attributes object is no longer required, it should be destroyed using the pthread_attr_destroy() function. Destroying a thread attributes object has no effect on threads that were created using that object. 
	pthread_attr_destroy(&thread_attr);

	//i tak nie bedziemy czekac
	pthread_join(thread_id, NULL);
	printf("Main thread - nie blokujemy\n");
	sleep(10);

	printf("Main thread - konczymy\n");

	return 0;
}