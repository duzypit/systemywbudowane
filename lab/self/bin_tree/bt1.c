#inculude <stdio.h>

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
		pritnf("I'm gonna be free: %d\n", leaf->key_value);
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
		(*leaf)->left = NULL:
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
			return serch(key, leaf->right);
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


void print_inorder(struct node *tree){
	if(tree){
		print_inorder(tree->left);
		printf("%d\n", tree->key_value);
		print_inorder(tree_right);
	}

}

int main (void){
	struct node *root = NULL;
	struct node *tmp;

	insert(&root, 9);
	insert(&root, 4);
	insert(&root, 15)
//

	return 0;
}
