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

//------------------------------------------------MACRO
//------------------------------------------------DEF
typedef struct huff_node {
        int frequency;
        char symbol;
        int valid;
        char* code; 
        struct huff_node *left;
        struct huff_node *right;
} huff_node;

typedef struct huff_list {
    huff_node* node;
    struct huff_list * next;
} huff_list;

typedef struct entry {
	int frequency;
	char symbol;
	char* code;
	struct entry* next;
} entry;

//static const...
static const char LEFT = '0';
static const char RIGHT = '1';

//------------------------------------------------GLOBALS
huff_list* head = NULL;
huff_node* root = NULL;

entry* dictionary_head = NULL;

int size_of_coded_msg;

char depth[2056]; //print_tree, pop_format_tree, push_format_tree
int di; //print_tree, pop_format_tree, push_format_tree

//------------------------------------------------PROTO
void usage(const char* argv);
void push_format_tree (char c);
void pop_format_tree(void);
void print_tree(huff_node* node);
char* load_file(const char* filename);
void count_symbol(char symbol);
void print_huff_list(void);
void bubble_sort_list(void);
void plant_huff_tree(void);
huff_list* pop_front(void);
void gen_huff_code(huff_node* tree, char* parent_code, int level, char side);
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

		//print_huff_list();
		bubble_sort_list();
		print_huff_list();
		printf("\n============================\n\n");
		while(head != NULL){
			//print_huff_list();
			plant_huff_tree();
		
		}

		print_tree(root);
		gen_huff_code(root, "-", 1, LEFT);

		printf("Loaded file size (bits): %lu\n", strlen(text)*8);
		printf("Size of mem to alloc for coded msg (bits): %d\n", size_of_coded_msg);


	}

	free(text);
	free(head);
	free(root);
	return 0;
}
//------------------------------------------------FUNCS
void usage(const char* file){
		printf("Simple Huffman tree generator\n");
		printf("Usage: %s file_to_encode \n", file);
		exit(0);
}

void push_format_tree (char c){
	depth[di++] = ' ';
	depth[di++] = c;
	depth[di++] = ' ';
	depth[di++] = ' ';
	depth[di] = 0;
}

void pop_format_tree(void){
	depth[di-=4] = 0;
}

void print_tree(huff_node* node){
	if((int)node->symbol == 10){
		printf("(10):%d\n", node->frequency);
	} else if(node->symbol == '*'){ 
		printf("(\033[22;31m%c:%d\033[0m)\n", node->symbol,node->frequency);
	}else {
		printf("%c:%d\n", node->symbol,node->frequency);
	}

    if(node->right){
            printf("%s ├───", depth);
            push_format_tree('|');
            print_tree(node->right);
            pop_format_tree();
    }

	if(node->left){
		printf("%s └───", depth);
		push_format_tree(' ');
		print_tree(node->left);
		pop_format_tree();
	}
}

char* load_file(const char* fn){
	char* data = NULL;
	FILE *f;
	size_t sz;

	f = fopen(fn, "rb");

	if(!f){
		puts("File does not exist");
		exit(1);
	}

	fseek(f, 0, SEEK_END);
	sz = ftell(f);
	fseek(f, 0, SEEK_SET);

	data = (char*) malloc(sz);
	if(data == NULL){
		fclose(f);
		puts("Can't malloc for file");
		exit(1);
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
	    current -> node = malloc(sizeof(huff_node));
	    current -> node -> symbol = symbol;
	    current -> node -> frequency = 1;
	    current -> node -> valid = 1;
	    current -> node -> code = NULL;
	    current -> node -> left = NULL;
	    current -> node -> right = NULL;
	    current -> next = NULL;  		
	    head = current;
	    //free(current);
    } else {
		//find symbol
    	huff_list* current = NULL;
    	current = head;
    	int found = 0;

    	while(current != NULL){
    		if(current -> node -> symbol == symbol){
    			//symbol exists
    			found = 1;
    			current -> node -> frequency = current -> node -> frequency + 1;
    			break;
    		}
    		current = current -> next;
    	}

		if(found == 0){
			//symbol doesnt exist
			huff_list* current = NULL;
		    current  = malloc(sizeof(huff_list));
		    current -> node = malloc(sizeof(huff_node));
		    current -> node -> symbol = symbol;
		    current -> node -> frequency = 1;
		    current -> node -> valid = 1;
		    current -> node -> code = NULL;
		    current -> node -> left = NULL;
		    current -> node -> right = NULL;
		    current -> next = NULL;  		
			current -> next = head;
			head = current;


			//free(new);
		}

	}
}

void print_huff_list(void){ //debug
	int i = 1;
	huff_list* current = NULL;
	current = head;
	while(current != NULL){
		if((int)current -> node -> symbol == 10){
			printf("%d:: (10), %d\n",i, current -> node -> frequency);
		} else {
			printf("%d:: %c, %d\n",i, current -> node -> symbol, current -> node -> frequency);
		}
		current = current -> next;
		i++;
	}
	//printf("Total: %d elements\n\n", i-1);
}


