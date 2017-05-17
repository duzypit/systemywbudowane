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

//------------------------------------------------INTERFACES
void push_back(void);
int pop_front(void);
void show_flat(void);

void * produce(void *args);
void consume_1();
void consume_2();
void consume_3();
void * show(void *args);

//------------------------------------------------MAIN
int main(void){
    srand(time(NULL));
        
    pthread_t thread_produce, /*thread_consume_1, thread_consume_2, thread_consume_3, */ thread_show;
    
    pthread_create(&thread_produce, NULL, produce, NULL);
    pthread_create(&thread_show, NULL, show, NULL);

    pthread_join(thread_produce, NULL);
    pthread_join(thread_show, NULL);
    
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

void * produce(void *args){

    while(1){
        int i = 0;
        for(i = 0; i < 10; i++){
            pthread_mutex_lock(&my_mutex);
            push_back();
            pthread_mutex_unlock(&my_mutex);
        }
        sleep(5);
    }

    return NULL;
}

void * show(void *args){
    while(1){
        pthread_mutex_lock(&my_mutex);
        show_flat();
        pthread_mutex_unlock(&my_mutex);
        sleep(7);
    }

    return NULL;
}