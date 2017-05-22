#include <iostream>
#include <thread>
#include <unistd.h>

class My_Thread
{
public:
	void th_fun()  {
		std::cout << "New thread\n";
		sleep(5);
	}
};

int main()
{
	std::cout << "Main thread\n";
	My_Thread myTh;
	std::thread th{&myTh.th_fun};

	std::cout << "Main thread before join\n";
	th.join(); 
	std::cout << "Main thread after join\n";
	
	return 0;
}
