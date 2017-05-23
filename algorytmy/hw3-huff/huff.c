/*
 * @author Tomasz Piątek
 * @brief Huffman encoding algorithm
 */

/*
	load input
	gen dictionary
	save to file
	encode input 
	print encoded data
 */
#include <stdio.h>
#include <stdlib.h> //exit
#include <string.h> //strlen

//------------------------------------------------MACROS
#define PEXIT(str) {perror(str);exit(1);}

//------------------------------------------------DEF
typedef struct huff_list{
	char symbol;
    int amount;
    struct huff_list * next;
} huff_list;

typedef struct huff_node {
        int frequency;
        char symbol;
        int valid;
        struct huff_node *left;
        struct huff_node *right;
} huff_node;


//------------------------------------------------GLOBALS
huff_list* head = NULL;
huff_node* root = NULL;
//------------------------------------------------PROTO
void usage(const char* argv);
char* load_file(const char* filename);
void count_symbol(char symbol);
void print_huff_list(void);
void bubble_sort_list(void);
void plant_huff_tree(void);
huff_list* pop_front(void);
//------------------------------------------------MAIN
int main(int argc, char **argv){
	
	char* text = NULL; // data to process
	int i = 0; //for var iterator

	if (argc < 2){
		usage(argv[0]);
	} else {
		text = load_file(argv[1]);
		for(i = 0; i < (int)strlen(text); i++){
			count_symbol(text[i]);
		}

		print_huff_list();
		bubble_sort_list();
		print_huff_list();

	}

	free(text);
	return 0;
}
//------------------------------------------------FUNCS
void usage(const char* file){
		printf("Simple Huffman tree generator\n");
		printf("Usage: %s file_to_encode \n", file);
		exit(0);
}

char* load_file(const char* fn){
	char* data = NULL;
	FILE *f;
	size_t sz;

	f = fopen(fn, "rb");
	if(!f){
		PEXIT("File does not exist");
	}

	fseek(f, 0, SEEK_END);
	sz = ftell(f);
	fseek(f, 0, SEEK_SET);

	data = (char*) malloc(sz);
	if(data == NULL){
		fclose(f);
		PEXIT("Can't malloc for file");
	}

	fread(data, 1, sz, f);
	fclose(f);
	data[sz] = '\0';
	return(data);
}

void count_symbol(char symbol){ // increment counter for symbol on list, if symbol doesnt exist add as a head
	//head == NULL
	if(head == NULL){
		huff_list* current = NULL;
	    current  = malloc(sizeof(huff_list));
	    current -> symbol = symbol;
	    current -> amount = 1;
	    current -> next = NULL;  		
	    head = current;
	    //free(current);
    } else {
		//find symbol
    	huff_list* current = NULL;
    	current = head;
    	int found = 0;

    	while(current != NULL){
    		if(current -> symbol == symbol){
    			//symbol exists
    			found = 1;
    			current -> amount = current -> amount + 1;
    			break;
    		}
    		current = current -> next;
    	}

		if(found == 0){
			//symbol doesnt exist
			huff_list* new = NULL;
			//next = head;
			new = malloc(sizeof(huff_list));
			new -> symbol = symbol;
			new -> amount = 1;
			new -> next = head;
			head = new;
			//free(new);
		}

	}
}

void print_huff_list(void){ //debug
	int i = 1;
	huff_list* current = NULL;
	current = head;
	while(current != NULL){
		printf("%d:: %c, %d\n",i, current -> symbol, current->amount);
		current = current -> next;
		i++;
	}
	printf("Total: %d elements\n", i);
}


void bubble_sort_list(void){ //sort huff_list from smallest amount
	
	huff_list* previous = NULL;
	huff_list* current = NULL;
	huff_list* next = NULL;
	huff_list* tmp = NULL;
	
	
	int swap_count = 1;
	

	while(swap_count > 0){
		previous = NULL;
		current = head;
		next = head -> next;		
		swap_count = 0;
		while(next != NULL){

			if(current -> amount > next -> amount){ //swap
				printf("Curent: %c, next %c\n", current->symbol, next->symbol);
				tmp = NULL;
				previous -> next = next;
				tmp = current;
				current = next;
				
				next = tmp;
				next -> next = current -> next;
				current -> next = next;

				if(previous -> next == head){ //head guard
					head = previous;
				}

				printf("Swapped: %c (%d) - %c (%d)\n",current->symbol,(int)current->symbol,current->next->symbol, (int)current->next->symbol);
				swap_count++;
			}
			previous = current;
			current = current -> next;
			next = current-> next;
		}

	}
}

huff_list* pop_front(void){
	if(head != NULL){
		huff_list* result = head;
		head = result->next;
		return(result);
	} else {
		return NULL;
	}
}

void plant_huff_tree(void){
	//if root = null
	if(root == NULL){
		huff_list* first = pop_front();
		huff_list* second = pop_front();

		huff_node* tree_head = malloc(sizeof(huff_node));
        tree_head -> frequency = first -> amount + second -> amount;
        tree_head -> symbol = '-';
        tree_head -> valid = 0;
        tree_head -> left = NULL;
        tree_head -> right = NULL;

		huff_node* left = malloc(sizeof(huff_node));
        left -> frequency = first -> amount;
        left -> symbol = first -> symbol;
        left -> valid = 1;
        left -> left = NULL;
        left -> right = NULL;

		huff_node* right = malloc(sizeof(huff_node));
        right -> frequency = first -> amount;
        right -> symbol = first -> symbol;
        right -> valid = 1;
        right -> left = NULL;
        right -> right = NULL;

        root = tree_head;
        if(left -> frequency < right -> frequency){

        	root -> left = left;
        	root -> right = right;
        } else {
        	root -> left = right;
        	root -> right = left;
        }

	} else { //add first element of list to tree;
		huff_list* tmp = pop_front();

		huff_node* new_root = malloc(sizeof(huff_node));
        new_root -> frequency = (tmp -> amount + root -> frequency);
        new_root -> symbol = '-';
        new_root -> valid = 0;
        new_root -> left = NULL;
        new_root -> right = NULL;		

        huff_node* new_node = malloc(sizeof(huff_node));
        new_node -> frequency = tmp -> amount;
        new_node -> symbol = tmp -> symbol;
        new_node -> valid = 1;
        new_node -> left = NULL;
        new_node -> right = NULL;

        if(new_node -> frequency < root -> frequency){

        	new_root -> left = new_node;
        	new_root -> right = root;
        } else {
        	new_root -> left = root;
        	new_root -> right = new_node;
        }

        root = new_root;
	} //end else

}