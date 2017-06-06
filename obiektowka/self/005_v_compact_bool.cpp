#include <iostream>
#include <vector>

int main(){
	//compacting bools ex - compact 8 booleans into a byte
	std::vector<bool> v {true, false, false, true, true};
	std::cout << "the length is: " << v.size() << '\n';

	for(auto const &elem: v){
		std::cout<<elem<< ' ';
	}
	std::cout << '\n';
}

