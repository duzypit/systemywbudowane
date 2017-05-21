#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

typedef struct Sum {
	int a;
	int b;
	int result;
} Sum;

void* fun_1(void* arg)
{
	Sum* p = (Sum*)arg;
	p->result = p->a + p->b;

	return NULL;
}

void* fun_2(void* arg)
{
	Sum* p = (Sum*)arg;
	p->result = p->a + p->b;
	return (p);
}

void* fun_3(void* arg)
{
	Sum* p = (Sum*)arg;
	p->result = p->a + p->b;
	//function terminates the calling thread and returns
    //a value via retval that (if the thread is joinable) is available to
    //another thread in the same process that calls pthread_join
	//void pthread_exit(void *retval);
	pthread_exit(p);
}

int main() 
{
	pthread_t thread1, thread2, thread3;
	Sum first  = {2,3,0};	
	Sum second = {2,3,0};
	Sum third  = {2,3,0};
	Sum* status;
	//int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
	pthread_create(&thread1, NULL, fun_1, &first);	
	pthread_create(&thread2, NULL, fun_2, &second);
	pthread_create(&thread3, NULL, fun_3, &third);

	//int pthread_join(pthread_t thread, void **retval);
	pthread_join(thread1, NULL);	
	pthread_join(thread2, (void**)&status);
	pthread_join(thread2, NULL);

	printf("thread 1 first  : %d + %d = %d\n", first.a, first.b, first.result);	
	printf("thread 2 second : %d + %d = %d\n", second.a, second.b, second.result);	
	printf("thread 2 status : %d + %d = %d\n", status->a, status->b, status->result);	
	printf("thread 3 third  : %d + %d = %d\n", third.a, third.b, third.result);	
	
return 0;
}
