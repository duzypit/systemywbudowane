/*
 * @author Tomasz Piątek
 * @brief Arrays 3-pkt Write a program to concatenate two tables.
 */

#include <iostream>
#include <array>
#include <algorithm>

template <typename T, size_t N>
std:: ostream& operator<<(std::ostream& os, const std::array<T, N>&arr){
	os << "[";
	for(auto r: arr){
	 	os << r;
		if(r != arr.back()){
			os << ", ";
		}
	}
	os << "]";
	return os;
}

int main(){
// c style
	int b1[] = {1,2,3};
	int b2[] = {4,5,6};
	int b3[6] = {};

	int i = 0;
	int size = sizeof(b1)/sizeof(b1[0]);
	for(i = 0; i < size; i++){
		b3[i] = b1[i];
	}

	for(int j = 0; j < size; j++){
		b3[i+j] = b2[j];
	}

	std::cout << "B3 (copied b1, b2): ";
	for(i = 0; i < 6; i++){
		std::cout << b3[i] << " ";
	}
	std::cout << std::endl;

//cpp style
	std::array<int, 3> a1 {1,2,3};
	std::array<int, 3> a2 {4,5,6};
	std::array<int, 6> a3;
	std::merge(std::begin(a1), std::end(a1), std::begin(a2),std::end(a2),std::begin(a3));

	std::cout << "Array a1: " << a1 << std::endl;
	std::cout << "Array a2: " << a2 << std::endl;
	std::cout << "Array a3 (std::merge a1, a2): " << a3 << std::endl;


	return 0;
}
