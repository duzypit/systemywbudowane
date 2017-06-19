#include <iostream>
#include <thread>
#include <future>


int factorial(std::shared_future<int> f)
{
	int res = 1;
	
	std::cout << "New thread : waiting for a future to be ready..." << std::endl;	
	int N = f.get();
	std::cout << "New thread : future received" << std::endl; 

	for(int i = 1 ; i <= N ; i++)
		res *= i;
	
	std::this_thread::sleep_for(std::chrono::seconds(5));
	return res;
}

int main()
{
	int result = 0;

	std::promise<int> p;
	std::future<int> f = p.get_future();
	//A shared_future object behaves like a future object, except that it can be copied, and that more 
	//than one shared_future can share ownership over their end of a shared state. They also allow the 
	//value in the shared state to be retrieved multiple times once ready.

	//shared_future objects can be implicitly converted from future objects (see its constructor), or 
	//explicitly obtained by calling future::share. In both cases, the future object from which it is 
	//obtained transfers its association with the shared state to the shared_future and becomes itself non-valid.

	//The lifetime of the shared state lasts at least until the last object with which it is associated is destroyed. 
	//Retrieving the value from a shared_future (with member get) does not release its ownership over the shared state 
	//(unlike with futures). Therefore, if associated to shared_future objects, the shared state can survive the object 
	//from which it was obtained in the first place (if any).
	std::shared_future<int> sf = f.share();
	 
	std::cout << "Main thread : before async" << std::endl;
	std::future<int> fu1 = std::async(std::launch::async, factorial, sf); 
	std::future<int> fu2 = std::async(std::launch::async, factorial, sf); 
	std::future<int> fu3 = std::async(std::launch::async, factorial, sf); 

    p.set_value(4);	
	
	result = fu1.get();
	std::cout << "Main thread: result = " << result << std::endl;
	
	result = fu2.get();
	std::cout << "Main thread: result = " << result << std::endl;

	result = fu3.get();
	std::cout << "Main thread: result = " << result << std::endl;

	return 0;
}

