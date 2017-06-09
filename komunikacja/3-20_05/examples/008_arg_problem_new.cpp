#include <iostream>
#include <thread>

void fun(int* ptr)
{
	std::this_thread::sleep_for(std::chrono::seconds(5));
	std::cout << "zapisujemy...\n";
	*ptr = 20;
}

void createThread()
{
	int* i = new int();
	std::thread th(fun, i);
	std::cout<<"i (przed delete, po podaniut do fun) = " << i << std::endl;
	delete i;
	th.detach();
}

int main()
{
	createThread();

	std::this_thread::sleep_for(std::chrono::seconds(10));
	return 0;
}
