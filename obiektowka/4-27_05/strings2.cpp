#include <iostream>
#include <algorithm>
//Strings 3-pkt Write a program to revert a string (const char*, std::string)


int main (){

	//const char* 
	std::string f("łódź");
    std::string copy(f);
    std::reverse(copy.begin(), copy.end());
    std::cout << f << '\n' << copy << '\n';


	return 0;
}