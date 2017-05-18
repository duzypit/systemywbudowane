#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define THREADS_NUM 3

typedef struct List {
	int value;
	struct List* next;
} List;

List* head = NULL;
List* tail = NULL;
int elem_num;

pthread_mutex_t my_mutex;
sem_t my_sem;


void push_back(int value)
{
	List* node = malloc(sizeof(List));
	node->value = value;
	node->next = NULL;

	if(head == NULL) {
		head = node;
		tail = node;
	}
	else {
		if(head == tail) {
			tail = node;
			head->next = node;
		} else {
			tail->next = node;
			tail = node;
		}
	}
	elem_num++;
}

int pop_front()
{
	int ret = -1;

	if(head != NULL) {
		if(head == tail) {
			ret = head->value;
			free(head);
			head = NULL;
			tail = NULL;
		}
		else {
			List* old_head = head;
			ret = head->value;

			head = head->next;
			free(old_head);
		}
		elem_num--;
	}

	return ret;
}

int is_empty()
{
	if(head == NULL)
		return 1;
	else
		return 0;
}

int get_elem_num()
{
	return elem_num;
}

void show_all() 
{
	List* temp = head;
	while(temp != NULL) {
		printf("value = %d\n", temp->value);
		temp = temp->next;
	}
}

void* thread_write(void *arg)
{
	while(1) {
		for(int i = 0; i < 10 ; i++) {
			pthread_mutex_lock(&my_mutex);
				push_back(i);
			pthread_mutex_unlock(&my_mutex);
			sem_post(&my_sem);
		}
		sleep(10);
	}
	return NULL;
}

void* thread_read(void *arg)
{
	int sem_val;
	while(1) {
		sem_wait(&my_sem);
		pthread_mutex_lock(&my_mutex);	
			printf("thread_read = %li | value = %d | elem_num = %d\n", pthread_self(), pop_front(), elem_num);
		pthread_mutex_unlock(&my_mutex);
	}
}

int main()
{
	pthread_t thread_pool[THREADS_NUM];
	pthread_mutex_init(&my_mutex, NULL);
	sem_init(&my_sem, 0, 0);

	for(int i = 0 ; i < THREADS_NUM ; i++) 
	{
		pthread_create(&thread_pool[i], 
						NULL, 
						(i == 0) ? &thread_write : &thread_read, 
						NULL);

	}

	for(int i = 0 ; i < THREADS_NUM ; i++) {
		pthread_join(thread_pool[i], NULL);
	}

	return 0;
}
