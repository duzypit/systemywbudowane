#include <iostream>
#include <thread>
#include <unistd.h>

struct My_Thread
{
	void operator()() const {
		std::cout << "New thread\n";
		sleep(5);
	}
};

int main()
{
	std::cout << "Main thread\n";
	My_Thread myTh;
	std::thread th{myTh};

	std::cout << "Main thread before join\n";
	th.join(); 
	std::cout << "Main thread after join\n";
	
	return 0;
}
