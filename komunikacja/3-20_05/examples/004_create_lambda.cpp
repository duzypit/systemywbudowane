#include <iostream>
#include <thread>
#include <unistd.h>

int main()
{
	std::cout << "Main thread\n";

	std::thread th([]() {
			std::cout << "New thread\n";
			sleep(5);
		});

	std::cout << "Main thread before join\n";
	th.join(); 
	std::cout << "Main thread after join\n";
	
	return 0;
}
