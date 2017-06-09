#include <iostream>
#include <thread>

void fun(int* ptr)
{
	//std::this_thread
	std::cout << "Moje id = " << std::this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));

	std::cout << "zapisujemy...\n";
	*ptr = 20;
	//error: ‘i’ was not declared in this scope
	//std::cout<<"i (wewnątrz fun()) = " << i << std::endl;
}

void createThread()
{
	int i = 10;
	std::thread th(fun, &i);
	std::cout<<"i (przed th.detach()) = " << i << std::endl;
	/*
	std::thread::detach
	Detaches the thread represented by the object from the calling thread, allowing them to execute independently from each other.

	Both threads continue without blocking nor synchronizing in any way. Note that when either one ends execution, its resources are released.

	After a call to this function, the thread object becomes non-joinable and can be destroyed safely.
	*/
	th.detach();
	std::cout<<"i (po th.detach()) = " << i << std::endl;
}

int main()
{
	std::cout << "odpalam createThread()" <<std::endl;
	createThread();
	std::this_thread::sleep_for(std::chrono::seconds(10));
	return 0;
}
