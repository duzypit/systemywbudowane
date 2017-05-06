#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
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

typedef struct List{
    int value;
    struct List * next;
} List;

void push_back(List** t);
int pop_front(List** h);
void show_flat(List* h);

int main(void){
    srand(time(NULL));
    
    List* head = NULL;
    int i;
    for(i = 0; i < 10; i++){
      push_back(&head);
    }

    show_flat(head);
    
    printf("\nzdejmuje val: %d\n\n", pop_front(&head));

    show_flat(head);
    
    return 0;
}

void push_back(List** node){
    List* current = malloc(sizeof(List));
    current -> value = rand()%1000;
    current -> next = NULL;

    if(*node == NULL){
        *node = current;
    } else {
        List* tmp = *node;
        while(tmp -> next != NULL){
            tmp = tmp -> next; 
        }
        tmp -> next = current;
    }
}

int pop_front(List** h){
    List* tmp = *h;

    if(tmp == NULL){
        return(-1);
    } else {
        *h = tmp -> next;
        int val = tmp -> value;
        free(tmp);
        return val;
    }
}

void show_flat(List* current){
    int i = 0;
    while(current != NULL){
        i++;
        printf("Element: %d, val: %d \n", i, current -> value);
        current = current -> next;
    }
    printf("\n");
}