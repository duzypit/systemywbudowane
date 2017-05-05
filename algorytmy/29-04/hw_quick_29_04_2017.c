#include <stdio.h>

void print_flat(int* t, int n);
void quick_sort(int* t, int lo, int hi);
int part(int* t, int lo, int hi);

int main(void){
	int tab[] = {23,9,2,7,3,4,5,8,1};
	int n = sizeof(tab) / sizeof(tab[0]);
	
	print_flat(tab, n);
	quick_sort(tab, 0, n);
	puts("* quick");
	print_flat(tab, n);

	return 0;
}

void quick_sort(int* t, int lo, int hi){
	int pos;
	if(lo < hi) {
		pos = part(t, lo, hi); //dziele tablice na czesci, po elemencie rozdzielającym - pierwszy w tab
		quick_sort(t, lo, pos); //sortuje czesc tablicy od pirwszego e. do e. rozdzielajacego
		quick_sort(t, pos+1, hi); //sortuje czesc tablicy od e. rozdzielajacego do ostateniego e w tab
	}
}

int part(int* t, int lo, int hi){

	int pivot = t[lo]; //wybieram element rozdzielający, pierwszy w tablicy
	int i = lo;
	int j;
	int tmp;

	for( j = i; j < hi; j++ ){
		//jeśli element jest mniejszy niż e. rozdzielajacy zamieniam element i z j
		if(t[j] < pivot){
			i++;
			tmp = t[i];
			t[i] = t[j];
			t[j] = tmp;
		}
	}
	//zamieniam element rozdzielajcy z ostatnio zamienionym w pętli
	tmp = t[i];
	t[i] = t[lo];
	t[lo] = tmp;

	return i; //zwracam pozycje w talblicy elementu rozdzielajacego
}

void print_flat(int* t, int n){
	int i;
	for(i = 0; i < n; i++){
		printf("%d ", t[i]);
	}
	printf("\n");
}