#include <iostream>
#include <vector>

int main(){
	std::vector<int> array {0,1,2};
	array.resize(5); //set size to 5
	std::cout<< "Lenght is: " << array.size() << std::endl;

	for (auto const &elem: array){
		std::cout << elem << ' '; //empty elements filled with zeros
	}
	std::cout << std::endl;

	array.resize(3); //set size to 5
	std::cout<< "Shrinked Lenght is: " << array.size() << std::endl;


	for (auto const &elem: array){
		std::cout << elem << ' '; 
	}
	std::cout << std::endl;
}

