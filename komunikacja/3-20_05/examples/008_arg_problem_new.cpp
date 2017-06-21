#include <iostream>
#include <thread>

void fun(int* ptr)
{
	std::this_thread::sleep_for(std::chrono::seconds(5));
	std::cout << "zapisujemy...\n";
	std::cout<<"i (w fun()) " << *ptr << std::endl;

	*ptr = 20;
	std::cout<<"i (w fun() po zwiększeniu) " << *ptr << std::endl;

}

void createThread()
{
	int* i = new int();
	std::thread th(fun, i);
	std::cout<<"i (przed delete, po wysłaniu do fun) = " << *i << std::endl;
	delete i;
	th.detach();
}

int main()
{
	createThread();

	std::this_thread::sleep_for(std::chrono::seconds(10));
	return 0;
}
