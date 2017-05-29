/*
 * @author Tomasz Piątek
 * @brief Strings 3-pkt Write a program to copy a string as a const char* and std::string into another one.
 */

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>

void copy_c_style(void);
void copy_cpp_style(void);

int main(){

	copy_c_style();
	copy_cpp_style();

	return 0;
}

void copy_c_style(void){

	size_t size = strlen("test string 1");
	const char* source = "test string 1";

	char* dest = NULL;
	dest = (char*)malloc(size * sizeof(char));
	strcpy(dest, source);
	std::cout << "Source: " << source << " dest (after strcpy): " << dest << std::endl;

}

void copy_cpp_style(void){
	std::string source ("test string 2");
	std::string dest(source);
	
	std::cout << "Source: " << source << " dest (copy ctor): " << dest << std::endl;

}

