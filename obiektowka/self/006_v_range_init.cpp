#include <iostream>
#include <vector>
#include <string>

void print_vector(std::vector<std::string> v){
	for(auto const &elem: v){
		std::cout<<elem<< ' ';
	}
	std::cout << '\n';
}

int main(){
	
	//certain eleme, number of times
	std::vector<std::string> v(4, "test");
	std::cout << "v: " << "\n";
	print_vector(v);
	std::vector<std::string> v1(v.begin(), v.end());
	std::cout << "v1: " << "\n";
	print_vector(v1);

}

