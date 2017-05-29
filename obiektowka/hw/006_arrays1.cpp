/*
 * @author Tomasz Piątek
 * @brief Arrays 3-pkt Write a program to concatenate two tables.
 */

#include <iostream>
#include <array>

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
	std::array<int, 3> a1 {1,2,3};
	std::array<int, 3> a2 {4,5,6};
	std::array<int, 6> a3;
	std::merge(std::begin(a1), std::end(a1), std::begin(a2),std::end(a2),std::begin(a3));

	std::cout << "Array a1: " << a1 << std::endl;
	std::cout << "Array a2: " << a2 << std::endl;
	std::cout << "Array a3 (std::merge a1, a2): " << a3 << std::endl;


	return 0;
}
