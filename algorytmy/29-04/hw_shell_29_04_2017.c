#include <stdio.h>

void print_tab(int* t, int n){
	//printf("first elem of t is: %i", t[0]);
	int i;
	for(i = 0; i < n; i++){
		printf("%d : %d\n", i, t[i]);
	}
	puts("\n");
}

void shell_sort(int* t, int n){
	int gap, temp, i, j;
	for(gap = n/2; gap > 0; gap /= 2){
		for(i = gap; i < n; i++){
			temp = t[i];
			for(j = i; j >= gap && t[j-gap] > temp; j -= gap){
				t[j] = t[j-gap];
			}
			t[j] = temp;
		}
	}
}

int main(void){
	int tab[] = {23,9,2,7,3,4,5,8,1};
	int n = sizeof(tab) / sizeof(tab[0]);
	
	puts("* init");
	print_tab(tab, n);

	shell_sort(tab, n);
	
	puts("* shell");
	print_tab(tab, n);

	return 0;
}