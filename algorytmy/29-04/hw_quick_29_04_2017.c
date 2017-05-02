#include <stdio.h>
//funkcje pomocnicze
//wyswietlaja zawartosc tablicy
void print_tab(int* t, int n);
void print_flat(int* t, int n);

//glowna funkcja, rekrurencja
void quick_sort(int* t, int lo, int hi);

//funkcja partycjonujaca
int part(int* t, int lo, int hi);

int main(void){
	//int tab[] = {23,9,2,7,3,4,5,8,1};
	int tab[] = {23,9,45,2,7,32,3,4,5,87,8,1};
	int n = sizeof(tab) / sizeof(tab[0]);
	
	puts("* init");
	print_flat(tab, n);

	quick_sort(tab, 0, n);
	
	puts("* quick");
	print_flat(tab, n);

	return 0;
}

void print_tab(int* t, int n){
	int i;
	for(i = 0; i < n; i++){
		printf("%d : %d\n", i, t[i]);
	}
	puts("\n");
}

void print_flat(int* t, int n){
	int i;
	for(i = 0; i < n; i++){
		printf("%d ", t[i]);
	}
	puts("\n");
}

void quick_sort(int* t, int lo, int hi){
	int pos;
	if(lo < hi) {
		pos = part(t, lo, hi);
		quick_sort(t, lo, pos);
		quick_sort(t, pos+1, hi);
	}
}

int part(int* t, int lo, int hi){
	int pivot = t[lo];
	int i = lo;
	int j;
	int tmp;
	for( j = i; j < hi; j++ ){
		if(t[j] < pivot){
			i++;
			tmp = t[i];
			t[i] = t[j];
			t[j] = tmp;
		}
	}
	printf("* * i:%d, hi: %d\n", lo, hi);
	tmp = t[i];
	t[i] = t[lo];
	t[lo] = tmp;
	print_flat(t, hi);
	return i;
}