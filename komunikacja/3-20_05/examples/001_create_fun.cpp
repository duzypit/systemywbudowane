#include <iostream>
#include <thread> //std::thread
#include <unistd.h>

void fun()
{
	std::cout << "New thread\n";
	sleep(5);
}

int main()
{
	std::cout << "Main thread\n";
	//Thread Class to represent individual threads of execution.
	std::thread th{fun}; //uniform initialization removing the distinction between initialization of aggregate + non-aggregate classes, arrays, STL/custom collection classes, and PODs.
	//std::thread th(fun);
	
	std::cout << "Main thread before join\n";
	th.join(); 
	std::cout << "Main thread after join\n";
	
	return 0;
}
