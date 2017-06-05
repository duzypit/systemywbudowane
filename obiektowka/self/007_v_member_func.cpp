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
	std::vector<std::string> v(2, "test");
	std::cout << "initial v: " << "\n";
	print_vector(v);

	v.push_back("its not test?");
	std::cout << "v.push_back(): " << "\n";
	print_vector(v);

	std::vector<std::string>::iterator i = v.begin();
	v.insert(i, "its a test!");
	std::cout << "v.insert(): " << "\n";
	print_vector(v);

	v.pop_back();
	v.pop_back();
	std::cout << "2x v.pop_back(): " << "\n";
	print_vector(v);

	v.erase(i);
	std::cout << "v.erase(0): " << "\n";
	print_vector(v);	

	std::vector<std::string> v2 (4, "jan");
	v.swap(v2);
	std::cout << "v.swap(): " << "\n";
	print_vector(v);
	print_vector(v2);

	v.clear();
	std::cout << "v.clear() - its not deleted: " << "\n";
	print_vector(v);


	std::cout << "v.size - its not deleted: " << v.size() << "\n";
	std::cout << "v.empty - its not deleted: " << v.empty() << "\n";
	std::cout << "v.capacity - its not deleted: " << v.capacity() << "\n\n";

	std::cout << "v2.at(num): " << v2.at(0) << "\n";
	std::cout << "v2.front(): " << v2.front() << " v2.back(): " << v2.back() << "\n";



}