void bubble_sort_list(void){ //sort huff_list from smallest freq
	
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

			if(current -> node -> frequency > next -> node -> frequency){ //swap
				//printf("Bubble: curent: %c, next %c\n", current -> node -> symbol, next -> node -> symbol);
				tmp = NULL;
				if(previous != NULL){
					//hotswap ;)
					previous -> next = next;
				}

				tmp = current;
				current = next;
			
				next = tmp;
				next -> next = current -> next;
				current -> next = next;

				if(previous != NULL && previous -> next == head){ //head guard
					head = previous;
				}

				if(next == head) {
					head = current;
				}



				//printf("Swapped: %c - %c\n",current -> node -> symbol,current ->next-> node -> symbol);
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
	//empty list
	if(head == NULL){
		printf("No nodes to plant a TREE!\n");
	}

	//only one element on list
	if(head -> next == NULL){
		root = head -> node;
		head = NULL;
		//free(head);
	} else {
		//pop 2 elements from list
		huff_list* first = pop_front();
		huff_list* second = pop_front();
		
		// combine & create new node from first & second
		huff_list* parent = NULL;
	    parent  = malloc(sizeof(huff_list));
	    parent -> node = malloc(sizeof(huff_node));
	    parent -> node -> symbol = '*';
	    parent -> node -> frequency = first -> node -> frequency + second -> node -> frequency;
	    parent -> node -> valid = 0;
	    parent -> node -> code = NULL;
	    //maloc & memcopy
	    parent -> node -> left = malloc(sizeof(huff_node));;
	    parent -> node -> right = malloc(sizeof(huff_node));;

	    if(first -> node -> frequency > second -> node -> frequency){
	    	memcpy(parent -> node -> left, first -> node, sizeof(huff_node));
	    	memcpy(parent -> node -> right, second -> node, sizeof(huff_node));
	    } else {
	    	memcpy(parent -> node -> right, first -> node, sizeof(huff_node));
	    	memcpy(parent -> node -> left, second -> node, sizeof(huff_node));
	    }

	    // free unused huff_list*
	    //free(first);
	    //free(second);

		//push front new element

	    parent -> next = NULL;  		
		parent -> next = head;
		head = parent;

		//sort list
		//printf("\t push front Head -> node -> frequency: %d\n", head->node->frequency);
	    bubble_sort_list();
		//repeat until no elements on list
	} //end else

}

void gen_huff_code(huff_node* current, char* parent_code, int level, char side){

	if(current != NULL){
		current -> code = malloc(level * sizeof(char));
		
		if(current != root && current -> symbol != '*' && current-> valid == 1){	
			//create new dictionary entry, add it as head entry on list
			entry* tmp_dict_entry = NULL;
			tmp_dict_entry = malloc(sizeof(entry));
			tmp_dict_entry -> frequency = current -> frequency;
			tmp_dict_entry -> symbol = current -> symbol;
			tmp_dict_entry -> code = malloc(level * sizeof(char));
			sprintf(tmp_dict_entry->code,"%s%c",parent_code, side);
			tmp_dict_entry -> next = dictionary_head;
			dictionary_head = tmp_dict_entry;

			//enlarge output buffer
			size_of_coded_msg += level * tmp_dict_entry -> frequency; 
		} 
		
		//if(current -> symbol != '*' && current-> valid == 1){
			// if((int)current->symbol == 10){
			// 	printf("(10): %5d: %10s\n",current->frequency, current -> code);
			// } else{
			// 	printf("%4c: %5d: %10s\n", current->symbol, current->frequency, current -> code);
			// }
		//}

		if(current->left != NULL){
			gen_huff_code(current->left, current->code, level+1, LEFT);
		}

		if(current->right != NULL){
			gen_huff_code(current->right, current->code, level+1, RIGHT);
		}
	}

}

// void gen_huff_code(huff_node* current, char* parent_code, int level, char side){

// 	if(current != NULL){
// 		current -> code = malloc(level * sizeof(char));
		
// 		if(current != root){	
// 			sprintf(current->code,"%s%c",parent_code, side);
// 		} else {
// 			current -> code = "0";
// 		}
		
// 		if(current -> symbol != '*' && current-> valid == 1){
// 			if((int)current->symbol == 10){
// 				printf("(10): %5d: %10s\n",current->frequency, current -> code);
// 			} else{
// 				printf("%4c: %5d: %10s\n", current->symbol, current->frequency, current -> code);
// 			}
// 		}

// 		if(current->left != NULL){
// 			gen_huff_code(current->left, current->code, level+1, LEFT);
// 		}

// 		if(current->right != NULL){
// 			gen_huff_code(current->right, current->code, level+1, RIGHT);
// 		}
// 	}
