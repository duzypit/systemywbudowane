/*
 * @author Tomasz Piątek
 * @brief Literals 3-pkt Write a function to compare two numbers of float. Add unit tests to check if its right.
 */
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <limits>



void usage(char* prog);
bool compare(float a, float b);
void res(bool c);
void unit_test();

int main(int argc, char*argv[]){

	if(argc != 2){
		usage(argv[0]);
	}

	if(std::string(argv[1]) == std::string("p")){
	float x, y;
		std::cout << "give me me float 1: " << std::endl;
		std::cin >> x;
		std::cout << "give me float 2: " << std::endl;
		std::cin >> y;

		res(compare(x, y));
	}

	if(std::string(argv[1]) == std::string("t")){
		unit_test();
	}

	return 0;
}


void res(bool test){
	if(test){
		std::cout << "Result: same" << std::endl;
	} else {
		std::cout << "Result: different" << std::endl;
	}
}

void usage(char* prog){
	std::cout << "Usage: " << prog << " option" << std::endl;
	std::cout << "Options: t - run test, p - run program" << std::endl;
	std::exit(0);
}

bool compare(float a, float b)
{
    return std::fabs(a - b) < std::numeric_limits<float>::epsilon();
}

void unit_test(){
	float pi = 3.14159;
    float x = 1.2345 * pi;
    float y = 1.2345 * pi;
    std::cout << "Test1" << std::endl;
    std::cout << "Compare x: " << x << " y: " << y << " expected tesult: same" << std::endl;
    res(compare(x, y));

    x = 1.2345678 * pi;
    y = 1.2345 * pi;
    std::cout << "Test2" << std::endl;
    std::cout << "Compare x: " << x << " y: " << y << " expected tesult: different" << std::endl;   
    res(compare(x, y));

    x = 1.2345678 * pi;
    y = 1.23456666666666 * pi;
    std::cout << "Test3" << std::endl;
    std::cout << "Compare x: " << x << " y: " << y << " expected tesult: different" << std::endl; 
    res(compare(x, y));
}
