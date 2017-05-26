/*
 * @author Tomasz Piątek
 * @brief Huffman encoding algorithm
 */

/*
	load input
	gen tree
	gen dictionary
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

char* encoded_text = NULL;

int size_of_coded_msg;

char depth[2056]; //print_tree, pop_format_tree, push_format_tree
int di; //print_tree, pop_format_tree, push_format_tree

//------------------------------------------------PROTO
void usage(const char* argv);
void push_format_tree (char c); //utility
void pop_format_tree(void); //utility
void print_tree(huff_node* node); //utility
char* load_file(const char* filename);
void count_symbol(char symbol);
void print_huff_list(void); //utility
void bubble_sort_list(void);
void plant_huff_tree(void);
huff_node* pop_front(void);
void gen_huff_code(huff_node* tree, char* parent_code, int level, char side);
void print_dictionary_list(void); //utility
char* find_code(char symbol);
void destroy_dictionary_list(void);
void destroy_huff_tree(huff_node* tree);
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

		bubble_sort_list();
		// printf("Frequency list\n");
		// print_huff_list();
		printf("Huffman tree\n\n");
		while(head != NULL){
			plant_huff_tree();
		
		}

		print_tree(root);
		gen_huff_code(root, "-", 1, LEFT);
		printf("\nMath: \n");
		printf("Loaded file size (bits): %lu\n", strlen(text)*sizeof(char)*8);
		printf("Size of mem to alloc for coded msg (bits): %d\n", size_of_coded_msg);
		printf("\nList of codes:\n");
		print_dictionary_list();


		//output buffer generation
		encoded_text = calloc(size_of_coded_msg +1, sizeof(char));

		i = 0;
		while(text[i] != '\0'){
		 	char* code = NULL;
		 	code = find_code(text[i]);
		 	strcat(encoded_text,code);
		 	free(code);
		 	i++;
		}

		printf("\nText: %s", text);
		printf("Encoded text: %s\n",encoded_text);

	}
	//first destroy dictionary of codes stored in entry*
	destroy_dictionary_list(); // last created first destroyed

	//destroy tree & root
 	destroy_huff_tree(root);
	free(head);

	
	free(text); //load_file malloc
	free(encoded_text);
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

	data = (char*) malloc(sz+1);
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

				swap_count++;
			}

			previous = current;
			current = current -> next;
			next = current-> next;
		}

	}
}

huff_node* pop_front(void){
	if(head != NULL){
		huff_list* result = head;
		head = result->next;
		huff_node* node = NULL;
		node = result-> node;
		free(result);
		return(node);
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
		//one element on list means
		root = head -> node;
		free(head);
		head = NULL; //loop end condition
	} else {
		//pop 2 elements from list
		huff_node* first = NULL;
		first = pop_front();
		huff_node* second = NULL;
		second = pop_front();
		
		// combine & create new node from first & second
		huff_list* parent = NULL;
	    parent  = malloc(sizeof(huff_list));
	    parent -> node = malloc(sizeof(huff_node));
	    parent -> node -> symbol = '*';
	    parent -> node -> frequency = first -> frequency + second -> frequency;
	    parent -> node -> valid = 0;
	    parent -> node -> code = NULL;
	    parent -> node -> left = NULL;
	    parent -> node -> right = NULL;
	    
	    if(first -> frequency > second -> frequency){
	    	parent -> node -> left = first;
	    	parent -> node -> right = second;
	    } else {
	    	parent -> node -> left = second;
	    	parent -> node -> right = first;
	    }

		//push front new element
	    parent -> next = NULL;  		
		parent -> next = head;
		head = parent;

	    bubble_sort_list();
	} //end else

}

void gen_huff_code(huff_node* current, char* parent_code, int level, char side){
	//START WITH GLOBAL ROOT
	if(current != NULL){
		current -> code = malloc(level+1 * sizeof(char));

		if(current == root){
			sprintf(current->code,"%s","0");
		}	else {
			sprintf(current->code,"%s%c",parent_code, side); //its not root of tree
		}

		
		if(current != root && current -> symbol != '*' && current-> valid == 1){	
			//create new dictionary entry, add it as head entry on list
			entry* tmp_dict_entry = NULL;
			tmp_dict_entry = malloc(sizeof(entry));
			tmp_dict_entry -> frequency = current -> frequency;
			tmp_dict_entry -> symbol = current -> symbol;
			tmp_dict_entry -> code = malloc(level+1 * sizeof(char));
			sprintf(tmp_dict_entry->code,"%s%c",parent_code, side);
			tmp_dict_entry -> next = dictionary_head;
			dictionary_head = tmp_dict_entry;

			//enlarge output buffer
			size_of_coded_msg += level * tmp_dict_entry -> frequency; 
		} 
		
		if(current->left != NULL){
			gen_huff_code(current->left, current->code, level+1, LEFT);
		}

		if(current->right != NULL){
			gen_huff_code(current->right, current->code, level+1, RIGHT);
		}
	}

}

void print_dictionary_list(void){ //utility
	int i = 1;
	entry* current = NULL;
	current = dictionary_head;
	while(current != NULL){
		if((int)current -> symbol == 10){
			printf("%5d:: %5s, %5d, %s\n",i, "(10)", current -> frequency, current -> code);
		} else {
			printf("%5d:: %5c, %5d, %s\n",i, current -> symbol, current -> frequency, current -> code);
		}
		current = current -> next;
		i++;
	}
}

char* find_code(char symbol){
	entry* current = NULL;
	current = dictionary_head;

	while(current != NULL){
		if(current -> symbol == symbol){
			//return symbol code
			char* code = calloc(strlen(current->code)+1,sizeof(char));
			memcpy(code,current->code,strlen(current->code));
			return(code);
		}
		current = current->next;
	}

	return("-");
}

void destroy_dictionary_list(void){
	while(dictionary_head != NULL){
		entry* current = NULL;
		current = dictionary_head;
		dictionary_head = current->next;

		free(current->code);
		free(current);
	}

}

void destroy_huff_tree(huff_node* current){
	
	if(current != NULL){
		
		destroy_huff_tree(current->left);
		destroy_huff_tree(current->right);
		free(current->code);
		free(current);
		
	}
}