/*
 * @author Tomasz Piątek
 * @brief HW linked list with producer and 3 consumers - cpp version
 */

#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>

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

std::mutex mtx;
std::condition_variable cv;

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
    List() : mt(rd()), dist(1, 128) {
        
        head = nullptr;
        tail = nullptr;
        node_quantity = 0;
    }

    int pop_front() {
        int ret_val = 0; //head == nullptr;

        if(head == nullptr){
            ret_val = -1;
        } else if(head == tail){
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

        node_quantity -= 1;
        return(ret_val);
    }

    void push_back() {
        Node* current = new Node;
        current -> add_value((dist(mt)));
        current -> set_next(nullptr);

        if(head == nullptr){
            head = current;
            tail = current;
        } else {
            Node* tmp = tail;
            tmp -> set_next(current);
            tail = current;
        }

        node_quantity += 1;
    }

    void print() {
        Node* current = head;
        int i = 0;
        std::cout << "[ ";
        while(current != nullptr){
            i++;
            std::cout << i << ":" << current -> get_value();
            if (current != tail)
                std::cout << ", ";
            current = current -> get_next();
        }

        std::cout<< " ]" << std::endl;
    }

    bool is_product_redy(){
        if(node_quantity > 0) {
            return true;
        } else {
            return false;
        }
    }

private:
    Node* head;
    Node* tail;
    int node_quantity;

    std::random_device rd;
    std::mt19937 mt;
    std::uniform_int_distribution<int> dist;
};

//------------------------------------------------GLOBALS


// //------------------------------------------------PROTO
void producer(List& l, int id){

    while(1){
        {
            std::lock_guard<std::mutex> lck(mtx);
            for(int i = 0; i < 6; i++){
                l.push_back();
                std::cout << "PRODUCER "<< id << ": push back" << std::endl;

            }
        }
        cv.notify_all();
        
        std::this_thread::sleep_for (std::chrono::seconds(id+1));       

    }
}


void consumer(List& l, int id) {
    int result;

    while(1){
        std::unique_lock<std::mutex> lck(mtx);
        cv.wait(lck);
        do{
        std::cout << "CONSUMER " << id << ": pop_front() -> ";
        result = l.pop_front();
        std::cout << "value: " << result << std::endl;
        } while (result != -1);

    }
}

//------------------------------------------------MAIN
int main(void){
    //https://stackoverflow.com/questions/2085511/wait-and-notify-in-c-c-shared-memory
    List my_list;   

    std::vector<std::thread> producers_vector;
    
    for(int i = 0; i < 2; i++){
        //std::thread p (producer, std::ref(my_list));
        producers_vector.push_back(std::thread(producer, std::ref(my_list), i));

    }

    std::vector<std::thread> consumers_vector;
    for(int i = 0; i < 2; i++){
        consumers_vector.push_back(std::thread(consumer, std::ref(my_list), i));
    }


    for(std::thread& th : producers_vector){
        th.join();
    }

    for(std::thread& th : consumers_vector){
        th.join();
    }
    return 0;
}

