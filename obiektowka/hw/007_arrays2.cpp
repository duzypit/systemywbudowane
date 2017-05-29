/*
 * @author Tomasz Piątek
 * @brief Arrays 3-pkt Write a program to revert values from an array.
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
	std::array<int, 3> a1 {1,2,3};
	std::cout << "Array a1: " << a1 << std::endl;
	std::reverse(a1.begin(), a1.end());
	std::cout << "Array a1 (std::reverse): " << a1 << std::endl;


	return 0;
}
