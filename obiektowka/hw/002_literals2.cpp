/*
 * @author Tomasz Piątek
 * @brief Literals 2-pkt Write a program to get a number and display it in dec oct hex val.
 */
#include <iostream>
// 

int main(){
	int n;
	std::cout << "Give me a number: " << std::endl;
	std::cin >> n;

	std::cout << "Dec: " << std::dec << n << std::endl;
	std::cout << "Oct: " << std::oct << n << std::endl;
	std::cout << "Hex: " << std::hex << n << std::endl;
	return 0;
}
