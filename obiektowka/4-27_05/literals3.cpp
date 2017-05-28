#include <iostream>
#include <cmath>
#include <limits>
//Literals 3-pkt Write a function to compare two numbers of float. Add unit tests to check if its right.

bool compare(float a, float b);

int main(){

	float x, y;
	std::cout << "give me me float 1: " << std::endl;
	std::cin >> x;
	std::cout << "give me float 2: " << std::endl;
	std::cin >> y;

	if(compare(x, y)){
		std::cout << "same" << std::endl;
	} else {
		std::cout << "different" << std::endl;
	}

	return 0;
}

bool compare(float a, float b)
{
    return std::fabs(a - b) < std::numeric_limits<float>::epsilon();
}

void unit_test(){
	//http://www.cplusplus.com/forum/beginner/118693/
	//tc1

	//tc2

	//tc3
}
