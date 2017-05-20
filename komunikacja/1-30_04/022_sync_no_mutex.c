#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define BUF_SIZE 16

typedef struct Student
{
	char name[BUF_SIZE];
	char surname[BUF_SIZE];
	int grade;
} Student;

Student temp;

void* fun_write(void *arg)
{
	while(1) {
		for(int i = 0 ; i < 2 ; i++) {
			if(i % 2) {
				strcpy(temp.name, "Przemyslaw");
				strcpy(temp.surname, "Nowak");
				temp.grade = 5;
			} else {
				strcpy(temp.name, "Adam");
				strcpy(temp.surname, "Kazimierczak");
				temp.grade = 2;
			}
		}
	}
	return NULL;
}

void* fun_read(void* arg)
{
	Student local;

	while(1)
	{
		memcpy(&local, &temp, sizeof(Student));	
		printf("====================================\n");
		printf("%s\n", local.name);
		printf("%s\n", local.surname);
		printf("%d\n", local.grade);
	}
	return NULL;
}

int main() 
{
	pthread_t thread_write, thread_read;
	pthread_create(&thread_write, NULL, fun_write, NULL);
	pthread_create(&thread_read, NULL, fun_read, NULL);
	
	pthread_join(thread_write, NULL);
	pthread_join(thread_read, NULL);
	
	return 0;
}
