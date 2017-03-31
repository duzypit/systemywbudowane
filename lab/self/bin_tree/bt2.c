#include <stdio.h>
#include <stdlib.h>
#define COLOR_RED "\x1b[31m"
#define COLOR_BLACK "\x1b[37m"   
#define COLOR_RESET "\x1b[0m"


typedef enum color_type{
	Red, Black
} color_type;

struct node {
	int key_value;
	color_type color;
	struct node *left;
	struct node *right;
	struct node *parent;
};

char depth[2056];
int di;

/*
	awesome recursion example
*/
void destroy_tree(struct node *leaf){
	if(leaf != NULL){
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		//show yourself!
		//printf("I'm gonna be free: %d\n", leaf->key_value);
		free(leaf);
	}
}

/*
	what if key is equal to existing in tree key_value?
*/
void insert(int key, struct node **leaf, struct node *parent){
	if (*leaf == NULL){
		*leaf = (struct node *) malloc(sizeof(struct node));
		(*leaf)->key_value = key;
		(*leaf)->parent = parent;
		(*leaf)->left = NULL;
		(*leaf)->right = NULL;
		if ((*leaf)->parent == NULL){
			(*leaf)->color = Black;
		} else {
			(*leaf)->color = Red;
		}

while((*leaf)-> parent != NULL && (*leaf)->parent->color == Red && (*leaf)->color != Black){


/*
case A, 
Parent of leaf is left child of grand parent of leaf

*/
	struct node *parent = (*leaf)->parent;
printf("parent %d\n",parent->key_value);
	struct node *grand_parent = parent->parent;
printf("grand_parent %d\n",grand_parent->key_value);
	if(parent == grand_parent->left){

		struct node *uncle = grand_parent->right;
/*
	case: 1
	the uncle of leaf is also red, only recoloring required
*/

		if(uncle->color == Red && uncle != NULL){
			//case 1 - change color
			grand_parent-> color = Red;
			parent->color = Black;
printf("uncle %d\n",uncle->key_value);
			uncle->color = Black;
			//*leaf = grand_parent;	

		} else {
/*
	case: 2
	leaf is right child of its parent, left rotation required
http://quiz.geeksforgeeks.org/c-program-red-black-tree-insertion/
*/
		}
	

	}
}


	} else if(key < (*leaf)->key_value) {
//		printf("go to left node, %d\n", key);
		insert(key, &(*leaf)->left, *leaf);

	} else if(key > (*leaf)->key_value){
//		printf("go to right node, %d\n", key);
		insert(key, &(*leaf)->right, *leaf);
	}
}

struct node *search(int key, struct node *leaf){
	if(leaf != NULL){
		if(key == leaf->key_value){
			return leaf;
		} else if(key < leaf->key_value) {
			return search(key, leaf->left);
		} else {
			return search(key, leaf->right);
		}
	} else {
		return NULL;
	}
}

void push (char c){
	depth[di++] = ' ';
	depth[di++] = c;
	depth[di++] = ' ';
	depth[di++] = ' ';
	depth[di] = 0;
}

void pop(){
	depth[di-=4] = 0;
}

void print_tree(struct node *tree){
	if(tree-> color == Red){
		printf("(\033[22;31m%d\033[0m)\n", tree->key_value);
	} else {
		printf("(\033[90m%d\033[0m)\n", tree->key_value);		
	}
        if(tree->right){
                printf("%s ├───", depth);
                push('|');
                print_tree(tree->right);
                pop();
        }




	if(tree->left){
		printf("%s └───", depth);
		push(' ');
		print_tree(tree->left);
		pop();
	}



}

int main (void){
	system("clear");

	struct node *root = NULL;

	insert(12, &root, NULL);
	print_tree(root);
puts("");
puts("================================================");
	insert(4, &root, NULL);
	print_tree(root);
puts("");
puts("================================================");
	insert(15, &root, NULL);
	print_tree(root);
puts("");
puts("================================================");
	insert(5, &root, NULL);
	print_tree(root);
puts("");
puts("================================================");
//	insert(3, &root, NULL);
//	print_tree(root);
//puts("");
//puts("================================================");
//	insert(14, &root, NULL);
	//print_tree(root);
//puts("");
//puts("================================================");
//	insert(16, &root, NULL);
//	print_tree(root);
//puts("");
//puts("================================================");
//	insert(-4, &root, NULL);
	//print_tree(root);
//puts("");
//puts("================================================");
//	insert(-10, &root, NULL);
//	puts("insert end");
//	print_tree(root);
//	puts("print end");
	destroy_tree(root);

	return 0;
}
