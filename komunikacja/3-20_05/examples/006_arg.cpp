#include <iostream>
#include <thread>
#include <unistd.h>

void fun(int arg1, int* arg2, int& arg3,  std::string str)
{
	arg1 = 20;
	*arg2 = 20;
	arg3 = 20;
	str = "nowy tekst";
}

int main()
{
	int a = 1, b = 1, c = 1;
	std::string temp{"hello world"};

	std::thread th{fun, a, &b, std::ref(c), temp};
	th.join(); 

	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "c = " << c << std::endl;
	std::cout << "temp = " << temp << std::endl;
	
	return 0;
}
