#include <stdio.h>

void shell_sort(int* t, int n);
void print_flat(int* t, int n);

int main(void){
	int tab[] = {23,9,2,7,3,4,5,8,1};
	int n = sizeof(tab) / sizeof(tab[0]);

	print_flat(tab, n);
	shell_sort(tab, n);
	puts("* shell");
	print_flat(tab, n);

	return 0;
}

void shell_sort(int* t, int n){
	int gap, temp, i, j;
	for(gap = n/2; gap > 0; gap /= 2){ //wyznaczam przedział na n/2, każdy kolejny = przedział/2, pętla powtarza się, jeśli przedzia >0
		for(i = gap; i < n; i++){ //i = przedział, pętla powtarza się jeśli i < niż wielkośc sortowanej tablicy
			temp = t[i]; //do zmiennej tymaczasowej przypisuję wartość od której zaczynam przeszukiwać tablicę
			for(j = i; j >= gap && t[j-gap] > temp; j -= gap){ 
			//i jest równe wartości równej wielkości przedziału, trwa jeśli wartość j >= wielkości przedziału i wartość po przeciwnej
			//stronie przedziału jest większa niż wartosć w zmiennej tymczaoswej.
				t[j] = t[j-gap];
			}
			t[j] = temp;
		}
	}
}

void print_flat(int* t, int n){
	int i;
	for(i = 0; i < n; i++){
		printf("%d ", t[i]);
	}
	printf("\n");
}