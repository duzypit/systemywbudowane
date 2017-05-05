#include <stdio.h>


void bubble(int* t, int n);
void print_flat(int* t, int n);

int main(void){
	//tablica do posortowania
	int tab[] = {0,9,2,7,3,4,5,8,1};
	//rozmiar tablicy
	int n = sizeof(tab) / sizeof(tab[0]);
	print_flat(tab, n);
	//sortowanie
	bubble(tab, n);
	//wynik
	puts("* bubble");
	print_flat(tab, n);

	return 0;
}

void bubble(int* t, int n){
	int i, tmp;

	int change;
	do{ //powtarzaj, jeśli była zamiana
		change = 0;
		for(i = 0; i < n; i++){
			//jeśli element większy od następnego - zamień
			if(t[i] > t[i+1]){
				tmp = t[i];
				t[i] = t[i+1];
				t[i+1] = tmp;
				change = 1;
			}
		}
	} while (change == 1);
}


void print_flat(int* t, int n){
	int i;
	for(i = 0; i < n; i++){
		printf("%d ",t[i]);
	}
	printf("\n");
}