/*
 * @author Tomasz Piątek
 * @brief HW 30.04 - linked list with producer and 3 consumers
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //sleep
#include <time.h> //time
#include <pthread.h>
#include <semaphore.h>

/*
Treść zadania

1. Zaimplementuj listę korzystając z dynamicznej alokacji pamięci.

2. Węzeł listy ma być zdefiniowany jako:

typedef struct List{
    int value;
    struct * List next;
}

3. zaimplementuj metody dostępu do listy:

    void push_back();
    int pop_front();

- zwracana wartość to wartość pola value z węzła listy
- jeżeli lista jest pusta, zwracana wartosć wynosi -1

4. Stwórz pulę N-wątków (N >= 3) z czego:
    0-wątek -> dodaje losowe dane do listy
    <1-N) -> wątki ściągają (pop_front) dane z listy

5. Zidentyfikuj stacje krytyczne w programie i odpowiednio je zabezpiecz

6. Jeżeli lista jest pusta, wówczas czytające wątki mają być uśpione.

*/

//------------------------------------------------TYPEDEFS
typedef struct List{
    int value;
    struct List * next;
} List;

//------------------------------------------------GLOBALS
List * head = NULL;
List * tail = NULL;
pthread_mutex_t my_mutex;
sem_t buff_sem;

//------------------------------------------------PROTO
void push_back(void);
int pop_front(void);
void show_flat(void);

void * producer(void *args);
void * consumer_1(void *args);
void * consumer_2(void *args);
void * consumer_3(void *args);
void * show(void *args);

//------------------------------------------------MAIN
int main(void){
    srand(time(NULL));
        
    pthread_t thread_producer, thread_consumer_1, thread_consumer_2, thread_consumer_3;
    sem_init(&buff_sem, 0, 0);
    pthread_create(&thread_producer, NULL, producer, NULL);
    pthread_create(&thread_consumer_1, NULL, consumer_1, NULL);
    pthread_create(&thread_consumer_2, NULL, consumer_2, NULL);
    pthread_create(&thread_consumer_3, NULL, consumer_3, NULL);

    pthread_join(thread_producer, NULL);
    pthread_join(thread_consumer_1, NULL);
    pthread_join(thread_consumer_2, NULL);
    pthread_join(thread_consumer_3, NULL);
    
    
    //show_flat();
    
    //printf("\nRemove val: %d\n\n", pop_front());

    //show_flat();
    
    return 0;
}

//------------------------------------------------FUNCS
void push_back(void){

    List * current = NULL;
    current  = malloc(sizeof(List));
    current -> value = rand()%1000;
    current -> next = NULL;    
         
    
    if(head == NULL){
        head = current;
        tail = current;
    } else {
        List* tmp = tail;
        tmp -> next = current;
        tail = current;
    }
}

int pop_front(void){

    int val = 0;

    if(head == NULL){
        val = -1;
    } else if(head == tail) {
        val = head -> value;
        head = NULL;
        tail = NULL;
    } else {
        List * tmp = head;
        head = tmp -> next;
        val = tmp -> value;
        free(tmp);
    }

    return val;
}

void show_flat(void){
    List * current = head;
    int i = 0;
    while(current != NULL){
        i++;
        printf("Element: %d, val: %d \n", i, current -> value);
        current = current -> next;
    }
    printf("\n");
}

void * producer(void *args){

    while(1){
        int i = 0;
        for(i = 0; i < 30; i++){
            pthread_mutex_lock(&my_mutex);
            push_back();
            printf("  Producer push_back\n");
            pthread_mutex_unlock(&my_mutex);
            sem_post(&buff_sem);
        }
        sleep(5);
    }

    return NULL;
}

void * consumer_1(void *args){
    int result;
    while(1){
        printf("* Consumer_1 sem_wait\n");
        sem_wait(&buff_sem);
        pthread_mutex_lock(&my_mutex);
        result = pop_front();
        printf("* Consumer_1 pop_front: %d\n", result);
        pthread_mutex_unlock(&my_mutex);
    }

    return NULL;
}


void * consumer_2(void *args){
    int result;
    while(1){
        printf("* * Consumer_2 sem_wait\n");
        sem_wait(&buff_sem);
        pthread_mutex_lock(&my_mutex);
        result = pop_front();
        printf("* * Consumer_2 pop_front: %d\n", result);
        pthread_mutex_unlock(&my_mutex);
    }

    return NULL;
}


void * consumer_3(void *args){
    int result;
    while(1){
        printf("* * * Consumer_3 sem_wait\n");
        sem_wait(&buff_sem);
        pthread_mutex_lock(&my_mutex);
        result = pop_front();
        printf("* * * Consumer_3 pop_front: %d\n", result);
        pthread_mutex_unlock(&my_mutex);
    }

    return NULL;
}

/*func for debug*/
void * show(void *args){
    while(1){
        pthread_mutex_lock(&my_mutex);
        show_flat();
        pthread_mutex_unlock(&my_mutex);
        sleep(5);
    }

    return NULL;
}