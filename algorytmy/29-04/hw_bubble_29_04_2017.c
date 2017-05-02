#include <stdio.h>

void print_tab(int* t, int n){
	//printf("first elem of t is: %i", t[0]);
	int i;
	for(i = 0; i < n; i++){
		printf("el: %d, val: %d\n",i, t[i]);
	}
}

void bubble(int* t, int n){
	int i, tmp;

	int change;
	do{
		change = 0;
		for(i = 0; i < n; i++){
			if(t[i] > t[i+1]){
				tmp = t[i];
				t[i] = t[i+1];
				t[i+1] = tmp;
				change = 1;
			}
		}
	} while (change == 1);
}

int main(void){
	int tab[] = {0,9,2,7,3,4,5,8,1};

	int n = sizeof(tab) / sizeof(tab[0]);
	puts("Init");
	print_tab(tab, n);

	bubble(tab, n);
	puts("----------bubbles");
	print_tab(tab, n);

	return 0;
}