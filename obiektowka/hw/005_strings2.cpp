/*
 * @author Tomasz Piątek
 * @brief Strings 3-pkt Write a program to revert a string (const char*, std::string)
 */

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>
#include <codecvt>
#include <locale>

void rev_c_style(void);
void rev_cpp_style(void);

int main(){

	rev_c_style();
	rev_cpp_style();

	return 0;
}

void rev_c_style(void){

	// const char* source = "Rägnarock Mötorhead";
	const char* source = "łódż";

	int length = strlen(source) ;
	std::cout << "length -c: " << length << std::endl;
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

    std::cout << "Source: " << source << " dest: " << dest << std::endl;

}

void rev_cpp_style(void){
	std::string source("Rägnarock Mötorhead");

	std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8_conv;
	std::wstring dest = L"Rägnarock Mötorhead";

	std::reverse(dest.begin(), dest.end());

	std::cout << "Source: " << source << " dest (std::reverse + utf8_conv): " << utf8_conv.to_bytes(dest) << std::endl;

}