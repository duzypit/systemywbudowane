#include <stdio.h>
#include <stdlib.h>

struct node {
	int key_value;
	struct node *left;
	struct node *right;
};

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
		//init the children to null
		(*leaf)->left = NULL;
		(*leaf)->right = NULL;
	} else if(key < (*leaf)->key_value) {
		insert(key, &(*leaf)->left);

	} else if(key > (*leaf)->key_value){
		insert(key, &(*leaf)->left);
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

void print_preorder(struct node *tree){
	if(tree){
		printf("%d\n",tree->key_value);
		print_preorder(tree->left);
		print_preorder(tree->right);
	}
}

void print_simple(int l, struct node *leaf){
	int i;

	if(leaf){
		print_simple(l+1, leaf->right);
		for(i=0; i<l; ++i){
			printf(" ");
		}
		printf("%d\n",leaf->key_value);
		print_simple(l+1, leaf->left);
	}
}

void padding(char ch, int n){
	int i;
	for(i = 0; i < n; i++){
		putchar(ch);
	}
}

void structure(int level, struct node *leaf){
	
	if (leaf == NULL){
		padding('\t', level);
		puts("-");
	} else {
		structure(level+1, leaf->right);
		padding('\t', level);
		printf("%d\n",leaf->key_value);
		structure(level+1, leaf->left);
	{
}

/*
void print_visual(char sp[2], char sn[2], struct node *tree){
	char s[2];
	if(tree != NULL){
		s = sp;
		if(sn == cr) {
			s[s.length() - 2] = ' ';
		}
		print_visual(s + cp, cr, tree->right);
		s = s.substr(0, sp.length()-2);
		printf("%d",tree->key_value);

		s = sp;
		if(sn == cl) {
			s[s.length()-2] = ' ';
		}
		print_visual(s+cp, cr, tree->left);
	}

}

char cr[2];
char cl[2];
char cp[2];
*/
int main (void){
/*
	cr = "  ";		 
	cl = "  ";
	cp = "  ";
	cr[0] = 218;
	cr[1] = 196;
	cl[0] = 192;
	cl[1] = 196;
	cp[0] = 179;
*/	
	struct node *root = NULL;

	insert(9, &root);
	insert(4, &root);
	insert(15, &root);
	insert(5, &root);
	insert(3, &root);
	//print_visual("", "", root);
	//print_simple(0,root);
	structure(0, root);
	destroy_tree(root);

	return 0;
}
