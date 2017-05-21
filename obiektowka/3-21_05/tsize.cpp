//1 rozmiar tablicy w funkcji
#include <iostream>

void tsize(int tabl[5]){
	int size = sizeof(tabl)/sizeof(int);
	std::cout << "func size: " << size << std::endl;
}

template<int N>
void tsize3(std::array<int, N> arr){
	std::cout << arr.size() << size << std::endl;
}



void tsize2(std::array<int, 10> arr){
	std::cout << arr.size() << size << std::endl;
}


int main(void){
	

	int tabl[] = {1,2,3,4,5};
	int size = sizeof(tabl)/sizeof(int);
	std::cout << "size: " << size << std::endl;	
	tsize(tabl);
	//std::array <int, 10> array {0,1,2,3} - deklaracja, rozmiar zawsze musi byc podany 
	//array.size(); 
	// kopiowanie przez przypisanie, jesli rozmiar jest rozny, kompilator krzyknie
	//arr.data() - zwraca wskaznik na pierwszy element tablicy	
	return 0;
}