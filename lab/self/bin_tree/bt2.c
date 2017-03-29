#include <stdio.h>
#include <stdlib.h>

typedef enum color_type{
	Red, Black
} color_type;

struct node {
	int key_value;
	struct node *left;
	struct node *right;
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
void insert(int key, struct node **leaf){
	if (*leaf == NULL){
		*leaf = (struct node *) malloc(sizeof(struct node));
		(*leaf)->key_value = key;

		(*leaf)->left = NULL;
		(*leaf)->right = NULL;

	} else if(key < (*leaf)->key_value) {
//		printf("go to left node, %d\n", key);
		insert(key, &(*leaf)->left);

	} else if(key > (*leaf)->key_value){
//		printf("go to right node, %d\n", key);
		insert(key, &(*leaf)->right);
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
	printf("(%d)\n", tree->key_value);
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

	insert(12, &root);
	insert(4, &root);
	insert(15, &root);
	insert(5, &root);
	insert(3, &root);
	insert(14, &root);
	insert(16, &root);
	insert(-4, &root);
	insert(-10, &root);
	puts("insert end");
	print_tree(root);
	puts("print end");
	destroy_tree(root);

	return 0;
}
