/*
 * @author Tomasz Piątek
 * @brief HW linked list with producer and 3 consumers - cpp version
 */

#include <iostream>
#include <random>

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


struct Node {
public:

    Node() {
        next = nullptr;
        value = 0;
    }

    void set_next(Node* const ptr){
        next = ptr;
    }

    Node* get_next(){
        return(next);
    }

    void add_value(int v){
        value = v;
    }

    int get_value(){
        return(value);
    }

private:
    Node* next;
    int value;
};

class List {
public:
    List() : mt(rd()), dist(1.0, 100.0) {
        
        head = nullptr;
        tail = nullptr;
    }

    int pop_front() {
        int ret_val = -1; //head == nullptr;

        if(head == tail){
            ret_val = head -> get_value();
            delete head;
            head = nullptr;
            tail = nullptr;
        } else {
            Node* tmp = head;
            head = tmp -> get_next();
            ret_val = tmp ->get_value();
            delete tmp;
        }

        return(ret_val);
    }

    void push_back() {
        Node* current = new Node;
        current -> add_value(static_cast<int>(dist(mt)));
        current -> set_next(nullptr);

        if(head == nullptr){
            head = current;
            tail = current;
        } else {
            Node* tmp = tail;
            tmp -> set_next(current);
            tail = current;
        }
    }

    void print_list() {
        List* current = head;

    }

private:
    Node* head;
    Node* tail;
    int node_quantity;

    std::random_device rd;
    std::mt19937 mt;
    std::uniform_real_distribution<double> dist;
};

//------------------------------------------------GLOBALS
// pthread_mutex_t my_mutex;
// sem_t buff_sem;

// //------------------------------------------------PROTO
// void * producer(void *args);
// void * consumer_1(void *args);
// void * consumer_2(void *args);
// void * consumer_3(void *args);
// void * show(void *args);

//------------------------------------------------MAIN
int main(void){
    srand(time(NULL));
        

    
    return 0;
}

