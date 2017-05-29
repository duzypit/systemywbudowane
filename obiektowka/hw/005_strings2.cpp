/*
 * @author Tomasz Piątek
 * @brief Strings 3-pkt Write a program to revert a string (const char*, std::string)
 */

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>

void rev_c_style(void);
void rev_cpp_style(void);

int main(){

	rev_c_style();
	rev_cpp_style();

	return 0;
}

void rev_c_style(void){

	const char* source = "Rägnarock Mötorhead";
	int length = strlen(source) ;
	
	char* dest = NULL;
	dest = (char*)malloc(length * sizeof(char));
	strcpy(dest, source);

    int c, i, j;

    for (i = 0, j = length - 1; i < j; i++, j--)
    {
        c = dest[i];
        dest[i] = dest[j];
        dest[j] = c;
    }

    std::cout << "Source: " << source << " dest (std::reverse): " << dest << std::endl;

}

void rev_cpp_style(void){
	std::string source("Rägnarock Mötorhead");
	std::string dest(source);
	std::reverse(dest.begin(), dest.end());

	std::cout << "Source: " << source << " dest (std::reverse): " << dest << std::endl;

}