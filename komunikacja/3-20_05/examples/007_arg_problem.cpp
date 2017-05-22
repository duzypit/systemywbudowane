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
	int i = 10;
	std::thread th(fun, &i);
	th.detach();
}

int main()
{
	createThread();
	std::this_thread::sleep_for(std::chrono::seconds(10));
	return 0;
}
