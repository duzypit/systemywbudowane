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
	for(const auto& r: arr){
	 	os << r;
		if(r != arr.back()){
			os << ", ";
		}
	}
	os << "]";
	return os;
}

int main(){
//cpp
	std::array<int, 3> a1 {1,2,3};
	std::cout << "Array a1: " << a1 << std::endl;
	std::reverse(a1.begin(), a1.end());
	std::cout << "Array c++ reverse (std::reverse): " << a1 << std::endl;

//c
	int c[] = {1,2,3,4,5};
	int len = sizeof(c)/sizeof(c[0]);
	
	int i = len - 1;
  	int j = 0;
  	while(i > j)
  	{
    	int temp = c[i];
    	c[i] = c[j];
    	c[j] = temp;
    	i--;
    	j++;
  	}

	std::cout << "Array reverse c style: ";
	for(int i = 0; i < len; i++){
		std::cout << c[i] << " ";
	}
	std::cout << std::endl;	

	return 0;
}