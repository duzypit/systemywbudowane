#include <iostream>
#include <thread>
#include <unistd.h>

void fun()
{
	std::cout << "New thread\n";
	sleep(5);
}

int main()
{
	std::cout << "Main thread\n";
	std::thread th{fun}; //uniform initialization
	//std::thread th(fun);
	
	std::cout << "Main thread before join\n";
	th.join(); 
	std::cout << "Main thread after join\n";
	
	return 0;
}
